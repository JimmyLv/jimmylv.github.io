---
layout: session
title: 思沃讲堂：Spring MVC 实战
categories: [演讲]
tags: [Spring, MVC, Web]
speaker: Jimmy Lv
transition: move
files: /assets/slide.js,/assets/slide.css,/js/zoom.js
highlightStyle: kimbie.light
theme: color
published: True
---

[slide]

# Th Wo - Bookshelf
<small>by Jimmy Lv</small>

[slide]

## MVC Workshop

[slide]

### Step 0:

GET: hello {name}! 

via [Spring Web MVC DispatcherServlet](http://docs.spring.io/spring/docs/current/spring-framework-reference/html/mvc.html#mvc-servlet).

[slide]

### Step 1:

// given

GET: show all books in index page.

// when

// then

implement `fetch book details` functionality.

[slide]

### Step 2:

// given

a ready-to-wear `form` for book information.

// when

// then

implement `create new book` functionality.

[slide]

### Step 3:

Edit / Delete / ...

[slide]

## Extendibility

- What's Spring IoC & DI?
- Service interface => different implementation
- Data Repository => using different database
- Split front-end & back-end => return data with JSON format

[slide]

## 作业

- 先把书架CURD的功能，使用**后端MVC**的形式完善。
    + 当然你可以改用其他模板语言，比如Jade什么的，这儿用的是Thymeleadf。
- 然后再改用**JSON格式**返回，而不再需要后端模板。
    + 为了前后端分离，😂 以下形式就Okay：

![](//o7mw3gkkh.qnssl.com//json-format.jpg)

