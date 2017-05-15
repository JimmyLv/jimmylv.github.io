---
layout: session
title: Rethink AngularJS in Action
categories: [演讲]
tags: [AngularJS, Rethink, Summary]
speaker: Jimmy Lv
transition: move
theme: green
published: True
---

30 min = 15 min * 2

[slide]
# 「Done is better than perfect.」

[slide]
# Angular in Action
<small>by Jimmy Lv</small>

[slide]

## MVVM: 双向绑定

<iframe id="preview" style="height: 600px;" frameborder="0" width="100%" height="100%"
        src="https://laracasts.com/series/learning-vue-step-by-step/episodes/1">
</iframe>

> 很讽刺的是，需要使用 Vue 来演示 AngularJS 的 MVVM 概念，需要 React 来演示 Component，以及单向数据流。

[slide]

## Template&Directive

基于DOM <=> Vitural DOM

ng-controller="MainCtrl as main"

content Editable

[slide]

## Model&View Data binding

"single-source-of-truth" 其实只需要关注data，易测试，灵活性高

双向数据绑定，dirty check -> $watch -> 影响性能

View 和 Model 应该分开? 

React: 数据只会由parent流向children，只会由逻辑流向页面，更好理解和维护。

onChange={this.handleChange.bind(this, "pass")} in React

[slide]

## Dependency Injection

动态语言、ES5没有包管理/注入？ -> Angular module -> ES6 or RequireJS

[slide]

## 学习曲线

最开始只要Controller&Directive就实现了hello world

但是一旦深入，就必须接受一大堆Angular自创术语

[slide]

## module

<div ng-app="app">

```
<div ng-controller="MainCtrl">
    <p>{{ message }}</p>
</div>
```

</div>
angular.module('app', []);
angular.module('app').controller('MainCtrl', function ($scope){

```
$scope.message = 'hello';
```

});

[slide]

## Controller

to expose data to our view via $scope & add functions to $scope

nested or multiple nested controllers 可以继承，每 ng-controller 指令会创建新的子级 scope，三层div结构，也就对应有三层 scope 继承关系的层级结构 

不要操作具体的DOM和filter等其他事情，专注单个view的业务逻辑

Presentation logic should remain within views and directives.

相互间操作使用Service（across app/module），再注入controller

old? > controller as syntax : -> this = self . create a reference to this so that we don't lose context of our controller when we create/call functions within our controller.

[slide]

## $scope

不显式注入$scope了，语法是这样：

```
function CtrlB() {
  this.a = 1;
  this.foo = function() {
  };
}

<div ng-controller="CtrlB as instanceB"></div>
```

在任意一个已有的作用域上调用$new()，就能创建一个新的作用域：

var newScope = scope.$new();
刚创建出来的作用域是一个“悬空”的作用域，也就是说，它跟任何界面模板都不存在绑定关系，创建它的作用域会成为它的$parent。这种作用域可以经过$compile阶段，与某视图模板进行融合。

[slide]

## Service

to share data 

singletons that can be injected into controllers and other services: reusable

like $http

最明显的DI体现

Lazily instantiated:  not registering a service instance, but rather a factory function ->  angular.module('myModule', []).factory('serviceId',

[slide]

## Test

Controller的数据测试，

Jasmine spy (mock) a real browser alert.

[slide]

## Form

{{}} 只支持一部分js表达式，支持三元

angular.copy(user)

form 可以直接用css

[slide]

## Promise $q

Deferred:

$q.defer()  resolve(), reject(), and notify()

$q(function(resolve, reject) {

```
  $timeout(function() {
    if(Math.round(Math.random())) {
      resolve('data received!')
    } else {
      reject('oh no an error! try again')
    }
  }, 2000)
```

Promise:

then().then().finally()

catch(errorCallback) – shorthand for promise.then(null, errorCallback)

$http - success() error()

[slide]

## Filters

Chaining built-in filters: `<p ng-repeat="person in test.people | filter:search | orderBy:'name'  | limitTo: 5">`

[slide]

## Directive

add things like behaviors: 

- "A" is for attribute `<div welcome></div>` (default restrict property）
- "E" is for element `<welcome></welcome>`
- "C" is for class ` <div class="welcome"></div>`
- "M" for comment `<!-- directive: welcome -->`

functionalities:

addClass() removeClass()

```
<div entering="activeClass"></div>
function(scope, element, attrs) {
  element.bind("mouseenter", function(){
    element.addClass(attrs.entering);
  })
}
```

can be used in controller

[slide]

## $Route

```
$routeProvider.when("/:firstName/:middleName/:lastName",
    {
      templateUrl: "app.html",
      controller: "AppCtrl",
      controllerAs: "app"
    }
  );
```

$routeParams.firstName + " " + $routeParams.middleName + " " + $routeParams.lastName;

[slide]

## MindMap

http://www.xmind.net/m/xDmL