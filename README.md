# vjudge作弊检测

## 简介
初步检测在 [vjudge](http://vjudge.net/) 比赛中的作弊行为，给出方便进一步查验的报告。基于 Python3.6 编写。

使用 [Moss](http://theory.stanford.edu/~aiken/moss/) 进行作弊检测。使用了 [moss.py](https://github.com/soachishti/moss.py) 调用服务。

演示 Demo：https://nedchu.github.io/vjudge-cheat-detection/

## 安装
确认使用 Python3 环境，本地获取之后，使用 requirements.txt 进行安装，运行 `pip install -r requirements.txt`

为使用 Moss 进行检测需要通过邮箱注册。请根据 [Moss主页](http://theory.stanford.edu/~aiken/moss/) 中的 Registering for Moss 通过邮箱进行注册，获得合法的 userid 后使用。

## 使用方式

### 输入内容

vjudge 比赛的拥有者能够在 Setting 中导出所有的提交文件打包的 zip 压缩文件，以此文件为输入。

### 输出内容

内容输出到输入文件所在文件夹下，以比赛名称形成一个文件夹包含如下内容：

- submissions: 包含了所有提交，第一层为题目编号，第二层为该编号题目的所有提交，通过解压缩输入文件能够直接获得
- result_buffer: 所有 Moss 输出的检测报告，第一层为语言名，第二层为题号，第三层为题号下该语言的所有检测报告，打开 index.html 查看
- result: 基于 result_buffer 下的文件进行更改后的结果，加入了返回标签，在结果主页中使用，结构与 result_buffer 一致
- 结果主页: 若干个 html 文件，每个文件是集成了 result 中所有含有异常的题目的检测报告，按照题号分别报告。报告名称由比赛名称，提交语言构成，没有异常的输出报告不会被加入

### 使用及例子

利用 `python vjudge-cheat-detection.py -h` 获取帮助。

展示 demo: https://nedchu.github.io/vjudge-cheat-detection/，使用了许久以前的一次选拔 [ECL Selection](https://vjudge.net/contest/203228)

获得输入内容中所说的提交源码压缩文件后，指定该文件的目录为参数运行，需要通过 `-m` 参数指定 Moss userid 才能够正常使用，若是没有就需要通过 [Moss主页](http://theory.stanford.edu/~aiken/moss/) 中的 Registering for Moss 通过邮箱进行注册。

### 删除近似代码

同一人可能多次提交同一道题目，有些时候是换了思路编码，有些时候只是更改了一些细节，对于后者希望能够尽量减少近似的代码，减少阅读代码时的排查工作。

在考虑是否要保留这个功能。

## TODO
- [x] 尝试其他工具如 moss
- [x] 删除同一个人，同一题目的多次通过提交，通过配置文件进行设置，默认关闭，暂时考虑当同一人的两次提交字符数相差不大时只保留其中的一份
- [ ] 利用账号密码和比赛的 ID 直接模拟登陆，登陆所需信息在配置文件中设置
- [ ] 指定模板代码，一些题目需要特定算法，容易形成大量相同代码片段，与模板代码近似的代码不会被检测和报告，通过配置文件指定关系。在某默认文件夹下放模板文件，然后文件名对应一系列题号
- [ ] 通过设置文件指定忽略一些 ID 的提交
