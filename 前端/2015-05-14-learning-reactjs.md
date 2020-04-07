---
layout: post
title: React.js 复习笔记：组件组合与复用
categories: [前端]
tags: [React, Rethink]
published: True
---

## Why React?

React 的创建是为了数据的频繁交互：通过组件化轻松展现数据；数据改变时，自动更新 UI，并且只更新有改变的部分。

## 组件入门

### 创建组件

`var component = React.createClass()`用来创建一个组件类，组件类似于函数，可以把它看作有着 props 和 state 状态并且可以返回（`render()`）HTML 结构的函数。

`React.render()`将 React 的模板转化为 HTML，并插入到相应的 DOM 结构中，`React.render`方法可以渲染 HTML 结构，也可以渲染 React 组件。

### 渲染 HTML 标签

声明变量采用首字母小写

```js
var myDivElement = <div className="foo" />
React.render(myDivElement, document.body)
```

### 渲染 React 组件

声明变量采用首字母大写

```js
var MyComponent = React.createClass({
  /*...*/
})
var myElement = <MyComponent someProperty={true} />
React.render(myElement, document.body)
```

## 关于 JSX

### 目的

组件应该关注分离，而不是模板和展现逻辑分离。结构化标记和生成结构化标记的代码是紧密关联的，此外，展现逻辑一般都很复杂，使用模板语言会使展现变得笨重。

### 语法说明

标签的属性 class 和 for，需要写成 className 和 htmlFor，因为两个属性是 JavaScript 的保留字和关键字，无论你是否使用 JSX。

JSX 是 HTML 和 JavaScript 混写的语法，当遇到`<`，JSX 就当 HTML 解析，遇到`{`就当 JavaScript 解析。

### 虚拟 DOM

React 使用了内部的虚拟 DOM，当数据发生改变，先在虚拟 DOM 中计算变化，最后将变动的部分反应到真实的 DOM 中。

```js
#app.js
var HelloWorld = React.createClass({
    render: function () {
        return (
            <p>
            Hello,<input type="text" placeholder="Your name here" value={this.props.date.toTimeString()}/>!
            It is {this.props.date.toTimeString()}
            </p>
        );
    }
});

setInterval(function () {
    React.render(
        <HelloWorld date={new Date()} />,
        document.getElementById('example')
    );
}, 500);
```

input 相对于这个组件来说，是它的属性，并且没有嵌入动态的数据。而在 React 的设定中，属性是不可变的。

## 组件属性

### 属性延伸

例如 component 组件有两个动态的属性 foo 和 bar：

`var component = <Component foo={x} bar={y} />;`

而实际上，有些属性可能是后续添加的，当需要拓展我们的属性的时候，定义个一个属性对象，并通过`{...props}`的方式引入，React 会帮我们拷贝到组件的 props 属性中。

可以使用属性延伸覆盖原来的属性值：

```js
var Component = React.createClass({
  render: function () {
    return (
      <div {...this.props} title="zzz">
        this is a div
      </div>
    )
  },
})

React.render(<Component name="xxx" title="yyy" />, document.body)
```

### style 属性

在 React 中写行内样式时，要这样写，不能采用引号的书写方式

```js
React.render(<div style={{ color: 'red' }}>xxxxx</div>, document.body)
```

## UI 交互

### this.props

```js
var HelloWorld = React.createClass({
  render: function () {
    return <div data-title={this.props.title}>{this.props.content}</div>
  },
})

React.render(<HelloWorld title="this is title" content="this is content" />, document.body)
```

通过`this.props`我们可以拿到组件被使用时的属性，this.props 就是组件的属性集合。React 将组件的子节点封装到了 children 属性中，当子节点只有一个的时候直接通过`this.props.children`获取子节点的内容。当子节点的个数大于 1 时，`this.props.children`返回的是一个数组。

### this.state

`this.state`是同 UI 交互最重要的属性，this 指向组件的实例。React 将 UI 简单的看作状态机，拥有各种各样的状态，并在各种状态间切换，这样很容易保持 UI 的一致性。在 React 中，你只要改变组件的状态，就会重新渲染 UI，React 会在最有效的方式下更新 DOM。通过调用`setState(data, callback)`方法，改变状态，就会触发 React 更新 UI。

```js
var ColorButton = React.createClass({
  getInitialState: function () {
    return { bColor: 'green' }
  },
  render: function () {
    return (
      <button onClick={this.handleClick} style={{ backgroundColor: this.state.bColor }}>
        click
      </button>
    )
  },
  // 点击按钮，切换按钮的颜色：
  handleClick: function (event) {
    this.setState({ bColor: this.state.bColor === 'green' ? 'red' : 'green' })
  },
})

React.render(<ColorButton />, document.body)
```

`getInitialState`是用来初始化 state，`handleClick`是用来处理我们点击事件的，如果想要拿到当前操作的 DOM，通过参数 event 获取。

### 两种属性的运用

大部分的组件应该从 props 属性中获取数据并渲染。但有的时候组件得相应用户输入，同服务器交互，这些情况下会用到 state。React 的官方说法是：尽可能的保持你的组件无状态化。为了实现这个目标，得保持你的状态同业务逻辑分离，并减少冗余信息，尽可能保持组件的单一职责。

React 官方推荐的一种模式就是：构建几个无状态的组件用来渲染数据，在这些之上构建一个有状态的组件同用户和服务交互，数据通过 props 传递给无状态的组件。

```js
var RenderComponent = React.createClass({
  render: function () {
    return (
      <ul>
        {this.props['data-list'].map(function (item) {
          return <li>{item}</li>
        })}
      </ul>
    )
  },
})

var StateComponent = React.createClass({
  getInitialState: function () {
    return { list: ['xxx', 'yyy'] }
  },
  render: function () {
    return (
      <div>
        <button onClick={this.handleClick}>click</button>
        <RenderComponent data-list={this.state.list} />
      </div>
    )
  },
  handleClick: function () {
    this.setState({ list: [1, 2, 3] })
  },
})

React.render(<StateComponent />, document.body)
```

React 还允许我们下面的方式自定义属性的默认值：

```js
var ComponentWithDefaultProps = React.createClass({
  getDefaultProps: function () {
    return {
      value: 'default value',
    }
  },
  /* ... */
})
```

`getDefaultProps()`的值将会被缓存，当`this.props.value`的值没有被父组件指定时，将会使用这个默认值。

## 组件组合

官方示例：

```js
var Avatar = React.createClass({
  render: function () {
    return (
      <div>
        <ProfilePic username={this.props.username} />
        <ProfileLink username={this.props.username} />
      </div>
    )
  },
})

var ProfilePic = React.createClass({
  render: function () {
    return <img src={'http://graph.facebook.com/' + this.props.username + '/picture'} />
  },
})

var ProfileLink = React.createClass({
  render: function () {
    return <a href={'http://www.facebook.com/' + this.props.username}>{this.props.username}</a>
  },
})

React.render(<Avatar username="pwh" />, document.getElementById('example'))
```

上面的例子中，组件 Avatar 包含了组件 ProfilePic 和 ProfileLink。在 React 当中，**所有者就是可以设置其他组件 props 的组件**。说的通俗点：如果组件 X 出现在了组件 Y 的 render()方法中，那么组件 Y 就是所有者。正如我们之前所讨论的，组件不能改变 props—props 应同所有者初始化它们时保持一致。

### 父子节点的关系

一定要弄清所有者和被所有关系，父子关系的区别。所有者和被所有者关系是针对 React 组件的，父子关系是针对 DOM 结构的。来上面的例子来说，Avatar 是所有者，拥有 div、ProfilePic、ProfileLink，而 div 和 ProfilePic、ProfileLink 则是父子关系。

`<Parent><Child /></Parent>`创建实例，Parent 可以通过 this.props.children 获取到它的子内容。

### 动态子节点

在 React 更新 DOM 的过程中，子节点是根据它们渲染的顺序调节的。实际上，React 改变第一个子节点的内容，然后删除最后一个节点。所以当数据来自于搜索结果或者新的组件被添加到数据流里，在这种情况下，每个子节点都需要保持唯一的标识，此时可以给每个子节点添加 key 属性。

```js
var Component = React.createClass({
  render: function () {
    var results = this.props.results
    return (
      <ol>
        {results.map(function (result) {
          return <li key={result.id}>{result.text}</li>
        })}
      </ol>
    )
  },
})
```

### 单向数据流

在 React 当中，数据通过 props 从所有者向子节点传递，这就是所谓的单向数据绑定了。所有者将它拥有的组件 props 绑定到它的 props 或者 state，这个过程将会递归进行。数据改变就会通过组件到子组件再到子节点即所有的 DOM 节点，最终反映到 UI 层。
