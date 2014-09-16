---
layout: post
title: Markdown输入LaTeX数学公式
category: 技术
tags: Markdown LaTeX
keywords: 
description: 
---

Markdown是读写性都非常好的轻量文本编辑语言，这个博客以及世界上许多博客的文章都是用其书写的。但是，在写“科研”博客时，难免会需要频繁地输入数学公式，而Markdown本身并不支持数学公式的输入。我曾经想偷懒直接用Markdown的语法去代替LaTeX数学公式，最后页面显示的结果有点儿丑。却一直也没有去修改。直到前天收到了[印卧涛](http://www.math.ucla.edu/%7Ewotaoyin/)老师的一封邮件，邮件里所有的数学公式都是用LaTeX代码写的，正规而美观。由此觉得自己做事还是水了点。做事要认真啊亲。

本文默认我们是会使用LaTeX编辑数学公式的。

###解决办法：

- 将数学公式以图片形式保存，再在Markdown中将其插入。
- 或者，使用LaTeX在线编辑器，输入数学公式，获得html代码，将其插入Markdown。

###步骤：

- 进入[CodeCogs](http://www.codecogs.com/latex/eqneditor.php)
- 在盒子里书写公式
- 在页面下方复制html代码
- 将复制的html代码拷贝到Markdown里

###缺点：
Markdown文件的易读性却因此下降了很多。