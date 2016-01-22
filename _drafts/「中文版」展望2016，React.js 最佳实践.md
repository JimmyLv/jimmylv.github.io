---
layout: post
title: 展望2016，React.js 最佳实践
categories: [翻译]
tags: [React, 总结]
published: True
---

# 展望2016，React.js 最佳实践

过去的2015年，**[React](https://facebook.github.io/react/)** 在全世界范围都是一派欣欣向荣的景象，开发者会议无一不热衷于这个话题。在过去一年中发生了很多重要的里程碑事件，更多详情可以查看我们关于 [React in 2015](https://blog.risingstack.com/react-in-2015/) 的总结。

在新的2016年里，最有趣的问题来了：**我们该如何开发应用**，有什么推荐使用的库？

> 作为一个在工作中使用了很久 React.js 的开发者来说，我对这个问题有自己的答案以及相应的最佳实践，但很有可能你不会完全同意我。我也非常乐于倾听你的想法和观点：请留下评论以便讨论。

![](https://risingstack-blog.s3.amazonaws.com/2016/Jan/react_best_practices-1453211146748.png)    

如果你才刚刚开始学习 React.js，可以查看我们的 [React.js 教程](https://blog.risingstack.com/the-react-way-getting-started-tutorial/)，或者 Pete Hunt 所写的 [React howto](https://github.com/petehunt/react-howto)。

## Dealing with data | 数据处理

在 React.js 应用中处理数据轻而易举，与此同时亦充满挑战。

这是因为你可以通过各种方式将 properties 传递给 React 组件，并从中渲染 DOM 树；然而更新视图的方式也不总是那么显而易见的。

2015之初诞生了很多不同 Flux 库，并且不断产出了更多函数式和响应式方案。

不过让我们看看现在的状况：

### Flux

根据我们的经历，Flux 经常被滥用，*（这意味着人们总是在不需要的时候用上它）*。

Flux 提供了一种非常清晰的存储和更新应用状态的方式，并且只会在必要的时候触发页面渲染。

Flux 致力于**应用的全局状态管理**，比如：管理已登录用户，路由状态或者是已激活账户，但若是用来管理临时数据或者本地数据，瞬间就变成了痛苦。

我们不推荐使用 Flux 来管理路由相关的数据，比如：`/items/:itemId`。而只是获取路由数据，并存储在组件的 state 之中。在这种情况下，当组件消失之后数据也就被毁掉了。

*如果你想了解更多关于 Flux 的信息，[The Evolution of Flux Frameworks](https://medium.com/@dan_abramov/the-evolution-of-flux-frameworks-6c16ad26bb31#.90lamiv5l) 非常值得一读。*

#### Use Redux | 使用 Redux

> Redux 是 JavaScript 应用的可预测状态容器。

如果你自认为需要 Flux 或者一种类似的解决方案，可以查看 [redux](https://github.com/rackt/redux) 以及 [Dan Abramov](https://twitter.com/dan_abramov) 的[Getting started with redux](https://egghead.io/series/getting-started-with-redux) 课程，能够迅速提高你的开发技能。

> Redux 改善了 Flux 想要解决的问题，但是通过 (taking cues from Elm) 规避了它的复杂度。

#### Keep your state flat | 保持状态扁平化

API 经常会返回嵌套资源。这在 Flux 或者 Redux-based 架构中处理起来会非常困难。我们推荐使用 [normalizr](https://github.com/gaearon/normalizr) 之类的库将数据进行扁平化处理，，**尽可能保持状态扁平化**。

Pros 示意：

    const data = normalize(response, arrayOf(schema.user))
    
    state = _.merge(state, data.entities)  

*（我们使用 [isomorphic-fetch](https://www.npmjs.com/package/isomorphic-fetch) 来与 APIs 进行交互）*

### Use immutable states | 使用 immutable 状态

> 可变性状态共享乃万恶之源。 - *Pete Hunt, React.js Conf 2015*

![](https://risingstack-blog.s3.amazonaws.com/2016/Jan/immutable_logo_for_react_js_best_practices-1453211749818.png)

[不可变对象](https://en.wikipedia.org/wiki/Immutable_object)是一种在创建之后就不可修改的对象。

不可变对象可以让我们免于痛楚，并且通过引用级别的等同性检查来**改善渲染性能** 。比如说在 `shouldComponentUpdate` 中：
    
    shouldComponentUpdate(nexProps) {  
     // instead of object deep comparsion
     return this.props.immutableFoo !== nexProps.immutableFoo
    }

**如何在 JavaScript 中实现不可变性呢？**

最痛苦的方式就是小心为之，示例代码如下，你需要在单元测试中通过 [deep-freeze-node](https://www.npmjs.com/package/deep-freeze-node) 来反复验证。（在修改之前冻结，并在之后验证结果。）
    
    return {  
      ...state,
      foo
    }
    
    return arr1.concat(arr2)  

相信我，这有更加显而易懂的例子。
    
最简单但也是最自然的方式就是使用 [Immutable.js](https://facebook.github.io/immutable-js/)。

    import { fromJS } from 'immutable'
    
    const state = fromJS({ bar: 'biz' })  
    const newState = foo.set('bar', 'baz')  

Immutable.js 非常之快，背后理念也异常漂亮。哪怕你并不想使用它，我也推荐阅读这个由 [Lee Byron](https://twitter.com/leeb) 所制作的视频 [Immutable Data and React](https://www.youtube.com/watch?v=I7IdS-PbEgI)。视频对于 Immutable.js 的工作原理有非常深刻的讲解。

### Observables and reactive solutions | 观察式与响应式方案

如果你不喜欢 Flux/Redux 或者只是想要更加响应式，不要失望！这儿有很多其他数据处理的解决方案。这就有一个相关库的简要列表供你参考：

  * [cycle.js](http://cycle.js.org/) *("A functional and reactive *JavaScript* framework for cleaner code")*
  * [rx-flux](https://github.com/fdecampredon/rx-flux) *("The Flux architecture with RxJS")*
  * [redux-rx](https://github.com/acdlite/redux-rx) *("RxJS utilities for Redux.")*
  * [mobservable](https://mweststrate.github.io/mobservable/) *("Observable data. Reactive functions. Simple code.")*

## Routing | 路由

几乎所有的客户端应用都或多或少需要路由。如果你在浏览器中使用 React.js，你就会在挑选库的时候遇到这种分叉点。

我们的选择是由非凡的 [rackt](https://github.com/rackt) 社区所贡献的 [react-router](https://github.com/rackt/react-router)。Racket 给 React.js 的拥簇者带来了很多高质量的资源。

可以查看他们的[文档](https://github.com/rackt/react-router/tree/master/docs)以便于集成 `react-router`，但是更重要的是：如果你使用 Flux/Redux，我们建议你将路由状态和你的 store 或者全局状态**保持同步**。

同步的路由状态将帮助你对 Flux/Redux 的 Actions 所提供的路由行为有所控制，并且能够在组件中读取路由状态和参数。

Redux 用户可以通过 [redux-simple-router](https://github.com/rackt/redux-simple-router) 这个库轻松实现它。

#### Code splitting, lazy loading | 代码分离，惰性加载

只有一小部分 `webpack` 用户知道如何分离应用代码，将 bundler 的输出拆分成多个 *JavaScript* 块：
    
    require.ensure([], () => {  
      const Profile = require('./Profile.js')
      this.setState({
        currentComponent: Profile
      })
    })
    

这在大型应用中会非常有用，因为在每次部署之后，用户浏览器就**没有必要下载那些很少用到的代码**，比如 profile 页面。

更多代码块将导致更多 HTTP 请求 —— 但是使用 [HTTP/2 multiplexed](https://http2.github.io/faq/#why-is-http2-multiplexed) 的话就不成问题。

结合 [chunk hashing](https://christianalfoni.github.io/react-webpack-cookbook/Optimizing-caching.html)，你也可以在代码改变之后优化缓存命中率。

react-router 的下个版本就将在代码分离这方面提供更多帮助。

想要了解 react-router 的未来走向，可以查看 [Ryan Florence](https://twitter.com/ryanflorence) 所写的这篇博文： [Welcome to Future of Web Application Delivery](https://medium.com/@ryanflorence/welcome-to-future-of-web-application-delivery-9750b7564d9f#.vuf3e1nqi)。

## Components | 组件

大部分人都对 JSX 存有怨言。首先，你需要知道的是这在 React 中并不是必须的。

在最后，JSX 都会通过 Babel 被编译成 *JavaScript*。你可以直接编写 *JavaScript* 来替代 JSX，但是在使用 JSX 编写 HTML 的时候会更加自然。

> JSX 是一种 *JavaScript* 语法扩展，看起来与 XML 类似。你可以通过 React 实现简单的 JSX 句法变化。 —— [JSX in depth](https://facebook.github.io/react/docs/jsx-in-depth.html)

如果你想要阅读更多关于 JSX 的信息，可以查看 [JSX Looks Like An Abomination - But it’s Good for You](https://medium.com/javascript-scene/jsx-looks-like-an-abomination-1c1ec351a918#.ca28nvee6) 这篇文章。

### Use Classes | 使用类

React 和 ES2015 搭配完美。

    class HelloMessage extends React.Component {  
      render() {
        return <div>Hello {this.props.name}</div>
      }
    }

我们喜欢[高阶组件](http://jamesknelson.com/structuring-react-applications-higher-order-components/)更胜于 mixins，所以对于我们来说，保留 `createClass` 就更像一个语法问题而不是技术问题。我们相信使用 `createClass` 而不是 `React.Component` 绝对无可厚非，反之亦然。

### PropType | 属性类型

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

### Higher order components | 高阶组件

目前来说，[mixins 已死](https://medium.com/@dan_abramov/mixins-are-dead-long-live-higher-order-components-94a0d2f9e750)，而且在 ES6 Class 组件中已经不再被支持，我们应当寻找不同的替代方案。

**那什么是高阶组件呢？**

    PassData({ foo: 'bar' })(MyComponent)  

本质上来说，你可以由原始组件创造一个新的组件并且扩展它的行为。你可以在多种情况下使用它，比如授权：`requireAuth({ role: 'admin' })(MyComponent)` *（检查上层组件中的用户，若是未登录则需要重定向）*或者是连接你的组件和 Flux/Redux 仓库。

在RisingStack，我们也将数据获取和类似于控制器的逻辑分割成高阶组件，并且保持视图尽可能简单。

## Testing | 测试

在开发周期中，维持测试的高覆盖率是非常重要的一部分。幸运的是， React.js 社区诞生了很多优秀的库可以帮助我们达到这一点。

### Component testing | 组件测试

由 AirBnb 所开发的 [enzyme](https://github.com/airbnb/enzyme)是我们最喜爱的库之一，可以用于组件测试。非常神奇的是，它的浅渲染特性，可以让你测试组件的逻辑及其渲染输出。尽管它并不能替代你的 selenium 测试，但是你可以通过使用 enzyme，从此走上前端测试的新高度。

    it('simulates click events', () => {  
      const onButtonClick = sinon.spy()
      const wrapper = shallow(
        <Foo onButtonClick={onButtonClick} />
      )
      wrapper.find('button').simulate('click')
      expect(onButtonClick.calledOnce).to.be.true
    })

看起来就非常简洁，不是么？

你在使用 chai 作为测试断言库嘛？你会喜欢 [chai-enyzime](https://github.com/producthunt/chai-enzyme) 的！

### Redux testing | Redux 测试

**测试一个 reducer** 应该很简单，它响应新到来的 actions，并且将原来的状态进行更新：

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

若是使用异步的话**测试 actions** 就很简单。对于测试异步的 Redux Actions 来说，我们推荐使用 [redux-mock-store](https://www.npmjs.com/package/redux-mock-store)，非常有帮助。

    it('should dispatch action', (done) => {  
      const getState = {}
      const action = { type: 'ADD_TODO' }
      const expectedActions = [action]
    
      const store = mockStore(getState, expectedActions, done)
      store.dispatch(action)
    })

更深度了解 [redux testing](http://rackt.org/redux/docs/recipes/WritingTests.html)，可以查看官方文档。

### Use npm | 使用 npm

尽管无须代码打包 React.js 也可以很好地工作，但是我们还是推荐使用 [Webpack](https://webpack.github.io/) 或者 [Browserify](http://browserify.org/) 来发挥 [npm](https://www.npmjs.com/) 的能力。Npm 上满是高质量的 React.js 包，并且它可以通过一种很棒的方式来帮助你管理依赖。

*（请不要忘记复用你自己的组件，这是一种非常优秀的代码优化方式。）*

### Bundle size | Bundle 大小

这不是一个 React 相关的问题，但是因为大多数人都在打包他们的 React 应用，所以我认为提到这点很重要。

当你打包源代码的时候，时刻谨记打包后的文件大小，为了**保持最小化**，你应该考虑如何 require/import 依赖。

对比以下代码片段，这两种不同的方式在输出的时候区别巨大：

    import { concat, sortBy, map, sample } from 'lodash'
    
    // vs.
    import concat from 'lodash/concat';  
    import sortBy from 'lodash/sortBy';  
    import map from 'lodash/map';  
    import sample from 'lodash/sample';  

可以查看这篇文章 [Reduce Your bundle.js File Size By Doing This One Thing](https://lacke.mn/reduce-your-bundle-js-file-size/) 获取更多详情。

我们也喜欢将代码分离出至少 `vendors.js` 和 `app.js` 两个文件，因为 vendors 相对于我们的代码库来说更新就不是那么频繁。

将输出文件名称进行哈希化处理 *(chunk hash in WebPack)*，并且为了长远考虑将其缓存，我们可以大大减少代码大小，网站用户所需要下载的文件就变少了。将其与惰性加载相结合，你可以想象一下这是何等的优化。

如果你还不太熟悉 Webpack，可以查看这本优秀的 [React webpack cookbook](https://christianalfoni.github.io/react-webpack-cookbook)。

### Component-level hot reload | 组件级别热重载

如果你曾经使用过热加载来编写单页面应用，当你编写具有状态性的东西的时候，可能你就会明白那是多么讨厌，当你在编辑器中点击保存，整个页面都重新加载了。这样就不得不重新点击一遍应用，重复如此会令人抓狂的。

通过 React，在重载组件的同时**保持组件状态**已经成为可能 —— boom，不再痛苦！（~~没有蛀牙！~~）

关于如何使用热重载，可以参考[react-transform-boilerplate](https://github.com/gaearon/react-transform-boilerplate)。

### Use ES2015 | 使用ES2015

我之前有提到过，可以在 React.js 组件中使用 JSX，然后使用[Babel.js](https://babeljs.io/)进行编译。

其实 Babel 能做到的远不止这些，它也可以让我们现在就可以给浏览器编写 ES6/ES2015 代码。在 RisingStack，我们在服务器端和客户端都使用了 ES2015 特性，这都已经在最新的 LTS Node.js 版本中被实现了。

### Linters

或许你已经给你的 *JavaScript* 代码使用了一种风格指南，但是你知道也有用于 React 的风格指南了吗？我们强烈推荐挑选一个并开始遵循它。

在 RisingStack，我们也将 linters 强制运行在 CI 系统上，`git push` 亦然。可以试试 [pre-push](https://www.npmjs.com/package/pre-push) 或者 [pre-commit](https://www.npmjs.com/package/pre-commit)。

我们为 *JavaScript* 使用了 *JavaScript* 标准风格，为 React.js 代码使用了 [eslint-plugin-react](https://www.npmjs.com/package/eslint-plugin-react)进行规范 。

*（就是，我们不再使用分号。）*

## GraphQL and Relay | GraphQL 和 Relay

GraphQL 和 Relay 相对而言属于新技术，目前在 RisingStack，我们还没有将其使用到产品环境中，只是持续保持关注。

我们曾经写过一个库叫 [graffiti](https://github.com/risingstack/graffiti)，这是一个用于 Relay 的 MongoDB ORM，可以将已有的 mongoose 模型直接创建成一个 GraphQL 服务器。

如果你想要学习这些新技术，我们建议你可以找来玩一玩。

## Takeaway from these React.js Best Practices | 尽情享用 React.js 最佳实践

有些被提及的技术和库和 React.js 并不相关 —— 但是保持视野开阔，多看看社区其他人在做些什么。 React 社区在2015年里就受到了 [Elm architecture](https://github.com/evancz/elm-architecture-tutorial/) 的很多启发。

> 如果你知道其它在2016年必不可少的 React.js 工具，请留下评论让我们知道！

------

#### [Péter Márton](https://blog.risingstack.com/author/peter-marton/)

CTO at RisingStack, brewing beer with Node.js

<https://twitter.com/slashdotpeter>


