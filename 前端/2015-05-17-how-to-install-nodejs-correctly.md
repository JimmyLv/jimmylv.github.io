---
layout: post
title: Node.js的正确安装与相关工具（Mac OS X）
categories: [前端]
tags: [JavaScript, NodeJS]
published: True

---

## 版本分裂

- [node.js](https://nodejs.org/)
- [io.js](https://io.js.org/en/index.html)

## nvm

node version manager: 版本管理工具，可以同时安装不同的node版本包括io.js，并且随意切换相应的版本，甚至于特意使用某一版本的node来运行某个js文件。

```bash
nvm ls/ls-remote #列出已经安装的/远程仓库中的所有版本
nvm install/uninstall [version] #安装/卸载某个版本
nvm current #显示现在使用的版本，与node -v功能一样
nvm use [version] #切换版本
nvm which [version] #显示该版本所安装的位置
nvm alias default [version] #在所有的shell都使用这个默认版本
```

## npm

node package manager: 包管理工具，安装和管理其他依赖库。

```bash
npm install -g [package] #全局安装（如mocha）
npm install [package] #安装到当前文件夹（如chai）
npm install #按照package.json安装相关依赖
npm install [package] --save #自动把模块和版本号添加到dependencies部分
npm install [package] --save--dev #自动把模块和版本号添加到devdependencies部分
```

用于区别开发依赖模块和产品依赖模块，devDepandencies主要是配置测试框架， 例如jshint、mocha。

## 坑：安装包

如果从官方网站直接下载安装包安装的话会有一个问题：我安装io.js之后，它会在io.js和node的目录之间直接建立软链接（symlinks），从而导致了nvm怎么也不能把io.js切换到原来node.js版本

```bash
$ ll /usr/local/bin/{node,io.js}
16864 -rwxrwxr-x. 1 root root 17268324 Jan 14 08:29 /usr/local/bin/iojs
    0 lrwxrwxrwx. 1 root root        4 Jan 14 08:29 /usr/local/bin/node -> iojs
```

## Mac OS X下如何正确安装node

### 通过brew安装nvm

先使用brew安装好nvm（此时你还没有node呢，怎么`npm install nvm -g`）:

```bash
brew update #更新软件源（就像sudo apt-get update）
brew install nvm 
```

在安装完毕之后需要根据terminal里的提示做一下操作：

```bash
mkdir ~/.nvm #建立一个nvm版本库，之后安装的node版本都会在这里
cp $(brew --prefix nvm)/nvm-exec ~/.nvm/ #拷贝brew目录中的nvm-exec执行文件到新建的目录
```

然后把以下的内容添加到`~/.bashrc`和`~/.zshrc`中，这样就可以在终端中使用bash和zsh命令行工具啦，不然会显示`command not found`。

```bash
export NVM_DIR=~/.nvm
source $(brew --prefix nvm)/nvm.sh #实际上的目录是/usr/local/opt/nvm/nvm.sh
```

### 通过nvm安装node

```bash
nvm install 0.12.3 #首先安装好想要的版本
nvm alias default 0.12.3 #然后设置默认的node版本以便于在所有shell中使用
```

通过`npm config get prefix`命令可以看到安装的路径是`/Users/Thoughtworks/.nvm/versions/node/v0.12.3`，所以nvm是直接把不同的node版本安装在先前所建立的.nvm文件夹中，易于管理。


### 通过npm安装依赖库

```bash
npm install -g npm@latest #首先更新一下npm到最新版
```

最好不要使用sudo安装全局库，所以需要更改一下npm工具的权限，就不用每次都需要输入密码啦

```bash
sudo chown -R $USER ~/.npm
```

### 切换软件源

由于墙的问题，有时候npm install会在node-gyp rebuild那里卡很久，原因在于node-gyp编译时候需要Node.js源码来提供头文件，所以它会先尝试下载Node.js，但是由于下载速度奇慢所以就卡住不动了。

为了获得更快的库安装速度，我们可以切换到淘宝的软件源，淘宝说与官方的同步频率为10分钟，所以还是相当可靠的。

可以使用我们定制的cnpm命令行工具代替默认的npm:

```bash
npm install -g cnpm --registry=https://registry.npm.taobao.org
cnpm install [package] #使用cnpm来安装对应的库
```

## 参考资料

- [Mac 下如何删除 卸载 nodejs](http://www.freair.com/bbs/read.php?tid=1039)
- [Introduction to npm - How To Node - NodeJS](http://howtonode.org/introduction-to-npm)
- [03 - Fixing npm permissions _ npm Documentation](https://docs.npmjs.com/getting-started/fixing-npm-permissions)
- [How to use npm global without sudo on OSX](http://www.johnpapa.net/how-to-use-npm-global-without-sudo-on-osx/)
- [node.js - nvm keeps _forgetting_ node in new terminal session - Stack Overflow](http://stackoverflow.com/questions/24585261/nvm-keeps-forgetting-node-in-new-terminal-session)
- [osx - What is the suggested way to install brew, node.js, io.js, nvm, npm on OS X_ - Stack Overflow](http://stackoverflow.com/questions/28017374/what-is-the-suggested-way-to-install-brew-node-js-io-js-nvm-npm-on-os-x)
- [How to uninstall io.js (or io.js and Node.js together)](https://www.binarysludge.com/2015/01/14/how-to-uninstall-io-js-or-io-js-and-node-js-together/)
- [Install Node.js and io.js Together (safely)](http://blog.modulus.io/install-nodejs-and-iojs-together-safely)

