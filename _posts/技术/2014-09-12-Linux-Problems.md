---
layout: post
title: Linux学习：实际问题
category: 技术
tags: Linux
keywords: 
description: 
---

管理实验室服务器的大神师兄[苏宇]()毕业了，他将管理服务器的工作交给了我——对Linux和服务器管理毫无经验的小菜一枚。前几天师弟[段云鹏](https://yunpeng.blog.ustc.edu.cn)的一些机缘巧合的误操作导致服务器核崩溃，我却手足无措，请来[刘惠民](http://painterliu.com)童鞋帮着忙活了两晚，也没能复原系统。最后还是让苏神师兄回了学校一趟才解决问题。由此想了两件事：既然答应了负责管理服务器，就不能再以“浪费精力”、“没兴趣”等借口拒绝学习相关技术；人的时间与精力真的很有限，下一次给承诺之前，先想想自己是否花得起这份时间与精力。

- [《鸟哥的Linux私房菜——基础学习篇》](http://book.douban.com/subject/4889838/)
- [《鸟哥的Linux私房菜——服务器架设篇》](http://book.douban.com/subject/2338464/)

本系列文章分为两部分：

- 系统学习上面两本书的笔记。
- 实际中遇到的问题及解决方案，即本文内容。


##实际问题
##1. 建立网络映射
- Mac：`Finder`->`前往`->`连接服务器`->输入`smb://IPaddress/samba`->`连接`
- Linux：`位置`->`连接服务器`->“服务类型”选择`自定义位置`->输入`smb://IPaddress/samba`->`连接`

##2. ssh登陆失败
以root身份远程登陆服务器，密码正确，却显示如下警告：

```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the RSA key sent by the remote host is
3a:17:4b:6e:62:e6:94:df:09:78:99:90:51:68:18:62.
Please contact your system administrator.
Add correct host key in /Users/AnyaLin/.ssh/known_hosts to get rid of this message.
Offending RSA key in /Users/AnyaLin/.ssh/known_hosts:4
RSA host key for 222.195.93.129 has changed and you have requested strict checking.
Host key verification failed.
```

解决方法：

```
vi ~/.ssh/known_hosts     #选中最后一条登陆记录，双击`d`删除，按“：”进入末行编辑模式，输入“x”，回车
ssh root@222.195.93.129   #再次登陆
The authenticity of host '222.195.93.129 (222.195.93.129)' can't be established.
RSA key fingerprint is 3a:17:4b:6e:62:e6:94:df:09:78:99:90:51:68:18:62.
Are you sure you want to continue connecting (yes/no)?    #输入yes
```


