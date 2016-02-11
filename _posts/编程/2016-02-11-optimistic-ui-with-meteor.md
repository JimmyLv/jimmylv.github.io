---
layout: post
title: 使用 Meteor 构建「乐观的用户界面」
categories: [编程]
tags: [Meteor, JavaScript]
published: True

---

# Optimistic UI with Meteor | Meteor，致 UI 以乐观/使用 Meteor 构建「乐观的 UI」/延时补偿

May 27, 2015  By [Sashko Stubailo](http://info.meteor.com/blog/author/sashko-stubailo)

In this post we'll look at the collection of technologies that Meteor provides to enable 'Optimistic UI' updating. This capability is crucial to user expectations for modern web apps and is fundamental to Meteor.

在这篇博文中，我们就来看看 Meteor 为「乐观的 UI 更新」所提供的一系列技术。从用户对于现代 web 应用的期望来说，这种能力是非常之重要的，这对于 Meteor 来说也是至关重要的。

Meteor is a full-stack *JavaScript* platform with default technologies for every layer of the stack, starting with the database and ending with reactive UI re-rendering. You can swap these technologies out to suit your preference; for instance you can exchange the default [Blaze](https://www.meteor.com/blaze) front-end for [React](https://github.com/reactjs/react-meteor), *[Angular](http://angular-meteor.com/?__hstc=256467284.fe209fe52e5c6f2f467c8fba76fdf5a5.1436786287820.1454516487610.1454572978838.27&__hssc=256467284.2.1454572978838&__hsfp=1792478999)*, or a native [iOS front-end](https://github.com/martijnwalraven/meteor-ios).

Meteor 是一个全栈 *JavaScript* 平台，在从数据库到响应式 UI 渲染的每一部分都提供了默认解决方案。你也可以将其换成适合于自己的选择，比如说你可以将默认的 [Blaze](https://www.meteor.com/blaze) 前端换成 [React](https://github.com/reactjs/react-meteor)，*[Angular](http://angular-meteor.com/?__hstc=256467284.fe209fe52e5c6f2f467c8fba76fdf5a5.1436786287820.1454516487610.1454572978838.27&__hssc=256467284.2.1454572978838&__hsfp=1792478999)*，或者是原生的 [iOS 前端](https://github.com/martijnwalraven/meteor-ios)。

But there's one part that represents the core of the Meteor platform: full-stack data integration with [DDP](https://www.meteor.com/ddp), [LiveQuery](https://www.meteor.com/livequery), and [Minimongo](https://www.meteor.com/mini-databases). In this case the full-stack integration provides real value that would be hard to rebuild from separate components. Let me tell you why.

但也有一部分是代表着 Meteor 平台的核心部分：使用 [DDP](https://www.meteor.com/ddp)，[LiveQuery](https://www.meteor.com/livequery)，[Minimongo](https://www.meteor.com/mini-databases) 构建的全栈数据集成方案。在这种情况下，全栈集成提供了难以从独立组件中重建的真正价值。让我来告诉你为什么。

### TL;DR | "Too long; didn't read" / 太长不读版

Your app should be able to respond to user inputs faster than it takes to make a whole roundtrip to the server — we call this Optimistic UI updating. It's very hard to build an app that correctly implements client-side simulations as it takes a lot of work to make your UI consistent, avoid loading duplicate data over and over, and keep your client up to date with your server data. Keep reading to see why you need this, why it's hard and how Meteor makes it easy.

你的应用应当更快地响应用户输入，而不是等待它从服务器完成了整个来回 —— 我们称之为「乐观的 UI 更新」。构建应用时正确实现客户端模拟是非常困难的，因为这需要大量工作来保持 UI 一致、避免重复数据加载、以及保持客户端与服务器端数据更新。继续阅读，来看看需要为何这样做，为何如此之难，以及 Meteor 是如何使之变得容易。

![](http://cdn2.hubspot.net/hubfs/520701/Blog/optimistic-ui-latency-compensation.png?t=1454978788743)

### Users of modern web apps expect the UI to respond instantly | 用户期望现代 web 应用 UI 即时响应

When a user pushes a button in a website or a mobile app, they don't want to wait for a request to be sent all the way to the server to calculate the new state of the screen. Using the basic AJAX model of calculating the results on the server and then displaying them to the user will cause your app to feel laggy, and sometimes inconsistent with the user's input. Mobile developers especially need to worry about this because cellular networks can be unreliable, sometimes taking a second or more to deliver a result from your server.

当用户点击了网站或者移动应用的按钮之后，他们并不想要等待一个请求发送至服务器进行计算后，再在屏幕显示新状态。使用基本的 AJAX 模型需要在服务器端进行计算后才能够显示给用户，这会导致你的应用感觉滞后并且出现与用户输入不一致的情况。移动开发者尤其需要担心这种问题，因为移动网络稳定性较差，有时从服务器端返回结果需要花上一秒甚至更长时间。

There are four elements required to satisfy this expectation and requirement. Let's explore those.

满足期望和需求的四个必要元素如下，让我们来瞅瞅：

### 1\. To have your app respond instantly, you need to render the UI on the client | 应用即时响应，需在客户端渲染 UI

This is one explanation for the rise of client-side rendering frameworks like *Angular* and React — you need to be able to compute your HTML directly in the browser to be able to update the view without doing a round trip to the server. Whenever the user takes an action, you need to first update your UI to make things look fast, then send a request to the server to do that modification on the real database. At Meteor, we call this Optimistic UI, or latency compensation.

这是客户端渲染框架如 *Angular* 和 React 兴起的一个事实 —— 你需要在浏览器中直接计算 HTML 从而更新视图，而不是从服务器端重新走一遭。无论何时用户触发了一个操作，你需要首先更新 UI 使之看起来迅速，然后发送给服务器端去做真正的数据库修改操作。在 Meteor 中，我们称之为 Optimistic UI（暂且译为「积极的 UI」），或者是延时补偿。

In order to make optimistic updates and be able to predict the state of the UI after some user action, you will need to keep some of your application data on the client.

为了达到[乐观更新]，并且能够预测用户操作后的 UI 状态，你需要在客户端保存一些应用数据。

One option is to directly store things inside the front-end framework's local state — *Angular*'s `$scope` or React's component state — but you can imagine how this would easily result in duplication of data or inconsistency. If you have two widgets on the page showing the same data in different ways, then they will each have one copy of the data, and worse those copies might not be consistent. Having two UI elements on your page showing inconsistent results sounds like a great way to end up with confused users.

一个可选项就是直接在前端框架的本地状态中进行存储 —— 比如 *Angular* 的 `$scope` 或者是 React 的组件状态 —— 但可想而知，很容易就会导致数据的重复和不一致。如果你在同一页面的两个部分分别使用不同的方式显示相同的数据，然后他们都会有这个数据的拷贝，更糟糕的是这些拷贝很可能不一致。在页面上拥有两个显示不同结果的 UI 元素，这会使用户非常困惑，从而流失用户。

So what's the solution - how do we keep all of our UI state de-duplicated and internally consistent?

所以何为答案 —— 我们如何使所有的 UI 状态避免重复并且实质性一致？

### 2\. To have your UI consistent and avoid data duplication, you need a global data cache on the client | 保持 UI 一致，避免数据重复，需在客户端缓存全局数据

If you want your UI to be consistent and avoid loading the same data sets over and over again, you need to render everything from the same data source. When you make some action on the page and update this global data source, that can trigger updates in all of the relevant UI elements on the page to keep everything consistent. It's almost like magic — you can update your whole UI before you even hit the server.

如果你想要 UI 保持一致，并且避免相同数据集反复加载，需要从同一数据源渲染所有东西。当你在页面上触发某些操作，并且更新全局的数据源，这些数据会触发页面上所有的相关 UI 元素更新，从而使一切保持一致性。这就像魔术一样 —— 你可以在连接服务器之前就更新了整个 UI。

#### Minimongo is Meteor's single source of truth for the client | Minimongo 就是 Meteor 在客户端上单一资源的真相

Meteor is the only framework that includes a first-class solution for this problem, and it's called [Minimongo](https://www.meteor.com/mini-databases). The same way that your database is a single source of truth for your server, Minimongo is a single source of truth for the client. If you have two widgets that display overlapping data, you can render them both from a reactive query on this client-side database and they are guaranteed to be consistent.

Meteor 是为此问题提供一流解决方案的唯一框架，称之为 [Minimongo](https://www.meteor.com/mini-databases)。与此同时，数据库是在服务器端的[单一资源真相]，而 Minimongo 则是客户端的[单一资源真相]。如果你有两个显示[重叠]数据的部件，你可以在客户端数据库的响应式查询中共同渲染两部分，两者必然是一致的。

#### Run the same queries on the client and server | 在客户端和服务器端执行相同的查询

As you might be able to tell from the name, Minimongo uses a direct clone of MongoDB's query language to client-side *JavaScript*. This is nice because you can use the same code on the client and the server to get and update your data, making it even easier to write optimistic UI update code. Meteor has had this component since day one — it's a core part of how Meteor's magic works.

可能你已经从名字中猜到，Minimongo 直接在客户端 *JavaScript* 中使用了和 MongoDB 一致的查询语言。这非常棒，因为你可以在客户端和服务器端使用同样的代码来获取和更新数据，这使得编写 optimistic UI 更新的代码变得更加容易。Meteor 自第一天开始就拥有了这个组件 —— 这是 Meteor 的魔法如何工作的核心部分。

### 3\. To populate your data cache, you need a protocol for data subscriptions | 为了实现数据缓存，需要数据订阅的某种协议

Now that you know you need to put some of our data in a local cache on the client, you need a way to get it there and keep it up to date. This is where another core part of Meteor comes in — data subscriptions over [DDP](https://www.meteor.com/ddp), Meteor's data synchronization protocol.

既然你知道需要将我们的数据放入客户端的本地缓存当中，你需要一种方式从中获取数据并使之保持更新。这是 Meteor 诞生的另一核心部分 —— 建立于 [DDP](https://www.meteor.com/ddp) 之上的数据订阅，Meteor 的数据同步协议。

When a new part of your application is displayed, it can request data to be loaded by registering a subscription, which is a request to the server to send over some data and put it into Minimongo on the client. Now, you can just render your UI components from Minimongo, and trust that the correct data will be there as soon as it is loaded. When the data is no longer needed, you can just unsubscribe and it will go away.

当你的应用程序显示新的部分时，它可以通过注册一个订阅来请求将被加载的数据，这将请求服务器播送一些数据，并将之放入客户端的 Minimongo。现在，你就可以从 Minimongo 中渲染 UI 组件了，并确定正确的数据只要一被加载就会出现在那里。当你这些数据不再需要的时候，你可以取消订阅，它就会随之消失。

Subscriptions in Meteor have some awesome features:

1. They de-duplicate data. You will never end up with two copies of the same data inside Minimongo.
2. They deliver realtime updates. You don't have to manually poll or ask for updates; when new data shows up on the server, it will be automatically delivered to all of the clients that have subscribed to it.


Meteor 中的订阅有一些非常棒的特性：

1. 无重复数据。你将无需在 Minimongo 中存储相同数据的两份拷贝。
2. [投递]实时更新。你不再需要手动检查或请求更新；当新的数据出现在服务器中，它将会自动被运送到所有订阅了该数据的的客户端。

Subscriptions and Minimongo also work together with Meteor methods, which are the last piece of the puzzle to enabling correct optimistic UI rendering.

订阅也可以通过 Meteor 方法与 Minimongo 共同工作，这是解释「乐观 UI 渲染」能够正常工作的最后一部分。

### 4\. To solve client and server disagreements, you need to be able to patch your UI with the real result | 为了解决客户端和服务器端的不一致，需要使用真正的结果来修正 UI

When you are doing optimistic UI updates, the client tries to predict the outcome of some operation. Most of the time, this works great, but sometimes the client just doesn't have enough information to make an accurate prediction. Maybe it's missing some permissions data, maybe it doesn't know about some modification that a different client made, etc. Plus, as any experienced developer will know, you can't ever trust client code to do the right thing since users can modify the code running in their browser.

当你在做「乐观 UI 更新」时，客户端尝试预测某些操作的结果。大部分时间效果很好，但也有时客户端没有足够多的信息确保预测正确无误。也许是无权访问某些数据，也许是不知道不同客户端对数据做了修改等等。此外，因为任何有经验的开发者都知道，任何时候都不能相信客户端代码能够做正确的事情，因为用户可以在自己的浏览器中修改正在运行的代码。

At first, this sounds like an easy problem — of course, the server always wins, so can't you just use the result from the server? The answer is yes, but you need to make sure you have rolled back all of the operations done on the client as part of the optimistic UI update. It turns out it is actually really hard to do this when you have multiple user actions happening in parallel.

首先，这听起来像是个简单的问题 —— 当然，服务器总是会[赢]/[更胜一筹]，所以说，你难道就不可以只使用来自于服务器的结果？答案是肯定的，但你需要确保你已经把客户端的所有操作都做为「乐观 UI 更新」的一部分。事实上的结果是，当你有多个用户同时进行操作的时候，这就会变得非常困难。

To run an optimistic update and then roll back the changes to make room for the server result, you need the last piece of the Meteor data story: Methods.

要运行一个「乐观更新」，然后回滚已做的更改从而为服务器结果腾出空间，你需要了解 Meteor 数据故事的最后一部分：Methods。

Meteor methods are functions that run first on the client against Minimongo, then on the server, on the real MongoDB. Any modifications made during the simulation on the client are tracked, and then rolled back when the real modifications from the server are reported. You don't need to do anything about tracking changes on the client and rolling them back - you get automatic eventual consistency with the server, and it just works.

Meteor 方法是依靠 Minimongo 首先运行在客户端中的函数，然后到服务器真正的 MongoDB 数据库。任何已在客户端模拟的修改都会被追踪，然后当服务器端真正的修改上报的时候进行回滚。你无需在客户端做任何追踪变化的事情并将其回滚 —— 你将自动与服务器保持最终的一致，非常好用。

### Meteor provides these benefits no matter which front-end framework you are using | 不论你使用何种前端框架，都能享受 Meteor 所提供的这些好处。

As you may have noticed throughout this article, none of these features depend on your rendering framework. You can use Meteor's integrated rendering engine Blaze, the Meteor-*Angular* project, or one of several React integrations, and still get all of the benefits of Meteor's data caching and optimistic UI updates. If you are writing a native iOS app, you can also use the excellent [iOS-DDP](https://github.com/martijnwalraven/meteor-ios) project, which implements the same front-end logic but switches out Minimongo for iOS CoreData, letting you write your app in a completely native style.

通过这篇文章，就像可能你已经注意到的，这些特性中无一依赖于你的渲染框架。你可以使用 Meteor 已经集成的渲染引擎 Blaze，也可以是 Meteor-*Angular* 项目，或者是某种 React 的集成方案，依旧能够获得 Meteor 的数据缓存和「乐观 UI 更新」所带来的好处。如果你正在编写原生 iOS 应用，你也可以使用非常棒的 [iOS-DDP](https://github.com/martijnwalraven/meteor-ios) 项目，这个项目实现了同样的前端逻辑，只是为了 iOS 将 Minimongo 换成了 CoreData，从而使你能够使用一种完全原生的方式编写应用。

### Try it out for yourself | 为自己试一试

If you're not convinced yet that Meteor will let you build a first-class user experience without any of the hassle, try this experiment:

如果你还不是很确信 Meteor 可以让你毫无麻烦地构建一流用户体验，可以尝试一下这些试验：

First, [complete the official Meteor tutorial](https://www.meteor.com/try). Then, try building the same app with all of the same features, including optimistic UI updates and data caching, without Meteor. Measure how long it takes and how many lines of code you had to write — I bet you'll find it will take a lot less time and code with Meteor. Let me know how it goes!

首先，完成 Meteor [官方教程](https://www.meteor.com/try)。然后，尝试不使用 Meteor 来构建拥有包含「乐观 UI 更新」和数据缓存在内的所有相同特性的应用。估计一下总共会花多长时间，以及会写多少行不得已的代码 —— 我打赌你会发现远不如使用 Meteor 所花的时间和代码少。请让我拭目以待！
