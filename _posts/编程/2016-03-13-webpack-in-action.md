---
layout: post
title: 提升前端开发体验：Webpack 实际上手
categories: [编程]
tags: [Webpack, Angular, 前端]
published: True

---

## 安装，运行，热加载

首先当然是安装，当然是使用更加符合中国社会主义国情的 [cnpm](http://npm.taobao.org/)，道理大家都懂的。

    cnpm install webpack webpack-dev-server -g

> `webpack-dev-server` 是一个基于 Express.js 框架的静态资源Web服务器，对于简单静态页面或者仅依赖于独立服务的前端页面，都可以直接使用这个开发服务器进行开发。在开发过程中，开发服务器会监听每一个文件的变化，进行实时打包，并且可以推送通知前端页面代码发生了变化，从而可以实现页面的自动刷新。

在根目录下添加最基本的 `webpack.config.js` 配置文件，运行 webpack 时会默认该文件配置，如果要指定另外的配置文件，可以执行：`webpack --config webpack.custom.config.js`，这也就可以通过 Script 指定不同环境下所需要的打包配置了。然后在 `entry` 入口当中配置一下代码的热加载，只需要将 `'webpack/hot/dev-server'` 加入到打包的代码当中即可：

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

没想到一来就出错了：[Module not found: Error: Cannot resolve module ‘webpack/hot/dev-server’](http://react-china.org/t/module-not-found-error-cannot-resolve-module-webpack-hot-dev-server/4454)，从上述链接得知需要将 webpack 作为项目依赖直接安装到当前项目模块当中。

    cnpm install webpack --save--dev

前面所提到的 `'webpack/hot/dev-server'` 其实就是对应 `node_modules/webpack/` 目录当中的文件。可以使用 `webpack-dev-server` 命令直接启动，默认启动端口 8080，通过 <localhost:8080/webpack-dev-server/> 可以访问到页面，文件修改后保存时会在页面头部看到 sever 的状态变化，并且会进行热替换，实现页面的自动刷新。

对于 React 的配置来说稍有所不同，参考 <https://segmentfault.com/a/1190000002551952#articleHeader10>，可以实现组件级的刷新，甚至不用刷新整个页面，所以就[避免了只要一刷新就不得不重新点击一遍应用的痛苦](http://blog.jimmylv.info/2016-02-21-Chinese-Version-of-React.js-Best-Practices-for-2016#title17)。

    entry: [
      'webpack-dev-server/client?http://0.0.0.0:8080', // WebpackDevServer host and port
      'webpack/hot/only-dev-server',
      './scripts/index' // Your appʼs entry point
    ]

## 配置 NPM Script

程序员总是要学会偷懒并且应当「以偷懒为傲」，在开发过程中所发现的重复工作都应该利用构建工具来实现自动化，常见的前端构建工具可能有 Grunt/Gulp 之流，辅于各类插件就可以实现很多工程构建功能。但其实在这里，利用 webpack 本身的模块打包能力以及各种各样的 loader 和插件配置，我们甚至无需引入 Grunt/Gulp 就可以满足前端的工程构建需求，比如预处理、编译、混淆、压缩、打包等等。当然这里我们就直接借助 NPM Script 来进一步简化和管理 webpack 的相关命令。

    "scripts": {
        "build": "webpack -w --bail --display-error-details",
        "start": "webpack-dev-server --history-api-fallback --hot --inline --progress"
    }

打包，启动：

    npm run build # 提供 watch 方法，实时进行打包更新并打印出错信息
    npm start # 启动服务器，浏览器直接访问的是 index.html

## 重构项目代码

先就一股脑安装所有的 loader，我之后会再一一介绍每个 loader 所提供的预处理功能：

    cnpm install babel-core babel-loader style-loader css-loader less-loader file-loader url-loader html-loader ng-annotate-loader ngtemplate-loader --save-dev

然后在 `webpack.config.js` 配置文件当中添加相应文件所需的 loader 以及参数配置：

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

### babel-loader 预编译 ES6

即使浏览器并没有实现多少 ES6 的语法规范，但是在 Babel 等转译工具的引领之下，ES6 远比想象中要普及地多得多。很遗憾又遇到了问题，`You may need an appropriate loader to handle this file type`，但是非常棒的是，运行 webpack 能够实时打印错误信息，似乎是 `babel-loader` 没有正确地解析到 ES6 语法。参考 babel [官方文档]([http://babeljs.io/docs/setup/#webpack])，需要首先安装 es2015 预处理模块，再给 babel-loader 添加相应的 `es2015` 参数。

    cnpm install babel-preset-es2015 --save-dev

    echo '{ "presets": ["es2015"] }' > .babelrc # 也可以直接写 loader 参数里。

结果犯了个小错误，漏掉在 loaders 上一层写 module 了，实为罪过啊喂，折腾了半天。

    module: {
        loaders: [
          {test: /\.js$/, exclude: /node_modules/, loader: 'ng-annotate!babel-loader'}
        ]
    },

与此同时，把之前放在 `bower_components` 底下的模块 转移到 `node_modules` 底下，抛弃 Bower，统一使用 NPM 进行前端依赖管理。

接下来就可以使用 ES6 的 `export default` 和 `import from` 语法导入相关依赖了，虽说 Webpack 对 CommonJS 和 AMD 都做了兼容，但依旧有一些直接只采用 Angular 模块功能所定义的插件，这就没办法通过 `require` 或者 `import` 导入了，还是只能通过 HTML Script 的传统方式引入，待我再想想解决办法，摊手┑(￣Д ￣)┍：

    require ('./style/base.less');

    import angular from 'angular'
    import ngRoute from 'angular-route'

    import githubService from './app/services/githubService'
    import MainCtrl from './app/controllers/mainController'
    import Components from './app/components/components.module'

### ng-annotate-loader 确保依赖安全注入

一个小坑：添加 Angular `$inject` 的压缩插件，<https://www.npmjs.com/package/ng-annotate-loader>，官方文档没有更新，应该用 `!` 符号来联接多个 loader。

    controller: function ($http, $routeParams, base64) {
        'ngInject';

        var vm = this;

        vm.$onInit = function () {
            ...
        }
    }

然后就只需要在函数参数之下添加 `'ngInject';` 注释就可以自动转化为安全的数组写法，这个 loader 的自动转化效果如下，从而保证了变量被压缩之后依旧能够通过数组中的字符串找到相对应的依赖：

    controller:["$http","$routeParams","base64",function(e,t,n){"ngInject" ...}

### 使用 Less 替换 CSS

Webpack 最棒的一点就是将 JavaScript、CSS、 字体、图片等资源文件统统视为模块，所有的静态文件都支持打包，配合 loader 加载器，就可以支持 Sass，Less 等 CSS 预处理器，而且串联式模块加载器以及插件机制就使得处理流程特别地灵活。

    {test: /\.less$/, loader: "style!css!less"},

添加 Less 相关的 loader 便可以使用 Less 语法来书写样式了，所支持的[扩展语法](http://lesscss.org/features/#features-overview-feature)可以说大大提高了编程效率，也提高了 CSS 代码的可读性。干掉了项目所依赖的遗留文件 `app.min.css` 之后，不得不说边改边自动刷新的感觉实在太爽啦，当然需要注意的是修改 `webpack.config.js` 里边的东西时还是需要重启一下 Webpack。

这里还提到一点就是当 CSS 文件当中（比如 BootStrap 和 FontAwesome 等依赖）需要加载字体的时候，还需要使用 `url-loader` 来对相关字体进行预处理，并且可以设置相关参数比如 `limit` 来限制文件大小，以及 `name` 参数来指定字体文件被打包到的具体文件路径。

    {test: /\.(eot|woff|woff2|ttf|svg)(\?\S*)?$/, loader: 'url?limit=100000&name=./fonts/[name].[ext]'},
    {test: /\.(png|jpe?g|gif)$/, loader: 'url-loader?limit=8192&name=./images/[hash].[ext]'},

### String 化 HTML 模板

在 AngularJS 1.x 里边儿还是使用单独的 HTML 文件来作为组件模板，我在重构的时候首先使用了 `raw-loader` 来直接 `require` 组件所对应的模板文件，其效果就是将该 HTML 文件在引入 JS 之前就转化成了字符串，所以在 Angular 当中只需指定 `template` 即可，并且都不再需要写相对路径了，`'./features/note/note.html'` -> `'./note.html'`
。

    export default  {
      template: require('./note.html'),
      bindings: {
        postContent: '<',
        siteInfo: '<',
        index: '<'
      },
      ...
    }

然后第二种方案就直接更进一步了，使用 `ngtemplate-loader` 来使用 AngularJS 的模板 Cache 功能，其原理也是将 HTML 文件转化为 String 并通过 ID 的形式保存在 JavaScript 代码当中，从而免去了页面刷新重新加载 HTML 模板文件的时间了，在 HTTP 2.0 还没有普及之前，哪怕减少一个 HTTP request 也是能够在一定程度上减少客户端浏览器进行网络请求的压力，特别是在渣渣网速的移动设备上。

    {test: /\.html$/, loader: 'ngtemplate!html?attrs[]=img:src img:ng-src'}

从而我们的写法又变成了 `templateUrl` 的形式，但是最终 Angular 组件的 HTML 模板都已经被保存在了 JS 当中，这其实又跟 React 的 JSX 语法和 Angular 2.0 殊途同归了，并且在组件化的思想越发清晰之后，反而会觉得在不同的 JS、CSS、HTML 文件之间进行跳转实在太麻烦，而且并没有什么必要。

    export default {
      transclude: true,
      templateUrl: require('./post.html'),
      bindings: {
        pageContent: '<',
        showToc: '<'
      },

想起了 Vue 的组件化代码组织就是将三种类型的代码放在同一个 `.vue` 文件当中，实乃明智之举啊，开发体验一定很棒，我已经厌倦了每次修改一个组件却要频繁辗转于 3 个以上的文件了。
