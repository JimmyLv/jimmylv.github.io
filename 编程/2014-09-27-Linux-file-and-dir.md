---
layout: post
title: Ubuntu系统快捷键和文件处理命令
category: 编程
tags: [Ubuntu]
published: true
---

## 重要的快捷键

### 1. 桌面

- ALT + F1: 聚焦到桌面左侧任务导航栏，可按上下键导航。
- ALT + F2: 运行命令
- ALT + F4: 关闭窗口
- ALT + TAB: 切换程序窗口
- ALT + 空格: 打开窗口菜单
- PRINT: 桌面截图
- ALT + PRINT：窗口截图

### 2. Dash面板

在Dash面板中按CTRL + TAB: 切换到下一个子面板（可搜索不同类型项目，如程序、文件、音乐）

- WIN + A: 搜索或浏览程序（Application）
- WIN + F: 搜索或浏览文件（File）
- WIN + M: 搜索或浏览音乐文件（Music）

### 3. Terminal终端

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

## 文件与目录管理

### 1. 目录表示
```
.         #代表此层目录
..        #代表上一层目录
-         #代表前一个工作目录
~         #代表『目前使用者身份』所在的家目录
~account  #代表 account 这个使用者的家目录(account是个帐号名称)
```

### 2. 常见的文件目录处理命令

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


## 文件权限与目录配置

> Linux最优秀的地方之一，就在于它的多用户、多任务环境。Linux一般将文件可存取访问的身份分为3个类别，分别是owner（用户）、group（用户组）、others（其他人），且3种身份都各自有自己的read，write，execute等权限。

### 1. 文件权限概念
当屏幕前面出现“Permission deny”的时候，肯定是权限设置错误。

```sh
ls -al          #ls:list，列出所有文件的详细信息
ls -l           #显示文件，属性的第一个字段是文件的权限，共10位，比如-rwxr-xr--，表示owner具有rwx权限，group具有rx权限，others只具有r权限
```

### 2. 文件种类与扩展名

使用`ls -l`查看到的十个字符中，第一个字符为文件的类型：

- -: 普通文件（regular file）
- d: 目录文件（directory）
- l: 连接文件，类似于windows的快捷方式（link）
- b: 块设备文件（block）
- c: 字符设备文件（character）
- s: 套接字（sockets）
- p: 管道（FIFO, pipe）

### 3. 改变文件属性与权限

```
chgrp       #改变文件所属用户组，具体句法记得使用 man page 查询
chown       #改变文件所有者
chmod       #改变文件的权限
```
其中，chmod修改权限的方法有两种，分别是符号法与数字法，数字法中r，w，x的数值分别是4，2，1。

要开放“目录”（注意不是“文件”）给任何人看，应该至少同时给予r和x权限，但w权限不可随便给予。

### 4. 一个例子

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

## 其他有用的种种

### 1. 查询命令功能 

```
man command  #command是要查询的命令名称
```

进入man命令后，可按`空格`往下翻页，按`q`键离开。

在man page中，可以在任何时候输入`/keyword`来查询关键字，比如/date.

### 2. 正确的关机方法

惯用的关机命令：

```
shutdown -h now     #立刻关机
shutdown -h 20:25   #晚上8点25分关机
shutdown -h +10     #过十分钟后关机
shutdown -r now     #立刻重启
shutdown -r +30 ‘The system will be reboot’    #再过30分钟关机，并显示后面的消息给所有在线用户
shutdown -k now ‘The system will be reboot’    #仅发出警告，系统并不会真正关机
```
