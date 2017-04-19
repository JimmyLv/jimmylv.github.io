---
layout: post
title: Ubuntu下的程序安装与卸载
category: 编程
tags: [Ubuntu, 软件]
description: 
---

## 程序安装与卸载`apt-get`

### 1. 添加PPA源

> PPA，表示 Personal Package Archives，也就是个人软件包集。

> 有很多软件因为种种原因，不能进入官方的 Ubuntu 软件仓库。 为了方便 Ubuntu 用户使用，launchpad.net 提供了 ppa，允许用户建立自己的软件仓库， 自由的上传软件。

```sh

#到[launchpad.net](https://launchpad.net/+search)搜索到ppa:user/ppa-name之后

sudo add-apt-repository ppa:ubuntu-wine/ppa

```

### 2. 更新软件以及软件源列表

> 在修改`/etc/apt/sources.list`或者`/etc/apt/preferences`之后运行该命令，此外您需要定期运行`apt-get update`命令以确保您的软件包列表是最新的

```sh

#更新源

sudo apt-get update 

#更新已安装的包

sudo apt-get upgrade 

```

### 4. 安装指定的程序

```sh

#搜索包

apt-cache search package 

#获取包的相关信息，如说明、大小、版本等

apt-cache show package 

#安装包

sudo apt-get install package 

#重新安装包

sudo apt-get install package - - reinstall 

```

### 5. 卸载指定的程序

```sh

#卸载已安装的软件包

apt-get remove packagename

#卸载一个已安装的软件包（删除配置文件）

apt-get --purge remove packagename

#有些软件很难卸载，而且还阻止了别的软件的应用

dpkg --force-all --purge packagename

```

### 6. 清理空间

```sh

#清除已经卸载的软件包的.deb文件

sudo apt-get autoclean 

#将已安装软件包的.deb文件一并删除

sudo apt-get clean 

```

