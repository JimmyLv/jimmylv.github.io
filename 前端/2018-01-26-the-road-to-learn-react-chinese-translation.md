---
layout: post
title: '【译】《React 学习之道》The Road to learn React (简体中文版) 最简单，且最实用的 React 实战教程'
categories: [前端]
tags: [Tutorial, Roadmap, ES6, React]
published: True
---

> 通往 React 实战大师之旅：掌握 React 最简单，且最实用的教程。

![](https://s3.amazonaws.com/titlepages.leanpub.com/the-road-to-learn-react-chinese/hero?1514299109)

## 前言

[《React 学习之道》](https://leanpub.com/the-road-to-learn-react-chinese/)这本书使用路线图中的精华部分用于传授 React，并将其融入一个独具吸引力的真实世界 App 的具体代码实现。

如何掌握 React 存在特别多的路线图。本书提取这些路线图中的精华部分，并将其融入于一个具体的应用程序当中。您将会构建一个属于自己的 React 应用程序。在本次学习之旅当中，您将学习 ES6，了解所有 React 的基础知识、先进理念，以及组件的内部状态管理。

## 作者与译者

首先，感谢 [The Road to learn React](https://leanpub.com/the-road-to-learn-react) 原书作者，[Robin Wieruch](https://leanpub.com/u/rwieruch)。本书的翻译始于 React China 社区的一个帖子：[The Road to learn React - Simplified Chinese Translation](http://react-china.org/t/the-road-to-learn-react-simplified-chinese-translation/16497)。

本书翻译来自 ThoughtWorks 的 JS Community 超豪华译者团队（排名不分先后）：

[@LeiZeng](https://github.com/LeiZeng) （曾磊）、[@JimmyLv](https://github.com/JimmyLv) （吕靖）

[@SBeator](https://github.com/SBeator) （曾星鑫）、[@kenpusney](https://github.com/kenpusney) （刘清）

[@azzgo](https://github.com/azzgo) （文一山）、[@trotyl](https://github.com/trotyl) （余泽江）

[@ariesjia](https://github.com/ariesjia) （陈嘉）、[@Yixi](https://github.com/Yixi) （刘应皓）

[@HelloRuiLi](https://github.com/HelloRuiLi) （李睿）、[@lazurey](https://github.com/lazurey) （梁越）

[@zengyang2014](https://github.com/zengyang2014) （曾扬）、[@liujiefengfeng](https://github.com/liujiefengfeng) （刘杰凤）

[@futantan](https://github.com/futantan) （傅坦坦）、[@linksgo2011](https://github.com/linksgo2011) （林宁）

## 本书介绍

《React 学习之道》会教您一些 React 的基础知识。通过这套教程，您可以使用纯 React 构建一个真正可用的应用程序，而不需要去理会其他复杂的工具。我将为您逐一介绍从开发环境的准备到部署上线的全部过程。本书每一章都包含一些额外的索引资料以及课后练习。在读完本书之后，您将会有能力依靠自己构建一个 React 应用。我，[Robin Wieruch](https://leanpub.com/u/rwieruch)，以及整个社区会持续维护和更新这些资料。

通过《React 学习之道》，在开始陷入到更庞大的 React 生态圈之前，我想为您奠定一个良好的基础。它会通过一个真实可用的 React 应用来解释基本概念、设计模式以及最佳实践。

您将会学习构建您自己的 React 应用。这个应用会涉及一些真正可用的功能，比如分页，客户端缓存，以及像搜索和排序这样的交互功能。另外在这个过程中，您会慢慢从 JavaScript ES5 过渡到 JavaScript ES6。我希望这本书能充分体现我对 React 和 JavaScript 的热忱所在，并帮助您能够开始您的开发旅程。

## 您可以期望学到什么（目前为止...）

- [Hacker News 的 React 版本](https://intense-refuge-78753.herokuapp.com/)
- 没有复杂的配置
- 用 create-react-app 来初始化你的应用
- 高效而轻量级的代码
- 只用 React setState 来做状态管理（目前为止...）
- 从 JavaScript ES5 一路平滑过渡到 ES6
- React setState 和生命周期函数的用法
- 和真实 API 的交互（Hacker News）
- 高级用户交互
- 客户端排序
- 客户端过滤
- 服务器端搜索
- 客户端缓存的实现
- 高阶函数和高阶组件
- 用 Jest 进行组件的切片(snapshot)测试
- 用 Enzyme 进行组件的单元测试
- 过程中学到一些有用的工具库
- 过程中的练习题和扩展阅读
- 认同和巩固你的所学
- 将您的应用部署到产品环境

## 您需要具备哪些知识？

在开始阅读本书之前，您应该熟悉 HTML、CSS 和 JavaScript（ES5）。本书将会传授 ES6 及其更高版本，如果您熟悉于其它不同的 SPA 框架或库，您应该对这些基本知识已经了然于心。如果您刚刚开始您的 Web 开发之旅，您应该优先学习并掌握 HTML、CSS 和 JavaScript，然后再来学习 React。

## 读者赠言

**[Muhammad Kashif](https://twitter.com/appsdevpk/status/848625244956901376):** “《React 学习之道》是一本独一无二的书，我推荐给任何想要学习 React 基础和进阶技巧的学生或者专业人士。她包含了诸多启发性的小提示和绝无仅有的技术点。书中虽然引用了大量例子和参考资料，但最后都被用到我们要解决的问题上，这体现了编写本书令人惊叹地缜密。我有 17 年的互联网和桌面开发经验，阅读本书之前，我在学习 React 的过程中缺并不顺利。而这本书就像魔术一样有用。”

**[Andre Vargas](https://twitter.com/andrevar66/status/853789166987038720):** “Robin Wieruch 的《React 学习之道》是一本非常牛的书！我所学到的绝大部分有关 React 甚至是 ES6 的知识都是通过她得来的！”

**[Nicholas Hunt-Walker, Instructor of Python at a Seattle Coding School](https://twitter.com/nhuntwalker/status/845730837823840256):** “这是一本我读过的最严谨和最实用的编程书籍之一。一本完整的 React 和 ES6 使用说明。”

**[Austin Green](https://twitter.com/AustinGreen/status/845321540627521536):** “非常感谢，真的很喜欢这本书。完美的学习曲线，不管是 React，ES6，还是抽象编程概念。”

**[Nicole Ferguson](https://twitter.com/nicoleffe/status/833488391148822528):** “这个周末跟着 Robin 的课程学习 React，我发现这一切太有意思了。这几乎让我感到羞愧。”

**[Karan](https://twitter.com/kvss1992/status/889197346344493056):** “刚刚完成这个课程。这是全世界最好的学习 React 和 JS 的一本书。完美展现了 ES 的优雅。膜拜！ :)”

**[Eric Priou](https://twitter.com/erixtekila/status/840875459730657283):** “Robin 的《React 学习之道》是必读的一本书。简明扼要地介绍了 React 和 Javascript。”

**一个新手开发:** “作为一个开发新手，我刚刚完成了这本书的学习，非常感谢写了这本书。她非常容易上手，我相信自己在接下来的几天可以开始从头开发一个新应用。这本书比我之前试过的官方 React 入门文档好很多（由于缺乏细节，我并未能够完成）。每个章节后面的练习题对我有很好的激励效果。”

**一个学生:** “这是最好的学习 React 的一本书。我们可以一边做练习项目，一边学习知识点，然后还能紧扣我们的学习主题。我发现「边码边学」是最好的掌握编程的方法，而这本书完完全全是这样教我的。”

**[Thomas Lockney](https://www.goodreads.com/review/show/1880673388):** “这是一本非常扎实的介绍 React 的书，而不是试着把事情搞复杂。我本来只想尝试理解看看这本书到底讲了什么，然后我得出了上面的结论。我并没有跟着所有的脚注来学习我还没有注意到的新的 ES6 语法（我当然不会说我一直没有注意到，Bob）（译者注：这个是在博客中与另外一个朋友互动的话）。对于那些没有及时了解到这些新功能，并且很勤奋的跟着练习的朋友们，我想很肯定地对你们说，你们能学到的会不仅仅是这本书所教的东西。”

## 恭喜你，快去看看我们的 Leanpub 主页吧！

[《React 学习之道》The Road to learn React (简体中文版) [PDF/iPad/Kindle]](https://leanpub.com/the-road-to-learn-react-chinese/)

支持 PDF、EPUB、MOBI、Kindle 多种格式下载，并支持 Leanpub 在线阅读。

## 最后！求 Star！求小星星！

- GitHub 翻译地址：[the-road-to-learn-react/the-road-to-learn-react-chinese: 《React 学习之道》The Road to learn React (简体中文版) - 最简单，且最实用的 React 实战教程。](https://github.com/the-road-to-learn-react/the-road-to-learn-react-chinese)
- GitHub 原书地址：[the-road-to-learn-react/the-road-to-learn-react: The Road to learn React](https://github.com/the-road-to-learn-react/the-road-to-learn-react)
