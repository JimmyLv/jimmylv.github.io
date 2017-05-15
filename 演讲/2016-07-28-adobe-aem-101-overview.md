---
layout: session
title: Adobe AEM 101 Overview
categories: [演讲]
tags: [AEM, JavaScript, Java, CMS, Marketing, Adobe, REST]
speaker: Jimmy Lv
transition: move
files: /assets/slide.js,/assets/slide.css,/js/zoom.js
highlightStyle: kimbie.light
theme: green
published: True
---

30 min = 15 min * 2

[slide]
# AEM 101 Overview
<small>by <strong>Jimmy Lv</strong></small>

[slide]

# Agenda

- Part 1: AEM Overview
    +  AEM 在 Adobe 中的地位
    +  AEM 是什么？业务价值 👏
    +  AEM 的历史，顺带解释 Day 公司的贡献
- Part 2: AEM Functionality Preview
    -  从使用端来讲，拖拖拽拽
    -  从角色分工来讲
- Part 3: AEM 背后实现原理的相关概念
    -  一堆名词，根据官方文档顺序讲就是了
    -  组件化改变 Web（延伸到现在的 React） via 徐飞讲 [十年来感受的前端技术变化 · Issue #28 · xufei/blog](https://github.com/xufei/blog/issues/28)
- One more things...
    - 自己的想法，学习总结
    - Learning RoadMap

[slide]

# Part 1: AEM Overview

<br/>

## What? & Why? & How? & Question?

[slide] 

# How's Your Customer Experience?

[![](//o7mw3gkkh.qnssl.com//images/2016/1469770434690.png)](https://www.youtube.com/watch?v=HGb6NQMeZ-c)

[slide]

# Adobe Marketing Cloud

[![](//o7mw3gkkh.qnssl.com//images/2016/1469750403141.png)](http://www.adobe.com/)

<br/>

> We’re a Leader. And here’s why.

[note]
Don't just create experiences. Make it your business.

- We know what matters most to marketers. => AEM

To be an experience business, it takes a leader.

- We’re a Leader. And here’s why.
 
[/note]

[slide] 

# AEM in Adobe Marketing Cloud

![](//o7mw3gkkh.qnssl.com//images/2016/1469675204327.png)

[slide]

# Adobe Experience Manager

[![](//o7mw3gkkh.qnssl.com//images/2016/1469750678577.png)](http://www.adobe.com/marketing-cloud/enterprise-content-management.html#x)

> AEM is a comprehensive **content management** solution for building websites, mobile apps, and forms. And it makes it easy to manage your marketing content and assets.

[note]
涵盖网站和相关服务的创建、管理、部署，一揽子方法

集成软件套装，包含 infrastructure 和 application 层面的工具和服务，前者是后者的基础

[/note]

[slide]

# Product history of Adobe CQ

```
Date | Product      
---- | ----------
2002 | Day CQ 3.5                           
2005 | Day CQ 4.0                         
2006 | Day CQ 4.1                       
2008 | Day CQ 4.2                        
2008 | Day CQ 5.0                        
2009 | Day CQ 5.2                        
2010 | Day CQ 5.3                        
2011 | Adobe CQ 5.4                      
2012 | Adobe CQ 5.5                      
2013 | Adobe Experience Manager 5.6
2014 | Adobe Experience Manager 6.0
2015 | Adobe Experience Manager 6.1
2016 | Adobe Experience Manager 6.2
```

[note]
关键是 Day Software
[/note]

[slide]

# Google Trending

[![](//o7mw3gkkh.qnssl.com//images/2016/1469768209884.png)
](https://www.google.com/trends/explore#q=%22adobe%20cq%22%2C%20adobe%20cq5%2C%20adobe%20aem%2C%20Adobe%20Experience%20Manager&cmpt=q&tz=Etc%2FGMT-8)

[note]
解释完全曲线（之和）
[/note]

[slide]

# 知道真相的我眼泪掉下来

### 前身：[CQ5 - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/CQ5)

<br/> 

> CQ5 or Communique5 (renamed as **Adobe Experience Manager**) is a **Web Content Management System** (WCMS) designed to enable users (mainly marketers and IT professionals) to **create, edit, manage and optimize** websites **across different digital channels** such as web, mobile, social and more.

[slide]

# Day Software

- 收购！Adobe acquires Day Software, a market leader in next-generation web content management (WCM), was an enterprise content management software company. {:&.fadeIn}
- Roy T. Fielding 是 Day Software's chief scientist，现在是 [Senior Principal Scientist at Adobe Systems](https://www.linkedin.com/in/royfielding)，在 Adobe 继续担任首席科学家，所以才有了 [REST in AEM](http://www.slideshare.net/royfielding/rest-in-aem) 这个演讲。
- Day is engaged in the **Java Content Repository** API for Java standardization process and contributes to open source software projects such as **Apache Jackrabbit** and **Apache Sling**.

[note]
Apache HTTP服务器的核心开发者Roy Fielding,他还是Apache软件基金会的合作创始人
[/note]

[slide]

# Part 2: AEM Functionality Preview

[slide]

# 能做啥？

![](//o7mw3gkkh.qnssl.com//images/2016/1469776743596.png)

[slide]

# 功能演示

[![](//o7mw3gkkh.qnssl.com//images/2016/1468060034522.png)](http://localhost:4505/projects.html/content/projects)

[slide]

# 角色分工 之 Content Editor

![](//o7mw3gkkh.qnssl.com//images/2016/1469772633873.png)

[slide]

# 页面编辑 （ 拖拖拽拽 ）

[note]
编辑也有几种模式，视角不同。
[/note]

![](//o7mw3gkkh.qnssl.com//images/2016/1469716451473.png)

[slide]

#  Touch UI Customizations

[![](//o7mw3gkkh.qnssl.com//images/2016/1469772544746.png)](http://blogs.adobe.com/experiencedelivers/experience-management/touch-ui-customizations-part-1/)

[slide]

# 组件 构成 页面 

![](//o7mw3gkkh.qnssl.com//images/2016/1469716589609.png)

[note]
开发，完全组件化看起来好爽！（两者本质都是 HTML）
[/note]

[slide]

# 角色分工 之 PIM Editor

![](//o7mw3gkkh.qnssl.com//images/2016/1469772945441.png)

[note]
电子商务，改改价格什么的
[/note]

[slide]

# Developing

![](//o7mw3gkkh.qnssl.com//images/2016/1469716527090.png)

[slide]

# 角色分工 之 Componets Developer

![](//o7mw3gkkh.qnssl.com//images/2016/1469716341707.png)

[slide]

# Part 3: Magic Behind AEM

[slide]

# Rio Olympics: 'Welcome to hell' 

![](//o7mw3gkkh.qnssl.com//images/2016/1469772248011.png)

[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469776281516.png)

<br/> 

> An author in WCM **generates** the material which will, at some point, be published to your website.
> When ready, the content is **published** to the publish environment. 

[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469776380542.png)

[slide]

# 技术架构

![](//o7mw3gkkh.qnssl.com//images/2016/1469749733269.png)

[slide]

# Architechture

![](//o7mw3gkkh.qnssl.com//images/2016/1469614691277.png)

[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469613962134.png)

1.  **Web Application Server**: 可以单独集成 Jetty web server，也可以用于第三方
2.  **Web Application Framework**: 简化 RESTful 面向对象的 Web 应用，即内容优先
4.  **Content Repository**: AEM 引入了 JCR，用于处理非结构化或半结构化的数据；不仅包含内容，还有相关代码、模板等所有内部数据

[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469776708150.png)

<br/>

> Adobe Experience Manager is a web-based client-server system for building, managing and deploying commercial websites and related services. It combines a number of infrastructure-level and application-level functions into a single integrated package.

[slide]

# OSGi (Open Service Gateway Initiative)

[OSGi - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/OSGi)：一个基于Java语言的服务（业务）规范——OSGi服务平台（Service Platform）。

目前该平台逐渐成为一个为室内、交通工具、移动电话和其他环境下的所有类型的网络设备的应用程序和服务进行传递和远程管理的开放式服务平台。

![](//o7mw3gkkh.qnssl.com//images/2016/1469539342406.png)

[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469776814871.png)

> OSGi 的作用在于 Runtime，之所以为动态模块加载，用于管理复杂度，并可以动态扩展其依赖。（类 JavaScript 的 Require.js ？）
> 该规范和核心部分是一个框架，其中定义了**应用程序的生命周期模式和服务注册**。基于这个框架定义了大量的OSGi服务：日志、配置管理、偏好，HTTP（运行servlet）、XML分析、设备访问、软件包管理、许可管理、星级、用户管理、IO连接、连线管理、Jini和UPnP。

[slide]

# 最佳实现，[Apache Felix](http://felix.apache.org/documentation/subprojects/apache-felix-maven-scr-plugin/scr-annotations.html)

注解形式实现 OSGi 标准 bundle，在 AEM 中成为 Module。

* [@Component](http://felix.apache.org/documentation/subprojects/apache-felix-maven-scr-plugin/scr-annotations.html#component)
* [@Activate, @Deactivate, and @Modified](http://felix.apache.org/documentation/subprojects/apache-felix-maven-scr-plugin/scr-annotations.html#activate-deactivate-and-modified)
* [@Service](http://felix.apache.org/documentation/subprojects/apache-felix-maven-scr-plugin/scr-annotations.html#service)
* [@Property](http://felix.apache.org/documentation/subprojects/apache-felix-maven-scr-plugin/scr-annotations.html#property)
* [@Reference](http://felix.apache.org/documentation/subprojects/apache-felix-maven-scr-plugin/scr-annotations.html#reference)

```java
@Property(name = "sample",
    options = {
        @PropertyOption(name = "option1", value = "&option.label.1"),
        @PropertyOption(name = "option2", value = "&option.label.2")
    }
)
```

[slide]

# JCR （[JSR-170](https://jcp.org/en/jsr/detail?id=170) & [JSR-283](https://jcp.org/en/jsr/detail?id=283) Specification）

![](//o7mw3gkkh.qnssl.com//images/2016/1469777086086.png)

[slide]

# **WHAT IS CRX?**

> CRX is short for **C**ontent **R**epository e**X**treme, Day's JCR-compliant repository. CRX allows you to store, manage, and access data using a standardized Java interface.

![](//o7mw3gkkh.qnssl.com//images/2016/1469709908396.png)

[slide]

# Sling 背后靠着 CRX 吃饭

![](//o7mw3gkkh.qnssl.com//images/2016/1469777354485.png)

[slide]

# Sling & REST 

![](//o7mw3gkkh.qnssl.com//images/2016/1469777407980.png)

[slide]

# 做一个照片 CMS 

![](//o7mw3gkkh.qnssl.com//images/2016/1469707517793.png)


[slide]

Sling 背后靠着 CRX 吃饭： 

![](//o7mw3gkkh.qnssl.com//images/2016/1469710299369.png)
[slide]

对比传统 Controller，直接对应 JCR 节点，并且包含相关信息。

![](//o7mw3gkkh.qnssl.com//images/2016/1469710389235.png)
[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469710400998.png)
[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469710435546.png)

[note]
不是直接对应文件目录，但是也完全可以这样。
[/note]

[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469710511007.png)
[slide]

![](//o7mw3gkkh.qnssl.com//images/2016/1469710571268.png)

[slide]

# URI Decomposition

![](//o7mw3gkkh.qnssl.com//images/2016/1469777634817.png)

[slide]

# From URL to Content and Scripts

![](//o7mw3gkkh.qnssl.com//images/2016/1469777621445.png)

[slide]

# One more thing...

