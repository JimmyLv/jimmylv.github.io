---
layout: post
title: "Vue 应用单元测试的策略与实践 05 - 测试奖杯策略（终篇）"
categories: [前端]
tags: [Tutorial, UnitTest, ES6, Vue, Vuex, Jest, CQRS, TDD]
published: True
---

## 本文的目标

3. Vue 项目中测试收益如何最大化，如何配置高性价比的测试策略，即什么地方到底该花力气测试，什么地方又可以暂且放一放？

```md
// Given
一个具备UT基础但找不到着力点的求索之徒🐒
// When
当他🚶阅读本文的Vue应用测试策略部分
// Then
他能够找到测试的重点，重新燃起对UT的热情🔥
他能够在项目背景下合理配置单元测试的测试策略
```

### 单元测试的特点及其位置

- 重要参考：测试奖杯🏆
- React 版

### 单元测试的关注点
### 应用测试的测试策略

* 如何推进单元测试的落地
* 从性价比最高的测试开始写起，比如 Vuex 的 mutation
* 介绍如何提高测试覆盖率的技巧，比如 git hook
* 给予反馈，回到 XP 所提到的反馈环
* 再引出 TDD，最好的写单元测试的方式

## 总结一下

总之呢，不要测试 Vue 组件和 Vuex store 交互的时候引入一个真实的 Store，那样就不再是单元测试了，还记得我们在第二篇[单元测试基础][1]中所提到的社交型（Social Tests）还是独立型（Solitary Tests）测试单元吗？Vuex 等 `Redux-like` 架构在前端应用中的 “状态管理模式” ，已经将 View 视图层和 State 数据层尽可能合理得拆分与隔离，那么单元测试就只需要分别测试 Vue 和 Vuex，从而就能保证 Vue 组件和数据流按照预期那样工作。

## 未完待续……

**\## 单元测试基础**

* [x] ### 单元测试与自动化的意义
* [x] ### 为什么选择 Jest
* [x] ### Jest 的基本用法
* [x] ### 该如何测试异步代码？

**\## Vue 单元测试**

* [x] ### Vue 组件的渲染方式
* [x] ### Wrapper `find()` 方法与选择器
* [x] ### UI 组件交互行为的测试  

**\## Vuex 单元测试**

* [x] ### CQRS 与 `Redux-like` 架构
* [x] ### 如何对 Vuex 进行单元测试
* [x] ### Vue组件和Vuex store的交互  

**\## Vue 应用测试策略**

* [ ] ### 单元测试的特点及其位置
* [ ] ### 单元测试的关注点
* [ ] ### 应用测试的测试策略

[1]:	https://blog.jimmylv.info/2018-10-29-vue-application-unit-test-strategy-and-practice-02-how-jest-work/