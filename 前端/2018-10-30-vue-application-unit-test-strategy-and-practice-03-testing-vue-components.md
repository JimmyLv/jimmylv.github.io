---
layout: post
title: 'Vue 应用单元测试的策略与实践 03 - Vue 组件单元测试'
categories: [前端]
tags: [Tutorial, UnitTest, ES6, Vue, Jest, Agile, TDD]
published: True
---

## 本文的目标

2.1 在 Vue 应用的单元测试中，对不同 UI 组件的单元测试有何不同？颗粒度该细到什么样的程度？

```md
// Given
一个有基本的 UT 知识但没写过 Vue 测试的新人 🚶
// When
当他 🚶 阅读和练习本文的 Vue 单元测试的部分
// Then
当然，他能够学会 Vue 组件在测试当中的几种渲染方式
他能够学会 UI 组件的分类，特别是交互行为的测试方式
```

## 组件化与 UI 测试

在组件化出现之前，我们都压根不谈 UI 的**单元**测试，哪怕是对于 UI 页面层级的测试来说都是一件非常困难的事情。其实**组件化并不全是为了复用，很多情况下也恰恰是为了分治**，从而我们可以分组件对 UI 页面进行开发，然后分别对其进行单元测试。

![](https://raw.sevencdn.com/JimmyLv/images/master/2018/20181030220153.png)

前端组件化已经让 UI 测试变得容易很多，每个组件都可以被简化为这样一个表达式，即 `UI = f(data)`，这个纯函数返回的只是一个描述 UI 组件应该是什么样子的虚拟 DOM，本质上就是一个树形的数据结构。给这个纯函数输入一些应用程序的状态，就会得到相应的 UI 描述的输出，这个过程不会去直接操作实际的 UI 元素，也不会产生所谓的副作用。

### Vue 组件树的测试

按理来说按照纯函数这样的思路，Vue 组件的测试应该很简单的说。但与此同时，对 UI 渲染的组件树进行测试依然存在一个问题，从下图中可以看出，越处于上层的组件，其复杂度必然会随之提高。对于最底层的子组件来说，我们可以很容易得将其进行渲染并测试其逻辑的正确与否，但对于较上层的父组件来说，通常来说就需要对其所包含的所有子组件都进行预先渲染，甚至于最上面的组件需要渲染出整个 UI 页面的真实 DOM 节点才能对其进行测试，这显然是不可取的。

![Components-Tree](https://raw.sevencdn.com/JimmyLv/images/master/2018/20181030211115.png)

在单元测试中，通常我们希望将重点放在作为独立单元进行测试的组件上，并避免间接断言其子组件的行为。此外，对于包含许多子组件的组件，整个 render 树会变得非常之大，而反复 render 所有的子组件可能会减慢单元测试的速度。

而根据 Mike Cohn 的测试金字塔中所提到的两件事：

- 编写不同粒度的测试
- 层次越高，你写的测试应该越少

> 为了维持金字塔形状，一个健康、快速、可维护的测试组合应该是这样的：写许多小而快的单元测试。适当写一些更粗粒度的测试，写很少高层次的端到端测试。注意不要让你的测试变成冰淇淋那样子，这对维护来说将是一个噩梦，并且跑一遍也需要太多时间。（via [测试金字塔实战 – ThoughtWorks 洞见](https://insights.thoughtworks.cn/practical-test-pyramid/)）

![测试金字塔](https://raw.sevencdn.com/JimmyLv/images/master/2018/20181030211424.png)

对于 Vue 组件树来说，浅渲染（[Shallow Rendering](https://vue-test-utils.vuejs.org/guides/#shallow-rendering)）解决了这个问题，也就是说在我们针对某个上层组件进行测试时，可以不用渲染它的子组件，所以就不用再担心子组件的表现和行为，这样就可以只对特定组件的逻辑及其渲染输出进行测试了。Vue 官方提供了 `@vue/test-utils` 可以让我们使用浅渲染这个特性，用于测试虚拟 DOM 对象，即 `Vue.component` 的实例。

```js
import { shallowMount } from '@vue/test-utils'

const wrapper = shallowMount(Component)
wrapper.vm // the mounted Vue instance
```

## Vue 组件的渲染方式

### 浅渲染 **`shallowMount(component[, options]) => Wrapper`**

浅渲染在将一个组件作为一个单元进行测试的时候非常有用，可以确保你的测试不会去间接断言子组件的行为。`shallowMount` 方法就是 Shallow Rendering 的封装，`shallowMount` 跟 `mount` 类似返回 `mounted` 和 `rendered` Vue 组件的 Wrapper，但只会渲染出组件的第一层 DOM 结构，其嵌套的子组件不会被渲染出来，从而使得渲染的效率更高，单元测试的速度也会更快。

```javascript
import { shallowMount } from '@vue/test-utils'

describe('Vue Component shallowMount', () => {
  it('should have three <todo /> components', () => {
    const wrapper = shallowMount(App)
    expect(wrapper.find({ name: 'Todo' })).toHaveLength(3)
  })
}
```

### 全量渲染 **`mount(component[, options]) => Wrapper`**

`mount` 方法则会将 Vue 组件和所有子组件渲染为真实的 DOM 节点，特别是在你依赖真实的 DOM 结构必须存在的情况下，比如说按钮的点击事件。完全的 DOM 渲染需要在全局范围内提供完整的 DOM API， 这也就意味着 Vue Test Utils 依赖于浏览器环境。

从技术上讲，你可以在真实的浏览器中运行，但由于在不同平台上启动真实浏览器的复杂性，更建议使用 JSDOM 在虚拟浏览器环境中运行 Node 中的测试。推荐使用 `mount` 的方法是依赖于一个名为 `jsdom`的库，它本质上是一个完全在 JavaScript 中实现的 headless 浏览器。

```javascript
import { mount } from '@vue/test-utils'

describe('Vue Component Mount', () => {
  it('should delete Todo when click button', () => {
    const wrapper = mount(App)
    const todoLength = wrapper.find('li').length
    wrapper.find('button.delete').at(0).trigger('click')
    expect(wrapper.find('li').length).toEqual(todoLength - 1)
  })
})
```

### 静态渲染 **`render(component[, options]) => CheerioWrapper`**

`render` 方法则会将 Vue 组件渲染成静态的 HTML 字符串，而返回的则是一个 Cheerio 实例对象，采用的是一个第三方的 HTML 解析库 Cheerio，这是一个类 jQuery 的库，可以在 Node.js 中遍历 DOM。渲染后所返回的 CheerioWrapper 可以用于分析最终结果的 HTML 代码结构，好处是它的 API 跟 `shallowMount` 和 `mount` 方法的 API 都基本保持一致。

```javascript
import { render } from '@vue/test-utils'

describe('Vue Component Render', () => {
  it('should not have .todo-done class', () => {
    const wrapper = render(App)
    expect(wrapper.find('.todo-done').length).toEqual(0)
    expect(wrapper.text()).toContain('<div class="todo"></div>')
  })
})
```

### 纯字符串渲染 **`renderToString(component[, options]) => string`**

`renderToString` 很简单，顾名思义就是把一个组件渲染成对应的 HTML 字符串，在此不再赘述。

```javascript
import { renderedString } from '@vue/test-utils'

describe('Vue Component renderedString', () => {
  it('should have .todo class', () => {
    const renderedString = renderToString(App)
    expect(renderedString).toContain('<div class="todo"></div>')
  })
})
```

## 实例 Wrapper `find()` 方法与选择器

![](https://raw.sevencdn.com/JimmyLv/images/master/2018/20181030214617.png)

从前面的示例代码中可以看到，无论哪种渲染方式所返回的 wrapper 都有一个 `.find()` 方法，它接受一个 selector 参数，然后返回一个对应的 wrapper 对象。而 `.findAll()` 则会返回一个类型相同的 wrapper 对象数组，里面包含了所有符合条件的子组件。在这个对象数组的基础上，`at` 方法则可以返回指定位置的子组件，`trigger` 方法用于在组件之上模拟触发某种行为。

`@vue/test-utils` 中的 Selectors 即选择器，既可以是 CSS 选择器（也支持比较复杂的关系选择器组合），也可以是 Vue 组件 或是一个 option 对象，以便于在 wrapper 对象中可以轻松地指定想要查找的节点。

```javascript
/* CSS Selector */
wrapper.find('.foo') //class syntax
wrapper.find('input') //tag syntax
wrapper.find('#foo') //id syntax
wrapper.find('[foo="bar"]') //attribute syntax
wrapper.find('div:first-of-type') //pseudo selectors
```

在下面的示例中，我们可以通过 Vue 组件构造函数的引用找到该组件，与此同时也可以基于 Vue 组件属性的子集来查找组件和节点，或者通过根据 \$ref 选择相应元素。

```javascript
/* Component Constructor */
import foo from './foo.vue'

const wrapper = shallowMount(app)
expect(wrapper.find(foo).is(foo)).toBe(true)

/* Find Option Object */
const wrapper = appWrapper.find({ name: 'my-button' })
wrapper.trigger('click')

/* Find by refs */
const wrapper = appWrapper.find({ ref: 'myButton' })
wrapper.trigger('click')
```

## UI 组件交互行为的测试

![](https://raw.sevencdn.com/JimmyLv/images/master/2018/20181030212827.png)

我们不但可以通过 `find` 方法查找 DOM 元素，还可以通过 `trigger` 方法在组件上模拟触发某个 DOM 事件，比如 Click，Change 等等。对于浅渲染来说，事件模拟并不会像真实环境中所预期的那样进行传播，因此我们必须在一个已经设置好了事件处理方法的实际节点上才能够调用，实际上 `.trigger()` 方法将会根据模拟的事件触发这个组件的 prop。例如，`.trigger('click')` 实际上会获取 对应的 `clickHandler` propsData 并调用它。

```javascript
it('should trigger event when click button', () => {
  const clickHandler = jest.fn()
  const wrapper = shallowMount(Foo, {
    propsData: { clickHandler },
  })
  wrapper.trigger('click')
  expect(clickHandler).toHaveBeenCalled()
})
```

### 关于 `nextTick` 怎么办？

Vue 会异步的将未生效的 DOM 更新批量应用，以避免因数据反复突变而导致的无谓的重新渲染。这也是为什么在实践过程中我们经常在触发状态改变后用 `Vue.nextTick` 来等待 Vue 把实际的 DOM 更新做完的原因。

为了简化用法，Vue Test Utils 同步应用了所有的更新，所以你不需要在测试中使用 `Vue.nextTick` 来等待 DOM 更新。

_注意：当你需要为诸如异步回调或 Promise 解析等操作显性改进为事件循环的时候，`nextTick` 仍然是必要的。_

## 总结一下

Vue 组件的单元测试是前端 UI 测试组合的基石，单元测试保证了代码库里的每个组件（被测试的主体）都能按照预期那样工作，它的数量在测试组合中应该远远多于其他类型的测试。其实呢，也不要太拘泥于测试金字塔中各层次的名字，UI 测试显然不必位于金字塔的最高层，你也完全可以用 Cypress、Nightwatch 这样的 E2E 框架对 UI 进行单元测试，这个的话我们就留到后面再聊。

## 未完待续……

**## 单元测试基础**

- [x] ### 单元测试与自动化的意义
- [x] ### 为什么选择 Jest
- [x] ### Jest 的基本用法
- [x] ### 该如何测试异步代码？

**## Vue 单元测试**

- [x] ### Vue 组件的渲染方式
- [x] ### Wrapper `find()` 方法与选择器
- [x] ### UI 组件交互行为的测试

**## Vuex 单元测试**

- [ ] ### CQRS 与 `Redux-like` 架构
- [ ] ### 如何对 Vuex 进行单元测试
- [ ] ### Vue 组件和 Vuex store 的交互

**## Vue 应用测试策略**

- [ ] ### 单元测试的特点及其位置
- [ ] ### 单元测试的关注点
- [ ] ### 应用测试的测试策略
