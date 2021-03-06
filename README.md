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

文档地址：https://nedchu.github.io/vjudge-cheat-detection/

# TODO
- [x] 尝试其他工具如 moss
- [x] 删除同一个人，同一题目的多次通过提交，通过配置文件进行设置，默认关闭，暂时考虑当同一人的两次提交字符数相差不大时只保留其中的一份
- [ ] 利用账号密码和比赛的 ID 直接模拟登陆，登陆所需信息在配置文件中设置
- [x] 指定模板代码，一些题目需要特定算法，容易形成大量相同代码片段，与模板代码近似的代码不会被检测和报告，通过配置文件指定关系。在某默认文件夹下放模板文件，然后文件名对应一系列题号
- [x] 通过设置文件指定忽略一些 ID 的提交
- [x] 通过爬虫获得网络中的代码进行检测，初步构想根据百度结果前几页获得代码，需要支持CSDN以及博客园
- [ ] 检测配置参数是否符合要求
- [x] 正则表达式匹配用户名，然后再忽略
- [ ] 更加详细的使用教程
- [ ] 统计通过题目数
- [ ] 爬虫支持博客园
