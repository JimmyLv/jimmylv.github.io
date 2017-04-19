---
layout: post
title: "写作环境的搭建（Jekyll+GitHub+Markdown）"
category: 前端
tags: [Jekyll, 写作, Git]
published: true
---

## 搭建Jekyll环境

[官方文档](http://jekyllcn.com/docs/installation/)

### 1. 安装RubyGems

`apt-get install rubygems`

### 2. 安装[「Jekyll」](http://jekyllcn.com/)

```sh
$ gem install jekyll
Fetching: liquid-2.6.1.gem (100%)
ERROR:  While executing gem ... (Errno::EACCES)
    Permission denied - /var/lib/gems
$ sudo gem install jekyll
ERROR:  Error installing jekyll:
	ERROR: Failed to build gem native extension.
$ gem update --system
ERROR:  While executing gem ... (RuntimeError)
$ sudo gem update
Updating installed gems
Updating rdoc
......
27 gems installed
$ gem install jekyll
......
Successfully installed jekyll-2.4.0
26 gems installed
$ jekyll -v
Could not find a JavaScript runtime.
$ sudo apt-get install nodejs
$ jekyll -v
jekyll 2.4.0
```

### 3. 测试Jekyll

```sh
$ jekyll new my-awesome-site
$ cd my-awesome-site
~/my-awesome-site $ jekyll serve
# => Now browse to http://localhost:4000
```

打开浏览器可以看到：
![3](//o7mw3gkkh.qnssl.com//public/img/tech/0926-3.png)


## 使用[「JekyllBootstrap」](http://jekyllbootstrap.com/)

> The Quickest Way to Blog on GitHub Pages.
> Jekyll Generates Static Websites

### 1. 使用Jekyll + GitHub Pages快速生成博客

- JekyllBootstrap提供了一个界面：[Host on GitHub in 3 Minutes](http://jekyllbootstrap.com/usage/jekyll-quick-start.html)

> 1. Create a New Repository

> 2. Install Jekyll-Bootstrap

> 3. Profit

### 2. 利用Jekyll进行本地调试

- 直接下载jekyll-bootstrap模板

```sh
$ git clone https://github.com/plusjade/jekyll-bootstrap.git
$ cd jekyll-bootstrap
$ jekyll serve
```

> Your blog is now available at: [http://localhost:4000/](http://localhost:4000/)

- 下载/运行别人已经做好的模板

```sh
$ git clone git@github.com:liqing215/note-blog.git
$ cd note-blog
$ jekyll serve
Error:  Address already in use - bind(2)
```

这个错误是因为在另外一个在和终端里面也运行了jekyll serve，关掉之后在打开就可以看到自己的博客了。

![4](//o7mw3gkkh.qnssl.com//public/img/tech/0926-4.png)

```sh
$ jekyll serve
CNAME already taken: ......
```

这个错误是因为CNAME文件的原因，是用来指定自定义域名的，和本地调试地址冲突。如果你没有自定义域名，那就不需要删除。


### 3. Markdown写作

> [Markdown: Basics （快速入门）](http://wowubuntu.com/markdown/basic.html)

> [阳志平：Markdown写作浅谈](http://www.yangzhiping.com/tech/r-markdown-knitr.html)

1) **本地写作**

- [UberWriter](http://jonathanmh.com/uberwriter-a-markdown-editor-for-linux/): a MarkDown Editor for Linux

```sh
sudo add-apt-repository ppa:w-vollprecht/ppa
sudo apt-get update
sudo apt-get install uberwriter
```

- 只需要在_posts文件夹下添加相应博文的.md文件即可。

> 注意命名格式一定要是yy-mm-dd-title.md，title是你文章的标题。（也可以卸载.md文件开头）

- 每篇文章的开头都要指定一定的格式，如本文：

```
layout: post
title: "Ubuntu开发之旅[4]：写作环境的搭建（Jekyll+GitHub+Markdown）"
category: 技术
tags: Ubuntu
keywords: Ubuntu，Jekyll，GitHub，Markdown
description: null
published: true
```

layout: post指的是博文格式要按照_layouts文件夹下的

post.html指定的格式来显示。

categories: 指定博文分类技术。

tags: 指定博文标签。

published: 表示发布与否

2) **线上写作**

- 在线Md编辑器：

> 1.[马克飞象](http://maxiang.info)- 专为印象笔记打造的Markdown

> 2.[StackEdit](https://stackedit.io/) – In-browser markdown editor

> 3.[Cmd Markdown](https://www.zybuluo.com/mdeditor) 编辑阅读器 - 作业部落出品

- [Prose · A Content Editor for GitHubProse](http://prose.io)

> Prose is a content editor for GitHub designed for managing websites. Learn more. Authorize on GitHub.

最终就选择了Prose.io直接在线编辑修改GitHub上的文章，无比方便。

![5](//o7mw3gkkh.qnssl.com//public/img/tech/0926-5.png)


## 其他的快速「博客」方案

### 1. [Postach.io](http://postach.io)

Collect and share content from your favourite apps.

Connect and post using Evernote, Dropbox and Pocket.

> When you add or change an HTML, Markdown, or Image file in the folder for your Postach.io site in Dropbox, that change will be reflected on your Postach.io site after Dropbox is finished syncing. It’s that easy.

### 2. [Farbox](https://www.farbox.com/)

The Best Blog Platform on Cloud
 
> Realtime and dynamic, Folder is a database, FarBox is a webserver. Simple is Everything. 

### 3. [Medium](https://medium.com/about/welcome-to-medium-9e53ca408c48)

> Medium is a new place on the Internet where people share ideas and stories that are longer than 140 characters and not just for friends. 

### 4. [简书](http://www.jianshu.com/)

> 找回文字的力量 在这里更好地写作和阅读