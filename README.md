# vjudge作弊检测
## 简介
初步检测在 vjudge 比赛中的作弊行为，给出方便进一步查验的报告。基于 Python3.6 编写。

使用 [JPlag](https://github.com/jplag/jplag) 以及 [Moss](http://theory.stanford.edu/~aiken/moss/) 进行作弊检测。其中 Moss使用了 [moss.py](https://github.com/soachishti/moss.py) 调用服务。

## 安装
安装 [wkhtmltopdf](https://wkhtmltopdf.org/)，Windows 用户需要将安装好之后的 bin 目录添加到 Path 环境变量中。JPlag 的 jar 包已经包含在工程目录下。

本地获取之后，使用 requirements.txt 进行安装，运行 `pip install -r requirements.txt`

为使用 Moss 进行检测需要通过邮箱注册。请根据 [Moss主页](http://theory.stanford.edu/~aiken/moss/) 中的 Registering for Moss 注册，获得合法的 userid 后使用该功能

## 使用方式

### 输入内容

vjudge 比赛的拥有者能够在 Setting 中导出所有的提交文件打包的 zip 压缩文件，以此文件为输入。

### 输出内容

内容输出到输入文件所在文件夹下，以比赛名称形成一个文件夹包含如下内容：

- submissions: 包含了所有提交，第一层为题目编号，第二层为该编号题目的所有提交，通过解压缩输入文件能够直接获得
- result_buffer_jplag: 报告了所有 JPlag 输出的检测报告，第一层为语言名，第二层为题号，第三层为题号下该语言的所有检测报告，打开 index.html 查看
- result_buffer_moss: 报告了所有 Moss 输出的检测报告，第一层为语言名，第二层为题号，第三层为题号下该语言的所有检测报告，打开 index.html 查看
- 检测报告: 若干个 pdf 文件，每个文件是某个语言所有提交的检测报告，文件中按照题号分别报告，每个报告基于 Jplag, Moss 的输出报告拼接而成。报告名称由比赛名称，提交语言和 jplag/moss 构成，没有异常的输出报告不会被加入

### 使用及例子

利用 `python vjudge-cheat-detection.py -h` 获取帮助。

获得输入内容中所说的提交源码压缩文件后，指定该文件的目录为参数运行。

在目录 `.\demo` 下包含了一个例子，这是许久以前的一次选拔 [ECL Selection](https://vjudge.net/contest/203228)

运行 `python .\vjudge-cheat-detection.py .\demo\203228.zip -z -m $moss_userid`，执行完毕之后在 `.\demo` 下会生成文件夹 `.\demo\ECL Selection` 其中包含了之前所说的输出内容。将这个文件夹内的内容打包成 zip 就获得了 `.\demo\ECL Selection report.zip`，若去除 `-z` 参数就不会输出这个 zip 压缩包，若除去 `-m $moss_userid` 就不会使用 Moss 进行代码检测及生成报告。

在 `.\demo\ECL Selection` 下包含了两份报告以及提交和检测报告，具体构成请移步先前的输出内容模块。检阅两份报告之后可以发现：使用最多的还是 C/C++，使用 Python 提交因为没有发现问题所以并没有生成报告。从报告中可以发现 J 这题有比较大的问题，进一步检查后容易发现有两个账号提交了完全一样的代码，可以确定为抄袭。另有一对代码文件相似度高达 74.4%，结合其余检测结果，可以发现检出了不少模板近似和输入近似，这部分相似是可以接受的，很难断定真相。

代码是相对复杂的，通过本项目能辅助判定作弊，可还是需要人工接入，完全照抄以外的代码仍然很难把握。

### 删除近似代码

同一人可能多次提交同一道题目，有些时候是换了思路编码，有些时候只是更改了一些细节，对于后者希望能够尽量减少近似的代码，减少阅读代码时的排查工作。

`.\demo\unknown.zip` 包含了同一场比赛同一题的三份代码，可以发现其中的两份更改了求解dp的顺序但是思路基本没有变，对于这类近似，通过一些指标能够度量两份代码的近似程度，删除近似的代码。

调用 `python .\vjudge-cheat-detection.py .\demo\unknown.zip -u` 后生成了 `.\demo\unknown`，在目录 `.\demo\unknown\submissions\B` 下有两份代码，这是近似去重之后的结果，该目录下原有的第三份代码，由于只是基于另一份代码进行了小范围改动，在生成报告之前被删去了。

## 实现方式

将源码解压缩后，调用 JPlag 按某一语言进行检测，形成每道题目的作弊检测报告，再将报告的网页整合为一个 pdf 文件进行输出。

检测的语言为 C/C++, Java, Python，针对这三类语言会分别生成一个 pdf 文件。

删除同一人同一道题目的近似代码时，若两份代码去掉空白符后，匹配的代码量占到两份代码总代码量的 $90\%$ 就认为两份代码是类似的，删除其中一份。

## TODO

- [x] 删除同一个人，同一题目的多次通过提交，通过配置文件进行设置，默认关闭，暂时考虑当同一人的两次提交字符数相差不大时只保留其中的一份
- [ ] 利用账号密码和比赛的 ID 直接模拟登陆，登陆所需信息在配置文件中设置
- [ ] 指定模板代码，一些题目需要特定算法，容易形成大量相同代码片段，与模板代码近似的代码不会被检测和报告，通过配置文件指定关系。在某默认文件夹下放模板文件，然后文件名对应一系列题号
- [ ] 输入片段容易类似，通过模板避免进行检测
- [x] 尝试其他工具如 moss