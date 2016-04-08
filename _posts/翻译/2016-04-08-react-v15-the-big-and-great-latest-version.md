---
layout: post
title: "【译】Facebook 正式发布 ReactJS v15.0 稳定版"
categories: [翻译]
tags: [React, Release]
published: True

---

原文地址：[React v15.0 (April 7, 2016 by Dan Abramov)](https://facebook.github.io/react/blog/2016/04/07/react-v15.html)

> We would like to thank the React community for reporting issues and regressions in the release candidates on our [issue tracker](https://github.com/facebook/react/issues/). Over the last few weeks we fixed those issues, and now, after two release candidates, we are excited to finally release the stable version of React 15.

我们想要特别感谢 React 社区对已发布的候选版本所作出的贡献，谢谢你们在 GitHub 上的 [issue 追踪系统](https://github.com/facebook/react/issues/) 中所提供的反馈和支持。在过去的几个星期，我们修复了这些 issues，历经两个候选版本后，在此我们非常兴奋地发布最终的 React 15 稳定版。

> As a reminder, [we’re switching to major versions](https://facebook.github.io/react/blog/2016/02/19/new-versioning-scheme.html) to indicate that we have been using React in production for a long time. This 15.0 release follows our previous 0.14 version and we’ll continue to follow semver like we’ve been doing since 2013. It’s also worth noting that [we no longer actively support Internet Explorer 8](https://facebook.github.io/react/blog/2016/01/12/discontinuing-ie8-support.html). We believe React will work in its current form there but we will not be prioritizing any efforts to fix new issues that only affect IE8.

作为纪念，[我们特意切换到一个比较大的版本之上](https://facebook.github.io/react/blog/2016/02/19/new-versioning-scheme.html)，以象征我们已经在产品环境下使用了很长时间的 React。这次 15.0 版本的发布紧随之前的 0.14 版本而来，就像我们自 2013 年以来所做的那样，我们将继续关注着 SemVer ([What's Semantic Versioning](http://abdulapopoola.com/2015/10/26/what-is-semver/)) 版本。另外值得关注的就是我们不再积极支持 [Internet Explorer 8](https://facebook.github.io/react/blog/2016/01/12/discontinuing-ie8-support.html) 了，我们相信 React 在现有的形态下可以很好地工作，而我们将不会再优先修复仅在 IE8 出现的新问题了。

> React 15 brings significant improvements to how we interact with the DOM:

React 15 在如何与 DOM 进行交互这方面提供了重大改善：

>   * We are now using `document.createElement` instead of setting `innerHTML` when mounting components. This allows us to get rid of the `data-reactid` attribute on every node and make the DOM lighter. Using `document.createElement` is also faster in modern browsers and fixes a number of edge cases related to SVG elements and running multiple copies of React on the same page.

  * 现在我们在装载组件的时候将使用 `document.createElement` 而不是去设置 `innerHTML` 。这使得我们摆脱了每个节点上的 `data-reactid` 属性，从而保持 DOM 更加轻量级。在现代浏览器中使用 `document.createElement` 性能也会更快，与此同时修复了与 SVG 元素相关的一系列边缘问题，以及支持在同一页面同时运行多个 React 拷贝。

>   * Historically our support for SVG has been incomplete, and many tags and attributes were missing. We heard you, and in React 15 we [added support for all the SVG attributes that are recognized by today’s browsers](https://github.com/facebook/react/pull/6243). If we missed any of the attributes you’d like to use, please [let us know](https://github.com/facebook/react/issues/1657). As a bonus, thanks to using `document.createElement`, we no longer need to maintain a list of SVG tags, so any SVG tags that were previously unsupported should work just fine in React 15.

  * 过往我们对 SVG 的支持不够完善，缺失了很多标签和属性。我们听从意见，所以在 React 15 当中[添加了对当今浏览器所识别的所有 SVG 属性的支持](https://github.com/facebook/react/pull/6243)。如果我们遗漏了任何你可能会用到的属性，麻烦[告知我们](https://github.com/facebook/react/issues/1657)。作为奖励，得益于使用 `document.createElement`，我们将不再需要维护一连串的 SVG 标签了，所以任何之前无法被支持的 SVG 标签在 React 15 当中都可以很好地工作。

>   * We received some amazing contributions from the community in this release, and we would like to highlight [this pull request](https://github.com/facebook/react/pull/5753) by [Michael Wiencek](https://github.com/mwiencek) in particular. Thanks to Michael’s work, React 15 no longer emits extra `<span>` nodes around the text, making the DOM output much cleaner. This was a longstanding annoyance for React users so it’s exciting to accept this as an outside contribution.

  * 我们本次版本发布当中，也得到了一些非常优秀的社区贡献，我们觉得应当特别强调一下由 [Michael Wiencek](https://github.com/mwiencek) 所提供的这个 [pull request](https://github.com/facebook/react/pull/5753)。归功于 Michael，React 15 不再需要为文本单独包裹一层额外的 `<span>` 节点，这使得 DOM 输出更加整洁了。这是一个困扰 React 用户已久的问题，所以这是所采纳的一个非常令人兴奋的外部贡献。

> While this isn’t directly related to the release, we understand that in order to receive more community contributions like Michael’s, we need to communicate our goals and priorities more openly, and review pull requests more decisively. As a first step towards this, we started publishing [React core team weekly meeting notes](https://github.com/reactjs/core-notes) again. We also intend to introduce an RFC process inspired by [Ember RFCs](https://github.com/emberjs/rfcs) so external contributors can have more insight and influence in the future development of React. We will keep you updated about this on our blog.

尽管这不与本次的发布直接相关，但是我们明白，为了接受更多 Michael 这样来自于社区的贡献，我们需要更加开放地传达我们的目标和优先级，并且更加果断地审查 pull request。为此我们所做的第一步就是，我们开始再次公布 [React 核心团队每周会议记录](https://github.com/reactjs/core-notes)。我们也有打算引入一种名为 RFC 的流程，启发自 [Ember RFCs](https://github.com/emberjs/rfcs)，从而外部贡献者们能够对 React 的未来开发工作提供更多的意见和影响力。我们将会在博客中通知后续事宜。

> We are also experimenting with a new changelog format in this post. Every change now links to the corresponding pull request and mentions the author. Let us know whether you find this useful!

我们也在本篇博文当中试验一种新的 changelog 格式，每一个修改现在都会链接到相对应的 pull request，并且提及相关作者。请让我们知道这是否有效！

## Upgrade Guide | 升级指南

> As usual with major releases, React 15 will remove support for some of the patterns deprecated nine months ago in React 0.14. We know changes can be painful (the Facebook codebase has over 20,000 React components, and that’s not even counting React Native), so we always try to make changes gradually in order to minimize the pain.

跟以往的大版本更新一样，在九个月前所发布的 React 0.14 版本中标记为废弃的一些模式，将会在React 15 当中被彻底移除。我们知道这很痛苦（Facebook 代码库中有着超过 20,000 的 React 组件，这还不包括 React Native 的数量），所以我们就一直都在尝试着逐步修改，就是为了尽量减少这种痛苦。

> If your code is free of warnings when running under React 0.14, upgrading should be easy. The bulk of changes in this release are actually behind the scenes, impacting the way that React interacts with the DOM. The other substantial change is that React now supports the full range of SVG elements and attributes. Beyond that we have a large number of incremental improvements and additional warnings aimed to aid developers. We’ve also laid some groundwork in the core to bring you some new capabilities in future releases.

如果你的代码在 React 0.14 版本下没有任何警告的话，那么本次升级将会非常容易。本次发布的大部分更改实际上都在幕后，影响着 React 与 DOM 的交互，其他的重要修改就是现在的 React 全面支持了 SVG 的元素和属性。在此之外，我们还有着大量的增量改进和旨在帮助开发人员的额外警告。我们已经在核心部分也奠定了一些基础，以便于在将来的版本当中给你带来一些新的功能。

> See the changelog below for more details.

（从原文）查看 [changelog](https://facebook.github.io/react/blog/#installation) 以便得知更多详情。

