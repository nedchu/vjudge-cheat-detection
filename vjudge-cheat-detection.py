import argparse
import requests
import zipfile
import os
import bs4
import shutil
import json
import difflib
import mosspy
import glob
import collections
import logging
import mosspy
import yaml

from jinja2 import Template, PackageLoader, Environment


def ensure_list(item):
    if item is None:
        return []
    elif type(item) is list:
        return item
    else:
        return [item]

def get_config():
    parser = argparse.ArgumentParser(description='Detect cheat in vjudge contest.')

    parser.add_argument(dest='files', type=str, nargs='+',
                        help='zip files of vjudge contest submission')
    parser.add_argument('-z', '--zip', dest='output_zip',
                        action='store_true', help='build zip archive for output')
    parser.add_argument('-u', '--unique', dest='unique_submission', action='store_true',
                        help='retain only one copy of code when meeting similar submissions of a single user')
    parser.add_argument('-m', '--moss', dest='moss_userid', action='store', help='specify moss userid and use moss to detect cheating, regiester one if you don\'t have your own userid')
    parser.add_argument('-c', '--config', dest='config_file', action='store', help='config file')
    parser.add_argument('-iu', '--ignore-userid', nargs='+', dest='ignore_userid', default=[])
    parser.add_argument('-ip', '--ignore-problem', nargs='+', dest='ignore_problem', default=[])
    parser.add_argument('-l', '--language', dest='language', nargs='+', default=['cc'])
    parser.add_argument('-b', '--base-dir', dest='base_dir')
    parser.add_argument('-M', '--maximal-match', type=int, dest='maximal_match', default=10)
    parser.add_argument('-n', '--report-number', type=int, dest='report_number', default=250)

    config = parser.parse_args()
    if config.config_file is not None:
        with open(config.config_file, "r", encoding='utf-8') as f:
            y = yaml.load(f)
            config.moss_userid = config.moss_userid or y.get("moss_userid")
            config.output_zip = config.output_zip or y.get("output_zip")
            config.unique_submission = config.unique_submission or y.get("unique_submission")
            config.ignore_userid.extend(ensure_list(y.get("ignore_userid", [])))
            config.language.extend(ensure_list(y.get("language", [])))
    return config

# prepare
def unzip_file(zip_file_name, unzip_dir):
    try:
        with zipfile.ZipFile(zip_file_name) as zfile:
            zfile.extractall(path=unzip_dir)
        return True
    except:
        print(f"Unable to unzip {zip_file_name}")
    return False


def get_contest_title(contest_id):
    res = requests.get(f"https://vjudge.net/contest/{contest_id}")
    soup = bs4.BeautifulSoup(res.text, 'lxml')
    json_html = soup.find("textarea")
    if json_html is None:
        return None
    else:
        return json.loads(json_html.text)["title"] or None


# preprocess
def output_list(comment, item_list):
    if len(item_list) == 0:
        return
    print(comment)
    print('\n'.join(item_list))


def remove_duplicate(submission_dir):
    user_sub = {}
    for sub in os.listdir(submission_dir):
        user_id = '_'.join(sub.split('_')[1:-1])
        user_sub.setdefault(user_id, []).append(os.path.join(submission_dir, sub))
    
    remove_list = []
    for user_id in user_sub:
        remove_list.extend(sorted(user_sub[user_id])[:-1])
    
    for file_name in remove_list:
        os.remove(file_name)
    return remove_list

def preprocess(unzip_dir, unique_submission, ignore_problem, ignore_userid):
    all_removed = []
    for problem in ignore_problem:
        problem_dir = os.path.join(unzip_dir, problem)
        if os.path.exists(problem_dir):
            shutil.rmtree(problem_dir)
            all_removed.append(problem_dir)
    output_list("Ignored problem:", all_removed)

    all_removed = []
    for problem in os.listdir(unzip_dir):
        problem_dir = os.path.join(unzip_dir, problem)
        for sub in os.listdir(problem_dir):
            user_id = '_'.join(sub.split('_')[1:-1])
            if user_id in ignore_userid:
                all_removed.append(os.path.join(problem_dir, sub))
    for f in all_removed:
        os.remove(f)
    output_list("Ignore submission by userid:", all_removed)

    if config.unique_submission:
        all_removed = []
        for problem in os.listdir(unzip_dir):
            submission_dir = os.path.join(unzip_dir, problem)
            all_removed.extend(remove_duplicate(submission_dir))
        output_list("Removed duplicate file:", all_removed)
    
    # rename *.c to *.cpp
    rename_list = glob.glob(os.path.join(unzip_dir, '*', '*.c'))
    for f in rename_list:
        new_file = f + "pp"
        if os.path.exists(new_file):
            os.remove(f)
        else:
            os.rename(f, new_file)
    output_list("Rename c to cpp:", rename_list)

# postprocess
def replace_html(html_file, source, target):
    with open(html_file, 'r', encoding='GB2312') as f:
        html = f.readlines()
    with open(html_file, 'w', encoding='utf-8') as f:
        f.writelines([line.replace(source, target) for line in html])
    

def build_html(base_dir, all_index_name, build_dir_list):
    if len(build_dir_list) == 0:
        return
    
    # add go back tag to *top.html and index.html
    Problem = collections.namedtuple('Problem', 'url name')

    go_back_tag = '<p><a href="javascript:history.back()">Go Back</a></p>'

    problem_list = []
    for buffer_dir in build_dir_list:
        index_path = os.path.join(buffer_dir, 'index.html')
        html_list = [index_path]
        html_list.extend(list(glob.glob(os.path.join(buffer_dir, '*top.html'))))
        for html_file in html_list:
            replace_html(html_file, '</head>', f'</head>{go_back_tag}')
        problem = os.path.basename(buffer_dir)
        problem_list.append(Problem(os.path.relpath(index_path, base_dir), f'Problem: {problem}'))

    # use template to render main page
    env = Environment(loader=PackageLoader('vjudge-cheat-detection', 'templates'))
    template = env.get_template('base.html')
    all_index_html = template.render(problems=problem_list, title='Moss Result')
    with open(os.path.join(base_dir, all_index_name), 'w') as f:
        f.write(all_index_html)


def moss_download(unzip_dir, result_buffer_dir, config):
    language_list = ['cc', 'java', 'python']
    buffer_dir_list = ['c++', 'java', 'python']
    prefix_list = ['cpp', 'java', 'py']
    for language, dir_lan, prefix in zip(language_list, buffer_dir_list, prefix_list):
        if language not in config.language:
            continue

        for problem in os.listdir(unzip_dir):
            submission_dir = os.path.join(unzip_dir, problem)
            buffer_dir = os.path.join(result_buffer_dir, dir_lan, problem)
            wildcard = os.path.join(submission_dir, f"*.{prefix}")

            if len(list(glob.glob(wildcard))) <= 1:
                continue
            m = mosspy.Moss(config.moss_userid, language)
            m.setIgnoreLimit(config.maximal_match)
            m.setNumberOfMatchingFiles(config.report_number)
            if config.base_dir is not None:
                moss_base_file = os.path.join(config.base_dir, f"{problem}.cpp")
                if os.path.exists(moss_base_file):
                    m.addBaseFile(moss_base_file, "base")
            wildcard = os.path.join(submission_dir, f"*.{prefix}")
            m.addFilesByWildcard(wildcard)
            url = m.send()

            print("Report Url: " + url)
            if not url.startswith("http"):
                continue
            mosspy.download_report(url, buffer_dir + os.sep, 8, logging.INFO)


def moss_build(contest_title, base_dir, result_dir):
    for dir_lan in os.listdir(result_dir):
        build_dir_list = []
        for problem in os.listdir(os.path.join(result_dir, dir_lan)):
            buffer_dir = os.path.join(result_dir, dir_lan, problem)
            if len(list(glob.glob(os.path.join(buffer_dir, '*')))) <= 1:
                continue

            html_file = os.path.join(buffer_dir, 'index.html')
            if os.path.exists(html_file):
                build_dir_list.append(buffer_dir)
        build_html(base_dir, f'{contest_title} {dir_lan}.html', build_dir_list)


def process(file, config):
    if not os.path.exists(file):
        print(f"{file} does not exist.")
        return
    if config.moss_userid is None:
        print("Moss userid is needed.")
        return

    contest_id = os.path.basename(file[:-4])
    contest_title = get_contest_title(contest_id) or contest_id

    base_dir = os.path.join(os.path.dirname(file), contest_title)
    unzip_dir = os.path.join(base_dir, "submissions")
    if os.path.exists(unzip_dir):
        shutil.rmtree(unzip_dir)
    if not unzip_file(file, unzip_dir):
        return

    preprocess(unzip_dir, config.unique_submission, config.ignore_problem, config.ignore_userid)
    
    result_buffer_dir = os.path.join(base_dir, 'result_buffer')
    result_dir = os.path.join(base_dir, 'result')
    if not os.path.exists(result_buffer_dir):
        os.makedirs(result_buffer_dir)
    moss_download(unzip_dir, result_buffer_dir, config)

    # copy result buffer and postprocess
    if os.path.exists(result_dir):
        shutil.rmtree(result_dir)
    shutil.copytree(result_buffer_dir, result_dir)
    moss_build(contest_title, base_dir, result_dir)

    if config.output_zip:
        shutil.make_archive(f"{base_dir} report", 'zip', base_dir)


if __name__ == '__main__':
    config = get_config()
    print(config)
    for file in config.files:
        process(file, config)
