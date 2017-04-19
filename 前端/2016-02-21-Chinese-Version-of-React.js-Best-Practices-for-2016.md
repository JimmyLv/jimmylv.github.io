---
layout: post
title: 【译】展望2016，React.js 最佳实践
categories: [前端]
tags: [React, 总结, 最佳实践]
published: True
---

> React.js 作为前端框架的后起之秀，却在2015年携着虚拟 DOM，组件化，单向数据流等利器，给前端 UI 构建掀起了一波声势浩大的函数式新潮流。新鲜出炉的一篇 React.js 最佳实践，基本涵盖了所有的 React.js 生态周边，可用于实践参考。文章不仅表明了 Flux 经常被滥用的观点，也推荐开发者使用 Redux 作为 JavaScript 的可预测状态容器，并且提出保持状态扁平化和使用 Immutable.js 等数据处理解决方案。与此同时，也从高阶组件，组件测试以及组件级别热重载等方面提供了建议，当然也涉及了 Webpack，HTTP 2，使用 ES2015 乃至 Linters 等代码层面的建议。


# 【译】展望2016，React.js 最佳实践

原文地址：<https://blog.risingstack.com/react-js-best-practices-for-2016/>

过去的2015年，**[React](https://facebook.github.io/react/)** 在全世界范围都是一派欣欣向荣的景象，开发者会议无一不热衷于这个话题。在过去一年中发生了很多重要的里程碑事件，更多详情可以查看我们关于 [React in 2015](https://blog.risingstack.com/react-in-2015/) 的总结。

在新的2016年里，最有趣的问题来了：**我们该如何开发一个应用**，有什么推荐使用的库？

> 作为一名长时间使用 React.js 的开发者来说，我对这个问题有自己的答案以及最佳实践，但也有可能你不会完全认同。我也非常乐于倾听你的想法和观点：请留言以便讨论。

![](https://risingstack-blog.s3.amazonaws.com/2016/Jan/react_best_practices-1453211146748.png)

如果你才刚刚开始学习 React.js，可以查看我们的 [React.js 教程](https://blog.risingstack.com/the-react-way-getting-started-tutorial/)，或者 Pete Hunt 所写的 [React howto](https://github.com/petehunt/react-howto)。

## 数据处理

在 React.js 应用中处理数据轻而易举，与此同时亦充满挑战。

这是因为你可以通过各种方式将属性数据传递给 React 组件，并从中构建渲染树；然而这种方式也并非那么显而易见，到底该如何更新视图。

2015之初诞生了很多不同 Flux 库，并不断产出了更加实用的响应式方案。

让我们看看现在的情况：

### Flux

根据我们的经验，Flux 经常被滥用，*（这意味着大家总是在不需要的时候就用上它）*。

Flux 提供了一种非常清晰的方式来存储和更新应用状态，并且只会在必要的时候才触发页面渲染。

Flux 致力于**应用的全局状态管理**，比如：管理已登录用户状态，路由状态，或者是活跃账户状态，但若是用来管理临时数据或者本地数据，瞬间就变成了痛苦。

我们不推荐使用 Flux 来管理路由相关的数据，比如 `/items/:itemId`。而只是获取路由数据并存储在组件的 state 之中。在这种情况下，它会在组件消失之后一起被销毁。

*如果你想了解更多关于 Flux 的信息，[The Evolution of Flux Frameworks](https://medium.com/@dan_abramov/the-evolution-of-flux-frameworks-6c16ad26bb31#.90lamiv5l) 非常值得一读。*

#### 使用 Redux

> Redux 是一个 JavaScript 应用的可预测状态容器。

如果你觉得需要 Flux 或者一种类似的解决方案，你应该了解一下 [redux](https://github.com/rackt/redux)，以及学习 [Dan Abramov](https://twitter.com/dan_abramov) 的[Getting started with redux](https://egghead.io/series/getting-started-with-redux) 课程，这能够迅速提高你的开发技能。

> Redux 延续并改进了 Flux 的思想，并从 Elm 架构中取经，规避了 Flux 的复杂度。（译者注：Elm 是一门面向 Web 的函数式编程语言，致力于改善客户端 Web 编程体验。）

#### 保持状态扁平化

API 经常会返回嵌套资源。这在 Flux 或基于 Redux 的架构中处理起来会非常困难。我们推荐使用 [normalizr](https://github.com/gaearon/normalizr) 之类的库将数据进行扁平化处理，**保持状态尽可能地扁平化**。

示意：

    const data = normalize(response, arrayOf(schema.user))

    state = _.merge(state, data.entities)

*（我们使用 [isomorphic-fetch](https://www.npmjs.com/package/isomorphic-fetch) 来与 APIs 进行交互）*

### 使用 immutable 状态

> 共享的可变性状态乃万恶之源。 —— *Pete Hunt, React.js Conf 2015*

![](https://risingstack-blog.s3.amazonaws.com/2016/Jan/immutable_logo_for_react_js_best_practices-1453211749818.png)

[不可变对象](https://en.wikipedia.org/wiki/Immutable_object)是一种在创建之后就不可修改的对象。

不可变对象可以让我们免于痛楚，并通过引用级别的比对检查来**改善渲染性能** 。比如说在 `shouldComponentUpdate` 中：

    shouldComponentUpdate(nexProps) {
     // instead of object deep comparsion
     return this.props.immutableFoo !== nexProps.immutableFoo
    }

**如何在 JavaScript 中实现不可变呢？**

最痛苦的方式就是小心为之，示例代码如下，你需要在单元测试中通过 [deep-freeze-node](https://www.npmjs.com/package/deep-freeze-node) 来反复验证。（在修改之前冻结，并在结束后验证结果。）

    return {
      ...state,
      foo
    }

    return arr1.concat(arr2)

相信我，这是最平淡无奇的例子了。

更简单也更自然的方式就是使用 [Immutable.js](https://facebook.github.io/immutable-js/)。

    import { fromJS } from 'immutable'

    const state = fromJS({ bar: 'biz' })
    const newState = foo.set('bar', 'baz')

Immutable.js 非常之快，背后理念也异常漂亮。哪怕你并不想使用它，我也推荐阅读这个由 [Lee Byron](https://twitter.com/leeb) 所制作的视频 [Immutable Data and React](https://www.youtube.com/watch?v=I7IdS-PbEgI)。视频对于 Immutable.js 的工作原理有着非常深刻的讲解。

### 观察式与响应式方案

如果你不喜欢 Flux/Redux 或者只是想要更加 reactive，不要失望！这儿有很多其他数据处理的解决方案。这就有一个相关库的简要列表供你参考：

  * [cycle.js](http://cycle.js.org/) *("A functional and reactive *JavaScript* framework for cleaner code")*
  * [rx-flux](https://github.com/fdecampredon/rx-flux) *("The Flux architecture with RxJS")*
  * [redux-rx](https://github.com/acdlite/redux-rx) *("RxJS utilities for Redux.")*
  * [mobservable](https://mweststrate.github.io/mobservable/) *("Observable data. Reactive functions. Simple code.")*

## 路由

几乎所有的客户端应用都或多或少需要使用路由。如果你在浏览器中使用 React.js，你就会在挑选库的时候碰到这个分歧点。

我们的选择是出自优秀的 [rackt](https://github.com/rackt) 社区的 [react-router](https://github.com/rackt/react-router)。Racket 给 React.js 的拥簇者带来了很多高质量资源。

你可以查看他们的[文档](https://github.com/rackt/react-router/tree/master/docs)以便于集成 `react-router`，但是更重要的是：如果你使用 Flux/Redux，我们建议你将路由状态和你的 store 或全局状态**保持同步**。

同步的路由状态可以帮助你对 Flux/Redux 的 Actions 所提供的路由行为有所控制，并且能够在组件中读取路由状态和参数。

Redux 用户可以通过 [redux-simple-router](https://github.com/rackt/redux-simple-router) 这个库轻松实现它。

#### 代码分割，惰性加载

只有一小部分 `webpack` 用户知道应用代码是可以分割的，将 bundler 的输出拆分成多个 *JavaScript* 块：

    require.ensure([], () => {
      const Profile = require('./Profile.js')
      this.setState({
        currentComponent: Profile
      })
    })

这在大型应用中会非常有用，因为在每次部署之后，用户浏览器就**没有必要下载那些很少用到的代码**，比如 profile 页面。

更多代码块将导致更多 HTTP 请求 —— 但是使用 [HTTP/2 multiplexed](https://http2.github.io/faq/#why-is-http2-multiplexed) 的话就不成问题。

结合 [chunk hashing](https://christianalfoni.github.io/react-webpack-cookbook/Optimizing-caching.html)，你也可以在代码改变之后优化缓存命中率。（译者注：终端用户访问加速节点时，如果该节点有缓存住了要被访问的数据时就叫做命中，如果没有的话需要回原服务器获取，就是没有命中。）

react-router 的下个版本就将在代码分割这方面提供更多帮助。

想要了解 react-router 的未来走向，可以查看 [Ryan Florence](https://twitter.com/ryanflorence) 所写的这篇博文： [Welcome to Future of Web Application Delivery](https://medium.com/@ryanflorence/welcome-to-future-of-web-application-delivery-9750b7564d9f#.vuf3e1nqi)。

## 组件

大部分人都对 JSX 存有怨言。首先，你需要知道的是这在 React 中并不是必须的。

在最后，JSX 都会通过 Babel 被编译成 *JavaScript*。你可以直接编写 *JavaScript* 来替代 JSX，但是在处理 HTML 的时候使用 JSX 会感觉更加自然。

特别是对于不懂技术的人来说，他们依然可以理解和修改必要的部分。

> JSX 是一种与 XML 类似的 *JavaScript* 语法扩展。你可以通过一个简单的 JSX 语法转换器来编译 React。 —— [JSX in depth](https://facebook.github.io/react/docs/jsx-in-depth.html)

如果你想要了解更多关于 JSX 的信息，可以查看 [JSX Looks Like An Abomination - But it’s Good for You](https://medium.com/javascript-scene/jsx-looks-like-an-abomination-1c1ec351a918#.ca28nvee6) 这篇文章。

### 使用 Class

React 和 ES2015 的 Class 语法搭配完美。

    class HelloMessage extends React.Component {
      render() {
        return <div>Hello {this.props.name}</div>
      }
    }

我们喜欢[高阶组件](http://jamesknelson.com/structuring-react-applications-higher-order-components/)更胜于 mixins，所以对于我们来说，保留 `createClass` 就更像一个语法问题而不是技术问题。我们相信使用 `createClass` 而不是 `React.Component` 绝对无可厚非，反之亦然。

### 属性类型

如果你在2016年依然没有检查 properties，那么你应该从现在开始做起，这将为你节省大量时间，相信我。

    MyComponent.propTypes = {
      isLoading: PropTypes.bool.isRequired,
      items: ImmutablePropTypes.listOf(
        ImmutablePropTypes.contains({
          name: PropTypes.string.isRequired,
        })
      ).isRequired
    }

当然，验证 Immutable.js 所编写的 properties 也是可能的，可以使用[react-immutable-proptypes](https://www.npmjs.com/package/react-immutable-proptypes)。

### 高阶组件

目前来说，[mixins 已死](https://medium.com/@dan_abramov/mixins-are-dead-long-live-higher-order-components-94a0d2f9e750)，而且在 ES6 Class 组件中已经不再被支持，我们应当寻找不同的替代方案。

**那什么是高阶组件呢？**

    PassData({ foo: 'bar' })(MyComponent)

本质上来说，你可以由原始组件创造一个新的组件并且扩展它的行为。你可以在多种情况下使用它，比如授权：`requireAuth({ role: 'admin' })(MyComponent)` *（检查上层组件中的用户，若是未登录则需要重定向）*，或者是连接你的组件和 Flux/Redux 仓库。

在RisingStack，我们也将数据获取和类似 Controller 的逻辑分割成高阶组件，并保持视图层尽可能简单。

## 测试

在开发周期中，维持测试的高覆盖率是非常重要的一部分。幸运的是， React.js 社区诞生了很多优秀的库可以帮助我们达到这一点。

### 组件测试

我们最喜爱的库之一是由 AirBnb 所开发的 [enzyme](https://github.com/airbnb/enzyme)，可用于组件测试。非常神奇的是，它的浅渲染特性可以对组件的逻辑及其渲染输出进行测试。尽管它还不能替代你的 selenium 测试，但是将前端测试提升到了一个新的水平。

    it('simulates click events', () => {
      const onButtonClick = sinon.spy()
      const wrapper = shallow(
        <Foo onButtonClick={onButtonClick} />
      )
      wrapper.find('button').simulate('click')
      expect(onButtonClick.calledOnce).to.be.true
    })

看起来就非常简洁，不是么？

你在使用 chai 作为测试断言库嘛？相信你会喜欢 [chai-enyzime](https://github.com/producthunt/chai-enzyme) 的！

### Redux 测试

**测试一个 reducer** 非常简单，它响应新到来的 actions，并且将原来的状态进行更新：

    it('should set token', () => {
      const nextState = reducer(undefined, {
        type: USER_SET_TOKEN,
        token: 'my-token'
      })

      // immutable.js state output
      expect(nextState.toJS()).to.be.eql({
        token: 'my-token'
      })
    })

**测试 actions** 也很简单，但是异步 actions 就不太一样了。对于测试异步的 Redux actions 来说，我们推荐使用 [redux-mock-store](https://www.npmjs.com/package/redux-mock-store)，非常有帮助。

    it('should dispatch action', (done) => {
      const getState = {}
      const action = { type: 'ADD_TODO' }
      const expectedActions = [action]

      const store = mockStore(getState, expectedActions, done)
      store.dispatch(action)
    })

更深度地了解 [redux 测试](http://rackt.org/redux/docs/recipes/WritingTests.html)，可以查看官方文档。

### 使用 npm

虽然 React.js 并不依赖代码打包工具就可以很好地工作，但我们还是推荐使用 [Webpack](https://webpack.github.io/) 或者 [Browserify](http://browserify.org/) 来发挥 [npm](https://www.npmjs.com/) 的能力。Npm 上满是高质量的 React.js 包，还可以帮你非常优雅地管理依赖。

*（请不要忘记复用你自己的组件，这是一种绝佳的代码优化方式。）*

### Bundle 大小

这本身不是一个 React 相关的问题，但是大多数人都在打包他们的 React 应用，所以我认为提到这点很重要。

当你打包源代码的时候，时刻警惕打包后的文件大小。为了**保持体积最小化**，你应该考虑如何 require/import 依赖。

对比以下代码片段，这两种不同的方式对输出的影响区别巨大：

    import { concat, sortBy, map, sample } from 'lodash'

    // vs.
    import concat from 'lodash/concat';
    import sortBy from 'lodash/sortBy';
    import map from 'lodash/map';
    import sample from 'lodash/sample';

可以查看这篇文章 [Reduce Your bundle.js File Size By Doing This One Thing](https://lacke.mn/reduce-your-bundle-js-file-size/) 获取更多详情。

我们也喜欢将代码分离出至少 `vendors.js` 和 `app.js` 两个文件，因为 vendors 相对于我们的代码库来说更新不是那么频繁。

将输出文件名称进行哈希化处理 *(Webpack 中的 chunk hash)*，并使用长缓存，我们可以大大减少用户需要下载的代码大小。结合惰性加载，优化效果可想而知。

如果你还不太熟悉 Webpack，可以查看这本优秀的 [React webpack 手册](https://christianalfoni.github.io/react-webpack-cookbook)。

### 组件级别热重载

如果你曾经使用过热加载来编写单页面应用，当你在处理某些与状态相关的事情时，可能你就会明白当你在编辑器中点击保存，整个页面就重新加载了是多么令人讨厌。这样子就不得不重新点击一遍应用，重复如此会令人抓狂的。

通过 React，在重载组件的同时**保持组件状态**已经成为可能 —— 耶，从此不再痛苦！（~~没有蛀牙！~~）

关于如何搭建热重载，可以参考 [react-transform-boilerplate](https://github.com/gaearon/react-transform-boilerplate)。

### 使用ES2015

![](https://risingstack-blog.s3.amazonaws.com/2016/Jan/babel_logo_in_react_js_best_practices_2016-1453212218011.png)

前面有提到过，我们可以在 React.js 组件中使用 JSX，然后使用[Babel.js](https://babeljs.io/)进行编译。

其实 Babel 的能力远不止如此，它也可以让我们现在就可以给浏览器编写 ES6/ES2015 代码。在 RisingStack，我们在服务器端和客户端都使用了 ES2015 特性，这都已经在最新的 LTS Node.js 版本中被实现了。

### Linters

或许你已经给你的 *JavaScript* 代码制定了代码规范，但是你知道也有用于 React 的代码规范了吗？我们强烈推荐挑选一个并开始遵循它。

在 RisingStack，我们也将 linters 强制运行在 CI 系统上，`git push` 亦然。可以试试 [pre-push](https://www.npmjs.com/package/pre-push) 或者 [pre-commit](https://www.npmjs.com/package/pre-commit)。

我们使用标准的 *JavaScript* 代码风格，并使用了 [eslint-plugin-react](https://www.npmjs.com/package/eslint-plugin-react)对 React.js 代码进行规范 。

*（就是，我们不再使用分号。）*

## GraphQL 和 Relay

GraphQL 和 Relay 相对而言属于新技术，在 RisingStack，目前我们还没有在产品环境中使用它们，暂时保持关注。

我们曾经写过一个 Relay 的 MongoDB ORM库，叫做 [graffiti](https://github.com/risingstack/graffiti)，可以使用已有的 mongoose 模型直接创建一个 GraphQL 服务器。

如果你想要学习这些新技术，我们建议你可以找来玩一玩。

## 尽情享用这些 React.js 最佳实践

有些突出的技术和库其实跟 React.js 并不相关 —— 但是保持视野开阔，关注社区的其他人都在做些什么。React 社区在2015年里就受到了 [Elm 架构](https://github.com/evancz/elm-architecture-tutorial/) 的很多启发。

> 如果你知道其它在2016年必不可少的 React.js 工具，请留言让我们知道！

------

#### 原作者: [Péter Márton](https://blog.risingstack.com/author/peter-marton/)

CTO at RisingStack, brewing beer with Node.js

<https://twitter.com/slashdotpeter>
