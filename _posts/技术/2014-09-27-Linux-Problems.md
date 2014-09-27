---
layout: post
title: Ubuntu开发之旅[6]：Linux系统命令和快捷键整理
category: 技术
tags: Ubuntu
keywords: Ubuntu
description: 
---

##文件与目录管理

###1. 目录表示
```
.         #代表此层目录
..        #代表上一层目录
-         #代表前一个工作目录
~         #代表『目前使用者身份』所在的家目录
~account  #代表 account 这个使用者的家目录(account是个帐号名称)
```

###2. 常见的文件目录处理命令

1) 目录处理

- cd：变换目录，cd是Change Directory的缩写
- pwd：显示目前的目录，pwd是Print Working Directory的缩写
- mkdir：创建一个新的目录
- rmdir：删除一个空的目录

```
pwd -P                 #-P：代表显示正确的完整路径，而不是连接路径
mkdir -m 目录名称       #-m：直接配置文件的权限
mkdir -p test1/test2   #-p：直接将所需要的目录(包含上一级目录)递回创建起来！
PATH="$PATH":/root     #将/root路径加入PATH环境变量中
```

2) 文件处理

- mv：移走目录或者改文件名
- cp：拷贝文件
- rm：删除文件和目录
- cat：显示文件内容
- grep：文本内容搜索
- find：文件或者目录名以及权限属主等匹配搜索
- tar：解压命令
- clear：清屏，相当与DOS下的cls
- date：显示当前时间


##文件权限与目录配置

> Linux最优秀的地方之一，就在于它的多用户、多任务环境。Linux一般将文件可存取访问的身份分为3个类别，分别是owner（用户）、group（用户组）、others（其他人），且3种身份都各自有自己的read，write，execute等权限。

###1. 文件权限概念
当屏幕前面出现“Permission deny”的时候，肯定是权限设置错误。

```sh
ls -al          #ls:list，列出所有文件的详细信息
ls -l           #显示文件，属性的第一个字段是文件的权限，共10位，比如-rwxr-xr--，表示owner具有rwx权限，group具有rx权限，others只具有r权限
```

###2. 文件种类与扩展名

使用`ls -l`查看到的十个字符中，第一个字符为文件的类型：

- -: 普通文件（regular file）
- d: 目录文件（directory）
- l: 连接文件，类似于windows的快捷方式（link）
- b: 块设备文件（block）
- c: 字符设备文件（character）
- s: 套接字（sockets）
- p: 管道（FIFO, pipe）

###3. 改变文件属性与权限

```
chgrp       #改变文件所属用户组，具体句法记得使用 man page 查询
chown       #改变文件所有者
chmod       #改变文件的权限
```
其中，chmod修改权限的方法有两种，分别是符号法与数字法，数字法中r，w，x的数值分别是4，2，1。

要开放“目录”（注意不是“文件”）给任何人看，应该至少同时给予r和x权限，但w权限不可随便给予。

###4. 一个例子

将install.log文件复制成为LAYtest.log，并且要给linanya这个人读写权限，可以这样做：

```
[root@localhost ~]# cp install.log LAYtest.log     #若复制文件夹，用cp -r
[root@localhost ~]# ls -al LAYtest.log 
-rw-r--r-- 1 root root 62826 9月  17 15:19 LAYtest.log     #虽然完成了复制，但仍然是root的文件
[root@localhost ~]# chown linanya LAYtest.log 
[root@localhost ~]# ls -al LAYtest.log       
-rw-r--r-- 1 linanya root 62826 9月  17 15:19 LAYtest.log  #文件变成linanya的
[root@localhost ~]# 
```

##命令行编辑器

###1. vi

`:w`：Vi保存当前编辑文件，但并不退出

`:w newfile`：此时Vi将把当前文件的内容保存到指定的newfile中，而原有文件保持不变

`File exists (use ! to override)`

`:w! newfile`此时，若用户真的希望用文件的当前内容替换newfile中原有内容，可强行写入

`:q`：系统退出Vi返回到shell

`No write since last change (use ! to overrides)`
`:q!`：不想保存被修改后的文件而要强行退出Vi时，可放弃所作修改

`:wq`：Vi将先保存文件，然后退出Vi返回到shell。

`:x`：该命令的功能同命令模式下的`ZZ`命令功能相同，若当前编辑的文件曾被修改过，则Vi保存该文件后退出，返回到shell；若当前编辑的文件没被修改过，则Vi直接退出, 返回到shell。

###2. gedit

```sh
#以gedit打开名为av&gv的文件
sudo gedit /home/文档/av&gv 
```

###3. nano 

`sudo nano /etc/hosts`

完成后按ctrl+x退出，按y保存，回车，OK

###4. sed

> sed是一种非交互式的流编辑器，可动态编辑文件。所谓非交互式是说，sed和传统的文本编辑器不同，并非和使用者直接互动，sed处理的对象是文件的数据流（称为stream/流）。

> 特别注意：sed并不会更改文件内容。sed的工作方式是读取文件内容，经流编辑之后，把结果显示到标准输出。因此，如果想要存储sed的处理结果，得自行运用转向输出将结果存成其他文件。

```sh
#修改 RVM 的 Ruby 安装源到国内的 淘宝镜像服务器，能提高安装速度
$ sed -i -e 's/ftp\.ruby-lang\.org\/pub\/ruby/ruby\.taobao\.org\/mirrors\/ruby/g' ~/.rvm/config/db
```

##程序安装与卸载`apt-get`

###1. 添加PPA源

> PPA，表示 Personal Package Archives，也就是个人软件包集。

> 有很多软件因为种种原因，不能进入官方的 Ubuntu 软件仓库。 为了方便 Ubuntu 用户使用，launchpad.net 提供了 ppa，允许用户建立自己的软件仓库， 自由的上传软件。

```sh
#到[launchpad.net](https://launchpad.net/+search)搜索到ppa:user/ppa-name之后
sudo add-apt-repository ppa:ubuntu-wine/ppa
```

###2. 更新软件以及软件源列表

> 在修改`/etc/apt/sources.list`或者`/etc/apt/preferences`之后运行该命令，此外您需要定期运行`apt-get update`命令以确保您的软件包列表是最新的

```sh
#更新源
sudo apt-get update 
#更新已安装的包
sudo apt-get upgrade 
```

###4. 安装指定的程序

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

###5. 卸载指定的程序

```
#卸载已安装的软件包
apt-get remove packagename
#卸载一个已安装的软件包（删除配置文件）
apt-get --purge remove packagename
#有些软件很难卸载，而且还阻止了别的软件的应用
dpkg --force-all --purge packagename
```

###6. 清理空间

```sh
#清除已经卸载的软件包的.deb文件
sudo apt-get autoclean 
#将已安装软件包的.deb文件一并删除
sudo apt-get clean 
```

##重要的热键

###1. 桌面

- ALT + F1: 聚焦到桌面左侧任务导航栏，可按上下键导航。
- ALT + F2: 运行命令
- ALT + F4: 关闭窗口
- ALT + TAB: 切换程序窗口
- ALT + 空格: 打开窗口菜单
- PRINT: 桌面截图
- ALT + PRINT：窗口截图

###2. Dash面板

在Dash面板中按CTRL + TAB: 切换到下一个子面板（可搜索不同类型项目，如程序、文件、音乐）

- WIN + A: 搜索或浏览程序（Application）
- WIN + F: 搜索或浏览文件（File）
- WIN + M: 搜索或浏览音乐文件（Music）

###3. Terminal终端

- CTRL + ALT + T: 打开终端
- TAB: 自动补全命令或文件名
- CTRL + SHIFT + V: 粘贴（Linux中不需要复制的动作，文本被选择就自动被复制）
- CTRL + SHIFT + T: 新建标签页
- CTRL + D: 关闭标签页
- CTRL + L: 清楚屏幕
- CTRL + R + 文本: 在输入历史中搜索
- CTRL + A: 移动到行首
- CTRL + E: 移动到行末
- CTRL + C: 终止当前任务
- CTRL + Z: 把当前任务放到后台运行（相当于运行命令时后面加&）

##其他有用的种种

###1. 查询命令功能 

```
man command  #command是要查询的命令名称
```

进入man命令后，可按`空格`往下翻页，按`q`键离开。

在man page中，可以在任何时候输入`/keyword`来查询关键字，比如/date.

###2. 正确的关机方法

惯用的关机命令：

```
shutdown -h now     #立刻关机
shutdown -h 20:25   #晚上8点25分关机
shutdown -h +10     #过十分钟后关机
shutdown -r now     #立刻重启
shutdown -r +30 ‘The system will be reboot’    #再过30分钟关机，并显示后面的消息给所有在线用户
shutdown -k now ‘The system will be reboot’    #仅发出警告，系统并不会真正关机
```
