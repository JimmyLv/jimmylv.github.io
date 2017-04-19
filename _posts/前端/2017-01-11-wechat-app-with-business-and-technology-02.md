---
layout: post
title: 微信小程序之技术构建篇
tags: [WeChat, 微信, 小程序, 商业, 技术]
published: False
---

## 技术

- 官方小程序
    - IDE
      - 下载安装：`brew cask install wechatwebdevtools`
      - Appdata panel Appdata panel 用于显示当前项目当前时刻 appdata 具体数据，实时地反馈项目数据情况，可以在此处编辑数据，并及时地反馈到界面上。   [mp.weixin.qq.com]
      - 基于 [Microsoft/monaco-editor: A browser based code editor](https://github.com/Microsoft/monaco-editor)
      - 微信小程序运行在三端：iOS、Android 和 用于调试的开发者工具。 三端的脚本执行环境聚以及用于渲染非原生组件的环境是各不相同的： 在 iOS 上，小程序的 javascript 代码是运行在 JavaScriptCore 中，是由 WKWebView 来渲染的，环境有 iOS8、iOS9、iOS10 在 Android 上，小程序的 javascript 代码是通过 X5 JSCore来解析，是由 X5 基于 Mobile Chrome 37 内核来渲染的 在 开发工具上， 小程序的 javascript 代码是运行在 nwjs 中，是由 Chrome Webview 来渲染的   所以还是 WebView？ [mp.weixin.qq.com]
    - API
      - 数据绑定
        - 小程序中的数据绑定是单向的……   修改 data 会反馈到界面，但修改界面并不会反馈到数据里边。所以要获得输入框数据有两种办法，一种是通过 Form 组件的submit 事件取  e.detail.value ;另一种办法是单个组件手动加上 bindChange 事件，然后在事件函数中 用 this.setData( { key: e.detail.value } ) 去更新数据。=> Vue 的数据绑定和 Template 语法，React 的单向数据流。 [weibo.com]
      - 生命周期
        - 生命周期函数 onLoad: 页面加载  一个页面只会调用一次。 接收页面参数可以获取wx.navigateTo和wx.redirectTo及中的 query。 onShow: 页面显示  每次打开页面都会调用一次。 onReady: 页面初次渲染完成  一个页面只会调用一次，代表页面已经准备妥当，可以和视图层进行交互。 对界面的设置如wx.setNavigationBarTitle请在onReady之后设置。详见生命周期 onHide: 页面隐藏  当navigateTo或底部tab切换时调用。 onUnload: 页面卸载  当redirectTo或navigateBack的时候调用。   React：mount、update、unmount  Vue：mounted、 updated 、destroyed [mp.weixin.qq.com]
      - 模板 
        - WXML提供模板（template），可以在模板中定义代码片段，然后在不同的地方调用。 
        - 定义模板 使用name属性，作为模板的名字。然后在内定义代码片段，如：    [mp.weixin.qq.com]
      - 样式
        - rpx（responsive pixel）: 可以根据屏幕宽度进行自适应。  [mp.weixin.qq.com]
        - 样式导入 使用@import语句可以导入外联样式表，@import后跟需要导入的外联样式表的相对路径，用;表示语句结束。   [mp.weixin.qq.com]
      - 事件绑定
        - 在组件中绑定一个事件处理函数。  如bindtap，当用户点击该组件的时候会在该页面对应的Page中找到相应的事件处理函数。  Click me!   在相应的Page定义中写上相应的事件处理函数，参数是event。  Page({   tapName: function(event) {     console.log(event)   } })    [mp.weixin.qq.com]
- 第三方开发框架
    - [maichong/labrador: 微信小程序模块化开发框架](https://github.com/maichong/labrador)
    - [wepyjs/wepy: 小程序组件化开发框架](https://github.com/wepyjs/wepy)
    - 支持加载外部NPM包。在编译过程当中，会递归遍历代码中的require然后将对应依赖文件从node_modules当中拷贝出来，并且修改require为相对路径，从而实现对外部NPM包的支持。  [wepyjs.github.io]
    - wpy文件说明wpy文件的编译过程过下：  [zhuanlan.zhihu.com]
- 与其他方案的对比
    - PWA
    - ReactNative
    - Hybrid
- 相关资源：
    - [justjavac/awesome-wechat-weapp: 微信小程序开发资源汇总 :100:](https://github.com/justjavac/awesome-wechat-weapp)
    - [实例大全 - 微信小程序开发者](https://github.com/wxappdev)
