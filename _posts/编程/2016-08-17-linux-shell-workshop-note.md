---
layout: post
title: Linux shell 命令之密室逃脱 
categories: [编程]
tags: [Linux, DevOps, Shell]
published: True

---

> Thanks to 讲师/谈一秀、杜屹东

## WorkShop 内容前瞻

在日常工作中，命令行工具已凭借其强大的功能和简洁的交互形式称霸类 Unix 操作系统。

你是否在使用命令行工具的时候为找不到合适的工具而烦恼？是否在面对复杂任务的时候感到力不从心？

本次 workshop 将为你揭开 shell command 的神秘面纱！通过本次 Linux 密室逃脱之旅，你将会掌握一些实用的 shell 技能，超越 GUI 限制，提升工作效率。

## 正式开工

![](http://7xjbdq.com1.z0.glb.clouddn.com/images/2016/1471433233240.png)

> 场景：vagrant 启动虚拟机，使用 ssh「快速」登录 Linux 机器，发现 Tomcat 没启动，启动后发现端口被占用 `http://192.168.33.20:8080/`，然后 kill 掉进程却发现内容被压缩然后找不到了，切换用户（找到密码）才发现文件，解压后却发现内容被篡改，然后一键替换内容才最终还原网页。

`cat id_rsa.pub >> authorized_keys` 快速添加内容到特定文件 `>` 覆盖 | `>>` 增加

`ssh -i ./id_rsa dev@192.168.33.20` (--identity 身份)

`echo IdentityFile $PWD/id_rsa >> ~/.ssh/config` 

ssh + 别名 Host `ssh bws` 快速登录到 Linux 机器

`tldr systemctl` >> `man tldr` 好于 man，只是比较慢

![](http://7xjbdq.com1.z0.glb.clouddn.com/images/2016/1471427377924.png)

`set -o emacs` 设置 bash 快捷键模式

![](http://7xjbdq.com1.z0.glb.clouddn.com/images/2016/1471427513741.png)

`Ctrl + A` `Ctrl + E` `Ctrl + U` `Ctrl + R` `Ctrl + L` `Ctrl + K` `Ctrl + W`

`grep -v ^# .README.md` 找出非注释消息

`lsof -i:8080` 查找特定端口进程

`ps -ef|grep java` 查找特定程序进程

`sudo systemctl restart tomcat` systemctl 是系统命令需要 sudo

`cat /proc/version`

    Linux version 3.10.0-327.18.2.el7.x86_64 (builder@kbuilder.dev.centos.org) (gcc version 4.8.3 20140911 (Red Hat 4.8.3-9) (GCC) ) #1 SMP Thu May 12 11:03:55 UTC 2016

`grep -rI 747339117 .` 查找特定文字的文件

vim 设置编码 `set encoding:utf-8`

vim 转入后台进程 `Ctrl + Z` 然后 `fg + Enter` 返回

`find root_path -name '*.tar.gz'` 找到特定后缀名的文件

`find / -name "*.tar.gz" 2>>/dev/null` 过滤无用错误信息（2）

`cat /etc/passwd` 查看所用用户

`su - Darker` 切换到用户并新建 shell（带环境变量）（A mere `-` implies `-l`, `--login`.）

    [dev@localhost ~]$ su Darker
    Password:
    [Darker@localhost dev]$ sudo -iu dev
    [dev@localhost ~]$

`grep -r "Darker"` 找到密码 `U2Fsd,` 再照一次 tar 包

    .README.md:This is the message: Check the port and kill the process, you can start tomcat right. # Kissing your hand may make you feel very good, but a diamond and sapphire bracelet lasts for ever. -- Darker:U2Fsd,

`tldr locate` 也可以用 locate Find filenames quickly，但是需要 sudo 权限

`alias ll='ls -al'` 设置别名（只在当前进程生效，写入 `.bashrc`）

`tar -zxvf /home/Darker/.src/20/.web.tar.gz` 解压文件

`sudo mv index.html /usr/share/tomcat/webapps/ROOT/` 页面正常但是发现网页内容被篡改了

`sudo sed -i 's/Darker/ThoughtWorkers/g' index.html` 替换文本 `/find/replace/` `-i` 是字符，`sed -r 's/regex/replace/g' filename` 则是正则表达式

`cd /etc/sudoers.d/` 可以新建文件给每个用户设置 sudo 权限

`sudo -l` 查看当前用户的 sudo 权限

`history` 查看所有命令记录

`Ctrl + D` 返回上一个 Session，用于连续退出

`pstree` 树状显示所有的进程

禁止网页右键？ [JavaScript 可以做到](http://www.chhua.com/web-note2825)

[Installing the Z Shell (zsh) on Linux, Mac OS X and Windows](https://gist.github.com/derhuerst/12a1558a4b408b3b2b6e)

## Finally!!!

![](http://7xjbdq.com1.z0.glb.clouddn.com/images/2016/1471432922494.png)

> 关于 DevOps 的一个疑问？其持续时间是一阵一阵的吗？如果一次性都做完了，那就是一劳永逸的事情，岂不是之后都不用再维护了吗？

