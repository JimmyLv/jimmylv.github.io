---
layout: post
title: 【译】唯快不破：Web 应用的 13 个优化步骤
categories: [翻译]
tags: [Web, FED, Optimization, JavaScript]
published: True

---

原文地址: [12 Steps to a Faster Web App -- Auth0](https://auth0.com/blog/2016/02/22/12-steps-to-a-faster-web-app/)

> Web apps are now more interactive than ever. Getting that last drop of performance can do a great deal to improve your end-users' experience. Read the following tips and learn if there is anything more you can do to improve latency, render times and general performance!

时过境迁，Web 应用比以往任何时候都更具交互性。搞定性能可以帮助你极大地改善终端用户的体验。阅读以下的技巧并学以致用，看看哪些可以用来改善延迟，渲染时间以及整体性能吧！

- - - - - - - - - - -
 
## A Faster Web App | 更快的 Web 应用

> Optimizing web apps can be an arduous job. Not only are web apps split in client-side and server-side components, but they are also usually built using diverse technology stacks: there's the database, the backend components (which are usually built on a stack of different technologies as well), the frontend (HTML + JavaScript + CSS + transpilers). Runtimes are diverse too: iOS, Android, Chrome, Firefox, Edge. If you come from a different, monolithic platform, where optimization is usually done against a single target (and even a single version of that target), you will probably reason this is a much more complex task. This can be correct. There are, however, common optimization guidelines that go a long way into improving an app. We will explore these guidelines in the following sections.

优化 Web 应用是一项费劲的工作。Web 应用不仅处于客户端和服务器端的两部分组件当中，通常来说也是由多种多样的技术栈构建而成：数据库，后端组件（一般也是搭建在不同技术架构之上的），以及前端（HTML + JavaScript + CSS + 转化器）。运行时也是变化多端的：iOS，Android，Chrome，Firefox，Edge。如果你曾经工作在一个不同的单一庞大的平台之上，通过来说优化就只是针对于单一的目标（甚至只是目标的单一版本而已），你可能会意识到现在的任务复杂度要远超于此。这就对了。但是这儿也有一些通用的优化指南可以大大改进一个应用。我们将会在接下来的章节中探讨这些指南的内容。

> > A Bing study found that a 10ms increase in page load time costs the site $250K in revenue annually. - **Rob Trace and David Walp, Senior Program Managers at Microsoft**

> 一份 Bing 的研究表明，页面加载时间每增加 10ms，网站的年收入就会减少 25 万美元。 —— **Rob Trace 和 David Walp，微软高级程序经理**
 
### Premature Optimization? | 过早优化？

> The hard thing about optimization is finding the right point in the development life-cycle to do it. Donald Knuth famously said *"premature optimization is the root of all evil"*. The reasoning behind these words is quite simple: it is quite easy to lose time gaining that last 1% of performance in places where it won't make a significant impact. At the same time, some optimizations hinder readability or maintainability, or even introduce newer bugs. In other words, optimization should not be considered a "means to get the best performance out of an application", but "the search for the *right way* to optimize an app and get the *biggest benefits*". In other words, blind optimization can result in lost productivity and small gains. Keep this in mind when applying the following tips. Your biggest friend is the profiler: find the performance hotspots you can optimize to get the biggest improvements without impairing the development or maintainability of your app.

优化最难的地方就是如何在开发生命周期中最适当的时候去做优化。Donald Knuth 有一句名言：*「过早优化乃万恶之源」*。这句话背后的原因非常简单：因为一不小心就会浪费时间去优化某个 1% 的地方，但是结果却并不会对性能造成什么重大影响。与此同时，一些优化还妨碍了可读性或者是可维护性，甚至还会引入新的 Bug。换句话说，优化不应当被认为是「意味着得到应用程序的最佳性能」，而是「探索优化应用的*正确的方式*，并得到*最大的效益*」。再换句话说，盲目的优化可能会导致效率的丢失，而收益却很小。在你应用以下技巧的时候请将此铭记在心。你最好的朋友就是分析工具：找到你可以进行通过优化获得最大程度改善的性能点，而不用损害应用开发的进程或者可维护性。

> > Programmers waste enormous amounts of time thinking about, or worrying about, the speed of noncritical parts of their programs, and these attempts at efficiency actually have a strong negative impact when debugging and maintenance are considered. We should forget about small efficiencies, say about 97% of the time: premature optimization is the root of all evil. Yet we should not pass up our opportunities in that critical 3%. - **Donald Knuth**
 
> 程序员们浪费了大量时间来思考，或者说是担忧，他们的程序中非关键部分的运行速度。并且他们对于性能的这些尝试，实际上却对代码的调试和维护有着非常消极的影响。我们应当忘记那些不重要的性能影响，在 97% 的时间里都可以这么说：过早优化乃万恶之源。当然我们也不应当在那关键的 3% 上放弃我们的机会。—— **Donald Knuth**

## 1. JavaScript minification and module bundling | 1. JavaScript 压缩和模块打包

> parsing JavaScript apps are distributed in source-code form. Source-code parsing is less efficient than bytecode . For short scripts, the difference is negligible. For bigger apps, however, script size can have a negative impact in application startup time. In fact, one of the biggest improvements expected from the use of [WebAssembly](https://auth0.com/blog/2015/10/14/7-things-you-should-know-about-web-assembly/) are better startup times. Minification is the process of processing source-code to remove all unnecessary characters without changing functionality. This results in (unreadable) shorter code that can be parsed faster.

JavaScript 应用是以源码形式进行分发的，而源码解析的效率是要比字节码低的。对于一小段脚本来说，区别可以忽略不计。但是对于更大型的应用，脚本的大小会对应用启动时间有着负面的影响。事实上，寄期望于使用 [WebAssembly](https://auth0.com/blog/2015/10/14/7-things-you-should-know-about-web-assembly/)  而获得最大程度的改善，其中之一就是可以得到更快的启动时间。

> On the other hand, module bundling deals with taking different scripts and bundling them together in a single file. Fewer HTTP requests and a single file to parse reduces load times. Usually, a single tool can handle bundling and minification. [Webpack](https://webpack.github.io/) is one of those tools.

另一方面，模块打包则用于将不同脚本打包在一起并放进同一文件。更少的 HTTP 请求和单个文件解析都可以减少加载时间。通常情况下，单独一种工具就可以处理打包和压缩。[Webpack](https://webpack.github.io/) 就是其中之一。

> For example this code:

示例代码：

```js
function insert(i) {
    document.write("Sample " + i);
}

for(var i = 0; i < 30; ++i) {
    insert(i);
}
```

> Results in:

结果如下：

```js
!function(r){function t(o){if(e[o])return e[o].exports;var n=e[o]={exports:{},id:o,loaded:!1};return r[o].call(n.exports,n,n.exports,t),n.loaded=!0,n.exports}var e={};return t.m=r,t.c=e,t.p="",t(0)}([function(r,t){function e(r){document.write("Sample "+r)}for(var o=0;30>o;++o)e(o)}]);
//# sourceMappingURL=bundle.min.js.map
```
 
### Further bundling | 进一步打包

> You can also bundle CSS files and combine images with Webpack. These features can also help improve startup times. Explore the [docs](http://webpack.github.io/docs/) and run some tests!

你也可以使用 Webpack 打包 CSS 文件以及合并图片。这些特性都可以有助于改善启动时间。研究一下 [Webpack  文档](http://webpack.github.io/docs/)来做些测试吧！
 
## 2. On-demand loading of assets | 2. 按需加载资源

> On-demand or *lazy loading* of assets (images in particular) can help greatly in achieving better general performance of your web app. There are three benefits to lazy loading for image-heavy pages:

资源（特别是图片）的按需加载或者说*惰性加载*，可以有助于你的 Web 应用在整体上获得更好的性能。对于使用大量图片的页面来说惰性加载有着显著的三个好处：

> - Reduced number of concurrent requests to the server (which results in faster loading times for the rest of your page).
> - Reduced memory usage in the browser (fewer images, less memory).
> - Reduced load on the server.

- 减少向服务器发出的并发请求数量（这就使得页面的其他部分获得更快的加载时间）
- 减少浏览器的内存使用率（更少的图片，更少的内存）
- 减少服务器端的负载
 
> The general idea is to load images or assets (such as videos) at the moment they are being displayed for the first or the moment they are about to get displayed. Since this is deeply connected to how you build your site, lazy loading solutions usually come in the form of plugins or extensions to other libraries. For instance, [react-lazy-load](https://github.com/loktar00/react-lazy-load) is a plugin to handle lazy loading of images for React:

大体上的理念就是只在必要的时候才去加载图片或资源（如视频），比如在第一次被显示的时候，或者是在将要显示的时候对其进行加载。由于这种方式跟你建站的方式密切相关，惰性加载的解决方案通常需要借助其他库的插件或者扩展来实现。举个例子，[react-lazy-load](https://github.com/loktar00/react-lazy-load) 就是一个用于处理 React 惰性加载图片的插件：
 
```js
const MyComponent = () => (
  <div>
    Scroll to load images.
    <div className="filler" />
    <LazyLoad height={762} offsetVertical={300}>
      <img src='http://apod.nasa.gov/apod/image/1502/HDR_MVMQ20Feb2015ouellet1024.jpg' />
    </LazyLoad>
    (...)
```

> A great sample of how this looks in practice is the Google Images [search tool](https://www.google.com/search?site=&tbm=isch&source=hp&biw=1366&bih=707&q=parrots&oq=parrots&gs_l=img.12...0.0.0.4086.0.0.0.0.0.0.0.0..0.0....0...1ac..64.img..0.0.0.UJrFBFKkWMA). Click on the previous link and scroll the page to see the effect.

一个非常好的实践范例就像 Goggle Images 的[搜索工具](https://www.google.com/search?site=&tbm=isch&source=hp&biw=1366&bih=707&q=parrots&oq=parrots&gs_l=img.12...0.0.0.4086.0.0.0.0.0.0.0.0..0.0....0...1ac..64.img..0.0.0.UJrFBFKkWMA)一样。点击前面的链接并且滑动页面滚动条就可以看到效果了。
 
## 3. Use array-ids when using DOM manipulation libraries | 3. 在使用 DOM 操作库时使用 array-ids

> If you are using [React](https://facebook.github.io/react/), [Ember](http://emberjs.com/), [Angular](https://angularjs.org/) or other DOM manipulation libraries, using array-ids (or the track-by feature in Angular 1.x) can help a great deal in achieving good performance, in particular for dynamic sites. We saw the effects of this feature in our latest benchmarks article: [More Benchmarks: Virtual DOM vs Angular 1 & 2 vs Mithril.js vs cito.js vs The Rest (Updated and Improved!)](https://auth0.com/blog/2016/01/11/updated-and-improved-more-benchmarks-virtual-dom-vs-angular-12-vs-mithril-js-vs-the-rest/).

如果你正在使用 [React](https://facebook.github.io/react/)，[Ember](http://emberjs.com/)，[Angular](https://angularjs.org/) 或者其他 DOM 操作库，使用 array-ids（或者 Angular 1.x 中的 track-by 特性）非常有助于实现高性能，对于动态网页尤其如此。我们已经在上一篇程序衡量标准的文章中看到这个特性的效果了： [More Benchmarks: Virtual DOM vs Angular 1 & 2 vs Mithril.js vs cito.js vs The Rest (Updated and Improved!)](https://auth0.com/blog/2016/01/11/updated-and-improved-more-benchmarks-virtual-dom-vs-angular-12-vs-mithril-js-vs-the-rest/)。

![Benchmarks showing the difference between array-ids and no array-ids https://cdn.auth0.com/blog/newdombenchs2/usedheap.svg](//o7mw3gkkh.qnssl.com//images/2016/1465566744065.png)

> The main concept behind this feature is to reuse as much existing nodes as possible. **Array ids** allow DOM-manipulation engines to "know" when a certain node can be mapped to a certain element in an array. Without **array-ids** or **track-by** most libraries resort to destroying the existing nodes and creating new ones. This impairs performance.

此特性背后的主要概念就是尽可能多地重用已有的节点。**Array ids** 使得 DOM 操作引擎可以「知道」在什么时候某个节点可以被映射到数组当中的某个元素。没有 **array-ids** 或者 **track-by** 的话，大部分库都会进行重新排序而摧毁已有的节点并重新创建新的。这就非常损耗性能了。
 
## 4. Cache | 4. 缓存

> [Caches](https://en.wikipedia.org/wiki/Cache_%28computing%29) are components that store static data that is frequently accessed so that subsequent requests to this data can be served faster or in a more efficient way. As web apps are composed of many moving parts, caches can be found in many parts of their architecture. For instance, a cache may be put in place between a dynamic content server and clients to prevent common request from increasing the load of the server and at the same time improving the response time. Other caches may be found in-code, optimizing certain common access patterns specific to the scripts in use. Other caches may be put in front of databases or long-running processes.

[Caches](https://en.wikipedia.org/wiki/Cache_%28computing%29) 是用于存储那些被频繁存取的静态数据的组件，便于随后对于这个数据的请求可以更快地被响应，或者说请求方式更加高效。由于 Web 应用是由很多可拆卸的部件组合而成，缓存就可以存在于架构中的很多部分。举例来说，缓存可以被放在动态内容服务器和客户端之间，就可以避免公共请求以减少服务器的负载，与此同时改善响应时间。其他缓存可能被放置在代码里，以优化某些用于脚本存取的通用模式，还有些缓存可能被放置在数据库或者是长运行进程之前。

> In short, caches are a great way to improve response times and reduce CPU use in web applications. The hard part is getting to know which is the right place for a cache inside an architecture. Once again the answer is profiling: where are the common bottlenecks? Are the data or results cacheable? Are they invalidated too easily? These are all hard questions that need to be answered on a case by case basis.

简而言之，在 Web 应用中使用缓存是一种改善响应时间和减少 CPU 使用的绝佳方式。难点就在于搞清楚哪里才是在架构中存放缓存的地方。再一次，答案就是性能分析：常见的瓶颈在哪里？数据或者结果可缓存吗？他们都太容易失效吗？这都是一些棘手的问题，需要从原理上来一点一点回答。

> Uses of caches can get creative in web environments. For example, there is [basket.js](https://addyosmani.com/basket.js/), a library that uses *Local Storage* to cache scripts for your app. So the second time your web app runs scripts are loaded almost instantaneously.

缓存的使用在 Web 环境中富有创造性。比如，[basket.js](https://addyosmani.com/basket.js/) 就是一个使用*Local Storage* 来缓存应用脚本的库。所以你的 Web 应用在第二次运行脚本的时候就可以几乎瞬间加载了。

> A popular caching service nowadays is [Amazon CloudFront](https://aws.amazon.com/cloudfront/dynamic-content/). CloudFront works as a general purpose content distribution network (CDN) that can be setup as a cache for dynamic content.

如今一个广受欢迎的缓存服务就是亚马逊的 [CloudFront](https://aws.amazon.com/cloudfront/dynamic-content/)。CloudFront 就跟通常的内容分发网络（CDN）用途一样，可以被设置作为动态内容的缓存。
 
## 5. Enable HTTP/2 | 5. 启用 HTTP/2

> More and more browsers are starting to support HTTP/2. This may sound superfluous but HTTP/2 introduces many benefits for concurrent connections to the same server. In other words, if there are many small assets to load (and there shouldn't if you are bundling things!), HTTP/2 kills HTTP/1 in latency and performance. Check [Akamai's HTTP/2 demo](https://http2.akamai.com/demo) on a recent browser to see the difference.

越来越多的浏览器都开始支持 HTTP/2。这可能听起来没有必要，但是 HTTP/2 为同一服务器的并发连接问题带来了很多好处。换句话说，如果有很多小型资源需要加载（如果你打包过的话就没有必要了），在延迟和性能方面 HTTP/2 秒杀 HTTP/1。试试 [Akamai 的 HTTP/2 demo](https://http2.akamai.com/demo)，可以在最新的浏览器中看到区别。
 
![](//o7mw3gkkh.qnssl.com//images/2016/1465566806854.png)

 
## 6. Profile Your App | 6. 应用性能分析

> Profiling is an essential step in optimizing any application. As mentioned in the introduction, blindly trying to optimize an app often results in lost productivity, negligible gains and harder maintainability. Profiling runs are an essential step in identifying your application hotspots.

性能分析是优化任何应用程序时的重要一步。就像介绍中所提到的那样，盲目尝试优化应用经常会导致效率的浪费，微不足道的收益和更差的可维护性。执行性能分析是识别你的应用问题所在的一个重要步骤。

> When it comes to web applications, latency is one of the biggest complaints, so you want to make sure data is loading and getting displayed as fast as possible. Chrome provides great profiling tools. In particular, both the timeline view and the network view from Chrome's Dev Tools help greatly in finding latency hotspots:

对于 Web 应用来说，延迟时间是最大的抱怨之一，所以你需要确保数据的加载和显示都尽可能得快。Chrome 提供了非常棒的性能分析工具。特别是 Chrome Dev Tools 中的时间线和网络视图都对于定位延迟问题有着很大的帮助：

![](//o7mw3gkkh.qnssl.com//images/2016/1465566860809.png) ￼

> The timeline view can help in finding long running operations.

时间线视图可以帮忙找到运行时间较长的操作。

![](//o7mw3gkkh.qnssl.com//images/2016/1465566882266.png)

> The network view can help identify additional latency generated by slow requests or serial access to an endpoint.

网络视图可以帮助识别出额外的由缓慢请求导致的延迟或对于某一端点的串行访问。

> Memory is another area that can result in gains if properly analyzed. If you are running a page with many visual elements (big, dynamic tables) or many interactive elements (for example, games), memory optimization can result in less stuttering and higher framerates. You can find good insights on how to use Chrome's Dev Tools to do this in our recent [4 Types of Memory Leaks in JavaScript and How to Get Rid Of Them](https://auth0.com/blog/2016/01/26/four-types-of-leaks-in-your-javascript-code-and-how-to-get-rid-of-them/) article.

正确分析的话，内存则是另一块可能获得收益的部分。如果你正在运行着一个拥有很多虚拟元素的页面（庞大的动态表格）或者可交互式的元素（比如游戏），内存优化可以获得更少的卡顿和更高的帧率。从我们最近的文章 [4 Types of Memory Leaks in JavaScript and How to Get Rid Of Them](https://auth0.com/blog/2016/01/26/four-types-of-leaks-in-your-javascript-code-and-how-to-get-rid-of-them/) 中，对于如何使用 Chrome 的开发工具有着进一步的深度理解。

> CPU profiling is also available in Chrome Dev Tools. See [Profiling JavaScript Performance](https://developer.chrome.com/devtools/docs/cpu-profiling) from Google's docs.

CPU 性能分析也可以在 Chrome Dev Tools 中找到。看看这篇来自 Google 官方文档中的文章 [Profiling JavaScript Performance](https://developer.chrome.com/devtools/docs/cpu-profiling)。

![](//o7mw3gkkh.qnssl.com//images/2016/1465566917028.png)

> Finding performance cost centers lets you target optimizations effectively.

找到性能损耗的中心可以让你有效率地达到优化的目标。

> Profiling the backend can be harder. Usually a notion of which requests are taking more time gives you a good idea of which services you should profile first. Profiling tools for the backend depend on which technology stack it was built with.

对后端的性能分析会更加困难。通常情况下，确认一个耗费较多时间的请求可以让你明确应该优先分析哪一个服务。对于后端的分析工具来说，则取决于所构建的技术栈。
 
### A note about algorithms | 一个关于算法的注意事项

> In a majority of cases picking a more optimal algorithm stands to provide bigger gains than implementing specific optimizations around small cost centers. In a way, CPU and memory profiling should help you find big performance bottlenecks. When those bottlenecks are not related to coding issues, it is time to think about different algorithms.

在大多数情况下，选择一个更优的算法，比围绕着小成本中心所实现的具体优化策略能够获得更大的收益。在某种程度上，CPU 和内存分析应该可以帮你找到大的性能瓶颈。当这些瓶颈跟编码问题并不相关时，则是时候考虑考虑不同的算法了。
 
## 7. Use a Load Balancing Solution | 7. 使用负载均衡方案

> We mentioned content distribution networks (CDNs) briefly when talking about caches. Distributing load among different servers (and even different geographical areas) can go a long way into providing better latency for your users. This is especially true when handling many concurrent connections.

我们在之前讨论缓存的时候简要提到了内容分发网络（CDNs）。把负载分配到不同的服务器（甚至于不同的地理区域）可以给你的用户提供更好的延迟时间，但是这条路还很漫长，特别是在处理很多的并发连接的时候。

> Load balancing can be as simple as a round-robin solution based on a [reverse nginx proxy](http://nginx.org/en/docs/http/load_balancing.html) or be based on a full-blown distributed network such as [Cloudflare](https://www.cloudflare.com/) or [Amazon CloudFront](https://aws.amazon.com/cloudfront/).

负载均衡就跟使用某个 round-robin（循环）解决方案一样简单，可以基于一个 [nginx 反向代理](http://nginx.org/en/docs/http/load_balancing.html) ，或者基于一个成熟的分布式网络，比如 [Cloudflare](https://www.cloudflare.com/) 或者 [Amazon CloudFront](https://aws.amazon.com/cloudfront/)。

![](//o7mw3gkkh.qnssl.com//images/2016/1465566942211.png)
 
> > The above diagram is based on [this one](http://docs.citrix.com/content/dam/docs/en-us/legacy-edocs/netscaler-traffic-management-10-5-map/LB-Round_Robin_Mechanism.PNG) from Citrix.
> > For load-balancing to be really useful, dynamic and static content should be split for easy concurrent access. In other words, serial access to elements impairs the ability of the load balancer to find the best way to split the work. At the same time, concurrent access to resources can improve startup times.

> 以上的图来自于 [Citrix](http://docs.citrix.com/content/dam/docs/en-us/legacy-edocs/netscaler-traffic-management-10-5-map/LB-Round_Robin_Mechanism.PNG)。
> 为了使负载均衡真正有效，动态内容和静态内容都应该被拆分成易于并发访问的。换句话说，元素的串形访问会削弱负载均衡器以最佳形式进行分流的能力。与此同时，对于资源的并发访问可以改善启动时间。

> Load balancing can be complex, though. Data models that are not friendly to eventual consistency algorithms or caching make things harder. Fortunately, most apps usually require a high level of consistency for a reduced set of data. If your application was not designed with this in mind, a refactor may be necessary.

虽然负载均衡可能会很复杂。对最终一致性算法不友好的数据模型，或者缓存都会让事情更加困难。幸运的是，大多数应用对于已简化的数据集都只需要保证高层次的一致性即可。如果你的应用程序没有这样设计的话，就有必要重构一下了。
 
## 8. Consider Isomorphic JavaScript for Faster Startup Times | 8. 为了更快的启动时间考虑一下同构 JavaScript

> One way of improving the feel of web applications is reducing the startup time or the time to render the first view of the page. This is particularly important in newer single-page applications that do a lot of work on the client-side. Doing more work on the client-side usually means more information needs to be downloaded before the first render can be performed. Isomorphic JavaScript can solve this issue: since JavaScript can run in both the client and the server it is possible for the server to perform the first render of the page, send the rendered page and then have client-side scripts take over. This limits options for the backend (JavaScript frameworks that support this must be used), but can result in a much better user experience. For instance, React can be [adapted](https://github.com/DavidWells/isomorphic-react-example) to do this, as shown in the following code:

改善 Web 应用程序观感的方式之一，就是减少启动时间或者减少首页渲染时间。这对于新兴的单页面应用尤为重要，其需要在客户端执行大量任务。在客户端做更多事情通常就意味着，在第一次渲染被执行之前就需要下载更多的信息。同构 JavaScript 可以解决这个问题：自从 JavaScript 可以同时运行在客户端和服务器端，这就让在服务器端来执行页面的首次渲染成为可能，先把已渲染的页面发送出去然后再由客户端的脚本接管。这限制了所使用的后端（必须使用支持该特性的 JavaScript 框架），但却能获得更好的用户体验。举例来说，React 就很[适合于](https://github.com/DavidWells/isomorphic-react-example)做这个，就像以下代码所示：
 
```js
var React = require('react/addons');
var ReactApp = React.createFactory(require('../components/ReactApp').ReactApp);

module.exports = function(app) {

    app.get('/', function(req, res){
        // React.renderToString takes your component
        // and generates the markup
        var reactHtml = React.renderToString(ReactApp({}));
        // Output html rendered by react
        // console.log(myAppHtml);
        res.render('index.ejs', {reactOutput: reactHtml});
    });

};
```

> [Meteor.js](https://www.meteor.com/) has great support for mixing client side with server side JavaScript:

[Meteor.js](https://www.meteor.com/) 对于客户端和服务器端的 JavaScript 混用有着非常棒的支持。
 
```js
if (Meteor.isClient) {
  Template.hello.greeting = function () {
    return "Welcome to myapp.";
  };

  Template.hello.events({
    'click input': function () {
      // template data, if any, is available in 'this'
      if (typeof console !== 'undefined')
        console.log("You pressed the button");
    }
  });
}

if (Meteor.isServer) {
  Meteor.startup(function () {
    // code to run on server at startup
  });
}
```

> However, to support server-side rendering, plugins like [meteor-ssr](https://github.com/meteorhacks/meteor-ssr) are required.

但是，为了支持服务器端渲染，需要像 [meteor-ssr](https://github.com/meteorhacks/meteor-ssr) 这样的插件。
 
> > Thanks to gabrielpoca for pointing this out in the comments.
 If you have a complex or mid-sized app that supports isomorphic deployments, give this a try. You might be surprised.

> 谢谢 gabrielpoca 在评论中指出这一点。如果你有复杂的或者中等大小的应用需要支持同构部署，试试这个，你可能会感到惊讶的。
 
## 9. Speed up database queries with indexing | 9. 使用索引加速数据库查询

> If your database queries are taking too much time to be resolved (profile your app to see if this is the case!), it is time to look for ways to speedup your database. Every database and data-model carries its own trade-offs. Database optimization is a subject in its own: data-models, database types, specific implementation options, etc. Speedups may not be easy. Here is a tip, however, that may help with some databases: [indexing](https://en.wikipedia.org/wiki/Database_index). Indexing is a process whereby a database creates fast-access data structures that internally map to keys (columns in a relational database) that can improve retrieval speed of associated data. Most modern databases support indexing. Indexing is not specific to either document-based databases (such as [MongoDB](https://docs.mongodb.org/manual/indexes/)) nor relational databases (such as [PostgreSQL](http://www.postgresql.org/docs/9.1/static/indexes.html)).

如果你需要解决数据库查询耗费大量时间的问题（分析你的应用看看是否是这种情况！），是时候找出加速数据库的方法了。每个数据库和数据模型都有自己的权衡。数据库优化在每一方面都是一个主题：数据模型，数据库类型，具体实现方案，等等。提速可能不是那么的简单。但是这儿有个建议，可能可以对某些数据库有所帮助：[索引](https://en.wikipedia.org/wiki/Database_index)。索引是一个过程，即数据库所创建的快速访问数据结构，从内部映射到键（在关系数据库中的列），可以提高检索相关数据的速度。大多数现代数据库都支持索引。索引并不是文档型数据库（比如 [MongoDB](https://docs.mongodb.org/manual/indexes/)）所独有的，也包括关系型数据库（比如 [PostgreSQL](http://www.postgresql.org/docs/9.1/static/indexes.html)）。

> To have indexes optimize your queries you will need to study the access patterns of your application: what are the most common queries, on which keys or columns do they perform the search, etc.

为了使用索引来优化你的查询，你将需要研究一下应用程序的访问模式：什么是最常见的查询，在哪个键或列中执行搜索，等等。
 
## 10. Use faster transpiling solutions | 10. 使用更快的转译方案

> The JavaScript software stack is as complex as ever. This has increased the need for improvements to the language. Unfortunately, JavaScript as a target platform is limited by the runtime of its users. Although improvements have been implemented in form of ECMAScript 2015 (with 2016 in progress) it is usually not possible to depend on this version for client side code. This trend has spurred a series of *transpilers*: tools that process ECMAScript 2015 code and implement missing features using only ECMAScript 5 constructs. At the same time, module bundling and minification have been integrated into the process to produce what could be called *built-for-release* versions of the code. These tools transform the code, and can, in a limited fashion, affect the performance of the resulting code. Google developer Paul Irish [spent some time](https://github.com/paulirish/The-cost-of-transpiling-es2015-in-2016) looking at how different transpiling solutions affect the performance and size of the resulting code. Although in most cases gains can be small, it is worth having a look at the data before committing to any toolstack. For big applications, the difference might be significant.

JavaScript 软件技术栈一如既往的复杂。而改善语言本身的需求则又增加了复杂度。不幸地是，JavaScript 作为目标平台又会被用户的运行时所限制。尽管很多改进已经以 ECMAScript 2015（2016正在进行）的形式实现了，但是通常情况下，对客户端代码来说又不可能依赖于这个版本。这种趋势促使了一系列的*转译器*：用于处理 ECMAScript 2015 代码的工具和只使用 ECMAScript 5 结构实现其中所缺失的特性。与此同时，模块绑定和压缩处理也已经被集成到这个生产过程中，被称为*为发布而构建*的代码版本。这些工具可以转化代码，并且能够以有限的方式影响到最终代码的性能。Google 开发者 Paul Irish [花了一些时间](https://github.com/paulirish/The-cost-of-transpiling-es2015-in-2016)来寻找这些转译方案会如何影响性能和最终代码的大小。尽管大多数情况下收益会很小，但也值得在正式采用某个工具栈之前看看这些数据。对于大型应用程序来说，这种区别可能会影响重大。
 
## 11. Avoid or minimize the use of render blocking JavaScript and CSS | 11. 避免或最小化 JavaScript 和 CSS 的使用阻塞渲染

> Both JavaScript and CSS resources can block the rendering of the page. By applying certain rules you can make sure both your scripts and your CSS get processed as quickly as possible so that the browser can display your site's content.

JavaScript 和 CSS 资源都会阻塞页面的渲染。通过采取某些的规则，你可以保证你的脚本和 CSS 被尽可能快速地处理，以便于浏览器能够显示你的网站内容。

> For the case of CSS it is of the essence that all CSS rules that are not relevant to the specific media on which you are displaying the page are given a lower priority for processing. This can be achieved through the use of [CSS media queries](https://developer.mozilla.org/en-US/docs/Web/CSS/Media_Queries/Using_media_queries). Media queries tell the browser which CSS stylesheets apply to a specific display media. For instance, certain rules that are specific to printing can be given a lower priority than the rules used for displaying on the screen.

在 CSS 的情况下这是非常重要的，所有的 CSS 规则都不能与特定媒体直接相关，规则只用于处理你准备在页面上所显示内容的优先级。这可以通过使用 [CSS 媒体查询](https://developer.mozilla.org/en-US/docs/Web/CSS/Media_Queries/Using_media_queries)来实现。媒体查询告诉浏览器，哪些 CSS 样式表应用在某个特定的显示媒体上。举个例子，用于打印的某些规则可以被赋予比用于屏幕显示更低的优先级。

> Media queries can be set as <link> tag attributes:

媒体查询可以被设置成 `<link>` 标签属性：
 
```html
<link rel="stylesheet" type="text/css" media="only screen and (max-device-width: 480px)" href="mobile-device.css" /> 
```

> When it comes to JavaScript, the key lies in following certain rules for inline JavaScript (i.e. code that is inlined in the HTML file). Inline JavaScript should be as short as possible and put in places where it won't stop the parsing of the rest of the page. In other words, inline HTML that is put in the middle of an HTML tree stops the parser at that point and forces it to wait until the script is done executing. This can be a killer for performance if there are big blocks of code or many small blocks littered through the HTML file. Inlining can be helpful to prevent additional network fetches for specific scripts. For repeatedly used scripts or big blocks of code this advantage is eliminated.

轮到 JavaScript 了，关键就在于遵循某些用于内联 JavaScript 的规则（比如内联在 HTML 文件当中的代码）。内联 JavaScript 应该尽可能短，并将其放在不会阻塞页面剩余部分解析的地方。换句话说，被放在 HTML 树中间的内联 JavaScript 将会在这个地方阻塞解析器，并强制其等待直到脚本被执行完毕。如果在 HTML 文件中随意放了一些大的代码块或者很多小的代码块，对于性能来说这会成为性能杀手。内联可以有效减少额外对于某些特定脚本的网络请求。但是对于重复使用的脚本或者大的代码块来说，这个好处就可以忽略不计了。

> A way to prevent JavaScript from blocking the parser and renderer is to mark the `<script>` tag as *asynchronous*. This limits our access to the DOM (no document.write) but lets the browser continue parsing and rendering the site regardless of the execution status of the script. In other words, to get the best startup times, make sure that non-essential scripts for rendering are correctly marked as asynchronous via the async attribute.

防止 JavaScript 阻塞解析器和渲染器的一种方法就是将 `<script>` 标签标记为*异步的*。这限制了我们对于 DOM 的访问但是可以让浏览器不管脚本的执行状态而继续解析和渲染页面。换句话说，为了获得最佳的启动时间，确保那些对于渲染不重要的脚本已经通过异步属性的方式标记成异步的了。

```html
<script src="async.js" async></script> 
```
 
## 12. One for the future: use service workers + streams | 12. 用于未来的一个建议：使用 service workers + 流

> A [recent post by Jake Archibald](https://jakearchibald.com/2016/streams-ftw/#streaming-results) details an interesting technique for speeding up render times: combining service workers with streams. The results can be quite compelling:

[Jake Archibald](https://jakearchibald.com/2016/streams-ftw/#streaming-results) 最近的一篇博文详细描述了一种有趣的技术，可以用于加速渲染时间：将 service workers 和流结合起来。结果非常令人叹服：

<iframe width="600" height="400" allowfullscreen="" frameborder="0" src="https://www.youtube.com/embed/Cjo9iq8k-bc">VIDEO</iframe>

> Unfortunately this technique requires APIs that are still in flux, which is why it is an interesting concept but can't really be applied now. The gist of the idea is to put a service worker between a site and the client. The service worker can cache certain data (like headers and stuff that doesn't change often) while fetching what is missing. The content that is missing can then be streamed to the page to be rendered as soon as possible.

不幸的是这个技术所需要的 APIs 都还不稳定，这也是为什么这是一种有趣的概念但现在还没有真正被应用的原因。这个想法的主旨就是在网站和客户端之间放置一个 service worker。这个 service worker 可以在获取缺失信息的同时缓存某些数据（比如 header 和一些不会经常改变的东西）。缺失的内容就可以尽可能快速地流向被渲染的页面。
 
## 13. UPDATE: image encoding optimizations | 13. 更新：图片编码优化

> One of [our readers](https://twitter.com/dennisl/status/702123202118447105) pointed a very important omission: image encoding optimizations. Both PNGs and JPGs are usually encoded using sub-optimal settings for web publishing. By changing the encoder and its settings, significant savings can be realized for image-heavy sites. Popular solutions include [OptiPNG](http://optipng.sourceforge.net/) and [jpegtran](http://jpegclub.org/jpegtran/).

我们的[一个读者](https://twitter.com/dennisl/status/702123202118447105)指出了一个非常重要的遗漏：图片编码优化。PNGs 和 JPGs 在 Web 发布时都会使用次优的设置进行编码。通过改变编码器和它的设置，对于需要大量图片的网站来说可以获得有效的改善。流行的解决方案包括 [OptiPNG](http://optipng.sourceforge.net/) 和 [jpegtran](http://jpegclub.org/jpegtran/)。

> [A guide to PNG optimization](http://optipng.sourceforge.net/pngtech/optipng.html) details how OptiPNG can be used to optimize PNGs.

[A guide to PNG optimization](http://optipng.sourceforge.net/pngtech/optipng.html) 详细描述了 OptiPNG 可以如何用于优化 PNGs。

> [The man page for jpegtran](http://linux.die.net/man/1/jpegtran) provides a good intro to some of its features.

[The man page for jpegtran](http://linux.die.net/man/1/jpegtran) 对它的一些特性提供了很好的介绍。

> If you find these guides too complex for your requirements, there are online sites that provide optimization as a service. There are also GUIs such as [RIOT](http://luci.criosweb.ro/riot/) that help greatly in doing batch operations and checking the results.

如果你发现这些指南相对于你的要求来说都太复杂了的话，这儿有一些在线网站可以提供优化服务。也有一些像 [RIOT](http://luci.criosweb.ro/riot/) 一样的图形化界面，非常有助于批量操作和结果检查。

## Further reading | 扩展阅读

> You can read more information and find helpful tools for optimizing your site in the following links:

你可以在下面的链接中阅读更多信息，以及找到有助于优化网站的工具：

- [Best Practices for Speeding up Your Website - Yahoo Developer Network](https://github.com/paulirish/The-cost-of-transpiling-es2015-in-2016)
- [YSlow - a tool that checks for Yahoo's recommended optimizations](http://yslow.org/)
- [PageSpeed Insights - Google Developers](https://developers.google.com/speed/docs/insights/rules)
- [PageSpeed Tools - Google Developers](https://developers.google.com/speed/pagespeed/)
- [HTTP/2: The Long-Awaited Sequel](http://blogs.msdn.com/b/ie/archive/2014/10/08/http-2-the-long-awaited-sequel.aspx)

## Aside: common optimizations at Auth0 | 悄悄话：Auth0 中常见的优化

> We are a web company. As such, we have deployed specific optimizations for certain parts of our infrastructure. For instance, for the landing pages which you can find at the `/learn` path of our domain (for example, the [single sign on landing page](https://auth0.com/learn/how-to-implement-single-sign-on/)), we have resorted to a particular optimization: for convenience we use a CMS to create each post. As posts have no central index but are meant to be found by search engines, a crawler using a [webtask](https://webtask.io) pre-renders each page and generates a static version of it which is then uploaded to our CDN. This reduces load on our servers as no dynamic server-side content is generated for each visitor. At the same time this improves latency (and isolates us from security issues related to the CMS we picked).

我们是一个 Web 公司。就以这种身份来说，我们为我们的基础设施的某些部分部署了一些特定的优化。举例来说，在登录页面你可以发现，在我们域名的 `/learn` 路径下（比如，[登录页面的单点登录](https://auth0.com/learn/how-to-implement-single-sign-on/)），我们采用了一种特别的优化：为了方便我们使用 CMS 来创建每篇文章。因为文章都没有中心索引，但是为了能够被搜索引擎发现，使用了 [webtask](https://webtask.io) 的爬虫来预渲染每个页面并生成了一个静态版本然后上传到我们 CDN。这减少了我们在服务器端上的压力，因为无须为每个访客都生成动态的服务器端内容。与此同时还改善了延迟（并且隔离了我们发现与 CMS 相关的安全问题）。

> For the [docs area](https://auth0.com/docs) we are using *isomorphic JavaScript* which gives us great startup times and easy integration between our backend and frontend teams.

对于[文档部分](https://auth0.com/docs)，我们正在使用*同构 JavaScript*，这让我们获得了非常棒的启动时间，并且使我们的后端和前端团队能够轻松集成。

> Want to see our code in action? Sign-up.

想要实战看看我们的代码？注册一下吧。

> Are you a web developer with a taste for speed? Are you interested in working in an awesome development team? Show us how we can optimize our site along with a short intro about yourself to [jobs@auth0.com](mailto:jobs@auth0.com).

你是一个爱好速度的 web 开发者吗？你有兴趣和优秀的开发团队共事吗？向我们展示一下可以如何优化我们的网站，并附带一个简单的自我介绍发送至 [jobs@auth0.com](mailto:jobs@auth0.com) 吧。

## Conclusion | 结论

> Performance optimizations are getting more and more important for web development as applications get bigger and more complex. Targeted improvements are essential to make any optimization attempt worth the time and potential future costs. Web applications have long ago crossed the boundary of mostly static content and learning common optimization patterns can make all the difference between a barely usable application and an enjoyable one (which goes a long way to keeping your visitors!). No rules are absolute, however: profiling and studying the intricacies of your specific software stack are the only way of finding out how to optimize it. Have you found any other tips that made a big difference for your app? Let us know in the comments. Hack on!

由于应用程序变得越来越大和越来越复杂，性能优化对于 Web 开发来说正在变得越来越重要。在做出任何值得的时间和潜在的未来成本的优化尝试时，有针对性的改进都是必不可少的。Web 应用程序早已突破了大多数静态内容的边界，学习常见模式进行优化则是令人愉悦的应用和完全不可用的应用之间最大的区别（这是让你的访客留下来的长远之计！）。没有什么规则是绝对的，但是：性能分析和研究特定软件技术栈的错综复杂之处，是找出如何优化它的唯一方式。你曾经发现过对你的应用产生巨大影响的其他建议吗？请留言让我们知道。Hack on！