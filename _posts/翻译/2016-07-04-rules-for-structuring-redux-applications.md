---
layout: post
title: 【译】Redux + React 应用程序架构的 3 条规范（内附实例）
categories: [翻译]
tags: [Redux, React, FED, DX, Architecture]
published: True

---

原文地址：<http://jaysoo.ca/2016/02/28/organizing-redux-application/>

> As our applications grow, we often find that file structure and organization to be crucial for the maintainability of application code.

随着应用程序的增长，通常我们就会发现文件结构和组织对于应用程序代码的可维护性来说就会变得非常重要。

> What I want to do in this post is to present three organizational rules that I personally follow on my own projects. By following the rules, your application code should be easier to reason about, and you will find yourself wasting less time on file navigation, tedious refactoring, and bug fixes.

在这篇文章里，我会介绍自己在项目中亲自实践的三条组织规则。通过遵循这些规则，你的应用程序代码将会变得更加易读，而且你会发现自己不用再把时间浪费在文件导航，频繁重构以及 Bug 修复上了。

> I hope that these tips will prove useful for developers who want to improve their application structure, but don’t know where to start.

我希望这些建议，可以给那些想要改善应用结构却不知从何入手的开发者们提供帮助。

 
## Three rules for project structure | 项目结构的三条规则

> The following are some basic rules for structuring a project. It should be noted that the rules themselves are framework and language agnostic, so you should should be able to follow them in all situations. However, the examples are in React and Redux. Familiarity with these frameworks is useful.

接下来的内容就是关于构建一个项目的一些基本规则。需要注意的是，这些规则本身是跟框架和语言无关的，所以你在所有的情况下都应该可以遵循这些规则。但在这里，我们是以 React 和 Redux 为例，熟悉这些框架将会很有帮助。

### Rule #1: Organize by feature | 规则 #1: 基于特性进行组织

> Let’s first start by going over what not to do. A common way that projects can be organized is by object roles.

首先让我们来看看不该做什么，常见的一种方式就是根据对象角色来组织项目结构。

**Redux + React:**
 
```
actions/
  todos.js
components/
  todos/
    TodoItem.js
    ...
constants/
  actionTypes.js
reducers/
  todos.js
index.js
rootReducer.js
```

**AngularJS:**

```
controllers/
directives/
services/
templates/
index.js
```

**Ruby on Rails:**

```
app/
  controllers/
  models/
  views/
```


> It may seem reasonable to group similar objects together like this (controllers with controllers, components with components), however as the application grows this structure does not scale.

将类似的对象（Controller 和 Controller，Component 和 Component）组织在一起，这看似合情合理，但伴随着应用的增长，这种结构将会不利于扩展。

> When you add and change features, you’ll start to notice that some groups of objects tend to change together. **These objects group together to form a feature module**. For example, in a todo app, when you change the `reducers/todos.js` file, it is likely that you will also change `actions/todos.js` and `components/todos/*.js`.

每当你添加或修改特性的时候，你就会开始注意到某些部分的对象倾向于同时发生改变。**将这些对象归在一起可以共同构成一个特性模块**。比如说，在一个 Todo 应用里，每当你改变 `reducers/todos.js` 文件，很可能你也会改变 `actions/todos.js` 和 `components/todos/*.js`。

> Instead of wasting time scrolling through your directories looking for todos related files, it is much better to have them sitting in the same location.

相反，为了不再把时间浪费在浏览目录去寻找跟 todos 有关的文件，还是将它们放到同一个地方会明显比较好。

> **A better way to structure Redux + React project:**

**一种更好的 React + Redux 项目文件目录：**
 
```
todos/
  components/
  actions.js
  actionTypes.js
  constants.js
  index.js
  reducer.js
index.js
rootReducer.js
```

> **Note:** I will go into the details of what's inside the files later in this post. 

**注意：**我将会在文章后面的部分详细描述这些文件的具体内容。

> In a large project, organizing by feature affords you the ability to focus on the feature at hand, instead of having to worry about navigating the entire project. This means that if I need to change something related to todos, I can work soley within that module and not even think about the rest of the application. In a sense, it creates an **application within the main application**.

在一个大型项目当中，根据特性组织文件可以让你专注于近在手边儿的特性，而不会不得已而去担心整个项目的导航。这就意味着，如果我需要修改 todos 相关的东西，我可以单独工作在这个模块而不用考虑应用的其他部分。从感觉上来说，这就像是**在主应用程序里面创建了另外一个应用程序**。

> On the surface, organizing by feature may seem like an aesthetics concern, but as we will see in the next two rules, this way of structuring projects will help simplify your application code.

从表面上来看，根据特性组织似乎看起来像是一种基于美学的考虑。但是，就如我们在接下来的两个规则中所看到的那样，这种构建项目的方式将会帮助简化你的应用程序代码。
 
### Rule #2: Create strict module boundaries | 规则 #2: 设计严格的模块边界

> In his Ruby Conf 2012 talk [Simplicity Matters](https://www.youtube.com/watch?v=rI8tNMsozo0), Rich Hickey defines complexity as the **complecting** (or interleaving) of things. When you couple modules together, you can picture an actual knot or braid forming in your code.

Rich Hickey 在他的 Ruby Conf 2012 演讲 [Simplicity Matters](https://www.youtube.com/watch?v=rI8tNMsozo0) 中，将复杂度定义为一种**编织**（或交织）的东西。当你把模块耦合在一起，你将会从代码当中看到某种跟现实中的绳结或者辫子一样的形态。

![](//o7mw3gkkh.qnssl.com//images/2016/1467619650283.png)

> The relevence of complexity to project structure is that when you place objects in **close proximity** to one another, the **barrier to couple** them lowers dramatically.

项目结构的复杂相关度就是，当你把一个对象**靠近于**另外一个对象，将其**耦合到一起的障碍**就会显著减少。

> As an example, let’s say that we want to add a new feature to our TODO app: We want the ability to manage TODO lists by *project*. That means we will create a new module called projects.

作为示例，让我们来给 TODO 应用添加一个新特性：我们想要根据 *project* 来管理 TODO 列表。这就意味着我们将要创建一个名为 `projects` 的新模块。

```
projects/
  components/
  actions.js
  actionTypes.js
  reducers.js
  index.js
todos/
index.js
```

> Now, it is obvious that the *projects* module will have a dependency on todos. In this situation, it is important that we exercise discipline and only couple to the “public” API exposed in `todos/index.js`.

现在，*`projects`* 模块显然会依赖于 `todos`。在这种情况下，严格约束，以及仅耦合于由 `todos/index.js` 所暴露的「公共」接口就变得非常重要。

**BAD**

```js
import actions from '../todos/actions';
import TodoItem from '../todos/components/TodoItem';
```

**GOOD**

```js
import todos from '../todos';
const { actions, TodoItem } = todos;
```

> Another thing to **avoid is coupling to the state of another module**. For example, say that within the projects module, we need to grab information out of todos state in order to render a component. It is better that the todos module exposes an interface for projects to query this information, rather than complecting the component with todos state.

另外一件事就是**避免跟其他模块的状态相耦合**。比如说，在 `projects` 模块内部，我们需要从 `todos` 的状态里面获取信息从而渲染组件。那么 `todos` 模块就最好能给 `projects` 模块暴露一个接口用于查询信息，而不是让这个组件和 `todos`  状态交织在一起。

**BAD**

```
const ProjectTodos = ({ todos }) => (
  <div>
    {todos.map(t => <TodoItem todo={t}/>)}
  </div>
);

// Connect to todos state
const ProjectTodosContainer = connect(
  // state is Redux state, props is React component props.
  (state, props) => {
    const project = state.projects[props.projectID];

    // This couples to the todos state. BAD!
    const todos = state.todos.filter(
      t => project.todoIDs.includes(t.id)
    );

    return { todos };
  }
)(ProjectTodos);
```

**GOOD**

```
import { createSelector } from 'reselect';
import todos from '../todos';

// Same as before
const ProjectTodos = ({ todos }) => (
  <div>
    {todos.map(t => <TodoItem todo={t}/>)}
  </div>
);

const ProjectTodosContainer = connect(
  createSelector(
    (state, props) => state.projects[props.projectID],

    // Let the todos module provide the implementation of the selector.
    // GOOD!
    todos.selectors.getAll,

    // Combine previous selectors, and provides final props.
    (project, todos) => {
      return {
        todos: todos.filter(t => project.todoIDs.includes(t.id))
      };
    }
  )
)(ProjectTodos);
```

> In the “GOOD” example, the projects module is not concerned with the internal state of todos module. This is powerful because we can freely change the structure of the todos state, without worrying about breaking other dependent modules. Of course we still need to maintain our selector contracts, but the alternative is having to search through a whole bunch of disparate components and refactor them one by one.

在「GOOD」的例子当中，`projects` 模块并不用关心 `todos` 模块内部的状态。这是非常有用的，因为我们可以自由地改变 `todos` 状态的结构，而不用担心破坏其他依赖模块。当然，我们依旧需要维护我们的 selector 契约，但另一种选择则必须从一大堆不相干的组件中进行搜索并依次对其重构。

> By artificially creating strict module boundaries, we can simplify our application code, and in turn increase the maintainability of our application. **Instead of haphazardly reaching inside other modules, we should think about forming and maintaining contracts between them.**

通过人为地设计严格的模块边界，我们可以简化应用代码，并且反过来增加应用的可维护性。**无需涉及其他模块的内部，我们应当思考模块之间契约的形式和维护。**

> Now that the projects are organized by features, and we have explicit boundaries between each feature, there is one last thing I want to cover: *circular dependencies*.

既然项目已经根据特性组织而成，并且在每个特性之间也有了清晰的边界，那么接下来就是我想要涉及的最后一件事：*循环依赖*。

### Rule #3: Avoid circular dependencies | 规则 #3: 避免循环依赖

> It shouldn’t take too much convincing for you to believe me when I say that circular dependencies are bad. Yet, without proper project structure, it is all too easy to fall into this trap.

「循环依赖是很糟糕的」，这应该不用太费口舌就能让你相信我说的话。但是，如果没有适当的项目结构的话，还是会很容易就掉进了这个坑里。

> Most of the time, dependencies start out innoculously. We may *think* that the projects module need to reduce some state based on todos actions. If we are not grouping by features, and we see a large manifest of all action types within a global `actionTypes.js` file, it is all too easy for us to just reach in and grab what we need (at the time) without a second thought.

大多数时候，依赖在一开始的时候都是无害的。我们可能会*认为* `projects` 模块需要根据 `todos` 的 actions 来 reduce 一些状态。如果我们没有根据特性分组的话，然后我们就会在一个全局的 `actionTypes.js` 文件当中看到一个包含所有 action 类型的清单，这对我们来说，就很容易找到并且无需考虑就可以获取我们所需要的（在当时）。

> Say, that within todos we want to reduce state based on an action type of projects. Easy enough if we have a global `actionTypes.js` file. However, we will soon learn that this is no easy feat if we have explicit module boundaries. To illustrate why, consider the following example.

假设，在 `todos` 内部我们又想要根据 `projects` 的 action 类型来 reduce 状态。如果我们已经有了一个全局的 `actionTypes.js` 文件的话，这应该已经足够简单了。但是很快我们就会明白，要是我们有了清晰的模块边界的话这些就不足挂齿了。为了说明原因，来看看以下的实例。

#### Circular dependency example | 循环依赖示例

Given:

**a.js**

```
import b from './b';

export const name = 'Alice';

export default () => console.log(b);
```

**b.js**

```
import { name } from './a';

export default `Hello ${name}!`;
```

> What happens with the following code?

那么接下来的代码会发生什么呢？

```
import a from './a';

a(); // ???
```

> We might expect “Hello Alice!” to be printed, but in actuality, a() would print “Hello undefined!”. This is because the name export of a is not available when a is imported by b (due to circular dependencies).

我们可能会期待 “Hello Alice!” 会被打印出来，但其实 `a()` 会输出 “Hello undefined!”。这是因为 `a` 的命名导出，在 `a` 是由 `b` 引入的时候并不可用（由于循环引用）。

> The implication here is that we **cannot both have projects depend on action types within todos *and* todos depend on action types within projects.** You can get around restriction in clever ways, but if you go down this road I can guarantee you that it will come to bite you later on!

这里隐含的意思就是，我们**不能同时让 `projects` 依赖于 `todos` 内部的 action 类型，*并且* `todos` 又依赖于 `projects` 内部的 action 类型**。你可以使用聪明的方式绕过这种限制，但要是你继续这样下去的话，我保证你会在将来的时候被坑的！
 
#### Don’t make hairballs! | 不要制造毛团！

> Put another way, by creating circular dependencies, you are **complecting in the worst possible way**. Imagine a module to be a strand of hair, then modules that are inter-dependent on each other form a big, messy hairball.

换句话来说，制造循环依赖，你就是**在用最糟糕的方式在打着绳子的结**。想象一下一个模块就是一缕头发，然后模块之间相互依赖着形成了一个巨大的，混乱的毛团。

![](//o7mw3gkkh.qnssl.com//images/2016/1467640142143.png)

> Whenever you want to use a small module within the hairball, you will have no choice but to pull in the giant mess. And even worse, when you change something inside the hairball, it would be hard *not* to break something else.

不论什么时候，你想要使用这块毛团中的一个小模块，你都别无选择只能陷入这种巨大的混乱当中。而且更糟糕的是，当你需要修改毛团当中的某些东西，要想*不*破坏其他东西的话就变得很难了。

> By following Rule #2, it should make it hard for you to create these circular dependencies. Don’t fight against it. Instead, use that energy to properly factor your modules.

遵循规则 #2，你就很难会制造出这种循环依赖了。不要与之对抗，而是用这份精力来适当地分解你的模块。

## In-depth example and recommendations | 深入的实例和规范推荐

> I want to do a deeper dive into the contents of the different files within a Redux and React application. This section will be specifically about these frameworks, so feel free to skip if you are not interested in them. :)

接下来我想要深入到 Redux 和 React 应用当中不同文件的具体内容。这部分将会特别针对这些框架，要是你不感兴趣的话可以随你便跳过去。:)

> Let’s take a look at our TODO app again. (I added constants, model, and selectors into this example)

让我们来重新看看我们的 TODO 应用。（我在示例当中添加了 constants，model，以及 selectors）
 
```
todos/
  components/
  actions.js
  actionTypes.js
  constants.js
  index.js
  model.js
  reducer.js
  selectors.js
index.js
rootReducer.js
```

> We can break these modules down by their responsibilities.

我们将会根据他们的职责来拆分这些模块。
 
### Module index and constants | 模块 index 和 常量

> The module index is responsible for maintaining its public API. This is the exposed surface where modules can interface with each other.

模块 `index` 就是负责维护模块的公共 API。这是模块和模块之间相互进行交互而暴露的地方。

> A minimum Redux + React application should be something like this.

一个最小化的 Redux + React 应用应该就会如下所示。
 
```js
// todos/constants.js

// This will be used later in our root reducer and selectors
export const NAME = 'todos';
```
 
```js
// todos/index.js
import * as actions from './actions';
import * as components from './components';
import * as constants from './constants';
import reducer from './reducer';
import * as selectors from './selectors';

export default { actions, components, constants, reducer, selectors };
```
 
> **Note:** This is similar to the [Ducks](https://github.com/erikras/ducks-modular-redux) structure.

**注意：**这跟 [Ducks](https://github.com/erikras/ducks-modular-redux) 架构有所类似。

### Action types & Action creators | Action 类型 & Action Creators

> Action types are just string constants within Redux. The only thing I’ve changed here is that I prefixed each type with “todos/” in order to create a namespace for the module. This avoid name collisions with other modules in the application.

Action 类型在 Redux 当中只是一些字符串常量。唯一修改的地方就是我给每个类型都加上了 `todos/` 前缀，以便于给这个模块创造一个命名空间。这就避免了跟应用中其他模块的名字发生冲突。

```
// todos/actionTypes.js
export const ADD = 'todos/ADD';
export const DELETE = 'todos/DELETE';
export const EDIT = 'todos/EDIT';
export const COMPLETE = 'todos/COMPLETE';
export const COMPLETE_ALL = 'todos/COMPLETE_ALL';;
export const CLEAR_COMPLETED = 'todos/CLEAR_COMPLETED';
```

> As for action creators, not much changes from the usual Redux application.

至于 action creators，跟往常的 Redux 应用没什么太大改变。
 
```
// todos/actions.js
import t from './actionTypes';

export const add = (text) => ({
  type: t.ADD,
  payload: { text }
});

// ...
```

> Note that I don’t necessarily need to use `addTodo` since I’m already in the todos module. In other modules I may use an action creator as follows.

注意到我并没有必要去使用 `addTodo`，因为我已经在这个 todos 模块里面了。在其他模块里我也就可以像下面这样使用一个 action creator。

```
import todos from 'todos';

// ...

todos.actions.add('Do that thing');
```
 
### Model

> The `model.js` file is where I like to keep things that are related to the module’s state.

这个 `model.js` 文件是我想要存放一些跟模块的状态相关的东西的地方。

> This is especially useful if you are using TypeScript or Flow.

如果你使用 TypeScript 或者 Flow 的话，这将会尤其有用。
 
```js
// todos/model.js
export type Todo = {
  id?: number;
  text: string;
  completed: boolean;
};

// This is the model of our module state (e.g. return type of the reducer)
export type State = Todo[];

// Some utility functions that operates on our model
export const filterCompleted = todos => todos.filter(t => t.completed);

export const filterActive = todos => todos.filter(t => !t.completed);
```
 
### Reducers

> For the reducers, each module should maintain their own state as before. However, there is one particular coupling that should be solved. That is, a module’s reducer does not usually get to choose where it is mounted in the overall application state atom.

对于 reducers 来说，每个模块都应该跟以前一样只维护自己的状态。但是这儿有一种特殊的耦合应当被解决，即一个模块的 reducer 通常不会去决定它在哪里被装载到整个应用状态原子当中。

> This is problematic, because it means our **module selectors** (which we will cover next) will be **indirectly coupled to the root reducer**. In turn, the module components will also be coupled to the root reducer.

这是不确定的，因为它意味着我们的**模块 selectors**（我们接下来会涉及到）将会**间接地耦合到根 reducer 当中**。反过来，整个模块的组件也将会被耦合到根 reducer 中来。

> We can solve this issue by giving control to the todos module on where it should be mounted in the state atom.

我们可以通过授权给 `todos` 模块来解决这个问题，让这个模块来决定应该在哪里被装载到状态原子。
 
```js
// rootReducer.js
import { combineReducers } from 'redux';
import todos from './todos';

export default combineReducers({
  [todos.constants.NAME]: todos.reducer
});
```
 
> This removes the coupling between our todos module and root reducer. Of course, you don’t *have* to do it this way. Other options include relying on naming conventions (e.g. todos module state is mounted under “todos” key in the state atom), or you can use module factory functions instead of relying on a static key.

这就可以移除我们的 `todos` 模块和根 reducer 之间的耦合。当然，你也*不一定*要通过这种方式。其他的选择也包括依赖命名约定（比如，将 `todos` 模块状态装载到使用 todos 作为 key 的状态原子底下），或者你也可以使用模块工厂函数而不是依赖于静态 key。

> And the reducer would look as follows.

然后 reducer 就可能长得跟下面一样。
 
``` js
// todos/reducer.js
import t from './actionTypes';
import { State } from './model';

const initialState: State = [{
  text: 'Use Redux',
  completed: false,
  id: 0
}];

export (state = initialState, action: any): State => {
  switch (action.type) {
    case t.ADD:
      return [
        // ...
      ];
    // ...
  }
};
```
 
### Selectors

> Selectors provide a way to query data from the module state. While they are not normally named as such in a Redux project, they are always present.

Selectors 提供了从模块状态中查询数据的一种方式。虽然它们不再像往常的 Redux 项目中所命名的那样，但是它们永远都是存在的。

> The first argument of connect is a selector in that it selects values out of the state atom, and returns an object representing a component’s props.

connect 的第一个参数就是一个 selector，从状态原子当中**选择**想要的值，并且返回一个对象表示为一个组件的 props。

> I would urge that common selectors by placed in the `selectors.js` file so they can not only be reused within the module, but potentially be used by other modules in the application.

我想要强烈建议将公共的 selectors 放到这个 `selectors.js` 文件当中，以便于它们既可以在这个模块里面被复用，也可能被应用的其他模块所用到。

> I highly recommend that you check out [reselect](https://github.com/reactjs/reselect) as it provides a way to build composable selectors that are automatically memoized.

我非常推荐你去看看 [reselect](https://github.com/reactjs/reselect)，因为它提供了一种方式，可以用来构建可组合的 selectors，并且能够自动 memoized。
 
```js
// todos/selectors.js
import { createSelector } from 'reselect';
import _ from 'lodash';
import { NAME } from './constants';
import { filterActive, filterCompleted } from './model';

export const getAll = state => state[NAME];

export const getCompleted = _.compose(filterCompleted, getAll);

export const getActive = _.compose(filterActive, getAll);

export const getCounts = createSelector(
  getAll,
  getCompleted,
  getActive,
  (allTodos, completedTodos, activeTodos) => ({
    all: allTodos.length,
    completed: completedTodos.length,
    active: activeTodos.length
  })
);
```
 
### Components

> And lastly, we have our React components. I encourage you to use shared selectors here as much as possible. It gives you the advantage of having an easy way to unit test the mapping of state to props without relying on component tests.

最后，我们有了自己的 React 组件。我建议你在组件当中尽可能地使用共享的 selectors。其中一个好处就是可以很轻松地对从 state 到 props 的 mapping 进行单元测试，而不用依赖于组件的测试。

> Here’s an example of a TODO list component.

这儿就有一个 TODO 列表组件的例子：

```
import { createStructuredSelector } from 'reselect';
import { getAll } from '../selectors';
import TodoItem from './TodoItem';

const TodoList = ({ todos }) => (
  <div>
    todos.map(t => <TodoItem todo={t}/>)
  </div>
);

export default connect(
  createStructuredSelector({
    todos: getAll
  })
)(TodoList);
```

> That’s it in terms of my recommendations. But before we go, there is one last topic I want to discuss: How to detect project smells.

这就是按照我所推荐规范的内容了。但是在我们结束之前，还有最后一个我想要讨论的主题：如何发现项目坏味道。
 
## Litmus test for project structure | 项目结构的石蕊测试

> It is important for us to have the tools to tell us when something smells in our code. From experience, just because a project starts out clean doesn’t mean it’ll stay that way. Thus, I want to present an easy method to detect project structure smells.

对我们来说，用于发现我们的代码坏味道的工具很重要。从经验上来看，仅仅因为一个项目从开始的时候很整洁，但这并不意味着它会一直如此。因此，我想要提出一种简单的方法用于发现项目结构的坏味道。

> Every once in a while, pick a module in your application and **try to extract it as an external module** (e.g. a NodeJS module, Ruby gem, etc). You don’t have to actually do it, but at least think it through. If you can perform this extraction without much effort then you know it is well factored. The term “effort” here remains undefined, so you need to come up with your own measure (whether subjective or objective).

每隔一段时间，从你的应用当中挑选一个模块，并且**尝试将它抽取成一个外部模块**（比如，一个 NodeJS 模块，Ruby gem 等等）。你不用实际这么去做，但至少像那样去思考。如果你不用花太多 efforts 就可以完成抽取，那么你就知道这个模块已经被很好得分解了。在这里的 “effort” 并没有被下定义，所以你还是需要自己去衡量（无论是主观或者客观）。

> Run this experiment with other modules in your application. Jot down any problems you find in your experiments: circular dependencies, modules breaching boundaries, etc.

在你的应用程序当中，跟其他模块一起试验一下。记下从实验当中所找到的任何问题：循环依赖，模块边界不清晰，等等。

> Whether you choose to take action based on your findings is up to you. Afterall, the software industry is all about tradeoffs. But at the very least it should give you a much better insight into your project structure.

基于你的发现，无论你选择采取何种操作都取决于你。毕竟，软件行业就是一个与折衷息息相关的行业。但至少这应该会让你对自己的项目结构有更深入的了解。
 
## Closing | 收尾

> Project structure isn’t a particularly exciting topic to discuss. It is, however, an important one.

项目结构并不是一个特别令人兴奋的话题讨论。然而，这又是非常重要的。

> The three rules presented in this post are:

这篇文章所描述的三条规则就是：

> 1. Organize by featues
> 2. Create strict module boundaries
> 3. Avoid circular dependencies

1. 基于特性组织
2. 设计严格的模块边界
3. 避免循环依赖
 
> Whether you are using Redux and React or not, I highly recommend following these rules on your software projects.

无论你是否正在使用 React 和 Redux，我都非常推荐你在自己的软件项目当中遵循这些规则。

