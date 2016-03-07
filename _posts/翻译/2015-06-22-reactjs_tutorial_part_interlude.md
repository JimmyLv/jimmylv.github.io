---
layout: post
title: 【译】React.js教程 番外篇（一）：使用Bower包管理工具
categories: [翻译]
tags: [React, Bower]
published: True

---

技术系列笔记均已迁移至GitBook，更多`React`的内容请到：[http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html](http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html)

# React.js Tutorial Part (Interlude)

原文地址：[http://www.joshfinnie.com/blog/reactjs-tutorial-part-interlude/](http://www.joshfinnie.com/blog/reactjs-tutorial-part-interlude/)

> Welcome to part (Interlude) of my React.js/Express.js app tutorial. This is going to be an extension of [part 2](http://www.joshfinnie.com/blog/reactjs-tutorial-part-2/), where we go into a bit more detail of how to use Gulp along with Bower.io to make our application a better, well-rounded system. We will not be going into too much React.js this tutorial, so I didn't want to call this "part 3". If you haven't already, please start the tutorial at [Part 1](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/)

欢迎来到React.js/Express.js应用教程的番外篇，这将是[第二部分](http://www.joshfinnie.com/blog/reactjs-tutorial-part-2/)的扩展，我们将进一步了解如何配配合使用Gulp和Bower.io来使我们的应用更好更完善。这部分内容不会太多涉及React.js，所以我就不想称之为“第三部分”了。如果你还没准备好，从[第一部分](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/)开始吧。

## Bower

> For much of the UI, we are going to use a package manager called [Bower](http://bower.io/). Bower calls itself a package manager for the web, and it actually does a great job at doing just that. We are going to use Bower to install and keep track of many of the third-party libraries we are going to use for our job board.

使用包管理工具[Bower](http://bower.io/)可以让我们拿到更多的UI库。Bower自称为互联网的包管理工具，实际上它做得非常好。我们将使用Bower来安装和追踪我们将要使用到项目中的第三方库。

> To install Bower, we simply have to install it from NPM using the following command:

使用NPM来安装Bower：

```bash
$ npm install --save bower
```

> This automatically adds it to our `package.json` file which we all should be familiar with now. If you are comfortable with Bower, it is recommended to install the package globally, which I have done. Your mileage may vary.

这将自动添加依赖到`package.json`。如果你对Bower感觉良好，可以像我一样直接安装到全局。当然你的情况可能会有所不同。

> The one thing I do not enjoy about the default Bower installation is where the libraries are stored by default: `.bower-components/`. Luckily, it is not that hard to change, so let's change where we install our third-party libraries. To do this, create a `.bowerrc` file which looks like the following:

还有一件我不喜欢的事情是，Bower会将第三方库默认安装到`.bower-components/`目录。幸运的是，我们可以很容易修改这个位置，创建一个`.bowerrc`文件：

```json
{
  "directory": "public/libraries/"
}
```

> This will change the default bower install folder to be `public/libraries/` which will allow us to easily access it later on. Once we do this, let's create the `bower.json` file, which will allow us an easy way to save our Bower packages very much like `package.json`. Simply run the following commands to prompt you to create your `bower.json` file:

这就能将Bower的默认安装路径设置为`public/libraries/`，以便于之后的调用。一旦我们完成些之后，新建`bower.json`文件，就像`package.json`一样能够轻易保存我们的Bower包依赖。运行以下命令可以直接创建：

```bash
$ bower init
```

> After completing the prompts your `bower.json` file should look something like this:

将`bower.json`设置如下：

    {
      "name": "jobs.nodedc.com",
      "version": "0.1.0",
      "homepage": "https://github.com/joshfinnie/jobs.nodedc.com",
      "authors": [
        "Josh Finnie "
      ],
      "description": "A job board for the NodeDC meetup group.",
      "main": "./bin/www",
      "license": "MIT",
      "private": true,
      "ignore": [
        "**/.*",
        "node_modules",
        "bower_components",
        "public/lib/",
        "test",
        "tests"
      ]
    }


## Twitter Bootstrap and SASS Setup | 安装 Twitter Bootstrap 和 SASS

> The next bit of setup we are going to do for our web app is to install [Twitter Bootstrap](http://getbootstrap.com/) using its official [SASS](http://sass-lang.com/) bower package. You can see what packages are available through bower using its search function: `bower search` Searching for `bootstrap` brings up many, many packages, but also shows us the package we want. Here is an excerpt from the search:

下一步就是为我们的web应用安装[Twitter Bootstrap](http://getbootstrap.com/)，并且选用官方的[SASS](http://sass-lang.com/)版本的Bower包。可以使用`bower search`来搜索哪些包是可用的，搜索`bootstrap`可以得到很多包，当然包括我们想要的。这是一些搜索的片段：

    $ bower search bootstrap
    Search results:
        bootstrap git://github.com/twbs/bootstrap.git
        angular-bootstrap git://github.com/angular-ui/bootstrap-bower.git
        bootstrap-sass-official git://github.com/twbs/bootstrap-sass.git
        sass-bootstrap git://github.com/jlong/sass-bootstrap.git
        bootstrap-datepicker git://github.com/eternicode/bootstrap-datepicker.git
        bootstrap-select git://github.com/silviomoreto/bootstrap-select.git

> From here we want to install the `bootstrap-sass-official` package by running the following command:

找到之后可以使用命令安装`bootstrap-sass-official`：

```bash
$ bower install bootstrap-sass-official --save
```

> Now with the `bootstrap-sass-official` library installed, we can update our `style.scss` file to import the Bootstrap packages we want to use. For now, let's just import the entire bootstrap library. To do this, let's update our `style.scss` file to read as the following:

现在`bootstrap-sass-official`库已经安装好，我们可以将我们想要使用的Bootstrap更新到`style.scss`。到现在为止，我们直接导入整个bootstrap库，让我们更新`style.scss`如下所示：

```css
@import "../../libraries/bootstrap-sass-official/assets/stylesheets/bootstrap";

body {
  padding: 50px;
  font: 14px "Lucida Grande", Helvetica, Arial, sans-serif;
}

a {
  color: #00B7FF;
}
```

> Next, let's set up our Gulp file to automatically build our SASS and add it to our application. To do this, we need to install a few more applications:

接下来，设置Gulp文件来自动编辑我们的SASS文件并添加到我们的应用。我们需要安装更多应用：

```bash
$ npm install gulp-sass --save-dev
```

> This will install the `gulp-sass` so we can have Gulp build our SASS file. We now need to to update our Gulp file with the following function to build our SASS:

这将安装`gulp-sass`以便于编译SASS文件，我们现在需要更新Gulp文件来创建相应的函数：

```js
var sass = require('gulp-sass');

... // Our existing jsx task is here

gulp.task('sass', function() {
    gulp.src('public/stylesheets/scss/*.scss')
        .pipe(sass())
        .pipe(gulp.dest('public/stylesheets/css'));
})

gulp.task('watch', function() {
    ...
    gulp.watch("public/stylesheets/scss/*.scss", ["sass"]);
})

gulp.task('default', ['js', 'sass', 'watch']);
```

> With the gulp task above, we now have our SASS automatically compiled whenever we change it. Lastly we need to add the compiled CSS to our Jade template. We can do this by simply adding the following line to the head of `layout.jade`:

有了以上的Gulp任务，无论什么时候我们修改SASS文件，Gulp都会自动编译。最后让我们把已经编译好的CSS添加Jade模板中。直接添加到头文件：

```jade
link(rel='stylesheet', href='/stylesheets/css/style.css')
```

## Concatenating the Javascripts | 连接 JavaScript 脚本

> With the introduction of Twitter Bootstrap, we have also introduced two new javascript libraries to our code base: the Twitter Bootstrap javascript, and jQuery. Since we are already transforming our JSX code into javascript, let's take this time to concatenate all our javascripts together into a singular `app.js`. To do this, we just need to have a way to tell our JSX code that there are more libraries to import. Luckily since we are already using browserify, this is as simple as adding the following lines to our `app.jsx` file:

在介绍Twitter Bootstrap之后，我们还需要加入新的JavaScript库：jQuery。由于我们已经可以将JSX代码编译成JavaScript，让我们花点时间把JavaScript连接到单个`app.js`中。只需要告诉JSX导入相应的库即可，由于我们已经使用了browserify，所以很简单就可以加入到`app.jsx`文件：

```js
var $ = jQuery = require('../../libraries/jquery/dist/jquery');
var bootstrap = require('../../libraries/bootstrap-sass-official/assets/javascripts/bootstrap');
```

> Doing this points both `jQuery ($)` and `bootstrap` to the appropriate file which were installed via Bower. When we re-run our browserify gulp task, these two libraries get pulled in! Simple as that.

至此，`jQuery ($)`和`bootstrap`都已经通过Bower正确安装了，当我们重新运行browserify的Gulp任务，这两个库就已经被加入了。

## Bootstrapping our App | 初始化 App

> Now that we have all the plumbing working, let's add some niceties to our application. We can add the [starter Bootstrap template](http://getbootstrap.com/examples/starter-template/) to give it a bit of style. All we need to do is update our `layout.jade` file to look like this:

现在我们做好准备工作，让我们为应用程序添加一些内容。我们可以添加[starter Bootstrap template](http://getbootstrap.com/examples/starter-template/)模板来加上一些样式。只需要修改`layout.jade`文件：

```jade
doctype html(lang='en')
head
  meta(charset='utf-8')
  meta(http-equiv='X-UA-Compatible', content='IE=edge')
  meta(name='viewport', content='width=device-width, initial-scale=1')
  meta(name='description', content='')
  meta(name='author', content='')
  link(rel='icon', href='../../favicon.ico')
  title= title
  link(rel='stylesheet', href='/stylesheets/css/style.css')
  //if lt IE 9
    script(src='https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js')
    script(src='https://oss.maxcdn.com/respond/1.4.2/respond.min.js')
body
  nav.navbar.navbar-inverse.navbar-fixed-top
    .container
      .navbar-header
        button.navbar-toggle.collapsed(type='button', data-toggle='collapse', data-target='#navbar', aria-expanded='false', aria-controls='navbar')
          span.sr-only Toggle navigation
          span.icon-bar
          span.icon-bar
          span.icon-bar
        a.navbar-brand(href='#') jobs.nodedc.com
      #navbar.collapse.navbar-collapse
        ul.nav.navbar-nav
          li.active
            a(href='#') Home
          li
            a(href='#about') About
          li
            a(href='#contact') Contact
  .container
    .starter-template
      p
        block content
  script(src='/javascripts/build/app.js')
```

> This then makes our web application this:

完成之后的效果：

![](http://www.joshfinnie.com/assets/images/blog/bootstrapped-hello-react.png)

