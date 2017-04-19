---
layout: post
title: 【译】React.js教程 第三部分：一个真实的React组件
categories: [翻译]
tags: [React]
published: True

---

技术系列笔记均已迁移至GitBook，更多`React`的内容请到：[http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html](http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_1.html)

# React.js Tutorial Part 3

原文地址：[http://www.joshfinnie.com/blog/reactjs-tutorial-part-3/](http://www.joshfinnie.com/blog/reactjs-tutorial-part-3/)

> Welcome to part 3 of my React.js/Express.js app tutorial. In this part we are going to actually take a deep dive into react and start hashing out the application's components. If you haven't already, please start the tutorial at [Part 1](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/)

欢迎来到React.js/Express.js教程的第三部分。在这一部分我们将深入React并构建应用组件。如果还没有开始，请从[第一部分](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/)开始。

## A React Component | 一个 React 组件

> From the [React Documentation](https://facebook.github.io/react/docs/why-react.html), "React is all about building reusable components. In fact, with React the only thing you do is build components. Since they're so encapsulated, components make code reuse, testing, and separation of concerns easy." This is what drew me to React in the first place, coming from [Angular.js](https://angularjs.org/) the idea of components spoke to me. It seemed like React's components were the next logical step in the progression of Javascript's MVCs. Here we are going to try our hardest to stay true to the definition of a React Component and try to truly encapsulate a single idea of our web application per React component. First, let's see what this means in regards to our job board web application.

根据[React文档](https://facebook.github.io/react/docs/why-react.html)所述：“React一切都是为了组件重用，事实上，使用React你唯一需要做的就是构建组件。由于封装性，组件使得代码具有可复用性，可测试性，并且易于分离。”这是React在最开始吸引我的地方，这在[Angular.js](https://angularjs.org/)中是从来没有的，看起来React组件是属于Javascript的MVCs模型的逻辑部分。我们将尽力保持React组件的定义，并尽量使web应用的每一个React组件都保持单一想法的封装性。首先，让我们看看这对于我们的「工作布告栏」程序意味着什么。

## The Job Component | Job 组件

> This first encapsulated part of our web application is going to be the job posting itself. Here we want to create a component that simply lists the information that we should have in an individual job post. To start, lets create a file for this react component and let's call it `Job.jsx` and put it in our `public/javascripts/scr/` folder:

第一个封装的模块就是工作的发布功能，首先新建一个组件，简单列出所有的发布信息。让我们为React组件新建一个`Job.jsx`文件，放到`public/javascripts/scr/`文件夹：

```js
var React = require('react');

module.exports = React.createClass({
    render: function() {
        return (
            <h1>Job Title</h1>
        )
    }
});
```

> This file might look surprisingly similar to our `HelloWorld.jsx` file and that is because it is! Of course we want to add some functionality to our `Job` component, but first let's get it hooked up into our application. To do this, we will need to modify our `app.jsx` file slightly to use the `Job` component instead of the `HelloWorld` component. To do this, modify the `app.jsx` file to read as the following:

这个文件看起来就跟之前的`HelloWorld.jsx`文件易于。当然我们需要为`Job`组件加上一些功能，当然首先需要连接到我们的应用。稍微修改一下`app.jsx`，将`HelloWorld`组件替换为`Job`组件。

```js
var $ = jQuery = require('../../libraries/jquery/dist/jquery');
var bootstrap = require('../../libraries/bootstrap-sass-official/assets/javascripts/bootstrap');
var React = require('react');
var HelloWorld = require('./Job.jsx');

React.render(
    <HelloWorld />,
    document.getElementById('job-post')
);
```

> **Please note** we also changed the HTML element we are attaching our React app to from `example` to `job-post` so make sure to adjust your `index.jade` file to match. Running `gulp` and then serving your application, you should see a header title of "Job Title" instead of our "Hello World" text from the last couple of tutorials. Now let's add some information to this component and really make it look like a job posting!

**请注意**，我们应该将HTML元素从`example`改成`job-post`，所以确保`index.jade`能够对应上。运行`gulp`然后启动应用，你可以看到标题从前两个教程中的"Hello World"变成了"Job Title"。选择让我们为这个添加一些信息，使之更像一个工作公告。

### Adding Information to our Component | 为我们的组件添加信息

> To add some useful information to our `Job` component, we want to create an "initial state" for the component. This over simplifies the task of getting data into your component, but it will work for us right now. In the `Job.jsx` file, we want to create a function called `getInitialState` and return a dictionary with the information we want our component to start with. Once we do that, we want to change our rendering element to use the initialized state. Below you will see what changes we made to `Job.jsx` to accomplish this:

为了给我们的`Job`组件添加一些有用信息，我们需要为组件新建一个“初始状态”。这是在简化组件获取数据的任务，但是现在它为我们所用。在`Job.jsx`这个文件，我们新建一个`getInitialState`函数，然后返回一个字典，其中包括我们想要组件在最开始时所需要的一些信息。一旦我们完成这些，我们就可以使用初始state数据来改变渲染的原色。从以下的内容可以看到我们对`Job.jsx`所做的修改：

```js
var React = require('react');

module.exports = React.createClass({
    getInitialState: function() {
        return {
            company: 'TrackMaven',
            position: 'Software Maven',
            local: 'Washington, DC, USA',
            lookingFor: 'Angular.js, Django, ElasticSearch',
            postedDate: '4 April 2015',
            description: '',
            category: 'Engineer'
        };
    },

    render: function() {
        return (
            <div>
                <h2 class="listing-company">
                    <span class="listing-company-name">{ this.state.company }</span>
                    <span class="listing-location">{ this.state.local }</span>
                </h2>
                <span class="listing-job-type">Looking for: { this.state.lookingFor }</span>
                <span class="listing-posted">Posted: { this.state.postedDate }</span>
                <span class="listing-company-category">{ this.state.category }</span>
            </div>
        );
    }
});
```

> Note that with the `getInitialState` function, the `render` function now has access to a useful state. We can cycle through the state to render the data in our app. Our web application should now look like this:

可以注意到，通过`getInitialState`这个方法，`render`方法就操作一些有用的state数据。我们可以在app中循环使用state来渲染数据。现在的web应用：

![](http://www.joshfinnie.com/assets/images/blog/filled-out-job-component.png)

### Adding More Components (Components within Components) | 添加更多组件（组件含组件）

> Having a job posting is great and all, but we are not doing all this work to just post a single job. We need a way to iterate through a list of jobs and render many `Job` components. This isn't as hard as it sounds, we first need to create another component, though. Let's call this component `Jobs` since it's going to create many `Job` components. To keep our codebase as clean as possible, we are going to create another file to hold our `Jobs` component; we are going to call it `Jobs.jsx`.

有一个工作发布模块看起非常好，但是我们现在只能够显示发布的一条工作信息，还没有完成所有代码。我们需要在`Job`组件中迭代显示所有的工作信息。这不像听起来那么难，我们只需要另外新建一个组件。我们称之为`Jobs`组件，因为它将创建很多个`Job`组件。为了尽可能保持代码整洁，我们会新建一个`Jobs.jsx`文件来存放`Jobs`组件。

> In the `Jobs` component, we are going to map all the jobs to individual `Job` components, but for this part of the tutorial, we are still going to hard-code the data. First, we want to create an "initial state" that is going to mirror our future API call. This is done through the `getInitialState` function in our `Jobs` component. Looping over this data to render many components is easy in React.js, but not all that intuitive. We want to use the `map()` function in Javascript to map each "job" to the `Job component`. Below is what the final `Jobs.jsx` file looks like:

在`Jobs`组件中，我们map出所有单独的`Job`组件。但是在教程的这个部分，我们依然会很难为数据编程。首先，我们要新建“初始化state数据”，看起来就像我们将来的API形式。为`Jobs`组件添加`getInitialState`方法，在React.js中循环渲染很多组件很容易，但也不完全靠直觉。我们想要在JavaScript中使用`map()`函数map将每一个"job"渲染到`Job`组件。以下是最终的`Jobs.jsx`：

```js
var React = require('react');
var Job = require('./Job.jsx');

module.exports = React.createClass({
    getInitialState: function() {
        // This will be an API call eventually...
        return {
            data: [
                {
                    company: 'TrackMaven',
                    position: 'Software Maven',
                    local: 'Washington, DC, USA',
                    lookingFor: 'Angular.js, Django, ElasticSearch',
                    postedDate: '4 April 2015',
                    description: '',
                    category: 'Engineering'
                },
                {
                    company: 'TrackMaven',
                    position: 'Junior Software Maven',
                    local: 'Washington, DC, USA',
                    lookingFor: 'Javascript, Python',
                    postedDate: '4 April 2015',
                    description: '',
                    category: 'Engineering'
                }
            ]
        };
    },
    render: function(){
        return (
            <div className="list-group">
                {this.state.data.map(function(job){
                    return (
                        <Job
                            company={job.company}
                            position={job.position}
                            local={job.local}
                            lookingFor={job.lookingFor}
                            postedDate={job.postedDate}
                            description={job.description}
                            category={job.category}
                        />
                    )
                })}
            </div>
        )
    }
});
```

> This allows us to clean up the `Job` component a little bit, most importantly switching from using `state` to `props` since we are now passing in the data to the `Job` component and not using our `getInitialState` function. Most of this is the same, but we made some small changes to the return function. First note the change from `class` to `className` due to some issue with React.js and how it handles the `class` namespace. Second, note we got rid of the `getInitialState` function since we now pass in the data through our `Jobs` component.

这样使我们保证`Job`组件的整洁性，最重要的变化是将`state`换成了`props`，因为我们需要将数据传递到`Job`组件，而不是使用`getInitialState`方法。大部分都是一样的，但是我们在`return`方法中需要做出一点改变。首先，注意到`class`换成了`className`，这是由于React.js的一些issue，因为这涉及到`class`的命名空间。第二，注意到我们不需要`getInitialState`方法了，因为我们现在是从`Jobs`组件中拿到的数据。

```js
var React = require('react');

module.exports = React.createClass({
    render: function() {
        return (
            <a href="#" className="list-group-item">
                <h4 class="list-group-item-heading listing-company">
                    <span className="listing-position-name">{ this.props.position }</span>
                    <small className="listing-company-name">{ this.props.company }</small>
                    <small className="listing-location">{ this.props.local }</small>
                </h4>
                <p className="list-group-item-text">
                    <span className="listing-job-type">Looking for: { this.props.lookingFor }</span>
                </p>
                <p className="list-group-item-text">
                    <span className="listing-posted">Posted: { this.props.postedDate }</span>
                    <span className="listing-company-category">{ this.props.category }</span>
                </p>
            </a>
        );
    }
});
```

> Next let's add some simple SCSS in our `public/stylesheets/scss/style.scss` file to make our application look a little better. Below is all the SCSS I have added:

接下来让我们在`public/stylesheets/scss/style.scss`文件中添加一些简单的SCSS，这会使我们的应用看起来更漂亮一些。如下所示：

```css
@import "../../libraries/bootstrap-sass-official/assets/stylesheets/bootstrap";

body {
  padding: 50px;
  font: 14px "Lucida Grande", Helvetica, Arial, sans-serif;
}

a {
  color: #00B7FF;
}

#jobs {
    padding-top: 10px;
}

.listing-location {
  float: right;
}

.listing-company-name {
  margin-left: 10px;
}

.listing-company-category {
  float: right;
}
```

> And now looking at it all put together, we now have something that looks like this!

现在所有东西都放在一起，看起来就是这样：

![](http://www.joshfinnie.com/assets/images/blog/cssed-jobs-component.png)

## Conclusion | 结论

> In this tutorial we went through how to create a real component and how to loop over that component with data. Our application is looking more and more like a real web app! Next time we will work through how we are going to build out our Express.js app to return some JSON jobs data and how we can make our React.js app talk to that API. See you then!

在本次教程中，我们学习了如何创建一个真实的React组件和如何循环渲染组件并且传递数据。我们的应用看起来越来越像一个web应用！下一次我们会继续学习如何构建Express.js应用来返回JSON格式的工作信息数据，以及React.js应用如何与API进行交互。See you then！


