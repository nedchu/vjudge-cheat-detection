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


def get_contest_info(contest_id):
    res = requests.get(f"https://vjudge.net/contest/{contest_id}")
    soup = bs4.BeautifulSoup(res.text, 'lxml')
    json_html = soup.find("textarea")
    if json_html is None:
        return None
    else:
        return json.loads(json_html.text)

def get_userid(filename):
    return '_'.join(filename.split('_')[1:-1])

def get_contest_id(filename):
    return os.path.basename(filename[:-4])

def ensure_list(item):
    if item is None:
        return []
    elif type(item) is list:
        return item
    else:
        return [item]
        