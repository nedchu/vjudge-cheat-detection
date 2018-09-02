import argparse
import requests
import zipfile
import os
import bs4
import pdfkit
import shutil


parser = argparse.ArgumentParser(description='Detect cheat in vjudge contest.')

parser.add_argument(dest='files', type=str, nargs='+', help='zip files of vjudge contest submission')
parser.add_argument('-z', '--zip', dest='output_zip', action='store_true', help='build zip archive for output')

args = parser.parse_args()


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
    return soup.find(property="og:title")['content']


def process(file, output_zip=False):
    if not os.path.exists(file):
        print(f"{file} does not exist.")
        return

    contest_id = os.path.basename(file[:-4])
    contest_title = get_contest_title(contest_id)

    base_dir = contest_title
    unzip_dir = os.path.join(base_dir, "submissions")
    if not unzip_file(file, unzip_dir):
        return

    result_buffer_dir = os.path.join(base_dir, 'result_buffer')
    if not os.path.exists(result_buffer_dir):
        os.makedirs(result_buffer_dir)

    language_list=['c/c++', 'java17', 'python3']
    buffer_dir_list = ['c++', 'java', 'python']
    for language, dir_lan in zip(language_list, buffer_dir_list):
        html_file_list = []
        for problem in os.listdir(unzip_dir):
            submission_dir = os.path.join(unzip_dir, problem)
            buffer_dir = os.path.join(result_buffer_dir, dir_lan, problem)
            os.system('java -jar jplag.jar -l %s -s "%s" -r "%s"' % (language, submission_dir, buffer_dir))

            html_file = os.path.join(buffer_dir, 'index.html')
            if os.path.exists(html_file):
                html_file_list.append(html_file)
        
        if len(html_file_list) > 0:
            pdfkit.from_file(html_file_list, os.path.join(base_dir, f"{contest_title} {dir_lan}.pdf"))
    
    if output_zip:
        shutil.make_archive(contest_title, 'zip', base_dir)


if __name__ == '__main__':
    for file in args.files:
        process(file, args.output_zip)