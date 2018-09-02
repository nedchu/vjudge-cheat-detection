# vjudge作弊检测
## 简介
初步检测在 vjudge 比赛中的作弊行为，给出方便进一步查验的报告。基于 Python3.6 以及 [JPlag](https://github.com/jplag/jplag)

## 安装
本地获取之后，安装 [wkhtmltopdf](https://wkhtmltopdf.org/)，Windows用户需要将安装好之后的 bin 目录添加到 Path 环境变量中。

使用 requirements.txt 进行安装，运行 `pip install -r requirements.txt`

## 使用方式
### 输入内容
vjudge比赛的拥有者能够在Setting中导出所有的提交文件打包的压缩文件，以此文件为输入。

### 输出内容
以比赛的名字为名形成一个文件夹包含如下内容：

- submissions: 包含了所有提交，第一层为题目编号，第二层为该编号题目的所有提交，通过解压缩输入文件能够直接获得
- result_buffer: 报告了所有 JPlag 输出的检测报告，第一层为语言名，第二层为题号，第三层为题号下该语言的所有检测报告，打开 index.html 查看
- 检测报告: 若干个 pdf 文件
### 使用
利用 `python vjudge-cheat-detection.py -h` 获取帮助。

获得源码压缩文件放在目录下然后运行程序。

例子：`python vjudge-cheat-detection.py 203228.zip -z`

## 实现方式
将源码解压缩后，调用 JPlag 按某一语言进行检测，形成每道题目的作弊检测报告，再将报告的网页整合为一个 pdf 文件进行输出。

检测的语言为C/C++, Java, Python，针对这三类语言会分别生成一个 pdf 文件。




## TODO
- 删除同一个人，同一题目的多次通过提交，通过配置文件进行设置，默认关闭
- 利用账号密码和比赛的ID直接模拟登陆，登陆所需信息在配置文件中设置
- 指定模板代码，一些题目需要特定算法，容易形成大量相同代码片段，与模板代码近似的代码不会被检测和报告，通过配置文件指定关系。在某默认文件夹下放模板文件，然后文件名对应一系列题号
- 输入片段容易类似，通过模板避免进行检测
- 尝试其他工具如moss