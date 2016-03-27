---
layout: post
title: 关于前端的思考：Angular 2.0以及前后端边界
categories: [前端]
tags: [AngularJS, JavaScript]
published: True

---

## 前端的学习曲线

每个人在学AngularJS的时候都会觉得[Angular 1.x](https://angularjs.org/)自创的概念实在太多，学习曲线也因此变得非常陡峭。但对于一个完整的前端项目来说，所需要的东西本来就不够简单，而AngularJS作为一款大而全框架，自带一揽子解决方案，只要学习上手之后还是会有一劳永逸的感觉。就像Python的web框架代表Django和Flask一样，萝卜白菜各有所爱，轻量级框架所带来的灵活性固然很棒，但对于新手来说依旧会很容易玩脱。就像当前所兴起的React大潮，暂且不讨论深度玩家所表现的态度和看法，就论一个前端新手所面临的问题，在没有主见的时候到底该师从何派？

对于前端刚入门的我来说，依旧会推荐从一个大而全的框架开始学起，一个好的框架不但会强制你不犯错误，由此带来的「配置大于约定」也会让一个还没有能力进行约定的能力去学习如何约定。当你学有所成的时候自然会似脱缰一般出去闯荡一番。就像当初青春期的我们，在蜕变之前我们安定得学习该有的技能，当有了一定资本之后就开始自我思考，决定去走自己的路。

反过来说，其实走自己的路，又何尝不是陡峭的呢？对于React来说，也许它所带来的概念非常简单给力。但与此同时，若是以完成整个前端项目为目标的话，你所需要绝对不仅仅只是一个View层的React所能办到的，你会发现前端还可能面临构建、路由、数据流处理等等一系列问题。所以就像当初遇见AngularJS一样，又开始接触眼花缭乱的第三方库所灌输的各种概念。这个时候，你还会认为组合拳的方式好于一揽子式的解决方案吗？

当我们站到一定高度之后再回过头来看问题，似乎问题就变得简单乃至问题都不复存在了。而如何能站到更高的高度呢？那就是开始同时尝试两种方案吧。只有积攒了一定的经验之后，才会认识到跟随永远不是最终的答案，只有亲身体验之后才会拥有自己的认识。那么，最终送上一句话：就是干！

## AngularJS 1.x到2.0

从Angular 1.x官方文档的变迁中就可以看出，Google已经有意精简了核心Modules的内容，并且让其所引入的概念尽可能少。AngularJS拥有着诸多特性，人们津津乐道就是：依赖注入、模块化、自动化双向数据绑定、语义化标签等等。而如果你是一个习惯于写后端的软件工程师的话，所谓的DI和模块化都是常用的代码分层手段，而双向绑定也只是一种VM的简化形式，最核心也是最新颖的概念反而就是Directive，赋予了HTML更强大的能力，相当于让浏览器学习了新的语法。

但与此同时指令也变得过于复杂，赋予Template过多的功能之后只会让人想起原来的服务端脚本语言，比如JSP或者ASP，它们使用数据库的内容加上逻辑判断来直接填充HTML模板。而目前AngularJS中的赋予了类似JSP的过强能力，允许了，甚至鼓励了程序员把代码写得混乱的行为，模板再次成了[灰色地带](https://github.com/lifesinger/lifesinger.github.io/issues/184)。

> AngularJS的创始人之一Misko Hevery：AngularJS弥补了HTML在构建应用方面的不足，其通过使用标识符（directives）结构，来扩展Web应用中的HTML词汇，使开发者可以使用HTML来声明动态内容，从而使得Web开发和测试工作变得更加容易。 

当AngularJS刚创建出来的时候，它并不是给开发人员用的。它是一个工具，更倾向于给需要快速创建持久化HTML表单的设计人员用。随着时间推移，它作了改变以适应各种场景，开发人员也用它建造更多、更复杂的应用程序，而只是在原有基础之上直接进行「增量化地」改进是远远不够的。这就是Angular 2.0在较高层次上的动机。更详细的内容可以参考这篇[［翻译］有关Angular 2.0的一切](https://github.com/xufei/blog/issues/8)，我还特意去翻了一下原作者[Rob Eisenberg](https://twitter.com/eisenbergeffect)的Blog和Twitter，结果就发现他是：

> Creator of Caliburn.Micro & Durandal. Former Angular 2.0 team member. Currently building a new tech startup, Durandal Inc., whose first product is Aurelia.

Aurelia和Angular 2.0有诸多相似之处，详细的内容可以参考[Introducing Aurelia](http://blog.durandal.io/2015/01/26/introducing-aurelia/)，以及[后Angular时代二三事](https://github.com/xufei/blog/issues/21)这篇文章里面所提到的一些共同特性。

最后从这篇[浴火重生的Angular](https://github.com/xufei/blog/issues/9)中查看关于[Angular 2.0](https://angular.io/)最新的module、Web Components、observe、promise等特性吧，据说被诟病已久的性能也优化得不行不行的，总之我还是相当期待Angular 2.0的！

## 划分前后端边界？

在这篇来自关于[［翻译］Angular的问题](https://github.com/xufei/blog/issues/15)文章中，作者ppk乃至译者xufei自己也提到，Angular更多地是面向企业的IT部门，而不是前端人员，并且使用AngularJS的用户更多是有Java背景的人员。而在现在这个前端粥多僧少的阶段，必然有很大一部分Java开发人员要去写JavaScript，但与此同时由于JavaScript代码太过缺乏约束，也让Java开发人员更加无所适从。这时Angular的约束性以及依赖注入等特性的好处就彰显出来了，特别是对于传统后端开发者来说，当遵守AngularJS的约定时，生产力也会更高。

与此同时，AngularJS独特的编码风格，它那种更倾向服务端而不是浏览器端的对HTML模板系统的封装形式，以及严重而基础的性能问题也吓跑了不少原来写前端的开发者。对于很多前端人员而言，最大的问题就是，AngularJS强迫自己用一种指定的方式去干活。

xufei提到的另外一个关于前端代码写得烂的原因就在于：前端开发者缺乏架构意识，或者项目负责人和架构师（通常是后端）没有足够的前端知识，而这两点不解决，用什么框架都一定做成渣。这点需要反对一下的就是，这跟框架可用性以及易用性的关系还是挺大的，要是开发者都能够有清晰的编程架构意识，那岂不是纯靠原生的Java就可以把后端写得很漂亮，又或者是只靠JavaScript、CSS、HTML就可以把前端的脏活干得很漂亮？

然后，其实这儿也牵扯出一个更有趣的问题，在前后端分别都有相应的「模板」概念，那么HTML的动态内容究竟应该由谁来处理，也就是如何划分和界定前端后端？而评论中也有两位大神对模板应当归属于浏览器端还是服务器端[吵得不可开交](https://github.com/xufei/blog/issues/15#issuecomment-73462675)，而我个人还是比较赞同@calidion的观点，不应该去区分绝对的前端后端，更多内容在：[Web开发的前端与后端的界线在那里？](http://blog.3gcnbeta.com/2015/02/24/Web%E5%BC%80%E5%8F%91%E7%9A%84%E5%89%8D%E7%AB%AF%E4%B8%8E%E5%90%8E%E7%AB%AF%E7%9A%84%E7%95%8C%E7%BA%BF%E5%9C%A8%E9%82%A3%E9%87%8C%EF%BC%9F/)，最后的结论就在于「运行环境是唯一的前后端分界线」。

那么，在这个前后端分离趋势愈演愈烈的时期过渡之后呢？Web的未来是在哪里？[Isomorphic/Universal JavaScript](http://nerds.airbnb.com/isomorphic-javascript-future-web-apps/)嘛？其实对于一个更广泛概念的Application来说，前后端本来就是一家，最多分为界面（Application的界面可能是Web/iOS/Android/Desktop等等）和背后的数据处理而已。若是使用统一的数据格式（JSON）并且在浏览器内存和数据库间实现数据同步（个人很喜欢[Meteor](https://www.meteor.com/why-meteor/features)的概念），剩下的就只是编写业务逻辑，然后如何把数据显示到不同的「界面」上的问题而已。
