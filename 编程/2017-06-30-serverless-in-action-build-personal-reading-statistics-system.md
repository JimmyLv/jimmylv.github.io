---
layout: post
title: Serverless 实战：打造个人阅读追踪系统
categories: [编程]
tags: [Serverless, Reading, Align, PKM]
published: False

---

## 阅读习惯和个人知识管理体系

首先当然是介绍一下背景也只是我的**阅读习惯和体系**，最好能够把自己的博客内容引荐过来。也就是之前所提到的那个知识的三种分类。而最有效的方式可能是把那张图放进来，知乎那张图真的是比较完整的一个体系，而最近所看到的关于点面线流的这种阅读分类，简直不能再棒！

### 稍后阅读永远读不完的痛点：缺乏追踪

然后再讲一下这个体系当中的一些痛点，比如说没法追踪自己阅读的多少。也没办法给予自己奖励，没办法可视化出来给自己动力。在这里也推荐一篇文章《[用 GTD 的方法结束稍后读](https://sspai.com/post/33933)》

从而就有了这么一个想法，就是跟 GitHub 结合起来，更多的详情当然是参考自己以前写过的基于 GitHub 等敏捷学习方法之道与术。当然是自我推销了啦。

### 可视化 Cumulative Flow Diagram

其实这个地方必须重点来看一下具体的最终效果图，从而吸引大家能够看下去，并且产生好奇心，在这里简单介绍一下燃尽图、（差异）图和最有效果的预测完成日期，总之就是跟敏捷结合起来，用项目管理的方式来管理阅读列表。

## Serverless 架构

最后，真正的进入正题简单介绍一下 Serverless 的时代背景，以及他的一些适用场景。而现在这个场景下是特别特别合适的，并且，结合 IFTTT 的触发器和 Marker 工具能够非常方便的跟自有 API 相集成。

### 流程化：APIs 即服务

在此之前我们先介绍一下IFTTT，并且将他跟Instapaper 账号绑定，然后就可以发现它的一些 ❤️ 归档等行为可以作为一个 trigger，然后将相关信息发到某一个指定 API endpoint。

然后把整个 flow 给提炼总结一下，当然顺便来用一个酷炫的 AcsiiFlow 来画图。

### 初始化 Webtask 项目（与 AWS Lambda 对比）

[Build a Serverless MERN Story App With Webtask.io -- Zero to Deploy: 1 ― Scotch](https://scotch.io/tutorials/build-a-serverless-mern-story-app-with-webtask-io-zero-to-deploy-1)

先简单介绍一下 Webtask 与 AWS Lambda 的区别，而今天我们则着重介绍一下 Webtask，介绍一下出这个工具的这家公司，即 Auth0 和大名鼎鼎的 JWT，紧接着就开始正式进入初始化阶段。然后就安装工具初始化项目以及注册一些账号

在这里先创建一个 reading endpoint 并且能够处理 get 请求返回最简单的 HelloWorld！

## 使用 GitHub Issue 追踪阅读列表

### IFTTT：添加 Instapaper 后自动创建 GitHub Issue

先利用好 IFTTT 与 Instapaper 的集成功能，贴一张图即可

至于最后怎么去处理这样一个请求，然后就进入到第一个例子，即 API 的设计，与结合 Express 是怎么玩的，开始贴代码！这里面参考我原本参考的那篇文章就可以啦！
[Build a Serverless MERN Story App With Webtask.io -- Zero to Deploy: 1 ― Scotch](https://scotch.io/tutorials/build-a-serverless-mern-story-app-with-webtask-io-zero-to-deploy-1)

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

最后再来考虑一下后续计划，就比如说我把高亮部分作为评论放到 GitHub 的 comments 里面，但是最终我想把它收藏到自己的个人知识库即 Diigo 里面，但是还没有完成。

与此同时呢，所以还想把估点根据不同的文章类型和难易程度具体划分一下，而不是现在简简单单的一个点。

## 参考资料







