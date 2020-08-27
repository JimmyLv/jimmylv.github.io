---
layout: post
title: Serverless 实战：打造个人阅读追踪系统
categories: [编程]
tags: [Serverless, Reading, Agile, PKM, GitHub, Diigo, JavaScript]
published: True
---

## 阅读习惯和个人知识管理体系

在互联网时代，知识可以说从未像如此一般廉价，但是**再好的知识若是对个人没有产生价值的话，那也只不过是一种信息噪音而已**。我在 [个人知识管理：知识的三种形态](https://blog.jimmylv.info/2015-10-09-three-types-of-knowledge/) 这篇文章中使用 **`材料 -> 资料 -> 知识`** 这样的路径来解释信息的流通，**如何方便快捷并且有效地收集材料，再将其整理转化为有价值的个人知识体系结构**，在这个信息严重碎片化的时代变得尤为重要。而在 [去伪存真的知识管理之路](https://blog.jimmylv.info/2016-09-16-sorting-out-knowledge-from-information/) 一文中也详细阐述了如何将网络上的碎片化文章纳入统一的稍后阅读体系，比如说有时候在朋友圈看到一篇好文章，但暂时没时间直接看，或是这篇文章值得再读一遍，细读一遍，那么我就会将其存入稍后阅读工具即 [Instapaper](https://www.instapaper.com) 当中，诸如此类的还有 [Pocket](https://getpocket.com/)、[收趣](https://shouqu.me/)等等。

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2016/1474027837640.png)

### 稍后阅读永远读不完的痛点：缺乏追踪

随着时间的推移，Instapaper 里面的文章将会变得越来越多，就像我们在代码中所注释的 `TODO:` 可能就变成了 `Never Do`，稍后读也是一样地被人广为诟病：Read it Later = Read Never。其实我发现文章堆积的一个永恒痛点就是**没有有效的方式追踪自己的阅读需求与能力，其核心原因就是因为读完的速度赶不上添加的速度**。从而没办法可视化出来评估自己的阅读进度，合理安排阅读计划，也就没办法给予自己适当的奖励，进而失去了阅读的动力。

上回博客大赛写过一篇 [基于 GitHub 的敏捷学习方法之道与术](https://blog.jimmylv.info/2016-12-04-agile-learning-based-on-github-issues/)，其中提到使用 GitHub Issue 来管理自己的学习计划，从而就又产生了这么一个想法，就是将我的稍后阅读列表跟 GitHub 结合起来，使用 ZenHub 丰富的图表功能将阅读体系进行追踪与可视化。

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2016/1480844770670.png)

### 可视化 Cumulative Flow Diagram

首先让我们直接来看一下最终的具体效果图，在这里简单介绍一下 CFD（Cumulative Flow Diagram）即累积流图，这是一种能让你快速了解项目或产品工作概况的图表，关注的是价值的流动效率，价值的流动最直接的体现就是需求卡片在各个队列中的数量。

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499007659821.png)

里特定律（Little’s law）告诉我们**交付时间（Delivery time）依赖于在制品数量（Work In Progress, WIP）。WIP 是指所有已经初始但还未完成的工作，例如：所有在分析（Analysis）与完成（Done）之间的工作**。必须要首先留意的就是 WIP，**如果 WIP 增加了，交付日期就会有风险。**ZenHub 所提供的 Release Report 中最有效果的就是**预测完成日期**，总之就是跟敏捷方法结合起来，使用项目管理的方式来管理自己的阅读列表，当然其实我也在进一步的探索之中，但是每次看看到这个走势图就能对自己的阅读列表有了更多的掌控和理解，至少减少了文章堆积时所产生的焦虑感。

## IFTTT 与 Serverless 架构

那么这背后是怎么通过 APIs 来实现的呢？当然，在真正进入正题之前我们先来简单介绍一下 Serverless 架构。Serverless 指的是在构建 Web 应用程序的时候，而不用担心如何配置服务器，但是这并不意味着应用程序不会在服务器上运行，而是说服务器的管理都可以尽可能地交给相应的云平台，从而最大程度地减轻开发人员的部署与配置工作。与之对应的一个名词可能就是 Function As a Service（FAAS），由 AWS Lambda 这个命名上就能想到，当我们在构建 Serverless 架构时，实际上我们是在写一个个的 Function 即函数而已。

![](http://insights.thoughtworkers.org/wp-content/uploads/2017/05/0-lambda2.png)

### 流程化：APIs 即服务

首先让我们来介绍一下 [IFTTT](https://ifttt.com/discover) 即 if this then that 的缩写。通俗的来讲，IFTTT 的作用就是如果触发了一件事，则执行设定好的另一件事。所谓的「事」，指的是各种应用、服务之间可以进行有趣的连锁反应。IFTTT 的宗旨是 Put the internet to work for you （让互联网为你服务）。用户可以在 IFTTT 里设定任何一个你需要的条件，当条件达到时，便会触发下一个指定好的动作。**它就像是一座神奇的桥梁，能连接我们日常所用的各种网络服务。**

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499008946205.png)

而我们现在遇到的这个串联式的场景下是特别合适 Serverless 架构的，使用 IFTTT 并且将它跟 Instapaper 账号绑定，**设置文章添加、高亮、归档等行为作为 trigger 条件，然后将相关信息发到某一个指定 API endpoint。**先把操作 GitHub Issue 和 ZenHub 的各种 APIs 准备好，结合 IFTTT 的触发器与 Marker 工具能够非常方便地与之相集成，最后我们可以产出这样一个 APIs 交互流程图：

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499010393382.png)

### 初始化 Webtask 项目

虽然 AWS Lambda 是 Serverless 架构的典范，但它也有一些槽点以及我觉得已经被人说得足够多了，所以我们今天就来尝尝鲜，着重介绍和使用一下 Webtask。推出该服务的这家公司 [Auth0](https://auth0.com/) 你可能没有听说过，但你一直知道大名鼎鼎的 JWT 即 JSON Web Token，这是一种开放标准（[RFC 7519](https://tools.ietf.org/html/rfc7519)），通常被运用在身份验证（Authentication）和信息交换等需要安全传输信息的场景下。

首先让我们来安装工具初始化项目以及[注册账号](https://webtask.io/)，然后使用电子邮件进行登录：

```bash
npm install -g wt-cli

wt init <YOUR-EMAIL>
```

创建项目目录，添加 `index.js` 文件并添加以下内容：

```js
module.exports = function (cb) {
  cb(null, 'Hello World')
}
```

然后在该目录中运行以下命令进行应用程序部署之后，点击控制台中输出的 URL 就能看到编程史上最有名气没有之一的 `HelloWorld!`：

```bash
wt create index
```

![](https://cdn.scotch.io/10/T0RwEO5LQWu15i3UFjKu_Screen%20Shot%202017-04-26%20at%201.27.43%20PM.png)

### Webtask 的上下文绑定

Webtask 有一个实用工具 `webtask-tools` 可以将应用程序绑定到 Webtask 上下文，让我们将之前所 export 的简单函数修改为绑定到 Webtask 的 Express app，然后就可以愉快地使用 Express 进行开发，一切就又回到了熟悉的味道：

```js
const Express = require('express')
const Webtask = require('webtask-tools')
const bodyParser = require('body-parser')
const app = Express()

app.use(bodyParser.urlencoded({ extended: false }))
app.use(bodyParser.json())

require('./routes/reading')(app)

module.exports = Webtask.fromExpress(app)
```

Webtask context 还有一个非常重要的用途就是在部署时传输一些敏感信息比如安全 Token，从而在应用程序当中可以随时使用它们。下面的部署命令中 `--secret` 后面所传入的 `ACCESS_TOKEN` 都会在后续与 GitHub 和 ZenHub APIs 交互时被用到。

```bash
wt create index --bundle --secret GITHUB_ACCESS_TOKEN=$GITHUB_ACCESS_TOKEN --secret ZENHUB_ACCESS_TOKEN=$ZENHUB_ACCESS_TOKEN --secret ZENHUB_ACCESS_TOKEN_V4=$ZENHUB_ACCESS_TOKEN_V4
```

```js
# ./routes/reading.js

module.exports = (app) => {
  app.post('/reading', (req, res) => {
    const { GITHUB_ACCESS_TOKEN, ZENHUB_ACCESS_TOKEN, ZENHUB_ACCESS_TOKEN_V4 } = req.webtaskContext.secrets
    }
}
```

## 使用 GitHub Issue 追踪阅读列表

### IFTTT：添加 Instapaper 文章后自动创建 GitHub Issue

得益于 IFTTT 非常丰富的第三方服务，IFTTT 可以直接创建 Instapaper 与 GitHub Issue 相集成的 Applet：[If new item saved, then create a new issue - IFTTT](https://ifttt.com/applets/54307045d-if-new-item-saved-then-create-a-new-issue)，就可以在当 Instapaper 新增文章的时候，自动在 GitHub 所指定的仓库 [Issues · JimmyLv/reading](https://github.com/JimmyLv/reading/issues/) 中创建一个新的 Issue 并添加相应的标题、链接以及描述等相关信息。

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499013190840.png)

但仅仅只是添加一个 Issue 还不够，这时候还需要将这个 Issue 加入到指定的 Milestone 从而利用 ZenHub 的图表功能，使用 GitHub 的 Webhooks 功能就可以轻松帮我们把 Issue 更新的状态转发到我们所指定的 webtask 地址：

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499016439751.png)

### 使用 GitHub Webhook 更新 Issue 的 Milestone

所以我们的 Webtask 就需要处理 GitHub Webhook 所转发的 POST 请求，其中包括了 Issue 的类型和内容，在拿到 `'opened'` 即新建 Issue 类型的 action 之后我们可以对其进行相应的处理即添加到 Milestone 当中：

```js
if (action === 'opened') {
  fetch(`${url}?access_token=${GITHUB_ACCESS_TOKEN}`, {
    method: 'PATCH',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      milestone: 1,
    }),
  })
    .then(() => console.info(`[END] set milestone successful! ${html_url}`))
    .catch((err) => res.json(err))
}
```

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499017955460.png)

结合 ZenHub 的 Milestone 燃尽图我们可以清晰地看到剩余阅读量的多少，并且能够跟理想中的阅读速度进行对比，从而判断自己什么时候能够全部读完所有的文章。可能有些小伙伴看到这里会有所疑问了，这些所谓的 Story Point 是从哪儿来的呢？那么接下来就要提到我们将要集成的 ZenHub API 了。

## 集成 ZenHub API：阅读可视化

### 更新 Issue 的估点和 Release

GitHub Issue 的任何变动都会触发 Webhook，从而我们可以在 Issue 被加入 Milestone 之后再处理下一个 `'milestoned'` action，即：

```js
if (action === 'milestoned') {
  fetch(
    `https://api.zenhub.io/p1/repositories/${REPO_ID}/issues/${number}/estimate?access_token=${ZENHUB_ACCESS_TOKEN}`,
    {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ estimate: 1 }),
    },
  )
    .then(() => {
      console.info(`[END] set estimate successful! ${html_url}`)
      return fetch(
        `https://api.zenhub.io/v4/reports/release/591dc19e81a6781f839705b9/items/issues?access_token=${ZENHUB_ACCESS_TOKEN_V4}`,
        {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body: `add_issues%5B0%5D%5Bissue_number%5D=${number}&add_issues%5B0%5D%5Brepo_id%5D=${REPO_ID}`,
        },
      )
    })
    .then(() => console.info(`[END] set release successful! ${html_url}`))
    .catch((err) => res.json(err))
}
```

这样我们就完成了对每个 GitHub Issue 的估点，以及设置了对应的 Release，接下来所有的变动都将体现在 ZenHub 的图表当中。

### 归档 Instapaper 文章后关闭 GitHub Issue

说了这么多，不要忘了**整个阅读系统最最核心的部分依然还是要「阅读」啊！**在众多的稍后阅读工具中我无比喜爱 Instapaper 并迟迟没有转到 Diigo 的原因就在于它优秀、简洁、纯粹的阅读体验，让人可以专注在阅读本身这件事情上，在被 Pinterest 收购之后更是将所有的诸如全文搜索、无限高亮/笔记、速读等 Premium 功能都变成了免费，岂不美哉？

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499019018150.png)

那么在完成阅读归档之后，最后一步就是在 GitHub 当中将 Issue 关闭掉，但是 IFTTT 的 GitHub 服务并没有提供 close Issue 的接口，于是乎我们就只有利用 IFTTT 新推出的 Maker 自己创建一个，即 Instapaper 规划作为一个 IF trigger，然后 Maker 用于发出一个 Web 请求，可以是 GET ,PUT, POST, HEAD, DELETE, PATCH 或者 OPTIONS 之中的任何一种，你甚至还可以制定 Content Type 和 Body。

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499019483077.png)

```js
app.get('/reading', (req, res) => {
    const { GITHUB_ACCESS_TOKEN } = req.webtaskContext.secrets
    const title = req.query.title
    let keyword = encodeURIComponent(title.replace(/\s/g, '+'))

    fetch(`https://api.github.com/search/issues?q=${keyword}%20repo:jimmylv/reading`)
      .then(response => response.json())
      .then(data => {
        console.info('[RESULT]', data)
        if (data.total_count > 0) {
          data.items.forEach(({ url, html_url }) =>
            fetch(`${url}?access_token=${GITHUB_ACCESS_TOKEN}`, {
              method: 'PATCH',
              headers: { 'Content-Type': 'application/json' },
              body: JSON.stringify({ state: 'closed' }),
            })
              .then(() => console.info(`[END] issue closed successful! ${html_url}`))
              .catch(err => res.json('error', { error: err })))
          res.json({ message: 'Closed issue successful!' })
        }
    })
}
```

上述代码就可以用于处理 IFTTT Marker 所发送的 GET 请求，我们从 query 参数中取到文章标题之后再去搜索相对应的 Issues，再通过 GitHub API 将其关闭。

而与此同时，我们在文章的阅读过程中，有时候也会想要对文章中的亮点部分进行高亮，甚至评论自己的一些想法和总结，那我们也可以用过 IFTTT Marker 和 Webtask 的套路添加至 GitHub Issues 的 comments 当中，具体的代码就不贴了，更多内容都已经放在我的 GitHub 上：[JimmyLv/demo.serverless-mern](https://github.com/JimmyLv/demo.serverless-mern)。

## 总结与后续计划

随着时间的推移，日常你只需要在 Instapaper 添加文章、阅读文章即可，而背后利用 Serverless 所搭建的整套阅读追踪系统将会任劳任怨的帮你记录下所有的踪迹和笔记，你只需要在特定的时候定期 review、分析阅读的效果与预测效果，与此同时结合自己的时间统计系统，可以持续不断地改进自己的阅读目标与阅读计划。

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499020636682.png)

最后再来考虑一下后续计划，就比如说我现在只是简单把 Instapaper 中高亮部分和阅读笔记作为评论放到 GitHub 的 comments 里面，但是最终我需要把它收藏到自己的个人知识库即 [Diigo](https://diigo.com)，这也是可以通过 API 自动实现的，以及最终需要被刻意记忆的部分还需要与 [Tinycards](https://tinycards.duolingo.com/) API 相集成，对抗艾宾浩斯遗忘曲线。

与此同时呢，还需要把估点根据不同的文章类型和难易程度具体划分一下，而不是现在简简单单的 1 点，比如说 Instapaper 也有根据字数所预测的阅读分钟数，以及根据中文或英文、技术或~~鸡汤~~等不同种类文章阅读难度进行区分，从而使整套追踪系统更具有效性与参考性。

![](https://cdn.jsdelivr.net/gh/jimmylv/images/2017/07/1499007659821.png)

## 一些参考资料

- [基于 GitHub 的敏捷学习方法之道与术 - 吕立青的博客](https://blog.jimmylv.info/2016-12-04-agile-learning-based-on-github-issues/)
- [Build a Serverless MERN Story App With Webtask.io -- Zero to Deploy: 1 ― Scotch](https://scotch.io/tutorials/build-a-serverless-mern-story-app-with-webtask-io-zero-to-deploy-1)
- [触发你的智能生活：IFTTT 入门 - 少数派](https://sspai.com/post/25270)
- [利用 IFTTT Maker DIY 你的 Applet - 少数派](https://sspai.com/post/39243)
- [个人知识管理：知识的三种形态 - 吕立青的博客](https://blog.jimmylv.info/2015-10-09-three-types-of-knowledge/)
- [用 GTD 的方法结束稍后读 - 少数派](https://sspai.com/post/33933)
- [不断革新，不断改进：去伪存真的知识管理之路 - 吕立青的博客](https://blog.jimmylv.info/2016-09-16-sorting-out-knowledge-from-information/)
- [卡片状态累积流图（Cumulative Flow Diagram – CFD ） – 效率云](http://xiaolvyun.baidu.com/docs/knowledge-base/788)
