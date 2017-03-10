---
layout: post
title: "Ruby入门：环境的搭建与RubyMine的安装"
category: 编程
tags: [Ruby]
published: true
---

## 搭建Ruby环境（RVM+Ruby+Rails+Gems）

### 1. 安装RVM

- Ruby版本管理工具，一个命令行工具，它允许你在同一台电脑上安装并管理和切换多个 Ruby 版本。
- cURL是一个利用URL语法在命令行下工作的文件传输工具，它支持文件上传和下载，所以是综合传输工具。
- Source命令也称为“点命令”，通常用于重新执行刚修改的初始化文件，使之立即生效，而不必注销并重新登录。

```sh
$ curl -L get.rvm.io | bash -s stable
$ source ~/.bashrc
$ source ~/.bash_profile
```

### 2.1 利用RVM安装Ruby

- 安装Ruby

```sh
#修改 RVM 的 Ruby 安装源到国内的 淘宝镜像服务器，这样能提高安装速度
$ sed -i -e 's/ftp\.ruby-lang\.org\/pub\/ruby/ruby\.taobao\.org\/mirrors\/ruby/g' ~/.rvm/config/db
#列出已知的ruby版本
$ rvm list known
#安装/使用/设置ruby默认版本
$ rvm install ruby-1.9.3-p547
$ rvm use 1.9.3 --default 
```

- use RVM to install gems
 
`rvm rubygems current`

### 2.2 Ubuntu下apt-get直接安装Ruby[*不推荐*]

- 安装ruby

`sudo apt-get install ruby irb rdoc`

>这样安装之后rvm和ruby似乎是分开的，rvm无法使用和管理该版本的ruby

- 安装Rubygems

`sudo apt-get rubygems`

> RubyGems 是什么？
> RubyGems（简称 gems）是一个用于对 Ruby组件进行打包的Ruby打包系统。它提供一个分发 Ruby 程序和库的标准格式，还提供一个管理程序包安装的工具，功能类似于Linux下的apt-get。

使用它可以方便第从远程服务器下载并安装Rails。输入执行命令：

```
gem install rails --remote
gem install rails--include-dependencies
```

### 安装 Rails 环境

```sh
$ gem source -r https://rubygems.org/
$ gem source -a https://ruby.taobao.org
#手动更新下RubyGems 和其他需要更新的 Gem
$ gem update --system
$ gem update
#使用 RubyGems 安装 Rails
$ gem install rails
$ rails -v
Rails 4.1.6
```


## 安装RubyMine

### 1. 安装Oracle SDK

[百度经验](http://jingyan.baidu.com/article/7f766daf5e20944101e1d02b.html)

```sh
#因为版权问题，在Ubuntu的APT仓库中不提供Oracle Java下载
$ apt-cache search oracle-java　
---搜索不到任何包
$ apt-cache search java7
---只可以搜索到OpenJDK的相关包
#添加PPA：Personal Package Archive
$ sudo add-apt-repository ppa:webupd8team/java
#更新完成后，选择安装Java7
$ sudo apt-get update
$ sudo apt-get install oracle-java7-installer
#设置环境变量
$ sudo apt-get install oracle-java7-set-default
```

### 2. 安装RubyMine

- 下载.tar.gz文件
[Ruby on Rails IDE :: JetBrains RubyMine](http://www.jetbrains.com/ruby/)

- 解压并安装

```sh
#进入软件包目录
$ ./bin/rubymine.sh
bash: ./bin/rubymine.sh: Permission denied
$ sudo chmod 777 Soft
$ ls -l rubymine.sh
-rw------- 1 llgreen llgreen 5848  6月 10 19:22 rubymine.sh
$ sudo chmod 777 rubymine.sh
$ ./bin/rubymine.sh
run
```

- 激活

> 输入序列号验证：
[JetBrain 软件注册码](http://peter2009.iteye.com/blog/1975994)

- 右键锁定到启动器

###3. 第一次使用

- 选择配色

> 深色主题：Dracula

- 开始一个Rails项目

![1](//o7mw3gkkh.qnssl.com//public/img/tech/0926-1.png)

![2](//o7mw3gkkh.qnssl.com//public/img/tech/0926-2.png)