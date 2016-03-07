---
layout: post
title: 【译】React.js教程 番外篇（二）：如何升级NPM依赖的版本
categories: [翻译]
tags: [NodeJS, React]
published: True

---

技术系列笔记均已迁移至GitBook，更多`React`的内容请到：[http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html](http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html)

# React.js Tutorial Part (Interlude 2)

原文地址：[http://www.joshfinnie.com/blog/reactjs-tutorial-part-interlude-2/](http://www.joshfinnie.com/blog/reactjs-tutorial-part-interlude-2/)

> Welcome to part (Interlude 2) of my React.js/Express.js app tutorial. This is going to be an article about upgrading a [React.js](http://facebook.github.io/react/) application after coming back to a project after a while. Hopefully this will spur me to continue these tutorials as it has been too long since I have posted one.

欢迎来到我的React.js/Express.js应用教程番外篇的第二部分。这是一篇在项目开始之后如何升级[React.js](http://facebook.github.io/react/)版本的文章。希望这可以鞭策我继续把教程写下去，自从开始之后已经很长时间没有更新了。

## Reviewing Your Application | 回顾一下你的应用

> Since this is a Javascript application, we have the extreme benefit of having our package versions laid out within `package.json`. If we take a look at what is there currently, we'd see:

由于这是一个JavaScript应用程序，有个非常好的优势就是拥有`package.json`文件来管理package的版本信息。如果我们现在来看一下：

    {
      "name": "jobs.nodedc.com",
      "version": "0.1.0",
      "description": "A job board for the NodeDC meetup group.",
      "private": true,
      "scripts": {
            "start": "node ./bin/www",
            "postinstall": "node node_modules/bower/bin/bower install"
      },
      "dependencies": {
            "body-parser": "~1.10.1",
            "cookie-parser": "~1.3.3",
            "debug": "~2.1.1",
            "express": "~4.10.6",
            "jade": "~1.8.2",
            "morgan": "~1.5.1",
            "serve-favicon": "~2.2.0"
      },
      "devDependencies": {
            "bower": "^1.3.12",
            "browserify": "^8.1.3",
            "gulp": "^3.8.10",
            "gulp-nodemon": "^2.0.3",
            "gulp-sass": "^1.3.3",
            "gulp-sourcemaps": "^1.5.2",
            "react": "^0.12.2",
            "reactify": "^1.0.0",
            "vinyl-source-stream": "^1.0.0"
      }
    }
    

> Here, we have the list of `dependencies` and `dev-dependencies` for our application. To see what needs to be upgraded, we can use a super-handly Node.js module called [npm-check-updates](https://www.npmjs.com/package/npm-check-updates). Using this application is easy; first, install it globally (I recommend installing it globally, since you should be using this for all your projects which rely on NPM!) by running `npm install -g npm-check-updates`, and second, run `ncu` within the `jobs.nodedc.com` directory.

我们的应用程序有一个`dependencies`和`dev-dependencies`的版本列表。为了查看哪些版本需要升级，我们会用到一个「super-handly」的Node.js模块：`[npm-check-updates](https://www.npmjs.com/package/npm-check-updates)`。使用它非常容易，第一步全局安装（只所以推荐全局安装是因为你可能会在其他所有依赖NPM的项目上用到它），然后运行`npm install -g npm-check-updates`，第二步，在我们的`jobs.nodedc.com`项目目录下运行`ncu`命令即可。

> What this application will do is go to NPM and check to see if there's an update to your required packages (regardless of whether or not you have pinned your versions in `package.json`) and return with a nice list of what needs to be upgraded. When we run this application for `jobs.nodedc.com` we get the following list:

应用程序将会到NPM去检查项目所依赖的包是否有更新（不管你是否在`package.json`有没有添加版本信息），然后会返回一个需要升级的列表。
    
     $ ncu
    
     body-parser    ~1.10.1  →  ~1.13.3
     debug           ~2.1.1  →   ~2.2.0
     express        ~4.10.6  →  ~4.13.3
     jade            ~1.8.2  →  ~1.11.0
     morgan          ~1.5.1  →   ~1.6.1
     serve-favicon   ~2.2.0  →   ~2.3.0
     browserify      ^8.1.3  →  ^11.0.1
     gulp-sass       ^1.3.3  →   ^2.0.4
     react          ^0.12.2  →  ^0.13.3
    
    Run with -u to upgrade your package.json
    


> The `npm-check-updates` application gives you a nice flag, `-u`, to automatically update your `package.json` which is a nice feature and the main reason I prefer this app over just using `npm outdated`, but, FYI, it can be dangerous if you have major version jumps like we do here. Looking at the list above, we see two important upgrades which we will be handling in this blog post. First, `browserify` has gone from `8.1.3` to `11.0.1` and second, `react` has gone from `0.12.2` to `0.13.3`.

`npm-check-updates`应用还可以使用`-u`来自动升级所有`package.json`中的包，这将带来新的一些特性，这也是我更喜欢这个命令而不是`npm outdated`的主要原因。但是这也可能是非常危险的，如果你要进行一个非常大的版本跳跃。看看上面的列表，我们可以看到有两个非常重要的升级，我们将在这篇文章中来进行处理。首先，`browserify`将从`8.1.3`跨越到`11.0.1`，而`react`也从`0.12.2`升级到`0.13.3`。

> For the record, this is what `npm outdated` looks like:

作为记录，这是`npm outdated`的效果：

    $ npm outdated
    Package        Current  Wanted  Latest  Location
    debug            2.1.3   2.1.3   2.2.0  debug
    react           0.12.2  0.12.2  0.13.3  react
    jade             1.8.2   1.8.2  1.11.0  jade
    body-parser     1.10.2  1.10.2  1.13.3  body-parser
    morgan           1.5.3   1.5.3   1.6.1  morgan
    serve-favicon    2.2.1   2.2.1   2.3.0  serve-favicon
    gulp-sass        1.3.3   1.3.3   2.0.4  gulp-sass
    express         4.10.8  4.10.8  4.13.3  express
    browserify       8.1.3   8.1.3  11.0.1  browserify
    

> You can use this if you'd like and save the global download!

你也可以像这样全局安装然后使用它。

## Upgrading a Package | 升级包

> There are a few steps you want to take when upgrading a package that you rely on for your application. The first thing I do in read the release notes for each of the releases between where I am currently and where `npm-check-updates` wants me to be. Let's take a look at [React.js's release notes](https://github.com/facebook/react/blob/master/CHANGELOG.md). I am chosing to review React's changelog here since it is a shorter upgrade path than `browserify`'s...

当你升级应用程序所依赖的包的时候，需要这么几个步骤。首先就是查看在`npm-check-updates`想要升级的已经release的版本和当前版本之间相关信息。让我们看看[React.js的发布信息](https://github.com/facebook/react/blob/master/CHANGELOG.md)，我选择查看React的changelog是因为它的更新没有`browserify`那么多。

> When we take a look at the `changelog` we see it broken down into a few categories; "Breaking Changes", "New Features", and "Deprecations". I have to say that the React.js `changelog` is one of the nicer ones out there and with other projects you might not be so lucky. Anyways, we want to read through all the changes taking special care with the "Breaking Changes" and "Deprecations" sections as this is what is likely going to break our app when we upgrade. Do make sure to read the "New Features" section too so we know what cool things we can add to our app as well!

我们可以看到`changelog`中分为了几个类别，"Breaking Changes"、"New Features"以及"Deprecations"。不得不说React.js的`changelog`做得非常好，如果是其它项目可能就没有这么幸运了。Anyways，我们通读一遍所有的改变，特别注意一下"Breaking Changes"和"Deprecations"这两部分，因为这最可能在升级的时候搞崩我们的App。再次确认"New Features"部分，以便于我们可以给App添加一些酷的新功能。

> *I'll wait...*

等等……

> Now that we have read React's `changelog` we can comfortably move forward with upgrading. At this point in time, if there was any breaking changes that would affect our app, we'd want to take note to make sure we revisit that section of code after the upgrade. 

既然我们已经读了React的`changelog`，我们就可以舒舒服服得升级了。在这个时候，如果有任何影响我们的App的改变，我们一定要特别小心并且在升级之后，重新看一下`changelog`的代码部分。

> **Note**: This is where having good tests would really come in handy. You should have a level of test coverage that makes you comfortable with doing upgrades like this. Any breaking change to your app should be caught by a test and not by your walk-through of the site in a browser. Unfortunately, we do not have any tests yet for this application.

**注意：**这时候写好测试的好处就出来了，你应该保持测试覆盖率以便于今后舒舒服服得进行版本升级。任何可能搞崩App的改变都可以被测试捕获到，而不需要在浏览器里面人肉搜索了。不幸的是，我们并没有为这个应用程序写过测试。

> Upgrading a NPM package is really simple. First you want to update your `package.json` file to represent the version of the package you want to upgrade:

升级NPM包非常简单，首先更新一下`package.json`文件，改成你想要升级的那个版本：
    
    ...
    "react": "^0.13.3",
    ...

> Then you need to run `npm upgrade` which will upgrade all the packages to the latest version found in `package.json`. The output looks like this:

然后运行`npm upgrade`就可以把所有的库都升级到`package.json`中的最新版本了。
    
    $ npm upgrade
    react@0.13.3 node_modules/react
    └── envify@3.4.0 (through@2.3.8, jstransform@10.1.0)
    

> That's it. We have successfully upgraded a NPM module. Now let's see if our application is still working!

That's it. 我们已经成功升级了NPM模块，现在看看我们的程序是否依然可以工作！

## Conclusion | 结论

> Lucky for us our app worked just fine after the upgrade. I was not too surprised since we are still at a very basic level with our application. If the upgrade was not as successful, we'd have to go through and make some changes to make sure our app is back in working order. This is where reading the `changelog` really comes in handy.

非常幸运的是在升级以后，我们的App还是工作得非常好。我并不感到惊讶的原因是因为我们的应用程序还处于一个非常基础的阶段。如果升级不像这么成功，我们就不得不去遍历代码，并且做出一些改变来让我们的App重新工作。这就是阅读`changelog`的有用之处。
