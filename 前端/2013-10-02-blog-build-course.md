---
layout: post
title: 傻瓜式博客搭建教程：使用GitHub Pages快速生成博客
category: 前端
tags: [Git, Jekyll]
keywords: markdown
description:
---

关键词：**Git+github+jekyll+.tk+DNS.LA+markdown**

## 前言：搭建博客的几大要素

- 一个域名（即你的博客的网址，这里选用顶级免费域名.tk）
- 一个服务器（即博客的代码存放的地方，这里选用 github）
- 一个 Blog 生成工具（这里选用 jekyll，类似 WordPress）

## 第一部分：使用 GitHub Pages 快速生成博客

### 一、介绍 Git 和 Github

Git，一个非常强大的版本管理工具。

Github 则是一个基于 Git 的日益流行的开源项目托管库，也就是你的“代码仓库”（repository）。

你可以在本地或者网上对自己的代码进行修改，而 Github 就是一个将你对代码的任何修改和更改说明（commit）进行同步的一个工具，并且可以进行版本管理。在我们搭建博客的过程中，它就扮演着一个“云仓库”服务器的角色，存放我们的博客代码。

### 二、Github 的安装和配置

1. 注册，这个总会吧，官网（[https://github.com/](https://github.com/)）
2. 下载安装（[https://help.github.com/articles/set-up-git](https://help.github.com/articles/set-up-git)）
3. 安装完成后，桌面出现两个图标：
   ![](https://lh4.googleusercontent.com/-muAVO81BsfM/Ukwf1vepLzI/AAAAAAAAAFc/20AHhLdbK8U/s0/GIT.jpg)

[[https://lh4.googleusercontent.com/-muAVO81BsfM/Ukwf1vepLzI/AAAAAAAAAFc/20AHhLdbK8U/s0/GIT.jpg]]

4. GitHub 是客户端，点击登陆，输入你先前注册的帐号密码
5. Git Shell 是 Git 的命令行，类似于 window 下的 CMD
6. 在 Shell 里面配置本地信息，分别输入你的 github 帐号和邮箱：

```
git config --global user.name "Your Name Here"# Sets the default name for git to use when you commit

git config --global user.email "your_email@example.com"# Sets the default email for git to use when you commit
```

更多关于 Github 的设置可以看[这里](http://www.cnblogs.com/sprying/p/3276984.html)

### 三、使用 Github Pages 生成博客

> **说明：**

> 先前就介绍过 Github 是一个跨平台的“云仓库”，所以我们既可以在网上操作，也可以在本地操作再推送到云端。

> 我先介绍一下在 Github 网站上怎么直接用 Github Pages 快速生成一个博客，再介绍在本地利用 Git Shell 新建一个，同时可以熟悉一下 git 的操作流程。

1、在[Github 网站](https://github.com)上新建一个仓库（repository），网站右上角：

![](https://lh5.googleusercontent.com/-eQD90D5qlfY/UkwsyUt3ZHI/AAAAAAAAAFw/xSU3QCTUZPs/s0/%E5%88%9B%E5%BB%BArepository.jpg)

2、输入库的名字，**注意：**一定要以这种形式`yourname.github.com`进行命名，比如我的用户名是`liqing215`，于是我的命名就是`liqing215.github.com`。

![](https://lh3.googleusercontent.com/-EybvjDatNUg/UkwukR5hZjI/AAAAAAAAAGE/TtrM2NRohGU/s450/%25E5%2588%259B%25E5%25BB%25BArepository2.jpg)

3、创建完成之后进入这个界面后点击右边的设置。

![](https://lh3.googleusercontent.com/-gp-py8RIyfc/Ukww4ubcbGI/AAAAAAAAAGs/oVVXirynjp4/s450/%E5%88%9B%E5%BB%BArepository3.jpg)

4、把界面往下拉就可以看到一个“页面自动生成”按钮了，猛击它！！

![](https://lh3.googleusercontent.com/-465J4njURXw/Ukww9gZE8PI/AAAAAAAAAG4/2YfW-sTvMWI/s450/%E5%88%9B%E5%BB%BArepository4.jpg)

5、然后进入 Github 自带的 markdown 编辑器进行编辑，你可以随意修改写上几句自己的话。然后点击右下角的绿色按钮`Continue to Layouts`。

6、然后你可以选择一个自己喜欢的主题，点击 Publish 就可以生成属于你自己的博客啦！

7、试着在地址栏输入http://yourname.github.io/就可以进入你刚刚创建的博客，比如我的就是[http://liqing215.github.io/](http://liqing215.github.io/)

当然输入http://yourname.github.com/也可以，它会自动跳转到http://yourname.github.io/

### 四、在本地上新建一个 Github 项目

> 其实到以上为止我们已经创建好了一个属于自己的博客，接下来我们再新建一个其他项目，用来熟悉 github 的整个操作流程，你会发现它真的超好用。

#### 4.1 利用 GitHub 图形界面

1、跟上面一样，在网站上新建一个 repository，这里我们把名字命名为 myBlog，（其实随意啦）

2、新建好到这个界面的时候，打开你的 GitHub 软件，刷新一下你就可以在列表里看到你新建的那个 repository 了。

![](https://lh5.googleusercontent.com/-hTOYtR5YD2E/Ukw5VGhg8qI/AAAAAAAAAHo/ysaYhKsb9Ic/s450/HTTP+SSH.jpg)

3、此时你就可以把网上的仓库加载到本地：

一种非常简单的方法是点击列表中 repository 的右边有个 clone 按钮，点击之后等待下载，然后右键可以选择 open in explorer 在资源管理器中打开。

在资源管理器中你可以新建文件啊，更改文件啊，随便进行任何修改之后回到 GitHub 你会发现它已经感应到了。

![](https://lh5.googleusercontent.com/-03kwuSLa5fg/Ukw6OzSVIBI/AAAAAAAAAH0/lPmjGm3-Fzg/s450/local+update.jpg)

之后点击上方的 publish 按钮就可以把本地的更改发布上去了，这里 publish 的概念应该就是发布一个新版本，在右边它会让你填写 commit，应该是对此版本的一个说明。

#### 4.2 利用 Git Shell 命令行

1、也可以选择在 Shell 下完成整个过程，虽然比较麻烦，但是有一种程序员的感觉有木有：

![](https://lh5.googleusercontent.com/-hTOYtR5YD2E/Ukw5VGhg8qI/AAAAAAAAAHs/CnHE_IV0TP0/s450/HTTP+SSH.jpg)

2、在上图中可以看到在 Shell 中新建一个仓库的完整命令：

```
makdir ~/hello-world    //创建一个项目hello-world

cd ~/hello-world       //打开这个项目

git init             //初始化

touch README //创建说明文件

git add README        //更新README文件

git commit -m 'first commit'     //提交更新，并注释信息“first commit”

git remote add origin https://github.com/liqing215/myBlog.git //连接远程github项目

git push -u origin master     //将本地项目更新到github项目上去
```

3、还有怎样推送一个已经存在的，被你修改过的项目到网上：

```
git remote add origin https://github.com/liqing215/myBlog.git //连接远程github项目

git push -u origin master     //将本地项目更新到github项目上去
```

4、发现`https://github.com/liqing215/myBlog.git`就是下图中标识红线的那个类似于网址的东西了吧，记得把我的改成你的。

![](https://lh5.googleusercontent.com/-hTOYtR5YD2E/Ukw5VGhg8qI/AAAAAAAAAHs/CnHE_IV0TP0/s450/HTTP+SSH.jpg)

### 彩蛋：（可能的）**一个槽点**

> 发现还是图形界面好用吗？只需要用鼠标点击几个按钮就行了？
> 但是程序员可不一样，他们喜欢一直用键盘敲啊敲，这样的场景在电视电影中太常见了而且很酷炫有木有。
> 而且啊？！你有米有发现在 Shell 下完全不用切换界面了!!!
> 所有工作都在一个黑底白字的框框里面完成了，当你熟悉过后你就会发现图形界面才是更难用的。
