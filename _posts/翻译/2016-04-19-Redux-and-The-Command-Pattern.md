---
layout: post
title: "【译】Redux 和 命令模式"
categories: [翻译]
tags: [React, Redux, Design Pattern]
published: True

---

原文地址：[Redux and The Command Pattern (Apr 7, by Abhi Aiyer)](https://medium.com/@abhiaiyer/the-command-pattern-c51292e22ea7)

> There are two things I know for absolute certainty in the Software industry.

据我所知，软件行业有两件必然确定的事情：

## 1\. Frameworks Always Change | 1. 框架永远都在变化

> We’ve all been there. The Vicious cycle:

而，我们都曾在那里，恶性循环：

![](https://cdn-images-1.medium.com/max/1600/1*bl67_i5wn3Hro-eXBHa-TA.png)

> If things always change, then as a Software Engineer your job is to constantly be learning and making the right bets in libraries or frameworks you decide to use.

如果事情总是在变化，那么作为一名软件工程师，你的工作就是持续不断的学习，以及在你决定使用的库或框架上做出正确的押注。

## 2\. Design Patterns are the foundation of Software Engineering | 2. 设计模式是软件工程的基础

> So if we know Frameworks always change, then we have to stick to the foundation of great software: Design Patterns.

既然我们已经知道了框架永远都会变化，那我们就必须坚持优秀软件的基础：设计模式。

> Design patterns represent the **best practices** used by experienced software developers. Design Patterns **teach you how to think**. The main benefit of learning design patterns is that you can come up with solutions to your problems a lot faster and if your co-workers are aware of these patterns, everyone can speak the same language. Now I’m advocating Design Patterns, but they are not the end all be all of solutions. Its okay if you are not using every piece of a design pattern as long you have a better solution to your particular problem.

设计模式就代表着**最佳实践**，这些实践都是由经验丰富的软件开发者所使用并总结出来的。设计模式**教会你如何思考**。学习设计模式的主要好处就是，你在面对问题的时候能够更加快速地提出解决方案，如果你的同事也有设计模式方面的知识的话，那么每个人就是在说着同样一种语言。虽然现在我在提倡设计模式，但他们并不是最终的解决方案。只要你对于特定问题能有更好的解决方案，那么即使你并没有使用任何设计模式也是 okay 的。

## History Lesson | 历史的教诲

> We can trace design patterns back to Christopher Alexander, author of [Pattern Language](https://en.wikipedia.org/wiki/A_Pattern_Language). Alexander realized that certain methods, over time, created constructs to achieve efficiency. It was then, stemming from Alexander’s work, other publications started coming out. A great one to read is *[Design Patterns: Elements of Reusable Object-Oriented Software](http://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612)*. This describes patterns that provided solutions to common software development problems.

对于设计模式我们可以追溯到 Christopher Alexander，[Pattern Language](https://en.wikipedia.org/wiki/A_Pattern_Language) （中译名：[《建筑模式语言》](https://book.douban.com/subject/1157145/)）的作者，Alexander 意识到，随着时间的推移，某些方法所创造的结构可以达成效率。当时，由于 Alexander 的工作，其他出版物也开始出来了。其中很棒的一本读物就是 *[Design Patterns: Elements of Reusable Object-Oriented Software](http://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612)* （中译名：[《设计模式:可复用面向对象软件的基础》](https://book.douban.com/subject/1052241/)）。这本书描述了给常见的软件开发问题提供解决方案的各种模式。

> A great book for JavaScript developers is by Addy Osmani. It’s available online [here](https://addyosmani.com/resources/essentialjsdesignpatterns/book/).

对于 JavaScript 开发者来说，这儿有一本来自于 Addy Osmani 的好书。你可以在[这里](https://addyosmani.com/resources/essentialjsdesignpatterns/book/)在线查看。

## Command Pattern | 命令模式

> The Command Pattern is a great pattern for architecting really clean decoupled systems. The motivation of this pattern is to execute some piece of business logic at some point in the future. The reason why I wanted to touch on the Command Pattern specifically is because I believe its the root pattern of **Redux**. Let’s get into the Command Pattern, then translate this to Redux.

在设计真正解耦合的整洁系统架构时，命令模式是一种非常棒的模式。这种模式的缘由就是为了能够在未来的某个时刻执行某个部分业务逻辑。在这里我想要特别提及命令模式的原因，是因为我认为这是 **Redux** 模式的根源。现在就让我们来走进命令模式，然后将其「翻译」成 Redux。

> There are several elements to the Command Pattern: the **Receiver**, **Command**, and the **Executor**.

首先要理解命令模式当中的一些基本要素：**Receiver**， **Command**，以及 **Executor**。

### **The Receiver** | **接收器**

> The receivers job is to hold our business logic. When given a command, it knows how to fulfill that request.

**接收器**的职责就是保存我们的业务逻辑。每当给到一个命令，它都能知道如何满足相应的要求。

> Imagine we are running sales for Tesla’s new Model 3. Let’s write some code to describe how this would look:

想象一下我们正在销售特斯拉的新车型 Model 3。让我们写些代码来描述一下这是如何工作的：

    /**
     + Request information about the car
     + @param model - model of car
     + @param id - id of car
     **/
    function requestInfo(model, id) {
      return `${model} with id: ${id}`;
    }

    /**
     + Buy the car
     + @param model - model of car
     + @param id - id of car
     **/
    function buyVehicle(model, id) {
      return `You purchased ${model} with id: ${id}`;
    }

    /** 
     + Arrange viewing for car
     + @param model - model of car
     + @param id - id of car
     **/
    function arrangeViewing(model, id) {
      return `You have successfully booked a viewing of ${model} (${id})`;
    }

> In the traditional command pattern we would encapsulate this information in an object.

在传统的命令模式下，我们通常会将这些信息包裹在一个对象当中。

    const TeslaSalesControl = {
      buyVehicle,
      requestInfo,
      arrangeViewing
    }

    export default TeslaSalesControl;

### **The Command** | **命令**

> This contains information about the action being called, and its required parameters. It is represented as an object.

**命令**这会包含行为调用时的一些信息，及其所需要的参数，通常就表示为一个对象。

    const sampleCommand = {
      action: "arrangeViewing", 
      params: ['Tesla 3', '1337']
    };

> As you can see, the command defines the action. This corresponds to the method that is on our control object. In the example above, our sample command is taking the action “arrangeViewing”. It also passes the required params to arrangeViewing: **model** and **carId**.

如你所见，一个**命令**就定义着一个行为， 这与我们在控制对象当中的方法是一致的。在上面的例子中，我们的命令就是执行 “arrangeViewing” 行为。与此同时它也给 arrangeViewing 传入了两个必需的参数：**model** 和 **carId**。

### **The Executor** | **执行器**

> The next thing we need is an interface to executes commands. Lets give our Sales control an execution function. For this function I wanted to write a generic executor that can accept and receiver. The executors job is pass the command to the receiver and call our business logic.

接下来我们需要做的就是一个执行命令的接口。让我们来给 Sales 控制器加上一个执行函数。对这个函数来说我想要实现一个能够用于接收的通用执行器，以及接收器。执行器的职责就是传入命令给接收器，并且调用我们的业务逻辑。

    /**
     + A generic execute function
     + Takes a receiver and a command
     **/
    export default function execute(receiver, command) {
      return receiver[command.action] && receiver[command.action](...command.params);
    }

> Now we can execute commands from anywhere at any time!

现在我们无论在何时何地都可以执行这些命令了。

### **Make things happen** | 让奇迹发生

    import execute from 'executor.js';
    import TeslaSalesControl from 'receiver.js';
        
    // Arrange a viewing
    execute(TeslaSalesControl, {
      action: "arrangeViewing",
      param: ["Model S", "123"]
    });

    // Request Info
    execute(TeslaSalesControl, {
      action: "requestInfo",
      param: ["Model S Battery", "123342"]
    });

    // Buy a Car!
    execute(TeslaSalesControl, {
      action: "buyVehicle",
      param: ["Tesla 3", "23243425"]
    });

> Thats it, now how does this compare to Redux! In Redux:

就是这样，现在让我们来对比一下 Redux！在 Redux 中：

## The Store = The Receiver | Store 即接收器

> The Store is instantiated with “**reducers**”, descriptions on how the Store change. These reducers are pure functions that when called return a new state rather than causing mutations in place. This allows you to have highly predictable and testable code.

Store 会根据 “**reducers**” 进行初始化，描述 Store 是如何变化的。这些 reducers 都是一些纯函数，每当被调用的时候都会返回一个新的 state，而不会导致莫名其妙地发生变化。这使得我们的代码具有高度的可预测性以及可测试性。

    import { combineReducers } = 'redux';

    function arrangeViewing(state, action) {
      switch(action.type) {
        case "ARRANGE_VIEWING":
          const { model, id } = action.data;
          return `${model} and ${id}`
        default:
          return ""
      }
    }

    function requestInfo(state, action) {
      switch(action.type) {
        case "REQUEST_INFO":
          const { model, id } = action.data;
          return `${model} and ${id}`
        default:
          return ""
      }
    }

    function buyVehicle(state, action) {
      switch(action.type) {
        case "BUY_VEHICLE":
          const { model, id } = action.data;
          return `${model} and ${id}`
        default:
          return false
      }
    }

    const rootReducer = combineReducers({
      arrangeViewing,
      requestInfo,
      buyVehicle
    });

    export default rootReducer;

.

    import { applyMiddleware, createStore } from 'redux';
    import createLogger from 'redux-logger';
    import ReduxThunk from 'redux-thunk';
    import rootReducer from '../imports/client/reducers/rootReducer';

    // create a logger

    const logger = createLogger();
    const middleware = [ReduxThunk, logger];

    const Store = createStore(rootReducer, {}, applyMiddleware(...middleware));
    export default Store;

## The Action = The Command | Action 即命令

> The action object represents the description of the command and parameters it needs to execute our state change.

Action 对象则代表着对命令的描述，以及它在执行 state 更改时所需要的参数。

    const sampleActionObject = {
      type: "BUY_CAR",
      data: {
        model: "TESLA",
        id: "1234"
      }
    }

## Dispatch = Executor | Dispatch 即执行器

> The difference between vanilla Flux and Redux, is the dispatch is a method of the store. The Store can dispatch actions to change the state of our application.

普通的 Flux 和 Redux 之间的区别，就在于 dispatch 属于 store 当中的一个方法。Store 可以直接分派 action 从而改变我们应用程序的 state。

    import Store from 'store';

    Store.dispatch({
      type: "ARRANGE_VIEWING",
      data: {
        model: "Model S",
        id: "123"
      }
    });

    Store.dispatch({
      type: "REQUEST_INFO",
      data: {
        model: "Model S Battery",
        id: "123342"
      }
    });

    Store.dispatch({
      type: "BUY_VEHICLE",
      data: {
        model: "TESLA 3",
        id: "23243425"
      }
    });

> As you can see, pretty similar right!? Knowing the Command Pattern makes learning Redux a lot easier! Trust me!

如你所见，非常相似是不是！？弄懂了命令模式可以让 Redux 的学习变得容易很多！相信我！

> Design Patterns in general help you stay rooted in your application architecture!

总之，设计模式会帮助你掌握应用程序架构的本质！

![](https://cdn-images-1.medium.com/max/1600/1*kvdXC-IpoTjaXeuHcaVGuQ.png)