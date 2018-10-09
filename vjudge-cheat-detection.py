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
from jinja2 import Template, PackageLoader, Environment


SIMILAR_RATIO_BOUND = 0.9

def get_args():
    parser = argparse.ArgumentParser(description='Detect cheat in vjudge contest.')

    parser.add_argument(dest='files', type=str, nargs='+',
                        help='zip files of vjudge contest submission')
    parser.add_argument('-z', '--zip', dest='output_zip',
                        action='store_true', help='build zip archive for output')
    parser.add_argument('-u', '--unique', dest='unique_submission', action='store_true',
                        help='retain only one copy of code when meeting similar submissions of a single user')
    parser.add_argument('-m', '--moss', dest='moss_userid', default=None, nargs=1, help='specify moss userid and use moss to detect cheating, regiester one if you don\'t have your own userid')

    return parser.parse_args()


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


def remove_duplicate(submission_dir):
    user_sub = {}
    for sub in os.listdir(submission_dir):
        user_id = '_'.join(sub.split('_')[1:-1])
        user_sub.setdefault(user_id, []).append(os.path.join(submission_dir, sub))
    
    remove_list = []
    for submissions in user_sub.values():
        l = len(submissions)
        f = [open(sub, 'r') for sub in submissions]
        s = list(map(lambda x: ''.join(x.readlines()), f))
        s = list(map(lambda x: ' '.join(x.split()), s))
        for i in range(l):
            should_remove = False
            for j in range(i):
                sim = difflib.SequenceMatcher(None, s[i], s[j]).ratio()
                should_remove |= sim >= SIMILAR_RATIO_BOUND
            if should_remove:
                remove_list.append(submissions[i])
        
        for ff in f:
            ff.close()
    
    for file_name in remove_list:
        os.remove(file_name)
    return remove_list


def replace_html(html_file, source, target):
    with open(html_file, 'r') as f:
        html = f.readlines()
    with open(html_file, 'w') as f:
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


def moss_download(unzip_dir, result_buffer_dir, moss_userid):
    language_list = ['cc', 'java', 'python']
    buffer_dir_list = ['c++', 'java', 'python']
    prefix_list = ['cpp', 'java', 'py']
    for language, dir_lan, prefix in zip(language_list, buffer_dir_list, prefix_list):
        for problem in os.listdir(unzip_dir):
            submission_dir = os.path.join(unzip_dir, problem)
            buffer_dir = os.path.join(result_buffer_dir, dir_lan, problem)
            wildcard = os.path.join(submission_dir, f"*.{prefix}")

            if len(list(glob.glob(wildcard))) <= 1:
                continue
            print(moss_userid, language, wildcard, list(glob.glob(wildcard)))
            m = mosspy.Moss(moss_userid, language)
            m.addFilesByWildcard(wildcard)
            url = m.send()

            print("Report Url: " + url)
            if not url.startswith("http"):
                continue
            mosspy.download_report(url, buffer_dir + os.sep, connections=8)


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


def process(file, output_zip=False, unique_submission=False, moss_userid=None):
    if not os.path.exists(file):
        print(f"{file} does not exist.")
        return

    contest_id = os.path.basename(file[:-4])
    contest_title = get_contest_title(contest_id) or contest_id

    base_dir = os.path.join(os.path.dirname(file), contest_title)
    unzip_dir = os.path.join(base_dir, "submissions")
    if not unzip_file(file, unzip_dir):
        return

    if unique_submission:
        all_removed = ["Removed file:"]
        for problem in os.listdir(unzip_dir):
            submission_dir = os.path.join(unzip_dir, problem)
            all_removed.extend(remove_duplicate(submission_dir))
        print('\n'.join(all_removed) + '\n')
    
    if moss_userid is not None:
        result_buffer_dir = os.path.join(base_dir, 'result_buffer')
        result_dir = os.path.join(base_dir, 'result')
        if not os.path.exists(result_buffer_dir):
            os.makedirs(result_buffer_dir)
            moss_download(unzip_dir, result_buffer_dir, moss_userid)

        if os.path.exists(result_dir):
            shutil.rmtree(result_dir)
        shutil.copytree(result_buffer_dir, result_dir)
        moss_build(contest_title, base_dir, result_dir)

    if output_zip:
        shutil.make_archive(f"{base_dir} report", 'zip', base_dir)


if __name__ == '__main__':
    args = get_args()
    for file in args.files:
        process(file, args.output_zip, args.unique_submission, args.moss_userid[0])
