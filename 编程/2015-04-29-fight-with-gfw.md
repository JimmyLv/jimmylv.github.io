---
layout: post
title: '关于不同翻墙软件：GoAgent和ShadowSocks'
category: 编程
tags: [GFW]
published: false
---

## 伟大的 HTTPS

他们的实现原理各不相同，区别大致在于走的路径不同，比如 GoAgent 借助免费的 GAE，那是谷歌自己在亚洲拉的光缆，所以说还是有一些可用的 Google hosts，可以选择适合自己的、速度最快的 Google 可用 IP 段。[快速找到 Google 可用 Hosts 的方法 - 月光博客](http://www.williamlong.info/archives/3878.html)、[XX-Net 自动搜索可用 IP 的代码 - GitHub](https://github.com/XX-net/XX-Net)、甚至于[访问 Google 的神器：Chrome 的 QUIC 协议 - 月光博客](http://www.williamlong.info/archives/3879.html)。而 ShadowSocks 要自己先搭一个 VPS，然后再通过走 Socks5 的方式走出去，相同的技术点就是使用 HTTPS，这是加密的 HTTP 协议，GFW 是没有那个能力知道其中传输的是什么东西。

## 先决条件

使用的先决条件就是是需要不同的账号，GoAgent 需要自己去 GAE 上注册一个 appid，这里有教程：[申请 Google App Engine 并创建 appid](https://github.com/goagent/goagent/blob/wiki/InstallGuide.md)。而 SS 需要自己去 Linux 系统的 VPS 上安装配置 libev 版本的服务端，在这里感谢一下 Kimmy 给我的 ShadowSocks 账号。但是用起来的时候都是一样的，可以直接利用源码来修改自己的账号并且部署使用，再者也可以利用 GUI 客户端简化使用，直接输入相关账号信息就好了。

在使用的时候涉及到一点墙外/墙内服务器与自家 Mac/PC 的通信知识，两台电脑都是通过 IP 地址和端口来交流信息的，当然其中会涉及到不同的通信协议/方式（比如 HTTP、HTTPS、SOCKS 等），所以我们用的时候就需要设置和墙外服务器交互的本机端口。

## 代理方式

在代理的时候有全局/PAC/浏览器插件这么几种方式：

- 全局就是全部使用代理去访问所有网站，可想而知访问一些国内网站会变慢或者根本打不开。

- 而一般的 GUI 客户端也都集成了 PAC 代理，自动解析当前访问网站是否需要代理，一般用这个也就够了。

- 当然在浏览器插件里面也可以设置 PAC，访问该 PAC 的本地端口即可，然后浏览器插件就是可以设置自动切换，根据 Rule List 用不同的代理从而使不同的本机端口走不同的路径到达不同的墙内/墙外服务器。我用的 SwitchyOmega 插件还可以自己添加一些 Rule 访问一些不能访问而官方 List 没有加入的网站。

![image](https://raw.sevencdn.com/JimmyLv/images/master/images/tech/fight-with-gfw/Auto-Switch.png)

## HTTPS 错误

然后这里有一个从根本上杜绝 HTTPS 请求错误的方法。原先，一边解决该问题的方法是用 GoAgent 里面的 CA 证书替换原有站点的证书，如果你没有导入根证书，你用打开 twitter 这类强制 https 的站点就会被浏览器阻止并收到警告。

![image](https://raw.sevencdn.com/JimmyLv/images/master/images/tech/fight-with-gfw/HTTPS-Error.png)

在实际使用中就算导入了证书有时候也还是会出现错误，而且我记得知乎上面有讨论过有人伪造了 GoAgent 证书，所以说还是有一定风险的。

## 混合代理

所以我们设置一个名为 GA&SS Mixed 的混合代理，如下图：

![image](https://raw.sevencdn.com/JimmyLv/images/master/images/tech/fight-with-gfw/GA&SS-Mixed.png)

已知 GoAgent 使用本地端口 8103，而 Shadowsocks 本地端口为 1080。从而 HTTP、FTP 为未加密连接可填入 GoAgent 的代理端口配置，而在 SOCKS 代理中填入 ShadowSocks 的端口号，如此一来，HTTPS 就会自动走 ShadowSocks，未加密流量就会走 GoAgent，从而不用导入 GoAgent CA 证书。不过使用此方法带来的问题就是 HTTPS 的降速，除非你有速度良好的国外 VPS 用来设置 ShadowSocks，因为大部分国外服务器代理速度都拼不过 GAE 的，毕竟 Google 足够强大啊。

## 公司 VPN

其实到头来，目前对我来说最好的翻墙方式就是使用公司的 VPN，简直太爽！但是偶尔也连不上北京的服务器，还有不能上 Facebook 的时候开一个 GA&SS 代理就行了。
