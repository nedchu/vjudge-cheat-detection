import argparse
import requests
import zipfile
import os
import bs4
import pdfkit
import shutil
import json
import subprocess
import difflib
import re
import mosspy
import glob


parser = argparse.ArgumentParser(description='Detect cheat in vjudge contest.')

parser.add_argument(dest='files', type=str, nargs='+',
                    help='zip files of vjudge contest submission')
parser.add_argument('-z', '--zip', dest='output_zip',
                    action='store_true', help='build zip archive for output')
parser.add_argument('-u', '--unique', dest='unique_submission', action='store_true',
                    help='retain only one copy of code when meeting similar submissions of a single user')
parser.add_argument('-m', '--moss', dest='moss_userid', default=None, nargs=1, help='specify moss userid and use moss to detect cheating, regiester one if you don\'t have your own userid')

args = parser.parse_args()

SIMILAR_RATIO_BOUND = 0.9

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


def jplag_build(contest_title, base_dir, unzip_dir, result_buffer_dir):
    language_list = ['c/c++', 'java17', 'python3']
    buffer_dir_list = ['c++', 'java', 'python']
    for language, dir_lan in zip(language_list, buffer_dir_list):
        html_file_list = []
        for problem in os.listdir(unzip_dir):
            submission_dir = os.path.join(unzip_dir, problem)
            buffer_dir = os.path.join(result_buffer_dir, dir_lan, problem)


            subprocess.Popen(['java', '-jar', 'jplag.jar', '-l',
                              language, '-s', submission_dir, '-r', buffer_dir]).wait()
            
            if len(list(glob.glob(os.path.join(buffer_dir, "*")))) <= 8:
                continue
            html_file = os.path.join(buffer_dir, 'index.html')
            if os.path.exists(html_file):
                html_file_list.append(html_file)

        if len(html_file_list) > 0:
            pdfkit.from_file(html_file_list, os.path.join(
                base_dir, f"{contest_title} {dir_lan} jplag.pdf"))


def moss_build(contest_title, base_dir, unzip_dir, result_buffer_dir, moss_userid):
    language_list = ['cc', 'java', 'python']
    buffer_dir_list = ['c++', 'java', 'python']
    prefix_list = ['cpp', 'java', 'py']
    for language, dir_lan, prefix in zip(language_list, buffer_dir_list, prefix_list):
        html_file_list = []
        for problem in os.listdir(unzip_dir):
            submission_dir = os.path.join(unzip_dir, problem)
            buffer_dir = os.path.join(result_buffer_dir, dir_lan, problem)
            wildcard = os.path.join(submission_dir, f"*.{prefix}")

            if len(list(glob.glob(wildcard))) <= 1:
                continue
            m = mosspy.Moss(moss_userid, language)
            m.addFilesByWildcard(wildcard)
            url = m.send()

            print("Report Url: " + url)
            if not url.startswith("http"):
                continue
            mosspy.download_report(url, buffer_dir + os.sep, connections=8)

            if len(list(glob.glob(os.path.join(buffer_dir, "*")))) <= 1:
                continue
            html_file = os.path.join(buffer_dir, 'index.html')
            if os.path.exists(html_file):
                html_file_list.append(html_file)

        if len(html_file_list) > 0:
            pdfkit.from_file(html_file_list, os.path.join(
                base_dir, f"{contest_title} {dir_lan} moss.pdf"))


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
        result_buffer_dir_moss = os.path.join(base_dir, 'result_buffer_moss')
        if not os.path.exists(result_buffer_dir_moss):
            os.makedirs(result_buffer_dir_moss)
        moss_build(contest_title, base_dir, unzip_dir, result_buffer_dir_moss, moss_userid[0])
    
    result_buffer_dir_jplag = os.path.join(base_dir, 'result_buffer_jplag')
    if not os.path.exists(result_buffer_dir_jplag):
        os.makedirs(result_buffer_dir_jplag)
    jplag_build(contest_title, base_dir, unzip_dir, result_buffer_dir_jplag)

    if output_zip:
        shutil.make_archive(f"{base_dir} report", 'zip', base_dir)


if __name__ == '__main__':
    for file in args.files:
        process(file, args.output_zip, args.unique_submission, args.moss_userid)
