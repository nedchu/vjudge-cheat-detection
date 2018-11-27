import argparse
import requests
import zipfile
import os
import bs4
import shutil
import json
import mosspy
import glob
import collections
import logging
import mosspy
import yaml
import time
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import Select


def get_config():
    parser = argparse.ArgumentParser(description='Download source code.')

    parser.add_argument(dest='files', type=str, nargs='+',
                        help='zip files of vjudge contest submission')
    parser.add_argument('-ip', dest='ignore_problem', nargs='+', default=[], help='problem to be ignored')
    parser.add_argument('-n', dest='page_num', type=int, default=1)

    config = parser.parse_args()
    return config

Problem = collections.namedtuple("Problem", "oj_id num")

def get_problem_list(contest_id):
    res = requests.get(f"https://vjudge.net/contest/{contest_id}")
    soup = bs4.BeautifulSoup(res.text, 'lxml')
    json_html = soup.find("textarea")
    if json_html is None:
        return None
    else:
        problems = json.loads(json_html.text)["problems"]
        problems = [Problem(p["oj"] + p["probNum"], p["num"]) for p in problems]
        return problems

Solution = collections.namedtuple("Solution", "source url")

def handle_csdn(driver):
    solutions = []
    driver.execute_script('window.scrollTo(0, document.body.scrollHeight)')
    time.sleep(1)
    more = driver.find_element_by_id("btn-readmore")
    more.click()
    for e in driver.find_elements_by_class_name("language-cpp"):
        solutions.append(Solution(e.text, driver.current_url))
    return solutions

def handle_bokeyuan(driver):
    return []

def handle_page(driver):
    solutions = []
    current_url = driver.current_url
    if current_url.find("blog.csdn.net") != -1:
        solutions.extend(handle_csdn(driver))
    elif current_url.find("www.cnblogs.com") != -1:
        solutions.extend(handle_bokeyuan(driver))
    return solutions

def crawl_baidu(search_item, pages=1):
    opts = Options()
    opts.add_argument('headless')
    opts.add_argument("user-agent=Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.86 Safari/537.36")
    driver = webdriver.Chrome(chrome_options=opts)
    time.sleep(1)
    driver.maximize_window()

    base_url = f"https://www.baidu.com/s?wd={search_item}"
    driver.get(base_url)

    real_url_list = []
    solutions = []
    for i in range(pages):
        elements = driver.find_elements_by_class_name("t")
        main_page_handle = driver.current_window_handle
        for e in elements:
            time.sleep(1)
            e.find_element_by_tag_name("a").click()
            for h in driver.window_handles:
                if h != main_page_handle:
                    driver.switch_to.window(h)
                    break
            time.sleep(1)
            real_url_list.append(driver.current_url)
            solutions.extend(handle_page(driver))
            driver.close()
            driver.switch_to.window(main_page_handle)
        try:
            next_btn = driver.find_element_by_class_name("n")
            next_url = str(next_btn.get_attribute("href"))
            driver.get(next_url)
        except:
            break
    print(real_url_list)
    driver.quit()
    return solutions

def process(file, config):
    if not os.path.exists(file):
        print(f"{file} does not exist.")
        return
    if not file.endswith(".zip"):
        print(f"{file} is not zip file.")
        return

    contest_id = os.path.basename(file[:-4])
    problems = get_problem_list(contest_id)
    print(problems)
    base_dir = os.path.join(file[:-4] + "_add")
    for search_item, num in problems:
        output_dir = os.path.join(base_dir, num)
        solutions = crawl_baidu(search_item, config.page_num)
        if len(solutions) == 0 or num in config.ignore_problem:
            continue
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        for i, sol in enumerate(solutions):
            with open(os.path.join(output_dir, f"from_web_{i}.cpp"), 'w', encoding='utf-8') as f:
                f.write(f"// {sol.url}\n")
                f.write(sol.source)


if __name__ == '__main__':
    config = get_config()
    print(config)
    for file in config.files:
        process(file, config)
    