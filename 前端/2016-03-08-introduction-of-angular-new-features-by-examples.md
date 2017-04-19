---
layout: post
title: 升级 AngularJS 1.5：新特性对比与最佳实践
categories: [前端]
tags: [AngularJS, JavaScript]
published: True

---


## 图谋不轨：帮助（~~勾引~~）开发者过渡到 Angular 2.0

私以为，本次更新最重要的两个部分就是 `angular.component()` 方法和支持了 Multi-slot 的 transclusion：

- 组件与 **`angular.component()`** 方法：

首先最大的一个变化就是引入了组件的概念，并新增了 `angular.component()` 方法。经过这么长时间的摸爬滚打，Angular 社区乃至整个前端领域也慢慢地总结出了符合实际项目开发的最佳实践，其中最大的一个共识就是组件化，在 Angular 1.x 中我们就已经可以通过元素指令的方式定义可复用的组件，而其实 Components 就是一种特别的元素指令，通过自定义的 HTML 元素将之激活。

本次更新的 `.component()` 方法其实就是一种更加方便定义元素指令的方式，并自带默认配置使之符合最佳实践。而组件开发的方式也就使应用更加符合 [Angular 2.0](http://www.angular.io/) 的架构风格，所以说，Angular 1.5 就是为了方便开发者能够更加顺利地过渡到 Angular 2.0。为了 Angular 2.0 的未来 Google 也是迫不得已啊，要知道很多前端开发者在经历过 Angular 1.x 的「折磨」过后都转投了其他框架的怀抱。可以说前有 [React.js](https://github.com/facebook/react) 携着组件化，虚拟 DOM ，单向数据流等利器，给前端 UI 构建掀起了一波声势浩大的函数式新潮流；后有 [Vue.js](http://vuejs.org/) 等更轻便的 MVVM 框架穷追猛赶，据说用过 Vue 的开发者都一致叫好。

![](//o7mw3gkkh.qnssl.com//images/2016/1466241519959.png)

- 终于支持了 **Multi-slot transclusion**：

在之前，使用 Directive 定义组件的时候老是感觉有点儿憋屈，我们的组件只有一个 transclusion 也就是说只能在一个地方被填充，这就完全限制乃至丧失了组件的模板自定义功能。在构建复杂组件元素的时候，也就需要更多类似于 `ng-if` 和 `ng-switch` 等方式辅助，从而导致组件模板的样板文件越来越多。而 **Multi-slot transclusion** 则可以把自定义的主动权交出去，我并不需要知道这个地方会变成什么样，我只需要告诉你这个地方能够被填充就好了。当然，新版本也支持了默认的 transclusion 内容，这也就让配置组件模板的成本进一步降低了。

## 举个栗子：`angular.component()`

需要说明的就是，没有什么事是 Component 能做而 Directive 不能够做的，下面就来看个对比的例子：

    <my-component first-name="'Alan'" last-name="'Rickman'"></my-component>

    myModule.component('myComponent', {
      template: '<h1>Hello {{ $ctrl.getFullName() }}</h1>',
      bindings: { 
        firstName: '<', 
        lastName: '<' 
      },
      controller: function() {
        this.getFullName = function() {
          return this.firstName + ' ' + this.lastName;
        };
      }
    });


    myModule.directive('myComponent', function() {
        return {
            restrict: 'E',
            template: '<h1>Hello {{ ctrl.getFullName() }}</h1>',
            scope: {},
            bindToController: { 
                firstName: '<', 
                lastName: '<' 
            },
            controller: function() {
                this.getFullName = function() {
                    return this.firstName + ' ' + this.lastName;
                };
            },
            controllerAs: 'ctrl'
        }
    )};

通过 `.component()` 方法定义的组件默认就是一个元素组件，并且拥有自己的独立 Scope。与此同时使用 `bindings` 替代了 `bindToController`，并且可以通过 '<' 符号单向绑定一个变量，即只有父 Scope 的变化会影响子 Scope 的值，这样也就避免了一些 Scope 黑魔法所造成的误伤。还有比较重要的就是，组件拥有默认为空的 Controller 方法，并且不需要 `controllerAs` 语法就可以在模板中直接使用默认的 `$ctrl` 别名。更多详细对比请看[官方文档](https://docs.angularjs.org/guide/component)。

### 新的 `$onInit()` 生命周期

新加入 AngularJS 豪华午餐的 `$onInit()` 方法，其实就 相当于 React 组件的 [`componentDidMount()`](https://facebook.github.io/react/docs/component-specs.html#lifecycle-methods) 方法，在组件内 Controller 初始化的时候统一加载数据。其实这种方式在之前的版本当中，已经被约定俗成作为一种最佳实践了，可以参考 [johnpapa/angular-styleguide](https://github.com/johnpapa/angular-styleguide) 中所提到的 [`activate()`](https://github.com/johnpapa/angular-styleguide/blob/master/a1%2Fi18n%2Fzh-CN.md#controller-activation-promises) 方法。只不过 AngularJS 1.5 进一步提供了官方的支持，`$onInit()` 方法会在组件及其所有 binding 初始化之后被 compiler 调用，从而我们就有了一个清晰的地方统一存放数据初始化的逻辑。

    controller: function ($location, githubService) {
      'ngInject';

      var vm = this;
      
      vm.$onInit = function () {
        githubService.getConfig().then(res =>
          vm.config = res.data
        );
        githubService.getIndex().then(res =>
          vm.posts = res.data.paginator
        );
      };
    }

当然，这也更加便于用户向  Angular 2.0 迁移，如果你对 Angular 2.0 的[生命周期](https://angular.io/docs/ts/latest/guide/lifecycle-hooks.html)有所了解的话，这里的 `$onInit()` 其实就等同于 `ngOnInit` 函数。

### ControllerAs 语法是什么鬼？

AngularJS 在早些版本引入了 `controllerAs` 语法，相当于给 ViewModel 定义了一个命名空间，从而避免了不同层级 Scope 关系的混淆不清。并且，`controllerAs`语法也更加从语法层面上体现了 Controller 初始化 ViewModel 数据的单一职责，若把 `as` 看做面向对象编程当中的 `new`，其实就相当于将 Controller 这个 Function() 进行实例化，从而我们就拥有了 ViewModel 这么一个可以在模板当中直接使用的对象。而其实现原理，则是直接把这个对象再次挂在当前 Controller 所对应的 $scope 之上，可以试着在 `link` 方法里边儿判断一下 `$ctrl === $scope.vm`，其结果为 `true`。

    <div ng-controller="MainCtrl as main">
        <my-component 
            first-name="'Alan'" 
            last-name="'Rickman'" 
            name="main.name">
        </my-component>
    </div>

    myModule.controller('MainCtrl', function () {
      this.name = 'JimmyLv';
    });

![](//o7mw3gkkh.qnssl.com//images/2016/1466241548419.png)

但与此同时，在指令使用 `controllerAs` 语法也会遇到问题：

    myModule.directive('myComponent', {
      restrict: 'E',
      template: '<h1>Hello {{ ctrl.getFullName() }} to {{ ctrl.name }}</h1>',
      scope: {
        firstName: '@', 
        lastName: '<',
        name: '='
      },
      controller: function($scope) {
        this.getFullName = function() {
          return this.firstName + ' ' + this.lastName;
        };
          this.name = 'Pascal';
          $scope.$watch('name', function (newValue) {
            this.name = newValue;
          }.bind(this));
      },
      controllerAs: 'ctrl'
    });

当某一个变量需要双向绑定的时候，我们不得已重新使用只有挂载在 $scope 底下的 `$watch()` 方法来动态监测这个值在指令当中是否发生了改变，好不容易消失的 $scope 又出来丢人现眼了。也就是因为这个原因，Angular 又加入新的 `bindToController` 语法，从字面上就很容易看懂它的意思，即将这个变量直接绑定到指令自带的 Controller，从而也就不用 `$watch()` 方法了，至此，彻底摆脱了 $scope。

### 再论 Scope 黑魔法

在 AngularJS 当中，Scope 可以说是最难理解也是最强大的一部分，在没有理解其背后原理的时候感觉处处都是坑，理解过后又觉得 Angular 恰恰因此而获得了 JavaScript 原型继承的强大力量。首先，子 Scope 总是会自动继承自父 Scope，一切的源头就是所谓的 `$rootScope`，试着把它在 console 里面打印出来，可以看到其 `$id` 为 1，之后的所有子 Scope `$id` 依次增加。

回到正题，我们来看看指令当中的 Scope，对于指令来说会有三种情况：

- `scope: false` —— 定义指令时 `.directive()` 的默认设置，此时不会创建子 Scope，将会直接共享父 Scope，所以说没有理解的时候就可能出现莫名其妙改变了上一层 Scope 当中某个值的情况。
- `scope: { ... }` —— 创建新的「独立」 Scope，但是不会继承父 Scope，当需要传入某些值的时候，只需要在花括号当中写入该变量名称以及绑定方式即可，1.5 新版本增加了单向绑定，所以共有四种方式：'@'、'<'、'='、'&'，而这在 `.component()` 创建组件的时候是默认的，Scope 永远都是隔离的，通过绑定变量和方法的方式定义组件的输入输出，这一点之后会提到。
- `scope: true` —— 创建新的「独立」 Scope 并且继承自父 Scope，所以说能够在 Directive 当中访问到所有父 Scope 当中的值。其原理需要大家去理解一下 JavaScript 的原型链，就能够明白 Angular 是如何一层层往上查找并获得该变量的值了。

### （理想的）组件树

理想情况下，整个 Web 应用就是一颗组件树，并且每个组件都有着非常的输入输出，数据流从根部扩散至每个部分，很少会出现双向绑定的情况。通过这种方式，就可以很容易预测数据的改变会如何影响到 UI 组件的状态改变。

- **组件只能控制自身的输入输出**：组件绝不应该修改不属于自身 Scope 的任何数据和 DOM。通常来说，Angular 通过 Scope 继承的方式提供了随时随处可修改数据的能力。但其实，当修改数据职责不清晰的时候就会导致问题，这也就是为什么组件指令要默认使用独立 Scope，从而避免了跨 Scope 操作的可能，

- **组件应该拥有清晰的公共API - Inputs 和 Outputs**：隔离 Scope 的方式也难以避免 Angular 的双向绑定，如果你通过 `bindings: {item: '='}` 这种方式将一个对象传入组件，你依然可以改变父组件当中的属性。所以说，组件应该只能修改属于它自己的数据，这样的话就很容易控制什么时候要进行修改，以及为什么要修改。所以说纯粹的组件 Inputs 应该只使用 '<' 和 '@' 单向数据绑定，而 Outputs 应当通过 '&' 进行函数方法的绑定，作为组件内事件的 callbacks。
 
比如说一个删除操作，组件不再直接操作输入的数据，而是去调用正确的 Outputs 事件来改变数据，这就意味着组件不会删除数据本身，而是通过事件的形式将其返回到拥有该数据的组件当中。

    <button ng-click="$ctrl.onDelete({hero: $ctrl.hero})">Delete</button>

通过这种方式，父组件就可以根据这个事件再来决定最终的操作，比如说彻底删除该项数据，或者只是更新自己的属性而已。

    ctrl.deleteHero(hero) {
      $http.delete(...).then(function() {
        var idx = ctrl.list.indexOf(hero);
        if (idx >= 0) {
          ctrl.list.splice(idx, 1);
        }
      });
    }

### ngRoute 路由的 `$resolve`

我们都知道，Controller 应该保持初始化 ViewModel 的单一职责，不应该把数据获取的逻辑放入 Controller，所以说在进入 Controller 之前数据就应该已经准备好了。最通常的办法就是将数据在 Route 的时候就 Resolve 出来，而 ngRoute 也提供了非常方便的方式来获取 `$resolve` 当中的数据并将其传入组件。

    var myMod = angular.module('myMod', ['ngRoute']);
    myMod.component('home', {
      template: '<h1>Home</h1><p>Hello, {{ $ctrl.user.name }} !</p>',
      bindings: {
        user: '<'
      }
    });
    myMod.config(function($routeProvider) {
      $routeProvider.when('/', {
        template: '<home user="$resolve.user"></home>',
        resolve: {
          user: function($http) { return $http.get('...'); }
        }
      });
    });

## 多个 slot 的 Transclusion

通过 `transclude: {...}` 的方式就可以直接定义支持多个 slot 的 transclusion，而以往我们只能设置 `transclude: true` 而且只能定义一个 transclusion。

    myMod
    .controller('ExampleController', ['$scope', function($scope) {
        $scope.title = 'Lorem Ipsum';
        $scope.link = 'https://google.com';
        $scope.text = 'Neque porro quisquam est qui dolorem ipsum quia dolor...';
      }]
    )
    .directive('pane', function(){
        return {
          restrict: 'E',
          transclude: {
            'title': '?paneTitle',
            'body': 'paneBody',
            'footer': '?paneFooter'
          },
          template: '<div ng-transclude="title">Fallback Title</div>' + 
                    '<p ng-transclude="body"></p>' + 
                    '<div ng-transclude="footer">Fallback Footer</div>'
        };
    });

    <div ng-controller="ExampleController as ctrl">
        <input ng-model="ctrl.title">
        <textarea ng-model="ctrl.text"></textarea>
        <pane>
            <pane-title>
                <a ng-href="{{ ctrl.link }}">{{ ctrl.title }}</a>
            </pane-title>
            <pane-body>{{ ctrl.text }}</pane-body>
        </pane>
    </div>

首先可以看到 `ng-transclude="footer"` 这一部分，我们可以通过 `'footer': '?paneFooter'` 当中的问号形式表明这个 transclusion 其实是可选的，在组件模板当中已经有了默认值。而其他两部分，通过自定义 HTML 的方式可以任意得传入我们想要填充的模板，这带来的一个明显好处就是，不需要再把一些不必要的值都统统传进去了，比如说这里的`{{ ctrl.link }}`，我们在上一层进行计算过后就直接替换了 ng-transclusion 的位置。

而我们再来看看不使用 Multi-slot transclusion 定义 Component 的方式，不但需要传入所有的值，而且更重要的是丧失了定义 HTML 模板的机会，而这种能力在定义不同形式的复杂组件时是非常重要的。

    myMod.component('pane', function(){
        return {
          template: '<div>{{ $ctrl.title}}</div>' + 
                    '<p>{{ $ctrl.body}}</p>' + 
                    '<div>{{ $ctrl.footer}}</div>',
          bindings: {
            'title': '<paneTitle',
            'body': '<paneBody',
            'footer': '<?paneFooter'
          }
        };
    })

    <div ng-controller="ExampleController as ctrl">
      <input ng-model="ctrl.title">
      <textarea ng-model="ctrl.text"></textarea>
      <pane pane-title="ctrl.title"
            pane-body="ctrl.text">
      </pane>
    </div>

## Reference：重构实战手册

- [Refactoring Angular Apps to Component Style](http://teropa.info/blog/2015/10/18/refactoring-angular-apps-to-components.html)
- [Understanding Components - Developer Guide](https://docs.angularjs.org/guide/component)
- [Angular Style Guide](https://github.com/johnpapa/angular-styleguide/blob/master/a1%2Fi18n%2Fzh-CN.md)
- [AngularJS Best Practices - Two Fucking Developers](http://twofuckingdevelopers.com/category/angularjs/)
- [AngularJS Archives - AngularClass](https://angularclass.com/blog/)
- [Angular articles by thoughtram Blog](http://blog.thoughtram.io/categories/angular/)
- [Angular Blog Archive - codelord.net](http://www.codelord.net/blog/archives/)