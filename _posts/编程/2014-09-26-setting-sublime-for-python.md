---
layout: post
title: "配置Python开发环境和Sublime Text 3编辑器"
category: 编程
tags: [Ubuntu, Sublime, Python]
published: true
---

## 配置Python环境

### 1. 安装pip
 
> pip 是 Python 的包管理工具，建议 Python 的包都用 pip 进行管理。

```sh
# 安装 pip
$ sudo apt-get install python-pip
#安装python包
$ pip install [ ]
#升级python包
$ pip install --upgrade [ ]
#卸载python包
$ pip uninstall [ ]
```


### 2. 构建虚拟环境

> virtualenv用于创建独立的Python环境，多个Python相互独立，互不影响，它能够：

* 在没有权限的情况下安装新套件

* 不同应用可以使用不同的套件版本

* 套件升级不影响其他应用

- 安装Virtualenv和Virtualenvwrapper

> Virtaulenvwrapper是virtualenv的扩展包，用于更方便管理虚拟环境，它可以做：

* 将所有虚拟环境整合在一个目录下

* 管理（新增，删除，复制）虚拟环境 

* 切换虚拟环境


1) **安装virtualenv和virtualenvwrapper**

```sh
$ sudo apt-get install python-virtualenv
$ virtualenv --version
1.11.6
$ sudo pip install virtualenvwrapper  

```

2) **设置环境**

```sh
#创建目录用来存放虚拟环境
$ mkdir $HOME/.virtualenvs
#在~/.bashrc中添加： 
$ nano ~/.bashrc
export WORKON_HOME=$HOME/.virtualenvs
source /usr/local/bin/virtualenvwrapper.sh
#重载环境
$ source ~/.bashrc
```

3) **使用方法**

> 默认情况下，虚拟环境会依赖系统环境中的site packages，就是说系统中已经安装好的第三方package也会安装在虚拟环境中，如果不想依赖这些package，那么可以加上参数 --no-site-packages建立虚拟环境`virtualenv --no-site-packages [虚拟环境名称]`

```sh
#列出虚拟环境列表
$ workon
#或者
$ lsvirtualenv
#新建虚拟环境
$ mkvirtualenv testENV
New python executable in testENV/bin/python
Installing setuptools, pip...lsdone.
#列出虚拟环境列表
(testENV)llgreen@Work-PC:~$ lsvirtualenv
testENV
=======
#启动/切换虚拟环境
$ workon [虚拟环境名称]
#删除虚拟环境
$ rmvirtualenv [虚拟环境名称]
#离开虚拟环境
(testENV)llgreen@Work-PC:~$ deactivate
```

## Sublime Text 3的安装与配置

[官网下载](http://www.sublimetext.com/3)

### 1. 安装插件

1) 首先安装[Package Control](https://sublime.wbond.net/installation#st3)，通过Package Control可以很方便安装其他插件

> - 通过快捷键 ctrl+` 或者 View > Show Console 菜单打开控制台

> - 粘贴对应版本的代码后回车安装

```python
#适用于 Sublime Text 3：
import urllib.request,os,hashlib; h = '7183a2d3e96f11eeadd761d777e62404' + 'e330c659d4bb41d3bdf022e94cab3cd0'; pf = 'Package Control.sublime-package'; ipp = sublime.installed_packages_path(); urllib.request.install_opener( urllib.request.build_opener( urllib.request.ProxyHandler()) ); by = urllib.request.urlopen( 'http://sublime.wbond.net/' + pf.replace(' ', '%20')).read(); dh = hashlib.sha256(by).hexdigest(); print('Error validating download (got %s instead of %s), please try manual install' % (dh, h)) if dh != h else open(os.path.join( ipp, pf), 'wb' ).write(by)
```

2) 按快捷键Ctrl+Shift+P调出命令窗口，选择Package Control: Install Package，安装 Python 开发常用的插件：

>Sublime 有一个非常丰富的插件系统。而我当前使用的插件如下：
 
* Color Scheme - Tomorrow Night Color schemes 决定了编辑器界面语法高亮的字体颜色。这是一个非常酷的暗黑系样式。
 
* Theme  - Soda Dark Themes 影响 Sublime 界面元素的颜色和风格。这个非常适合 Tomorrow Night 的配色方案。 

* All  Autocomplete Sublime 默认的自动完成只关注当前文件的单词。这个插件扩展了其自动完成的单词列表到所有打开的文件。 

* SublimeCodeIntel  为部分语言增强自动完成功能，包括了 Python 。这个插件同时也可以让你跳转到符号定义的地方，通过按住 alt 并点击符号。非常方便。
 
* SublimeTmpl  这个插件允许用户定义文件的模板，比如在写一个html文件时，老是重复文件头的一些引入信息很繁琐，可以定义一个模板直接生成必须的信息，具体的SublimeTmpl插件用法请自行百度。

* SideBarEnhancements  一个增强侧边栏文件夹浏览功能的插件，比较不错。

* SublimeREPL  允许你在编辑界面直接运行 Python 解释器。我倾向于在单独的终端窗口用 bpython 来运行，但有时 SublimeREPL 是很有帮助的。 

* GitGutter  在编辑器的凹槽区，依照 Git ，增加小图标来标识一行是否被插入、修改或删除。在 GitGutter 的 readme 中有说明如何更改颜色图标来更新你的配色方案文件。 

* Pylinter  这个插件提供了目前我所见到的最好的 pylint 编辑器整合。它自动检查 .py 文件，无论其何时被保存，并且会直接在编辑界面显示 pylint 违规。它还有一个快捷方式来禁用局部的 pylint 检查，通过插入一个 #pylint: 禁用注释。这个插件对于我确实非常有用。 

* SublimeLinter 是用来在写代码时做代码检查的，可以检查Python代码是否符合PEP8的要求。

* Tag  可以为web开发者提供html和css标签，很方便快捷，对于web前端设计者非常实用。

3) 自动安装插件

> 修改配置文件Preferences->Package Settings->Package Control->Settings-User如下，保存以后，选择Package Control->Install Package，将会自动下载。


```json
{
	"installed_packages":
	[
		"Terminal",
		"Alignment",
		"BracketHighlighter",
		"SublimeLinter",
		"ColorPicker",
		"CompactExpandCss",
		"CSScomb JS",
		"Emmet Css Snippets",
		"Hex-to-RGBA",
		"HTML5",
		"JsFormat",
		"Package Control",
		"Rails Developer Snippets",
		"Ruby on Rails snippets",
		"RubyTest",
		"SublimeTmpl",
		"Tag",
		"Tradsim"
	]
}
```

### 2. 修改快捷键

> SublimeREPL安装之后没有快捷键，每次运行程序必须用鼠标去点工具栏，有些不爽。

1) **SublimeREPL插件的菜单命令**

Preferences => Browser Packages…打开插件安装包位置，依次找到 SublimeREPL\config\Python文件夹下的Main.sublime-menu并打开。

该文件即是插件菜单的结构及相关参数，从中找到运行Python文件的菜单项的部分：

```json
    {"command": "repl_open",
     "caption": "Python - RUN current file",
     "id": "repl_python_run",
     "mnemonic": "d",
     "args": {
        "type": "subprocess",
        "encoding": "utf8",
        "cmd": ["python", "-u", "$file_basename"],
        "cwd": "$file_path",
        "syntax": "Packages/Python/Python.tmLanguage",
        "external_id": "python",
        "extend_env": {"PYTHONIOENCODING": "utf-8"}
        }
    },
```

其中id的值是我们需要的，因为我们正是要为其添加快捷键。另外，菜单文件的位置也是需要先记下的，因为需要为这个命令指定定义的来源。

2) **自定义快捷键**

Preferences => Key Boundings-User打开自定义快捷键文件，写入如下内容：

```json
[
	{
		"keys" : ["f5"],                           // 快捷键，注意小写
		"command" : "run_existing_window_command", // 运行定义的命令
		"args" :                                   // 命令参数
		{
			"id" : "repl_python_run",              // 上一步查看的命令的id
			"file" : "config/Python/Main.sublime-menu" // 菜单定义文件位置
		}

	}
]
```

### 3. 修改视图

- 选择查看--布局--行：2 或者 Shift+Alt+8

将Sublime分割为上下两部分，选择F5进行代码编译，编译信息将会显示在下面的编译区域。

### 4. 编辑器快捷键汇总

Ctrl+Shift+P：打开命令面板

Ctrl+P：搜索项目中的文件

Ctrl+G：跳转到第几行

Ctrl+W：关闭当前打开文件

Ctrl+Shift+W：关闭所有打开文件

Ctrl+Shift+V：粘贴并格式化

Ctrl+D：选择单词，重复可增加选择下一个相同的单词

Ctrl+L：选择行，重复可依次增加选择下一行

Ctrl+Shift+L：选择多行

Ctrl+Shift+Enter：在当前行前插入新行

Ctrl+X：删除当前行

Ctrl+M：跳转到对应括号

Ctrl+U：软撤销，撤销光标位置

Ctrl+J：选择标签内容

Ctrl+F：查找内容

Ctrl+Shift+F：查找并替换

Ctrl+H：替换

Ctrl+R：前往 method

Ctrl+N：新建窗口

Ctrl+K+B：开关侧栏

Ctrl+Shift+M：选中当前括号内容，重复可选着括号本身

Ctrl+F2：设置/删除标记

Ctrl+/：注释当前行

Ctrl+Shift+/：当前位置插入注释

Ctrl+Alt+/：块注释，并Focus到首行，写注释说明用的

Ctrl+Shift+A：选择当前标签前后，修改标签用的

F11：全屏

Shift+F11：全屏免打扰模式，只编辑当前文件

Alt+F3：选择所有相同的词

Alt+.：闭合标签

Alt+Shift+数字：分屏显示

Alt+数字：切换打开第N个文件

Shift+右键拖动：光标多不，用来更改或插入列内容

鼠标的前进后退键可切换Tab文件

按Ctrl，依次点击或选取，可需要编辑的多个位置

按Ctrl+Shift+上下键，可替换行
