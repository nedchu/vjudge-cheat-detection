# vjudge作弊检测
## 简介
初步检测在 [vjudge](http://vjudge.net/) 比赛中的作弊行为，给出方便进一步查验的报告。基于 Python3.6 编写。

使用 [Moss](http://theory.stanford.edu/~aiken/moss/) 进行作弊检测。使用了 [moss.py](https://github.com/soachishti/moss.py) 调用服务。使用了 [docsify](https://docsify.js.org/) 进行文档构建。

支持如下功能：

- 使用 Moss 中所支持的参数及报告下载
- 同一用户同一题目提交的去重
- C/C++，Python，Java的检测
- 根据 id 忽略问题以及根据 id 忽略用户
- 正则表达式指定包含用户
- 辅助功能：根据题目编号的百度搜索结果获得博客中的源码

## 使用方式

### 安装
确认使用 Python3 环境，本地获取之后，使用 requirements.txt 进行安装，运行 `pip install -r requirements.txt`

为使用 Moss 进行检测需要通过邮箱注册。请根据 [Moss主页](http://theory.stanford.edu/~aiken/moss/) 中的 Registering for Moss 通过邮箱进行注册，获得合法的 userid 后使用。

moss.py 之前在处理中文 utf-8 编码的时候会产生一些问题，讨论过后在版本 1.0.7 中进行了修复。使用 `pip` 安装的版本中还没有更新，可以直接从 [moss.py](https://github.com/soachishti/moss.py) 获得最新的代码。


### 输入输出

vjudge 比赛的拥有者能够在 Setting 中导出所有的提交文件打包的 zip 压缩文件，以此文件为输入。

内容输出到输入文件所在文件夹下，以比赛名称形成一个文件夹包含如下内容：

- submissions: 包含了所有提交，第一层为题目编号，第二层为该编号题目的所有提交，通过解压缩输入文件能够直接获得，预处理后将删去和更改部分文件，用作 Moss 输入文件
- result: 第一层为语言名，第二层为题号，第三层为题号下该语言的所有检测报告。基于 Moss 输出的检测报告，加入了返回标签，在结果主页中使用
- 结果主页: 若干个 html 文件，每个文件是集成了 result 中所有含有异常的题目的检测报告，按照题号分别报告。报告名称由比赛名称，提交语言构成，没有异常的输出报告不会被加入

### 参数说明

| 参数 | 变量类型          | 说明                                                                                            |
| ---- | ----------------- | ----------------------------------------------------------------------------------------------- |
|      | `list<file_path>` | 输入文件目录列表，每个都是从 vjudge 中提交源码的zip                                             |
| -c   | `file_path`       | YAML配置文件，书写规范见配置文件部分                                                            |
| -l   | `list<str>`       | 检测的语言，支持：`cc, java, python`，默认只检测C++                                             |
| -a   | `directory`       | `${add_dir}/${problem_id}` 下是题号对应的附加检测文件，检查对网络代码或以往作业代码的抄袭       |
| -r   | 无变量            | 是否移除用户同一题的重复提交                                                                    |
| -u   | `list<regex>`     | 一系列正则表达式，匹配任一正则表达式的用户名会被包含进检测                                      |
| -iu  | `list<str>`       | 需要忽略的用户名，优先级高于包含                                                                |
| -ip  | `list<str>`       | 需要忽略的问题ID                                                                                |
| -id  | `str`             | Moss 参数，检测使用的 Moss UserID，如果没有请使用邮箱进行注册                                   |
| -b   | `directory`       | Moss 参数，`${base_dir}/${problem_id}` 下是题号对应的基文件，与基文件相同的代码不会被判定为抄袭 |
| -m   | `int`             | Moss 参数，代码片出现多少次后被判定为基文件内容，默认为10                                       |
| -n   | `int`             | Moss 参数，报告中最多呈现多少条匹配报告，默认为250，该值较大时下载报告需要较多时间              |

### 配置文件
长期无需改变的参数可以保存于 YAML 配置文件中供程序使用，优先使用命令行参数，其次使用配置文件。

配置文件模板为 `./config_template.yml` 请自行修改使用。

| 变量             | 变量类型      | 对应参数 |
| ---------------- | ------------- | -------- |
| language         | `list<str>`   | -l       |
| remove_duplicate | `bool`        | -r       |
| ignore_userid    | `list<str>`   | -iu      |
| include_userid   | `list<regex>` | -u       |
| moss_userid      | `str`         | -id      |
| maximal_match    | `int`         | -m       |
| report_num       | `int`         | -n       |

## 辅助工具：爬取网络代码
对于从网络中抄袭源码的行为，提供了 `source_crawler.py` 辅助进行检测。

该工具使用了 Selenium 进行爬取，能够根据题号百度搜索的结果，找到对应页面抽取代码，目前仅支持爬取CSDN中的源码，后续将加入博客园等其它常见的博客平台。

获得的结果源文件开头处会附上源码地址，由于仅仅是爬取结果中的代码，不同页面中的代码可能近似，获得的源码可能并非该题目源码，需要人工判断去除部分代码。

调用程序后在输入文件所在文件夹下根据比赛 id 构建一个文件夹 `${id}_add`，第二级目录为题号，每个文件夹下为对应题目的源码，名称以 from_web_ 打头。

| 参数 | 变量类型          | 说明                                                |
| ---- | ----------------- | --------------------------------------------------- |
|      | `list<file_path>` | 输入文件目录列表，每个都是从 vjudge 中提交源码的zip |
| -ip  | `list<str>`       | 需要忽略的问题ID                                    |
| -n   | `int`             | 对于题号的搜索结果，在百度中取用前多少页            |