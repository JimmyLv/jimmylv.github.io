---
layout: post
title: 【译】什么是 Flux 架构？（兼谈 DDD 和 CQRS）
categories: [翻译]
tags: [Flux, DDD, CQRS, Architecture, MVC]
published: True

---

> [Flux](http://facebook.github.io/flux/docs/overview.html) is an application architecture designed by Facebook for their JavaScript applications. It was first introduced by Facebook in May 2014, and it has since garnered much interest in the JavaScript community.

[Flux](http://facebook.github.io/flux/docs/overview.html) 是一个由 Facebook 为其应用所设计的应用程序架构。Facebook 在 2014 年五月的时候首次提出 Flux，如今已经收获了 JavaScript 社区的浓厚兴趣。

> There are several implementations of Flux. Frameworks like [Fluxxor](http://jaysoo.ca/2015/02/06/what-the-flux/fluxxor.com) keep to the original Facebook Flux pattern, but reduces the amount of boilerplate code. While other frameworks like [Reflux](https://github.com/spoike/refluxjs) and [Barracks](https://github.com/yoshuawuyts/barracks) stray from the canonical Flux architecture by getting rid of the Dispatcher (Reflux) or ActionCreators (Barracks). So which framework should you choose?

现在市面上有一大堆的 Flux 实现。像 [Fluxxor](http://jaysoo.ca/2015/02/06/what-the-flux/fluxxor.com) 这样的框架在保持原生 Facebook Flux 模式的同时，减少了大量的样板文件代码。与此同时，其他类似 [Reflux](https://github.com/spoike/refluxjs) 和 [Barracks](https://github.com/yoshuawuyts/barracks) 之类的框架则偏离了规范的 Flux 架构，Reflux 摒弃了 Dispatcher，而 Barracks 则 抛弃了 ActionCreators。所以你会选择哪个框架呢？

> Before we get too wrapped up about what is canon, and whether we should be deviating from them, let’s consider a look into the past.

在我们深入了解标准以及是否选择偏离他们之前，让我们来考虑一下过去。

> While the Flux pattern may have found a new home in JavaScript applications, they have been explored before in **Domain-Driven Design** (DDD) and **Command-Query Responsibility Segregation** (CQRS). I think it is useful to learn from these older concepts, and see what they may tell us about the present.

虽然 Flux 模式在 JavaScript 应用里像是找到了新家一样，但是它们肯定也借鉴了**领域驱动设计** (DDD) 和**命令-查询职责分离** (CQRS)。我觉得学习这些以前的概念非常有用，来看看它们会告诉我们和现在有怎样的故事。

#### In this post I will: | 在这篇文章我将：

> 1. Give an overview of the Flux architecture.
> 2. Present the CQRS pattern.
> 3. Look at how Flux applies the concepts from CQRS.
> 4. Discuss when Flux is useful for a JavaScript application.

1. Flux 架构概述
2. 描述 CQRS 模式
3. Flux 如何应用来自 CQRS 的概念
4. 讨论 Flux 何时适用于 JavaScript 应用
    
> > Knowledge of DDD is assumed, though the article still provides value without it. To learn more about DDD, I recommend this [free ebook](http://www.infoq.com/minibooks/domain-driven-design-quickly) from InfoQ on the subject. 

> > Examples will be shown in JavaScript, though the language isn't the focus of this post. 

> 假设已知 DDD 基础知识，但是没有相关基础的话这篇文章也依然有价值。想了解更多关于 DDD 的知识，我推荐 InfoQ 有关这个话题的[免费电子书](http://www.infoq.com/minibooks/domain-driven-design-quickly)。

> 例子将会使用 JavaScript 展示，尽管语言并不是这篇文字的重点。

## What is Flux? | 什么是 Flux？

> A common way to describe Flux is by comparing it to a **Model-View-Controller** (MVC) architecture.

描述 Flux 最普遍的一种的方式就是将其与 **Model-View-Controller** (MVC) 架构进行对比。

> In MVC, a Model can be read by multiple Views, and can be updated by multiple Controllers. In a large application, this results in highly complex interactions where a single update to a Model can cause Views to notify their Controllers, which may trigger even more Model updates.

在 MVC 当中，一个 Model 可以被多个 Views 读取，并且可以被多个 Controllers 进行更新。在大型应用当中，单个 Model 会导致多个 Views 去通知 Controllers，并可能触发更多的 Model 更新，这样结果就会变得非常复杂。

![](//o7mw3gkkh.qnssl.com//images/2016/1467895052725.png)

> Flux attempts to solve this complexity by forcing a unidirectional data flow. In this architecture, Views query Stores (not Models), and user interactions result in Actions that are submitted to a centralized Dispatcher. When the Actions are dispatched, Stores can then update themselves accordingly and notify Views of any changes. These changes in the Store prompts Views to query for new data.

Flux 试图通过强制单向数据流来解决这个复杂度。在这种架构当中，Views 查询 Stores（而不是 Models），并且用户交互将会触发 Actions，Actions 则会被提交到一个集中的 Dispatcher 当中。当 Actions 被派发之后，Stores 将会随之更新自己并且通知 Views 进行修改。这些 Store 当中的修改会进一步促使 Views 查询新的数据。

![](//o7mw3gkkh.qnssl.com//images/2016/1467895448296.png)

> The main difference between MVC and Flux is the separation of queries and updates. In MVC, the Model is both updated by the Controller *and* queried by the View. In Flux, the data that a View gets from a Store is read-only. Stores can only be updated through Actions, which would affect the Stores themselves *not* the read-only data.

MVC 和 Flux 最大的不同就是查询和更新的分离。在 MVC 中，Model 同时可以被 Controller 更新*并且*被 View 所查询。在 Flux 里，View 从 Store 获取的数据是只读的。而 Stores 只能通过 Actions 被更新，这就会影响 Store 本身*而不是*那些只读的数据。

> The pattern described above is very close to CQRS as first described by Greg Young.

以上所描述的模式非常接近于由 Greg Young 第一次所提出的 CQRS。

## Command-Query Responsibility Segregation | 命令-查询职责分离

> To understand CQRS, let’s first talk about the object pattern **Command-Query Separation** (CQS).

为了理解 CQRS，让我们首先来讲讲对象模式**命令-查询分离**（CQS）。

> CQS at an object level means: 

> 1. If a method mutates the state of the object, it is a *command*, and it must not return a value.
> 2. If the method returns some value, it is a *query*, and it must not mutate state.

CQS 在一个对象的层面上意味着：

1. 如果一个方法修改了这个对象的状态，那就是一个 *command*（命令），并且一定不能返回值。
2. 如果一个方法返回了一些值，那就是一个 *query*（查询），并且一定不能修改状态。

> In normal DDD, Aggregate objects are used for both command and query. We will also have Repositories that contain methods to find and persist Aggregate objects.

在一般的 DDD 当中，Aggregate 对象通常被用于命令和查询。我们也有 Repositories 维护用于查找和存储 Aggregate 对象的方法。

> CQRS simply takes CQS further by separating command and query into different objects. Aggregates would have no query methods, only command methods. Repositories would now only have a single query method (e.g. `find`), and a single persist method (e.g. `save`).

CQRS 仅仅是让 CQS 进一步将命令和查询拆分到不同的对象当中。Aggregate 对象将不再拥有查询方法，而只有命令方法。Repositories 将不再只有一个单独的查询方法（如 `find`），而且有了一个存储方法（如 `save`）。

> In the CQRS pattern, you will find new objects not found in normal DDD.

在 CQRS 模式当中，你还会发现一些普通的 DDD 里找不到的新对象。

### Query Model | 查询模型

> The *Query Model* is a pure data model, and is not meant to deliver domain behaviour. These models are denormalized, and meant for display and reporting.

*查询模型* 就是一个纯数据模型，并且不再提供领域行为。这些模型都是[反规范化](http://www.searchdatabase.com.cn/whatis/word_5893.htm)的，用于显示和报告。

### Query Processor | 查询处理器

> Query Models are usually retrieved by performing a query. The queries can be handled by a *Query Processor* that knows how to look up data, say from a database table.

查询模型通常是在执行查询时获取到的。这些查询将被一个*查询处理器*所处理，这个处理器知道如何从一个数据库表中查找数据。

### Command Model | 命令模型

> Command Models are different from normal Aggregates in that they only contain command methods. You can never “ask” it anything, only “tell” (in the Tell, Don’t Ask sense).

命令模型和一般的 Aggregates 不同的地方在于它们只包含命令方法。你永远都不能「问」它任何事情，而只能「告诉」（用「告诉」，而不是靠「问」）。

> As a command method completes, it publishes a Domain Event. This is crucial for updating the Query Model with the most recent changes to the Command Model.

当一个命令方法完成之后，它就会发布一个「领域事件」（Domain Event）。这对于命令模型使用最新的更改进而更新查询模型来说是非常重要的。

### Domain Event | 领域事件

> Domain Events lets Event Subscribers know that something has changed in the corresponding Command Model. They contain the *name* of the event, and a *payload* containing sufficient information for subscribers to correctly update Query Models.

领域事件会让「事件订阅者」（Event Subscribers）知道在相应的命令模型中发生了一些变化。它们包含着这个事件的*名字*，并且附带一个 *payload*，里面包含了能让订阅者正确更新查询模型的有效信息。

> > **Note:** Domain Events are always in past tense since they describe what has already occurred (e.g. `'ITEM_ADDED_TO_CART'`). 

> **注意：**领域事件总在过去时，因为它们描述着已发生的事情（如 `'ITEM_ADDED_TO_CART'`）。

### Event Subscriber | 事件订阅者

> An *Event Subscriber* receives all Domain Events published by the Command Model. When an event occurs, it updates the Query Model accordingly.

一个*事件订阅者*接受由命令模型所发布的所有领域事件。当一个事件发生时，它就会相应地更新查询模型。

### Command | 命令
 
> *Commands* are submitted as the means of executing behaviour on Command Models. A command contains the *name* of the behaviour to execute and a *payload* necessary to carry it out.

命令模型所执行的行为就意味着所提交的*命令*。一个命令包含这个要被执行的行为的*名字*和需要携带的*负载*。

> > **Note:** Commands are always in imperative tense since they describe behaviours that need to be executed (e.g. `AddItemToCart`). 

> **注意：**命令总是命令式的，因为它们描述需要被执行的行为（比如 `AddItemToCart`）。

### Command Handler | 命令处理器

> The submission of a Command is received by a *Command Handler*, which usually fetches an Command Model from its Repository, and executes a Command method on it.

提交的命令会被一个*命令处理器*接收，通常来说会从它的 Repository 当中取出一个命令模型，然后执行其中的命令方法。

## An example in e-commerce | 一个电商例子

> Let’s compare normal DDD with CQRS in the context of an e-commerce system with a shopping cart.

让我们来比较普通的 DDD 和 CQRS 在电子商务系统中的购物车场景下的区别。

### Shopping cart with normal DDD | 使用普通 DDD 的购物车

> In normal DDD, we may find an Aggregate `ShoppingCart` that contains multiple `CartItems`, as well as a corresponding Repository.

在普通的 DDD 当中，我们可能会发现一个 Aggregate `ShoppingCart` 会包含多个 `CartItems`，并且会有一个相应的 Repository。
    
```js
// The Aggregate model
class ShoppingCart {
  constructor({id: id, cartItems: cartItems, taxPercentage: taxPercentage,
                shippingAndHandling: shippingAndHandling}) {
    this.id = id;
    this.cartItems = cartItems || [];
    this.taxPercentage = this.taxPercentage;
    this.shippingAndHandling = shippingAndHandling;
  }

  // Command methods
  addItem(cartItem) {
    this.cartItems.push(cartItem);
  }
  removeItem(cartItem) {
    this.cartItems = cartItems.filter((item) => item.sku !== cartItem.sku);
  }

  // Query method
  total() {
    var prices = this.shoppingCart.cartItems.map((item) => item.price);
    return prices.reduce((total, price) => total + price, 0);
  }
}

// A child of the Aggregate
class CartItem {
  constructor({sku: sku, description: description, price: price, quantity: quantity}) {
    this.sku = sku;
    this.description = description;
    this.price = price;
    this.quantity = quantity;
  }
}

// Repository to perform CRUD operations
class ShoppingCartRepository {
  all() { /* … */ }
  findById(id) { /* … */ }
  create(cart) { /* … */ }
  update(cart) { /* … */ }
  destroy(cart) { /* … */ }
}
```

> Here, the `ShoppingCart` is responsible for both queries (`cartItems` and `total()`), and updates (`addItem()`, `removeItem()`, and normal property setters). The `ShoppingCartRepository` is used to perform CRUD operations on `ShoppingCart`.

此时，`ShoppingCart` 要共同维护查询（`cartItems` 和 `total()`）和更新（`addItem()`， `removeItem()` 和普通属性的 setters）。而 `ShoppingCartRepository` 则被用于执行在 `ShoppingCart` 上的 CRUD 操作。

### Shopping cart with CQRS | 使用 CQRS 的购物车

> In CQRS, we can do the following:

> 1. Convert the `ShoppingCart` into a Command Model. It would not have any query methods, only command methods. It also has the extra responsibility to publish two Domain Events (`'CART_ITEM_ADDED'`, `'CART_ITEM_REMOVED'`).
> 2. Create a Query Model for reading the shopping cart total (replacing the original `.total()` method). This Query Model can simply be a plain JavaScript object.

在 CQRS 中，我们可以这样做：

1. 把 `ShoppingCart` 变成一个命令模型，不再有任何查询方法，而只有命令方法。它还会额外负责两个领域事件的发布（`'CART_ITEM_ADDED'`， `'CART_ITEM_REMOVED'`）。
2. 创建一个查询模型用于读取购物车当中的总数（代替原有的 `.total()` 方法）。这个查询模型可以是一个简单的 JavaScript 对象。

```js
{
  cartId: 123,
  total: 129.95
}    
```

> 1. Create `CartTotalStore` that holds the query models in memory. This object acts like a Query Processor in that it knows how to look up out Query Models.
> 2. Create an Event Subscriber that will keep out Query Models updated whenever Domain Events are published. In this example we will assign this extra responsibility to the `CartTotalStore`, which is easier and closer to what Flux does.
> 3. Create a Command Handler `ShoppingCartCommandHandler` in order to execute behaviour on the Command Model. It will handle both `AddItemToCart` and `RemoveItemFromCart` Commands.

1. 创建 `CartTotalStore` 用来维护查询模型的金额。这个对象就像查询处理器一样，知道如何查找查询模型。
2. 创建一个事件订阅者，将会基于事件模型的发布随时保持查询模型的更新。在这个例子里面，我们将会给 `CartTotalStore` 赋予额外的职责，这样更容易也更接近于 Flux 的做法。
3. 创建一个命令处理器 `ShoppingCartCommandHandler` 以便于执行命令模型之上的行为。它将会一起处理 `AddItemToCart` 和 `RemoveItemFromCart` 命令。

> > **Note:** We are creating a Command Handler that is responsible for multiple Commands. In practice, we may choose to create one handler for each command.

> **注意：**我们现在只创建了一个命令处理器用于处理多个命令。而实际操作上，我们可能会选择给每个命令都创建一个处理器。

```js
// The Command Model publishes Domain Events.
class ShoppingCart {
  constructor(/* … */) {
    // …
  }
  addItem(cartItem) {
    // …
    DomainEventPublisher.publish('CART_ITEM_ADDED', {
      cartId: this.id,
      sku: cartItem.sku,
      price: cartItem.price,
      quantity: cartItem.quantity
    });
  }
  removeItem(cartItem) {
    // …
    DomainEventPublisher.publish('CART_ITEM_REMOVED', {
      cartId: this.id,
      sku: cartItem.sku,
      price: cartItem.price,
      quantity: cartItem.quantity
    });
  }
}

// This object acts as both the Query Processor and Event Subscriber.
class CartTotalStore {
  constructor() {
    // Holds Query Models in memory.
    this.totals = {};

    // Subscribe to events that allows this store to update its Query Models.
    DomainEventPublisher.subscribeTo('ITEM_ADDED_TO_CART', this.handleItemAdded);
    DomainEventPublisher.subscribeTo('ITEM_REMOVED_FROM_CART', this.handleItemRemoved);
  }

  // Query method
  forCart(cartId) {
    return {
      cartId: cartId,
      total: this.totals[id]
    };
  }

  // Methods to update Query Models.
  handleItemAdded({cartId: cartId, cartItem: cartItem}) {
    var total = this.totals[cartId] || 0;
    var newTotal = total + cartItem.price * cartItem.quantity
    this.totals[cartId] = newTotal;
  }
  handleItemRemoved({cartId: cartId, cartItem: cartItem}) {
    var total = this.totals[cartId] || 0;
    var newTotal = total - cartItem.price * cartItem.quantity
    this.totals[cartId] = newTotal;
  }
}

// This Command Handler maps Commands to command methods ShoppingCart.
class ShoppingCartCommandHandler extends CommandHandler {
  constructor(repo) {
    this.repo = repo;

    // Assumes commands implement subscribe that appends the handler to themselves.
    AddItemToCart.subscribe(this.addItemToCart);
    RemoveItemFromCart.subscribe(this.removeItemFromCart);
  }
  addItemToCart(payload) {
    var cart = this.repo.find(payload.cartId);
    cart.addItem(payload.cartItem); // This publishes a Domain Event
  }
  removeItemToCart(payload) {
    var cart = this.repo.find(payload.cartId);
    cart.removeItem(payload.cartItem); // This publishes a Domain Event
  }
}
```

> You should now have an understanding of CQRS. Next, we will examine how Flux relates to CQRS.

现在你应该已经对 CQRS 有了一定的了解。那么接下来，我们将会仔细介绍 Flux 与 CQRS 是如何搞基的。

## Flux and CQRS | Flux 和 CQRS 

> Let’s see how the different types of object in Flux map to the CQRS pattern.

让我们来看看如何将 Flux 中的不同对象映射到 CQRS 模式当中。

### Actions

> Actions are exactly the same as Domain Events. They should represent events that have happened in the past, and will cause updates to Query Models in the system.

Actions 就跟领域事件一模一样。它们都代表着过去发生的一些事件，并且将会导致系统中的查询模型被修改。

### Dispatcher

> The Dispatcher is the Domain Event Publisher. It is a centralized place where Actions are published to. It also allows Stores to subscribe to Actions that are published in the system.

Dispatcher 就是领域事件发布者。这是 Actions 被发布之后所到达的一个中心地，它还允许 Stores 订阅在系统中已经发布出去的 Actions。

### Stores

> Stores listen for Actions published through the dispatcher, and update themselves accordingly. In CQRS, they would be the Event Subscriber.

Stores 监听通过 Dispatcher 所发布的 Actions，并相应地更新自己。在 CQRS 中，其实就是事件订阅者。

> In addition to being the Event Subscribers, they also act as Query Processors. This is intentionally similar to our implementation of `CartTotalStore`. In some CQRS systems, however, the Event Subscriber and Query Processor may not be the same object.

除了作为事件订阅者，他们也作为查询处理器。这表面上类似于我们的 `CartTotalStore` 的实现。但是在一些 CQRS 系统中，事件订阅者和查询处理器可能都不是同一个对象。

### ActionCreators

> ActionCreators are the Command Handlers. In this case, though, submitting Commands just means calling methods on the ActionCreator. As opposed to having Commands exist as a separate object.

ActionCreators 就是命令处理器。不过，在这种情况下，提交命令只是意味着调用 ActionCreator 上的方法，而不是让命令以一个单独对象的形态而存在。

e.g. `ShoppingCartActionCreators.addItem(…)`

> As you see, the canonical Flux architecture is only one way of implementing CQRS in a system. It also adds a lot of objects into a system, compared with a normal DDD approach. Is added bloat worth it?

如你所见，规范的 Flux 只是一种 CQRS 在系统中的一种实现方式。相比于 一般的 DDD 方法，它也给一个系统添加了大量的对象。有必要因此而得意吗？

## When should I Flux? | 何时应用 Flux？

> I don’t think this architectural pattern is appropriate for all situations. Like other tools under our belt, don’t use mindlessly apply the same patterns everywhere.

我不认为这种架构模式适用于所有情况。就像我们面对过的其他工具一样，不要盲目地在所有地方都运用同一种模式。

> In particular, Flux *may be inappropriate* if your views map well to your domain models. For example, in a simple CRUD application, you may have exactly three views for each model: index, show, and edit + delete. In this system, you will likely have just one controller and one view for each CRUD operation on your model, making the data flow very simple.

特别的是，Flux *可能不适用于*视图和领域模型合理映射的情况。比如说，在一个简单的 CRUD 应用程序里，对于每种模型来说，你都可能有三种视图：index，show，以及 edit 和 delete。在这种系统里，你可能只需要给每个模型的 CRUD 操作配备一个控制器和视图就可以了，数据流就已经足够简单。

> Where Flux *shines* is in a system where you present multiple views that don’t map directly to your domain models. The views may be presenting data aggregated across multiple models and model classes.

在一个系统中，在你需要描述多个视图并且不能直接映射到领域模型的地方，Flux 能够*大展宏图*。这些视图可能需要来自于多个模型和不同种类的聚合数据。

> In our shopping cart example, we may have:

> 1. A view that lists out items in the cart.
> 2. A view that handles displaying subtotals, taxes, shipping & handling, and totals.
> 3. A view that displays amount of items in cart, with a detailed dropdown.

在我们的购物车例子里，我们可能有：

1. 一个列出购物车所有物品的视图。
2. 一个处理显示汇总，税，配送和包装，以及总数的视图。
3. 一个处理购物车中物品的个数，以及下拉详情菜单的视图。

![](//o7mw3gkkh.qnssl.com//images/2016/1467904299891.png)

> In this system, we don’t want to tie different views and controllers directly to a ShoppingCart model because changes to the model causes a complex data flow that is hard to reason about.

在这个系统中，我们不想把不同的视图和控制器直接绑定到 ShoppingCart 一个模型上，因为这个模型的修改将会导致难以理解的复杂数据流。

## Closing thoughts | 结论

> As you have seen, we can think about the canonical Flux architecture in terms familiar in CQRS.

就像你已经看到的那样，我们可以认为规范的 Flux 架构跟 CQRS 非常相似。

> There are several object roles in CQRS.

> * Query Model
> * Query Processor
> * Command Model (Aggregate)
> * Commands
> * Command Handler
> * Domain Event
> * Domain Event Publisher
> * Event Subscriber

这是一些 CQRS 当中的对象角色。

* Query Model | 查询模型
* Query Processor | 查询处理器
* Command Model (Aggregate) | 命令模型（Aggregate）
* Commands | 命令
* Command Handler | 命令处理器
* Domain Event | 领域事件
* Domain Event Publisher | 领域事件发布者 
* Event Subscriber | 事件订阅者

> In Facebook Flux some objects take on more than one role. This is perfectly reasonable to do! When we encounter other Flux implementations, we could also discuss them using the different object roles in CQRS.

在 Facebook 的 Flux 里有一些对象承担了多个角色。这是非常合理的！当我们遇到其他的 Flux 实现，我们也可以讨论他们使用了哪些 CQRS 中的不同对象。

> Does this mean we should buy books and materials about CQRS and become experts on that? Not necessarily. But I think it is interesting to see how some of these old concepts are becoming new again.

难道这就意味着我们应该买一些与 CQRS 相关的书和材料，并且成为相关的专家吗？并不需要。但是我觉得呢，了解这些旧概念是怎样重新焕发新生的是一件非常有趣的事情。😃

### Further Readings | 扩展阅读

* [The State of Flux](https://reactjsnews.com/the-state-of-flux/)
* [Domain-Driven Design Quicky](http://www.infoq.com/minibooks/domain-driven-design-quickly) (ebook)
* [CQRS writeup by Martin Fowler](http://martinfowler.com/bliki/CQRS.html)
