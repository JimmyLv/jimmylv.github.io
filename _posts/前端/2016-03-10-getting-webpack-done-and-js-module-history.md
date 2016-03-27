---
layout: post
title: 搞定 Webpack (1)：前端模块化实践小史与 Webpack 入门
categories: [前端]
tags: [Webpack, 工程化, JavaScript]
published: True

---

## JavaScript 模块化管理

### 未来即现在：ES6 模块

via [《ECMAScript 6 入门》 —— 阮一峰](http://es6.ruanyifeng.com/#docs/module)：

> 历史上，JavaScript一直没有模块（module）体系，无法将一个大程序拆分成互相依赖的小文件，再用简单的方法拼装起来。其他语言都有这项功能，比如Ruby的require、Python的import，甚至就连CSS都有@import，但是JavaScript任何这方面的支持都没有，这对开发大型的、复杂的项目形成了巨大障碍。

> 在ES6之前，社区制定了一些模块加载方案，最主要的有CommonJS和AMD两种。前者用于服务器，后者用于浏览器。ES6在语言规格的层面上，实现了模块功能，而且实现得相当简单，完全可以取代现有的CommonJS和AMD规范，成为浏览器和服务器通用的模块解决方案。

> ES6模块的设计思想，是尽量的静态化，使得编译时就能确定模块的依赖关系，以及输入和输出的变量。CommonJS和AMD模块，都只能在运行时确定这些东西。比如，CommonJS模块就是对象，输入时必须查找对象属性。

    // profile.js
    var firstName = 'Michael';
    var lastName = 'Jackson';
    var year = 1958;

    export {firstName, lastName, year};

    // main.js
    import {firstName, lastName, year} from './profile';

---*然而那是未来，我们来看看过去，以及现在*---

### CommonJS，AMD，以及 UMD 

CommonJS 和 AMD 就在在 JavaScript 还没有模块管理的情况下民间所制定的两大规范，前者定义的是模块的同步加载，主要用于 NodeJS；而后者则是异步加载，通过 RequireJS 等工具适用于浏览器。

众所周知，NodeJS 的出现使 JavaScript 一下子有了新的用武之地，同时在 NodeJS 推动下的 CommonJS 模块系统也是逐渐深入人心。使用 CommonJS 的写法大致如下：

    var firstModule = require("firstModule");
    //your code...
    module.export = anotherModule

**但是**，随着 NPM 成为主流的 JavaScript 组件发布平台，越来越多的前端项目也依赖于 NPM 上的项目，或者自身就会发布到 NPM 平台。因此，让前端项目**在浏览器中更方便地使用 NPM 上的资源**成为一大需求。

而浏览器加载脚本的方式天生不支持同步的加载，无法通过文件 I/O 同步的方式 require 加载一个 JavaScript 脚本。所以就[从 CommonJS 中逐渐分裂出了 AMD](https://leohxj.gitbooks.io/front-end-database/content/javascript-modules/modules-tools-compare.html)，即 Asynchronous Module Definition，属于**异步加载**的模块机制。这个在浏览器环境有很好支持的 module 规范，其中最有代表性的实现则是 RequireJS。使用 Require.js 的写法大致如下：

    define(['firstModule'], function(module) {
        //your code...
        return anotherModule
    })

其实我们单比较写法，就知道 CommonJS 是更为优秀的。它是一种同步的写法，对 Human 友好，而且代码也不会繁琐臃肿。而 Browserify 工具的出现，则满足了在浏览器当中直接使用 `require()` 的同步语法加载 NPM 模块的需求。

既然 CommonJS 和 AMD 风格非常流行，似乎就缺少了一个统一的规范。所以人们产生了这样的需求，希望能够同时支持两种风格的「通用」模式，而 UMD (Universal Module Definition) 即通用模块规范的出现，就是希望提供一个前后端跨平台的解决方案(支持 AMD 与 CommonJS 模块方式)。

不得不承认，这个模式略难看，但是它兼容了 AMD 和 CommonJS，同时还支持老式的「全局」变量规范：

    (function (root, factory) {
        if (typeof define === 'function' && define.amd) {
            // AMD
            define(['jquery'], factory);
        } else if (typeof exports === 'object') {
            // Node, CommonJS之类的
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

UMD 的实现其实很简单：

- 先判断是否支持 AMD（`define` 是否存在），存在则使用 AMD 方式加载模块。
- 再判断是否支持 Node.js 模块格式（`exports` 是否存在），存在则使用 Node.js 模块格式。
- 前两个都不存在，则将模块公开到全局（window 或 global）。

### 只能在运行时分析依赖？

以上所提到的类似于 RequireJS 等模块化框架在工程方面都依旧存在缺点，其关键原因就在于[**「纯前端方式只能在运行时分析依赖关系」**](https://github.com/fouber/blog/issues/4)，不能同时满足**按需加载**，**请求合并**和**依赖管理**这三个需求。

既然根本问题出在运行时分析依赖，那么新思路的策略就很简单了：不在运行时分析依赖。当然，这就要借构建工具来做线下分析了，其基本原理就是：利用构建工具**在线下进行模块依赖分析**，然后把依赖关系数据写入到构建结果中，并调用模块化框架的依赖关系声明接口，实现模块管理、请求合并以及按需加载等功能。

## 资源模块化

### Webpack 的特性介绍

长久以来，Web 开发者都是把所需的 Javascript、CSS 等文件一股脑放进 HTML 里边儿，这对于庞大的项目来说管理起来非常麻烦，也无法满足前端在模块管理、资源加载等方面的工程需求。

而在 Webpack 当中，最酷的一点就是将 Web 开发中常用的如 JavaScript、CSS 以及图片、字体等各种静态文件统称为模块，并对它们进行统一的模块化加载，预处理以及打包发布，从而让开发过程变得更为高效。而且，**任何静态资源都可以视作模块，然后模块之间还可以相互依赖**，通过 Webpack 对模块进行处理后，就可以打包成我们想要的静态资源。其官方主页用下面这张图来说明 Webpack 的作用：

![](https://webpack.github.io/assets/what-is-webpack.png)

就像前面所提到的那样，Webpack 具有和 RequireJS， Browserify 等模块化工具相类似的功能，但还有更多独有的新特性：

1. 对 CommonJS 、 AMD 、ES6的语法做了兼容，以及特殊模块的 Shim 处理，也就是说基本可以无痛迁移旧项目。
2. 对 JS、CSS、图片等资源文件都支持打包，配合 loader 加载器，也可以支持 Sass，Less 等 CSS 预处理器。
3. 串联式模块加载器以及插件机制，让其具有更好的灵活性和扩展性，例如通过 babel-loader 就可以直接使用 ES6 的模块机制（当然 [Webpack 2 将会直接支持 ES6 模块](https://gist.github.com/sokra/27b24881210b56bbaff7)）。
4. 有独立的配置文件 `webpack.config.js`，并可以根据环境的不同加载特定的配置文件，配置好就可以一劳永逸了。
5. 可以将代码切割成不同的 chunk，实现按需加载，有效利用浏览器的缓存功能提升性能，从而降低了初始化时间，提高用户体验。
6. 支持 SourceUrls 和 SourceMaps，即使打包在一起依旧方便调试。
7. 具有强大的 Plugin 接口，大多是内部插件，使用起来比较灵活。
8. Webpack 使用异步 IO 并具有多级缓存。这使得 Webpack 很快且在增量编译上更加快。

简单来说，Webpack 可以把你的应用代码分离成许多文件，如果你有许多页面在你的单页应用里面，用户只需要下载当前页面所需要的代码。如果你跳转到另一个页面，他们不需要重新加载通用的代码。
与此同时也能替代 Grunt 或者 Gulp 大部分的功能，因为它自己就可以构建和打包 CSS，预处理 CSS，编译 JS 和打包处理图片，甚至更多事情。

### 一个简单的 React 例子

首先来安装我们的主角 Webpack：

    cnpm i webpack -g

虽然在目前的情况下，浏览器还未完全支持 ES6 新特性，当我们依旧可以通过 Webpack 的 babel-loader 来将 ES6 语法预编译成现在浏览器都已经支持的 ES5 代码。首先使用 ES6 定义一个简单的 React 组件：

    // hello.js
    import React, {Component} from 'react';

    class Hello extends Component {
        render(){
            return (
                <div>Hello, {this.props.name}!</div>
            );
        }
    }

`entry.js` 作为应用的入口文件，将一个 Hello 组件输出到界面：

    // entry.js
    import React from 'react';
    import Hello from './hello';

    React.render(<Hello name="Nate" />, document.body);

`webpack.config.js` 文件通常放在项目的根目录中，它本身也是一个标准的 CommonJS 规范的模块：

    var path = require('path');

    module.exports = {
        entry: path.resolve(__dirname, './src/entry.js'),
        output: {
            path: path.resolve(__dirname, './assets'),
            filename: 'bundle.js'
        },

        module: {
            loaders: [
                { test: /\.js?$/, loaders: ['babel'], exclude: /node_modules/ },
                { test: /\.js$/, loader: 'babel-loader', exclude: /node_modules/}
            ]
        },

        resolve:{
            extensions:['','.js','.json']
        },
    };

可以看到，`entry`参数和`output`参数分别定义了输入输出文件的位置及名字，定义好的所有入口文件都会打包生成一个 `filename` 文件，然后就只需要在 HTML 文件中引入打包完成的 `./assets/bundle.js` 即可。

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

整个代码在[这里](https://github.com/dwqs/react_practice/tree/master/react-sample)，`git clone` 之后切换到 react-sample 目录下，在终端运行 `npm i && npm run build` 即可进行打包。更多有关 Webpack 的详细设置请参考原文章，[详解前端模块化工具-Webpack](https://segmentfault.com/a/1190000003970448)。

## Reference：最佳实践

Webpack 最酷的就是按「模块」预处理，最终按需打包，官方提供了很多很好用的 [loader](http://webpack.github.io/docs/list-of-loaders.html) 和 [plugins](https://webpack.github.io/docs/list-of-plugins.html)。化繁为简，结合 NPM Script 及其庞大的生态圈就可以搞定几乎全部的前端构建需求了，从而大幅度提升了开发体验。前端也在工程化的道路上越走越远，刀耕火种的时代正在慢慢改善，能够见证并参与其中享受着创造的乐趣，真是一件幸事。

- [Getting Started - Webpack](http://webpack.github.io/docs/tutorials/getting-started/)
- [如何使用webpack —— webpack-howto](http://qiutc.me/post/%E5%A6%82%E4%BD%95%E4%BD%BF%E7%94%A8webpack%E2%80%94webpack-howto.html)
- [Webpack，101入门体验](http://www.html-js.com/article/Webpack%203009)
- [详解前端模块化工具 Webpack](https://segmentfault.com/a/1190000003970448)
- [Webpack 入门指迷 —— 题叶](https://segmentfault.com/a/1190000002551952)
- [基于webpack的前端工程化开发之多页站点篇（一）](https://segmentfault.com/a/1190000004511992)