---
layout: post
title: 【译】整洁代码：JavaScript 当中的面向对象设计原则（S.O.L.I.D）
category: [翻译]
tags: [JavaScript, 前端, 面向对象, 设计原则, 类型系统]
published: true

---

原文地址：<https://github.com/ryanmcdermott/clean-code-javascript#classes>

> GitHub 总之有很多 Code Example 案例的仓库来教你如何正确写出好代码，诸多 Markdown 写手以 BAD/GOOD 两种代码作为示范，辅以一些叙述和注释作为说明，清晰易懂。我就准备来翻译最近看到的 JavaScript 整洁代码中 Classes 设计原则这一段，进一步加深对面向对象设计原则的理解，而不只是 Java 世界。

## [JavaScript **Classes**](https://github.com/ryanmcdermott/clean-code-javascript#classes)

### [Single Responsibility Principle (SRP)](https://github.com/ryanmcdermott/clean-code-javascript#single-responsibility-principle-srp) | 单一职责原则

> As stated in Clean Code, "There should never be more than one reason for a class to change". It's tempting to jam-pack a class with a lot of functionality, like when you can only take one suitcase on your flight. The issue with this is that your class won't be conceptually cohesive and it will give it many reasons to change. Minimizing the amount of times you need to change a class is important. It's important because if too much functionality is in one class and you modify a piece of it, it can be difficult to understand how that will affect other dependent modules in your codebase. 

如《整洁代码》中所述，「不应该有一个以上的理由去修改某个类」。我们往往会倾向于往一个类里面塞入过多的功能，类似于你只能往航班上携带唯一一个行李箱。这里的问题在于，这个类从概念上来说不再是内聚的，从而导致了将来可能有很多理由会去修改它。尽可能少地去修改某个类是非常重要的，因为如果在一个类里面包含了过多的功能，那么当你修改其中的某一部分，就会很难理解你所做的修改将如何影响代码库当中其他相互依赖的模块。

**Bad:**

```js
class UserSettings {
  constructor(user) {
    this.user = user;
  }

  changeSettings(settings) {
    if (this.verifyCredentials(user)) {
      // ...
    }
  }

  verifyCredentials(user) {
    // ...
  }
}
```

**Good**:

```js
class UserAuth {
  constructor(user) {
    this.user = user;
  }

  verifyCredentials() {
    // ...
  }
}

class UserSettings {
  constructor(user) {
    this.user = user;
    this.auth = new UserAuth(user)
  }

  changeSettings(settings) {
    if (this.auth.verifyCredentials()) {
      // ...
    }
  }
}
```

### [Open/Closed Principle (OCP)](https://github.com/ryanmcdermott/clean-code-javascript#openclosed-principle-ocp) | 开放封闭原则

> As stated by Bertrand Meyer, "software entities (classes, modules, functions,
etc.) should be open for extension, but closed for modification." What does that mean though? This principle basically states that you should allow users to extend the functionality of your module without having to open up the `.js` source code file and manually manipulate it.

正如 Bertrand Meyer 所言，「软件实体（类、模块、函数等等）应该对于扩展是开放的，而对于修改是封闭的」。换句话说，该原则的基本意思就是你应该让用户在扩展你的模块功能时，没有必要去打开 `.js` 源文件并且手动修改源代码。

**Bad:**

```js
class AjaxRequester {
  constructor() {
    // What if we wanted another HTTP Method, like DELETE? We would have to
    // open this file up and modify this and put it in manually.
    this.HTTP_METHODS = ['POST', 'PUT', 'GET'];
  }

  get(url) {
    // ...
  }

}
```

**Good**:

```js
class AjaxRequester {
  constructor() {
    this.HTTP_METHODS = ['POST', 'PUT', 'GET'];
  }

  get(url) {
    // ...
  }

  addHTTPMethod(method) {
    this.HTTP_METHODS.push(method);
  }
}
```

### [Liskov Substitution Principle (LSP)](https://github.com/ryanmcdermott/clean-code-javascript#liskov-substitution-principle-lsp) | 里氏替换原则

> This is a scary term for a very simple concept. It's formally defined as "If S is a subtype of T, then objects of type T may be replaced with objects of type S (i.e., objects of type S may substitute objects of type T) without altering any of the desirable properties of that program (correctness, task performed, etc.)." That's an even scarier definition.

这个原则听起来有点儿拗口但是概念非常简单。正式的定义就是「如果 S 为 T 的子类型，那么 T 类型的对象可以被 S 类型的对象所替换（也就是说类型 S 的对象可以替换类型 T 的对象），而不会改变该程序的任何期望的属性（正确性，执行的任务等）」。不得不说这是一个更拗口的定义。

> The best explanation for this is if you have a parent class and a child class, then the base class and child class can be used interchangeably without getting incorrect results. This might still be confusing, so let's take a look at the classic Square-Rectangle example. Mathematically, a square is a rectangle, but if you model it using the "is-a" relationship via inheritance, you quickly get into trouble.

最好的一种解释就是，我们所创建的父类与其子类应当可交换地使用而不会引起异常。可能这还是会使人感到困惑，所以让我们来看一个经典的 Square-Rectangle 例子。从数学上来说，一个 Square 也是 一个 Rectangle，但是如果你通过继承使用 “is-a” 的关系对其进行建模，你很快就会遇到问题。

**Bad:**

```js
class Rectangle {
  constructor() {
    this.width=0;
    this.height = 0;
  }

  setColor(color) {
    // ...
  }

  render(area) {
    // ...
  }

  setWidth(width) {
    this.width = width;
  }

  setHeight(height) {
    this.height = height;
  }

  getArea() {
    return this.width \* this.height;
  }
}

class Square extends Rectangle {
  constructor() {
    super();
  }

  setWidth(width) {
    this.width = width;
    this.height = width;
  }

  setHeight(height) {
    this.width = height;
    this.height = height;
  }
}

function renderLargeRectangles(rectangles) {
  rectangles.forEach((rectangle) => {
    rectangle.setWidth(4);
    rectangle.setHeight(5);
    let area = rectangle.getArea(); // BAD: Will return 25 for Square. Should be 20.
    rectangle.render(area);
  })
}

let rectangles = [new Rectangle(), new Rectangle(), new Square()];
renderLargeRectangles(rectangles);
```

**Good**:

```js
class Shape {
  constructor() {}

  setColor(color) {
    // ...
  }

  render(area) {
    // ...
  }
}

class Rectangle extends Shape {
  constructor() {
    super();
    this.width = 0;
    this.height = 0;
  }

  setWidth(width) {
    this.width = width;
  }

  setHeight(height) {
    this.height = height;
  }

  getArea() {
    return this.width \* this.height;
  }
}

class Square extends Shape {
  constructor() {
    super();
    this.length = 0;
  }

  setLength(length) {
    this.length = length;
  }

  getArea() {
    return this.length \* this.length;
  }
}

function renderLargeShapes(shapes) {
  shapes.forEach((shape) => {
    switch (shape.constructor.name) {
      case 'Square':
        shape.setLength(5);
      case 'Rectangle':
        shape.setWidth(4);
        shape.setHeight(5);
    }

    let area = shape.getArea();
    shape.render(area);
  })
}

let shapes = [new Rectangle(), new Rectangle(), new Square()];
renderLargeShapes(shapes);
```

### [Interface Segregation Principle (ISP)](https://github.com/ryanmcdermott/clean-code-javascript#interface-segregation-principle-isp) | 接口隔离原则

> JavaScript doesn't have interfaces so this principle doesn't apply as strictly as others. However, it's important and relevant even with JavaScript's lack of type system.

JavaScript 语言本身并不包含对于接口语法的支持，因此也无法像其他语言那样达到严格限制的程度。不过鉴于 JavaScript 本身类型系统的缺失，遵循接口隔离原则还是非常重要的。

> ISP states that "Clients should not be forced to depend upon interfaces that
they do not use." Interfaces are implicit contracts in JavaScript because of
duck typing.

ISP 的表述是「不应该强制客户端去依赖于他们不需要的接口」，由于 JavaScript 的「鸭子类型」，JavaScript 当中的接口只是一种隐性的契约而已。

> A good example to look at that demonstrates this principle in JavaScript is for classes that require large settings objects. Not requiring clients to setup huge amounts of options is beneficial, because most of the time they won't need all of the settings. Making them optional helps prevent having a "fat interface". 

这一点在 JavaScript 中较为典型的例子就是那些需要大量配置信息的类。其实使用者并不需要去关心每一个配置项，不强制他们设置大量的选项能够节省大量的时间，保持设置选项可选能够有助于防止「胖接口」。

**Bad:**

```js
class DOMTraverser {
  constructor(settings) {
    this.settings = settings;
    this.setup();
  }

  setup() {
    this.rootNode = this.settings.rootNode;
    this.animationModule.setup();
  }

  traverse() {
    // ...
  }
}

let $ = new DOMTraverser({
  rootNode: document.getElementsByTagName('body'),
  animationModule: function() {} // Most of the time, we won't need to animate when traversing.
  // ...
});
```

**Good**:

```js
class DOMTraverser {
  constructor(settings) {
    this.settings = settings;
    this.options = settings.options;
    this.setup();
  }

  setup() {
    this.rootNode = this.settings.rootNode;
    this.setupOptions();
  }

  setupOptions() {
    if (this.options.animationModule) {
      // ...
    }
  }

  traverse() {
    // ...
  }
}

let $ = new DOMTraverser({
  rootNode: document.getElementsByTagName('body'),
  options: {  
    animationModule: function() {}
  }
});
```

### [Dependency Inversion Principle (DIP)](https://github.com/ryanmcdermott/clean-code-javascript#dependency-inversion-principle-dip) | 依赖反转原则

> This principle states two essential things:
> 1. High-level modules should not depend on low-level modules. Both should depend on abstractions.
> 2. Abstractions should not depend upon details. Details should depend on abstractions.

这个原则主要阐述了两件重要的事情：

1. 上层模块不需要依赖下层模块，两者依赖于抽象。
2. 抽象不应该依赖于细节。细节应当依赖于抽象。

> This can be hard to understand at first, but if you've worked with Angular.js, you've seen an implementation of this principle in the form of Dependency Injection (DI). While they are not identical concepts, DIP keeps high-level modules from knowing the details of its low-level modules and setting them up. It can accomplish this through DI. A huge benefit of this is that it reduces the coupling between modules. Coupling is a very bad development pattern because it makes your code hard to refactor.

最开始可能很难理解，但是如果你曾经用过 Angular.js，你就已经见过这个原则的一种实现了，依赖注入（DI）就是其中一种形式。但是他们不是完全相同的概念，DIP 可以避免上层模块知道你的下层模块的实现细节和具体设置，这可以通过 DI 来达成目的。一个显著的好处就是减少了模块之间的耦合，耦合是非常坏的一种开发模式，因为它会使得你的代码难以重构。

> As stated previously, JavaScript doesn't have interfaces so the abstractions
that are depended upon are implicit contracts. That is to say, the methods and properties that an object/class exposes to another object/class. In the example below, the implicit contract is that any Request module for an `InventoryTracker` will have a `requestItems` method.

就像之前所提到的，JavaScript 语言本身没有接口，从而抽象只能依赖于隐性的契约。也就是指，一个对象/类所暴露给另一个对象/类的方法和属性。下面这个例子当中的隐性契约就是，`InventoryTracker` 所依赖的任意一个 Request 模块都要有一个 `requestItems` 方法。

**Bad:**

```js
class InventoryTracker {
  constructor(items) {
    this.items = items;

    // BAD: We have created a dependency on a specific request implementation.
    // We should just have requestItems depend on a request method: `request`
    this.requester = new InventoryRequester();
  }

  requestItems() {
    this.items.forEach((item) => {
      this.requester.requestItem(item);
    });
  }
}

class InventoryRequester {
  constructor() {
    this.REQ_METHODS = ['HTTP'];
  }

  requestItem(item) {
    // ...
  }
}

let inventoryTracker = new InventoryTracker(['apples', 'bananas']);
inventoryTracker.requestItems();
```

**Good**:

```js
class InventoryTracker {
  constructor(items, requester) {
    this.items = items;
    this.requester = requester;
  }

  requestItems() {
    this.items.forEach((item) => {
      this.requester.requestItem(item);
    });
  }
}

class InventoryRequesterV1 {
  constructor() {
    this.REQ_METHODS = ['HTTP'];
  }

  requestItem(item) {
    // ...
  }
}

class InventoryRequesterV2 {
  constructor() {
    this.REQ_METHODS = ['WS'];
  }

  requestItem(item) {
    // ...
  }
}

// By constructing our dependencies externally and injecting them, we can easily
// substitute our request module for a fancy new one that uses WebSockets.
let inventoryTracker = new InventoryTracker(['apples', 'bananas'], new InventoryRequesterV2());
inventoryTracker.requestItems();
```
