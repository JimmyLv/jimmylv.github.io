---
layout: post
title: 双向绑定和单向数据流
categories: [前端]
tags: [Design Pattern, Angular, React, Redux, Vue]
published: False

---

- Reactive Data
- State 复杂度
- UI 状态机
- Rerender optimize
- 干掉~~时间~~变量

https://www.quora.com/Why-is-the-two-way-data-binding-being-dropped-in-Angular-2

https://www.quora.com/What-are-the-differences-between-Two-way-data-binding-vs-reactivity

https://hashnode.com/post/why-does-react-emphasize-on-unidirectional-data-flow-and-flux-architecture-ciibz8ej600n2j3xtxgc0n1f0

https://medium.com/@gilbox/how-can-react-and-flux-help-us-create-better-stronger-faster-angular-applications-639247898fb

http://huangxuan.me/2016/02/01/React-vs-Angular2/ + 评论

https://segmentfault.com/a/1190000004681757 双向绑定的实现

+ 理解 Vue 文档中的几篇深度文章，如何利用 JavaScript 的原始特性

+ 再来看 React 中的实现：https://facebook.github.io/react/docs/two-way-binding-helpers.html

储配技能 React 绝对第一选择：绝不脱离商业谈技术；技术受众考量；跟着高手一起学习


Redux implements the concept of state management using Flux design pattern. It does that using pure functions (reducers) that return a new state given a certain event (type of action) and its event data (payload of action).



落实到自身：

- 函数式
- FRP
- 学好 JavaScript
- 入坑 Elem

方法：

- React 的文档确实很赞，还有很多大咖喜欢在 Youtube 上分享视频 => 每学到一个知识点都到官方文档中找到出处：
    + https://facebook.github.io/react/docs/reusable-components.html#stateless-functions
    + https://github.com/airbnb/javascript/tree/master/react#class-vs-reactcreateclass-vs-stateless
    + https://egghead.io/lessons/react-building-stateless-function-components-new-in-react-0-14
    + https://egghead.io/lessons/react-building-a-react-js-app-utilizing-stateless-function-components
    + https://medium.com/@joshblack/stateless-components-in-react-0-14-f9798f8b992d 「CSS!!!」
    + http://brewhouse.io/blog/2015/03/24/best-practices-for-component-state-in-reactjs.html
