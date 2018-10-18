# vjudge作弊检测

## 简介
初步检测在 [vjudge](http://vjudge.net/) 比赛中的作弊行为，给出方便进一步查验的报告。基于 Python3.6 编写。

使用 [Moss](http://theory.stanford.edu/~aiken/moss/) 进行作弊检测。使用了 [moss.py](https://github.com/soachishti/moss.py) 调用服务。

支持使用 Moss 中所支持的参数，支持同一用户同一题目提交的去重，支持 C/C++，Python，Java的检测，支持忽略问题以及忽略用户。

演示 Demo：https://nedchu.github.io/vjudge-cheat-detection/

## 使用方式

### 安装
确认使用 Python3 环境，本地获取之后，使用 requirements.txt 进行安装，运行 `pip install -r requirements.txt`

为使用 Moss 进行检测需要通过邮箱注册。请根据 [Moss主页](http://theory.stanford.edu/~aiken/moss/) 中的 Registering for Moss 通过邮箱进行注册，获得合法的 userid 后使用。

moss.py 之前在处理中文 utf-8 编码的时候会产生一些问题，讨论过后在版本 1.0.7 中进行了修复。使用 `pip` 安装的版本中还没有更新，可以直接从 [moss.py](https://github.com/soachishti/moss.py) 获得最新的代码。


### 输入输出

vjudge 比赛的拥有者能够在 Setting 中导出所有的提交文件打包的 zip 压缩文件，以此文件为输入。

内容输出到输入文件所在文件夹下，以比赛名称形成一个文件夹包含如下内容：

- submissions: 包含了所有提交，第一层为题目编号，第二层为该编号题目的所有提交，通过解压缩输入文件能够直接获得
- result_buffer: 所有 Moss 输出的检测报告，第一层为语言名，第二层为题号，第三层为题号下该语言的所有检测报告，打开 index.html 查看
- result: 基于 result_buffer 下的文件进行更改后的结果，加入了返回标签，在结果主页中使用，结构与 result_buffer 一致
- 结果主页: 若干个 html 文件，每个文件是集成了 result 中所有含有异常的题目的检测报告，按照题号分别报告。报告名称由比赛名称，提交语言构成，没有异常的输出报告不会被加入

### 参数说明

| 参数 |  变量类型 | 说明 |
| ------ | ------ | ---------------|
| -c | `file_path` | YAML配置文件，书写规范见配置文件部分 |
| -l | `str list` | 检测的语言，支持：`cc, java, python` |
| -a | `directory` | `${add_dir}/${problem_id}` 下是题号对应的附加检测文件，检查对网络代码或以往作业代码的抄袭 |
| -r | 无变量 | 是否移除用户同一题的重复提交 |
| -u | `regex list` | 一系列正则表达式，匹配任一正则表达式的用户名会被包含进检测 |
| -iu | `str list` | 需要忽略的用户名，优先级高于包含 |
| -ip | `str list` | 需要忽略的问题ID |

WIP

### 配置文件
长期无需改变的参数可以保存于 YAML 配置文件中供程序使用，优先使用命令行参数，其次使用配置文件。

这是 [配置文件模板](./config_template.yml) 请自行修改使用。

WIP

## TODO
- [x] 尝试其他工具如 moss
- [x] 删除同一个人，同一题目的多次通过提交，通过配置文件进行设置，默认关闭，暂时考虑当同一人的两次提交字符数相差不大时只保留其中的一份
- [ ] 利用账号密码和比赛的 ID 直接模拟登陆，登陆所需信息在配置文件中设置
- [x] 指定模板代码，一些题目需要特定算法，容易形成大量相同代码片段，与模板代码近似的代码不会被检测和报告，通过配置文件指定关系。在某默认文件夹下放模板文件，然后文件名对应一系列题号
- [x] 通过设置文件指定忽略一些 ID 的提交
- [ ] 通过爬虫获得网络中的代码进行检测，初步构想根据百度结果前几页获得代码，需要支持CSDN以及博客园
- [ ] 检测配置参数是否符合要求
- [ ] 正则表达式匹配用户名，然后再忽略
- [ ] 工具各部分的分离
