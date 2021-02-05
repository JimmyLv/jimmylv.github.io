---
layout: session
title: 「技术雷达」之 Micro Frontends：微前端 - 将微服务理念扩展到前端开发
categories: [演讲]
tags: [Microfrontends, FED, Microservices, WebComponents, React]
speaker: Jimmy Lv
transition: move
files: /assets/slide.css,/js/zoom.js
highlightStyle: kimbie.light
theme: colors
published: True
---

[slide]

# ✨ Micro Frontends ✨

微前端 - 将微服务理念扩展到前端开发

---

(<small>via <strong>Jimmy Lv </strong>🐵</small>)

[slide]

# ⏲️ | Agenda

1. 微前端的概念缘由与定义
2. 微前端的实践方案（4+）
3. Demo
4. 优缺点总结与思考

[slide style="background-image:url('https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513920317188.png')"]

# The Majestic Monolith

[note] \* 当今的软件开发环境中，大多数应用程序都是单一的，这种方法的缺点之一是企业所有者一年内需要做的决策数量非常有限（因为依赖关系，响应时间较慢）。

    * 升级产品，在一系列相关服务中增加尺寸较大等新功能，需要所有相关方共同努力，以同步方式进行变更。

[/note]

[slide]

# 💡 | 微服务架构带来了哪些好处？

> 假设服务边界已经被正确地定义为可独立运行的业务领域，并确保在微服务设计中遵循诸多最佳实践。

---

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513908599811.png)

    * 复杂性：服务可以更好地分离。 {:&.moveIn}
    * 可扩展性：服务可以独立伸缩。
    * 灵活性：服务可以独立失败。
    * 敏捷性：服务可以独立开发，测试和部署。

[note]
_ 微服务是孤立的，独立的 “模块”，它们共同为更高的逻辑目的服务。他们通过商定的协议彼此沟通，每个服务都负责特定的功能。这使得每个服务都能够保持简单，简洁和可测试性。
_ 微服务允许您更自发地采取更深远的业务决策，因为每个微服务都是独立运作的，而且一个正在管理的团队可以很好地控制变更。
_ 微服务架构允许每个团队决定最适合他们的技术和基础架构。
_ 引入微服务体系结构的重大好处，它允许团队扩展独立部署和维护服务的交付。
[/note]

[slide]

# 💡 | 那么前端的现状呢？ —— 臃肿的前端

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513877114486.png)

---

- ✨ SPA：一个功能丰富，功能强大的浏览器应用程序。 {:&.moveIn}
- 💔 随着时间的推移，往往由一个独立团队所开发的前端层越来越难以维护。

[note]

- 如果做得对，它提供了优秀的用户体验。主要缺点是它不能很好地扩展。在一个大公司里，有许多开发团队，单前端团队可能成为一个发展瓶颈。
- 大型 SPA 却位于微服务架构之上。
  - one App with one BFF. Why split with Microservices together?
  - 不幸的是，我们也看到许多团队在其后端微服务之上创建了前端庞然大物 - 一个庞大而庞大的浏览器应用程序。
  - 前端变得越来越大，后端变得越来越不重要。
    - 90％的前端代码，具有非常薄的后端。
- 举实例：OSP 项目中 components library 的弊端 (NPM package)
  - What if you want to publish a change to the header, an already have fifty pages using that? You would have to ask every page to upgrade it's version of header, meanwhile, your users would get inconsistent headers across the website
  - You are now compiling another app as part of yours, what if it throws something unexpected, will your app break too?
  - You are forced to have the same technologies on both sides, what if header the header uses clojurescript and your page uses elm? Poor webpack, it now has to understand it all when compiling.

[/note]

[slide]

# 微前端的定义 - 将微服务理念扩展到前端开发

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513877768959.png)

---

微前端（Micro Frontends）这个术语是微服务的衍生物。同时构建多个自包含的和松耦合的 UI 组件（服务），其中每个组件负责特定的 UI 元素和功能。

[note]

ThoughtWorks 的同志们最擅长举一反三，包装概念啦！

- 如果我们看到微服务提供了后端的好处，如果我们能够将这些好处应用到前端，并不是向前迈出的一步，而且设计微服务不仅要完成后端逻辑，而且还要完成视觉部分。
- 使各个前端团队按照自己的步调迭代，然后在准备就绪时释放; 风险隔离; 而且更容易尝试新技术。
- 对于微服务来说，微前端的许多要求是相同的：监控，健康检查，日志记录，仪器仪表，度量标准等等。

[/note]

[slide]

# 更详细的「微前端 Micro Frontends」

- 根据领域特定功能将应用程序分解为更小的单元。每个单元是独立的，可以独立开发部署。
- 将网站或 Web 应用程序视为由独立团队拥有的功能组合。每个团队都有一个独特的业务或任务关注和专业的任务。
- 每一个团队是跨职能的，从数据库到用户界面端到端地开发其功能/特性。
- 所有前端功能（身份验证，库存，购物车等）都是 Web 应用程序的一部分，并与后端（大部分时间通过 HTTP）进行通信，并将其分解为微服务。
- 可以同时拥有后端，前端，数据访问层和数据库，即一个服务中的子域所需的所有内容。每一项服务都应该由一个独立的团队来完成。

[note]

- Web 应用程序被分解成独立的特征，并且每个特征都由不同的团队拥有，前端到后端。这确保了每个功能都是独立于其他功能开发，测试和部署的。
- 找到线上 bug，测试，理解代码，改变框架，甚至语言，隔离，责任和其他事情变得更容易处理。我们不得不付出的代价是部署，但是，容器（Docker 和 Rocket）以及不可变服务器的概念也得到了极大的改善。
- 通过微服务，DevOps 和持续交付是我们工程实践的核心，我们决定 AWS 是支持我们专注于基础架构自动化的正确环境，同时为我们提供冗余和可扩展性。
  - Docker 容器将给我们两个具体的好处：
  - 跨越环境以及跨 JVM 和非 JVM 应用程序统一部署管道：目前，我们正在管理 Symfony / Angular 表示层的部署，与我们的 JVM / Agora 中间层不同，导致不必要的差异，复制工作和浪费。
  - 在单独的主机上部署每个应用程序 / 服务实例的能力：容器调度将使我们能够整合我们的计 ​​ 算资源，同时保持服务实例之间的隔离，同时提高利用率。
- 存在多种技术来重新组合特征 - 有时作为页面，有时作为组件 - 变为有凝聚力的用户体验。
- 前端（不管是不是 SPA）将被缩减为只负责路由选择和决定要导入哪些服务的脚手架。

[/note]

[slide]

# 微前端的核心思想

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513878936981.png)

---

- ✨ Be Technology Agnostic {:&.moveIn}
- ✨ Isolate Team Code
- ✨ Establish Team Prefixes
- ✨ Favor Native Browser Features over Custom APIs
- ✨ Build a Resilient Site

[note]

- 每个团队都应该能够选择和升级他们的技术栈，而不必与其他团队协调。自定义元素是隐藏实现细节的好方法，同时为其他人提供公共接口。
- 即使所有团队使用相同的框架，也不要共享运行时。构建独立的应用程序。不要依赖共享状态或全局变量。
- 相互约定命名隔离。为 CSS、Events、Local Storage 和 Cookies 制定命名空间，以避免冲突和明确所有权。
- 使用浏览器事件进行通信，而不是构建全局的 PubSub 系统。如果您确实需要构建跨团队 API，请尽量保持简单。（与框架无关，CustomEvent）
- 即使 JavaScript 失败或尚未执行，您的功能仍应有用。使用通用渲染和渐进增强来提高感知性能。

[/note]

[slide]

# 微前端的实践方案

🔨 Creating small apps (rather than components) 🔨

```js
# src/App.js
export default () =>
  <header>
    <h1>Logo</h1>
    ......
  </header>;
```

```js
# server.js
const renderedApp = renderToString(React.createElement(App, null));
```

---

- https://microfrontends-header.herokuapp.com/
- https://microfrontends-products-list.herokuapp.com/
- https://microfrontends-cart.herokuapp.com/

[slide]

# 💞 Joining apps together

## Option 1: SSR using template

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

```js
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

---

Problem: Some apps may take longer to load

[note]

There are some cases where things take a while to load on the back-end, maybe your header loads much faster than the other parts, and you want to display that ASAP to your users, while the products list takes more time.

[/note]

[slide]

# 💞 Joining apps together

## Option 1.1: Progressive loading from the back-end

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513879504186.png)

[slide]

# Option 2: iframe

```html
<body>
  <iframe width="100%" height="200" src="https://microfrontends-header.herokuapp.com/"></iframe>
  <iframe width="100%" height="200" src="https://microfrontends-products-list.herokuapp.com/"></iframe>
  <iframe width="100%" height="200" src="https://microfrontends-cart.herokuapp.com/"></iframe>
</body>
```

---

- 优点 {:&.moveIn}
  - 最强大的是隔离了组件和应用程序部分的运行时环境，因此每个部分都可以独立开发，并且可以与其他部分的技术无关
  - 可以在 React 中开发一些部分，在 Angular 中开发一些部分，在 vanilla Js 中开发更多或任何其他技术。
  - 只要 iframes 来自同一个来源，消息传递也就相当直接和强大。[Window.postMessageAPI](https://developer.mozilla.org/en-US/docs/Web/API/Window/postMessage)
- 缺点
  - Bundle 的大小非常明显，因为你最终会多次发送相同的库，并且由于应用程序是分开的，所以在构建时不能提取公共依赖关系。
  - 至于浏览器的支持，你基本上不能嵌套两层以上的 iframes（parent - > iframe - > iframe），或者所有的地狱崩溃。
  - 如果任何嵌套的框架需要能够滚动或具有 Form 表单域，就会很痛苦。

[note]

- 每个应用程序都在自己的小 iframe 中，这使得小组能够使用任何他们需要的框架，而无需与其他小组协调工具和依赖关系。
- 将微服务包装到 IFrames 中，然后使用一些库和 Window.postMessageAPI 来交互。

[/note]

[slide]

# Option 3: Client-Side JavaScript

```js
var script = document.createElement('script')
script.setAttribute('src', nonExecutableScript.src)
script.setAttribute('type', 'text/javascript')
element.appendChild(script)
```

---

- This basically loads the apps through ajax and insert their content inside those `divs`. It also has to clone each script tag manually for them to work.

- Note: to avoid problems with Javascript and CSS loading order, I suggest you to evolve this to a solution similar to facebook's bigpipe, returning a JSON like `{ html: ..., css: [...], js: [...] }` so you can have full control of it.

[slide]

# Option 4: WebComponents

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

[note]

- 每个团队建立他们的组件使用他们所选择的网络技术，并把它包装自定义元素中（如<order-minicart></order-minicart>）。
  - 允许创建可以导入到 Web 应用程序中的可重用组件。它们就像可以导入任何网页的小部件。
- Web 组件 - Web 组件是应用程序中包含的组件的本地实现，如菜单，表单，日期选择器等。每个组件都是独立开发的，主应用程序项目利用它们并组成最终的应用程序。
- 这个特定元素（标签名称，属性和事件）的 DOM 规范充当其他团队的合同或公共 API。

[/note]

[slide]

# Web Components 用于整合所有功能模块

> Web Components 是一个 Web 标准，所以像 Angular，React，Preact，Vue 或 Hyperapp 这样的主流 JavaScript 框架都支持它们。

---

```md
- 自定义元素
- Shadow DOM
- HTML 导入
- HTML 模板元素
```

```html
<link rel="import" href="/components/tc-books/tc-books.html" />
<link rel="import" href="/components/tc-books/tc-book-form.html" />
```

[note]

- 优点 {:&.moveIn}
  - 自定义元素可以创建自己的自定义 HTML 标签和元素。每个元素可以有自己的脚本和 CSS 样式。还包括生命周期回调，它们允许我们定义特定于正在开发的组件的行为。
  - Shadow DOM：允许我们在 Web 组件中封装 JavaScript，CSS 和 HTML。在组件内部时，这些东西与主文档的 DOM 分离。
    HTML 导入
    - 在微服务的上下文中，导入可以是包含我们要使用的组件的服务的远程位置。
    - <link rel="import" href="/components/tc-books/tc-books.html">
      <link rel="import" href="/components/tc-books/tc-book-form.html">
  - HTML 模板元素：可以用来保存客户端内容，当页面加载时不会渲染。
  - 功能团队可以使用组件及其功能，而不必知道实现。他们只需要能够与 HTML DOM 进行交互。
  - 使用 PubSub 机制，组件可以发布消息，其他组件可以订阅特定的主题。幸运的是浏览器内置了这个功能。
    - 购物车现在可以订阅此事件 window 并在应该刷新其数据时得到通知。
    - window.addEventListener('blue:basket:changed', this.refresh);
- 缺点

  - 可悲的是，Web 组件规范根本不谈论服务器渲染。没有 JavaScript，就没有自定义元素。😔
  - 浏览器不全，支持不够，社区不够，框架支持不够。

- WebComponents are still not fully supported in all browsers, with Mozilla holding back HTML imports, so you will need polyfills, more code for the user to load.
- It haven't really gained popularity yet, maybe never will, I see blogposts from 2013 and still few people have tried it!
- JavaScript bundle has to load first and register the components in order for the DOM to load, which means that to gain the advantages of server-side rendering you'll probably need to be more clever.
- For this alternative we had to make changes not only on the homepage, but on the apps too, to convert them to WebComponents.
  [/note]

[slide]

# Communication Between Apps

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

[note]

- because it should work with any other technologies and frameworks, you can send messages from React to Angular for example.
- This is the same reason nowadays everybody uses JSON to communication on the back-end, even if nobody uses NodeJS!
- how do we test this communication? How to write integration or contract tests here? I don't know. Also adding some ideas from Event Driven Architecture here might be good.
  [/note]

[slide]

# More Options...

- 组件库 - 根据主应用程序的技术栈，不同的组件和应用程序部分可以作为库和主应用程序，所以主应用程序是由不同组件组成的。
- 将 “应用程序” 作为黑盒 React 组件分发给消费应用程序 - 应用程序的状态完全包含在组件中，API 只是通过 props 暴露出来。
- Edge Side Includes(ESI)/Server Side Includes(SSI) - 通过特殊的文件后缀 (shtml,inc) 或简单的标记语言来对那些可以加速和不能加速的网页中的内容片断进行描述，将每个网页划分成不同的小部分分别赋予不同的缓存控制策略。

[note]

这种方式增加了应用程序之间的耦合，因为它迫使每个人都使用 React，甚至会使用相同版本的 React，但是对于我们来说，情况已经如此，所以这似乎是一个好的折衷。

### SSI / ESI 方法的缺点是，最慢的片段决定了整个页面的响应时间。所以当一个片段的响应可以被缓存时是很好的。

- Edge Side Includes(ESI) 和 Server Side Includes(SSI) 和功能类似. SSI 需要特殊的文件后缀 (shtml,inc).ESI（Edge Side Include）通过使用简单的标记语言来对那些可以加速和不能加速的网页中的内容片断进行描述,
- 每个网页都被划分成不同的小部分分别赋予不同的缓存控制策略, 使 Cache 服务器可以根据这些策略在将完整的网页发送给用户之前将不同的小部分动态地组合在一起.
- 通过这种控制, 可以有效地减少从服务器抓取整个页面的次数, 而只用从原服务器中提取少量的不能缓存的片断, 因此可以有效降低原服务器的负载, 同时提高用户访问的响应时间.

[/note]

[slide]

# 页面加载的问题与优化建议

## ![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513881261010.png)

- 响应式布局：使用 skeleton screen
- 加快初始渲染：浏览器异步加载
- 视觉体验一致：共享 UI 组件库
- Router：依赖反转（前端 BFF/Gateway）
- 提取共同依赖作为 externals
- ……

[note]

- 推荐区域最初是空白的。团队绿色 JavaScript 被加载和执行。用于获取个性化推荐的 API 调用已经完成。推荐标记被呈现并且请求关联的图像。现在片段需要更多的空间，并推动页面的布局。
- 团队红，控制页面，可以固定建议容器的高度。在响应式网站上，确定高度往往很难，因为不同的屏幕尺寸可能会有所不同。但更重要的问题是，这种队际协议在球队红绿之间产生了紧密的联系。
- 更好的方法是使用称为骨架屏幕的技术。Team red 将 green-recosSSI Include 包含在标记中。此外，团队绿色会更改其片段的服务器端渲染方法，以便生成内容的原理图版本。该骷髅标记可以重用的实际内容的布局样式的部分。这样就保留了所需的空间，实际内容的填充不会导致跳跃。
  - A skeleton screen is essentially a blank version of a page into which information is gradually loaded.

### 优化

- 对于生产成本高且难以缓存的碎片，将其从初始渲染中排除是一个好主意。浏览器异步加载。
  在我们的例子中 green-recos，显示个性化推荐的片段就是这个候选人。
- 在前端设计中，必须向用户呈现外观和感觉一致的用户界面。有很多页面上都出现了 UI 元素。关注的分离并不总是像后端服务一样清晰。
- UI 组件库
  - 我们用微前端解决的下一个挑战是呈现一致的外观和感觉，同时也隔离风险。
  - 我们建立了一个共享组件（CSS，Font 和 JavaScript）的库。我们将这些资源托管在每个微前端可以在其 HTML 输出中引用它们的位置。每个组件库的版本都正确地对资源进行版本控制，每个微前端都指定要使用的组件库的版本。因此，CSS 和 JavaScript 不会意外地改变; 每个微前端的开发者都必须显式更新依赖关系。
    [/note]

[slide]

# Micro Frontends + AEM/jQuery

- AEM (of course), which contains web content only (no structured domain data).
- React.js components that are hosted in AEM. AEM passes through different properties the components need e.g. ids, URLs of services.
- Microservices that contain the structured domain data, and that are queried by the React.js components via Ajax.

[slide]

# Demo: [Single-SPA “meta framework”](https://single-spa.surge.sh/)

可以在一个页面将多个不同的框架整合，甚至在切换的时候都不需要刷新页面 (支持 React, Vue, Angular 1, Angular 2, etc)

---

- Build micro frontends that coexist and can each be written with their own framework.
- Use multiple frameworks on the same page without refreshing the page (React, AngularJS, Angular, Ember, or whatever you're using)
- Write code using a new framework, without rewriting your existing app
- Lazy load code for improved initial load time.
- Hot reload entire chunks of your overall application (instead of individual files).

[slide]

# 🐒 SHOW ME THE CODE!

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

[slide]

# 总结与思考：微前端的优缺点

[slide]

# 优点

- 敏捷性 - 独立开发和更快的部署周期
  - 开发团队可以选择自己的技术并及时更新技术栈。
  - 一旦完成其中一项就可以部署，而不必等待所有事情。
- 降低错误和回归问题的风险，相互之间的依赖性急剧下降。
- 更简单快捷的测试，每一个小的变化不必再触碰整个应用程序。
- 有助于持续集成、持续部署以及持续交付。
- 维护和 bugfix 非常简单，每个团队维护特定的区域。

[slide]

# 缺点

- 开发与部署环境分离
  - 一个复杂的开发环境
  - 有一个孤立的部署周期。
  - 需要在一个孤立的环境中运行。
- 复杂的集成
  - 隔离 js，避免 css 冲突，根据需要加载资源，在团队之间共享公共资源的机制，处理数据获取并考虑用户的良好加载状态。
  - 微前端模块之间的 Contract Testing？
- 第三方模块重叠 / 依赖冗余增加了管理的复杂性
- 影响最终用户的体验
  - 初始 Loading 时间可能会增加
  - HTML 会需要服务器端的渲染

---

```html
<script src="https://cdnjs.cloudflare.com/ajax/libs/react/15.4.2/react.min.js" crossorigin="anonymous"></script>
```

[slide]

# 💡 | 持续思考…

![](https://raw.sevencdn.com/JimmyLv/images/master/2017/12/1513909558428.png)

- （变幻莫测）前端的技术选型？
- 在 Mobile/Mobile Web 上的悖论
- 合理划分的边界：DDD
- Don't use any of this if you don't need it
- 软件架构到底在解决什么问题？

---

> 所谓架构，其实是解决人的问题；所谓敏捷，其实是解决沟通的问题；所谓精益，其实是在讨论如何榨干劳动力；

[note]

### 前端的技术选型？

- 既然 React 经验不错，那为什么不推广到全公司？可能是跨 vendor 合作
- 前端 JavaScript 框架穷出不穷，最后又出来要取代 Webpack 和 Yarn 的工具，过几个月就要重写项目？重构压力、负担大，那不如直接支持多 framework？

### 在 Mobile/Mobile Web 上的悖论

- 已经分出了不同的子页面，那何不如直接 Router 即可？

### 合理划分：DDD

- 最大的挑战是搞清楚如何划分应用程序。糟糕的设计可能成为开发和维护的噩梦。主要原则是将应用程序分为不同的部分，子部分和组件。

### Don't use any of this if you don't need it

- do not use the ideas described here until it is needed, it will make things more complex.
- If you are in a big company, those ideas could help you

### 所谓架构，其实是解决人的问题；所谓敏捷，其实是解决沟通的问题；所谓精益，其实是讨论如何榨干劳动力，美其名曰减少浪费；

### 解决了什么问题？

- 跨团队沟通的问题
  - Spotify 在内部被分成小队（3-12 人）队称为小队。一个特点通常由一个小队拥有，而在正常情况下，小队拥有开发和维持其特征所需的一切。一个小队的 iOS，Android，网络和后端开发人员是很正常的。一般的想法是，每个小队都应该有自己的能力来完成自己的功能，最大限度地减少小组要求其他部门获得许可和 / 或帮助。
  - 提供了大量引进 library 的好处是少数人讨论，而不是涉及约 100 人的决定和他们的各种需求。这样一场大讨论不仅会耗费时间和精力，而且会迫使我们采用最不起眼的方法来选择 library，而不是选择专门针对每个 team 的问题领域的方案。
    [/note]

[slide]

# ❤️ | Thank you!

```md
- https://medium.com/@tomsoderlund/micro-frontends-a-microservice-approach-to-front-end-web-development-f325ebdadc16
- https://medium.com/@_rchaves_/building-microfrontends-part-i-creating-small-apps-710d709b48b7
- http://allegro.tech/2016/03/Managing-Frontend-in-the-microservices-architecture.html
- https://technologyconversations.com/2015/08/09/developing-front-end-microservices-with-polymer-web-components-and-test-driven-development-part-55-using-microservices/
- https://technologyconversations.com/2015/08/09/including-front-end-web-components-into-microservices/
- https://inbox.google.com/u/1/search/microfrontend
- https://inbox.google.com/u/1/search/micro%20frontend
- https://medium.com/@_rchaves_/building-microfrontends-bonus-part-rewriting-an-app-with-elm-97ddce415ff4
- https://m.signalvnoise.com/the-majestic-monolith-29166d022228
- https://medium.com/@_rchaves_/building-microfrontends-part-v-communication-between-apps-34ae3649d610
- https://developer.mozilla.org/en-US/docs/Web/API/CustomEvent
- https://medium.com/@_rchaves_/building-microfrontends-part-iv-using-cdns-tech-radar-for-consensus-7dd658c1edb7
- https://medium.com/@_rchaves_/building-microfrontends-part-iii-public-path-problem-1ce823be24c9
- https://medium.com/@_rchaves_/building-microfrontends-part-ii-joining-apps-together-dfa1b6f17d3e
- https://www.upwork.com/blog/2017/05/modernizing-upwork-micro-frontends/
- https://www.upwork.com/blog/2017/01/upwork-modernization/
- https://engineering.hellofresh.com/front-end-microservices-at-hellofresh-23978a611b87
- https://news.ycombinator.com/item?id=13009285
- https://www.thoughtworks.com/radar/techniques/micro-frontends
- http://www.agilechamps.com/microservices-to-micro-frontends/
- https://www.tikalk.com/js/introduction-to-micro-frontends/
- https://github.com/CanopyTax/single-spa
- http://www.infoq.com/cn/news/2015/08/netflix-falcor
- http://insights.thoughtworks.cn/frontend-future-radar/
- https://blog.prototypr.io/luke-wroblewski-introduced-skeleton-screens-in-2013-through-his-work-on-the-polar-app-later-fd1d32a6a8e7
- https://micro-frontends.org/
- https://blog.fundebug.com/2017/08/02/micro_frontend_development/
- https://www.quora.com/How-is-JavaScript-used-within-the-Spotify-desktop-application-Is-it-packaged-up-and-run-locally-only-retrieving-the-assets-as-and-when-needed-What-JavaScript-VM-is-used/answer/Mattias-Petter-Johansson
```
