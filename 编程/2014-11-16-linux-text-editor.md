---
layout: post
title: Ubuntu下的几种命令行编辑器介绍
category: 编程
tags: [Ubuntu]
description:
---

## 命令行编辑器

### 1. vi

`:w`：Vi 保存当前编辑文件，但并不退出

`:w newfile`：此时 Vi 将把当前文件的内容保存到指定的 newfile 中，而原有文件保持不变

`File exists (use ! to override)`

`:w! newfile`此时，若用户真的希望用文件的当前内容替换 newfile 中原有内容，可强行写入

`:q`：系统退出 Vi 返回到 shell

`No write since last change (use ! to overrides)`
`:q!`：不想保存被修改后的文件而要强行退出 Vi 时，可放弃所作修改

`:wq`：Vi 将先保存文件，然后退出 Vi 返回到 shell。

`:x`：该命令的功能同命令模式下的`ZZ`命令功能相同，若当前编辑的文件曾被修改过，则 Vi 保存该文件后退出，返回到 shell；若当前编辑的文件没被修改过，则 Vi 直接退出, 返回到 shell。

### 2. gedit

```sh
#以gedit打开名为av&gv的文件
sudo gedit /home/文档/av&gv
```

### 3. nano

`sudo nano /etc/hosts`

完成后按 ctrl+x 退出，按 y 保存，回车，OK

### 4. sed

> sed 是一种非交互式的流编辑器，可动态编辑文件。所谓非交互式是说，sed 和传统的文本编辑器不同，并非和使用者直接互动，sed 处理的对象是文件的数据流（称为 stream/流）。

> 特别注意：sed 并不会更改文件内容。sed 的工作方式是读取文件内容，经流编辑之后，把结果显示到标准输出。因此，如果想要存储 sed 的处理结果，得自行运用转向输出将结果存成其他文件。

```sh
#修改 RVM 的 Ruby 安装源到国内的 淘宝镜像服务器，能提高安装速度
$ sed -i -e 's/ftp\.ruby-lang\.org\/pub\/ruby/ruby\.taobao\.org\/mirrors\/ruby/g' ~/.rvm/config/db
```
