---
layout: session
title: Web 前端开发模式演变
categories: [演讲]
tags: [Rethink, JavaScript, Web]
speaker: Jimmy Lv
transition: move
files: /assets/slide.js,/assets/slide.css,/js/zoom.js
highlightStyle: kimbie.light
theme: green
published: True
---

30 min = 15 min * 2

[slide]
# 「Done is better than perfect.」

[slide]
# Web 前端开发模式演变
<small>by Jimmy Lv</small>

[slide]

## ？

[slide]

## 被误解的前端

![](//o7mw3gkkh.qnssl.com//css.jpeg)

[slide]

## 热门的前端

![](//o7mw3gkkh.qnssl.com//money.png)

[slide]

## 两次巨大革命

- PC和因特网革命
    + 35年, -> 21亿台设备 {:&.moveIn}
- 移动互联网革命
    + 5年, -> 60亿台设备 {:&.moveIn}

[slide]

## 语言排行榜

![](//o7mw3gkkh.qnssl.com//hot_language.jpg)

[slide]


[slide]

## JavaScript与Netscape

- Sun, Java 
- Brendan Eich, Scheme 
- Mircosoft, JScript
- ECMAScript

![Netscape](http://image.beekka.com/blog/201106/bg2011062401.jpg)

[slide]

## Web 1.0时代

- 服务端生成，浏览器负责展现 {:&.moveIn}
    - Java + JSP | ASP
    - Tomcat、Apache
- 缺点：
    + JSP代码 越来越多，灰色地带 可维护性差

![Web 1.0](https://camo.githubusercontent.com/90850e93b917cd3c958dff1c7d0197f819167343/687474703a2f2f696d672e68622e616963646e2e636f6d2f63333639616163633864613338616638653432326664323935313438633537643162353831376666666335362d4f636250646c5f6677363538)

[slide]

## 后端MVC时代

-  Structs、Spring MVC {:&.moveIn}
-  View层变得简单：模板引擎（ Velocity、Freemaker）
-  缺点：
    *  纠缠不清的Controller
    *  前端开发重度绑定后端环境

![后端MVC](https://camo.githubusercontent.com/b9e16b0b3ff3361a481badaca7d408e8fa6b404f/687474703a2f2f696d672e68622e616963646e2e636f6d2f3961366266353237646162626462396237393563353862306237616636633761313864653963653331316136312d3975697578545f6677363538)

[slide]

## Web 2.0时代：AJAX

- Gmail横空出世，Web Application 
- Ajax，XMLHttpRequest接口
- jQuery，JS操作网页DOM结构变得非常容易

![AJAX](https://camo.githubusercontent.com/d0098546c9fa01b443c16ff1953c90aa9056955b/687474703a2f2f696d672e68622e616963646e2e636f6d2f3932393766646337336438336632373764343439633932313933613361663432386464633064343431316366392d6e31445936465f6677363538)

[slide]

## 单页面应用

- `#` 无需刷新页面 {:&.moveIn}
    + 前端路由，展现
    + 后端路由，数据
- 挑战：
    + 前后端接口的约定，前端的数据绑定
    + JavaScript 代码越来越多

![SPA](https://camo.githubusercontent.com/f064bc7a5b06ea9a39cf039a5dec0ca6675141ff/687474703a2f2f696d672e68622e616963646e2e636f6d2f3135383839323134336263363430333364323264643865643765373533366537316530373063346131336335372d6850673150635f6677363538)

[slide]

## MV** 时代

- Knockout、Backbone、Angular 1.x {:&.moveIn}
- 前后端分离，职责清晰
- 缺点：
    - 代码不能复用（数据校验）
    - 不利于SEO，搜索引擎爬虫不会执行JS
    - 性能并非最佳，移动端网络是个渣

![](https://camo.githubusercontent.com/2ab0e0e247dfae7b74760b7d57056a680204874d/687474703a2f2f696d672e68622e616963646e2e636f6d2f3536663463656530653663376166363165323464626633316534626531376631343264353930326331313039612d42637852696d5f6677363538)

[slide]

## 全栈时代：Node.js

- 异步IO：JS单线程 + Chrome的V8编译器 {:&.moveIn}
- Front-end：只处理浏览器层的展现逻辑 | 路由、模板、数据获取
- Node Web Server：业务逻辑，SEO时使用服务端渲染
- Universal JavaScript：前后复用部分逻辑代码
- 回归后端，JS->Node / Java->JSP

![](http://assets.toptal.io/uploads/blog/image/25/toptal-blog-image-1374849974023.png)

[slide]

## 未来：前端组件化

如何将来自于服务器端或者用户输入的动态数据高效的反映到复杂的用户界面上。

- 下一代的HTML标准：Web Component
- React、Angular 2.0、Polymer
- 转译语言：TypeScript、CoffeeScript、ES6

![](https://github.com/fouber/blog/raw/master/201508/assets/modular-component.png)

[slide]

## 跨平台时代：界面编程

- Webkit：Electron {:&.moveIn}
- Hybrid App：WebView
- React Native

[slide]

## Atwood's Law

Any application that can be written in JavaScript, 

will eventually be written in JavaScript.