---
layout: post
title: "Git安装笔记与如何连接GitHub远程仓库"
category: 编程
tags: [Ubuntu, Git]
published: true
---

## 1. 安装/设置Git

```bash
#下载
$ sudo apt-get install git
#设置
$ git config --global user.name "llgreen"
$ git config --global user.email "460051518@qq.com"
#常用的命令都设置alias，尽量少敲键盘
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.co checkout
git config --global alias.st status
```

## 2. 初始化本地仓库

```bash
#第一次链接远程库，忘记初始化本地仓库了
$ git remote add origin git@github.com:liqing215/note-blog.git
fatal: Not a git repository (or any of the parent directories): .git

#建立本地仓库
$ mkdir Documents/Git_repository
$ cd /Documents/Git_repository
$ git init
Initialized empty Git repository in /home/llgreen/Documents/Git_repository/.git/
```

## 3. 连接/克隆远程仓库Github

[Permission denied: 怎样生成SSH Keys?](https://help.github.com/articles/generating-ssh-keys)

[如何添加SSH key到GitHub?](https://github.com/settings/ssh)

```bash
#第二次连接远程仓库，忘记添加密匙，权限拒绝
$ git remote add origin git@github.com:liqing215/note-blog.git
$ git clone git@github.com:liqing215/note-blog.git
Permission denied (publickey).
fatal: Could not read from remote repository.

#添加本地_rsa.pub到GitHub上
#Step 1: Check for SSH keys
$ ls -al ~/.ssh

#Step 2: Generate a new SSH key
$ ssh-keygen -t rsa -C "460051518@qq.com"
Your identification has been saved in /home/llgreen/.ssh/id_rsa.
Your public key has been saved in /home/llgreen/.ssh/id_rsa.pub.
#add your new key to the ssh-agent:
$ eval "$(ssh-agent -s)"
Agent pid 7359
$ ssh-add ~/.ssh/id_rsa
Enter passphrase for /home/llgreen/.ssh/id_rsa: 
Identity added: /home/llgreen/.ssh/id_rsa (/home/llgreen/.ssh/id_rsa)

#Step 3: Add your SSH key to GitHub
#查看本地_rsa.pub中的SSH key
$ cat /home/llgreen/.ssh/id_rsa.pub
ssh-rsa [a-zA-Zd]* 460051518@qq.com
#利用xclip复制到clipboard，在添加到GitHub - SSH key
$ sudo apt-get install xclip
$xclip -sel clip < ~/.ssh/id_rsa.pub
# Copies the contents of the id_rsa.pub file to your clipboard

#Step 4: Test everything out
$ ssh -T git@github.com
Hi liqing215! You've successfully authenticated, but GitHub does not provide shell access.
```

## 4. 修改/推送本地内容到远程库

```bash
$ git clone git@github.com:liqing215/note-blog.git
$ cd note-blog/
$ nano README.md 
#添加文件 add -> commit -> push
$ git add README.md 
$ git commit -m 'learngit commit'
#查看文件在那个分支，选择推送到gh-pages分支（这是GitHub的pages分支，项目在master上）
$ git status
On branch gh-pages
Your branch is ahead of 'origin/gh-pages' by 1 commit.
$ git push -u origin gh-pages

```

[廖雪峰-Git教程-添加远程库](http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/0013752340242354807e192f02a44359908df8a5643103a000)

> - 要关联一个远程库：
`git remote add origin git@server-name:path/repo-name.git`
> - 关联后，第一次推送master分支的所有内容：
`git push -u origin master`
> - 此后，每次本地提交后，推送最新修改：
`git push origin master`
> - 提交默认的对应分支：
`git push`

## 5. Git命令大全

![cheat-sheet-large01](//o7mw3gkkh.qnssl.com//public/img/tech/cheat-sheet-large01.png)