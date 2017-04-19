---
layout: post
title: 【译】一种更好的 React/Redux 应用程序的文件目录结构
categories: [翻译]
tags: [React, Redux, Test, FED, DX]
published: True

---

原文地址: <http://marmelab.com/blog/2015/12/17/react-directory-structure.html>

> Most of the examples I could find about React/Redux applications (either client side or universal) are very simple. They choose to organize files by *nature* (action, component, container, reducer). The result is a directory structure looking like the following:

我所能找到的大部分有关 React/Redux 应用的示例都非常简单（不论客户端或者同构方案）。它们都选择根据*功能属性*（action，component，container，reducer）来组织文件。结果目录结构就会如下所示：

```bash
actions/
    CommandActions.js
    UserActions.js
components/
    Header.js
    Sidebar.js
    Command.js
    CommandList.js
    CommandItem.js
    CommandHelper.js
    User.js
    UserProfile.js
    UserAvatar.js
containers/
    App.js
    Command.js
    User.js
reducers/
    index.js
    command.js
    user.js
routes.js
```

> The [Redux Book](http://redux.js.org/docs/advanced/ExampleRedditAPI.html) follows this convention, and I know at least two Redux boilerplate repositories following it, too: [3ree](https://github.com/GordyD/3ree), and [react-redux-universal-hot-example](https://github.com/erikras/react-redux-universal-hot-example).

这本 [Redux Book](http://redux.js.org/docs/advanced/ExampleRedditAPI.html) 也遵循了这一惯例，而且我已知的两个 Redux 样板文件仓库都是这样的：[3ree](https://github.com/GordyD/3ree) 和 [react-redux-universal-hot-example](https://github.com/erikras/react-redux-universal-hot-example)。

> That’s nice, but what happens when I need to add code about a new domain, including actions, components, and a reducer? For instance, if I want to deal with a catalog of products, I need to add files in all of these directories, ending with:

这是很不错，但要是我需要新增一个 Domain，然后同时添加 actions, components 和 reducer 有关的代码，这个时候该怎么办呢？举例来说，如果我需要处理一个产品目录，那么我就需要在所有的文件夹中添加这么些个文件，然后目录结构就变成了这样：
 
```bash
actions/
    CommandActions.js
    ProductActions.js   <= Here
    UserActions.js
components/
    Header.js
    Sidebar.js
    Command.js
    CommandList.js
    CommandItem.js
    CommandHelper.js
    Product.js          <= Here
    ProductList.js      <= Here
    ProductItem.js      <= Here
    ProductImage.js     <= Here
    User.js
    UserProfile.js
    UserAvatar.js
containers/
    App.js
    Command.js
    Product.js          <= Here
    User.js
reducers/
    index.js
    foo.js
    bar.js
    product.js          <= Here
routes.js
```

> You see where this is going. Fast forward two months from now, and the `components/` directory contains dozens of files, and I need to open 4 files in 4 different directories each time I touch a single feature.

你应该知道事情下一步会怎么发展了。过去两个月到现在，`components/` 目录下面就包含了大量文件，而且每当我修改某个特性的时候，却需要在四个不同目录下打开四个文件。

> Why not group files by *domain* instead? To make the difference between actions, components, and reducers, I can still use a file suffix:

为什么就不能通过 *domain* 来组织文件呢？我依然可以使用文件后缀来区分 actions，components 和 reducers：
 
``` bash
app/
    Header.js
    Sidebar.js
    App.js
    reducers.js
    routes.js
command/
    Command.js
    CommandContainer.js
    CommandActions.js
    CommandList.js
    CommandItem.js
    CommandHelper.js
    commandReducer.js
product/
    Product.js
    ProductContainer.js
    ProductActions.js
    ProductList.js
    ProductItem.js
    ProductImage.js
    productReducer.js
user/
    User.js
    UserContainer.js
    UserActions.js
    UserProfile.js
    UserAvatar.js
    userReducer.js
```
 
> I can make things even a little easier to read by merging a container and the related component. Redux makes the difference between *containers*, which are connected to the state, and *components*, which are dumb and stateless. Most tutorials reflect this difference with two separate files:

通过合并容器和相关组件还可以让代码变得更加易读。Redux 将连接状态的*容器*和无状态的哑巴*组件*区分开来。大部分教程都使用两个独立的文件来反映了这种区别：
 
```jsx
// in Product.js
export default function Product({ name, description }) {
    return <div>
        <h1>{ name }</h1>
        <div className="description">
            {description}
        </div>
    </div>
}

// in ProductContainer.js
import { bindActionCreators } from 'redux';
import { connect } from 'react-redux';
import * as ProductActions from './ProductActions';
import Product from './Product';

function mapStateToProps(state) {
    return {...state};
}

function mapDispatchToProps(dispatch) {
    return bindActionCreators({
        ...ProductActions,
    }, dispatch);
}

export default connect(mapStateToProps, mapDispatchToProps)(Product);
```

> The only practical interest to separate component and container is to facilitate the unit tests of the component (without using Redux at all). In 99% of the cases, the component is never used outside of the container. Well, ES6 allows to export more than one element, right? Then I can merge those two scripts into a single file, where the export default is the container, and export Product is the component:

区分组件和容器的唯一一个实际好处就是有利于组件的单元测试（根本无需 Redux）。99% 的情况下，这个组件都不会在容器以外的地方被用到。那么，ES6 允许一个文件不止导出一个元素对吧？然后我就可以把这两部分代码合并到一个文件里，并且默认导出的是容器，而 Production 则导出作为组件：
 
```jsx
// in Product.js
import { bindActionCreators } from 'redux';
import { connect } from 'react-redux';
import * as ProductActions from './ProductActions';

// component part
export function Product({ name, description }) {
    return <div>
        <h1>{ name }</h1>
        <div className="description">
            {description}
        </div>
    </div>
}

// container part
function mapStateToProps(state) {
    return {...state};
}

function mapDispatchToProps(dispatch) {
    return bindActionCreators({
        ...ProductActions,
    }, dispatch);
}

export default connect(mapStateToProps, mapDispatchToProps)(Product);
```

> That way, a unit test on the component can simply `import { Product } from './Product.js'`. Now the directory structure counts one less file per directory:

这样的话，组件中的单元测试就可以轻松地 `import { Product } from './Product.js'`。现在每个目录结构里就少了一个文件：
 
```bash
app/
    Header.js
    Sidebar.js
    App.js
    reducers.js
    routes.js
command/
    Command.js         // component & container
    CommandActions.js
    CommandList.js
    CommandItem.js
    CommandHelper.js
    commandReducer.js
product/
    Product.js         // component & container
    ProductActions.js
    ProductList.js
    ProductItem.js
    ProductImage.js
    productReducer.js
user/
    User.js            // component & container
    UserActions.js
    UserProfile.js
    UserAvatar.js
    userReducer.js
```
  
> And while we’re talking about tests, they usually live in their own `test/` directory, far from the runtime code:

当我们谈论测试的时候，他们通常都位于自己的 `test/` 目录，并且远离运行时代码：
 
```bash
src/
    app/
        Header.js
        Sidebar.js
        App.js
        reducers.js
        routes.js
    command/
        Command.js
        CommandActions.js
        CommandList.js
        CommandItem.js
        CommandHelper.js
        commandReducer.js
    product/
        Product.js
        ProductActions.js
        ProductList.js
        ProductItem.js
        ProductImage.js
        productReducer.js
    user/
        User.js
        UserActions.js
        UserProfile.js
        UserAvatar.js
        userReducer.js
test/
    app/
        Header.js
        Sidebar.js
        App.js
        reducers.js
        routes.js
    command/
        Command.js
        CommandActions.js
        CommandList.js
        CommandItem.js
        CommandHelper.js
        commandReducer.js
    product/
        Product.js
        ProductActions.js
        ProductList.js
        ProductItem.js
        ProductImage.js
        productReducer.js
    user/
        User.js
        UserActions.js
        UserProfile.js
        UserAvatar.js
        userReducer.js
```
 
> I find it harder to spot missing tests for components, or to navigate the file structure once the domain expands. So I try to keep tests in the same directory as the element they test - simply using a `-spec.js` suffix. If this were Python, tests would even be in the same file! All the scripts related to a bounded context, including tests, are now grouped in a single directory - easy to read and reason about.

我就发现这很难去定位那些缺失测试的组件，而且一旦 Domain 扩展过后就很难在文件结构之间进行导航了。所以我尝试将测试和被测试的元素放到同一个文件夹底下 —— 简单地使用一个 `-spec.js` 后缀。如果是 Python 的话，测试甚至就在同一个文件里面！所有相关的代码都处于同一边界的上下文之中，包括测试在内都被组织到同一个目录里 —— 易于阅读和理解。
 
```bash
src/
    app/
        Header.js
        Header-spec.js
        Sidebar.js
        Sidebar-spec.js
        App.js
        App-spec.js
        reducers.js
        reducers-spec.js
        routes.js
        routes-spec.js
    command/
        Command.js
        Commands-spec.js
        CommandActions.js
        CommandActions-spec.js
        CommandList.js
        CommandList-spec.js
        CommandItem.js
        CommandItem-spec.js
        CommandHelper.js
        CommandHelper-spec.js
        commandReducer.js
        commandReducer-spec.js
    product/
        Product.js
        Product-spec.js
        ProductActions.js
        ProductActions-spec.js
        ProductList.js
        ProductList-spec.js
        ProductItem.js
        ProductItem-spec.js
        ProductImage.js
        ProductImage-spec.js
        productReducer.js
        productReducer-spec.js
    user/
        User.js
        User-spec.js
        UserActions.js
        UserActions-spec.js
        UserProfile.js
        UserProfile-spec.js
        UserAvatar.js
        UserAvatar-spec.js
        userReducer.js
        userReducer-spec.js
```

> Configuring the test runner (either Jest or Mocha) is easy: just make it run the tests in ./src/**/*-spec.js.

配置测试启动器（比如 Jest 或者 Mocha）也很容易：只需要让它跑一下 `./src/**/*-spec.js` 测试即可。

> This directory structure grows well with the project size. And when it’s time to split an app into independent repos to ease reusability across projects, then the code refactoring is really lightweight. I highly recommend it!

这种目录结构对于项目大小的增长特别友好。而且，当为了项目间灵活的复用性而将一个应用拆分成独立代码库的时候，代码重构就会变得非常轻量级。我强烈推荐这种方式！

> **Edit**: It seems the Reddit community heard about this post; the discussion continues there: [https://www.reddit.com/r/reactjs/comments/47mwdd/a\_better\_file\_structure\_for\_reactredux/](https://www.reddit.com/r/reactjs/comments/47mwdd/a_better_file_structure_for_reactredux/).

**编辑**：看来是 Reddit 社区已经注意到了这篇文章；进一步的讨论在这里：[https://www.reddit.com/r/reactjs/comments/47mwdd/a\_better\_file\_structure\_for\_reactredux/](https://www.reddit.com/r/reactjs/comments/47mwdd/a_better_file_structure_for_reactredux/)。
