---
layout: post
title: 「技术雷达」之使用 Enzyme 测试 React（Native）组件
categories: [前端]
tags: [React, ReactNaitve, Enzyme, Testing, TechRadar]
published: True
---

## 组件化与 UI 测试

在组件化出现之前，我们不谈 UI 的单元测试，哪怕是对于 UI 页面的测试来说都是一件非常困难的事情。其实**组件化并不全是为了复用，很多情况下也恰恰是为了分治**，从而我们可以分组件对 UI 页面进行开发，然后分别对其进行单元测试。

特别是当浏览器中的 Web 应用越来越庞大的时候，借鉴于在后端将大型单体应用拆分成微服务架构的最佳实践一样，前端应用也可以被拆分成不同的页面和特性。每个特性由一个单独的团队从端到端对其负责，它允许团队规模化地交付那些能够独立部署和维护的服务，在最新一期的技术雷达当中这种方式称之为**微前端**，微前端的目标就是允许 Web 应用的特性之间彼此独立，每个特性可以独立地开发、测试和部署。

React.js 作为前端框架的后起之秀，却在 2015 年携着虚拟 DOM，组件化，单向数据流等利器，给前端 UI 构建掀起了一波声势浩大的函数式新潮流。虽然说组件化不是 React 最先提出来的，但却是 React 使得组件化在前端世界里发扬光大的，而现在几乎所有的所谓现代化 UI 框架比如 Angular 或者 Vue 都已经将组件化作为框架的立足之本。

![](//o7mw3gkkh.qnssl.com//images/2016/1481267000925.png)

React 已经让 UI 测试变得容易很多，React 组件都可以被简化为这样一个表达式，即 `UI = f(data)`，这个纯函数返回的只是一个描述 UI 组件应该是什么样子的虚拟 DOM，本质上就是一个树形的数据结构。给这个纯函数输入一些应用程序的状态，就会得到相应的 UI 描述的输出，这个过程不会去直接操作实际的 UI 元素，也不会产生所谓的副作用。

## React 组件树的测试

按理来说按照纯函数这样的思路，React 组件的测试应该很简单的说。但与此同时对于（渲染出 UI 的）组件树进行测试依然存在一个问题，从下图中可以看出，越处于上层的组件，其复杂度必然会随之提高。对于最底层的子组件来说，我们可以很容易得将其进行渲染并测试其逻辑的正确与否，但对于较上层的父组件来说，通常来说就需要对其所包含的所有子组件都进行预先渲染，甚至于最上面的组件需要渲染出整个 UI 页面的真实 DOM 节点才能对其进行测试，这显然是不可取的。

![Components-Tree](//o7mw3gkkh.qnssl.com//images/2016/1481119659338.png)

> Shallow rendering lets you render a component "one level deep" and assert facts about what its render method returns, without worrying about the behavior of child components, which are not instantiated or rendered. This does not require a DOM.

浅渲染（Shallow Rendering）解决了这个问题，也就是说在我们针对某个上层组件进行测试时，可以不用渲染它的子组件，所以就不用再担心子组件的表现和行为，这样就可以只对特定组件的逻辑及其渲染输出进行测试了。Facebook 官方提供了 `react-addons-test-utils` 可以让我们使用浅渲染这个特性，用于测试虚拟 DOM 对象，即 `React.Component` 的实例。

## 使用 Enzyme 简化测试代码

我们常常会提到，测试代码对于复杂代码库的可维护性至关重要，但是**测试的代码本身的易于理解和编写，以及可读性和可维护性也同等重要。**

> Enzyme is a JavaScript Testing utility for React that makes it easier to assert, manipulate, and traverse your React Components' output.

而 Enzyme 则来自于活跃在 JavaScript 开源社区的 Airbnb 公司，是对官方测试工具库（`react-addons-test-utils`）的封装，它模拟了 jQuery 的 API，非常直观并且易于使用和学习，提供了一些与众不同的接口和几个方法来减少测试的样板代码，方便你判断、操纵和遍历 React Components 的输出，并且减少了测试代码和实现代码之间的耦合。Enzyme 理论上应该与所有 TestRunner 和断言库相兼容，已经集成了多种测试类库，比如 Jest，Mocha & Chai，或者 Jasmine，不过这些不是我们今天的重点。

对比一下两者 `facebook/react-addons-test-utils` vs `airbnb/enzyme` 的 API 就一目了然，立见分明：

![](//o7mw3gkkh.qnssl.com//images/2016/1481121353201.png)

## Enzyme 的三种渲染方法

### **`shallow(node[, options]) => ShallowWrapper`**

shallow 方法就是对官方的 Shallow Rendering 的封装，浅渲染在将一个组件作为一个单元进行测试的时候非常有用，可以确保你的测试不会去间接断言子组件的行为。shallow 方法只会渲染出组件的第一层 DOM 结构，其嵌套的子组件不会被渲染出来，从而使得渲染的效率更高，单元测试的速度也会更快。

```javascript
import { shallow } from 'enzyme'

describe('Enzyme Shallow', () => {
  it('App should have three <Todo /> components', () => {
    const app = shallow(<App />)
    expect(app.find('Todo')).to.have.length(3)
  })
}
```

### **`mount(node[, options]) => ReactWrapper`**

mount 方法则会将 React 组件渲染为真实的 DOM 节点，特别是在你依赖真实的 DOM 结构必须存在的情况下，比如说按钮的点击事件。完全的 DOM 渲染需要在全局范围内提供完整的 DOM API， 这也就意味着它必须在至少“看起来像”浏览器环境的环境中运行，如果不想在浏览器中运行测试，推荐使用 mount 的方法是依赖于一个名为 jsdom 的库，它本质上是一个完全在 JavaScript 中实现的 headless 浏览器。

```javascript
import { mount } from 'enzyme'

describe('Enzyme Mount', () => {
  it('should delete Todo when click button', () => {
    const app = mount(<App />)
    const todoLength = app.find('li').length
    app.find('button.delete').at(0).simulate('click')
    expect(app.find('li').length).to.equal(todoLength - 1)
  })
})
```

### **`render(node[, options]) => CheerioWrapper`**

render 方法则会将 React 组件渲染成静态的 HTML 字符串，返回的是一个 Cheerio 实例对象，采用的是一个第三方的 HTML 解析库 Cheerio，官方的解释是「我们相信 Cheerio 可以非常好地处理 HTML 的解析和遍历，再重复造轮子只能算是一种损失」。这个 CheerioWrapper 可以用于分析最终结果的 HTML 代码结构，它的 API 跟 shallow 和 mount 方法的 API 都保持基本一致。

```javascript
import { render } from 'enzyme'

describe('Enzyme Render', () => {
  it('Todo item should not have todo-done class', () => {
    const app = render(<App />)
    expect(app.find('.todo-done').length).to.equal(0)
    expect(app.contains(<div className="todo" />)).to.equal(true)
  })
})
```

## Enzyme 的 API 方法

### `find()` 方法与选择器

从前面的示例代码中可以看到，无论哪种渲染方式所返回的 wrapper 都有一个 `.find()` 方法，它接受一个 selector 参数，然后返回一个类型相同的 wrapper 对象，里面包含了所有符合条件的子组件。在这个对象的基础上，`at` 方法则可以返回指定位置的子组件，`simulate` 方法可以在这个组件上模拟触发某种行为。

Enzyme 中的 Selectors 即选择器类似于 CSS 选择器，但是只支持非常简单的 CSS 选择器，如果需要支持复杂的 CSS 选择器，就需要引入 `react-dom` 模块的 `findDOMNode` 方法，而这是官方的 `TestUtils` 本身都不提供的方式。 

```javascript
/* CSS Selector */
wrapper.find('.foo') //class syntax
wrapper.find('input') //tag syntax
wrapper.find('#foo') //id syntax 
wrapper.find('[htmlFor="foo"]') //prop syntax
```

Selectors 也可以是许多其他的东西，以便于在 Enzyme 的 wrapper 中可以轻松地指定想要查找的节点，在下面的示例中，我们可以通过 React 组件构造函数的引用找到该组件，也可以基于 React 的 `displayName` 来查找组件，如果一个组件存在于渲染树中，其中设置了 `displayName` 并且它的第一个字符为大写字母，就能通过字符串找到它，与此同时也可以基于 React 组件属性的子集来查找组件和节点。

```javascript
/* Component Constructor */
wrapper.find(ChildrenComponent)
myComponent.displayName = 'ChildrenComponent'
wrapper.find('ChildrenComponent')

/* Object Property Selector */
const wrapper = mount(
  <div>
    <span foo={3} bar={false} title="baz" />
  </div>
)

wrapper.find({ foo: 3 })
wrapper.find({ bar: false })
wrapper.find({ title: 'baz'})
```

### 测试组件的交互行为

我们不但可以通过 find 方法查找 DOM 元素，还可以通过 `simulate` 方法在组件上模拟触发某个 DOM 事件，比如 Click，Change 等等。对于浅渲染来说，事件模拟并不会像真实环境中所预期的那样进行传播，因此我们必须在一个已经设置好了事件处理方法的实际节点上才能够调用，实际上 `.simulate()` 方法将会根据模拟的事件触发这个组件的 prop。例如，`.simulate('click')` 实际上会获取 onClick prop 并调用它。

Sinon 则是一个可以用来 Mock 和 Stub 数据代码的第三方测试工具库，当我们需要检查一个组件当中某个特定的函数是否被调用时，我们可以使用 `sinon.spy()` 方法监视所传入该组件作为 prop 的 onButtonClick 方法，然后再通过 wrapper 的 simulate 方法模拟一个 Click 事件，最终验证这个被 spy 的 onButtonClick 函数是否被调用。

```javascript
it('simulates click events', () => {  
  const onButtonClick = sinon.spy()
  const wrapper = shallow(
    <Foo onButtonClick={onButtonClick} />
  )
  wrapper.find('button').simulate('click')
  expect(onButtonClick.calledOnce).to.be.true
})
```

##  如何测试 React Native？

前面我们所谈论的都是如何测试使用 react-dom 所构建的 React 组件，即最终渲染的结果是浏览器当中的 DOM 结构，但对于 React Native 来说，JavaScript 代码最终会被编译并用于调用 iOS 或 Android 上的 Native 代码，因此无法再使用基于 DOM 的测试工具了。与此同时，React Native 还有特别多的 Mobile 环境依赖，所以在没有真实设备的情况下很难对其运行环境进行模拟，特别是当你希望在持续集成服务器（如 Jenkins、Travis CI）运行单元测试的时候。

事实上，我们可以通过欺骗 React Native 让它返回常规的 React 组件而不是 Native 组件，然后就又能愉快地使用传统的 JavaScript 测试库来单独测试 React Native 组件逻辑。最基本的 mock 示例代码如下：

```javascript
const mockComponent = (type) => {
  return React.createClass({
    displayName: type,
    propTypes: {
      children: React.PropTypes.node
    },
    render() {
      return <div {...this.props}>{this.props.children}</div>
    }
  })
}

RN.View = mockComponent("View")
RN.Text = mockComponent("Text")
RN.Image = mockComponent("Image")
```

Enzyme 推荐在测试环境中使用 [react-native-mock](https://github.com/RealOrangeOne/react-native-mock) 这个辅助库，这是一个使用纯 JavaScript 将全部的 React Native 组件进行 mock 的第三方库，只需要导入这个库就可以对 React Native 组件进行渲染和测试。

## 总结

> **技术雷达**：我们非常享受Enzyme为React.js应用提供的快速组件级UI测试功能。与许多其他基于快照的测试框架不同，Enzyme允许开发者在不进行设备渲染的情况下做测试，从而实现速度更快，粒度更小的测试。在开发React应用时，我们经常需要做大量的功能测试，而Enzyme可以在大规模地减少功能测试数量上做出贡献。

![TechRadar](//o7mw3gkkh.qnssl.com//images/2016/1481128632569.png)

