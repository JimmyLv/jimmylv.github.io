---
layout: post
title: 【译】展望2016，React.js 最佳实践 (中英对照版)
categories: [翻译]
tags: [React, 总结]
published: True
---

# React.js Best Practices for 2016

原文地址：<https://blog.risingstack.com/react-js-best-practices-for-2016/>

Tags: [React](https://blog.risingstack.com/tag/react/) · [ReactJS](https://blog.risingstack.com/tag/reactjs/) · [best practices](https://blog.risingstack.com/tag/best-practices/) 

> **2015 was the year of [React](https://facebook.github.io/react/)** with tons of new releases and developer conferences dedicated to the topic all over the world. For a detailed list of the most important milestones of last year, check out our [React in 2015](https://blog.risingstack.com/react-in-2015/) wrap up.

过去的2015年，**[React](https://facebook.github.io/react/)** 在全世界范围都是一派欣欣向荣的景象，开发者会议无一不热衷于这个话题。在过去一年中发生了很多重要的里程碑事件，更多详情可以查看我们关于 [React in 2015](https://blog.risingstack.com/react-in-2015/) 的总结。

> The most interesting question for 2016: **How should we write an application** and what are the recommended libraries?

在新的2016年里，最有趣的问题来了：**我们该如何开发一个应用**，有什么推荐使用的库？

> > As a developer working for a long time with React.js I have my own answers and best practices, but it's possible that you won’t agree on everything with me. I’m interested in your ideas and opinions: please leave a comment so we can discuss them.

> 作为一名长时间使用 React.js 的开发者来说，我对这个问题有自己的答案以及最佳实践，但也有可能你不会完全认同。我也非常乐于倾听你的想法和观点：请留言以便讨论。

![](https://risingstack-blog.s3.amazonaws.com/2016/Jan/react_best_practices-1453211146748.png)    

> If you are just getting started with React.js, check out our [React.js tutorial](https://blog.risingstack.com/the-react-way-getting-started-tutorial/), or the [React howto](https://github.com/petehunt/react-howto) by Pete Hunt.

如果你才刚刚开始学习 React.js，可以查看我们的 [React.js 教程](https://blog.risingstack.com/the-react-way-getting-started-tutorial/)，或者 Pete Hunt 所写的 [React howto](https://github.com/petehunt/react-howto)。

## Dealing with data | 数据处理

> Handling data in a React.js application is super easy, but challenging at the same time.   

在 React.js 应用中处理数据轻而易举，与此同时亦充满挑战。

> It happens because you can pass properties to a React component in a lot of ways to build a rendering tree from it; however it's not always obvious how you should update your view.

这是因为你可以通过各种方式将属性数据传递给 React 组件，并从中构建渲染树；然而这种方式也并非那么显而易见，到底该如何更新视图。

> 2015 started with the releases of different Flux libraries and continued with more functional and reactive solutions.

2015之初诞生了很多不同 Flux 库，并不断产出了更加实用的响应式方案。

> Let's see where we are now:

让我们看看现在的情况：

### Flux

> According to our experience, Flux is often overused *(meaning that people use it even if they don't even need it)*.

根据我们的经验，Flux 经常被滥用，*（这意味着大家总是在不需要的时候就用上它）*。

> Flux provides a clean way to store and update your application's state and trigger rendering when it's needed.

Flux 提供了一种非常清晰的方式来存储和更新应用状态，并且只会在必要的时候才触发页面渲染。

> Flux can be **useful for the app's global states** like: managing logged in user, the state of a router or active account but it can turn quickly into pain if you start to manage your temporary or local data with it.

Flux 致力于**应用的全局状态管理**，比如：管理已登录用户状态，路由状态，或者是活跃账户状态，但若是用来管理临时数据或者本地数据，瞬间就变成了痛苦。

> We don’t recommend using Flux for managing route-related data like `/items/:itemId`. Instead, just fetch it and store it in your component's state. In this case, it will be destroyed when your component goes away.

我们不推荐使用 Flux 来管理路由相关的数据，比如 `/items/:itemId`。而只是获取路由数据并存储在组件的 state 之中。在这种情况下，它会在组件消失之后一起被销毁。

> *If you need more info about Flux, [The Evolution of Flux Frameworks](https://medium.com/@dan_abramov/the-evolution-of-flux-frameworks-6c16ad26bb31#.90lamiv5l) is a great read.*

*如果你想了解更多关于 Flux 的信息，[The Evolution of Flux Frameworks](https://medium.com/@dan_abramov/the-evolution-of-flux-frameworks-6c16ad26bb31#.90lamiv5l) 非常值得一读。*

#### Use Redux | 使用 Redux

> > Redux is a predictable state container for *JavaScript* apps.

> Redux 是一个 JavaScript 应用的可预测状态容器。

> If you think you need Flux or a similar solution you should check out [redux](https://github.com/rackt/redux) and [Dan Abramov](https://twitter.com/dan_abramov)'s [Getting started with redux](https://egghead.io/series/getting-started-with-redux) course to quickly boost your development skills.

如果你觉得需要 Flux 或者一种类似的解决方案，你应该了解一下 [redux](https://github.com/rackt/redux)，以及学习 [Dan Abramov](https://twitter.com/dan_abramov) 的[Getting started with redux](https://egghead.io/series/getting-started-with-redux) 课程，这能够迅速提高你的开发技能。

> > Redux evolves the ideas of Flux but avoids its complexity by taking cues from Elm.

> Redux 延续并改进了 Flux 的思想，并从 Elm 架构中取经，规避了 Flux 的复杂度。（译者注：Elm 是一门面向 Web 的函数式编程语言，致力于改善客户端 Web 编程体验。）

#### Keep your state flat | 保持状态扁平化

> API's often return nested resources. It can be hard to deal with them in a Flux or Redux-based architecture. We recommend to flatten them with a library like [normalizr](https://github.com/gaearon/normalizr) and **keep your state as flat as possible**.

API 经常会返回嵌套资源。这在 Flux 或基于 Redux 的架构中处理起来会非常困难。我们推荐使用 [normalizr](https://github.com/gaearon/normalizr) 之类的库将数据进行扁平化处理，**保持状态尽可能地扁平化**。

> Hint for pros: 

示意：

    const data = normalize(response, arrayOf(schema.user))
    
    state = _.merge(state, data.entities)  

> *(we use [isomorphic-fetch](https://www.npmjs.com/package/isomorphic-fetch) to communicate with our APIs)*

*（我们使用 [isomorphic-fetch](https://www.npmjs.com/package/isomorphic-fetch) 来与 APIs 进行交互）*

### Use immutable states | 使用 immutable 状态

> > Shared mutable state is the root of all evil - *Pete Hunt, React.js Conf 2015*

> 共享的可变性状态乃万恶之源。 —— *Pete Hunt, React.js Conf 2015*

![](https://risingstack-blog.s3.amazonaws.com/2016/Jan/immutable_logo_for_react_js_best_practices-1453211749818.png)

> [Immutable object](https://en.wikipedia.org/wiki/Immutable_object) is an object whose state cannot be modified after it is created.

[不可变对象](https://en.wikipedia.org/wiki/Immutable_object)是一种在创建之后就不可修改的对象。

> Immutable objects can save us all a headache and **improve the rendering performance** with their reference-level equality checks. Like in the `shouldComponentUpdate`:

不可变对象可以让我们免于痛楚，并通过引用级别的比对检查来**改善渲染性能** 。比如说在 `shouldComponentUpdate` 中：
    
    shouldComponentUpdate(nexProps) {  
     // instead of object deep comparsion
     return this.props.immutableFoo !== nexProps.immutableFoo
    }

> **How to achieve immutability in *JavaScript*?**   

**如何在 JavaScript 中实现不可变呢？**

> The hard way is to be careful and write code like the example below, which you should always check in your unit tests with [deep-freeze-node](https://www.npmjs.com/package/deep-freeze-node) *(freeze before the mutation and verify the result after it)*. 

最痛苦的方式就是小心为之，示例代码如下，你需要在单元测试中通过 [deep-freeze-node](https://www.npmjs.com/package/deep-freeze-node) 来反复验证。（在修改之前冻结，并在结束后验证结果。）
    
    return {  
      ...state,
      foo
    }
    
    return arr1.concat(arr2)  

> Believe me, these were the pretty obvious examples.

相信我，这是最平淡无奇的例子了。

> The less complicated way but also less natural one is to use [Immutable.js](https://facebook.github.io/immutable-js/).
    
更简单也更自然的方式就是使用 [Immutable.js](https://facebook.github.io/immutable-js/)。

    import { fromJS } from 'immutable'
    
    const state = fromJS({ bar: 'biz' })  
    const newState = foo.set('bar', 'baz')  

> Immutable.js is fast, and the idea behind it is beautiful. I recommend watching the [Immutable Data and React](https://www.youtube.com/watch?v=I7IdS-PbEgI) video by [Lee Byron](https://twitter.com/leeb) even if you don't want to use it. It will give deep insight to understand how it works.

Immutable.js 非常之快，背后理念也异常漂亮。哪怕你并不想使用它，我也推荐阅读这个由 [Lee Byron](https://twitter.com/leeb) 所制作的视频 [Immutable Data and React](https://www.youtube.com/watch?v=I7IdS-PbEgI)。视频对于 Immutable.js 的工作原理有着非常深刻的讲解。

### Observables and reactive solutions | 观察式与响应式方案

> If you don't like Flux/Redux or just want to be more reactive, don't be disappointed! There are other solutions to deal with your data. Here is a short list of libraries what you are probably looking for:

如果你不喜欢 Flux/Redux 或者只是想要更加 reactive，不要失望！这儿有很多其他数据处理的解决方案。这就有一个相关库的简要列表供你参考：

  * [cycle.js](http://cycle.js.org/) *("A functional and reactive *JavaScript* framework for cleaner code")*
  * [rx-flux](https://github.com/fdecampredon/rx-flux) *("The Flux architecture with RxJS")*
  * [redux-rx](https://github.com/acdlite/redux-rx) *("RxJS utilities for Redux.")*
  * [mobservable](https://mweststrate.github.io/mobservable/) *("Observable data. Reactive functions. Simple code.")*

## Routing | 路由

> Almost every client side application has some routing. If you are using React.js in a browser, you will reach the point when you should pick a library.

几乎所有的客户端应用都或多或少需要使用路由。如果你在浏览器中使用 React.js，你就会在挑选库的时候碰到这个分歧点。

> Our chosen one is the [react-router](https://github.com/rackt/react-router) by the excellent [rackt](https://github.com/rackt) community. Rackt always ships quality resources for React.js lovers.

我们的选择是出自优秀的 [rackt](https://github.com/rackt) 社区的 [react-router](https://github.com/rackt/react-router)。Racket 给 React.js 的拥簇者带来了很多高质量资源。

> To integrate `react-router` check out their [documentation](https://github.com/rackt/react-router/tree/master/docs), but what's more important here: if you use Flux/Redux we recommend to **keep your router's state in sync** with your store/global state.

你可以查看他们的[文档](https://github.com/rackt/react-router/tree/master/docs)以便于集成 `react-router`，但是更重要的是：如果你使用 Flux/Redux，我们建议你将路由状态和你的 store 或全局状态**保持同步**。

> Synchronized router states will help you to control router behaviors by Flux/Redux actions and read router states and parameters in your components.

同步的路由状态可以帮助你对 Flux/Redux 的 Actions 所提供的路由行为有所控制，并且能够在组件中读取路由状态和参数。

> Redux users can simply do it with the [redux-simple-router](https://github.com/rackt/redux-simple-router) library.

Redux 用户可以通过 [redux-simple-router](https://github.com/rackt/redux-simple-router) 这个库轻松实现它。

#### Code splitting, lazy loading | 代码分割，惰性加载

> Only a few of `webpack` users know that it's possible to split your application’s code to separate the bundler's output to multiple *JavaScript* chunks:

只有一小部分 `webpack` 用户知道应用代码是可以分割的，将 bundler 的输出拆分成多个 *JavaScript* 块：
    
    require.ensure([], () => {  
      const Profile = require('./Profile.js')
      this.setState({
        currentComponent: Profile
      })
    })

> It can be extremely useful in large applications because the user's browser **doesn't have to download rarely used codes** like the profile page after every deploy.

这在大型应用中会非常有用，因为在每次部署之后，用户浏览器就**没有必要下载那些很少用到的代码**，比如 profile 页面。

> Having more chunks will cause more HTTP requests - but that’s not a problem with [HTTP/2 multiplexed](https://http2.github.io/faq/#why-is-http2-multiplexed).

更多代码块将导致更多 HTTP 请求 —— 但是使用 [HTTP/2 multiplexed](https://http2.github.io/faq/#why-is-http2-multiplexed) 的话就不成问题。

> Combining with [chunk hashing](https://christianalfoni.github.io/react-webpack-cookbook/Optimizing-caching.html) you can also optimize your cache hit ratio after code changes.

结合 [chunk hashing](https://christianalfoni.github.io/react-webpack-cookbook/Optimizing-caching.html)，你也可以在代码改变之后优化缓存命中率。（译者注：终端用户访问加速节点时，如果该节点有缓存住了要被访问的数据时就叫做命中，如果没有的话需要回原服务器获取，就是没有命中。）

> The next version of react-router will help a lot in code splitting.

react-router 的下个版本就将在代码分割这方面提供更多帮助。

> For the future of react-router check out this blog post by [Ryan Florence](https://twitter.com/ryanflorence): [Welcome to Future of Web Application Delivery](https://medium.com/@ryanflorence/welcome-to-future-of-web-application-delivery-9750b7564d9f#.vuf3e1nqi).

想要了解 react-router 的未来走向，可以查看 [Ryan Florence](https://twitter.com/ryanflorence) 所写的这篇博文： [Welcome to Future of Web Application Delivery](https://medium.com/@ryanflorence/welcome-to-future-of-web-application-delivery-9750b7564d9f#.vuf3e1nqi)。

## Components | 组件

> A lot of people are complaining about JSX. First of all, you should know that it’s optional in React.

大部分人都对 JSX 存有怨言。首先，你需要知道的是这在 React 中并不是必须的。

> At the end of the day, it will be compiled to *JavaScript* with Babel. You can write *JavaScript* instead of JSX, but it feels more natural to use JSX while you are working with HTML.   

在最后，JSX 都会通过 Babel 被编译成 *JavaScript*。你可以直接编写 *JavaScript* 来替代 JSX，但是在处理 HTML 的时候使用 JSX 会感觉更加自然。

> Especially because even less technical people could still understand and modify the required parts.

特别是对于不懂技术的人来说，他们依然可以理解和修改必要的部分。

> > JSX is a *JavaScript* syntax extension that looks similar to XML. You can use a simple JSX syntactic transform with React. - [JSX in depth](https://facebook.github.io/react/docs/jsx-in-depth.html)

> JSX 是一种与 XML 类似的 *JavaScript* 语法扩展。你可以通过一个简单的 JSX 语法转换器来编译 React。 —— [JSX in depth](https://facebook.github.io/react/docs/jsx-in-depth.html)

> If you want to read more about JSX check out the [JSX Looks Like An Abomination - But it’s Good for You](https://medium.com/javascript-scene/jsx-looks-like-an-abomination-1c1ec351a918#.ca28nvee6) article.

如果你想要了解更多关于 JSX 的信息，可以查看 [JSX Looks Like An Abomination - But it’s Good for You](https://medium.com/javascript-scene/jsx-looks-like-an-abomination-1c1ec351a918#.ca28nvee6) 这篇文章。

### Use Classes | 使用类

> React works well with ES2015 classes.

React 和 ES2015 的 Class 语法搭配完美。

    class HelloMessage extends React.Component {  
      render() {
        return <div>Hello {this.props.name}</div>
      }
    }

> We prefer higher order components over mixins so for us leaving `createClass` was more like a syntactical question rather than a technical one. We believe there is nothing wrong with using `createClass` over `React.Component` and vice-versa.

我们喜欢[高阶组件](http://jamesknelson.com/structuring-react-applications-higher-order-components/)更胜于 mixins，所以对于我们来说，保留 `createClass` 就更像一个语法问题而不是技术问题。我们相信使用 `createClass` 而不是 `React.Component` 绝对无可厚非，反之亦然。

### PropType | 属性类型

> If you still don't check your properties, you should start 2016 with fixing this. It can save hours for you, believe me.

如果你在2016年依然没有检查 properties，那么你应该从现在开始做起，这将为你节省大量时间，相信我。

    MyComponent.propTypes = {  
      isLoading: PropTypes.bool.isRequired,
      items: ImmutablePropTypes.listOf(
        ImmutablePropTypes.contains({
          name: PropTypes.string.isRequired,
        })
      ).isRequired
    }

> Yes, it's possible to validate Immutable.js properties as well with [react-immutable-proptypes](https://www.npmjs.com/package/react-immutable-proptypes).

当然，验证 Immutable.js 所编写的 properties 也是可能的，可以使用[react-immutable-proptypes](https://www.npmjs.com/package/react-immutable-proptypes)。

### Higher order components | 高阶组件

> Now that [mixins are dead](https://medium.com/@dan_abramov/mixins-are-dead-long-live-higher-order-components-94a0d2f9e750) and not supported in ES6 Class components we should look for a different approach.

目前来说，[mixins 已死](https://medium.com/@dan_abramov/mixins-are-dead-long-live-higher-order-components-94a0d2f9e750)，而且在 ES6 Class 组件中已经不再被支持，我们应当寻找不同的替代方案。

> **What is a higher order component?**

**那什么是高阶组件呢？**

    PassData({ foo: 'bar' })(MyComponent)  

> Basically, you compose a new component from your original one and extend its behaviour. You can use it in various situations like authentication: `requireAuth({ role: 'admin' })(MyComponent)` *(check for a user in higher component and redirect if the user is not logged in)* or connecting your component with Flux/Redux store.

本质上来说，你可以由原始组件创造一个新的组件并且扩展它的行为。你可以在多种情况下使用它，比如授权：`requireAuth({ role: 'admin' })(MyComponent)` *（检查上层组件中的用户，若是未登录则需要重定向）*，或者是连接你的组件和 Flux/Redux 仓库。

> At RisingStack, we also like to separate data fetching and controller-like logic to higher order components and keep our views as simple as possible.

在RisingStack，我们也将数据获取和类 Controller 的逻辑分割成高阶组件，并保持视图层尽可能简单。

## Testing | 测试

> Testing with good test coverage must be an important part of your development cycle. Luckily, the React.js community came up with excellent libraries to help us achieve this. 

在开发周期中，维持测试的高覆盖率是非常重要的一部分。幸运的是， React.js 社区诞生了很多优秀的库可以帮助我们达到这一点。

### Component testing | 组件测试

> One of our favorite library for component testing is [enzyme](https://github.com/airbnb/enzyme) by AirBnb. With it's shallow rendering feature you can test logic and rendering output of your components, which is pretty amazing. It still cannot replace your selenium tests, but you can step up to a new level of frontend testing with it.

我们最喜爱的库之一是由 AirBnb 所开发的 [enzyme](https://github.com/airbnb/enzyme)，可用于组件测试。非常神奇的是，它的浅渲染特性可以对组件的逻辑及其渲染输出进行测试。尽管它还不能替代你的 selenium 测试，但是将前端测试提升到了一个新的水平。

    it('simulates click events', () => {  
      const onButtonClick = sinon.spy()
      const wrapper = shallow(
        <Foo onButtonClick={onButtonClick} />
      )
      wrapper.find('button').simulate('click')
      expect(onButtonClick.calledOnce).to.be.true
    })

> Looks neat, isn't it?

看起来就非常简洁，不是么？

> Do you use chai as assertion library? You will like [chai-enyzime](https://github.com/producthunt/chai-enzyme)!

你在使用 chai 作为测试断言库嘛？相信你会喜欢 [chai-enyzime](https://github.com/producthunt/chai-enzyme) 的！

### Redux testing | Redux 测试

> **Testing a reducer** should be easy, it responds to the incoming actions and turns the previous state to a new one:

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

> **Testing actions** is simple until you start to use async ones. For testing async redux actions we recommend to check out [redux-mock-store](https://www.npmjs.com/package/redux-mock-store), it can help a lot.

**测试 actions** 也很简单，但是异步 actions 就不太一样了。对于测试异步的 Redux actions 来说，我们推荐使用 [redux-mock-store](https://www.npmjs.com/package/redux-mock-store)，非常有帮助。

    it('should dispatch action', (done) => {  
      const getState = {}
      const action = { type: 'ADD_TODO' }
      const expectedActions = [action]
    
      const store = mockStore(getState, expectedActions, done)
      store.dispatch(action)
    })

> For deeper [redux testing](http://rackt.org/redux/docs/recipes/WritingTests.html) visit the official documentation.

更深度地了解 [redux 测试](http://rackt.org/redux/docs/recipes/WritingTests.html)，可以查看官方文档。

### Use npm | 使用 npm

> However React.js works well without code bundling we recommend using [Webpack](https://webpack.github.io/) or [Browserify](http://browserify.org/) to have the power of [npm](https://www.npmjs.com/). Npm is full of quality React.js packages, and it can help to manage your dependencies in a nice way.

虽然 React.js 并不依赖代码打包工具就可以很好地工作，但我们还是推荐使用 [Webpack](https://webpack.github.io/) 或者 [Browserify](http://browserify.org/) 来发挥 [npm](https://www.npmjs.com/) 的能力。Npm 上满是高质量的 React.js 包，还可以帮你非常优雅地管理依赖。

> *(Please don’t forget to reuse your own components, it’s an excellent way to optimize your code.)*

*（请不要忘记复用你自己的组件，这是一种绝佳的代码优化方式。）*

### Bundle size | Bundle 大小

> This question is not React-related but because most people bundle their React application I think it’s important to mention it here.

这本身不是一个 React 相关的问题，但是大多数人都在打包他们的 React 应用，所以我认为提到这点很重要。

> While you are bundling your source code, always be aware of your bundle’s file size. To **keep it at the minimum** you should consider how you require/import your dependencies.

当你打包源代码的时候，时刻警惕打包后的文件大小。为了**保持体积最小化**，你应该考虑如何 require/import 依赖。

> Check the following code snippet, the two different way can make a huge difference in the output: 

对比以下代码片段，这两种不同的方式对输出的影响区别巨大：

    import { concat, sortBy, map, sample } from 'lodash'
    
    // vs.
    import concat from 'lodash/concat';  
    import sortBy from 'lodash/sortBy';  
    import map from 'lodash/map';  
    import sample from 'lodash/sample';  

> Check out the [Reduce Your bundle.js File Size By Doing This One Thing](https://lacke.mn/reduce-your-bundle-js-file-size/) for more details.

可以查看这篇文章 [Reduce Your bundle.js File Size By Doing This One Thing](https://lacke.mn/reduce-your-bundle-js-file-size/) 获取更多详情。

> We also like to split our code to least `vendors.js` and `app.js` because vendors updates less frequently than our code base.  

我们也喜欢将代码分离出至少 `vendors.js` 和 `app.js` 两个文件，因为 vendors 相对于我们的代码库来说更新不是那么频繁。

> With hashing the output file names *(chunk hash in WebPack)* and caching them for the long term, we can dramatically reduce the size of the code what needs to be downloaded by returning visitors on the site. Combining it with lazy loading you can imagine how optimal can it be.

将输出文件名称进行哈希化处理 *(Webpack 中的 chunk hash)*，并使用长缓存，我们可以大大减少用户需要下载的代码大小。结合惰性加载，优化效果可想而知。

> If you are new to Webpack, check out this excellent [React webpack cookbook](https://christianalfoni.github.io/react-webpack-cookbook).

如果你还不太熟悉 Webpack，可以查看这本优秀的 [React webpack 手册](https://christianalfoni.github.io/react-webpack-cookbook)。

### Component-level hot reload | 组件级别热重载

> If you ever wrote a single page application with livereload, probably you know how annoying it is when you are working on something stateful, and the whole page just reloads while you hit a save in your editor. You have to click through the application again, and you will go crazy repeating this a lot.

如果你曾经使用过热加载来编写单页面应用，当你在处理某些与状态相关的事情时，可能你就会明白当你在编辑器中点击保存，整个页面就重新加载了是多么令人讨厌。这样子就不得不重新点击一遍应用，重复如此会令人抓狂的。

> With React, it's possible to reload a component while **keeping its states** - boom, no more pain!

通过 React，在重载组件的同时**保持组件状态**已经成为可能 —— 耶，从此不再痛苦！（~~没有蛀牙！~~）

> To setup hot reload check out the [react-transform-boilerplate](https://github.com/gaearon/react-transform-boilerplate).

关于如何搭建热重载，可以参考 [react-transform-boilerplate](https://github.com/gaearon/react-transform-boilerplate)。

### Use ES2015 | 使用ES2015
 
![](https://risingstack-blog.s3.amazonaws.com/2016/Jan/babel_logo_in_react_js_best_practices_2016-1453212218011.png)

> I mentioned that we use JSX in our React.js components what we transpile with [Babel.js](https://babeljs.io/).

前面有提到过，我们可以在 React.js 组件中使用 JSX，然后使用[Babel.js](https://babeljs.io/)进行编译。

> Babel can do much more and also makes possible to write ES6/ES2015 code for browsers today. At RisingStack, we use ES2015 features on both server and client side which are available in the latest LTS Node.js version.

其实 Babel 的能力远不止如此，它也可以让我们现在就可以给浏览器编写 ES6/ES2015 代码。在 RisingStack，我们在服务器端和客户端都使用了 ES2015 特性，这都已经在最新的 LTS Node.js 版本中被实现了。

### Linters

> Maybe you already use a style guide for your *JavaScript* code but did you know that there are style guides for React as well? We highly recommend to pick one and start following it.

或许你已经给你的 *JavaScript* 代码制定了代码规范，但是你知道也有用于 React 的代码规范了吗？我们强烈推荐挑选一个并开始遵循它。

> At RisingStack, we also enforce our linters to run on the CI system and for `git push` as well. Check out [pre-push](https://www.npmjs.com/package/pre-push) or [pre-commit](https://www.npmjs.com/package/pre-commit).

在 RisingStack，我们也将 linters 强制运行在 CI 系统上，`git push` 亦然。可以试试 [pre-push](https://www.npmjs.com/package/pre-push) 或者 [pre-commit](https://www.npmjs.com/package/pre-commit)。

> We use *JavaScript* Standard Style for *JavaScript* with [eslint-plugin-react](https://www.npmjs.com/package/eslint-plugin-react) to lint our React.js code.

我们使用标准的 *JavaScript* 代码风格，并使用了 [eslint-plugin-react](https://www.npmjs.com/package/eslint-plugin-react)对 React.js 代码进行规范 。

> *(That's right, we do not use semicolons anymore.)*

*（就是，我们不再使用分号。）*

## GraphQL and Relay | GraphQL 和 Relay

> GraphQL and Relay are relatively new technologies. At RisingStack, we don’t use it in production for now, just keeping our eyes open.

GraphQL 和 Relay 相对而言属于新技术，在 RisingStack，目前我们还没有在产品环境中使用它们，暂时保持关注。

> We wrote a library called [graffiti](https://github.com/risingstack/graffiti) which is a MongoDB ORM for Relay and makes it possible to create a GraphQL server from your existing mongoose models.   

我们曾经写过一个 Relay 的 MongoDB ORM库，叫做 [graffiti](https://github.com/risingstack/graffiti)，可以使用已有的 mongoose 模型直接创建一个 GraphQL 服务器。

> If you would like to learn these new technologies we recommend to check it out and play with it.

如果你想要学习这些新技术，我们建议你可以找来玩一玩。

## Takeaway from these React.js Best Practices | 尽情享用这些 React.js 最佳实践

> Some of the highlighted techniques and libraries are not React.js related at all - always keep your eyes open and check what others in the community do. The React community is inspired a lot by the [Elm architecture](https://github.com/evancz/elm-architecture-tutorial/) in 2015.

有些突出的技术和库其实跟 React.js 并不相关 —— 但是保持视野开阔，关注社区的其他人都在做些什么。React 社区在2015年里就受到了 [Elm 架构](https://github.com/evancz/elm-architecture-tutorial/) 的很多启发。

> > If you know about other essential React.js tools that people should use in 2016, let us know in the comments!

> 如果你知道其它在2016年必不可少的 React.js 工具，请留言让我们知道！

------

#### 原作者: [Péter Márton](https://blog.risingstack.com/author/peter-marton/)

CTO at RisingStack, brewing beer with Node.js

<https://twitter.com/slashdotpeter>


