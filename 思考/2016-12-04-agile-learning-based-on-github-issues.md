---
layout: post
title: 基于 GitHub 的敏捷学习方法之道与术
categories: [思考]
tags: [学习, GitHub, 成长, 敏捷, 知识]
published: True

---

> 「持续行动，持续反思，持续进步。」—— via. 敏捷学习宣言

## 前言

### 对时间的敬畏

> 需要好多年才能懂得，最好不是去震惊世界，而是要像易卜生所说的，生活在世界上。

我们都一样，渴望着建树功勋、改变世界，可是伴随着年岁的增长，却发现想要实现的梦想依然那么遥远，而时间却依然残酷得流逝着，不会仅仅因为「你」而发生丝毫的改变。如《奇特的一生》当中所言，我对时间始终充满着敬畏之心，最好的方式也不过是奢求时间能够跟自己做朋友，伴随着我这也许注定朴实无华的一生，共同成长。

在我们的一生所能做的事情里边儿，睡眠占去 1/3，此生只剩 2/3，除去非做不可的[基本生活维护成本](http://blog.jimmylv.info/2015-09-05-periodically-anxiety/#title0)过后，剩下的时间要么选择浪费而荒度此生，要么选择目标而奋力向前，让这一生不留遗憾。Follow your heart，你需要找到一些愿意为其付诸终身的「目标」，以这样的姿态「生活在这世界上」。

### 敏捷与个人成长

就像软件开发一样，一个人的成长也应该要有自己的方法论。人的一生若是顺风顺水一成不变的话，那未免太无趣了，正是由于世界的未知在等着我们去探索，不一样的经历才会让人感到惊喜和有趣。想做的事情永远都不会嫌多，就像柳比歇夫最开始是研究生物学的，却在科学的道路上越走越远，进而研究起了数学、物理、哲学，甚至于美学，而更关键的是，他在每一方面都做出了很大贡献并且留下了诸多著作。

时间充当着 Product Owner 的角色在不断着向你提出各种各样的需求，敏捷当中最重要的一大前提就是「拥抱变化」，而在「[记录时间这件小事儿](https://github.com/JimmyLv/jimmylv.github.io/issues/85)」里面我提到的 GTD 流程便可以用于处理这源源不断的需求，即收集、整理、执行、回顾，对应到敏捷当中的几大会议显然也可以由个人完成，自己就是自己的 IM & PM，当然也是 BA & Dev & QA。（当然不用担心人格分裂，😂）

## 实践之术

> 我都没想到写着写着怎么就把开头写成了鸡汤文，`[捂脸](./wechat/emoji.jpg)`。但是咧，如果说前面的讲的是「道」，那么接下来就会具体到基于 GitHub 的「术」，即各种实践。

首先呢，让我们从需求出发，从市面上来寻找一款符合敏捷的学习软件，别想了，当然是没有的。对于一名程序猿来说，**最理想的答案其实就是 GitHub**，作为全球最大的程序猿~~交友~~网站，GitHub 本身以及围绕 GitHub 的各种插件使得其项目管理能力其实远比你所能想象的厉害得多。

* 收集：需求无时无刻，无处不在，anywhere anytime
* 整理：as BA 即分析，Elaboration & Estimation & IPM => 确定 MVP & Efforts
* 执行：as Dev & QA，Developing & Testing & Review/Sign-Off
* 回顾：Retrospection，Introspection，持续反思，持续进步…

### 通过 GitHub Issues 收集需求

首先你可以给自己建一个 GitHub 仓库作为主页，比如我的 [JimmyLv/jimmylv.github.io: Agile Learning based on GitHub issues](https://github.com/JimmyLv/jimmylv.github.io) 其实最开始就是从[个人博客](http://blog.jimmylv.info/)的主仓库发展而来。那么，如何快速得收纳自己的想法呢？以解决问题为导向，当然就是有什么需求就直接给自己的 repo 建一个 issue 作为 Story Card，然后了却这个需求的最终形态就是 close 掉这个 Issue，比如我要写这篇文章就始于这个 issue：[基于 GitHub 的敏捷学习方法总结 · Issue #36 · JimmyLv/jimmylv.github.io](https://github.com/JimmyLv/jimmylv.github.io/issues/36)。

![GitHub README](//o7mw3gkkh.qnssl.com/images/2016/1480841415310.png)

#### GitHub issues 的进阶用法

与此同时，新建 issue 还有更高级的用法，也就是通过 [ISSUE_TEMPLATE](https://help.github.com/articles/creating-an-issue-template-for-your-repository/) 这样一个模板来新建某个 issue，从而更快地定位问题所在和解析自己的想法，最主要的是能够输出更具体的 TODOs，即下一步行动的具体内容，这个还会在后面详细解释的。

![New issue](//o7mw3gkkh.qnssl.com/images/2017/03/1489125677512.png)

- issue 和 issue 之间是可以通过 `#` 相互连接的，甚至可以跨仓库，被 reference 的 issue 也会出现在另外一边的 issue 里面；
- 而通过 `#!` 符号是可以在 comments 里面直接新建一个 issue 的，这在思维爆炸的时候来得特别爽快；
- 你还可以随意艾特你的小伙伴们 @linesh-simplicity @Yaowenjie ，互相监督、互相学习或者给出 Constructive Feedback 之类的，😂；
- 更甚至于，若是在 Intellij 里面关联了 GitHub，就可以在 git commit 信息里面直接看到你所要关联的 issues 列表了。

这种方式仿佛学习中的大脑，神经网络被连通了的感觉。

![Intellij & Issues](//o7mw3gkkh.qnssl.com/images/2016/1480844039076.png)

#### 移动端的解决方案

而在移动端则可以通过 [GitDo](http://gitdo.io/) 这个 App 来轻松新建和管理自己的 Issues，没错，就是有人把 GitHub issues 做成了一个 Todos 类 App，还做得很漂亮功能很完善。只可惜不知道这软件最近为啥被下降了，伤感，我就又重新把滴答清单（TickTick）作为自己的万能收集箱了，之后再把比较重要的、需要进一步追踪的事项添加到 GitHub issues 里面来。

![GitDo](https://cloud.githubusercontent.com/assets/4997466/20562832/b1916908-b1c0-11e6-9961-cb5d65ab893a.png)

### 整理你的 GitHub Issues

大胆地把 issues 作为你的个人需求列表吧，需要解决的问题可以大到做一个开源项目，或者小到读一本书、写一篇文章。对于比较大的需求，你还可以将其转化为 Epic 然后把拆分过后的小 issues 们加入到这个列表里面来。

![Epic](//o7mw3gkkh.qnssl.com/images/2016/1480845918534.png)

而 GitHub (with [ZenHub](https://www.zenhub.com/)) 强大的 issues 管理能力绝对会让你的迭代工作变得井井有条，使用 GitHub 新出的 [Projects](https://github.com/JimmyLv/jimmylv.github.io/projects/1) 特性或者使用 ZenHub 的 [Boards](https://github.com/JimmyLv/jimmylv.github.io/issues/100#boards?repos=13273392) 应该就可以让你瞬间有了日常敏捷工作的感觉了吧！

![ZenHub piepline](//o7mw3gkkh.qnssl.com/images/2016/1480844770670.png)

### 计划与执行具体任务

#### 制定迭代计划

首先呢，让我们来新建一个 [Milestone](https://github.com/JimmyLv/jimmylv.github.io/milestones?state=open) 来制定计划，也就是决定在一个 Iteration 里面你需要完成哪些 issues。在这里我所制定的阶段性计划周期为一个月，当然你也可以勤快一点以 2 周作为一个 Iteration，享受一下自己的计划要完不成了这个 Milestone 就要废了，没法向「时间」这个一生的朋友交付所有需求的快感吧，🙂

![Milestone](https://cloud.githubusercontent.com/assets/4997466/20562662/b6ccb2e8-b1bf-11e6-9702-755d137ab570.png)

当然咯，一般我会在月初做计划的时候给自己准备专门的时间来做 Elaboration，把 Backlog 里面的卡拖到 Rethink/Plan 这一列，然后经过分析和详细输出 TODOs 以及所对应的估点 points 之后便可以将其拖到 Ready For Todo 了，一般我给自己估的点数就是完成这件事情所需要的时间，一小时即对应一个 point。

![Iteration](//o7mw3gkkh.qnssl.com/images/2016/1480845577392.png)

这样你就可以愉快得选择 Filter Issues by Milestone 专注于当前 Iteration，专注于 In Progress 这一列所要做的事情，并且垂涎于 Ready For Todo 里面将要做的事情，每次做完还可以放到 Review/SignOff 里面写写对这件事情的总结和感想什么的，每次挪卡都充满了敏捷的仪式感（认真脸）。

#### 进度的把控

GitHub 在 issues 里面直接集成了 Markdown 的 TODO 语法，甚至于可以在渲染过后直接拖动某个 item 进行排序，而且前面的勾选项可以直接打勾 ☑️ 标记为完成，而且完成之后这个 issue 还能直接显示完成进度；前面所提到的 Epic 也能直接显示子 issues 的完成情况即 closed 比例，两者结合起来简直不能再美好，😂

比如说拿来作为读书列表的记录就很不错，每本书作为一个 issue 还可以把章节划分为具体的 TODOs，结合估点可以追踪自己看书的进度和速度，顺便在 comments 底下做个笔记也不错啊！

![TODOs](//o7mw3gkkh.qnssl.com/images/2016/1480846952139.png)

#### 专注当下

而且 ZenHub 还提供了一个基于 GitHub Issues 的 Todo List，你可以只用关注 Today 这一个列表，专心于当前要完成的任务。而且更有趣的是这个 list 可以加入 GitHub 的任何 issues，也就是说是全局的，所以你就可以加入很多在 GitHub 上通过 issues 写的 blog，比如徐飞的这篇文章[流动的数据——使用 RxJS 构造复杂单页应用的数据逻辑 · Issue #38 · xufei/blog](https://github.com/xufei/blog/issues/38)，被我加入到了 Reading 的列表当中。

![Things to do](//o7mw3gkkh.qnssl.com/images/2016/1480849332535.png)

与此同时我还会使用 [Toggl](https://toggl.com/) 来记录每个 issue 具体实施的时间，以便于在时间花费上能够获得及时的反馈。这样做会让你真切地感受到时间的流逝，而在回顾记录的时候也能够进行总结分析，从而在下一次的计划当中能够更精确地预估时间（点数）。比方说这篇文章我估了 5 个点现在已经写了 4.5 hours 了，不过这是另外一个大话题，可以参考 [记录时间这件小事儿](https://github.com/JimmyLv/jimmylv.github.io/issues/85) 这个 issue。

![Toggl](//o7mw3gkkh.qnssl.com/images/2016/1480858232002.png)

### 迭代回顾与总结分析

ZenHub 也提供了 Burndown 和 Velocity tracking 图，可以得出这个迭代总体的完成情况，看看跟预期有何不同；也可以跟其他迭代进行对比，看看有何不同的地方，然后进行下一步的具体分析。

![Burndown](//o7mw3gkkh.qnssl.com/images/2016/1480848185821.png)

还可以根据 GitHub 和 Toggl 里面的数据进行汇总和分析，下面这个表格就是我在 11 月这个迭代完成后一部分 issues 的具体 Estimation Points 和 Time Efforts，再结合 issues 里面所记录下的各种笔记和 references，就可以有一个比较直观的总结和复盘了。

| Number & Description                     | Estimation Points | Time Efforts |
| ---------------------------------------- | ----------------- | ------------ |
| [#85](https://github.com/JimmyLv/jimmylv.github.io/issues/85) 记录时间这件小事儿 | 3                 | 04:26:18     |
| [#96](https://github.com/JimmyLv/jimmylv.github.io/issues/96) 如何对时间进行分类？ | 8                 | 03:00:09     |
| [#102](https://github.com/JimmyLv/jimmylv.github.io/issues/102) 建立个人 Wiki 系统 | 2                 | 02:53:56     |
| [#101](https://github.com/JimmyLv/jimmylv.github.io/issues/101) 技术雷达宣讲：enzyme 测试框架 | 5                 | 06:11:19     |
| [#90](https://github.com/JimmyLv/jimmylv.github.io/issues/90) Working time improvement | 1                 | 33:27 min    |
| [#97](https://github.com/JimmyLv/jimmylv.github.io/issues/97) 如何使用 XX 的标签系统？ | 1                 | 25:21 min    |

#### 其他辅助工具

- 看板：as Jira/[Trello](https://trello.com/)，可视化当前进度 => GitHub Issues group by @Projects / 日历 in @滴答清单；如果你不想用 ZenHub 可以试试 [Gitlo](http://gitlo.co) 可以在 GitHub issues 和 Trello 之间进行双向同步。
- 晨间日记/每日回顾：as Stand-Up，只用关注 Timeline/Done/Todo/Blocker 以及当天的心情/天气等等，使用 @[格志日记](http://griddiaryapp.com/zh/)的一个特点就是可以通过问答的方式对一天进行回顾。
- 时间记录：@[时间块](http://timeblocks-simple-daily-activi.appstor.io/zh/)的优点在于记录非常得简单、快捷，用户评论最省时间的时间记录工具没有之一，推荐新手可以试试。但由于个人需要更加详细的记录细节和报告分析，以及多平台（包括 Chrome Extension）的支持，从而选择了 @[Toggl](https://toggl.com/app/timer)。
- 白噪声：作为一款时间记录工具，@[Toggl](https://toggl.com/app/timer) 本身就支持 Pomodoro 的 25 分钟提示，而作为专注力辅助的白噪声软件我在手机上用的 @[潮汐](https://itunes.apple.com/tw/app/chao-xi-mei-hao-fan-jia-zhong/id1077776989?l=zh&mt=8)，电脑上则选择了 @[Noizio](http://noiz.io/)。

## 后话

也许你很喜欢这个解决方案但又不太想公开自己的 issues 列表，那可以试试 GitHub 的 private repo（需要付费），免费的可以试试 GitLab，支持从 GitHub 一键导入，并且已经原生支持了 pipeline 和 kanban 功能。当然咯，不限于工具或软件，这一套方法论其实是可以运用在任何地方的，甚至于我们可以来做一个结合敏捷方法论的个人学习管理软件也不错嘛！

但是于我而言，选择在 GitHub 这样一个公开环境下记录学习的最大一个动机就在于「开源」，很喜欢一句话，大意是「**在这个互联网时代，能限制住学习的只有你的求知欲**」。当你从互联网这个广阔的知识海洋当中汲取知识的时候，也应当有所输出到即反哺到整个互联网当中去。我会经常写博客/笔记来总结分享自己的所学，但是一篇文章诞生的背后往往还有很多其他知识和经验的相互交融与沉淀。[Issues · JimmyLv/jimmylv.github.io](https://github.com/JimmyLv/jimmylv.github.io/issues) 这个列表里面的某个 issues 最终能否演变成一篇文章我不知道，但是基于 GitHub 开放式的学习历程都会被这些 issues 如实地记录着，任何一个想法都能追本溯源被找出最开始的缘由。

> 相比于软件开发这件小事儿，健康快乐地成长显然要重要得多。—— 立青