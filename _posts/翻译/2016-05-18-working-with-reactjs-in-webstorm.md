---
layout: post
title: 【译】在 Webstorm 中使用 ReactJS：编码辅助、代码规范、重构以及编译
categories: [翻译]
tags: [React, Intellij, IDE, DX]
published: True

---

## 1. [Working with ReactJS in WebStorm: Coding Assistance](https://blog.jetbrains.com/webstorm/2015/10/working-with-reactjs-in-webstorm-coding-assistance/)

Posted on *October 5, 2015* by [Ekaterina Prigara](https://blog.jetbrains.com/webstorm/author/ekaterina-prigara/)

> [ReactJS](https://facebook.github.io/react/) is no doubt one of the trendiest JavaScript libraries released recently and as such is seeing wide adoption.

[ReactJS](https://facebook.github.io/react/) 无疑是最新发布的 JavaScript 库当中最为新潮的，有目共睹地被广泛采用。

> React support was introduced in WebStorm 10 and has undergone continuous improvement since then. In this blog post we’d like to show how WebStorm can help you write code with React. We are using WebStorm 11 that you can get [here](https://www.jetbrains.com/webstorm/whatsnew/).

最开始是在 WebStorm 10 中就初步支持了 React，并在那之后持续不断地进行了改进。这篇文章我们就将为你展现一下 WebStorm 将如何在编写 React 代码时助你一臂之力。我们将使用 WebStorm 11，你可以[这儿](https://www.jetbrains.com/webstorm/whatsnew/)获取最新版本。

> React introduces **JSX**, an XML-like syntax that you can use inside your JavaScript code, but you can also use React in pure JavaScript.

React 首次引入了 **JSX**，一种可以直接在 JavaScript 代码当中直接使用的类 XML 语法，但是你也可以使用纯 JavaScript 的方式使用 React。

> If you’re using JSX, WebStorm will suggest switching language version to *JSX Harmony* so that it may understand JSX syntax in *.js* files. That’s it, now you can write JSX code and enjoy **code** **completion** for JSX tags,**navigation** and **code analysis**.

如果你正在使用 JSX，WebStorm 将会建议你将语言版本切换至 *JSX Harmony*，从而 IDE 可以在 *.js* 文件当中理解 JSX 语法。就是这种，现在你可以愉快得编写 JSX 代码，并且享受 JSX 标签的**代码补全**，**导航**，**代码分析**等功能。

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/jsx_language_level.png)

> You can also switch language version to *JSX Harmony* manually in *`Preferences | Languages & Frameworks | JavaScript`*.

你可以手动地在 *`Preferences | Languages & Frameworks | JavaScript`* 当中切换语言版本到 *JSX Harmony*。

> **NB:** Once you have *react.js* library file somewhere in your project, WebStorm will provide you code completion for **React methods** and **React-specific attributes**. By default, the code completion popup displays automatically as you type. For example:

**注意：**只要你在项目的任何地方有了 *react.js* 的库文件，WebStorm 就会为你提供 **React 方法**和 **React 特定属性**提供代码自动补全。默认情况下，代码补全会根据你的输入自动显示弹出框。比如：

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_code_completion.png)

> From your code you can jump to the method definition in the library with *Cmd-click (Ctrl+click)*.

使用 *Cmd-click (Ctrl+click)* 可以从你的代码直接跳转到库中的方法定义。

> To enhance code completion with typed parameter information we recommend that you add a TypeScript definition file for [react.d.ts](https://github.com/borisyankov/DefinitelyTyped/blob/master/react/react.d.ts) as a JavaScript library for the project.

为了增强代码补全的类型参数信息，我们推荐你可以添加一个 TypeScript 类型定义文件 [react.d.ts](https://github.com/borisyankov/DefinitelyTyped/blob/master/react/react.d.ts)，作为当前项目的 JavaScript 库。

> Go to *`Preferences | Languages & Frameworks | JavaScript | Libraries`*, click *Download…*, search for *react* and click Download. The file will be added as [JavaScript library](http://blog.jetbrains.com/webstorm/2014/07/how-webstorm-works-completion-for-javascript-libraries/) for WebStorm to use in coding assistance.

到 *`Preferences | Languages & Frameworks | JavaScript | Libraries`* 选项下，点击 *Download…*，搜索 *react* 并点击下载。这个文件将会被添加作为 [JavaScript 库](http://blog.jetbrains.com/webstorm/2014/07/how-webstorm-works-completion-for-javascript-libraries/)，给 WebStorm 用来做为编码辅助。

> Now when you type, you’ll also see information on parameters that you can use in this method:

现在的话，只要你一输入，你就有看到可以在方法中使用的参数信息：

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_param_info.png)

> Press *Cmd-P* to invoke a popup with information about arguments and types again.

按住 *Cmd-P* 就可以重新调出参数和类型相关信息的弹出框。

> WebStorm can also provide code completion for HTML tags and component names that you have defined inside methods in JavaScript or inside other components.

WebStorm 也可以为 HTML 标签和组件名称提供代码补全，只要你已经在 JavaScript 的方法或者是其他组件中定义好了。

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_component_competion.png)

> Completion also works for imported components with ES6 style syntax:

自动补全也适用于使用 ES6 语法所导入的组件：

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_imported_component_completion.png)

> From there you can also jump to the component definition with *Cmd-click* (*Ctrl+click* on Windows and Linux) on component name or see a definition in a popup with *Cmd-Y* (*Ctrl+Shift+I*).

当然这里你也可以用使用 *Cmd-click* (*Ctrl+click* on Windows and Linux) 点击组件名称跳转到组件定义的地方，或者可以使用 *Cmd-Y* (*Ctrl+Shift+I*) 直接在弹出框中查看定义。

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_quick_definition.png)

> In JSX tags, the IDE provides coding assistance for [React-specific attributes](https://facebook.github.io/react/docs/tags-and-attributes.html#html-attributes) such as *className* or classID. Moreover, for class names you can autocomplete classes defined in the project’s CSS files.

在 JSX 标签中，IDE 给[特定的 React 属性](https://facebook.github.io/react/docs/tags-and-attributes.html#html-attributes) 提供代码辅助，比如 *className* 或 *classID*。而且对于 class 来说还可以自动补全那些项目 CSS 文件中已有的 class 名。

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_classname.gif)

> Of course there is also code completion for JavaScript expressions inside the curly braces. That includes all methods and functions that you have defined:

当然在花括号当中的 JavaScript 表达式也可以有代码补全。这包括所有已定义的方法和函数：

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_javascript_expression.png)

### Emmet in JSX | 在 JSX 中使用 Emmet

> With [Emmet](http://docs.emmet.io/cheat-sheet/) support in WebStorm, you can generate HTML markup really fast. You type an abbreviation that expands to HTML code when you press Tab. You can also use Emmet in JSX code, and that brings us to some special React twists. For example, the abbreviation *div.my-class* would expand in JSX to **`<div className=”my-class></div>`** and not to **`<div class=”my-class></div>`** like it would in HTML.

通过 WebStrom 中的 [Emmet](http://docs.emmet.io/cheat-sheet/) 支持，可以让你非常迅速地生成 HTML 标记。你可以在输入缩写后再按 Tab 键就可以自动扩展至 HTML 代码。你也可以在 JSX 代码中使用 Emmet，给我们带来一些专用于 React 的特殊扩展。比如，*`div.my-class`* 缩写就可以展开成 `<div className=”my-class></div>` 而不是像 HTML 中的 `<div class=”my-class></div>`。

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_emmet.gif)

### Live templates | 动态模板

> Live templates work very similar to Emmet – type a special abbreviation and it will expand into a code snippet. WebStorm has a predefined set of templates for JavaScript and HTML, and you can also create your custom templates for React in *`Preferences | Editor | Live templates`*.

动态模板和 Emmet 工作方式很像 —— 输入特殊缩写就可以自动展开成代码片段。WebStorm 有着一系列预先定义好的 JavaScript 和 HTML 模板，而且你也可以在 *`Preferences | Editor | Live templates`* 中为 React 创建自己的自定义模板。

> As an example let’s create a live template for creating a new React component:

我们给新建 React 组件创建一个动态模板来作为例子：

    var $NAME$ = React.createClass({
        render: function () {
            return (
                <div>$END$</div>
            )
        }
    });

> Let’s set the abbreviation to *rC*. With *$variable_name$* syntax, we can set the edit points for variable and function names (we have multiple edit points in one template), and with *$END$* we specify a location of the cursor at the end.

让我们将缩写设为 *rC*。通过 *$variable_name$* 语法，我们可以给变量和函数名字预留一些编辑点（我们可以在同一个模板中有多个编辑点），然后通过 *$END$* 我们可以给光标在最后特别指定一个位置。

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/new_live_template.png)

> We also need to specify the kind of files in which this template can be invoked; in our case it will be JSX.

我们还需要指定哪些文件可以调用这些模板，这种情况当然就是 JSX。

> Now when you type *rC* and press *Tab*, the code snippet will expand. Type the component name and press *Tab* again to jump to the end edit location:

现在当你输入 *rC* 并且按 *Tab* 的时候，代码片段就会展开。输入组件名称并再次按 *Tab* 键既可以跳到编辑的最后位置：

![](https://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/10/react_live_template1.gif)

> Another way to go is to import a set of templates created by community members for development with React in WebStorm. See [GitHub](https://github.com/Minwe/jetbrains-react) for details on the installation process.

另外一种方式就是直接导入模板集合，社区成员已经给 WebStorm 中的 React 开发创建好了的。可以到 [GitHub](https://github.com/Minwe/jetbrains-react) 上获取更多安装过程的细节。

> In a[ follow-up blog post](http://blog.jetbrains.com/webstorm/2015/12/working-with-reactjs-in-webstorm-linting-refactoring-and-compiling/) we’ll talk more about the available refactoring options, code quality analysis, and compiling code. Stay tuned!

在[接下来的一篇文章中](http://blog.jetbrains.com/webstorm/2015/12/working-with-reactjs-in-webstorm-linting-refactoring-and-compiling/)，我们将会讨论更多关于可用的重构项，代码质量分析，以及代码编译。敬请期待！

## 2. [Working with ReactJS in WebStorm: Linting, refactoring and compiling](http://blog.jetbrains.com/webstorm/2015/12/working-with-reactjs-in-webstorm-linting-refactoring-and-compiling/)

Posted on *December 30, 2015* by [Ekaterina Prigara](http://blog.jetbrains.com/webstorm/author/ekaterina-prigara/)

> We recently explored [coding assistance](http://blog.jetbrains.com/webstorm/2015/10/working-with-reactjs-in-webstorm-coding-assistance/) that WebStorm provides for React and JSX. Now we would like to talk a bit about the tools in the React ecosystem. In this area it’s not easy to provide a complete overview as tools are developing at a crazy pace. So right now we’ll focus on linters (code quality tools), refactoring and tools that can help us compile code.

我们最近探索了 WebStorm 给 React 和 JSX 所提供的 [编码辅助](http://blog.jetbrains.com/webstorm/2015/10/working-with-reactjs-in-webstorm-coding-assistance/)。现在我们就来讨论一些 React 生态中的工具。在这方面提供一个完整的概述并不容易，因为工具正在以疯狂的速度发展。所以现在我们就只会专注于 linters（代码质量分析工具），重构，以及可以帮助我们编译代码的工具。

### Code analysis | 代码分析

> As you may know, WebStorm has a wide range of built-in inspections for JavaScript and HTML, and these inspections also work for JSX code.

由于你可能已经知道了，WebStorm 内置很多对于 JavaScript 和 HTML 的广泛检查。这些检查对于 JSX 代码同样有效。

> For example, WebStorm alerts you in case of unused variables and functions, missing closing tags, missing statements and much more. For some inspections WebStorm provides quick-fixes, like add a missing semicolon:

比如，WebStorm 可以在一些情况下提醒你，比如无用的变量和函数，缺失语句乃至更多。对于一些检查 WebStorm 可以给你提供快速修复，比如添加缺失的分号：

![](http://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/12/react-inspection.png)

> You can customize the list of inspections in *`Preferences | Editor | Inspections`*. Disable those you don’t want to see, or change severity level from warning to error or vice versa.

你可以在 *`Preferences | Editor | Inspections`* 中定制这一系列的检查。禁掉那些你并不想看到的，或者将安全等级从警告改成错误，反之亦然。

> On top of such inspections, you can also use linters like ESLint and JSCS for the JSX code. Let’s talk about these in more detail.

在以上的检查之外，你也可以给 JSX 代码用上一些如 ESLint 和 JSCS 之类的 linters。让我们来谈论更多有关细节。

### ESLint

> **[ESLint](http://eslint.org/)** is a linting utility that provides a wide range of linting rules, which can also be extended with plugins. WebStorm integrates with ESLint and allows you to see warnings as errors reported by ESLint right in the editor, as you type.

**[ESLint**](http://eslint.org/) 是一种规范工具，提供了非常广泛的 linting 规则，并可以通过插件的方式进行扩展。WebStorm 集成了 ESLint， 并且让你在输入的时候就可以在编辑器中看到 ESLint 所报告的警告和错误。

> While ESLint itself understands JSX syntax, authors [recommend](https://github.com/eslint/eslint#does-eslint-support-jsx) using [eslint-plugin-react](https://www.npmjs.com/package/eslint-plugin-react) if you are working with React. To get started, add *eslint* and *eslint-plugin-react* modules to your project via npm, then add an ESLint configuration file *.eslintrc*.

ESLint 本身就可以理解 JSX 语法，如果你在使用 React 的话，作者[推荐](https://github.com/eslint/eslint#does-eslint-support-jsx)使用 [eslint-plugin-react](https://www.npmjs.com/package/eslint-plugin-react)。通过 npm 安装 *eslint* 和 *eslint-plugin-react* 模块到你的项目就可以上手了，然后添加一个 ESLint 的配置文件 *.eslintrc*。

> Here’s what *.eslint* file structure looks like when using ESLint 1.x and react plugin:

这儿有一个使用 ESLint 1.x 和 React 的 *.eslint* 文件结构示例：

    {
        "ecmaFeatures": {
            "jsx": true
        },
        "plugins": [
            "react"
        ],
        "rules": {}
    }                    

> In [ecmaFeatures](http://eslint.org/docs/2.0.0/user-guide/configuring.html#specifying-parser-options) object you can specify additional language features you’d like to use, for example ES6 classes, modules, etc.

在 [ecmaFeatures](http://eslint.org/docs/2.0.0/user-guide/configuring.html#specifying-parser-options) 对象当中你可以指定额外你想要使用的语言特性，比如 ES6 类，模块，等等。

> In rules object you can list ESLint [built-in rules](http://eslint.org/docs/rules/) that you would like to enable, as well as [rules](https://github.com/yannickcr/eslint-plugin-react#list-of-supported-rules) available via the react plugin.

在规则对象中你可以列出想要启用的 ESLint [内置规则](http://eslint.org/docs/rules/)，通过 React 插件实现的[规则](https://github.com/yannickcr/eslint-plugin-react#list-of-supported-rules)也是一样的。

> For example, thanks to ESLint with react plugin we can get warnings when the display name is not set for React component, or when some dangerous JSX properties are used. Here’s how it looks in the editor, if you have ESLint integration enabled in WebStorm:

比如，得益于 ESLint 的 React 插件，我们可以获得一些警告，比如当显示的名字不属于 React 组件，或者一些危险的 JSX 属于被使用的时候。这就是在 WebStorm 集成了 ESLint 后编辑器中的样子：

![](http://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/12/eslint-react.png)

> To enable ESLint, go to *`Preferences | Languages & Frameworks | JavaScript | Code quality | ESLint`* (or simply search for ESLint in Preferences) and check the *Enable* checkbox. WebStorm will automatically locate ESLint in your project’s node_modules folder and then use *.eslintrc* configuration by default.

为了启用 ESLint，可以到 *`Preferences | Languages & Frameworks | JavaScript | Code quality | ESLint`* （或者直接在 Preferences 中搜索 ESLint）然后选中 *Enable* 选项。WebStorm 将会自动找到项目 node_modules 文件夹下的 ESLint 并默认使用 *.eslintrc* 配置。

![](http://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/12/eslint-enable.png)

## Refactoring | 重构

> WebStorm offers lots of different refactorings to modify and maintain your code. For example, when you rename a file with *Refactor -> Rename*, all the references will be renamed automatically. Or, you can easily rename a variable, class or method throughout your whole project.

WebStorm 提供了种类繁多的重构方式来修改和维护你的代码。比如，当你使用 *Refactor -> Rename* 重命名一个文件的时候，所有的引用都会自动被重新命名。或者是，你可以轻松重命名一个贯穿整个项目的变量，类，或者方法。

> For React applications, WebStorm can also help you rename components. Place the cursor on the component name and press **Ctrl+T** to open the *Refactor This* popup. Select *Rename…*, type the new name and press Enter. Done!

对于 React 应用来说，WebStorm 也可以帮助你重命名组件。只要把光标放到组件的名字上，并按 **Ctrl+T** 打开 *Refactor This* 弹出框，然后选择 *Rename…*，输入新的名字并按 Enter 键，完成！

> Here’s an example of renaming a component that is refined and used in only one file:

这儿有个重命名组件的例子，这个组件只在这一个文件中被定义和使用：

![](http://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/12/rename-component.gif)

> In the same way, you can rename components defined in one file and then imported using a named export to another file:

同样地，你可以重命名一个导入的组件，这个组件在其他文件中所定义然后被导出到另外一个文件：

![](http://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/12/rename-component-import.gif)

## Compiling the code | 编译代码

> You can set up a build process for your React app in multiple ways. [The React Getting started page](https://facebook.github.io/react/docs/getting-started.html) suggests using [Browserify](http://browserify.org/) or [Webpack](https://webpack.github.io/) which are CommonJS module systems. You will also need Babel and, if using Babel 6 and ES6 code, [babel-preset-react](https://www.npmjs.com/package/babel-preset-react) and [babel-preset-es2015](https://www.npmjs.com/package/babel-preset-es2015) to compile your code. You can find lots of articles and tutorials with recommendations for the build process using various tools.

你可以通过多种方式给你的 React 应用准备一个构建进程。[React Getting started 页面](https://facebook.github.io/react/docs/getting-started.html)上就建议使用 [Browserify](http://browserify.org/) 或者 [Webpack](https://webpack.github.io/)，这些都支持 CommonJS 模块系统。你也将使用到 Babel，如果使用 Babel 6 和 ES6 代码的话，[babel-preset-react](https://www.npmjs.com/package/babel-preset-react) 和 [babel-preset-es2015](https://www.npmjs.com/package/babel-preset-es2015) 可以用来编译你的代码。你可以找到大量的文章和教程，都会推荐使用各种各样工具来进行构建处理。

> As the [Getting started tutorial](https://facebook.github.io/react/docs/getting-started.html) suggests, install the following modules via npm:

就像 [Getting started 教程](https://facebook.github.io/react/docs/getting-started.html)中所建议的那样，通过 npm 安装以下模块：

`npm install --save react react-dom browserify babelify babel-preset-es2015 babel-preset-react`

> To automate the build process a little bit, let’s add the command suggested in the tutorial to the scripts section of the project’s *package.json* file:

为了更加自动化构建的过程，让我们来添加教程中所建议的命令，作为项目 *package.json* 文件中的脚本部分：

    "scripts": {    "build": "browserify -t [ babelify --presets [ react ] ] main.js -o bundle.js"}

> where *main.js* is the main app file and *bundle.js* is the output file.

*main.js* 文件作为应用的主文件，*bundle.js* 作为输出文件。

> WebStorm displays npm tasks listed in package.json in a separate tool window. Just double-click on the task name to run it. No need to run commands in the terminal.

WebStorm 可以在单独的工具窗口显示在 package.json 中所定义好的 npm 任务。只需要双击任务名称就可以运行它。不需要再在终端中运行命令。

![](http://d3nmt5vlzunoa1.cloudfront.net/webstorm/files/2015/12/npm-build.png)

> In a similar way you can start [Gulp or Grunt tasks](https://youtu.be/EI62ZhMx4lI) in WebStorm.

同样地，你也可以在 WebStorm 中启动 [Gulp 或者 Grunt 任务](https://youtu.be/EI62ZhMx4lI)。

> You can also set up a File watcher for Babel and Browserify in WebStorm to execute similar tasks (you can read about it [here](http://blog.jetbrains.com/webstorm/2015/05/ecmascript-6-in-webstorm-transpiling/)), but running tasks via npm scripts or Gulp gives you more flexibility if you add more steps.

你也可以在 WebStorm 中给 Babel 和 Browserify 装一个文件监听器，用来执行相似命令（你可以阅读[这里](http://blog.jetbrains.com/webstorm/2015/05/ecmascript-6-in-webstorm-transpiling/)），但是如果你需要很多步骤的话，通过 npm 脚本或者 Gulp 的方式就可以给你更多的可扩展性。

*Develop with pleasure!
– JetBrains WebStorm Team*
