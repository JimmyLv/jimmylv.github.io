---
layout: post
title: 【译】React.js教程 第二部分：使用Gulp自动化构建工具
categories: [翻译]
tags: [React, Gulp]
published: True

---

技术系列笔记均已迁移至GitBook，更多`React`的内容请到：[http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html](http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html)

# React.js Tutorial Part 2

原文地址：[http://www.joshfinnie.com/blog/reactjs-tutorial-part-2/](http://www.joshfinnie.com/blog/reactjs-tutorial-part-2/)

> Welcome to part 2 of my tutorial on how to get a website up and running using [React.js](http://facebook.github.io/react/) and [Node.js](http://nodejs.org/). You can read Part 1 [here](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/) if you haven't already.

欢迎来到如何使用[React.js](http://facebook.github.io/react/)搭建网站教程的第二部分不，如果你还没有阅读第一部分，[戳这里](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/)。

> In this part of the tutorial, we are going to make our React.js/Express.js app more like a full-fledged web application with the addition of a build system called [Gulp.js](http://gulpjs.com/). Gulp.js is a build system (or task runner) that I have been using for a while. There are [many](http://gruntjs.com/), [many](https://github.com/broccolijs/broccoli), [many](http://webpack.github.io/) out there, but I find Gulp.js to be very sufficient for my needs.

这一部分，我们将使用额外的[Gulp.js](http://gulpjs.com/)构建工具，搭建一个更加完善的React.js/Express.js应用。Gulp.js是一个我一直在使用的构建工具（任务管理器），这里有很多类似的[gruntjs](http://gruntjs.com/), [broccoli](https://github.com/broccolijs/broccoli), [webpack](http://webpack.github.io/)等工具，但是最终发现Gulp.js最符合需求。

## Installing Gulp | 安装 Gulp

> Installing Gulp is very similar as to how we installed Express in the last tutorial, we need to add the `--save-dev` flag to save gulp to our `devDependencies` portion of the `package.json` file. Run:

安装Gulp非常简单，就像上个教程中安装Express一样。使用`--save-dev`标记将gulp保存到`package.json`文件的`devDependencies`部分，运行：

```bash
$ npm install --save-dev gulp
```

> Now with Gulp installed, we can create our basic `gulpfile.js` file:

Gulp安装好之后，我们建立一个`gulpfile.js`文件：

```js
var gulp = require('gulp');

gulp.task('default', function() {
// place code for your default task here
});
```

> Now we need to install the Gulp packages that we will need to build our application. To start, let's install [browserify](https://www.npmjs.com/package/browserify), [reactify](https://www.npmjs.com/package/reactify) and [vinyl-source-stream](https://www.npmjs.com/package/vinyl-source-stream). To install these packages, run the following command:

现在需要为我们的应用安装Gulp包，开始之前，让我们添加[browserify](https://www.npmjs.com/package/browserify)，[reactify](https://www.npmjs.com/package/reactify)和[vinyl-source-stream](https://www.npmjs.com/package/vinyl-source-stream)。运行：

```bash
$ npm install --save-dev react browserify reactify vinyl-source-stream
```

> At this point, we can remove `react-tools` from our `devDependencies` since we no longer need to build our `.jsx` files via the command line. Your `devDependencies` should look like this:

在这时，我们可以从`devDependencies`中删除`react-tools`，因为我们不再需要通过命令行手动编译`.jsx`文件了。

```json
"devDependencies": {
    "browserify": "^8.1.3",
    "gulp": "^3.8.10",
    "react": "^0.12.2",
    "reactify": "^1.0.0",
    "vinyl-source-stream": "^1.0.0"
}
```

### Setting up Gulp | 设置 Gulp

> The next step is to set up Gulp to automatically build our `.jsx` files into usable javascript. To do this, we are going to create a Gulp task. A Gulp task is a function that will stream a bunch of steps transforming our `.jsx` to javascript. We will need to modify our `gulpfile.js` to look like this:

下一步就是编写Gulp任务来将`.jsx`文件自动编译成可用的JavaScript文件。一个Gulp任务就是一个函数，包含编译文件的一系列步骤。我们需要修改`gulpfile.js`：

```js
var gulp = require('gulp');

var browserify = require('browserify');
var reactify = require('reactify');
var source = require('vinyl-source-stream');

gulp.task('js', function(){
    browserify('./public/javascripts/src/app.jsx')
        .transform(reactify)
        .bundle()
        .pipe(source('app.js'))
        .pipe(gulp.dest('public/javascripts/build/'));
});

gulp.task('default', ['js']);
```

> Now running `gulp` from the command line will trigger the build of our React app; however, there are some things we need to do to our react app first!

现在从命令行中运行`gulp`就会自动编译我们的React应用。但是，还有一些事情需要做！

### Browserifying React | 将 React 浏览器化

> There are some things we need to do to our application before browserify will work. Last tutorial we wrote a `helloworld.jsx`, now we need to modify this slightly to work with browserify. If you don't know browserify is a tool for compiling node-flavored commonjs modules for the browser. So let's modify our React code to work with browserify.

在browserify可以工作之前需要做一些事情，在上一节中编写了`helloworld.jsx`，现在我们需要稍微修改一下。browserify是一个工具，可以将node模块编译成浏览器可执行的commonjs模块。

> First, we need to create an "entry point" for browersify, we can do this by simply creating an `app.jsx` file:

首先，我们需要为browersify创建一个入口，建立一个`app.jsx`文件就可以了：

```js
var React = require('react');
var HelloWorld = require('./HelloWorld.jsx');

React.render(
    <HelloWorld />,
    document.getElementById('example')
);
```

> This file is taking our `HelloWorld` component and rendering it in the div with id "example". This code is taken from our original `helloworld.jsx` file from last tutorial. Instead of doing everything in that file, we are now requiring a module `HelloWorld` and rendering it in `app.jsx`. The reason for this is that as our application gets more complex, we have more control of how our files are broken out.

这个文件就是一个`HelloWorld`组件，可以被渲染到`id="example"`的div标签中，这份代码是直接从上一个教程的`helloworld.jsx`文章拿到的。但现在不是在一个文件中做所有事情，而是将`HelloWorld`模块渲染到`app.jsx`中。

> The next thing is that we have is modify our existing `helloworld.jsx` file to be a React component named `HelloWorld.jsx`. This is easily done and our `HelloWorld.jsx` file now looks like this:

下一件事是已有的`helloworld.jsx`文件修改成React组件，`HelloWorld.jsx`：

```js
var React = require('react');

module.exports = React.createClass({
render: function() {
    return (
    <h1>Hello, world from a React.js Component!</h1>
    )
}
});
```

> Notice that the `HelloWorld.jsx` and `app.jsx` files are combined to be very similar to how the 'helloworld.jsx' looked. Again, the reason for breaking our app into these two files are for future modules to be added.

注意到`HelloWorld.jsx`和`app.jsx`文件组合在一起，看起来很像单独的'helloworld.jsx'文件。原因是为了将我们的应用拆分成不同的模块，以便于未来的可扩展性。

> Now, running `gulp` will create a javascript file in `public/javascripts/build/` called `app.js` and it will have everything we need to run our React app. Let's add this to our `layout.jade` file instead of the `react.min.js` and `helloworld.js` files:

现在运行`gulp`会在`public/javascripts/build/`目录中新建名为`app.js`的标准JavaScript文件，我们需要它来运行React应用。让我们添加到`layout.jade`，替换之前的`react.min.js`和`helloworld.js`文件：

```
doctype html
html
head
    title= title
    link(rel='stylesheet', href='/stylesheets/style.css')
body
    block content
    script(src='/javascripts/build/app.js')
```

> There you have it, a React application being built with Gulp using browersify!

现在就有了一个使用Gulp自动构建browersify的React应用啦！

![](http://www.joshfinnie.com/assets/images/blog/hello-react-component.png)

### Gulp Watch | Gulp 监控

> To make Gulp even better, let's implement the built-in `watch` functionality to have gulp watch for changes in our `.jsx` files and automatically build our javascript. To do this, we want to add the following task to our `gulpfile.js`:

为了更好得使用Gulp，我们可以实现一个内建的`watch`功能，能够自动监测和编译`.jsx`文件。添加任务：

```js
gulp.task('watch', function() {
    gulp.watch("public/javascripts/src/**/*.jsx", ["js"])
})
```

> Also add that task to your default Gulp task:

同时将`watch`任务添加到默认任务中：

```js
gulp.task('default', ['js', 'watch']);
```

> Now when we run `gulp` it will watch for changes in our `.jsx` and rebuild our javascript with that change! Awesome!

现在我们可以运行`gulp`来自动监控`.jsx`的变化，并且自动重新编译成标准的JavaScript，Awesome！

### Next Time | 下一次

> Next time we will continue to use Gulp to build out some more niceties when building a web application, introduce [Bower](http://bower.io/), and finally get to building some of the React Components we will use in our job board.

下一次我们将继续使用Gulp来构建开发web应用时的其他细节，介绍[Bower](http://bower.io/)，最终为我们的工作布告栏应用的编写React组件。

