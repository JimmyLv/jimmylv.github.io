---
layout: post
title: 一个知识清单：如何学习Python爬虫
categories: [编程]
tags: [Python, 爬虫]
published: True

---

> import this.

- 前言
    + [能利用爬虫技术做到哪些很酷很有趣很有用的事情？ - 知乎](http://www.zhihu.com/question/27621722)
- 学习Python，基本语法，常用数据处理库
    + [你是如何自学 Python 的？ - 知乎](http://www.zhihu.com/question/20702054)
    + [Python 2.7教程 - 廖雪峰](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000)，学基础看这个完全就够了。
    + 或者看他讲的视频，[Python入门 - 廖雪峰](http://www.imooc.com/learn/177)。
- 了解网页的基本结构、组成 HTML+CSS+JS三剑客
    + 类比于一个人，HTML就是骨架、CSS是衣服、JS是这个人的一系列动作，比如打自己一巴掌。
    + [HTML 教程](http://www.w3school.com.cn/html/index.asp)，[CSS 教程](http://www.w3school.com.cn/css/index.asp)，[JavaScript 教程](http://www.w3school.com.cn/js/index.asp)
- 了解爬虫工作原理，涉及文件下载，数据解析，以及数据存储
    + [如何入门 Python 爬虫？ - 知乎](http://www.zhihu.com/question/20899988)
    + 网页下载，[HTTP协议详解](http://www.cnblogs.com/TankXiao/archive/2012/02/13/2342672.html)，一个非常好用的Python库，[Requests for Humans ](http://cn.python-requests.org/zh_CN/latest/)
    + 数据解析，[深入浅出之正则表达式（一）](http://dragon.cnblogs.com/archive/2006/05/08/394078.html)，[regex可视化工具](http://regexper.com/)
    + 超越正则表达式，[XPath](http://www.jikexueyuan.com/course/902.html)是什么鬼。
    + 数据存储，Python自带轻量级数据库[SQLite](http://www.cnblogs.com/vamei/p/3794388.html)。
- 了解各种坑，模拟登陆，JS加载、点击动作，请求次数限制
    + [网络爬虫定向抓取漫谈](http://www.searchtb.com/2011/01/an-introduction-to-crawler.html)
    + [详解抓取网站，模拟登陆，抓取动态网页的原理和实现（Python，C#等）](http://www.crifan.com/files/doc/docbook/web_scrape_emulate_login/release/html/web_scrape_emulate_login.html)
    + [专栏：Python爬虫入门教程](http://blog.csdn.net/column/details/why-bug.html)
    + [爬虫视频课程 - 极客学院](http://search.jikexueyuan.com/course/?q=%E7%88%AC%E8%99%AB)
- 超级武器，上手Scrapy框架
    + 非常好用的大而全功能完备的[Scrapy框架](http://doc.scrapy.org/en/latest/index.html)
    + 这里有之前版本的中文翻译，[Scrapy 0.25 文档](http://scrapy-chs.readthedocs.org/zh_CN/latest/)。
- 一栈式解决方案，直接上浏览器webkit解决JS动态加载问题
    + 网页动态刷新，什么是[AJAX](http://www.w3school.com.cn/ajax/index.asp)？
    + 两个无图形化的浏览器内核爬虫，[spynner](https://github.com/makinacorpus/spynner)，[Ghost.py](https://github.com/jeanphix/Ghost.py)
- 究极武器，直接使用第三方服务：PQL，Kimono
    + 能够直接把网页变成API的[Kimono](https://www.kimonolabs.com/apidocs)。
    + 像SQL查询语句一样调用网站服务的[YQL](https://developer.yahoo.com/yql/)，雅虎出品。
