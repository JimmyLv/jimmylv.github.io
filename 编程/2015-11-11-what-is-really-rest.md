---
layout: post
title: 什么才是真正的 RESTful 架构？
categories: [编程]
tags: [REST, API, HTTP]
published: True

---

更多内容请看我最近在写的一本小书：[《Microservice 最佳实践之路》](https://jimmylv.gitbooks.io/learning-microservices/content/)，实为项目上的踩坑手册。

## What?

> Wikipedia: 表征性状态传输（英文：Representational State Transfer，简称REST）是Roy Fielding博士于2000年在他的博士论文中提出来的一种软件架构风格。

Roy Fielding是HTTP协议（1.0版和1.1版）的主要设计者，事实上HTTP 1.1规范正是基于REST架构风格的指导原理来设计的。需要注意的是，REST是一种设计风格而不是标准，如果一个架构符合REST原则，我们就称它为RESTful架构。

## Why？

![](//o7mw3gkkh.qnssl.com//images/2016/1471531874674.png)

在「远古时代」前端后端是融合在一起的，比如之前的PHP，JSP，ASP等等（参考我之前做过的一场演讲：[Web前端开发模式演变](http://blog.jimmylv.info/2015-11-02-history-about-web-development-evolution/)）。近年来随着移动互联网的飞速发展，各种类型的Client端层出不穷，就需要通过一套统一的接口分别为Web，iOS和Android乃至桌面端提供服务。另外对于广大平台来说，比如Facebook platform，微博开放平台，微信公共平台等，它们不需要有显式的前端，只需要一套提供服务的接口，于是RESTful更是它们最好的选择。

而要理解RESTful架构，最好的方法就是去理解**Representational State Transfer**这个词组，直译过来就是「表现层状态转化」，其实它省略了主语。「表现层」其实指的是「资源」的「表现层」，所以通俗来讲就是：资源在网络中以某种表现形式进行状态转移。分解开来：

- Resource：资源，即数据。比如newsfeed，friends，order等；
- Representational：某种表现形式，比如用JSON，XML，JPEG等；
- State Transfer：状态变化。通过HTTP动词实现。

然后再来理解一个具体的RESTful架构——面向资源的架构（Resource-Oriented Architecture，ROA）：

- 资源是由URI来指定。所谓「上网」，就是与互联网上一系列的「资源」互动，调用它的URI。
- 对资源的操作包括获取、创建、修改和删除资源，这些操作正好对应HTTP协议提供的GET、POST、PUT和DELETE方法。
- 通过操作资源的表现形式来操作资源。具体表现形式，应该在HTTP请求的头信息中用Accept和Content-Type字段指定。
- 资源的表现形式则是XML或者HTML，取决于读者是机器还是人，是消费web服务的客户软件还是web浏览器。当然也可以是任何其他的格式。

## How？

应用于Web服务，符合REST设计风格的Web API称为RESTful API。它从以下三个方面资源进行定义：

- 直观简短的资源地址：URI，比如：`http://example.com/resources/`；每一个URI代表一种资源；
- 传输的资源：Web服务接受与返回的互联网媒体类型，比如：JSON，XML，YAML等。
- 对资源的操作：Web服务在该资源上所支持的一系列请求方法（比如：POST，GET，PUT或DELETE）。

来个图，

![](http://cdn2.infoqstatic.com/statics_s2_20151020-0055-2u1/resource/articles/rest-introduction/zh/resources/figure2.jpg)

HTTP请求方法在RESTful API中的典型应用：

|资源 | GET | PUT | POST | DELETE|
|----|-----|-----|------|-------|
|一组资源的URI，比如`http://example.com/resources/`|列出URI，以及该资源组中每个资源的详细信息（后者可选）。|使用给定的一组资源替换当前整组资源。|在本组资源中创建/追加一个新的资源。该操作往往返回新资源的URL。|删除整组资源。|
|单个资源的URI，比如`http://example.com/resources/142`|获取指定的资源的详细信息，格式可以自选一个合适的网络媒体类型（比如：XML、JSON等）|替换/创建指定的资源。并将其追加到相应的资源组中。|把指定的资源当做一个资源组，并在其下创建/追加一个新的元素，使其隶属于当前资源。|删除指定的元素。|

## REST的误解

现在看来，REST在2000年那个时代，确实是超前于时代的。Web开发者社区对于HTTP的设计意图存在着大量的误解，由此导致了对于HTTP的大量低效率的误用。这个情况持续一直到2005年Web 2.0的崛起。那个时候，DCOM、EJB、SOAP/WSDL这些DO风格的架构由于难以满足互联网环境对分布式应用架构设计的约束，与Web自身的架构风格REST相冲突，很难融入到Web之中。所谓的「Web
Services」，其实除了将HTTP作为底层的传输协议外，跟（互联网环境中的）真正的Web没有什么关系。

而随着Ruby on Rails这个著名的Web开发框架开始大力支持REST开发之后，一线的Web开发者才真正接触到了REST。然而Rails所支持的REST开发将对资源的操作局限于CRUD（创建、获取、修改、删除）的语义（即，将对资源的CRUD操作映射到
GET/POST/PUT/DELETE四个HTTP方法），这其实是收窄了REST的适用范围。其他编程语言的Web开发框架（例如Java语言的
Struts、Spring MVC等等）也紧接着模仿了Rails的方式开始支持REST开发，然而这更加导致了一线的Web开发者误以为：REST开发就是
通过GET/POST/PUT/DELETE四个HTTP方法对资源执行CRUD操作。甚至还有很多仅仅使用了HTTP，而没有使用SOAP的Web服
务API，都自称是REST风格（RESTful）的API。

对于什么才是真正的REST风格的误解是如此之多，而将REST作为一个便于营销的
buzzword的挂羊头卖狗肉者也是如此之多，以至于REST的创造者Fielding终于忍无可忍了。2008年10月Fielding写了一篇博
客，做出了一个非常明确的断言：[REST APIs must be hypertext-driven!](http://roy.gbiv.com/untangled/2008/rest-apis-must-be-hypertext-driven)（REST API必须是超文本驱动的！）超文本驱动这个理念变成了一个缩写词HATEOAS，这个缩写词来自于当初Fielding博士论文中的一句话：
hypermedia as the engine of application state（将超媒体作为应用状态的引擎）。其实超文本驱动（Hypertext Driven）的理念才是REST架构风格最核心的理念，也是REST风格的架构达到松耦合目标的根本原因。

## REST设计进阶

当谈及REST成熟度时，一些人常常会引用Richardson所提出来的REST成熟度模型（[Maturity Model](http://restcookbook.com/Miscellaneous/richardsonmaturitymodel/)），并视之为正确的度量方法。

![](http://martinfowler.com/articles/images/richardsonMaturityModel/overview.png)

### 第一级：在架构中引入资源（Resource）的概念。

大多数WS-*服务和POX都只是使用一个URI作为一个服务端口，也只使用一个HTTP方法传输数据。这种做法相当于把HTTP这个应用层协议降级为传输层协议用，《REST实战》也一再强调HTTP是一种应用协议而不是传输协议。再好一点就是使用多个URI，然而不同的URI只是作为不同的调用入口，与此同时只使用同一个HTTP方法传输数据。最常见的错误就是在URI中包含动词，比如URI `http://example.com/getOrder?orderId=1234`，其实「资源」表示一种实体，所以应该是名词，动词应该放在HTTP协议中。而与此同时URI也有可能破坏HTTP GET的安全性和幕等性，比如某个客户端在`http://example.com/updateOrder?id=1234&coffee=latte`上执行GET（而不是POST），就能创建一笔新的咖啡订单（一个资源），按理来说GET请求不能改变服务的任何状态。

### 第二级：每一个URI代表一种资源，支持HTTP动词。

此时使用多个URI的话，需要让不同的URI代表不同的资源（注意[多个URI可能指向同一个Resource，而一个URI不能指向不同Resource](http://www.ibm.com/developerworks/cn/webservices/1101_mace_restservicePart1/1101_mace_restservicePart1.html)。），同时使用多个HTTP方法操作这些资源，例如使用POST/GET/PUT/DELET分别进行CRUD操作。这时候HTTP头和有效载荷都包含业务逻辑，例如HTTP方法对应CRUD操作，HTTP状态码对应操作结果的状态。我们现在看到的大多数所谓RESTful API做到的也就是这个级别。《REST实战》的译者也谈到：悟性差的人，理解到CRUD式Web服务就满足了。而悟性好的人，可以彻底理解超文本驱动，甚至是与REST关系密切的语义网，最终达到
REST开发的最高境界。

### 第三级：HATEOAS，使用超媒体（hypermedia）作为应用状态引擎。

根据Roy的严格规定，超媒体（hypermedia）是REST的先决条件。任何其他东西不应该自我标榜为REST。要解释HATEOAS这个概念先要解释什么是超媒体：我们已经知道什么是多媒体（multimedia），以及什么是超文本（hypertext）。其中超文本特有的优势是拥有超链接（hyperlink）。如果我们把超链接引入到多媒体当中去，那就得到了超媒体，因此关键角色还是超链接。使用超媒体作为应用引擎状态，意思是应用引擎的状态变更由客户端访问不同的超媒体资源驱动。

让我们来看个实例，这个响应内容可能略有不同：

```JSON
GET https://api.example.com/profile

{
  "name": "Steve",
  "picture": {
    "large": "https://somecdn.com/pictures/1200x1200.png",
    "medium": "https://somecdn.com/pictures/100x100.png",
    "small": "https://somecdn.com/pictures/10x10.png"
  }
}
```

由于在响应中包含了链接地址，因此使用该API的客户端就能够自由选择要下载怎样的信息。这些链接告知了客户端有哪些选择，并且它们的地址在哪里。因此在这里我们无需同时返回三个不同版本的用户档案图片，我们所做的只是告诉客户端有三种可用的图片尺寸可以选择，并且告诉客户端能够在哪里找到这些图片。这样一来，客户端就能够根据不同的场景，做出符合自身需要的选择。而且，如果客户端只需要一种格式的图片，那就无需下载全部三种版本的图片了。这样一来可谓一箭三雕：既减少了网络负载，又增进了客户端的灵活性，更增进了API的可探索性。

超媒体的核心概念就是所谓的`<link>`元素，而这些相互链接的资源实际上描述了一个协议，即引导我们达成某个目标的一系列步骤，例如订购一杯咖啡所需要的点单、付款、取咖啡等等。这就是超媒体的本质：经由资源之间的链接，我们改变整个应用的状态，即超媒体转换了分布式应用的状态。需要注意的是，服务器和消费者两者间交换的是资源状态的表述，而不是应用的状态，被转移的表述中包括了反应应用状态的链接。

![](http://image.slidesharecdn.com/hypermedia-apis-140121015019-phpapp01/95/hypermedia-apis-why-what-how-17-638.jpg?cb=1390269110)

在这里也推荐直接看看设计非常优秀的[GitHub API](https://developer.github.com/v3/)，以便于更好地理解真实的RESTful API以及hypermedia的概念。

## Reference

- [What Is REST? -- Learn REST: A RESTful Tutorial](http://www.restapitutorial.com/lessons/whatisrest.html)
- [什么是REST与Go语言的RESTful实现](https://github.com/astaxie/build-web-application-with-golang/blob/master/zh/08.3.md)
- [理解RESTful架构 -- 阮一峰](http://www.ruanyifeng.com/blog/2011/09/restful.html)
- [REST 架构该怎么生动地理解？ -- 知乎](http://www.zhihu.com/question/27785028)
- [深入浅出REST - InfoQ](http://www.infoq.com/cn/articles/rest-introduction)
- [面向资源的架构 -- 《RESTful Web Services中文版》](http://www.cnblogs.com/heartstill/archive/2010/12/23/1915029.html)
- [《REST实战》](http://book.douban.com/subject/6854551/)
- [怎么样才算是 RESTful？读 REST in Practice](https://book.douban.com/review/5450803/)
- [Richardson Maturity Model -- Martin Fowler](http://martinfowler.com/articles/richardsonMaturityModel.html)
- [实现超媒体](http://www.infoq.com/cn/articles/implementing-hypermedia)
- [GitHub API文档](https://developer.github.com/v3/)
