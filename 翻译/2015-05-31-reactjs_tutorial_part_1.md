---
layout: post
title: 【译】React.js教程 第一部分：Hello World!
categories: [翻译]
tags: [React, Express]
published: True

---

技术系列笔记均已迁移至GitBook，更多`React`的内容请到：[http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html](http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html)

# React.js Tutorial Part 1

原文地址：[http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/)

> Welcome to my tutorial on how to get a website up and running using [React.js](http://facebook.github.io/react/) and [Node.js](http://nodejs.org/). I am expecting this to be a multipart tutorial as we go through building a job board for my local [Node.js Meetup Group](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/), though I am not sure how long these tutorials will last. I hope you enjoy them and if so feel free to share them! You can follow along with my progression on my jobs.nodedc.com [github repo](https://github.com/joshfinnie/jobs.nodedc.com)

欢迎来到我的教程，本教程将讲述如何利用[React.js](http://facebook.github.io/react/)和[Node.js](http://nodejs.org/)搭建一个网站。通过这几部分的教程，期望我们能够一起为我的本地`Node.js`见面群（Node.js Meetup Group）搭建一个工作布告栏，尽管我都不确定这些教程会持续多久。期望你能够享受并且尽情地分享这些教程！你可以在jobs.nodedc.com [github repo](https://github.com/joshfinnie/jobs.nodedc.com)上随时查看我的进展。

## Getting Started with Express | 从 Express 开始

> In this tutorial I am going to assume you have Node.js installed since it is becomming standard in so many of today's build processes. If you do not have it installed, check out [this article](http://howtonode.org/how-to-install-nodejs).

在本次教程中，我假设你已经安装好Node.js，因为它已经在很多现代构建流程中成为标准了。如果你还没有安装好，参考[这篇文章](http://howtonode.org/how-to-install-nodejs)吧！

> The first thing we are going to do is set up a standard [express](http://expressjs.com/) app. This is easy do to through `express-generator`. Install `express-generator` using the following command:

我们要做的第一件事就是搭建一个标准的[express](http://expressjs.com/)应用，使用`express-generator`能够轻松快速生成相应的文件目录（译者注：脚手架scaffold）。使用以下命令安装：

```bash
$ npm install express-generator -g
```

> Once installed, we are going to create a basic express app. To generate this express app, we run the following command:

安装好之后就可以构建一个基础的express应用了，使用以下命令：

```bash
$ express jobs.nodedc.com

create : jobs.nodedc.com
create : jobs.nodedc.com/package.json
create : jobs.nodedc.com/app.js
create : jobs.nodedc.com/public
create : jobs.nodedc.com/public/javascripts
create : jobs.nodedc.com/public/stylesheets
create : jobs.nodedc.com/public/stylesheets/style.css
create : jobs.nodedc.com/routes
create : jobs.nodedc.com/routes/index.js
create : jobs.nodedc.com/routes/users.js
create : jobs.nodedc.com/public/images
create : jobs.nodedc.com/views
create : jobs.nodedc.com/views/index.jade
create : jobs.nodedc.com/views/layout.jade
create : jobs.nodedc.com/views/error.jade
create : jobs.nodedc.com/bin
create : jobs.nodedc.com/bin/www

install dependencies:
    $ cd jobs.nodedc.com && npm install

run the app:
    $ DEBUG=jobs.nodedc.com ./bin/www
```

> With the output of `express-generator` we can see that we are well on our way to what we need from Express. This is a bit overkill, but with a few small changes, we should have a working express app which will then run (eventually) our API and serve our React site.

从`express-generator`的输出中我们可以看到我们正在构建所需要的Express部件。这有一点矫枉过正，但有一些小的变化，我们应该要有一个可以工作的express程序来（最终）运行我们的API，从而服务于我们的React网站。

> Let's start up this generated site and see what we get. Below is the image that you should see in your browser (at [http://localhost:3000](http://localhost:3000/)) if you are following along.

让我们启动已经生成的网站看看吧，从下面的图片你可以从浏览器中([http://localhost:3000](http://localhost:3000/)) 看到以下内容。

![](http://www.joshfinnie.com/assets/images/blog/hello-express.png)

> I then recommend going through the generated code and cleaning it up a little bit. We will not need the `user` routes so I just deleted them. I also expanded on the `package.json` some to add a description and keywords as well as changed the version to something more reasonable.

我建议查看已生成的代码，然后清除一些不必要的东西。我们不需要`user`路由就删掉，然后需要在`package.json`中添加一些描述、关键字和版本，使之更加合理。

## Adding React.js | 添加 React.js 

> Now that we have a pretty basic express application as our backend, we are now going to jump into adding react. Adding react is not that difficult, but there are a few ways of doing things. Since we are already within a node.js app, I am going to go down the route of building our jsx scripts into javascript. To get ready for this, we need to install the `react-tools` node package. You can do that by the following command:

既然我们已经有了一个漂亮的基础Express应用作为后端，现在就开始添加React。添加React并不困难，这里有几种能够实现。由于我们已经有了node.js应用，我们就继续添加相应的工具来将jsx脚本编译成标准JavaScript。为此，我们需要安装`react-tools`这个node包，使用如下命令：

    $ npm install react-tools --save-dev

> We add the `--save-dev` flag to make sure the `react-tools` package is saved as a development requirement in our `package.json`. Now, to convert the jsx scripts to javascript, we just have to run the following command:

使用`--save-dev`标志可以保证`react-tools`这个包能够作为开发环境依赖添加到我们的`package.json`里面。现在我们可以使用这样的命令将jsx脚本编译成标准JavaScript：

    $ ./node_modules/react-tools/bin/jsx public/javascripts/src/ public/javascripts/build/

> **Note:** You could also install `react-tools` globlally if you'd like.

**注意：** 你也可以全局安装`react-tools`。

> Next we want to [download React 0.12.2](http://facebook.github.io/react/downloads/react-0.12.2.zip), extract, and move `react-0.12.2/build/react.min.js` to our `/public/javascripts/build/` directory. Let's add React.js to our template! The default templating language for `express-generator` is [Jade](http://jade-lang.com/). It is a bit difficult to comprehend at first (and `express-generator` allows you to substitute either [EJS](http://www.embeddedjs.com/) or [Handlebars](http://handlebarsjs.com/) if you are more comfortable with those), but I find it super simplistic!

接下来，我们下载[React 0.12.2](http://facebook.github.io/react/downloads/react-0.12.2.zip)，解压，移动`react-0.12.2/build/react.min.js`到`/public/javascripts/build/`目录。然后添加React.js到我们的模板中！`express-generator`的默认模板语言是[Jade](http://jade-lang.com/)。（`express-generator`还允许你使用[EJS](http://www.embeddedjs.com/)或者[Handlebars](http://handlebarsjs.com/)，如果你更喜欢他们的话。）这在一开始可能会有点理解困难，但是我发现这特别简单。

> To add `react.min.js` to our templates, we just append it to the bottom of our `views/layout.jade` file as below:

将`react.min.js`添加到模板中，然后我们可以在`views/layout.jade`文件的底部添加：

```jade
doctype html
html
head
    title= title
    link(rel='stylesheet', href='/stylesheets/style.css')
body
    block content
    script(src='/javascripts/build/react.min.js')
```

> Rerunning `DEBUG=jobs.nodedc.com ./bin/www` we should see our starting screen again, but now it's React.js ready. Now our templates should be ready for our React Components!

重新运行`DEBUG=jobs.nodedc.com ./bin/www`，应该可以看到跟开始时一模一样的内容，但是React.js已经准备好了。现在模板就为React模块做好准备啦！

## Adding a React.js Component | 添加一个 React.js 组件

> Now that we have our express app running react.js, we can now start the process of writing our react application. In this part of the tutorial, we are only going to do a basic "Hello World" component, but next time we will start developing the components we need for our job board. So first, let's create our component.

既然我们已经准备好了可以运行react.js的express应用，我们现在可以开始编写React应用了。在这部分的教程中，我们只是写一个最基础的“Hello World”组件，但是下一次我们会正式开始开发所需要的工作布告栏。让我们开始吧。

> The first thing we want to do is create the `div` needed for react. In the `views/index.jade` file, add a div with an `id` of "example". With jade, your `index.jade` file should look like this:

第一件要做的是就是为react创建一个`div`标签。在`views/index.jade`文件中添加一个div，`id`为"example"。`index.jade`文件如下：

```jade
extends layout

block content
    #example
```

> Next we want to create a simple react.js component in our `public/javascripts/src/` folder called `helloworld.jsx`. This component should look like:

接下来我们在`public/javascripts/src/`目录中创建一个简单的react.js组件，`helloworld.jsx`：

```js
React.render(
<h1>Hello, world from React.js!</h1>,
document.getElementById('example')
);
```

> Because we are using the `react-tools` node package, we want to add the compiled javascript code to our templates. Change you `views/layout.jade` file to the following:

由于我们使用的`react-tools`包，所以我们将添加已经编译好的JavaScript代码。改变`views/layout.jade`文件：

```jade
doctype html
html
head
    title= title
    link(rel='stylesheet', href='/stylesheets/style.css')
body
    block content
    script(src='/javascripts/build/react.min.js')
    script(src='/javascripts/build/helloworld.js')
```

> And run the `react-tools` package to compile our component with the following command:

使用`react-tools`编译：

```bash
$ ./node_modules/react-tools/bin/jsx -x jsx public/javascripts/src/ public/javascripts/build/
```

> Remember to use the `-x` flag as we used the extension `.jsx` for our jsx code. Now running the express server again we should see:

记得使用`-x`标志，因为我们使用`.jsx`作为代码文件扩展名，现在运行重新运行服务器：

![](http://www.joshfinnie.com/assets/images/blog/hello-react.png)

> There we have it. A pretty simple Hello World app with React.js and Express.js. Next we will clean up this process with some automation help from [gulp](http://gulpjs.com/) and start building react.js components to help us with our NodeDC job board!

至此，我们使用React.js和Express.js搭建了一个简单的Hello World应用。下一次我们会使用[gulp](http://gulpjs.com/)来自动化进行整个搭建过程，然后正式开始使用react.js组件来帮助我们搭建NodeDC工作布告栏。
