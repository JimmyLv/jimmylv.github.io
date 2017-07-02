---
layout: post
title: Serverless 实战：打造个人阅读追踪系统
categories: [编程]
tags: [Serverless, Reading, Aglie, PKM]
published: False

---

## 阅读习惯和个人知识管理体系

在互联网时代，知识可以说从未像如此一般廉价，但是**再好的知识若是对个人没有产生价值的话，那也只不过是一种信息噪音而已**。我在 [个人知识管理：知识的三种形态](https://blog.jimmylv.info/2015-10-09-three-types-of-knowledge/) 这篇文章中使用 **`材料 -> 资料 -> 知识`** 这样的路径来解释信息的流通，**如何方便快捷并且有效地收集材料，再将其整理转化为有价值的个人知识体系结构**，在这个信息严重碎片化的时代变得尤为重要。而在 [不断革新，不断改进：去伪存真的知识管理之路](https://blog.jimmylv.info/2016-09-16-sorting-out-knowledge-from-information/) 一文中也详细阐述了如何将网络上的碎片化文章纳入统一的稍后阅读体系，比如说有时候在朋友圈看到一篇好文章，但暂时没时间直接看，或是这篇文章值得再读一遍，细读一遍，那么我就会将其存入稍后阅读工具即 [Instapaper](https://www.instapaper.com) 当中，诸如此类的还有 [Pocket](https://getpocket.com/)、[收趣](https://shouqu.me/)等等。

![](https://o7mw3gkkh.qnssl.com//images/2016/1474027837640.png)

### 稍后阅读永远读不完的痛点：缺乏追踪

随着时间的推移，Instapaper 里面的文章将会变得越来越多，就像我们在代码中所注释的 `TODO:` 可能就变成了 `Never Do`，稍后读也是一样地被人广为诟病：Read it Later = Read Never。其实我发现文章堆积的一个永恒痛点就是**没有有效的方式追踪自己的阅读需求与能力，其核心原因就是因为读完的速度赶不上添加的速度**。从而没办法可视化出来评估自己的阅读进度，合理安排阅读计划，也就没办法给予自己适当的奖励，进而失去了阅读的动力。

上回博客大赛写过一篇[基于 GitHub 的敏捷学习方法之道与术](https://blog.jimmylv.info/2016-12-04-agile-learning-based-on-github-issues/)，其中提到使用 GitHub Issue 来管理自己的学习计划，从而就又产生了这么一个想法，就是将我的稍后阅读列表跟 GitHub 结合起来，使用 ZenHub 丰富的图表功能将阅读体系进行追踪与可视化。

![](https://o7mw3gkkh.qnssl.com/images/2016/1480844770670.png)

### 可视化 Cumulative Flow Diagram

首先让我们直接来看一下最终的具体效果图，在这里简单介绍一下 CFD（Cumulative Flow Diagram）即累积流图，这是一种能让你快速了解项目或产品工作概况的图表，关注的是价值的流动效率，价值的流动最直接的体现就是需求卡片在各个队列中的数量。

![](https://o7mw3gkkh.qnssl.com/images/2017/07/1499007659821.png)

里特定律（Little’s law）告诉我们**交付时间（Delivery time）依赖于在制品数量（Work In Progress, WIP）。WIP 是指所有已经初始但还未完成的工作，例如：所有在分析（Analysis）与完成（Done）之间的工作**。必须要首先留意的就是 WIP，**如果 WIP 增加了，交付日期就会有风险。**ZenHub 所提供的 Release Report 最有效果就是**预测完成日期**，总之就是跟敏捷方法结合起来，用项目管理的方式来管理阅读列表。当然其实我也在进一步的探索之中，但是每次看看到这个走势图就能对自己的阅读列表有了更多的掌控和理解，至少减少了我看到堆积文章数量时所产生的焦虑感。

## Serverless 架构

那么这背后是怎么通过 APIs 来实现的呢？当然，在真正进入正题之前我们先来简单介绍一下 Serverless 架构。Serverless 指的是在构建 Web 应用程序的时候，而不用担心如何配置服务器，但是这并不意味着应用程序不会在服务器上运行，而是说服务器的管理都可以尽可能地交给相应的云平台，从而最大程度地减轻开发人员的部署与配置工作。与之对应的一个名词可能就是 Function As a Service（FAAS），由 AWS Lambda 这个命名上就能想到，当我们在构建 Serverless 架构时，实际上我们是在写一个个的 Function 即函数而已。

![](http://insights.thoughtworkers.org/wp-content/uploads/2017/05/0-lambda2.png)

### 流程化：APIs 即服务

首先让我们来介绍一下 [IFTTT](https://ifttt.com/discover) 即 if this then that 的缩写。通俗的来讲，IFTTT 的作用就是如果触发了一件事，则执行设定好的另一件事。所谓的「事」，指的是各种应用、服务之间可以进行有趣的连锁反应。IFTTT 的宗旨是 Put the internet to work for you （让互联网为你服务）。用户可以在 IFTTT 里设定任何一个你需要的条件，当条件达到时，便会触发下一个指定好的动作。**它就像是一座神奇的桥梁，能连接我们日常所用的各种网络服务。**

![](https://o7mw3gkkh.qnssl.com/images/2017/07/1499008946205.png)

而我们现在遇到的这个串联式的场景下是特别合适 Serverless 架构的，使用 IFTTT 并且将它跟 Instapaper 账号绑定，设置好添加、归档等行为作为 trigger 条件，然后将相关信息发到某一个指定 API endpoint。先把操作 GitHub Issue 和 ZenHub 的各种 APIs 准备好，结合 IFTTT 的触发器与 Marker 工具能够非常方便地与之相集成，最后我们可以产出这样一个 APIs 交互流程图：

![](https://o7mw3gkkh.qnssl.com/images/2017/07/1499010393382.png)

### 初始化 Webtask 项目

虽然 AWS Lambda 是 Serverless 架构的典范，但它也有一些槽点以及我觉得已经被人说得足够多了，所以我们今天就来尝尝鲜，着重介绍和使用一下 Webtask。推出该服务的这家公司 [Auth0](https://auth0.com/) 你可能没有听说过，但你一直知道大名鼎鼎的 JWT 即 JSON Web Token，这是一种开放标准（[RFC 7519](https://tools.ietf.org/html/rfc7519)），通常被运用在身份验证（Authentication）和信息交换等需要安全传输信息的场景下。

首先让我们来安装工具初始化项目以及[注册账号](https://webtask.io/)，然后使用电子邮件进行登录：

```bash
npm install -g wt-cli

wt init <YOUR-EMAIL>
```

创建项目目录，添加 `index.js` 文件并添加以下内容：

```
module.exports = function (cb) {
  cb(null, 'Hello World!');
}
```

然后在该目录中运行以下命令进行应用程序部署之后，点击控制台中输出的 URL 就能看到编程史上最有名气没有之一的 `HelloWorld!`：

```
wt create index
```

![](https://cdn.scotch.io/10/T0RwEO5LQWu15i3UFjKu_Screen%20Shot%202017-04-26%20at%201.27.43%20PM.png)

## 使用 GitHub Issue 追踪阅读列表

### IFTTT：添加 Instapaper 后自动创建 GitHub Issue

得益于 IFTTT 非常丰富的第三方服务，IFTTT 可以直接创建 Instapaper 与 GitHub Issue 相集成的 Applet：[If new item saved, then create a new issue - IFTTT](https://ifttt.com/applets/54307045d-if-new-item-saved-then-create-a-new-issue/edit)，就可以在当 Instapaper 新增文章的时候，自动在 GitHub 所指定的仓库创建 [Issues · JimmyLv/reading](https://github.com/JimmyLv/reading/issues/)

![](https://o7mw3gkkh.qnssl.com/images/2017/07/1499013190840.png)

至于最后怎么去处理这样一个请求，然后就进入到第一个例子，即 API 的设计，与结合 Express 是怎么玩的，开始贴代码！

### 使用 GitHub Hook 更新 Issue 的 Milestone 

然后当然是秀一秀优秀的 GitHub API，

然后在添加 Issue 之后还需要跟 ZenHub 相结合起来，。所以就需要把我们的 Issue 的估点和 Release 给设置好。在这样一个场景下最好引入 GitHub Hook的概念，然后就完美的把这些事情结合起来了，在这里要讲一下 hook 是怎么工作的。

## 集成 ZenHub API：阅读可视化

### 更新 Issue 的估点和 Release

介绍 ZenHub 所提供的丰富图标功能

### 归档 Issue 与效果分析

然后再讲一下归档的API怎么写，地方就简单过一下代码就好，因为基本原理已经讲清楚了。

然后分析阅读的效果与预测效果，顺便提一下自己的时间统计系统

## 后续计划

最后再来考虑一下后续计划，就比如说我把高亮部分作为评论放到 GitHub 的 comments 里面，但是最终我想把它收藏到自己的个人知识库即 Diigo 里面，但是还没有完成，以及刻意记忆部分所用到的 Tinycards API。

与此同时呢，所以还想把估点根据不同的文章类型和难易程度具体划分一下，而不是现在简简单单的 1 点。

## 参考资料

- [Build a Serverless MERN Story App With Webtask.io -- Zero to Deploy: 1 ― Scotch](https://scotch.io/tutorials/build-a-serverless-mern-story-app-with-webtask-io-zero-to-deploy-1)
- [触发你的智能生活：IFTTT 入门 - 少数派](https://sspai.com/post/25270)
- [用 GTD 的方法结束稍后读 - 少数派](https://sspai.com/post/33933)
- [卡片状态累积流图（Cumulative Flow Diagram – CFD ） – 效率云](http://xiaolvyun.baidu.com/docs/knowledge-base/788)





