---
layout: post
title: 'Vue 应用单元测试的策略与实践 02 - 单元测试基础'
categories: [前端]
tags: [Tutorial, UnitTest, ES6, Vue, Jest, Agile, TDD]
published: True
---

## 本文的目标

1. 在 TDD 做完 Tasking 列完实例化数据之后，完全没有 UT 基础不知道该怎么写单元测试？

```md
// Given
一个完全没有 UT 基础的新人 🚶
// When
当他 🚶 阅读和练习本文的 Jest 的部分
// Then
他能够把 Given/When/Then 的套路学会
他能够学会 Jest 的基本用法，包括测试 suite 和断言等语法
他能够学会 Jest 中测试异步的几种方式
```

## 单元测试基础

在[上一篇文章](https://blog.jimmylv.info/2018-09-19-vue-application-unit-test-strategy-and-practice-01-introduction/)当中我们介绍了单元测试的意义，以及为何选择 Facebook 的 Jest 作为我们的测试框架。现在就让我们一起来学习如何编写最基础的单元测试。

> 如果你已经有了使用 Jest 编写单元测试的经验，可以选择直接跳到第二段。

### 第一个 Jest 实例

首先创建 `jest-demo` 项目并安装 `jest` 作为项目 `devDependencies` 依赖：

```js
mkdir jest-demo && cd $_
yarn init -y #--yes
yarn add jest -D #--dev
```

然后创建一个 `math.js` 文件，输入一个我们稍后测试的 `sum` 函数:

```js
const sum = (a, b) => a + b

module.exports = { sum }
```

接下来，让我们写第一个测试。在同一个文件夹中创建一个 `math.test.js` 文件，在这里我们将使用 Jest 来测试 `math.js` 中定义的函数:

```js
const { sum } = require('./math')

describe('Math module', () => {
  it('should return sum result when one number plus another number', () => {
    // Given
    const number = 1
    const anotherNumber = 2
    // When
    const result = sum(number, anotherNumber)
    // Then
    expect(result).toBe(2)
  })
})
```

然后运行 `yarn test` （添加 NPM Script）你就可以看到相应的结果。

![](https://raw.sevencdn.com/JimmyLv/images/master/images/jest-failure.png)

### Given/When/Then 的套路

麻雀虽小五脏俱全，在上面的例子当中，我们可以看到很多的测试元素，下面将会一一介绍：

首先我们看到的是一个由 `it` 包裹的测试主体最小单元，采用了 Given When Then 的经典格式，我们常常称之为测试三部曲，也可以解释为 3A 即：

| GWT       | 3A      | 说明                                                                    |
| --------- | ------- | ----------------------------------------------------------------------- |
| **Given** | Arrange | 准备测试测试数据，有时可以抽取到 `beforeEach`                           |
| **When**  | Act     | 采取行动，一般来说就是调用相应的模块执行对应的函数或方法                |
| **Then**  | Assert  | 断言，这时需要借助的就是 Matchers 的能力，Jest 还可以扩展自己的 Matcher |

在 `expect` 后面的 `toBe`称之为 Matcher，是断言时的判断语句以验证正确性 ✅，在后面的文章中我们还会接触更多 Matchers，甚至可以扩展一些特别定制的 Matchers。

```js
expect(1 + 1).toBe(2)
expect(1 + 1).not.toBe(3)
```

修改断言的结果，就可以看到成功后的结果了：

![](https://raw.sevencdn.com/JimmyLv/images/master/images/jest-success.png)

## 模块间依赖 Fake/Stub/Mock/Spy

![](https://raw.sevencdn.com/JimmyLv/images/master/images/isolate.png)

如同人类世界中的羁绊，软件模块之间必然也免不了依赖。[Martin Fowler](https://martinfowler.com/) 在 [UnitTest](https://martinfowler.com/bliki/UnitTest.html) 这篇文章当中将单元测试作了一个重要的区分，即你所测试的单位应该是社交型（Social Tests）还是独立型（Solitary Tests）？ 想象一下你正在测试一个 `Order` Class 的 `price()` 方法，而 `price()` 方法需要在 `Product` 和 `Customer` Class 中调用一些函数。如果你希望单元测试所测试的 `Order` 模块是独立的，那么你就不想直接使用真正的 `Product` 或 `Customer` Class，因为 `Customer` Class 的错误会直接导致 `Order` Class 的单元测试失败。相反，你可能会使用一个替身作为依赖的对象，也就是我们接下来会提到的 Fake/Stub/Mock/Spy。

现实世界里，我们在写代码和单元测试时，常常遇到的一些需要替身的对象包括：

- Database 数据库
- Network requests 网络请求
- access to Files 存取文件
- any External system 任何外部系统

其实在 Jest 当中，Fake/Stub/Mock/Spy 这些概念或许会有所混淆，而这跟 JavaScript 语言本身的特点有一定关系，但是我觉得 Jest 通过统一的 `fn()` 方法把问题解决得还比较恰当，让我们来一块儿看看实例 🌰：

### Mock 用于替代整个模块

```js
import SoundPlayer from './sound-player'

const mockPlaySoundFile = jest.fn()

jest.mock('./sound-player', () => {
  return jest.fn().mockImplementation(() => {
    return { playSoundFile: mockPlaySoundFile }
  })
})
```

我们可以看到 `jest.mock()` 方法中的第二个参数是一个函数，那么我们就可以完全接管整个 `./sound-player` JavaScript 模块，比如说这里的 `playSoundFile` 本来应该是从 `./sound-player` 这个文件当中 `export` 出来的，而被 Mock 之后我们的测试就可以使用 Mock 所返回的数据或方法，从而保证模块所返回的内容是我们所期望的。但这时需要注意的是，该模板的所有功能都已经被 Mock 掉，而不会再从原模块当中返回，所以我们就需要重新实现该模块中的所有功能。可别一不小心就成了张艺谋导演《影》片中的影子，被完全“取而代之”，连夫人也被 Mock 所吸引。

### Stub 用于模拟特定行为

```js
const mockFn = jest.fn()
mockFn()
expect(mockFn).toHaveBeenCalled()

// With a mock implementation:
const returnsTrue = jest.fn(() => true)
console.log(returnsTrue()) // true;
```

这里的特定行为也可以是没有行为，`jest.fn()` 代表着我就是一个 Stub（桩），“你来我就在这里，你走我也依然在这里，风雨无阻”。不需要什么输入输出，只要能在测试的时候验证到 Stub 被调用过就行，也就能够断言到某处代码被执行，从而确定代码被测试所覆盖。而另一种特定行为就是返回特定的数据，即 Stub 也可以根据输入模拟返回一种输出，作为某些模块的替身帮它演戏，比如“小鲜肉们”遇到要跳车啦、要~~卿卿我我~~（误）的时候就要找替身，“一二三四五六七八”连台词都不用背还需要配音。

### Spy 用于监听模块行为

> Spy packages without affecting the functions code

```js
const video = require('./video')

it('plays video', () => {
  const spy = jest.spyOn(video, 'play')
  const isPlaying = video.play()

  expect(spy).toHaveBeenCalled()
  expect(isPlaying).toBe(true)
})
```

Spy 并不会影响到原有模块的功能代码，而只是充当一个监护人的作用，“你可以继续我型我秀上课讲小话，但是老师会偷偷告诉你妈妈，看你放学后老妈不打断你的腿”。比如说上文中的 `video` 模块中的 `play()` 方法已经被 `spy` 过，那么之后 `play()` 方法只要被调用过，我们就能判断其是否执行，甚至执行的次数。

### 如何 Mock 全局的方法？

把全局的数据 Mock 掉很简单，只需要像 `window.document.title = undefined` 这样简单 Fake 赋值就很完美。而像 `matchMedia` 这样的方法在 jsdom 里面并没有被实现，这时候我们当然就需要去把它 Mock 掉，简单把要用到的一些对象属性赋值就好，总之不至于在运行时报错。

```js
window.matchMedia = jest.fn().mockImplementation((query) => {
  return {
    matches: false,
    media: query,
    onchange: null,
    addListener: jest.fn(),
    removeListener: jest.fn(),
  }
})
```

### 代码模块的易测性

从上文的一些例子当中，我们也可以看到，不管是 Fake/Stub/Mock/Spy 最最重要的一个原则就是「简单」，因为我们是在写测试代码，而所依赖的模块就应该以最简单的形态展现出来，绝不要给 `jest.fn()` 编写~~过于~~哪怕一点点复杂的逻辑。如果这个模块有多种表现形态，那就把它分种测试单元进行多次 Mock，每个 `it()` 单元测试一定是针对于单个功能点进行测试的。

保持单元测试独立性的同时，也是在促使你去思考什么样的模块才是符合「职责单一原则」的。单元测试站在使用者的角度来使用该模块，而代码的易测性也就代表着代码的可维护性。

## 如何测试异步代码？

异步是 JavaScript 中绕不开的永恒话题，多亏了 ES6+ 高级语法所提供的多种优雅的异步代码方式，让我们写测试代码的方式也多了好多种。（逃

让我们先来看一下什么是异步请求，这里有一个通过 Chrome API 获取当前位置的实例，可想而知 Chrome 要根据 GPS 信号才能算出当前的经纬度，相当于从卫星 🛰 来回走了一遭，怎么不会异步（代表有延时，延迟返回）呢？

```js
navigator.geolocation.getCurrentPostion() # chrome API 异步获取当前位置
```

### Callback 回调函数

```js
it('the data is peanut butter', (done) => {
  function callback(data) {
    expect(data).toBe('peanut butter')
    done()
  }

  fetchData(callback)
})
```

这是最最普通的方式，也是各大框架都支持的一种写法， `done()` 作为异步代码结束的结束标志，从而让测试框架“知道”在结束时进行断言。但这种方式侵入性比较强，对测试语句不友好且违背了 Given/When/Then 的三段式套路，就像回调地狱一样的道理，如果让 `done()` 充斥着测试那么代码也就变得混乱。

### Promise 让爱 `then()` 到底

```js
it('the data is peanut butter', () => {
  expect.assertions(1)
  return fetchData().then((data) => {
    expect(data).toBe('peanut butter')
  })
})
```

```js
expect(Promise.resolve('lemon')).resolves.toBe('lemon')

expect(Promise.reject(new Error('octopus'))).rejects.toThrow('octopus')
```

其实这种方式也好不到哪去，无非就是把 `done()` 方式换成了 `then()` 又一次充斥在整个 expect 当中，混乱了 When 和 Then 两种本该分开的时刻。但也有一个不错的点，可以通过 Promise 的 `.resolve()` 和 `.reject()` 方法使测试分别验证正常或异常的情况。

### Async/Await 让异步变得同步

```js
test('the data is peanut butter', async () => {
  expect.assertions(1)
  const data = await fetchData()
  expect(data).toBe('peanut butter')
})
```

Async/Await 语法糖在业务代码当中就特别好使了，好处不多说直接看得见：原本需要 `done()` 或 `then()` 的地方都不再混乱，又一次回归到了正常的 Given/When/Then 三段式套路，让测试代码变得非常清晰易读。唯一需要注意的是， 额外的`expect.assertions(number)` 其实是验证在测试期间所调用的断言数量，这在测试多层异步代码时很有用，以确保实际调用回调中的断言次数。

意犹未尽吗？更加 Jest 相关的内容可以查看这篇文章 [Testing JavaScript with Jest](https://flaviocopes.com/jest/)，与此同时具体的 API 可以参考[官方文档](https://facebook.github.io/jest/)。

## 未完待续……

**## 单元测试基础**

- [x] ### 单元测试与自动化的意义
- [x] ### 为什么选择 Jest
- [x] ### Jest 的基本用法
- [x] ### 该如何测试异步代码？

**## Vue 单元测试**

- [ ] ### Vue 组件的渲染方式
- [ ] ### Wrapper `find()` 方法与选择器
- [ ] ### UI 组件交互行为的测试

**## Vuex 单元测试**

- [ ] ### CQRS 与 `Redux-like` 架构
- [ ] ### 如何对 Vuex 进行单元测试
- [ ] ### Vue 组件和 Vuex store 的交互

**## Vue 应用测试策略**

- [ ] ### 单元测试的特点及其位置
- [ ] ### 单元测试的关注点
- [ ] ### 应用测试的测试策略
