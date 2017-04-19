---
layout: session
title: 前端模块化小史，Webpack 入门
categories: [演讲]
tags: [Webpack, JavaScript, 工程化]
speaker: Jimmy Lv
transition: move
files: /assets/slide.js,/assets/slide.css,/js/zoom.js
highlightStyle: kimbie.light
theme: green
published: True
---

30 min = 15 min * 2

[slide data-on-enter="incallback"]

<div id="incallback" style="margin-bottom: 30px; font-size: 60px;"></div>

```js
function incallback() {
    setTimeout(function(){
        alert('Done is better than perfect.  -  via Facebook');
        document.getElementById('incallback').innerHTML = 'Welcome to my session!';
    }, 300)
}
```

[slide]
# 前端模块化小~~屎~~史，Webpack 入门
<small>by <strong>Jimmy Lv</strong></small>

[slide]

# 模块化管理？

[slide]

# JavaScript 模块化

------

* ES6 Module {:&.fadeIn}
* CommonJS
* AMD
* UMD

[slide data-on-leave="outcallback"]

# 现在即未来：ES6 模块规范

```js
// profile.js
var firstName = 'Michael';
var lastName = 'Jackson';

var sayHi = () => {
    console.info('I am '+ firstName + ',' + lastName + '!');
    console.info(`I am ${firstName}, ${lastName}!`);
}

export {firstName, lastName, sayHi};
```

```js
// main.js
import {firstName, lastName, sayHi} from './profile';

import * as profile from './profile';
profile.sayHi();
```

[slide]

# 民间两大规范

- CommonJS: 同步加载，主要用于 NodeJS **服务器**端；
- AMD: 异步加载，通过 RequireJS 等工具适用于**浏览器**端。

[slide]

# 过去式：CommonJS 规范

> NodeJS: ~~JavaScript 要逆袭！我是窜天~~ 🐵，~~我要上天！~~

<br/>

```js
var firstModule = require("firstModule");

//playing code...

module.export = anotherModule
```

[slide]

# JavaScript 组件发布平台：NPM

<br/>

> 🐒🐒🐒🐒🐒：前端项目要是能在**浏览器**中更方便地使用 **NPM 资源**就好了！

[slide]

# 过去式：AMD 规范

> 即 (Asynchronous Module Definition) {:&.pull-right} 

------

```js
define(['firstModule'], function(module) {

    //playing code...

    return anotherModule
})
```

[slide]

# Browserify.js 

> 🐒🐒🐒🐒🐒：要是能在浏览器使用 *require* 同步语法加载 NPM 模块就好了！

<br/>

```js
var firstModule = require("firstModule");

//playing code...

module.export = anotherModule
```

```js
define(['firstModule'], function(module) {

    //playing code...

    return anotherModule
})
```

[slide]

# 「通用」模式：UMD

> 即 (Universal Module Definition) {:&.pull-right} 

------

```js
(function (root, factory) {
    if (typeof define === 'function' && define.amd) {
        // AMD
        define(['jquery'], factory);
    } else if (typeof exports === 'object') {
        // Node, CommonJS
        module.exports = factory(require('jquery'));
    } else {
        // 浏览器全局变量(root 即 window)
        root.returnExports = factory(root.jQuery);
    }
}(this, function ($) {
    //    方法
    function myFunc(){};
    //    暴露公共方法
    return myFunc;
}));
```

[slide]

# 前端工程化需求

> 前端模块化框架肩负着 模块管理、资源加载 两项重要的功能，这两项功能与工具、性能、业务、部署等工程环节都有着非常紧密的联系。因此，模块化框架的设计应该最高优先级考虑工程需要。

<br/>

- 依赖管理 {:&.rollIn}
- 按需加载 
- 请求合并

[slide]

> 关键原因就在于[「纯前端方式只能在运行时分析依赖关系」](https://github.com/fouber/blog/issues/4)

[slide]

# 新思路：「不」在运行时分析依赖。

- 借助构建工具来做线下分析:

<br/>

> 利用构建工具在线下进行模块依赖分析，然后把依赖关系数据写入到构建结果中，并调用模块化框架的依赖关系声明接口，实现模块管理、请求合并以及按需加载等功能。

[slide]

# 主角：Webpack

> 「任何静态资源都可以视作模块，然后模块之间还可以相互依赖。」

![](https://webpack.github.io/assets/what-is-webpack.png)

[slide]

# 特性

1. 兼容CommonJS 、 AMD 、ES6语法 {:&.rollIn}
2. 支持打包 JS、CSS、图片等资源文件
3. 串联式 loader 以及插件机制
4. 独立配置文件 **webpack.config.js**
5. 代码切割 chunk，实现按需加载
6. 支持 SourceUrls 和 SourceMaps
7. 具有强大的 Plugin 接口，使用灵活
8. 支持异步 IO 并具有多级缓存，增量编译速度快

[slide]

# 一个简单的 React 例子

```js
// hello.js
import React, {Component} from 'react';

class Hello extends Component {
    render(){
        return (
            <div>Hello, {this.props.name}!</div>
        );
    }
}

export default Hello;
```

```js
// entry.js
import React from 'react';
import Hello from './hello';

React.render(<Hello name="Jimmy" />, document.body);
```

[slide]

# Webpack 配置文件

```js
// webpack.config.js
var path = require('path');

module.exports = {
    entry: path.resolve(__dirname, './src/entry.js'),
    output: {
        path: path.resolve(__dirname, './assets'),
        filename: 'bundle.js'
    },

    module: {
        loaders: [
            { test: /\.js?$/, loaders: 'babel-loader', exclude: /node_modules/ },
        ]
    },

    resolve:{
        extensions:['','.js','.json']
    },
};
```

[slide]

# 打包完毕

```
// index.html

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>React Sample</title>
</head>
<body>
<script src="./assets/bundle.js"></script>
</body>
</html>
```

[slide]

# 实战：重构现有项目

- 代码热加载
- 配置 NPM Script
- babel-loader: 预编译 ES6
- ng-annotate-loader: 确保依赖安全注入
- less-loader: 使用 Less 替换 CSS
- ngtemplate-loader: String 化 HTML 模板

[slide]

# 代码热加载：webpack-dev-server

> **webpack-dev-server** 是一个基于 Express.js 框架的静态资源 Web 服务器。开发服务器会监听每一个文件的变化，进行实时打包，并推送通知给前端页面，从而实现自动刷新。

<br/>

```js
 module.exports = {
    entry: {
        app: ['webpack/hot/dev-server', './app.js']
    },
    output: {
        path: './assets',
        filename: 'bundle.js'
    },
    ...
}
```

默认端口 8080：[localhost:8080/webpack-dev-server/](localhost:8080/webpack-dev-server/)

[slide]

# 配置 NPM Script

```json
"scripts": {
    "dev": "webpack -w --bail --display-error-details",
    "start": "webpack-dev-server --history-api-fallback --hot --inline --progress",
    "build": "webpack -p"
}
```

```bash
npm run dev # 提供 watch 方法，实时进行打包更新并打印出错信息
npm start # 启动服务器，浏览器直接访问的是 index.html
npm run build # 输出 production 环境下的压缩打包代码
```

[slide]

# babel-loader 预编译 ES6

```json
module: {
    loaders: [
      {test: /\.js$/, exclude: /node_modules/, 
        loader: 'ng-annotate!babel?presets=es2015'}
    ]
}
```


```js
require ('./style/base.less');

import angular from 'angular'
import ngRoute from 'angular-route'

import githubService from './app/services/githubService'
import MainCtrl from './app/controllers/mainController'
import Components from './app/components/components.module'
```

[slide]

# ng-annotate-loader 依赖安全注入

```js
controller($http, $routeParams, base64) {
    'ngInject';

    var vm = this;

    vm.$onInit = () => {
        ...
    }
}
```

```js
controller:["$http","$routeParams","base64",function(e,t,n){"ngInject" ...}]
```

[slide]

# 使用 Less 替换 CSS

```js
{test: /\.less$/, loader: "style!css!less"},

{test: /\.(eot|woff|woff2|ttf|svg)(\?\S*)?$/, 
    loader: 'url?limit=100000&name=./fonts/[name].[ext]'},
{test: /\.(png|jpe?g|gif)$/, 
    loader: 'url-loader?limit=8192&name=./images/[hash].[ext]'}
```

```js
import '../../node_modules/font-awesome/css/font-awesome.css'
import '../../assets/styles/bootstrap.css'
import '../../assets/styles/yue.css'
import '../../assets/styles/base.less'
```

[slide]

# String 化 HTML 模板

```js
{test: /\.html$/, loader: 'ngtemplate!html?attrs[]=img:src img:ng-src'}
```

```js
import './post.less'

export default {
  templateUrl: require('./post.html'),
  bindings: {
    pageContent: '<',
    showToc: '<'
  }
  controller() {
    ...
  }
```

```js
import post from './post/post'

export default angular.module('app.note', [])
  .component('post', post);
```

[slide]

# AngularJS 组件结构

```bash
app/
├── app.js
├── commons
│   ├── commons.module.js
│   ├── footer
│   │   ├── footer.html
│   │   └── footer.js
│   ├── header
│   │   ├── header.html
│   │   ├── header.js
│   │   └── header.less
├── configs
│   ├── app.config.js
│   ├── app.routes.js
│   ├── app.run.js
│   └── configs.module.js
├── features
│   ├── features.module.js
│   ├── apps
│   │   ├── apps.html
│   │   └── apps.js
│   └── note
│       ├── note.html
│       ├── note.js
│       ├── note.less
│       ├── note.module.js
│       ├── page
│       │   ├── page.html
│       │   ├── page.js
│       │   └── page.less
│       ├── post
│       │   ├── post.html
│       │   ├── post.js
│       │   └── post.less
└── services
    ├── githubService.js
    ├── musicService.js
    └── services.module.js
```

[slide]

# 「越痛苦的事情越要早做」

```js
var path = require('path');
var webpack = require('webpack');

module.exports = {
  context: __dirname,
  entry: {
    app: ['webpack/hot/dev-server', './app/app.js']
  },
  output: {
    path: './dist',
    filename: 'bundle.js'
  },

  module: {
    loaders: [
      {test: /\.js$/, exclude: /node_modules/, loader: 'ng-annotate?add=true!babel-loader'},
      {test: /\.css$/, loader: "style!css"},
      {test: /\.less$/, loader: "style!css!less"},
      {test: /\.(eot|woff|woff2|ttf|svg)(\?\S*)?$/, loader: 'url?limit=100000&name=./fonts/[name].[ext]'},
      {test: /\.(png|jpe?g|gif)$/, loader: 'url-loader?limit=8192&name=./images/[hash].[ext]'},
      {test: /\.html$/, loader: 'ngtemplate!html?attrs[]=img:src img:ng-src'}
    ],
    noParse: []
  },

  plugins: [
    new webpack.HotModuleReplacementPlugin()
  ],

  resolve: {
    extensions: ['', '.js', '.json'],
    alias: {
      'react': './pages/build/react'
    },
    modulesDirectories: ['node_modules', 'bower_components']
  }
};
```
[slide]

# [NoBackend Website](http://nobackend.website)

----

<iframe data-src="http://nobackend.website" src="about:blank;"></iframe>


