---
layout: post
title: WorkShop 笔记：Linux shell 命令密室逃脱之旅
categories: [编程]
tags: [Linux, DevOps, Shell, Bash]
published: True

---

> Thanks to 讲师/谈一秀、杜屹东

## 内容前瞻

在日常工作中，命令行工具已凭借其强大的功能和简洁的交互形式称霸类 Unix 操作系统。

你是否在使用命令行工具的时候为找不到合适的工具而烦恼？是否在面对复杂任务的时候感到力不从心？

本次 workshop 将为你揭开 shell command 的神秘面纱！通过本次 Linux 密室逃脱之旅，你将会掌握一些实用的 shell 技能，超越 GUI 限制，提升工作效率。

## 正式开工

![](//o7mw3gkkh.qnssl.com//images/2016/1471433233240.png)

> 场景：vagrant 启动虚拟机，使用 ssh「快速」登录 Linux 机器，发现 Tomcat 没启动，启动后发现端口被占用 `http://192.168.33.20:8080/`，然后 kill 掉进程却发现内容被压缩然后找不到了，切换用户（找到密码）才发现文件，解压后却发现内容被篡改，然后一键替换内容才最终还原网页。

命令/快捷键 | 解释/作用/备注
-----------|--------------
`ssh-keygen -t rsa` | 后续选择文件夹可以在当前位置生成密钥对
`scp id_rsa.pub dev@192.168.33.20:/.ssh` | 拷贝公钥（`id_rsa.pub`）到服务器上
`cat id_rsa.pub >> authorized_keys` | 快速添加内容到特定文件 `>` 覆盖、`>>` 增加
`ssh -i ./id_rsa dev@192.168.33.20` | (`--identity_file` 带上身份认证秘钥)
`echo IdentityFile $PWD/id_rsa >> ~/.ssh/config` | 一行命令id_rsa 文件路径**增加**到指定配置文件
`ssh bws` | ssh + 别名 Host，快速登录到 Linux 机器
`tldr systemctl` | >> `man tldr` 好于 man，只是比较慢

![](//o7mw3gkkh.qnssl.com//images/2016/1471439210291.png)

命令/快捷键 | 解释/作用/备注
-----------|--------------
`set -o emacs` | 设置 bash 的快捷键模式
`Ctrl + A` | 跳到行首
`Ctrl + E` | 跳到行尾
`Ctrl + U` | 清除当前输入
`Ctrl + R` | 搜索历史命令
`Ctrl + L` | 清屏，但保留记录
`Ctrl + K` | 从当前位置删除至尾
`Ctrl + W` | 删除单词

![](//o7mw3gkkh.qnssl.com//images/2016/1471427513741.png)

命令/快捷键 | 解释/作用/备注
-----------|--------------
`grep -v ^# .README.md` | 找出非注释消息
`lsof -i:8080` | 查找特定端口进程
`ps -ef|grep java` | 查找特定程序进程
`sudo systemctl restart tomcat` | systemctl 是系统命令，需要 sudo
`cat /proc/version` | 查看当前系统信息

    Linux version 3.10.0-327.18.2.el7.x86_64 (builder@kbuilder.dev.centos.org) (gcc version 4.8.3 20140911 (Red Hat 4.8.3-9) (GCC) ) #1 SMP Thu May 12 11:03:55 UTC 2016


命令/快捷键 | 解释/作用/备注
-----------|--------------
`grep -rI 747339117 .` | 查找特定文字的文件
`set encoding:utf-8` | vim 设置编码 
`Ctrl + Z` | vim 转入后台进程
`fg + Enter` | 返回 vim 后台进程 
`find root_path -name '*.tar.gz'` | 找到特定后缀名的文件
`find / -name "*.tar.gz" 2>>/dev/null` | 过滤无用错误信息（2）
`cat /etc/passwd` | 查看所用用户
`su - Darker` | 切换到用户并新建 shell（带环境变量）（A mere `-` implies `-l`, `--login`.）

    [dev@localhost ~]$ su Darker
    Password:
    [Darker@localhost dev]$ sudo -iu dev
    [dev@localhost ~]$

`grep -r "Darker"` | 找到密码 `U2Fsd,` 再查找一次 tar 包

    .README.md:This is the message: Check the port and kill the process, you can start tomcat right. # Kissing your hand may make you feel very good, but a diamond and sapphire bracelet lasts for ever. -- Darker:U2Fsd,

命令/快捷键 | 解释/作用/备注
-----------|--------------
`tldr locate` | 也可以快速定位文件并且省内存，但是需要 sudo 权限
`alias ll='ls -al'` | 设置别名（只在当前进程生效，写入 `.bashrc`）
`tar -zxvf /home/Darker/.src/20/.web.tar.gz` | 解压文件，注意 `-z` 参数在不同系统作用不同
`sudo mv index.html /usr/share/tomcat/webapps/ROOT/` | 页面正常但是发现网页内容被篡改了
`sudo sed -i 's/Darker/ThoughtWorkers/g' index.html` | 替换文本 `/find/replace/`
`sed -r 's/regex/replace/g' filename` | 则用于替换正则表达式
`cd /etc/sudoers.d/` | 可以新建文件给每个用户设置 sudo 权限
`sudo -l` | 查看当前用户的 sudo 权限
`history` | 查看所有命令记录
`Ctrl + D` | 返回上一个 Session，用于连续退出
`pstree` | 树状显示所有的进程

禁止网页右键？ [使用 JavaScript 可以做到，监听事件永远返回 false](http://www.chhua.com/web-note2825)。

[Installing the Z Shell (zsh) on Linux, Mac OS X and Windows](https://gist.github.com/derhuerst/12a1558a4b408b3b2b6e)，可惜也需要 sudo 权限。

## Finally!!!

![](//o7mw3gkkh.qnssl.com//images/2016/1471432922494.png)

另外不得不说 Dash 太好用了，好用到哭，/(ㄒoㄒ)/~~

![](//o7mw3gkkh.qnssl.com//images/2016/1471440990555.png)

## 一点儿小思考

> - 关于 DevOps 的一个疑问？其工作的持续时间是一阵一阵的吗？如果一次性都做完了，那么性质就变成了一劳永逸的事情，岂不是之后都不用再维护了吗？
> - 那么 DevOps 如何使得需求源源不断来保证自己工作的必要性呢，（手动微笑）而这样的性质似乎很适合拿来做咨询项目呀？
> - 另一方面的思考就是，正因为其不持续的必要性，DevOps 应当作为开发者的基本素质而不应为其专门设置职位，在迭代开始的最早期就把最困难的部分做好做完善，一劳永逸。
> - 而随着 AWS 等各类“服务”性质平台的不断完善，这方面的工作大概会越来越少并且现有工具、脚本都将成为资产，值得被维护，也应当被持续维护，但属于 Developer 分内的事情。

