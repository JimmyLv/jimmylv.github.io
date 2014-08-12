---
layout: post
title: 在Mac上通过Sublime、Skim编辑LaTeX
category: 技术
tags: LaTeX Sublime Skim Mac
keywords: 
description: 
---

Sublime Text是一款非常优秀的编辑器，速度快，界面简洁，插件众多。并且能跨平台使用，在Mac和Windows上都能完美使用。虽然是一款付费软件，但作者很厚道地给了无限期的试用期限。这一切正如其官网广告词说的那样：The text editor you'll fall in love with.

Skim是一款免费轻量的PDF阅读、标注工具，布局贴心友好，与OS X自带的Previewer相比，Skim能更好的注释PDF文件。

LaTeX是一款权威的科技论文排版软件，不仅可以写论文，也可以处理日常的各种文档工作，甚至是做幻灯片。相比于Word，LaTeX最大的优势是对于复杂公式的编辑与排版非常漂亮。并且用简单的命令就可以生成脚注、索引、目录和参考文献等复杂的结构。这一切优点都使得世界上众多的“科学家”们不再需要身兼作者与排版工两职，从而将更多的精力集中于文章内容本身。

本文的目的是将上述三种软件综合部署在Mac上。完成之后，你将可以在Sublime Text里面进行LaTeX代码编辑，用Skim预览生成的PDF文件。更重要的是，让你觉得，写论文也可以是一件很优美的事。

###准备工作：

- Mac上至少4GB的空余空间
- 高速的互联网连接

###第一步：安装MacTeX
- 进入[MacTeX官网](http://www.tug.org/mactex)下载`MacTeX.pkg`文件。文件大约2GB，需要一段时间才能完成下载，趁现在去喝杯咖啡吧。
- 下载完成之后，双击`MacTeX.pkg`进行安装。
- 安装完成之后，会看到许多与TeX有关的程序图标，暂时忽略它们。

###第二步：安装Sublime Text
- 进入[Sublime Text官网](http://www.sublimetext.com)下载最新版本的Sublime Text。这里我下载的是Sublime Text 3.
- 下载完成之后，将文件拖入应用程序文件夹安装。

###第三步：在Sublime Text中安装Package Control
我们需要在Sublime Text中下载插件以便能够很好地操作与LaTeX有关的文件。而插件是通过Package Control下载的。

- 进入[Package Control官网](http://sublime.wbond.net/installation)复制灰色区块的代码。
- 打开Sublime Text。
- 使用快捷键“`control+~`”（~就在Esc键的下方）打开控制面板Console。你会在Sublime Text的底部看到弹出一个白色窗口。
- 将刚才复制的代码粘贴到控制面板。
- 按下“`Enter`”回车键。然后退出并重启Sublime Text。

###第四步：安装LaTeX Tools
- Sublime Text重启后，按下“`Command+Shift+P`”打开命令托盘Command pallet，这一步也可以通过Tools下拉菜单完成。
- 在命令托盘里输入“`Install Package`”，按下`Enter`回车建。
- 完成之后，输入“`LaTeX Tools`”，找到这一项并回车安装。
- 退出并重启Sublime Text。

###第五步：安装Skim
- 进[Skim](http://skim-app.sourceforge.net)下载Skim并安装
- 打开Skim，在菜单栏中`Skim > Preference(选项) > Sync(同步)`
- 在预设菜单中选择`Sublime Text`

![skim](/public/img/skim.png)

- 关闭上面这个窗口。

###全部完成，✌️
现在，我们已经做完了所有的步骤，可以打开Sublime Text，`Command+N`新建文件并在里面编写LaTeX代码了，完成编辑之后，`Command+S`保存文件，`Command+B`编译并运行，这时就可以在Skim里面看到PDF预览了。



