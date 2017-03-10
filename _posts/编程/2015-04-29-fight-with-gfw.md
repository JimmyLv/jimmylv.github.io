---
layout: post
title: "关于不同翻墙软件：GoAgent和ShadowSocks"
category: 编程
tags: [GFW]
published: true
---

## 伟大的HTTPS

他们的实现原理各不相同，区别大致在于走的路径不同，比如GoAgent借助免费的GAE，那是谷歌自己在亚洲拉的光缆，所以说还是有一些可用的Google hosts，可以选择适合自己的、速度最快的Google可用IP段。[快速找到Google可用Hosts的方法 - 月光博客](http://www.williamlong.info/archives/3878.html)、[XX-Net自动搜索可用IP的代码 - GitHub](https://github.com/XX-net/XX-Net)、甚至于[访问Google的神器：Chrome的QUIC协议 - 月光博客](http://www.williamlong.info/archives/3879.html)。而ShadowSocks要自己先搭一个VPS，然后再通过走Socks5的方式走出去，相同的技术点就是使用HTTPS，这是加密的HTTP协议，GFW是没有那个能力知道其中传输的是什么东西。

## 先决条件

使用的先决条件就是是需要不同的账号，GoAgent需要自己去GAE上注册一个appid，这里有教程：[申请 Google App Engine 并创建 appid](https://github.com/goagent/goagent/blob/wiki/InstallGuide.md)。而SS需要自己去Linux系统的VPS上安装配置libev版本的服务端，在这里感谢一下Kimmy给我的ShadowSocks账号。但是用起来的时候都是一样的，可以直接利用源码来修改自己的账号并且部署使用，再者也可以利用GUI客户端简化使用，直接输入相关账号信息就好了。

在使用的时候涉及到一点墙外/墙内服务器与自家Mac/PC的通信知识，两台电脑都是通过IP地址和端口来交流信息的，当然其中会涉及到不同的通信协议/方式（比如HTTP、HTTPS、SOCKS等），所以我们用的时候就需要设置和墙外服务器交互的本机端口。

## 代理方式

在代理的时候有全局/PAC/浏览器插件这么几种方式：

- 全局就是全部使用代理去访问所有网站，可想而知访问一些国内网站会变慢或者根本打不开。

- 而一般的GUI客户端也都集成了PAC代理，自动解析当前访问网站是否需要代理，一般用这个也就够了。

- 当然在浏览器插件里面也可以设置PAC，访问该PAC的本地端口即可，然后浏览器插件就是可以设置自动切换，根据Rule List用不同的代理从而使不同的本机端口走不同的路径到达不同的墙内/墙外服务器。我用的SwitchyOmega插件还可以自己添加一些Rule访问一些不能访问而官方List没有加入的网站。

![image](//o7mw3gkkh.qnssl.com//public/img/tech/fight-with-gfw/Auto-Switch.png)

## HTTPS错误

然后这里有一个从根本上杜绝HTTPS请求错误的方法。原先，一边解决该问题的方法是用GoAgent里面的CA证书替换原有站点的证书，如果你没有导入根证书，你用打开twitter这类强制https的站点就会被浏览器阻止并收到警告。

![image](//o7mw3gkkh.qnssl.com//public/img/tech/fight-with-gfw/HTTPS-Error.png)

在实际使用中就算导入了证书有时候也还是会出现错误，而且我记得知乎上面有讨论过有人伪造了GoAgent证书，所以说还是有一定风险的。

## 混合代理

所以我们设置一个名为GA&SS Mixed的混合代理，如下图：

![image](//o7mw3gkkh.qnssl.com//public/img/tech/fight-with-gfw/GA&SS-Mixed.png)

已知GoAgent使用本地端口8103，而Shadowsocks本地端口为1080。从而HTTP、FTP为未加密连接可填入GoAgent的代理端口配置，而在SOCKS代理中填入ShadowSocks的端口号，如此一来，HTTPS就会自动走ShadowSocks，未加密流量就会走GoAgent，从而不用导入GoAgent CA证书。不过使用此方法带来的问题就是HTTPS的降速，除非你有速度良好的国外VPS用来设置ShadowSocks，因为大部分国外服务器代理速度都拼不过GAE的，毕竟Google足够强大啊。

## 公司VPN

其实到头来，目前对我来说最好的翻墙方式就是使用公司的VPN，简直太爽！但是偶尔也连不上北京的服务器，还有不能上Facebook的时候开一个GA&SS代理就行了。