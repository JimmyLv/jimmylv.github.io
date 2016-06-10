---
layout: 
title: Mac环境下的各种最优配置
categories: []
tags: []
published: True

---

- 写作
- 效率 MissionControl
- 编程
- 预览
- 时间花费
- 小工具

工具不再多，而是定制化，深度适应个人需求，并应当 infrastructure as assets. 成为个人资产绝对是这个成长期需要注重的事情。

就像软件开发一样，一个人的成长也应有自己的方法论。

就像敏捷，拥抱变化：

- 估算 >< 不用执着于计划，永远赶不上变化
- 小步迭代 >< 挽起袖子就是干，避免完美主义失败恐惧症
- Retro >< Refect
- 学习型组织 >< 此刻没做好是因为过去没学习，从此恶性循环
- 非单一角色，可靠交付为导向 >< 全栈性选手，懂得直击要害

相比于软件开发这件小事儿，健康地成长明显要更加重要。

## really cool

- https://www.reflectapp.io
- https://www.evernote.com (use MardkownHere in web)

## 新的起点

上一个阶段也许就是懂得了如何：

- 获取资源（更丰富地更准确地
- 收集资源（更方便快捷地

那么接下来：

- 筛选资源
- 整理资源
- 吸收资源

## 似乎完美解决了图片上传问题

- 换了个截图工具，[腾讯出品](https://github.com/SublimeText-Markdown/MarkdownEditing)，可以直接截图后编辑。
- 并且自己设了一个 Alfred 的 WorkFlow 用来关闭和打开截图的阴影。参考：[一篇文章，解决 Mac 截图的所有问题 | 领客专栏·Mac 玩儿法 | 爱范儿](http://www.ifanr.com/app/546621)
- 另外用上了一个好用 Alfred 的 WorkFlow，[tiann/markdown-img-upload: markdown图片实用工具](https://github.com/tiann/markdown-img-upload)，可以直接快捷键上传文件以及生产 md 链接。
- 进一步考虑 GIF 的录制，感觉小功能需要演示才倍感酸爽啊。我已经下载过的有 Gifrocket，是将视频转成 GIF 的，而[Mac 上怎么能少了一款好用的 GIF 录制工具？ - Pinapps - 感谢那些赐予我们力量的 apps - 知乎专栏](https://zhuanlan.zhihu.com/p/20732038?refer=pinapps)

## 以及 Evernote 和 Sublime 的无缝链接

- 在 Sublime 里面最佳编辑方式（Markdown 端）
    + 除了不能再中文词组间跳转以外（这个可以在 Evernote 中做到）
    + 放弃在 Evernote 编辑的想法（通常有借助 [AppleScript](https://github.com/sandai/madever) 实现）
    + Evernote 作为富文本编辑的一端，主要功能在于显示（其中图片无法缩成 md link，故遮挡了视线）
    + 进一步学习 Sublime 中 [MarkdownEditing](https://github.com/SublimeText-Markdown/MarkdownEditing) 的快捷键，好用到哭，以及完美格式高亮
    + check 一下 Evernote 在 [Mac OS X 下的文件系统](https://www.zhihu.com/question/20651262)是怎么样的，可以打开看到在 content 目录下。
- 版本管理
    + 经过实际使用效果来说，并没有什么情况下是需要用到这个功能的，若一切都是同步到 Evernote 的，就并不会出现误删除的情况了，还有就是 Evernote 付费账号是有历史版本的。 [How to access and use note history – Evernote Help & Learning](https://help.evernote.com/hc/en-us/articles/208313858-How-to-access-and-use-note-history)
    + 至于非自我产出的内容，比如 Session PPT，电子书，这些都可以到互联网上随时可找的。
    + 还有物理备份，即 TimeMachine 是同步到移动硬盘的，所以有了多重保障。

## 爱上写作

- 工作流的确定和便利之后，偏可以在肌肉记忆下无意识完成相关操作，从而将自己的意识回归到真真正正的写作上来。
- 对于 Markdown 文件的处理来说，直接打开是预览，然后 `Cmd + E` 这是打开 Sublime 来进行编辑
- 而 Marboo 的作用就更加注重在对于文件夹级别的层级预览，在 Marboo 做打开和分享等操作最佳。
- 通过 Marboo 直接映射到 `http://192.168.199.123:56866/xxxx.html`，同一局域网下可直接访问，还有贴心的二维码。
- 如果需要映射到外网，那就在本地起了 Server 之后打开 [ngork - Secure tunnels to localhost](https://ngrok.com/) 神器来突破防火墙吧。

## 时间花费

- 这个主题就是在真正做事情的时候了

## 专注力

- 自动整理桌面 [Noodlesoft – Noodlesoft – Simply Useful Software](https://www.noodlesoft.com/)，以及 Finder 中的 Smart Folder 可以自定义一些搜索结果集合，从而实现了在特定条件规则限制下的自动整合。

![](http://7xjbdq.com1.z0.glb.clouddn.com/images/2016/1463930568879.png)

- 快捷键打开特定软件、特定功能，全局、局部
    + `^ + Number` 打开 Desktop，缺憾是不能打开全屏应用，故少用全屏为妙，当进入全屏后，即为专注于一个/两个软件的时候
    + `alt + Number` 打开常用的必用软件，比如 Chrome，Sublime，IDEA。多谢 [Snap - Launch apps in a snap!](http://indragie.com/snap/)
    + `Cmd + Number` 就是在特定软件中，打开不同的 Tab，比如 Chrome 中和 iTerm2 中的不同标签页。
- 从而专注于单一任务，比如写作、写代码，绝对是效率提升的王道。
    + 通过 Alfred 和快捷键，就可以尽可能得减少切换成本，所以 [Hocus Focus - A Mac menu bar utility that hides your inactive windows](http://hocusfoc.us/) 自动隐藏其他窗口，大概是个伪需求。
    + 减少切换，亦为隔离任务。在单一任务无需切换的时候，如果你发现你还在切换，那就说明你并没有专注在当前任务，依然在分心而已。
    + 而大而全的应用也切中了少切换的首要要害，在 IDEA 中开发绝对比你同时打开多种工具要爽得多得多，并且和 Evernote 一样，也可以通过定制化使页面变得简洁。所以在机器性能够好的情况下，笨重的软件也变成了伪话题。
    + 再比如全局可显示，即每个 Desktop 都能随处打开的窗口就是一个痒点，比如 `F12` 之下的 iTerm2，以及 `Cmd + Space` Alfred 和 `^ + Cmd + N` 打开的 Evernote 通知栏小窗口。很爽，随时随地就是干。