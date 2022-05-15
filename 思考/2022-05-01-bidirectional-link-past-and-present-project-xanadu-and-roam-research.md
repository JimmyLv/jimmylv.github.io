---
layout: post
title: 【双向链接的前世今生】上都计划与 Roam Research 思维工具
categories: [思考]
tags: [认知, 双向链接, 效率, 自我管理, 知识创造, RoamResearch, 上都计划, 思维工具, 卡片写作, Zettelkasten, PKM]
published: True
---

- （后续）修订版：[https://jimmylv.noto.so/xanadu](https://jimmylv.noto.so/xanadu)
- 少数派：🔗 [https://sspai.com/post/72995](https://sspai.com/post/72995) 🔗

对我来说，我在很久之前就一直在探索知识管理、任务管理，这方面是我一直以来非常热衷的兴趣点。本文是我**第一次系统性地介绍双向链接是什么**，会先为你讲述 **Roam 的 3 个故事**，然后专注于解释 Roam Research**最核心的 1 个功能**：双向链接（当然，Roam 还有很多其他好玩的地方）。最后，我会介绍**自己的 2 个应用场景**，以及什么是 Tools for Thought 和为什么你需要一款思维工具？

# **一、Roam 的 3 个故事，源自上都计划**

### **故事 1：@Ted Nelson 失落的超文本 —— 上都计划（Project Xanadu）**

第一个故事其实是 Ted Nelson（泰德·尼尔森）的故事，上都计划（Project Xanadu）。**1963 年，信息技术先驱、《Computer Lib / Dream Machines》作者 Ted Nelson 发明了「超文本」（hypertext）这一概念。**但是，此时的超文本跟我们现在所讲的 HTTP 超文本传输协议大相径庭。

![https://cdn.sspai.com/2022/05/02/article/f739d301585145f141d930ff9f8086c2?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/f739d301585145f141d930ff9f8086c2?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

在 Ted Nelson 构想的超文本系统中，我们访问的所有的网页或者叫文本，都应该是相互链接的。Xanadu（上都）是一个拥有很富文学意涵的字，马可·波罗（Marco Polo）在他的自传里提到 Shan-Du，指的是忽必烈汗元帝国的夏季之都。1965 年，Ted Nelson 将他发起的超文字构想，依照柯立芝的诗命名为「仙那度计划」（Project Xanadu），因为他认为仙那度是**「一个记忆永远不会被遗忘的神奇地方」**。

但它最终跟我们现在听到的超文本系统是非常不一样的。**1991 年，Tim Berners-Lee（蒂姆·伯纳斯-李）在欧洲粒子物理研究所工作时，提出了一套新的协议超文本传输协议**（The Hypertext Transfer Protocol，即 HTTP），并且定义了超文本标记语言（HyperText Markup Language，即 HTML），然后才有了 HTTP 1/2 的实现。

![https://cdn.sspai.com/2022/05/02/article/6d51b04daf8286de54441bc7f8b1c8ca?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/6d51b04daf8286de54441bc7f8b1c8ca?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

在 HTTP 这套系统里面，其实每一个事物都是有对应的一个统一资源标识符（URL）。但是你有没有想过，**我们每次通过链接点进去，从 A 网页到达 B 网页，那我们又怎么从 B 回到 A 呢？**

在 1991 年之后，基于 HTTP 协议的整个网络我们称之为它为万维网（World Wide Web，即 WWW），这都是我们非常熟悉的概念了，Tim Berners-Lee 也因此被称之为万维网之父。并且，在万维网上诞生了 Google、Amazon、Meta 等一系列大型互联网公司，使其易于连接和交易。

但是，Tim Berners-Lee 在一系列的连锁事件中，他也开始指责这些公司用广告的名义破坏了网络，凭借平台积累了过多的权力，因此创办了「Inrupt」公司和 Solid 项目，**试图通过建立一个让用户控制自己数据的平台来「重塑互联网」**。

![https://cdn.sspai.com/2022/05/02/article/41d988e419e445db2dec9501c9d624a5?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/41d988e419e445db2dec9501c9d624a5?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

而对于 84 岁的 Ted Nelson 来说，「上都计划」是他一直以来的初心，他的个人梦想，直到 2014 年发布了第一个试用版本。「上都计划」的试用版本可以通过这个网页链接 [https://xanadu.com](https://xanadu.com/xanademos/MoeJusteOrigins.html) 进入，你将看到一篇宇宙学的文章。

![https://cdn.sspai.com/2022/05/02/article/76e5da8e672d168577dd21980651fd6d?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/76e5da8e672d168577dd21980651fd6d?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

网页的左右两边分别有不同颜色的划分，重点来说中间的这篇文章，其实它是引用了很多其他文章里面的内容。所以，**在 Ted Nelson 最开始的愿景中，就期望通过双向链接在浏览网页的同时，能够把引用不同文章里的高亮能够互相引用起来。**

不同颜色的高亮其实就表达了一种引用关系。当然「上都计划」除了这个引用关系的描述以外，还会有其他的一些构想，比如说版本管理或者增量出版等等，文本就不多作具体介绍了。

从 1963 年到 2014 年，「上都计划」才发布了它的第一个版本对吧？但是大家有没有想过，它竟然也是发布在万维网上的一个 URL 链接，也就是说**连 Ted Nelson 的最初版本都还是不得已借助于 HTTP 协议来传播，基于万维网去实现它的第一个发布版本。**

### **故事 2：@Conor 与 Roam Research 双向链接笔记/思考工具**

![https://cdn.sspai.com/2022/05/02/article/da943fc3721bb0e1df40b6459fde1da0?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/da943fc3721bb0e1df40b6459fde1da0?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

第二个故事就要讲到 Conor，也就是 Roam Research 的创始人，他在 2019 年的时候推出了 Roam Research，掀起了双向链接笔记工具的浪潮。但其实在 Roam 的官网上，一直将 Roam Research 称之为一个「网状思维工具」。

![https://cdn.sspai.com/2022/05/02/article/49c31b272b13899126e7efc2bba66f8a?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/49c31b272b13899126e7efc2bba66f8a?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

首先，Roam 是可以在一定程度上模拟前文提到的「上都计划」，不同页面之间可以相互链接，与此同时也有社区的[设计师 Azlen](https://twitter.com/i/status/1272600877493137408) 在 Roam Research 里面实现了 Block 块与块之间能够互相链接的可视化，不同的页面之间会有段落和段落之间的联系，而这些联系通过高亮的方式链接起来。

![https://cdn.sspai.com/2022/05/02/7a389c191c86d497bd16c2c6df98b5ce.gif](https://cdn.sspai.com/2022/05/02/7a389c191c86d497bd16c2c6df98b5ce.gif)

[Azlen Roam Style: "parallel pages, visibly connected"](https://www.bilibili.com/video/BV17Y4y1h7u8?spm_id_from=333.999.0.0)

那在 2019 年推出 Roam 之后，2020 年双链笔记最火热的同时，特别是资本也是非常狂热的，Roam Research A 轮融资 900 万美元，估值两亿多美元，最新的[这个报道](https://www.enterprisetech30.com/)，显示的总计融资应该是 1240 万美元。

虽然体量很小，但是 Roam Research 却受到了资本的狂热的追捧，有十几家公司及个人参与了 Roam 的 A 轮融资，包括 Stripe 联合创始人 Patrick 和 John Collison、True Ventures 和 Lux Capital 等非常知名的一些资本。

当然，除了狂热的资本以外，Roam 也拥有一个非常狂热的社区，我们通常来说都称之它为 #roamcult 类似宗教的一个概念。这里有一个蛋糕，就是用户自行制作的 Roam Research 界面的蛋糕。

![https://cdn.sspai.com/2022/05/02/article/9edf899450a3a0329b4e15c2cb86970a?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/9edf899450a3a0329b4e15c2cb86970a?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

然后与此同时，甚至还有人把 Roam Research 的 LOGO**𐃏** 符号纹到了身上或者腿上，我至少在推特上见过 5 个这样的狂热份子。

![https://cdn.sspai.com/2022/05/02/article/ce06c1211e789a66476b70208db9ea47?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/ce06c1211e789a66476b70208db9ea47?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

### **故事 3：@JimmyLv 与 RoamCN 社区，“探索未来工作”**

第三个故事是我自己的一个故事，我其实是在 2019 年初次知道双向链接，遇见 Roam Research，然后在 2020 年跟另外两个区块链领域的小伙伴（Jessie、Victor）共同创立了 [RoamCN 中文社区](https://github.com/JimmyLv/roam-cn.github.io)。

![https://cdn.sspai.com/2022/05/02/article/f4a70297fe40826c75570c05b945133d?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/f4a70297fe40826c75570c05b945133d?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

前文提到我自己的兴趣点，关注知识管理已经很长时间了，而 Roam Research 提供的双向链接刚好解答了我探索已久的困惑。与此同时，在中文社区，特别是对于我自己而言，我也在寻找很多的一些同路者，大家一起来学习探讨新的工具，一个极具突破性的工具。所以，我就不断地在使用这款工具来管理我的日常，不管是做项目或者是写文章、做视频等等。

[「逍遥漫游，即时创作」](https://www.bilibili.com/video/BV1m44y1V7EG?spm_id_from=333.999.0.0)是我最近在合桃派的一次直播，也是我使用 Roam Research 两年多的经验总结，分享的内容会比较详细啦，也可以推荐大家去看看。另外在 B 站上面，我有做过六十多个视频，也是一个不断输出不断学习的一个过程。

![https://cdn.sspai.com/2022/05/02/0d0f950993efe4007c65d640ace2ad7a.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/0d0f950993efe4007c65d640ace2ad7a.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

特别好玩的是，**在 2020 年我也因为对 Roam Research 的探索和学习，积累了一些工作机会**。包括当时我去阿里，跟面试官聊的时候也聊到了 Roam Research，而在 2022 年 2 月 22 号，我加入了一家纯远程办公的公司（[Parabol.co](https://parabol.co/)），开启了新的「完全在家办公」的工作方式。

![https://cdn.sspai.com/2022/05/07/80552fbdf009246ace297c2f130f1350.gif](https://cdn.sspai.com/2022/05/07/80552fbdf009246ace297c2f130f1350.gif)

[Parabol.co - Build the Future of Work](https://www.parabol.co/)

所以说，Roam Research 这样一款新工具不光是承接了我自己的一个兴趣，也让我有了一个“探索未来工作”的机会。其实我也是非常感激这些机会，特别是我遇到了很多非常好玩有趣的人，特别是像字节跳动、小米、微软、阿里巴巴的高层（我平常不可能接触到的那种）都注意到了双向链接，并且推进了相关产品的研发。

这三个故事分享完，我们可以对双向链接有了一个基本脉络，**双向链接这个概念它并不新颖**，其实在 1963 年就由 Ted Nelson 发布了「超文本」（hypertext）一词，此时超文本的原本概念就已经包含了相互链接。而**直到 2022 年 Roam Research 推出之后，双向链接的概念才被普通人接触到**，包括印象笔记等等这样的很多知识管理工具都开始跟进设计。

# **二、Roam 的 1 个核心：[[双向链接]]**

接下来我会介绍在 Roam Research 里面，双向链接到底是一个什么东西，以及我为什么会对双向链接以及社区为什么会对双向链接如此的热衷。

### **0. 思想即技术 Thought as a Technology**

首先想给大家介绍一个概念，就是「思想即技术」。在我们没有这个高速摄像机的时候，我们会怎么样去描述一个子弹穿过某些物体的呢？其实我们是没有任何手段去描述它或者说去观察这个过程的。

![https://cdn.sspai.com/2022/05/02/article/b391583bf40650e39475d4c6dfa5d2cc?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/b391583bf40650e39475d4c6dfa5d2cc?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

在高速摄影机出现之后，我们就相当于有了一种新的认知元素。[Michael Nielsen](http://michaelnielsen.org/) 物理学家在 [Thought as a Technology](https://cognitivemedium.com/tat/index.html) 这篇文章提到 Tools for Thought 就是思维层面的工具，当我们拥有了一个新的认知元素，就可以在更低维度或者说在不同的维度去观察，那些以前我们觉得非常习以为常的一些元素，或者是概念、事物。

就像唐·诺曼提到，**人们其实高估了自己独立思考的能力**。我们的大脑如果没有像双向链接这样的思维工具作为外部的辅助，我们的思考、推理其实都是会受到限制的。那如果我们有了这样能够提高认知能力的外界辅助工具，我相信大家的这种思考或者是推理能力都会得到提升。

> 唐·诺曼，全球最具影响力的设计师，《设计心理学》的作者，苹果的前用户体验架构师，在他的《Things That Make Us Smart 让我们变聪明的事情: 在机器时代捍卫人类属性》一书中提到：「人们高估了独立思考的能力。 没有外部帮助，记忆、思维和推理都会受到限制... ...真正的力量来自于设计能够提高认知能力的外部辅助设备。」

### **1. 页引用 [[]]，“时空隧道”**

Roam Research 的第一个概念就是页引用，大家接触双向链接之后最常见的双中括号的符号就是页引用。

![https://cdn.sspai.com/2022/05/02/article/14c2ba4427203452534e47577e5fc725?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/14c2ba4427203452534e47577e5fc725?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

如图所示，首先我们在 [[October 12th, 2019]] 页面上写下了自己的一些想法，然后我们可以通过双括号的方式直接新建一个页面 [[Grant Proposal v3]]，然后从这个页面上就可以直接跳转过去。而在 [[Grant Proposal v3]] 页面下方会显示对应的一个反向链接，**所谓的双向链接就是包括正向链接和反向链接。**

如果说大家对这个概念不是特别了解，我就抽象了一个相对来说更熟悉的一个概念，叫「时空隧道」。比如说你可以从今天穿越到 50 年之后或者是 3 年之前**（时间）**，或者从今天穿越到一个对应的页面，你还可以在不同的页面当中进行穿梭**（空间）**。

文字解释起来非常苍白，我在下方准备了一个视频，从任意的地方打开一个传送门，就可以直接穿越过去，这在一些解密游戏里面是非常常见的。比如说上方的锯齿机关就要压到你，进入传送门就直接从这一端穿越到了另外一端，恭喜通关。

<iframe src="https://player.bilibili.com/player.html?aid=981148661&amp;bvid=BV1W44y1372M&amp;cid=590201730&amp;page=1" title="iframe embed" height="467px" width="100%" frameborder="0" allowfullscreen="" loading="lazy"></iframe>

这个就很像**奇异博士的超能力，能够直接打开一个时空门或者叫哆啦 A 梦的任意门，你就可以随意地从时间上和空间上进行一个穿梭。**

好，这是第一个双向链接的一个解释，特别是在 Roam Research 里双向链接的用途之一。当然页引用还有其他用途，我会在第三部分，也就是我自己的两个使用场景上给大家具体去解释。

### **2. 块引用 (())，“蜘蛛丝”**

下一个双向链接的应用场景就是块引用。比如说我们在一个页面上有很多很多的节点或者叫段落，我们在写文章的时候，会期望把另外一个页面上的某一个段落直接摘录过来。

那就可以**通过两个圆括号 (()) 直接把对应的段落 “拉”过来**，比如说我用圆括号搜索刚刚写的「页引用」内容，你会发现它可以搜索到之前我写过的所有内容，然后直接把它拉过来。

![https://cdn.sspai.com/2022/05/02/fdf84391cb9a6aada7e81155fa29888e.gif](https://cdn.sspai.com/2022/05/02/fdf84391cb9a6aada7e81155fa29888e.gif)

相应的，在块级别右上角有一个 reference 的数字，如果点一下就会发现又回到了刚刚讲页引用的出处，建立了块级别的「时空隧道」，也就是段落级别或者叫 Block 块级别的一个双向链接。

块级别的双向链接，我更期望说用“蜘蛛丝”的具体概念来给大家映射一下，或者叫类比一下。比如说我们想要拿到一个东西，我们并不需要直接跑到那个页面上去，而是**直接通过圆括号 (()) 的方式直接就把它拉过来了，就像蜘蛛侠弹出蜘蛛丝，然后就把这个内容来拉过来**。

![https://cdn.sspai.com/2022/05/02/article/7463a06f6f9020c5d07b6aa994c9986f?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/7463a06f6f9020c5d07b6aa994c9986f?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

### **3. 动态块 {{}}，“乐高马达”**

下一个在 Roam Research 里面的概念是「动态块」，比如说我在视频中最开始的时候有提到过一个计时器，`{{[[POMO]]: 25}}` 就是通过花括号 {{}} 的方式直接创建出来的。

我可以把「动态块」类比成「乐高马达」，乐高这家公司确实~~X~~炸天，乐高机械组 1:1 比例完整还原全球时速最快的量产超跑——BUGATTI CHIRON。布加迪首席试车员更将这辆独一无二的超跑开上了跑道，真正意义上实现了机械传动的无限可能，完成了“让积木跑起来”的惊艳挑战。

![https://cdn.sspai.com/2022/05/02/article/83b8783a0ef7380433a6a946bd83cffe?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/83b8783a0ef7380433a6a946bd83cffe?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

那么这辆车里面是用到了真正的「乐高马达」，因为乐高其实会有动态的和静态的两种，我们平常接触到的可能都是静态的，但其实是有一些动态的模块可以作为马达来使用的，从而你可以创作出更多的好玩的东西。

那这里我给大家举一个具体的例子，比如说我可以通过花括号加上一个 video 的特殊标识 `{{[[video]]: https://www.youtube.com/watch?v=ZQdlCQmzUAM }}`，然后再输入视频的链接，这个 block 就会变成了一个动态的，可以显示 YouTube 视频的「动态块」，从而还可以播放视频，插入时间戳记录笔记，进行功能上的交互。

![https://cdn.sspai.com/2022/05/02/7ff5a38e79db8d152727d3891cfc8404.gif](https://cdn.sspai.com/2022/05/02/7ff5a38e79db8d152727d3891cfc8404.gif)

### **为什么说 Roam Research 是一款思维工具，而非笔记工具？**

所以说，**Roam Research 被称之为一款思维工具**，而不仅仅只是一款笔记工具的原因就在于**基于 Block 的可编程性**。首先就是前文提到的每一个 block 每一个段落都可以单独去拖动和处理，并且它可以单独显示，单独执行，可以被引用，可以被拉取。

**万物皆可 Block** 这个概念在使用 Roam Research 之前也有很多工具，包括 Notion、Microsoft Loop 等等，不得不说 [Loop](https://www.microsoft.com/en-us/microsoft-loop?ms.url=microsoftcommicrosoft-loop) 的宣传片确实是让我垂涎欲滴等了好久，确实做得非常非常漂亮，也是我 2022 年最期待的一个产品之一。

![https://cdn.sspai.com/2022/05/02/ea6b7fe2981d82767d0ccc8bc6d641bc.gif](https://cdn.sspai.com/2022/05/02/ea6b7fe2981d82767d0ccc8bc6d641bc.gif)

每一个元素都是可以单独拖拽、编辑和显示，并且具有很强的可交互性，你就可以像搭建乐高一样去搭建属于自己的知识操作系统，可以实现看板、 Table 等等各种各样的子系统，让它们去帮助你去做任务管理、知识管理等工作。

**而 Roam Research 在使用体验上最大的特点，就在于它让我们写作跟“写代码”一样 `[[]]`、`(())`、`{{}}`。**我们只需要通过简单的中括号 `[[]]` 去跳转到之前记录下的一些笔记页面或者叫卡片标题；我们可以通过圆括号 `(())` 来搜索之前包含关键词的一些段落内容；最后，我们还可以用花括号 `{{}}` 来实现一些特殊用途的动态元素，比如说前文提到的番茄钟，就会变成了一个时间的按钮，我可以点击它，然后进行一个倒计时。

# **三、我的 2 个应用场景：输入/输出**

![https://cdn.sspai.com/2022/05/02/article/ae89324a1ebc3e5ed818887da292a824?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/ae89324a1ebc3e5ed818887da292a824?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

首先，我们需要有一种思维的辅助工具，比如说像高速摄像机一样，**当我们拥有了双向链接这样一个思考工具，或者叫新的认知元素，就能辅助我们在思维上有所提升，辅助你去思考，辅助你去推理。**

「时空隧道」我们可以从今天跳到明天，跳到 50 年之后，也可以用它来串联起不同概念之间的一个联系。比如说我在准备这一次分享内容的时候，其实是有关联到到之前的一些页面的，比如说「探索未来工作」这个页面，跟今天要讲的内容就是串联起来的。这样产生的一个局部的知识图谱，就是双向链接的一个可视化效果。

![https://cdn.sspai.com/2022/05/02/article/a0940c3c677d9b241f7ac1f75849dbaa?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/a0940c3c677d9b241f7ac1f75849dbaa?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

而当我们使用块引用的时候，我们可以把不同页面的段落快速地组装起来，像搭乐高一样把积木块搭起来，那就可以用到「蜘蛛丝」去快速拉取自己想要调取的内容。

另外还可以通过「乐高马达」来实现知识的编程，Roam Research 内的 Block 并不是静态的，而是可能能够像乐高里面的马达一样“转动”起来。

所以，拥有了这样一款思维工具，我们应该怎么样去使用它呢？接下来就进入到我的下一个话题，就是我是怎么去使用 Roam Research，怎么样在具体的场景中去使用它。

通过最简单的输入、输出模型将其分为两个部分，**第一个是输入，我是怎么读书记笔记的，第二个则是怎么样高效地去产出，用自己的卡片盒快速地产出我要分享的内容、我要写的文章等等**。

### **1. 逍遥输入 - 读书、记笔记**

所以，第一部分我会来讲读书记笔记的过程。可能之前大家都已经听说过卡片盒笔记法，甚至还有本书叫《卡片笔记写作法》，书中有一个最核心的观点，就是「不写，就无法思考」。那我们可以以读这本书为例，来简单讲解一下阅读+记笔记的过程。

<iframe src="https://player.bilibili.com/player.html?aid=726118391&bvid=BV1NS4y1Y749&cid=588113838&page=1&t=1138" title="iframe embed" height="467px" width="100%" frameborder="0" allowfullscreen="" loading="lazy"></iframe>

点击跳转时间戳 18:58[https://www.bilibili.com/video/BV1NS4y1Y749?t=1138](https://www.bilibili.com/video/BV1NS4y1Y749?t=1138)

（这一段的文字描述同样过于苍白，还是推荐大家去看我在视频中的演示，我尽力了，🤣）

首先，我会新建一个单独的 Graph 来存放要读的书，《卡片笔记写作法》就是其中一本。那么在读书的时候，双向链接可以怎么样帮助到我们呢？比如说我们在读第一章的时候遇到一些概念，以「心流」概念为例，我就可以给[[心流]]加上中括号，也就是双向链接。

![https://cdn.sspai.com/2022/05/02/article/7b9f1d68a12c60f9bbf15256e3ec5107?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/7b9f1d68a12c60f9bbf15256e3ec5107?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

此时我再点进[[心流]]这个页面，我就可以点开 Unlinked References 看到跟「心流」相关的内容，也就是在这本书里面的其他章节也提到了心流这个概念。所以说，**每当我遇到了一些新的概念，我就会把新的概念加上中括号，从而就可以探索性地去发现这本书里面有哪些跟这个内容相关的。**

如果将这个过程总结一下的话，区别于以前「线性地」根据章节去读这本书的过程，**相反，我们其实是在跟作者进行一个交流，然后在交流的时候，还原作者脑海中原来的「网状结构」。**认知科学家史蒂芬·平克曾经说过，他是从写作者的角度来说的：

> 「写作之难，在于将网状的思想，通过树状的句法，用线性的文字展开。」

每当作者写成一本书，写成一篇文章，其实是**将自己在大脑中原本互相链接的网状结构，必须只能「局限性地」通过文字这种的线性方式进行展开。**

所以，当我们在 Roam Research 阅读一本书的时候，就更像是在与作者跨时空交流，根据自己的兴趣点向作者提问。

![https://cdn.sspai.com/2022/05/02/article/f8346771ba0d47aecd22ad6c3c63338e?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/f8346771ba0d47aecd22ad6c3c63338e?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

而我在提问交流的同时，我会使用 roam/comments 功能记录下自己的「闪念笔记」。这些笔记一方面会自动记录到某一天的 Daily Note，从而我**可以通过「时间隧道」穿越到当时我读这本书的那一天**。另一方面，也可以**通过「空间隧道」穿越到我当时读这部分的具体内容是什么**，以及当时我的想法灵感是什么。

当我通过双向链接回到到原文对应段落的位置时，我又可以重新去查看它的上下文。**划重点，这里有个很重要的概念就在于[「上下文」](https://sspai.com/post/69387)。**当我根据自己的笔记无法得知当时我在阅读的是哪部分的时候，我可以通过双向链接的反向链接直接回到当时读书的这个出处，从而我能够去得知当时在书中原有的意思是什么。

这基本上就是跟**一个作者**在**一本书**里面交流的过程。其实我还有个想法，期望以一个主题阅读的方式去同时读**多本书**的，在《如何阅读一本书》中称之为「检视阅读」。如果说，我把**多本书**同时导入到 Roam Research 里面，比如说把认知科学的一些书全部放到一块儿呢？

![https://cdn.sspai.com/2022/05/02/3fc2a9663f92ca59c2ac26d5e7c99b3a.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/3fc2a9663f92ca59c2ac26d5e7c99b3a.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

我最近在读斯坦诺维奇教授的系列著作《机器人叛乱》、《超越智商》、《决策与理性》、《理商》；平克教授的《风格感觉》；特纳教授的《古典风格》；艾利克森教授的《刻意练习》及弗林教授的《智力是什么》、道伊奇教授的《重塑大脑，重塑人生》、约翰逊的《日常生活的神经科学》、科斯林教授的《上脑下脑》等书，阳志平老师集结的《追时间的人》、《认知尺度》和所著的《人生模式》等书。

其实在心理学、认知科学这些领域里面有很多类似概念的书，并且在学术上还会相互引用。如果说我们把**多个作者**和**多本著作**全部导入到 Roam Research 里面，是不是就像**把这些作者全部都拉了一个群，围着一个圆桌，让他们自由地根据一些关键词概念进行讨论。**

**哇，这就相当于在不同年代、不同地区的人物们以一种双向链接的形式，从而形成一个「跨时空」的交流。**

![https://cdn.sspai.com/2022/05/02/f01fb2f64407b486333aa0861327f7f0.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/f01fb2f64407b486333aa0861327f7f0.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

### **2. 高效产出 - 卡片盒、块引用**

接下来我再讲第二个部分就是高效产出。当我们在读书、记笔记之后，我更希望的是能够高效产出。我在记完笔记卡片之后，会将卡片放入卡片盒，通常来说我会将卡片盒一直显示在侧边栏，里面存放了非常非常多的卡片内容。

![https://cdn.sspai.com/2022/05/02/78dfe249dc0cabee0fbb94fc7e8bb56b.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/78dfe249dc0cabee0fbb94fc7e8bb56b.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

卡片笔记我会通过一个 `#关键词`+`{{[[embed]]: [[卡片标题]]}}` 的方式组织起来，**最最重要的是右边的引用符号，显示的数字代表着我有几个地方关联起了这张卡片，也就是说这些知识卡片就是相互链接的，形成了一个网状结构。**

![https://cdn.sspai.com/2022/05/02/article/912871400e0422fa04bfbdc4a804f348?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/912871400e0422fa04bfbdc4a804f348?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

那么，当我需要产出或者写文章的时候，我就可以利用「块引用」，非常方便地去创建草稿，再基于草稿内容，我就能非常方便地去修改最终的产出。

<iframe src="https://player.bilibili.com/player.html?aid=726118391&bvid=BV1NS4y1Y749&cid=588113838&page=1&t=1550" title="iframe embed" height="467px" width="100%" frameborder="0" allowfullscreen="" loading="lazy"></iframe>

点击跳转时间戳 25:50[https://www.bilibili.com/video/BV1NS4y1Y749?t=1550](https://www.bilibili.com/video/BV1NS4y1Y749?t=1550)

（同样，这一段的文字描述同样过于苍白，还是推荐大家去看我在视频中的演示，我尽力了，🤣）

比如说我要做一个分享，就会在卡片盒里面去寻找相关的卡片，可以通过 Alt + 鼠标直接把卡片内容从侧边栏的卡片盒拖入当前的项目页面。**借助于卡片盒，可以非常快速地生成我想分享的一些内容，然后再对内容进行一个改写。这样产出文章的速度是非常之快的，且符合「快写慢改」的认知写作模式。**

比如说我在 B 站做视频，也会采用这样的过程来快速产出这个大纲，再把它通过录屏的方式讲解出来，而产出的视频又可以[通过语音识别自动生成文稿](https://www.bilibili.com/video/BV1rq4y1i7Kr/)，再对其进行润色就能产生一篇高质量文章。

另外，在我平常做项目的时候，其实也会使用类似的非线性方式。比如说我最近新上手公司的技术栈，我之前是没有用过 GraphQL 和 Relay 相关的一些技术。**那么，首先我需要理解问题，再去确定它的验收条件，在一个非线性的模式下去边学边做 Learning by Doing。**在这个例子中，首先我去学习什么是 Suspense，什么是 Entrypoint 模式，在学习的过程中会遇到很多很棒的文章，又会边读边做笔记，从而就是这样磕磕碰碰「非线性」地去完成开发需求。

![https://cdn.sspai.com/2022/05/02/article/e57267cf3caf57c601536507cd615514?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/e57267cf3caf57c601536507cd615514?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

总结一个框架叫做「人、事、果」，因为在整个开发的过程当中，比如说我会提到一些人或者一些事，比如说我会在很多提到同事 @Matt，而我每次只需要进入到 [[@Matt]] 这个页面，Roam 就会自动汇总我总共跟他有哪些联系，比如说我哪天跟他有 1:1 会议，或者是我需要有什么东西想要寻求他的帮助，就可以批量地一次性解决。

其实，**「人、事、果」就是可以把人、事情和结果全部都链接起来**，就很像一些在线协同工具，像飞书、钉钉、Microsoft Teams 都在尝试将组织、文档和目标链接起来，但可能都没有做到真正的双向链接。这样的话，公司在评估项目结果的时候，就可以看到有哪些人参与进来了，然后有哪些事情（“一事一文档”）被完成了，并且这这些事情所对应的人和目标其实也是非常清晰的。

所以，双向链接在这样的使用场景下，是能够帮助我们去了解**关于某个项目、某个人或者某个目标更多的上下文，并且只有链接在一起，才构成了一个完整的上下文。**

### **最重要的是，积累模板：e.g. 九宫格**

另外就是做决策，我们讲高效产出或者叫输出，**「输出」并不一定是写文章或者是做视频，其实更大的作用是帮助你去做出更好的决策。**

我平常会积累一些模板，**每当我需要做一个决定，第一件事情应该去扩充自己的可选项。**面对选择，其实不只有 A 或者 B 这两个选项，而是有更多可能的选项。比如说当我思考直播分享要不要开摄像头，原本的答案可能只有「开」和「不开」这两个选项，但其实我还可以思考一下，摄像头是不是买好一点？或者我可以开美颜？甚至是换上正式一点的衣服？

当我思考了更多的可能性，最终的决定可能是「换上正式的衣服，再开一个美颜」。这样的话，是不是比我们最开始选择「开与不开」的某一个选项会更加好一点的？

![https://cdn.sspai.com/2022/05/02/article/bbc5d4c0b28f8acc24422396a19ad3a2?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/article/bbc5d4c0b28f8acc24422396a19ad3a2?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

**最重要的是，Roam Research 是一个思考工具，而思考需要模型或者模板的辅助。**我们在整个产出过程当中应该多去积累自己的一些知识晶体，也就是知识的沉淀，并且在实际中去不断运用它，迭代它。

我在 roam/templates 和 [roam/js/smartblocks](https://roamjs.com/extensions/smartblocks) 里面积累了很多的自动化模板，比如说写文章、晨间日记、每日计划、Weekly Review 或者是深度工作的时候，都可以有一些模板。这其实是一种**「思维算法」（ Algorithms of Thought），也是一种思考的自动化。**

这些积累的模板是我的一个外置辅助，也就是刚刚提到的思考工具，就像高速摄像机一样，能够辅助我去做更好的内容产出，或者说加速我做事的过程。

![https://cdn.sspai.com/2022/05/02/413374a412a0e7212705856319ea27d0.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/413374a412a0e7212705856319ea27d0.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

再举一个例子叫九宫格。通常来说我会用九宫格的方式去思考要完成的项目，这次演讲的过程也是用九宫格快速地做出来的，**「中心」就是我的主题**：「做一场贼有意思的直播」，再通过南东北西这样的方式**建立一个大纲式的「初心」**，最后从西南、西北、东北、东南四个角这样的方式来**补充细节，也就是「细心」**。

这样的思考框架，可以帮助我更快地去思考，并且考虑整个产出的全面性。九宫格是我觉得非常有用的思考方式之一，而**只要日常不断积累和迭代思考的模板，就能通过模板加速你输入和输出的效率。**

# **为什么是我？Believer of Tools for Thought**

在前文的九宫格规划截图中，我就提到了我最希望的是认识更多的人，能够跟大家互相去学习和交流。因为我非常喜欢的一句话，**「在成长的同时帮助他人成长，在学习的同时帮助他人学习」**。学习和知识管理是息息相关的，这也是我在最开始的时候提到我为什么对学习方法和知识管理这件事情非常的热忱。

![https://cdn.sspai.com/2022/05/02/c594f0a4c0a73954c4c13ab93dd1cf26.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/c594f0a4c0a73954c4c13ab93dd1cf26.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

而 Roam Research 就是目前最好用的双向链接笔记工具，没有之一。我也是买了它 5 年的 Believer 版本，500 美元也就是一次性付费人民币 3000 多，但我所获得的成长价值已经远超于此。

另外，我也做了很多相关的视频，有兴趣的话大家可以[去 B 站上关注一波](https://space.bilibili.com/37648256)。如果大家对知识管理感兴趣，想要跟我交流，也可以加我的[微信](https://jimmylv.noto.so/roam#98288bff51c646f6aa0899649cbc89cc)。另外我在[少数派](https://sspai.com/u/jimmylv/posts)上也有很多文章都是讲 Roam Research 以及思考工具和知识管理相关的，大家也可以去查看一下。

# **彩蛋：如果，浏览器能够直接内置双链笔记呢？**

我在探索双向链接的过程中，一直在纳闷**为什么浏览器就没有动力去实现网页之间的双向链接呢？**直到我看到了 [Beam](https://beamapp.co/)，我在[B 站视频](https://www.bilibili.com/video/BV1iY4y1Y7z5/)中介绍了这个内置双链笔记的新型浏览器，有一个非常顺畅的交互体验在于，按住 Alt 可以直接对网页内容进行摘录，并且可以选择摘录到某一个页面。

![https://cdn.sspai.com/2022/05/02/009b62a368ded4ab4d2cb0e7b2dfc29f.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/009b62a368ded4ab4d2cb0e7b2dfc29f.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

但是，我在视频中也吐槽了为什么 Beam 浏览器没有做到极致，是因为**当我们回到「被摘录的网页」时，Beam 在右侧并没有任何地方去显示我在针对这个网页所做的笔记。**它虽然建立了摘录笔记的快捷方式，但遗憾的是也未能做到反向的链接，而这其实是实现了至少在我个人层面，我觉得最有价值的一个功能。

如果现阶段有浏览器能够实现任意网页和任意笔记之间的双向链接，我愿称之为“Dream Browser”！目前来看，Microsoft Edge 的集锦功能最有希望，毕竟已经有了一定的基础。

**如果能够实现「个人」的笔记跟「互联网」的网页之间的互相链接，那么也就回到了我最初所讲的「上都计划」，Ted Nelson 的最终愿景可能算是在一定程度上得以实现。**

![https://cdn.sspai.com/2022/05/02/ad0677affff48a2db900ab240081d28e.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1](https://cdn.sspai.com/2022/05/02/ad0677affff48a2db900ab240081d28e.png?imageView2/2/w/1120/q/90/interlace/1/ignore-error/1)

这绝对是非常非常牛逼的一件事情，也是 Ted Nelson 在 1963 年最初的构想里面，就思考过和想要做的「一个记忆永远不会被遗忘的神奇地方」。

**只是，互联网是人类历史的一段弯路吗？**

# **参考资料**

- [视频版【双向链接的前世今生】上都计划与 Roam Research 思维工具](https://www.bilibili.com/video/BV1NS4y1Y749/?spm_id_from=333.788)
- [@少楠 - 🗄 个人知识管理指南 flomo 101](https://help.flomoapp.com/thinking/pkm.html)
- [@离线杂志 - Issue 23 上都计划——失落的超文本 - 知乎](https://zhuanlan.zhihu.com/p/22015922)
- [@Conor 革命性思维工具：Roam Research 白皮书 - 知乎](https://zhuanlan.zhihu.com/p/142356397)
- [“万维网之父”年过花甲创业，皆因对互联网现状的震惊和失望 - 知乎](https://zhuanlan.zhihu.com/p/49058762)
- [互联网是人类历史的一段弯路吗？-虎嗅网](https://www.huxiu.com/article/350854.html)
