---
layout: post
title: 'Vue 应用单元测试的策略与实践 04 - Vuex 单元测试'
categories: [前端]
tags: [Tutorial, UnitTest, ES6, Vue, Vuex, Jest, CQRS, TDD]
published: True
---

## 本文的目标

2.2 在 Vue 应用的单元测试中，对 Vuex store 该如何测试？如何测试与 Vue 组件之间的交互？

```md
// Given
一个有基本的 UT 知识和 Vue 组件单元测试经验的开发者 🚶
// When
当他 🚶 阅读和练习本文的 Vuex 单元测试的部分
// Then
他能够对 Vuex 概念的理解更加深入，且知道 `Redux-like` 架构的好处
他能够合理测试 vuex store 的 mutation、getter 中的业务逻辑和异步 action
他能够测试组件如何正确读取 store 中的 state 以及 dispatch action
```

## 如何理解 Vuex 模式？

### Vuex 的前车之鉴

> Vuex 是一个专为 Vue.js 应用程序开发的状态管理模式。它采用集中式存储管理应用的所有组件的状态，并以相应的规则保证状态以一种可预测的方式发生变化。

![](https://raw.sevencdn.com/JimmyLv/images/master/2018/20181102201926.png)

古人说「读史让人明智」，学习历史是为了更好得前行，为了能够认识现在，看清未来。让我们来看看 Vuex 的历史，Vuex 借鉴于 Redux，而 Redux 的实现构想则最初出身于 [Flux](http://facebook.github.io/flux/docs/overview.html) ，这是一个由 Facebook 为其应用所设计的应用程序架构。Flux 模式在 JavaScript 应用里像是找到了新家一样，但其实只是借鉴了**领域驱动设计** (DDD) 和**命令-查询职责分离** (CQRS)。

### CQRS 与 Flux 架构

描述 Flux 最普遍的一种的方式就是将其与 **Model-View-Controller** (MVC) 架构进行对比。

在 MVC 当中，一个 Model 可以被多个 Views 读取，并且可以被多个 Controllers 进行更新。在大型应用当中，单个 Model 会导致多个 Views 去通知 Controllers，并可能触发更多的 Model 更新，这样结果就会变得非常复杂。

![mvc-diagram](https://jaysoo.ca/images/mvc-diagram.png)

而 Flux 以及我们要学习的 Vuex 则是试图通过强制单向数据流来解决这个复杂度。在这种架构当中，Views 查询 Stores（而不是 Models），并且用户交互将会触发 Actions，Actions 则会被提交到一个集中的 Dispatcher 当中。当 Actions 被派发之后，Stores 将会随之更新自己并且通知 Views 进行修改。这些 Store 当中的修改会进一步促使 Views 查询新的数据。

![flux-diagram](https://jaysoo.ca/images/flux-diagram.png)

MVC 和 Flux 最大的不同就是查询和更新的分离。在 MVC 中，Model 同时可以被 Controller 更新*并且*被 View 所查询。在 Flux 里，View 从 Store 获取的数据是只读的。而 Stores 只能通过 Actions 被更新，这就会影响 Store 本身*而不是*那些只读的数据。

以上所描述的模式非常接近于由 Greg Young 第一次所提出的 CQRS：

1. 如果一个方法修改了这个对象的状态，那就是一个 _command_（命令），并且一定不能返回值。
2. 如果一个方法返回了一些值，那就是一个 _query_（查询），并且一定不能修改状态。

### Vuex 背后的基本思想

所以说， Vuex 就是把组件的共享状态 “state” 抽取出来，以**一个**全局 “store” 的单例模式统一管理。在这种模式下，我们的组件树构成了一个巨大的“视图”，不管在树的哪个位置，任何组件都能获取状态或者触发行为。

另外，隔离状态管理能够获得很多好处，当然也需要强制遵守一定的规则：

1. Vuex 的状态存储是响应式的。当 Vue 组件从 store 中读取状态的时候，若 store 中的状态发生变化，那么相应的组件也会相应地得到高效更新。这也就是 CQRS 中 _query_（查询）的一种实现。
2. 你不能直接改变 store 中的状态。改变 store 中的状态的唯一途径就是显式地**提交 (commit) mutation**，这样使得我们可以方便地跟踪每一个状态的变化。这也就是 CQRS 中 _command_（命令）的一种实现。

## 如何对 Vuex 进行单元测试

得益于 Vuex 能够将 Vue 应用的共享状态进行隔离，我们的代码也因此变得更加结构化且易于维护，Vuex 中的 mutation、action 和 getter 都被放在了合理的位置，承担不同的职责 ，这也使得对它们进行单元测试变得容易很多。

### mutations 测试

Mutation 很容易被测试，因为它们仅仅是一些完全依赖参数的函数。最为简单的 mutation 测试，仅一一对应保存数据切片。此种 mutation 可以不需要测试覆盖，因为基本由架构简单和逻辑简单保证，不需要靠读测试用例来理解。而一个较为复杂、具备测试价值的 mutation 在保存数据的同时，还可能进行了合并、去重等操作。

```js
// count.js
const state = { ... }
const actions = { ... }
export const mutations = {
  increment: state => state.count++
}
// count.test.js
import { mutations } from './store'

// 解构 `mutations`
const { increment } = mutations

describe('mutations', () => {
  it('INCREMENT', () => {
    // 模拟状态
    const state = { count: 0 }
    // 应用 mutation
    increment(state)
    // 断言结果
    expect(state.count).toEqual(1)
  })
})
```

### actions 测试

Action 应对起来略微棘手，因为它们可能需要调用外部的 API。当测试 action 的时候，我们需要增加一个 mocking 服务层——例如，我们可以把 API 调用抽象成服务，然后在测试文件中用 mock 服务响应所期望的 API 调用。

```js
// product.js
import shop from '../api/shop'

export const actions = {
  getAllProducts({ commit }) {
    commit('REQUEST_PRODUCTS')
    shop.getProducts((products) => {
      commit('RECEIVE_PRODUCTS', products)
    })
  },
}
```

```js
// product.test.js
jest.mock('../api/shop', () => ({
  getProducts: jest.fn(() => /* mocked response */),
}))

describe('actions', () => {
  it('getAllProducts', () => {
    const commit = jest.spy()
    const state = {}

    actions.getAllProducts({ commit, state })

    expect(commit.args).toEqual([
      ['REQUEST_PRODUCTS'],
      ['RECEIVE_PRODUCTS', { /* mocked response */ }]
    ])
  })
})
```

### getters 测试

getter 的测试与 mutation 一样直截了当。getters 也是比较重逻辑的地方，并且它也是一个纯函数，与 mutations 测试享受同样待遇：纯净的输入输出，简易的测试准备。下面来看一个稍微简单点的 getters 测试用例：

```js
// product.js
export const getters = {
  filteredProducts(state, { filterCategory }) {
    return state.products.filter((product) => {
      return product.category === filterCategory
    })
  },
}
```

```js
// product.test.js
import { expect } from 'chai'
import { getters } from './getters'

describe('getters', () => {
  it('filteredProducts', () => {
    // 模拟状态
    const state = {
      products: [
        { id: 1, title: 'Apple', category: 'fruit' },
        { id: 2, title: 'Orange', category: 'fruit' },
        { id: 3, title: 'Carrot', category: 'vegetable' },
      ],
    }
    // 模拟 getter
    const filterCategory = 'fruit'

    // 获取 getter 的结果
    const result = getters.filteredProducts(state, { filterCategory })

    // 断言结果
    expect(result).to.deep.equal([
      { id: 1, title: 'Apple', category: 'fruit' },
      { id: 2, title: 'Orange', category: 'fruit' },
    ])
  })
})
```

## Vue 组件和 Vuex store 的交互

前面我们讲完了 Vuex 单元测试所需要的基本知识，而 Vue 组件需要从 Vuex store 读取状态或者是发送 action 改变 store 状态的时候，又该如何测试他们之间的交互呢？接下来就来聊聊如何用 Vue Test Utils 测试 Vue 组件中的 Vuex。

站在单元测试的角度，其实我们在测试 Vue 组件（单元）的时候不需要关心 Vuex store 长什么样子，我们只需要知道 Vuex store 当中的这些 action 将会在适当的时机触发，以及它们触发时的预期行为是什么。

```html
<template>
  <div class="app">
    <div class="price">amount: ${{$store.state.price}}</div>
    <button @click="actionClick()">Buy</button>
  </div>
</template>

<script>
  import { mapActions } from 'vuex'
  export default {
    methods: {
      ...mapActions(['actionClick']),
    },
  }
</script>
```

在单元测试的时候，shallowMount（浅渲染）方法接受一个挂载 options，可以用来给 Vue 组件传递一个伪造的 store。然后我们就可以使用 Jest 模拟一个 action 的行为再传给 store，而 actionClick 这个伪造函数能够让我们去断言该 action 是否被调用过。所以我们在测试 action 的时候就可以只关心 action 的触发，而至于触发之后对 store 做了什么事情我们就不需要再关心了，因为 Vuex 的单元测试会涵盖相关的代码逻辑。

```js
import { shallowMount, createLocalVue } from '@vue/test-utils'
import Vuex from 'vuex'

const localVue = createLocalVue()
localVue.use(Vuex)

const fakeStore = new Vuex.Store({
  state: {},
  actions: {
    actionClick: jest.fn(),
  },
})

it('当按钮被点击时候调用“actionClick”的 action', () => {
  const wrapper = shallowMount(Actions, { store: fakeStore, localVue })
  wrapper.find('button').trigger('click')
  expect(actions.actionClick).toHaveBeenCalled()
})
```

需要注意的是，在这里我们是把 Vuex store 传递给一个 localVue，而不是传递给基础的 Vue 构造函数。这是因为我们不想影响到全局的 Vue 构造函数，如果直接使用 `Vue.use(Vuex)` 会让 Vue 的原型上会增加 \$store 属性从而影响到其他的单元测试。而 localVue 则是一个独立作用域的 Vue 构造函数，我们可以对其进行任意的改动。

当然咯，除了 mock 掉 actions，Vuex store 里面的任何内容我们都可以将其模拟出来，比如 state 或者 getters：

```js
import { shallowMount, createLocalVue } from '@vue/test-utils'
import Vuex from 'vuex'

const localVue = createLocalVue()
localVue.use(Vuex)

const fakeStore = new Vuex.Store({
  state: {
    price: '998',
  },
  getters: {
    clicks: () => 2,
    inputValue: () => 'input',
  },
})

it('在app中渲染价格和“inputValue”', () => {
  const wrapper = shallowMount(Components, { store: fakeStore, localVue })
  expect(wrapper.find('p').text()).toBe('input')
  expect(wrapper.find('.price').text()).stringContaining('$998')
})
```

## 总结一下

总之呢，不要测试 Vue 组件和 Vuex store 交互的时候引入一个真实的 Store，那样就不再是单元测试了，还记得我们在第二篇[单元测试基础](https://blog.jimmylv.info/2018-10-29-vue-application-unit-test-strategy-and-practice-02-how-jest-work/)中所提到的社交型（Social Tests）还是独立型（Solitary Tests）测试单元吗？Vuex 等 `Redux-like` 架构在前端应用中的 “状态管理模式” ，已经将 View 视图层和 State 数据层尽可能合理得拆分与隔离，那么单元测试就只需要分别测试 Vue 和 Vuex，从而就能保证 Vue 组件和数据流按照预期那样工作。

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

- [x] ### CQRS 与 `Redux-like` 架构
- [x] ### 如何对 Vuex 进行单元测试
- [x] ### Vue 组件和 Vuex store 的交互

**## Vue 应用测试策略**

- [ ] ### 单元测试的特点及其位置
- [ ] ### 单元测试的关注点
- [ ] ### 应用测试的测试策略
