---
layout: 
title: 写作系统：Mac OS X 环境下的各种最优配置
categories: [思考]
tags: [写作, Mac, 学习, PKM, 个人成长, 敏捷, 效率]
published: True

---

## 敏捷与个人成长

工具不再多，而是要定制化，深度适应个人需求，并应当 infrastructure as assets，每个程序员都应该有属于自己的一套工具箱，这些基础设施的配置是伴随一个人最珍贵的资产，这绝对是这个成长期需要注重的事情。

就像软件开发一样，一个人的成长也应有自己的方法论。人的一生若是顺风顺水一成不变的话，那未免太无趣了，正是由于世界的未知在等着我们去探索，不一样的经历才会让人感到惊喜和有趣。 新时代新变化，而敏捷中最重要的一大前提就是「拥抱变化」：

- 估算 >-< 不用执着于计划，计划永远赶不上变化
- 小步迭代 >-< 挽起袖子就是干，避免完美主义失败恐惧症
- Retrospective >-< Reflection
- 学习型组织 >-< 此刻没做好是因为过去没学习，从此恶性循环
- 非单一角色，可靠交付为导向 >-< 全栈性选手，懂得直击要害

相比于软件开发这件小事儿，健康地成长明显要更加重要。

## 新的起点：爱上写作

我在[个人知识管理：知识的三种形态](http://blog.jimmylv.info/思考/2015-10-09-three-types-of-knowledge/)这篇文章中将我对于 Knowledge 的认识分为三种： 已内化的「知识」、可整理的「资料」、不可控的原始「材料」。于我而言，上一个阶段也许就是懂得了如何（更丰富地更准确地）获取资源和（更方便快捷地）收集资源；那么接下来，我就需要去认真做好更重要的事情，也就是（更高效地）筛选资源以及（更有效地）整理和吸收资源，并真真正正地有利于自己的学习、工作、生活。

其实写作在最开始对我来说，只是一个和自己慢慢谈话并最终和解的过程。在高中时代，我有一个专门的本子，从前面翻，记录着我的每一次模拟考成绩，点连成线彰显着我进步的趋势，还有每次考后的自我分析；而从后面翻，则是我每一次或低谷或骄傲的自我谈话，每一次心情不好都是在笔墨的挥洒之下渐渐好起来，慢慢说服自己重新振作，坚持走下去。其实在那时候以及后来，都是更喜欢用笔在纸上写写字，还可以随意的画画图、理理逻辑，但是后来电脑用多了吧就发现自己写字实在太丑不能看了，还有个原因就是写字的速度太慢跟不上思维的速度了。不管是纸笔还是键盘，写作带给我的就是一份难得的宁静吧，也比较喜欢以文字的形式记录下所学到的知识，分享自己的心得和经验。况且在这样一个微博 140 字的时代，阅读长段文字都已经变得很难得了，更何况沉下心来写这么一大段文字呢，越难得越珍贵。

其实对于写作者来说，文字的力量更多的是在写作的时候，那是任由思维发散并集结成句的时刻，思考的过程才是更快乐的更有意义的。不断的思考才会将前面所提到的各种「材料」和「资料」内化成真正属于自己的「知识」，整理的过程或许痛苦，但也就是在这样的过程中大脑的思维结构才开始形成，快速而有效地建立属于自己的内部索引，就是学习的一种形态。

## 工作流如何影响专注力

一直以来都想好好总结一下做事情的工作流，类似于一种程序员思维吧，把要做的事情流程化并尽量简化其流程，而一般流程化的过程都可以被自动化。对于人来说，在工作流的确定和便利之后，偏可以在肌肉记忆下无意识完成相关操作，从而将自己的意识回归到真真正正的写作上来。

### 专注于单一任务

专注，是[这个时代最稀缺的能力](http://www.nowamagic.net/librarys/veda/detail/2755)。对于写作、写代码这类事情来说，单线程作战绝对是效率提升的王道，多任务切换的成本对人脑来说是非常巨大的。

使用（全局、局部）快捷键打开特定软件、特定功能，并形成肌肉记忆：
    - `^ + Number` 打开 Desktop，缺憾是不能打开全屏应用，故少用全屏为妙，当进入全屏后，即为专注于一个/两个软件的时候
    - `alt + Number` 打开常用的必用软件，比如 Chrome，Sublime，IDEA。多谢 [Snap - Launch apps in a snap!](http://indragie.com/snap/)
    - `Cmd + Number` 就是在特定软件中，打开不同的 Tab，比如 Chrome 中和 iTerm2 中的不同标签页。

减少切换，亦为隔离任务。在单一任务无需切换的时候，如果你发现你还在切换，那就说明你并没有专注在当前任务，依然在分心而已。而大而全的应用也切中了少切换的首要要害，在 IDEA 中开发绝对比你同时打开多种工具要爽得多得多，并且和 Evernote 一样，也可以通过定制化使页面变得简洁。所以在机器性能够好的情况下，软件太笨重显然也变成了一个伪话题。

+ 通过 Alfred 和快捷键，就可以尽可能得减少切换成本，所以 [Hocus Focus - A Mac menu bar utility that hides your inactive windows](http://hocusfoc.us/) 自动隐藏其他窗口，大概是个伪需求。
+ 再比如全局可显示，即每个 Desktop 都能随处打开的窗口就是一个痒点，比如 `F12` 之下的 iTerm2，以及 `Cmd + Space` Alfred 和 `^ + Cmd + N` 打开的 Evernote 通知栏小窗口。很爽，随时随地就是干。

自动整理，这是一个高阶话题，也就是达到自动化工作流的最高境界，在必要的时候输出固定规则下的内容，但此时也会出现很多没有经过大脑处理过滤的内容，所以只发生在外部索引而缺失了内部索引。但这个话题下的自动整理更倾向于自动化处理那些根本不值得要经过大脑处理的内容，也就是繁杂的琐事并不能够产生价值。

- 尽可能排除视觉干扰，使用 [Noodlesoft – Simply Useful Software](https://www.noodlesoft.com/) 可以实现桌面上文件的自动整理。
- Finder 中的 Smart Folder 可以自定义一些搜索结果集合，从而实现了在特定条件规则限制下的自动整合，也算是一种自动整理。

![](http://7xjbdq.com1.z0.glb.clouddn.com/images/2016/1463930568879.png)

## 写作工具篇

### Evernote 和 Sublime 的无缝链接

- Markdown 编辑端：Sublime 依旧是目前来说的最佳编辑方式
    + 除了不能再中文词组间跳转以外（这个可以在 Evernote 中做到）
    + 放弃在 Evernote 编辑 Markdown 并预览的想法（通常有借助 [AppleScript](https://github.com/sandai/madever) 实现）
    + 进一步学习 Sublime 中 [MarkdownEditing](https://github.com/SublimeText-Markdown/MarkdownEditing) 的快捷键，好用到哭，以及完美格式高亮。
- 富文本编辑端：
    + Evernote 作为富文本编辑的一端，主要功能更多在于预览显示（其中图片无法缩成 md link，故遮挡了视线）
    + check 一下 Evernote 在 [Mac OS X 下的文件系统](https://www.zhihu.com/question/20651262)是怎么样的，可以打开看到在 content 目录下。
- 版本管理：
    + 经过实际使用效果来说，并没有什么情况下是需要用到这个功能的，若一切都是同步到 Evernote 的，就并不会出现误删除的情况了，还有就是 Evernote 付费账号是有历史版本的。 [How to access and use note history – Evernote Help & Learning](https://help.evernote.com/hc/en-us/articles/208313858-How-to-access-and-use-note-history)
    + 而最近在用的 MarkEditor 是有自带的版本管理的，右键文件名就可以查看 History Versions。
    + 至于非自我产出的内容，比如 Session PPT，电子书，这些都可以到互联网上随时可找的，并不担心丢失。
    + 还有物理备份，即 TimeMachine 是同步到移动硬盘的，所以有了多重保障。

### Markdown 文件的预览和修改

使用 Markdown 进行书写的好处不必多说，但是在写作完毕过后，对于这篇文字来说更多的形态就是**阅读**和**修改**：

- 对于 Markdown 文件，直接打开是用 [Markoff: A Free Markdown Previewer for OS X](https://robots.thoughtbot.com/markoff-free-markdown-previewer) 进行预览，然后 `Cmd + E` 则是打开 Sublime Text / MarkEditor 来进行编辑。
- 而 Marboo 的作用就更加注重在对于文件夹级别的层级预览，在 Marboo 做打开和分享等操作最佳，特别是会自动切换预览当前正在被修改的文件。
- 通过 Marboo 能够直接把生成的 HTML 内容映射到 `http://192.168.199.123:56866/xxxx.html`，同一局域网下可直接访问，还有贴心的二维码。
- 如果需要映射到外网，那就在本地起了 Server 之后打开 [ngork - Secure tunnels to localhost](https://ngrok.com/) 神器来突破防火墙吧。

### 似乎完美解决了写作时的图片上传问题

- 换了个截图工具，[腾讯出品](http://sspai.com/33021)，可以直接截图后编辑，但是窗口截图的时候没办法消除阴影（虽然我觉得阴影挺好看的）。
- 于是我自己设了一个 Alfred 的 WorkFlow 用来关闭和打开系统自带截图的阴影。参考：[一篇文章，解决 Mac 截图的所有问题 | 领客专栏·Mac 玩儿法 | 爱范儿](http://www.ifanr.com/app/546621)
- 另外用上了一个好用 Alfred 的 WorkFlow，[tiann/markdown-img-upload: markdown图片实用工具](https://github.com/tiann/markdown-img-upload)，可以直接快捷键上传文件以及生产 md 链接。
- 进一步考虑 GIF 的录制，感觉小功能需要演示才倍感酸爽啊。我已经下载过的有 Gifrocket，是将视频转成 GIF 的，而[Mac 上怎么能少了一款好用的 GIF 录制工具？ - Pinapps - 感谢那些赐予我们力量的 apps - 知乎专栏](https://zhuanlan.zhihu.com/p/20732038?refer=pinapps)

![](http://7xjbdq.com1.z0.glb.clouddn.com/images/2016/1465614364872.png)

## Really cool => Fantastic!!!

- http://zrey.com/app/markeditor
- https://www.reflectapp.io
- https://www.evernote.com (use MardkownHere in web)

下一篇我就会根据应用场景来详细总结描述一下使用 MarkEditor 进行写作的过程，类似问答的形式会比较好，方便于初学者能够更好地理解。然后还要介绍一下 Reflection 在个人生活中是如何应用起来的，比如一些 App（如 Evernote 配合 reflectapp、Google 配合 Kifi）以及 Pocket 和 Kindle 的高阶用法。
