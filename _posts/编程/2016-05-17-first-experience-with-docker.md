---
layout: post
title: Docker 初体验
categories: [编程]
tags: [Docker, DevOps, Deploy]
published: False

---

## 上手:

- [Install Docker on OS X](https://docs.docker.com/mac/step_one/)，这个官方 Getting Start 很赞啊，较下面的链接要新。
- [Installation on Mac OS X](https://docs.docker.com/engine/installation/mac/)

安装 Docker Toolbox 的时候可以看到 VM VirtualBox 在于其中，一般 Mac 上都是已安装的，若不是最新版会有更新的 Action，如果没有安装就需要安装了，所以 VM 也算 玩 Docker 的一个必备选项。安装完 Toolbox 就会获得 `docker-machine`, `docker`, `docker-compose` 的命令。与此同时我们用 `vagrant` 来方便管理我们的虚拟机配置，以及连接到 VM 上去操作 Docker，并不直接在 Mac 玩耍，其中有 forward port，shared `workshop` folder。

![](//o7mw3gkkh.qnssl.com//docker%20-%20THE%20WORKSHOP%20ENVIRONMENT.png)

值得一提的是 `Docker Engine for running the docker binary`，不同的系统上的 Docker Engine 是不一样的，因为不同可执行的操作系统文件的命令是不一样的，相当于作为中间层统一了接口给 Docker 内部的操作提供便利。基本概念就是，Docker share OS（Linux kernel），在 OS 层级之上拥有 magic black box，并将模拟一些 xx，称之为 namespace。

Linux容器工具有很多，OpenVZ、LXC、Docker、Rocket、Lmctfy等等，大都是基于Linux内核提供的两个机制：Cgroups（实现资源按需分配）和Namespace（实现任务隔离）。

![](//o7mw3gkkh.qnssl.com//docker%20-%20CONTAINERS%20AS%20LIGHTWEIGHT%20VMS.png)

集装箱的例子很赞，统一了形式，可以装任何东西。但是 Containers 的概念并不是出自 Docker，只是它实现了一个好的标准，而且 API 友好，生态完善，另外，赶上了好时代，毕竟 DevOps，MircoServices 等等的概念现在太火热。

![](//o7mw3gkkh.qnssl.com//docker%20-%20standard%20containers.png)

封装好 Container 之后对于 Developer 和 DevOps 的完美角色友好。

![](//o7mw3gkkh.qnssl.com//docker%20-%20separation%20of%20concerns.png)

Docker 的架构，以 Host 的方式区分 Container，从 Image （read-only templates） 而来，并且可以 pull from register，可私可公。

![](//o7mw3gkkh.qnssl.com//docker%20-%20DOCKER%20ARCHITECTURE.png)

Layer by Layer，按层级寻找文件，并不删除真正的 Read-only 文件，并带来了很多好处，快准省。

![](//o7mw3gkkh.qnssl.com//docker%20-%20SHIPPING%20EFFICIENTLY.png)

## [VMs VS Containers](http://www.zdnet.com/article/what-is-docker-and-why-is-it-so-darn-popular/) & [Docker - the open-source application container engine](https://github.com/docker/docker#better-than-vms):

- The key difference between containers and VMs is that while the hypervisor abstracts an entire device, containers just abstract the operating system kernel.
- Hypervisors can do that containers can’t is to use different operating systems or kernels; With Docker, all containers must use the same operating system and kernel.
- Couldn't care less about running multiple operating system VMs. Getting more applications running on the same hardware can save a data center or cloud provider tens-of-millions of dollars annually in power and hardware costs.
- Much easier and safer to deploy and use than previous approaches, with the other container powers, including Canonical, Google, Red Hat, and Parallels.
- Developers can use Docker to pack, ship, and run any application as a lightweight, portable, self sufficient LXC container that can run virtually anywhere.

## 实际操作 Image

BUILDING IMAGES WITH A DOCKERFILE

- Working with Docker from the command-line
- Building and tagging images
- Working with a private registry
- Launching and linking containers
- Using Docker Compose to simplify launching an application stack


## 疑问？

- Linux 基础： cgroups 和 namespace 两个内核模块
- 真实世界的 container 技术，比如云计算（由于我们 workshop 依然是运行在 VM 当中。
    + BaaS：http://zhihu.com/question/22969309/answer/30865048

