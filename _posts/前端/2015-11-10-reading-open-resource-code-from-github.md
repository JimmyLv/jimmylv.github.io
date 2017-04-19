---
layout: post
title: GitHub开源项目源码十阅(1)：getAwesomeness
categories: [前端]
tags: [开源项目, JavaScript, Express, GitHub]
published: True

---

# GitHub开源项目：getAwesomeness

![](//o7mw3gkkh.qnssl.com//getAwesome.png)

repo url: <https://github.com/panzhangwang/getawesomeness/>

time: 2 days

## 项目乐趣

近来GitHub上面的Awesome系列真的是灰常之多呀，各种关于语言、框架、工具等一切都可以分门别类地收集到`Awesome XX`里面，而更有甚者的就是这个项目，做`Awesome XX`系列的`Awesome`超级大集合。暂且不讨论这种超级集合的优劣，但至少提供了一种快速获取相关资源的方式，而与此同时可能带来的知识重复性和饱和度，以及集合过大从而导致的内容稂莠不齐等问题，也是我们值得思考的一方面，其实就是人性的一种原始欲望，在这个资源如此充裕并且唾手可得的时代依旧满足了现代人的收藏癖。

而自己当然也是有类似的需求的，这样一种更高一层的思考，以及展示的方式也让知识的流通更加方便和美观，这跟自己关于「知识流通起来才具有价值」的价值观也有契合。与此同时，在更高层次或框架上来思考的话，也是满足于自我知识展示平台应用的一种方式。

其他想法：

- 挖掘其所有已具备功能和可改进之处
- 直接套用其UI和交互功能，思考其他的内容用于展示
- 结合GitHub的issue博客，展现大而全的展示
- 博客系统的进一步想法扩充
- no-backend数据的一种例子
- 开始对博客系统进行计划啦，Trello
- 在Trello里面建立项目并且计划UI
- 全平台应用的blog展示
- 自定义任意数据源
- 如何实现简单搜索功能
- 导航栏展示已访问链接
- Markdown源文件直接渲染

## 马上开始

从`server.js`文件开始，结合网站功能以及`README.md`中所提示的用法，通过已实现的功能去找到代码中相对应的部分，关键在于找到程序的入口，然后再顺藤摸瓜找到具体实现的方法。

差不多就把整个项目架构以及实现弄清楚了，可以学到的东西也很多：

### 0x01. Express.js

- express配置app的过程
    + `var app = express();`
    + `routes` & `views`
    + `app.listen(3000)`
- nodejs的模块：`module.exports`与`require('./config/express')`
- `app.use([path,] function [, function...])` API
    + Mounts the middleware function(s) at the path. If path is not specified, it defaults to “/”.
    + `app.use(express.static(config.root + '/public'));`
    + `app.use(locale(supported));` & `var supported = ["en", "zh-CN"];`
- `app.engine('html', swig.renderFile);`
- `app.set('views', config.root + '/app/views');`

### 0x02. Routes路由

```js
  app.use(function (req, res, next) {
    res.status(404).render('404', {
      url: req.originalUrl,
      error: 'Not found'
    });
  });
```

![](//o7mw3gkkh.qnssl.com//swig_404.png)

当然可以再次分层，把具体的`res.render()`函数放到不同的地方。

```js
var sites = require('../app/sites');
app.get('/', sites.index);
app.get('/get/:awe', sites.get);
```

### 0x03. Sites视图

    exports.index = function (req, res){
      res.render('index', {
        title: 'Home',
        groups: db('groups').where({})
      });
    };

所对应的view文件，`index.html`

    <div class="row">
        {% for g in groups %}
        <div class="col-md-3">
            <div class="panel panel-primary">
                <div class="panel-heading">{{ __(g.key) }}</div>
                <div class="list-group">
                    {% for it in g.items %}
                    <h4><a class="list-group-item" href="{{ '/get/' + it }}">{{ label(it) }}</a></h4>
                    {% endfor %}
                </div>
            </div>
        </div>
        {% endfor %}
    </div>

### 0x04. Cookies

使用`req.cookies`

    exports.index = function (req, res){
        var aweCookie = req.cookies.aweCookie;
        var recents = aweCookie? JSON.parse(aweCookie) : [];
      res.render('index', {
        title: 'Home',
        recents: recents,
        groups: db('groups').where({})
      });
    };

而如何processCookie呢？

    if (!aweCookie) {
        var arr = [];
        arr.push(req.params.awe);
        res.cookie('aweCookie', JSON.stringify(arr), { maxAge: maxAge, httpOnly: true });
    }

### 0x05. lowdb库

<https://github.com/typicode/lowdb>

> Need a quick way to get a local database?

    var low = require('lowdb');
    var db = low('db.json');
    var found = db('defs').find({ key: awe });

    groups: db('groups').where({})

当然它还有其他非常易用好用的方法，only 8 methods and properties.

    db('posts').push({ title: 'lowdb is awesome'})

Database is automatically saved to db.json

    {
      "posts": [
        { "title": "lowdb is awesome" }
      ]
    }

### 0x06. request库

<https://github.com/request/request>

    var mkFile = found.file ? found.file : "README.md";
    var url = 'https://raw.githubusercontent.com' + found.repo + '/master/' + mkFile;

    request(url, function (error, response, body) {
        if (!error && response.statusCode == 200) {
            cache.put(awe, body );
        }
    }

### 0x07. Swig模板引擎

使用[swig模板引擎](http://paularmstrong.github.io/swig/docs/)，和Express.js搭配良好，可以传入函数这点很酷。

比如：

Use getAwesomeness() to retrieve all amazing awesomeness (README.md is markdown file) from Github.

    <article class="markdown-body">
        {{ md(article) }}
    </article>

    res.locals.md = function (text) {
      marked.setOptions({
        renderer: new marked.Renderer(),
        gfm: true,
        tables: true,
        breaks: false,
        pedantic: false,
        sanitize: false,
        smartLists: true,
        smartypants: false
      });
      return marked(text);
    }

### 0x08. Search功能

    $.get('/json/list', function(data){
        $("#typeahead").typeahead({ source:data });
    },'json');

    var $input = $('#typeahead');
    $input.change(function() {
        var current = $input.typeahead("getActive");
        if (current) {
            if (current.name == $input.val()) {
                window.location.href = '/get/' + current.key;
            }
        }
    });

### 0x09. toTop功能

    <a href="#top" id="toTop" class="btn btn-lg btn-primary" title="Back to top">&uarr;</a>

    $("#toTop").scrollToTop();

### 0x0a. TOC 功能

    <div class="col-md-3">
        <div id="sidebar">
            <div class="toc"></div>
        </div>
    </div>

    $('.toc').toc({
        'selectors': 'h1,h2,h3,h4',
        'container': 'article'
    });