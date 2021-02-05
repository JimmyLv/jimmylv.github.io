---
layout: post
title: 技术雷达之「微前端」- 将微服务理念扩展到前端开发（下：实战篇）
categories: [前端]
tags: [Microfrontends, FED, Microservices, WebComponents, React]
published: True
---

## 前言与大纲

> 本文分为[理论](https://blog.jimmylv.info/2017-12-24-tech-radar-microfrontends-extending-microservice-to-fed/)和[实战](https://blog.jimmylv.info/2017-12-24-tech-radar-microfrontends-extending-microservice-to-fed-next/)上下两篇。本篇为微前端的实战篇，共计约 5k 字，预计阅读时间 10 mins。

在[技术雷达之「微前端」- 将微服务理念扩展到前端开发（上：理论篇）](https://blog.jimmylv.info/2017-12-24-tech-radar-microfrontends-extending-microservice-to-fed/)中，我们介绍了微前端在单体应用和微服务的架构演进中所产生的缘由，将微服务理念运用到前端开发就是为了解决臃肿前端的当前现状。与此同时，合理拆分微前端也给我们的应用开发带来显而易见的好处，在本篇当中我们将逐一介绍微前端的实践方案与可能遇到的问题和对应的优化建议。

- [微前端的可选实践方案（4 种 +）](#title7)
  - [创建更小的 Apps（而不是 Components）](#title8)
  - [如何组合微前端的 App 模块？](#title9)
    - [Option 1: 使用后端模板引擎插入 HTML](#title10)
    - [Option 1.1: 渐进式从后端进行加载](#title11)
    - [Option 2: 使用 IFrame 隔离运行时](#title12)
    - [Option 3: 客户端 JavaScript 异步加载](#title13)
    - [Option 4: WebComponents 整合所有功能模块](#title14)
  - [不同 App 模块之间如何交互？](#title15)
  - [More Options…](#title16)
- [微前端的页面优化与实例](#title17)
  - [多模块页面加载问题与优化建议](#title18)
  - [微前端在 AEM（CMS）项目的应用](#title19)
  - [现成解决方案：Single-SPA “meta framework”](#title20)
- [总结与思考：微前端的优缺点](#title21)
  - [微前端的优点](#title22)
  - [微前端的缺点](#title23)
  - [持续思考…](#title24)
- [附：参考资料](#title25)

## 微前端的可选实践方案（4 种+）

### 创建更小的 Apps（而不是 Components）

首先让我们来创建一个典型 Web 应用程序的基本组件（Header、ProductList、ShoppingCart），以 Header 组件为例：

```jsx
# src/App.js
export default () =>
  <header>
    <h1>Logo</h1>
    <nav>
      <ul>
        <li>About</li>
        <li>Contact</li>
      </ul>
    </nav>
  </header>;
```

然后需要注意的是我们会用到 Express 对刚刚创建的 React 组件进行服务器端渲染，使之成为一个 App 模块:

```js
# server.js
fs.readFile(htmlPath, 'utf8', (err, html) => {
  const rootElem = '<div id="root">';
  const renderedApp = renderToString(React.createElement(App, null));

  res.send(html.replace(rootElem, rootElem + renderedApp));
});
```

再依次创建其他 Apps 并独立部署：

- <https://microfrontends-header.herokuapp.com/>
- <https://microfrontends-products-list.herokuapp.com/>
- <https://microfrontends-cart.herokuapp.com/>

### 如何组合微前端的 App 模块？

在每个独立团队创建好各自的 App 模块后，我们就可以将网站或 Web 应用程序视为由各种模块的功能组合。下文将介绍多种技术实践方案来重新组合这些模块（有时作为页面，有时作为组件），而前端（不管是不是 SPA）将只需要负责路由器（Router）如何选择和决定要导入哪些模块，从而为最终用户提供一致性的用户体验。

#### Option 1: 使用后端模板引擎插入 HTML

```js
# server.js
Promise.all([
    getContents('https://microfrontends-header.herokuapp.com/'),
    getContents('https://microfrontends-products-list.herokuapp.com/'),
    getContents('https://microfrontends-cart.herokuapp.com/')
  ]).then(responses =>
    res.render('index', { header: responses[0], productsList: responses[1], cart: responses[2] })
  ).catch(error =>
    res.send(error.message)
  )
);
```

```ejs
# views/index.ejs
  <head>
    <meta charset="utf-8">
    <title>Microfrontends Homepage</title>
  </head>
  <body>
    <%- header %>
    <%- productsList %>
    <%- cart %>
  </body>
```

但是，这种方案也存在弊端，即某些 App 模块可能会需要相对较长的加载时间，而在前端整个页面的渲染却要取决于最慢的那个模块。

比如说，可能 Header 模块的加载速度要比其他部分快得多，而 ProductList 则因为需要获取更多 API 数据而需要更多时间。通常情况下我们希望尽快将网页显示给用户，而在这种情况下后台加载时间就会变得更长。

#### Option 1.1: 渐进式从后端进行加载

当然，我们也可以通过修改一些后端代码来渐进式地（Progressive）往前端发送 HTML，但与此同时却徒增了后端复杂度，并且又将前端的渲染控制权交回了后端服务器。而且我们的优化也取决于每个模块加载的速度，若是进行优化就必须按一定顺序进行加载。

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513879504186.png)

#### Option 2: 使用 IFrame 隔离运行时

```html
<body>
  <iframe width="100%" height="200" src="https://microfrontends-header.herokuapp.com/"></iframe>
  <iframe width="100%" height="200" src="https://microfrontends-products-list.herokuapp.com/"></iframe>
  <iframe width="100%" height="200" src="https://microfrontends-cart.herokuapp.com/"></iframe>
</body>
```

我们也可以将每个子应用程序嵌入到各自的 `<iframe>` 中，这使得每个模块能够使用任何他们需要的框架，而无需与其他团队协调工具和依赖关系，依然可以借助于一些库或者 `Window.postMessageAPI` 来进行交互。

- **优点**：
  - 最强大的是隔离了组件和应用程序部分的运行时环境，因此每个模块都可以独立开发，并且可以与其他部分的技术无关
  - 可以各自使用完全不同的前端框架，可以在 React 中开发一部分，在 Angular 中开发一部分，然后使用原生 JavaScript 开发其他部分或任何其他技术。
  - 只要每个 iframe 来自同一个来源，消息传递也就相当直接和强大。参考文档 [`Window.postMessageAPI`](https://developer.mozilla.org/en-US/docs/Web/API/Window/postMessage)
- **缺点**：
  - Bundle 的大小非常明显，因为可能最终会多次发送相同的库，并且由于应用程序是分开的，所以在构建时也不能提取公共依赖关系。
  - 至于浏览器的支持，基本上不可能嵌套两层以上的 iframe（`parent - > iframe - > iframe`）。
  - 如果任何嵌套的框架需要能够滚动或具有 Form 表单域，那样的情况处理起来就会变得特别痛苦。

#### Option 3: 客户端 JavaScript 异步加载

```js
function loadPage(element) {
  ;[].forEach.call(element.querySelectorAll('script'), function (nonExecutableScript) {
    var script = document.createElement('script')
    script.setAttribute('src', nonExecutableScript.src)
    script.setAttribute('type', 'text/javascript')
    element.appendChild(script)
  })
}

document.querySelectorAll('.load-app').forEach(loadPage)
```

```html
<div class="load-app" data-url="header"></div>
<div class="load-app" data-url="products-list"></div>
<div class="load-app" data-url="cart"></div>
```

简单来说，这种方式就是在客户端浏览器通过 Ajax 加载应用程序，然后将不同模块的内容插入到对应的 `div` 中，而且还必须手动克隆每个 script 的标记才能使其工作。

需要注意的是，为了避免 Javascript 和 CSS 加载顺序的问题，建议将其修改成类似于 [Facebook `bigpipe`](https://www.facebook.com/notes/facebook-engineering/bigpipe-pipelining-web-pages-for-high-performance/389414033919/) 的解决方案，返回一个 JSON 对象 `{ html: ..., css: [...], js: [...] }` 再进行加载顺序的控制。

#### Option 4: WebComponents 整合所有功能模块

Web Components 是一个 Web 标准，所以像 Angular、React/Preact、Vue 或 Hyperapp 这样的主流 JavaScript 框架都支持它们。你可以将 Web Components 视为使用开放 Web 技术创建的可重用的用户界面小部件，也许会是 Web 组件化的未来。

Web Components 由以下四种技术组成（尽管每种技术都可以独立使用）：

- [自定义元素（Custom Elements）](https://developer.mozilla.org/zh-CN/docs/Web/Web_Components/Custom_Elements)对外提供组件的标签，实现自定义标签：可以创建自己的自定义 HTML 标签和元素。每个元素可以有自己的脚本和 CSS 样式。还包括生命周期回调，它们允许我们定义正在加载的组件特定行为。
- [HTML 模板（HTML `<template>`）](https://developer.mozilla.org/zh-CN/docs/Web/HTML/Element/template)定义组件的 HTML 模板能力：一种用于保存客户端内容的机制，该内容在页面加载时不被渲染，但可以在运行时使用 JavaScript 进行实例化。可以将一个模板视为正在被存储以供随后在文档中使用的一个内容片段。
- [影子 DOM（Shadow DOM）](https://developer.mozilla.org/zh-CN/docs/Web/Web_Components/Shadow_DOM)封装组件的内部结构，并且保持其独立性：允许我们在 Web 组件中封装 JavaScript，CSS 和 HTML。在组件内部时，这些东西与主文档的 DOM 分离。
- [HTML 导入（HTML Imports）](https://developer.mozilla.org/zh-CN/docs/Web/Web_Components/HTML_Imports)解决组件组合和依赖加载：在微前端的上下文中，可以是包含我们要使用的组件在服务器上的远程位置。

```js
# src/index.js
class Header extends HTMLElement {
  attachedCallback() {
    ReactDOM.render(<App />, this.createShadowRoot());
  }
}
document.registerElement('microfrontends-header', Header);
```

```html
<body>
  <microfrontends-header></microfrontends-header>
  <microfrontends-products-list></microfrontends-products-list>
  <microfrontends-cart></microfrontends-cart>
</body>
```

在微前端的实践当中：

- 每个团队使用各自的技术栈创建他们的组件，并把它包装到自定义元素（[Custom Element](https://developer.mozilla.org/en-US/docs/Web/Web_Components/Custom_Elements)）中（如 `<microfrontends-header></microfrontends-header>`）。
- Web 组件就是应用程序中包含的组件的本地实现，如菜单，表单，日期选择器等。每个组件都是独立开发的，主应用程序项目利用它们组装成最终的应用程序。
- 特定元素（标签名称，属性和事件）的 DOM 规范还可以充当跨团队之间的契约或公共 API。
- 创建可被导入到 Web 应用程序中的可重用组件，它们就像可以导入任何网页的用户界面小部件。

```html
<link rel="import" href="/components/microfrontends/header.html" />
<link rel="import" href="/components/microfrontends/products-list.html" />
<link rel="import" href="/components/microfrontends/cart.html" />
```

- 优点
  - 代码的可读性变得非常清晰，组件资源内部高内聚，组件资源由自身加载控制，作用域独立。
  - 功能团队可以使用组件及其功能，而不必知道实现，他们只需要能够与 HTML DOM 进行交互。
  - 使用 PubSub 机制，组件可以发布消息，其他组件可以订阅特定的主题。幸运的是浏览器内置了这个功能。比如购物车可以在 `window` 订阅此事件并在应该刷新其数据时得到通知。
- 缺点
  - 可惜的是，Web 组件规范跟服务器渲染无关。没有 JavaScript，就没有所谓的自定义元素。
  - 浏览器和框架的支持不够，需要更多的 polyfills 从而影响到用户页面的加载体验。
  - 我们需要在整个 Web 应用程序上做出改变，把它们全部转换成 Web Components。
  - 社区不够活跃，Web Components 还没有真正流行起来，也许永远也不会。

### 不同 App 模块之间如何交互？

```js
# angularComponent.ts
const event = new CustomEvent('addToCart', { detail: item });
window.dispatchEvent(event);
```

```js
# reactComponent.js
componentDidMount() {
  window.addEventListener('addToCart', (event) => {
    this.setState({ products: [...this.state.products, event.detail] });
  }, false);
}
```

- 得益于浏览器的原生 API，Custom Event 可以与其他任何技术和框架一起工作。比如，我们可以将消息从 Angular 组件发送到 React 组件。其实这也是现在 API 之间普遍使用 JSON 进行通信的原因，即使没有人使用 NodeJS 作为服务器端。
- 但是，新的问题又出现了。我们该如何测试这种跨模块之间的交互？需要编写类似于后端微服务之间的 Contract Testing 或 Integration Testing 吗？并没有答案。

### More Options...

- 组件库 - 根据主 App 的技术栈，不同的组件和 App 模块拆分作为库的形式提供给主 App，所以主 App 是由不同组件组成的。但是组件库的升级将成为一个大麻烦，比如对 Header 组件进行了更改，那么如果已经有 50 个页面使用了 Header 组件该怎么办？必须要求每一页都升级它的 Header，而且升级过程中用户还会在整个网站不同页面上看到不一致的标题。并且，在两边还必须都使用相同的技术，比如 Header 组件中使用了 ClojureScript，而 Content 组件中又用了 Elm，那么该怎么办？构建工具就必须在编译时处理不同的语言。
- 将 App 模块作为 React 黑盒组件分发给消费者模块 - 应用程序的状态完全包含在组件中，API 只是通过 props 暴露出来。这种方式其实增加了应用程序之间的耦合，因为它迫使每个人都使用 React，甚至会使用相同版本的 React，但是这似乎也是一个比较好的折衷。
- Edge Side Includes(ESI)/Server Side Includes(SSI) - 通过特殊的文件后缀 (shtml,inc) 或简单的标记语言来对那些可以加速和不能加速的网页中的内容片断进行描述，将每个网页划分成不同的小部分分别赋予不同的缓存控制策略。SSI / ESI 方法的缺点是，最慢的片段决定了整个页面的响应时间。

## 微前端的页面优化与实例

### 多模块页面加载问题与优化建议

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513881261010.png)

- **使用 skeleton screen 响应式布局**：如上图 LinkedIn 所做的那样，首先展现给用户一个页面的空白版本，然后在这个页面中逐渐加载和填充相应的信息。否则中间的信息流部分的内容最初是空白的，然后在 JavaScript 被加载和执行过后，信息流就会因为需要占用更多的空间而推动整个页面的布局。虽然我们可以控制页面来固定中间部分的高度，但在响应式网站上，确定一个确切的高度往往很难，而且不同的屏幕尺寸可能会有所不同。但更重要的问题是，这种高度尺寸的约定会让不同团队之间产生紧密的联系，从而违背了微前端的初衷。
- **使用浏览器异步加载加快初始渲染**：对于加载成本高且难以缓存的碎片，将其从初始渲染中排除是一个好主意。比如说 LinkedIn 首页的信息流就是一个很好的例子。
- **共享 UI 组件库保证视觉体验一致**：在前端设计中，必须向用户呈现外观和感觉一致的用户界面。建议可以建立一个共享组件库（包含 CSS、字体和 JavaScript）。将这些资源托管在 CDN，每个微前端就可以在其 HTML 输出中引用它们的位置。每个组件库的版本都正确地对资源进行版本控制，而每个微前端都指定要使用的组件库的版本和显式更新依赖关系。
- **使用集中式服务（Router）来管理 URL**：可以理解为前端的 Gateway，不同的 URL 对应不同应用程序所包含的内容。建议通过一个集中式的 URLs Router 来为应用程序提供一个 API 来注册他们自己的 URL，Router 将会位于 Web 应用程序的前面，根据不同的用户请求指向不同的 App 模块组合。

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1514122411683.png)

- **提取共同依赖作为 externals 加载**：虽然说不同 App 模块之间不能直接共享相同的第三方模块，当我们依然可以将常用的依赖比如 `lodash`、`moment.js`等公共库，或者跨多个团队共同使用的 `react` 和 `react-dom`。通过 Webpack 等构建工具就可以把打包的时候将这些共同模块排除掉，而只需要在 HTML `<header>` 中的 `<script>`中直接通过 CDN 加载 externals 依赖。

```html
<script src="https://cdnjs.cloudflare.com/ajax/libs/react/16.2.0/react.min.js" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/react/16.2.0/react-dom.min.js" crossorigin="anonymous"></script>
```

### 微前端在 AEM（CMS）项目的应用

我们在「三靠谱」（~~已和谐客户名称~~）的 Marketplace 项目当中也曾经探索过 AEM + React 混合开发的解决方案，其中就涉及到如何在 AEM 当中嵌入 React 组件，甚至将 AEM 组件又强行转化为 React 组件进行嵌套。现在回过头来其实也算是微前端的一种实践：

- AEM 仅仅包含网页内容，不包含 domain 相关的结构化数据。
- React 组件被托管在 AEM 组件当中，再经由 AEM 传递给组件所需要的属性，比如 IDs 或 APIs 的 URL 等等
- 后端微服务则包含 domain 结构化数据，由对应的 React 组件通过 Ajax 进行数据查询。

```html
<div id="cms-container-1">
  <div id="react-input-container"></div>
  <script>
    ReactDOM.render(React.createElement(Input, { ...injectProps }), document.getElementById('react-input-container'))
  </script>
</div>
<div id="cms-container-2">
  <div id="react-button-container"></div>
  <script>
    ReactDOM.render(React.createElement(Button, {}), document.getElementById('react-button-container'))
  </script>
</div>
```

### 现成解决方案：[Single-SPA “meta framework”](https://single-spa.surge.sh/)

[![点击图片可查看实例](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1514123775500.png)](https://single-spa.surge.sh/)

开源的 [`single-spa`](https://github.com/CanopyTax/single-spa) 自称为「元框架」，可以实现在一个页面将多个不同的框架整合，甚至在切换的时候都不需要刷新页面（支持 React、Vue、Angular 1、Angular 2、Ember 等等）：

- Build micro frontends that coexist and can each be written with their own framework.
- Use multiple frameworks on the same page without refreshing the page (React, AngularJS, Angular, Ember, or whatever you're using)
- Write code using a new framework, without rewriting your existing app
- Lazy load code for improved initial load time.
- Hot reload entire chunks of your overall application (instead of individual files).

**请看示例代码，所提供的 API 非常简单：**

```js
import * as singleSpa from 'single-spa'

const appName = 'app1'

const loadingFunction = () => import('./app1/app1.js')
const activityFunction = (location) => location.hash.startsWith('#/app1')

singleSpa.declareChildApplication(appName, loadingFunction, activityFunction)
singleSpa.start()
```

```js
# single-spa-examples.js

declareChildApplication('navbar', () => import('./navbar/navbar.app.js'), () => true);
declareChildApplication('home', () => import('./home/home.app.js'), () => location.hash === "" || location.hash === "#");
declareChildApplication('angular1', () => import('./angular1/angular1.app.js'), hashPrefix('/angular1'));
declareChildApplication('react', () => import('./react/react.app.js'), hashPrefix('/react'));
declareChildApplication('angular2', () => import('./angular2/angular2.app.js'), hashPrefix('/angular2'));
declareChildApplication('vue', () => import('src/vue/vue.app.js'), hashPrefix('/vue'));
declareChildApplication('svelte', () => import('src/svelte/svelte.app.js'), hashPrefix('/svelte'));
declareChildApplication('preact', () => import('src/preact/preact.app.js'), hashPrefix('/preact'));
declareChildApplication('iframe-vanilla-js', () => import('src/vanillajs/vanilla.app.js'), hashPrefix('/vanilla'));
declareChildApplication('inferno', () => import('src/inferno/inferno.app.js'), hashPrefix('/inferno'));
declareChildApplication('ember', () => loadEmberApp("ember-app", '/build/ember-app/assets/ember-app.js', '/build/ember-app/assets/vendor.js'), hashPrefix('/ember'));

start();
```

值得一提的是，[single-spa](https://github.com/CanopyTax/single-spa) 已经进入到最新一期技术雷达的**评估**阶段。这意味着 single-spa 会是值得研究一番的技术，以确认它将对你产生何种影响，你应该投入一些精力来确定它是否会对你所在的组织产生影响。

![](https://raw.sevencdn.com/JimmyLv/images/master/2016/1515998280875.png)

> 摘自技术雷达：SINGLE-SPA 是一个 JavaScript 元框架，它允许我们使用不同的框架构建微前端，而这些框架可以共存于单个应用中。一般来说，我们不建议在单个应用中使用多个框架，但有时却不得不这么做。例如当你在开发遗留系统时，你希望使用现有框架的新版本或完全不同的框架来开发新功能，single-spa 就能派上用场了。鉴于很多 JavaScript 框架 都昙花一现，我们需要一个解决方案来应对未来框架的变化，以及在不影响整个应用的前提下进行局部尝试。在这个方向上，single-spa 是一个不错的开始。

## 总结与思考：微前端的优缺点

### 微前端的优点

- 敏捷性 - 独立开发和更快的部署周期：
  - 开发团队可以选择自己的技术并及时更新技术栈。
  - 一旦完成其中一项就可以部署，而不必等待所有事情完毕。
- 降低错误和回归问题的风险，相互之间的依赖性急剧下降。
- 更简单快捷的测试，每一个小的变化不必再触碰整个应用程序。
- 更快交付客户价值，有助于持续集成、持续部署以及持续交付。
- 维护和 bugfix 非常简单，每个团队都熟悉所维护特定的区域。

### 微前端的缺点

- 开发与部署环境分离
  - 本地需要一个更为复杂的开发环境。
  - 每个 App 模块有一个孤立的部署周期。
  - 最终应用程序需要在**同一个**孤立的环境中运行。
- 复杂的集成
  - 需要考虑隔离 JS，避免 CSS 冲突，并考虑按需加载资源
  - 处理数据获取并考虑用户的初始化加载状态
  - 如何有效测试，微前端模块之间的 Contract Testing？
- 第三方模块重叠
  - 依赖冗余增加了管理的复杂性
  - 在团队之间共享公共资源的机制
- 影响最终用户的体验
  - 初始 Loading 时间可能会增加
  - HTML 会需要服务器端的渲染

### 持续思考…

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513909558428.png)

- （变幻莫测）前端的技术选型？
  - 前端 JavaScript 框架工具穷出不穷，过几个月就要重写前端项目？比如最近又出来了声称要取代 Webpack（[Parcel](https://github.com/parcel-bundler/parcel)）和 Yarn（[Turbo](https://medium.com/@ericsimons/introducing-turbo-5x-faster-than-yarn-npm-and-runs-natively-in-browser-cc2c39715403)）的工具。伴随着前端框架的更新换代，如果整个项目一起升级/重构的话压力大、风险高，那不如拆分微前端直接支持多 framework，或者同一 framework 的不同版本？
- 在 Mobile/Mobile Web 上的悖论
  - 受限于 Mobile 尺寸大小，单一页面所能展现的内容本就有限。
  - 既然已经分出了不同的子页面，那何不如直接 Route 即可？
- 合理划分的边界：DDD（领域驱动开发）
  - 最大的挑战是搞清楚如何合理拆分应用程序。
  - 糟糕的设计可能成为开发和维护的噩梦。
- Don't use any of this if you don't need it
  - Do not use the ideas described here until it is needed, it will make things more complex.
  - If you are in a big company, those ideas could help you.
- 软件架构到底在解决什么问题？—— 跨团队沟通的问题
  - 在正常情况下，每个团队拥有开发和维护其特性所需的一切，都应该有自己的能力来完成自己的特性，并最大限度地减少团队要求其他部门获得许可和/或帮助。
  - 当引入 library 或 framework 时的好处是只需要少数人讨论，而不用涉及超过 100 人的决策和他们的各种需求。这样一场大讨论不仅会耗费时间和精力，而且会迫使我们采用最不起眼的方法来选择 library，而不是选择专门针对每个 team 的问题领域的方案。
    > 所谓架构，其实是解决人的问题；所谓敏捷，其实是解决沟通的问题；

## 附：参考资料

> 本次技术雷达「微前端」主题的宣讲 Slides 可以在我的博客找到：[「技术雷达」之 Micro Frontends：微前端 - 将微服务理念扩展到前端开发 - 吕立青的博客](https://blog.jimmylv.info/2017-12-22-tech-radar-microfrontends-extending-microservice-to-fed/)

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1514125808768.png)

- 在做 Slides 之前所整理的 XMind 思维导图：<https://www.xmind.net/m/e3dv>
- 本人所整理的所有关于「微前端」的资料：<https://www.diigo.com/user/jimmylv?query=%23microfrontends>
- 日常挖宝：ThoughtWorks 邮件组搜索「microfrontend」关键字：<https://inbox.google.com/u/1/search/microfrontend>
- <https://micro-frontends.org/>
- <https://medium.com/@tomsoderlund/micro-frontends-a-microservice-approach-to-front-end-web-development-f325ebdadc16>
- <https://medium.com/@_rchaves_/building-microfrontends-part-i-creating-small-apps-710d709b48b7>
- <http://www.agilechamps.com/microservices-to-micro-frontends/>
- <http://allegro.tech/2016/03/Managing-Frontend-in-the-microservices-architecture.html>
- <https://technologyconversations.com/2015/08/09/developing-front-end-microservices-with-polymer-web-components-and-test-driven-development-part-55-using-microservices/>
- <https://technologyconversations.com/2015/08/09/including-front-end-web-components-into-microservices/>
