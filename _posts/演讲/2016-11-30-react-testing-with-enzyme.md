---
layout: session
title: React (Native) Testing with Enzyme
categories: [演讲]
tags: [React, ReactNaitve, Enzyme, UI, UnitTest]
speaker: Jimmy Lv
transition: move
files: /assets/slide.js,/assets/slide.css,/js/zoom.js
highlightStyle: kimbie.light
theme: green
published: True
---

30 min = 15 min * 2

[slide]
# React (Native) Testing with Enzyme
<small>via <strong>Jimmy Lv</strong></small>

[slide]

# 模块化管理？

[slide]

# JavaScript 模块化

------

```javascript
import { shallow } from 'enzyme'

describe('Enzyme Shallow', () => {
  it('App should have title equals to Todos', () => {
    let app = shallow(<App />)
    expect(app.find('h1').text()).to.equal('Todos')
  })
}
```
[slide]

```javascript
import { render } from 'enzyme'

describe('Enzyme Render', () => {
  it('Todo item should not have todo-done class', () => {
    let app = render(<App />)
    expect(app.find('.todo-done').length).to.equal(0)
  })
})
```
[slide]

```javascript
import { mount } from 'enzyme'

describe('Enzyme Mount', () => {
  it('should delete Todo when click button', () => {
    let app = mount(<App />)
    let todoLength = app.find('li').length
    app.find('button.delete').at(0).simulate('click')
    expect(app.find('li').length).to.equal(todoLength - 1)
  })
})
```

[slide]

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
[slide]

```javascript
/* CSS Selector */
wrapper.find('.foo') //class syntax
wrapper.find('input') //tag syntax
wrapper.find('#foo') //id syntax 
wrapper.find('[htmlFor="foo"]') //prop syntax


/* Component Constructor */
wrapper.find(MyComponent)
MyComponent.displayName = 'MyComponent'
wrapper.find('MyComponent')

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


[slide data-on-leave="outcallback"]

[slide]

# [NoBackend Website](http://nobackend.website)

----

<iframe data-src="http://nobackend.website" src="about:blank"></iframe>


