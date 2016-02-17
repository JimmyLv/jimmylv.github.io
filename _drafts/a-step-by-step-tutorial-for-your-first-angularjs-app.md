---
layout: post
title: A Step-by-Step Tutorial for Your First AngularJS App
categories: []
tags: []
published: True

---

# A Step-by-Step Tutorial for Your First AngularJS App

BY **[RAONI BOAVENTURA](http://www.toptal.com/resume/raoni-boaventura-cruz-gomes)** - JAVASCRIPT ENGINEER @[TOPTAL](http://www.toptal.com/)

[#AngularJS](http://www.toptal.com/blog#angularjs-posts) [#MVC](http://www.toptal.com/blog#mvc-posts) [#JavaScript](http://www.toptal.com/blog#javascript-posts)</div>

## What is AngularJS? | AngularJS 是什么？

> [AngularJS](http://www.toptal.com/angular-js) is a JavaScript MVC framework developed by Google that lets you build well structured, easily testable, and maintainable front-end applications.

[AngularJS](http://www.toptal.com/angular-js) 是由 Google 开发的一款 JavaScript MVC 框架，用于构建模块化、易测试、可维护的前端应用。

## And Why Should I Use It? | 为什么我应该使用 Angular？

> If you haven’t tried AngularJS yet, you’re missing out. The framework consists of a tightly integrated toolset that will help you build well structured, rich client-side applications in a modular fashion—with less code and more flexibility.

如果你还没有尝试过 AngularJS ，那你就亏大了。该框架包括了一个紧密集成的工具集，可以帮助你使用更少的代码和更灵活性的方式，来构建结构良好的富客户端应用程序。

> AngularJS extends HTML by providing [directives](http://docs.angularjs.org/guide/directive) that add functionality to your markup and allow you to create powerful dynamic templates. You can also create your own directives, crafting reusable components that fill your needs and abstracting away all the DOM manipulation logic.

AngularJS 提供了 [directives](http://docs.angularjs.org/guide/directive) 用来扩展 HTML，可以为你的标记添加功能以便于创建强力的动态模板。你也可以创建自己的 directives，构建可复用组件来满足你的需求，抽象出所有的 DOM 层操作逻辑。

> It also implements two-way data binding, connecting your HTML (views) to your JavaScript objects (models) seamlessly. In simple terms, this means that any update on your model will be immediately reflected in your view without the need for any DOM manipulation or event handling (e.g., with jQuery).

它也实现了双向数据绑定，将 HTML（views）和 JavaScript 对象（models）无缝连接起来。简而言之，这意味着 Model 上的任何改变都会立即反映到 view 上，无需任何 DOM 操作或者事件处理（比如使用jQuery）。

> > Angular provides services on top of XHR that dramatically simplify your code and allow you to abstract API calls into reusable services. With that, you can move your model and business logic to the front-end and build back-end agnostic web apps.

> Angular在 XHR 的顶端提供了服务，从而大大简化了代码，并且允许你抽象出 API 调用可复用的服务。通过这样，你可以将 Model 和业务逻辑放到前端，从而构建与后端分离的 web 应用。

Finally, I love Angular because of its flexibility regarding server communication. Like most JavaScript MVC frameworks, it lets you work with any server-side technology as long as it can serve your app through a RESTful web API. But Angular also provides services *on top* of XHR that dramatically simplify your code and allow you to abstract API calls into reusable services. As a result, you can move your model and business logic to the front-end and build back-end agnostic web apps. In this post, we’ll do just that, one step at a time.

最后，我喜欢 Angular 是因为它与服务器之间通信的灵活性。就像大部分的 JavaScript MVC 框架，它可以让你使用任何一种服务器端技术，只要服务器可以通过 RESTful 的 Web API 服务于你的应用程序。而且，Angular 在 XHR *顶端* 也提供了服务，从而大大简化了代码，并允许你抽象出 API  调用可复用的服务。这样一来，你可以将你的 model 和业务逻辑放到前端，从而构建与后端分离的 web 应用。在这篇文章中，我们就将这么做，一步一个脚印。

## So, Where Do I Begin? | 所以，我该从哪里开始？

First, let’s decide the nature of the app we want to build. In this guide, we’d prefer not to spend too much time on the back-end, so we’ll write something based on data that’s easily attainable on the Internet—like a sports feed app!

首先，让我们决定想要构建的应用特性。在这份指南中，我们更倾向于不要在后端上花太多时间，所以我们将会以数据为基础编写应用，从一个类-互联网运动信息流应用中轻易获取数据。

Since I happen to be a huge fan of motor racing and Formula 1, I’ll use an autosport API service to act as our back-end. Luckily, the guys at [Ergast](http://ergast.com/mrd/) are kind enough to provide a free motorsport API that will be perfect for us.

由于我恰巧是一名摩托车竞赛和一级方程式的超级粉丝，我将会使用一个自动运动 API 服务作为我们的后端。幸运的是，[Ergast](http://ergast.com/mrd/) 的哥们很乐于提供一个免费的摩托车运动的 API，简直完美。

For a sneak peak at what we’re going to build, take a look at the [live demo](http://rboaventura.com/f1feeder/). To prettify the demo and show off some Angular templating, I applied a Bootstrap theme from [WrapBootstrap](https://wrapbootstrap.com/), but seeing as this article isn’t about CSS, I’ll just abstract it away from the examples and leave it out.



## Getting Started Tutorial

Let’s kickstart our example app with some boilerplate. I recommend the [angular-seed](https://github.com/angular/angular-seed) project as it not only provides you with a great skeleton for bootstrapping, but also sets the ground for unit testing with [Karma](http://karma-runner.github.io/0.10/index.html) and[Jasmine](https://github.com/jasmine/jasmine) (we won’t be doing any testing in this demo, so we’ll just leave that stuff aside for now; see [Part 2](http://www.toptal.com/angular-js/your-first-angularjs-app-part-2-scaffolding-building-and-testing) of this tutorial for more info on setting up your project for unit and end-to-end testing).

***EDIT (May 2014):*** Since I wrote this tutorial, the [angular-seed](https://github.com/angular/angular-seed) project has gone through some heavy changes (including the additon of [Bower](http://bower.io/) as package manager). If you have any doubts about how to deploy the project, take a quick look at the first section of their [reference guide](https://github.com/angular/angular-seed/blob/master/README.md). In [Part 2](http://www.toptal.com/angular-js/your-first-angularjs-app-part-2-scaffolding-building-and-testing) of ths tutorial, [Bower](http://bower.io/), among other tools, is covered in greater detail.

OK, now that we’ve cloned the repository and installed the dependencies, our app’s skeleton will look like this:
<en-media alt="angularjs tutorial - start with the skeleton" style="padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; box-sizing: border-box; max-width: 100%; height: auto;" hash="3da937c84f931ef674cf0cc07ebd4232" type="image/png"/>

Now we can start coding. As we’re trying to build a sports feed for a racing championship, let’s begin with the most relevant view: **the championship table**.
<en-media alt="the championship table" style="padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; box-sizing: border-box; max-width: 100%; height: auto;" hash="7dbdce9b086d14932265137f3c016e35" type="image/png"/>

Given that we already have a drivers list defined within our scope (hang with me – we’ll get there), and ignoring any CSS (for readability), our HTML might look like:
    
    
    <body ng-app="F1FeederApp" ng-controller="driversController">
      <table>
        <thead>
          <tr><th colspan="4">Drivers Championship Standings</th></tr>
        </thead>
        <tbody>
          <tr ng-repeat="driver in driversList">
            <td>{{$index + 1}}</td>
            <td>
              <img src="img/flags/{{driver.Driver.nationality}}.png" />
              {{driver.Driver.givenName}}&nbsp;{{driver.Driver.familyName}}
            </td>
            <td>{{driver.Constructors[0].name}}</td>
            <td>{{driver.points}}</td>
          </tr>
        </tbody>
      </table>
    </body>
    
    

The first thing you’ll notice in this template is the use of expressions (“{{“ and “}}”) to return variable values. In AngularJS, expressions allow you to execute some computation in order to return a desired value. Some valid expressions would be:

  * `{{ 1 + 1 }}`
  * `{{ 946757880 | date }}`
  * `{{ [user.name](http://user.name) }}`

Effectively, expressions are JavaScript-like snippets. But despite being very powerful, you shouldn’t use expressions to implement any higher-level logic. For that, we use directives.

## Understanding Basic Directives

The second thing you’ll notice is the presence of `ng-attributes`, which you wouldn’t see in typical markup. Those are directives.

At a high level, directives are markers (such as attributes, tags, and class names) that tell AngularJS to attach a given behaviour to a DOM element (or transform it, replace it, etc.). Let’s take a look at the ones we’ve seen already:

  * The `ng-app` directive is responsible for bootstrapping your app defining its scope. In AngularJS, you can have multiple apps within the same page, so this directive defines where each distinct app starts and ends.

  * The `ng-controller` directive defines which controller will be in charge of your view. In this case, we denote the `driversController`, which will provide our list of drivers (`driversList`).

  * The `ng-repeat` directive is one of the most commonly used and serves to define your template scope when looping through collections. In the example above, it replicates a line in the table for each driver in `driversList`.

## Adding Controllers

Of course, there’s no use for our view without a controller. Let’s add `driversController` to our controllers.js:
    
    
    angular.module('F1FeederApp.controllers', []).
    controller('driversController', function($scope) {
        $scope.driversList = [
          {
              Driver: {
                  givenName: 'Sebastian',
                  familyName: 'Vettel'
              },
              points: 322,
              nationality: "German",
              Constructors: [
                  {name: "Red Bull"}
              ]
          },
          {
              Driver: {
              givenName: 'Fernando',
                  familyName: 'Alonso'
              },
              points: 207,
              nationality: "Spanish",
              Constructors: [
                  {name: "Ferrari"}
              ]
          }
        ];
    });
    
    

You may have noticed the `$scope` variable we’re passing as a parameter to the controller. The `$scope`variable is supposed to link your controller and views. In particular, it holds all the data that will be used within your template. Anything you add to it (like the `driversList` in the above example) will be directly accessible in your views. For now, let’s just work with a dummy (static) data array, which we will replace later with our API service.

Now, add this to app.js:
    
    
    angular.module('F1FeederApp', [
      'F1FeederApp.controllers'
    ]);
    
    

With this line of code, we actually initialize our app and register the modules on which it depends. We’ll come back to that file (`app.js`) later on.

Now, let’s put everything together in `index.html`:
    
    
    <!DOCTYPE html>
    <html>
    <head>
      <title>F-1 Feeder</title>
    </head>
    
    <body ng-app="F1FeederApp" ng-controller="driversController">
      <table>
        <thead>
          <tr><th colspan="4">Drivers Championship Standings</th></tr>
        </thead>
        <tbody>
          <tr ng-repeat="driver in driversList">
            <td>{{$index + 1}}</td>
            <td>
              <img src="img/flags/{{driver.Driver.nationality}}.png" />
              {{driver.Driver.givenName}}&nbsp;{{driver.Driver.familyName}}
            </td>
            <td>{{driver.Constructors[0].name}}</td>
            <td>{{driver.points}}</td>
          </tr>
        </tbody>
      </table>
      <script src="bower_components/angular/angular.js"></script>
      <script src="bower_components/angular-route/angular-route.js"></script>
      <script src="js/app.js"></script>
      <script src="js/services.js"></script>
      <script src="js/controllers.js"></script>
    </body>
    </html>
    
    

Modulo minor mistakes, you can now boot up your app and check your (static) list of drivers.

*Note: If you need help debugging your app and visualizing your models and scope within the browser, I recommend taking a look at the awesome [Batarang](https://chrome.google.com/webstore/detail/angularjs-batarang/ighdmehidhipcmcojjgiloacoafjmpfk?hl=en) plugin for Chrome.*

<div markdown="1" style=" padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; box-sizing: border-box;">

<div markdown="1" style="padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; color: rgb(37, 87, 161); font-size: 17px; font-weight: bold; text-transform: none; box-sizing: border-box;">

Like what you're reading?</div>

<div markdown="1" style="padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; color: rgb(49, 49, 49); font-size: 17px; box-sizing: border-box; font-style: italic;">

Get the latest updates first.</div>

</div>

<div markdown="1" style=" padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; box-sizing: border-box; -webkit-box-align: center; align-items: center;">

<div markdown="1" style=" padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; box-sizing: border-box; flex-shrink: 0; -webkit-box-ordinal-group: 1; order: 0;">

<div markdown="1" style="padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; color: rgb(154, 154, 154); font-size: 12px; box-sizing: border-box; -webkit-box-align: center; align-items: center;">

<div markdown="1" style=" padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; box-sizing: border-box;">

No spam. Just great engineering posts.</div>

</div>

</div>

</div>

## Loading Data From the Server

Since we already know how to display our controller’s data in our view, it’s time to actually fetch live data from a RESTful server.

To facilitate communication with HTTP servers, AngularJS provides the `$http` and `$resource` services. The former is but a layer on top of [XMLHttpRequest](https://developer.mozilla.org/en/xmlhttprequest) or [JSONP](http://en.wikipedia.org/wiki/JSONP), while the latter provides a higher level of abstraction. We’ll use `$http`.

To abstract our server API calls from the controller, let’s create our own custom service which will fetch our data and act as a wrapper around `$http` by adding this to our `services.js`:
    
    
    angular.module('F1FeederApp.services', []).
      factory('ergastAPIservice', function($http) {
    
        var ergastAPI = {};
    
        ergastAPI.getDrivers = function() {
          return $http({
            method: 'JSONP', 
            url: '<http://ergast.com/api/f1/2013/driverStandings.json?callback=JSON_CALLBACK>'
          });
        }
    
        return ergastAPI;
      });
    
    

With the first two lines, we create a new module (`F1FeederApp.services`) and register a service within that module (`ergastAPIservice`). Notice that we pass `$http` as a parameter to that service. This tells Angular’s[dependency injection](http://docs.angularjs.org/guide/di) engine that our new service requires (or *depends on*) the `$http` service.

In a similar fashion, we need to tell Angular to include our new module into our app. Let’s register it with `app.js`, replacing our existing code with:
    
    
    angular.module('F1FeederApp', [
      'F1FeederApp.controllers',
      'F1FeederApp.services'
    ]);
    
    

Now, all we need to do is tweak our `controller.js` a bit, include `ergastAPIservice` as a dependency, and we’ll be good to go:
    
    
    angular.module('F1FeederApp.controllers', []).
      controller('driversController', function($scope, ergastAPIservice) {
        $scope.nameFilter = null;
        $scope.driversList = [];
    
        ergastAPIservice.getDrivers().success(function (response) {
            //Dig into the responde to get the relevant data
            $scope.driversList = response.MRData.StandingsTable.StandingsLists[0].DriverStandings;
        });
      });
    
    

Now reload the app and check out the result. Notice that we didn’t make any changes to our template, but we added a `nameFilter` variable to our scope. Let’s put that variable to use.

## Filters

Great! We have a functional controller. But it only shows a list of drivers. Let’s add some functionality by implementing a simple text search input which will filter our list. Let’s add the following line to our `index.html`, right below the `<body>` tag:
    
    
    <input type="text" ng-model="nameFilter" placeholder="Search..."/>
    
    

We are now making use of the `ng-model` directive. This directive binds our text field to the `$scope.nameFilter` variable and makes sure that its value is always up-to-date with the input value. Now, let’s visit index.html one more time and make a small adjustment to the line that contains the `ng-repeat`directive:
    
    
    <tr ng-repeat="driver in driversList | filter: nameFilter">
    
    

This line tells `ng-repeat` that, before outputting the data, the `driversList` array must be filtered by the value stored in `nameFilter`.

At this point, two-way data binding kicks in: every time a value is input in the search field, Angular immediately ensures that the `$scope.nameFilter` that we associated with it is updated with the new value. Since the binding works both ways, the moment the `nameFilter` value is updated, the second directive associated to it (i.e., the `ng-repeat`) also gets the new value and the view is updated immediately.

Reload the app and check out the search bar.
<en-media alt="app search bar" style="padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; box-sizing: border-box; max-width: 100%; height: auto;" hash="a7cc42b4e07bb005b8781c2da751882b" type="image/png"/>

Notice that this filter will look for the keyword on all attributes of the model, including the ones we´re not using. Let’s say we only want to filter by `Driver.givenName` and `Driver.familyName`: First, we add to `driversController`, right below the `$scope.driversList = [];` line:
    
    
    $scope.searchFilter = function (driver) {
        var keyword = new RegExp($scope.nameFilter, 'i');
        return !$scope.nameFilter || keyword.test(driver.Driver.givenName) || keyword.test(driver.Driver.familyName);
    };
    
    

Now, back to `index.html`, we update the line that contains the `ng-repeat` directive:
    
    
    <tr ng-repeat="driver in driversList | filter: searchFilter">
    
    

Reload the app one more time and now we have a search by name.

## Routes

Our next goal is to create a driver details page which will let us click on each driver and see his/her career details.

First, let’s include the `$routeProvider` service (in `app.js`) which will help us deal with these varied*application routes*. Then, we’ll add two such routes: one for the championship table and another for the driver details. Here’s our new `app.js`:
    
    
    angular.module('F1FeederApp', [
      'F1FeederApp.services',
      'F1FeederApp.controllers',
      'ngRoute'
    ]).
    config(['$routeProvider', function($routeProvider) {
      $routeProvider.
            when("/drivers", {templateUrl: "partials/drivers.html", controller: "driversController"}).
            when("/drivers/:id", {templateUrl: "partials/driver.html", controller: "driverController"}).
            otherwise({redirectTo: '/drivers'});
    }]);
    
    

With that change, navigating to `<http://domain/#/drivers>` will load the `driversController` and look for the partial view to render in `partials/drivers.html`. But wait! We don’t have any partial views yet, right? We’ll need to create those too.

## Partial Views

AngularJS will allow you to bind your routes to specific controllers and views.

But first, we need to tell Angular where to render these partial views. For that, we’ll use the `ng-view`directive, modifying our `index.html` to mirror the following:
    
    
    <!DOCTYPE html>
    <html>
    <head>
      <title>F-1 Feeder</title>
    </head>
    
    <body ng-app="F1FeederApp">
      <ng-view></ng-view>
      <script src="bower_components/angular/angular.js"></script>
      <script src="bower_components/angular-route/angular-route.js"></script>
      <script src="js/app.js"></script>
      <script src="js/services.js"></script>
      <script src="js/controllers.js"></script>
    </body>
    </html>
    
    

Now, whenever we navigate through our app routes, Angular will load the associated view and render it in place of the `<ng-view>` tag. All we need to do is create a file named `partials/drivers.html` and put our championship table HTML there. We’ll also use this chance to link the driver name to our driver details route:
    
    
    <input type="text" ng-model="nameFilter" placeholder="Search..."/>
    <table>
    <thead>
      <tr><th colspan="4">Drivers Championship Standings</th></tr>
    </thead>
    <tbody>
      <tr ng-repeat="driver in driversList | filter: searchFilter">
        <td>{{$index + 1}}</td>
        <td>
          <img src="img/flags/{{driver.Driver.nationality}}.png" />
          <a href="#/drivers/{{driver.Driver.driverId}}">
                    {{driver.Driver.givenName}}&nbsp;{{driver.Driver.familyName}}
              </a>
            </td>
        <td>{{driver.Constructors[0].name}}</td>
        <td>{{driver.points}}</td>
      </tr>
    </tbody>
    </table>
    
    

Finally, let’s decide what we want to show in the details page. How about a summary of all the relevant facts about the driver (e.g., birth, nationality) along with a table containing his/her recent results? To do that, we add to `services.js`:
    
    
    angular.module('F1FeederApp.services', [])
      .factory('ergastAPIservice', function($http) {
    
        var ergastAPI = {};
    
        ergastAPI.getDrivers = function() {
          return $http({
            method: 'JSONP', 
            url: '<http://ergast.com/api/f1/2013/driverStandings.json?callback=JSON_CALLBACK>'
          });
        }
    
        ergastAPI.getDriverDetails = function(id) {
          return $http({
            method: 'JSONP', 
            url: '<http://ergast.com/api/f1/2013/drivers/>'+ id +'/driverStandings.json?callback=JSON_CALLBACK'
          });
        }
    
        ergastAPI.getDriverRaces = function(id) {
          return $http({
            method: 'JSONP', 
            url: '<http://ergast.com/api/f1/2013/drivers/>'+ id +'/results.json?callback=JSON_CALLBACK'
          });
        }
    
        return ergastAPI;
      });
    
    

This time, we provide the driver’s ID to the service so that we retrieve the information relevant solely to a specific driver. Now, we modify `controllers.js`:
    
    
    angular.module('F1FeederApp.controllers', []).
    
      /* Drivers controller */
      controller('driversController', function($scope, ergastAPIservice) {
        $scope.nameFilter = null;
        $scope.driversList = [];
        $scope.searchFilter = function (driver) {
            var re = new RegExp($scope.nameFilter, 'i');
            return !$scope.nameFilter || re.test(driver.Driver.givenName) || re.test(driver.Driver.familyName);
        };
    
        ergastAPIservice.getDrivers().success(function (response) {
            //Digging into the response to get the relevant data
            $scope.driversList = response.MRData.StandingsTable.StandingsLists[0].DriverStandings;
        });
      }).
    
      /* Driver controller */
      controller('driverController', function($scope, $routeParams, ergastAPIservice) {
        $scope.id = $routeParams.id;
        $scope.races = [];
        $scope.driver = null;
    
        ergastAPIservice.getDriverDetails($scope.id).success(function (response) {
            $scope.driver = response.MRData.StandingsTable.StandingsLists[0].DriverStandings[0]; 
        });
    
        ergastAPIservice.getDriverRaces($scope.id).success(function (response) {
            $scope.races = response.MRData.RaceTable.Races; 
        }); 
      });
    
    

The important thing to notice here is that we just injected the `$routeParams` service into the driver controller. This service will allow us to access our URL parameters (for the `:id`, in this case) using `$routeParams.id`.

Now that we have our data in the scope, we only need the remaining partial view. Let’s create a file named `partials/driver.html` and add:
    
    
    <section id="main">
      <a href="./#/drivers"><- Back to drivers list</a>
      <nav id="secondary" class="main-nav">
        <div class="driver-picture">
          <div class="avatar">
            <img ng-show="driver" src="img/drivers/{{driver.Driver.driverId}}.png" />
            <img ng-show="driver" src="img/flags/{{driver.Driver.nationality}}.png" /><br/>
            {{driver.Driver.givenName}} {{driver.Driver.familyName}}
          </div>
        </div>
        <div class="driver-status">
          Country: {{driver.Driver.nationality}}   <br/>
          Team: {{driver.Constructors[0].name}}<br/>
          Birth: {{driver.Driver.dateOfBirth}}<br/>
          <a href="{{driver.Driver.url}}" target="_blank">Biography</a>
        </div>
      </nav>
    
      <div class="main-content">
        <table class="result-table">
          <thead>
            <tr><th colspan="5">Formula 1 2013 Results</th></tr>
          </thead>
          <tbody>
            <tr>
              <td>Round</td> <td>Grand Prix</td> <td>Team</td> <td>Grid</td> <td>Race</td>
            </tr>
            <tr ng-repeat="race in races">
              <td>{{race.round}}</td>
              <td><img  src="img/flags/{{race.Circuit.Location.country}}.png" />{{race.raceName}}</td>
              <td>{{race.Results[0].[Constructor.name](http://Constructor.name)}}</td>
              <td>{{race.Results[0].grid}}</td>
              <td>{{race.Results[0].position}}</td>
            </tr>
          </tbody>
        </table>
      </div>
    
    </section>
    
    

Notice that we’re now putting the `ng-show` directive to good use. This directive will only show the HTML element if the expression provided is `true` (i.e., neither `false`, nor `null`). In this case, the avatar will only show up once the driver object has been loaded into the scope by the controller.

## Finishing Touches

Add in a bunch of CSS and render your page. You should end up with something like this:
<en-media alt="page rendered with CSS" style="padding: 0px; border: 0px; vertical-align: baseline; min-height: 0px; min-width: 0px; box-sizing: border-box; max-width: 100%; height: auto;" hash="7b5a3704b50f4b5f36b707e963b9b95d" type="image/png"/>

You’re now ready to fire up your app and make sure both routes are working as desired. You could also add a static menu to `index.html` to improve the user’s navigation capabilities. The possibilities are endless.

***EDIT (May 2014):*** I’ve received many requests for a downloadable version of the code that we build in this tutorial. I’ve therefore decided to release it [here](https://github.com/raonibr/f1feeder-part1) (stripped of any CSS). However, I really do **not** recommend downloading it, since this guide contains every single step you need to build the same application with your own hands, which will be a much more useful and effective learning exercise.

## Conclusion

At this point in the tutorial, we’ve covered everything you’d need to write a simple app (like a Formula 1 feeder). Each of the remaining pages in the live demo (e.g., constructor championship table, team details, calendar) share the same basic structure and concepts that we’ve reviewed here.

Finally, keep in mind that Angular is a very powerful framework and we’ve barely scratched the surface in terms of everything it has to offer. In [Part 2](http://www.toptal.com/angular-js/your-first-angularjs-app-part-2-scaffolding-building-and-testing) of this tutorial, we’ll give examples of why Angular stands out among its peer front-end MVC frameworks: testability. We’ll review the process of writing and running unit tests with [Karma](http://karma-runner.github.io/0.10/index.html), achieving continuous integration with [Yeomen](http://yeoman.io/), [Grunt](http://gruntjs.com/), and [Bower](http://bower.io/), and other strengths of this fantastic front-end framework.
