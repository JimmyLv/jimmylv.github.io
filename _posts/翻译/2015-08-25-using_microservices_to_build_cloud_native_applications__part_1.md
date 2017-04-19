---
layout: post
title: 【译】使用微服务构建原生云端应用 - 第一部分
categories: [翻译]
tags: [Microservices, Cloud]
published: True

---

# 使用微服务构建原生云端应用 - 第一部分

原文地址：[Using Microservices To Build Cloud Native Applications – Part 1](http://ryanjbaxter.com/2015/07/15/using-microservices-to-build-cloud-native-applications-part-1/)

> In my [previous post](http://ryanjbaxter.com/2015/07/13/building-cloud-native-applications/) I described at a high level what it means to build a cloud native application and hopefully gave you an idea of why building applications in the cloud can be different than you may be used to. One thing many cloud native applications have in common is that they are often built using a microservices architecture. But before we talk about microservices lets talk about the types of applications most people are familiar with building today.

在[上一篇文章](http://ryanjbaxter.com/2015/07/13/building-cloud-native-applications/)中，我从更高层面上描述了云端原生应用的构建，期望让你明白在云上构建应用的方式和以往为何不同。云端原生应用的一个共同点就是，它们都使用微服务架构进行构建。但是在我们谈论微服务之前，让我们回顾一下目前人们所熟知的几种应用程序类型。

> Most applications people build today are 3-tier, monolithic applications. What do I mean by monolithic? Basically the entire application is deployed as a single entity. In Java terms this might mean when you deploy your application, you deploy the entire thing in a single WAR or JAR file. The fact that the application is monolithic is not a bad thing, but at some point most applications reach a certain size and gain a certain amount of complexity where the monolith is too hard to understand and is starting to hinder the productivity of the team. At this point the monolith is no longer suited for the cloud (or on premise) and something needs to change.

目前来看，大部分构建的应用都是三层式的、单一的庞大应用。monolithic是什么意思呢？基本上整个应用程序都被部署为一个整体。从Java的角度而言，这可能意味着当你部署应用的时候，每次都需要部署整个单独的WAR或者JAR文件。事实上，单一应用不是一件坏事情，但是当大部分应用达到一定的体量，具有一定的复杂性的时候，这将非常难以被理解，就会开始拖延整个团队的效率。在这点上来说，单一应用已经不再适用于这种云端部署（也许是在将来）和需求变化的情况了。

> Enter microservices. At a high level an application that is implemented using a microservices architecture is one that is composed of several (this could be 10s or 100s) completely independent “services” or apps that work together to produce the overall end user experience. Obviously since the term “micro” is used in microservices these services are meant to be small, lightweight, and focus on a single task. How small is small? That is the million dollar question.

接下来讨论微服务。从更高层面而言，如果一个应用采取微服务架构实现的话，是由几个完全独立的「服务」或应用组成，共同工作，从而提供整体性的用户体验。显然，「微」指的是使用微服务，这些服务意味着很小，轻量级，专注单一任务。但是「小」到底是多小？这是一个百万美元的问题。

> There is no one measurement that I can give you that determines the correct size of a microservice. Instead it is all about productivity and speed. If a service gets to the point where you feel it is doing too many things and is hard to understand and work with, than it is likely too big and should be split into more than one service.

我没有确切的手段来确定微服务的具体大小，然而这通常与效率和速度紧密相关。如果一个服务有很多地方让你感觉做了太多事情，并且难以理解和使用。那么这个服务就过于庞大，应该被分割成几个不同的微服务。

![](http://ryanjbaxter.com/wp-content/uploads/2015/07/micro-service-architecture.png)

> In addition to the small size of the code base, the team that works on each microservice is also small and compact. Each team for each microservice is composed of the developers, testers, product managers, etc. They act completely independent of each other team and each other microservice. This is a very important part of the microservices architecture. Microservices are not only about the technical architecture of your application, but also the architecture of you organization. There is no separate organizations for test, development, and product management. Each microservice is comprised of a team that has people who test, develop, do DevOps, and handles product management. That team focuses on that one service and that one service alone and are the only people responsible for that service.

除了代码库变小之外，开发微服务的团队也会变得小而精。每个微服务的团队都由开发、测试、产品经理等组成，他们都与其他团队和微服务彼此独立，这是微服务架构中非常重要的一部分。微服务不仅指的是应用程序的技术架构，也包括组织架构。这指的不是彼此分开的测试、开发、产品管理的独立组织，而是指每个微服务都包括了测试、开发、运维和产品管理人员。整个团队专注于单一服务，并且每个服务都由唯一的人来单独负责。

> I always think that looking at concrete examples is a good idea when talking about something new. I have been working on a cloud native application that uses microservices. The idea behind the application is pretty simple. As a developer advocate, I am always giving talks at conferences and people, usually, have questions about the topic I am speaking about. I wanted to make it easier for people to ask questions so I wrote an application that allows you as a speaker to create an entry for a session you are giving and then anyone that attends that session can go to the application select your session and ask a question about the topic you are presenting on. Attendees can ask questions via the application itself or they can text questions from their mobile device. As a speaker you can then reply to whatever questions are asked via the application and the user who asked the question will get a response via email if they submitted the question via the application or via text if they texted the question. The idea is simple and you can imagine it would be easy to implement that application as a traditional 3-tier monolithic app. In fact, that is how it started out, and here is what it looked like.

「事实胜于雄辩」，我认为谈论一件新事物的时候最好能有具体的实例。我已经在使用微服务构建云端原生应用了，应用背后的理念非常简单。作为一个技术拥护者，我总是在会议上发表演讲，人们通常都会对所讲内容有所疑问。为了使人们问问题能够变得更容易，我就创建了一个应用程序，可以让召开会议的演讲者为此创建一个条目，而与此同时，任何参会的人都可以选择该会议并且对所演讲的话题进行提问。参会者还可以通过应用程序直接问问题，或者直接在移动设备上输入问题。作为演讲者就可以回复被问到的问题，然后提问者也能够得到邮件答复，或者通过文本的形式直接展示在应用程序上。这个想法很简单，你也可以想到它很容易通过传统的三层式单一应用结构来实现。事实上，这是最开始的时候的样子。

![](http://ryanjbaxter.com/wp-content/uploads/2015/07/intro-to-microservices.jpg)

> As you can see the monolith (the big blue square in the middle) had a number of components in it. It contained the client side code served to the browser, REST APIs the client side code used, a REST API for Twilio (for texting), and some code which took care of sending the emails/texts for answers. All the details about the sessions and the questions asked during those sessions was stored in a single DB. Like I said, a very traditional application architecture, and when deployed to the cloud it worked fine, no issues.

如你所见，单一应用（中间的蓝色方块）包含了很多组件。它包含了服务于浏览器的客户端代码、客户端代码所使用的REST APIs、Twilio（文字输入）的REST API以及用于发送邮件或文本答案的代码。所有关于演讲和在提问的细节都存储在一个数据库中。就像我所说的，一个非常传统的应用结构，已经部署在云服务上，没有任何问题。

> In fact at this point I would like to bring up an important point. In my own personal opinion (and not everyone agrees with me), I think that for certain types of applications a monolithic architecture will work fine in the cloud. For all the benefits of adopting microservices, one of the drawbacks is complexity (in how all the services works together, not in the individual services themselves). So if your application is simple enough and you are not experiencing some of the problems I have mentioned than it is OK to build a monolithic application and run it in the cloud. However, most production applications are not simple and quickly approach that threshold where the complexity (in the code) and size of the application starts effecting the stability of the application the performance of the team. Since I wanted to explore how I could transition this application to use microservices I decided to break this application apart, but that is not to say that this app the way it was originally architected was bound for failure.

事实上，我更想抛出另外一个很重要的点。在我个人观点中（不是所有人都认同），我认为某些确定类型的应用程序采用单一结构可以在云上运行得很好。为了能够受益于微服务的优点，其中一个缺点就是复杂度（在于服务之间如何共同工作，而不是独立工作）。所以说，如果应用程序足够简单，你并不会遇到我所提到的那些问题，构建部署于云上的单一应用也就是没什么问题的。但是，大部分产品层面的应用程序都不是那么简单，而且很快就能达到复杂度的下限（代码层次上），应用大小也开始影响应用的稳定性和团队的表现。因此我想要探索如何将其转化为使用微服务的应用，拆分成不同的应用部分。但这并不是说，这种最开始的架构方式是失败的。

> Lets look at a couple of problems that this monolithic architecture could cause in the cloud. First up failure. What happens if there is a problem in the Sessions API component of my application. Maybe it is chewing up a huge portion of the CPU, or maybe it just crashes. What happens to my application?

让我们看看单一结构在云上可能导致的一些问题。首先是失败，如果我的应用程序中的一个Sessions API组件出现问题，将会发生什么。也许是占用了CPU的大部分内存，也许直接导致崩溃。我的应用程序将会怎么样？

![](http://ryanjbaxter.com/wp-content/uploads/2015/07/intro-to-microservices2.jpg)

> Thats right, pretty the entire application will be effected by this. If it crashes all the other components of my application come crashing down with it. Maybe it is not even a problem with my code, maybe it is the networking or hardware underneath my application provided by the cloud (stuff that is out of my control). Whatever the reason for the problem is, my entire application is unavailable even if there is a problem with just a single component. This makes my application very fragile and is not what we want, fragility is the enemy.

对头，整个应用将会被这个部分所影响，这一个部分崩溃直接导致了其他组件也无法使用。这甚至不是我的代码问题，也许是由于网络或者应用程序之下的云服务的硬件问题（一些在我掌控之外的事情）。不论问题的原因是什么，如果有一个单独的组件出现问题，整个应用就将无法使用。这将会使得应用变得非常脆弱，这不是我们想要的，**fragility is the enemy**。

> The next problem with the monolithic architecture is scalability. Lets look at what scaling the monolith looks like.

接下来的问题就是单一结构的可扩展性，让我们来看看扩展过后的样子。

![](http://ryanjbaxter.com/wp-content/uploads/2015/07/intro-to-microservices3.jpg)

> Petty much what you would expect right? Instead of 1 instance of the monolith running, I have 2 instances running with a load balancer sitting infront of both instances routing requests between the two. There is nothing wrong with this configuration, it will work fine. Conceptually though, it is probably not what I really need. In all reality, if I am at the point where I need to scale my application it is more likely that it is just one component of my application that needs to scale. For example, say the Sessions API component is under a lot of load and can’t handle the number of requests being issued to it. Scaling that component horizontally will solve the issue, but since my application is a monolith I can’t just scale that one component I have to scale the entire app. Probably not a big idea when it is just one component of our monolith that needs to scale, but what if I have 2 or 3 components that need to be scaled? Maybe the Sessions API component would be fine with 2 instances but the Questions API component needs 5. My only option is to scale my monolith up to 5 instances even though most of the other component don’t need that many instances. This is a big waste of resources, and in the cloud that means wasted money!

比你想象的多得多，对吧？不只是一个应用在运行了，而是需要一个负荷均衡器来处理两个实例的路由请求。这样的配置没什么问题，也可以运行良好。理论上尽管如此，但这可能并不是我真正需要的东西。现实情况是，如果我需要进行扩展的时候，只需要为应用扩展其中一个组件。举个例子，Session API这个组件处于巨大的负荷之下，无法处理那么多被发送的请求。水平扩展组件可以解决这个问题，但是由于我的应用是单一结构，所以我并不能只扩展一个组件，而是不得不去扩展整个应用。可能在只有一个组件需要扩展的时候问题不大，但是如果有两个或者三个组件需要扩展呢？也许Session API组件只可以与两个实例正常工作，但是Question API组件却需要五个。唯一的选择就是将我的单一应用扩展到五个实例，甚至大部分其他的组件都不需要这么多实例。这是一种极大的资源浪费，在云端这就意味着浪费很多钱。

> In addition to the problems with monolithic applications described above we also have the problem of working with huge monolithic code bases. Consider when someone new joins the team to work on a monolithic application, how long would it take them to understand how the application works? The answer is a very long time, if ever. I know from experience. I worked on a giant, 25 year old, monolithic application in my previous role at IBM, and I only understood a very small piece of how that application worked and I worked on it for 5 years! Other issues include the time needed to build, test, and deploy monolithic applications. It is incredibly slow and fragile process (remember fragility is the enemy). If you have worked on a monolithic application, you know how painful this process can be. You get to the point where you are ready to release and someone finds a bug in a single small component. This stops everything, everything needs to go through the release process all over again, that is easily a multi-day process. This is just not acceptable when you are looking to be agile and move with speed.

除了上文描述的单一应用所产生的问题之外，我们使用庞大的单一代码库也会出现问题。考虑到新人加入开发单一应用的团队，他们需要多久才能够理解应用是如何工作的？答案就是时间非常长，如果可以的话。从经验得知，我之前在IBM开发一个庞大的、具有25年历史的单一应用。尽管我工作了五年，我也只是理解了整个应用工作的一小部分。其他的一些问题包括构建、测试、部署，这其中的过程是非常缓慢和脆弱的（记住脆弱就是敌人）。如果你也曾在一个单一应用项目上干过，你也会知道这个过程有多么痛苦。当你准备好发布的时候，发现有人在一个小模块中找到一个小bug，这将会停止所有事情，所有事情都需要重新来过。这很可能就是很多天的一个过程，如果你想要敏捷和前进速度的时候，这将是无法接受的。

> So how does changing the application to a microservices architecture help solve some of these problems? Let take a look at how the application looks once we move to using microservices.

所以将应用改成微服务架构是怎么帮助解决这些问题的呢？让我们看一下使用微服务的应用程序长什么样子。

![](http://ryanjbaxter.com/wp-content/uploads/2015/07/intro-to-microservices4.jpg)

> For the most part, what I have done here is take each light blue box from the monlithic architecture and made it its own app, or microservice. The SendGrid and Twillio services were also broken out into separate apps, I will address why I did this later on when we talk about scalabilty. From a fragility point of view, this architecture if much more resilient. Lets take the same example from above where the Sessions Service crashes, hangs, or goes down due to the infrastructure underneath it. In this architecture, if that happens, the client side code will still be served to clients, and the Questions, Reply, SendGrid, and Twilio services all will continue to function as before. Will the app behave perfectly with the Sessions Service unavailable? No. Is it better than if the entire application was down, YES!

在大多数情况下，我能够做的就是从单一架构应用中抽出每个轻量的蓝色盒子，使之成为独立的应用或微服务。SendGrid和Twillio服务也可以分解成独立的应用，我将会在讨论可扩展性的时候讨论为什么要这样做。从脆弱性这个角度来说，这种架构将更富有弹性。让我们举一个跟前面一样的例子，如果Sessions服务崩溃了、失效了或者由于底层的硬件设施事故而发生了故障。在这种架构中如果发生类似情况，客户端代仍然可以服务于客户。Questions、Reply、SendGrid和Twilio服务都可以像之前一样正常工作。没有了Sessions Service应用还会表现得那么完美吗？不会。但是这比整个应用瘫痪要好得多，对吧？

> What about scalability with this architecture? It is much better than before because I can scale each service independently of the other.

那这种架构的可扩展性如何呢？这也比之前好得多，因为我可以为每个独立于其他的服务进行扩展。

![](http://ryanjbaxter.com/wp-content/uploads/2015/07/intro-to-microservices5.jpg)

> In the above picture you can see I am able to scale the Sessions Service without scaling any other part of the application. The microservices architecture allows me to scale only the components of my application that need it. This is the reason for the changes I made to the SendGrid and Twilio services. These two services are responsible for sending out replies to questions via email or text. As you can imagine it might be easy for them to become overloaded with many speakers replying to questions at once. At the same time it is not important that those replies go out the second the speaker sends them, so in my opinion, this was the perfect place to use a message queue. The reply service receives replies that need to be sent out and just places them in a queue, which is a very quick operation. The SendGrid and Twilio services are more like workers which just take replies out of the queue and sends them along. This allows the reply service to handle much more load and at the same time I can scale the SendGrid and Twilio services up or down essentially creating more or less worked to handle whatever is in the queue.

如图所示，我可以只扩展Session服务而不用去扩展应用的其他任何部分。微服务架构可以让我只扩展应用程序中所需要的那个组件。这也是为什么我对SendGrid和Twillio服务做出了改变，这两部分可以通过邮件或文本信息发送问题的回复。可以想象的是，当很多演讲者同时回复问题的时候，reply服务很容易就过载了。与此同时，演讲者将回复发送出去的那一秒并不重要，所以我的观点是，这时使用消息队列是最好不过的了。reply服务接受回复，只需要将它们放到队列中，再将其发送出去，这个操作就很高效。SendGrid和Twillio服务更像一个工人，能够将回复从队列中取出来，再单独发送出去。这将使得reply服务能够处理尽可能多的负载。与此同时，我也可以增加或者减少SendGrid和Twillio的服务，本质上就是创建处理消息队列的多和少而已。

> There is one part of the microservices architecture in the pictures above that I have not addressed yet, and that has to do with the databases. In the monolithic architecture there was a single database, but in the microservices architecture there are 2, one database for the Questions Service and one for the Sessions Service, why? One of the golden rules of microservices is that each service should be independent of each other. If 2 services are sharing the same database than they are not truly independent because changes or problems with the database can effect one or both services. For this reason if a microservice needs to persist data, than it should do so in its own database. This in itself introduces a new set of problems and is one of the reasons why microservices architectures can be more complicated than monolithic architectures. The most challenging problem this introduces is a data consistency problem because you could be having to persist the same data in 2 different databases. The approach that most microservice applications take to solve this problem is to apply the [principal of eventual consistency to their data](http://www.ben-morris.com/eventual-consistency-and-the-trade-offs-required-by-distributed-development/), meaning the data in the different databases may not be consistent for some period of time but eventually it will be. This topic deserves its own blog post so I won’t go into it here, but try searching the “Internets” and I am sure you will find much more information on various approaches to this problem.

这一部分是我在微服务架构中没有提到的数据库部分，可以从上面的图片中看到。在单一架构中数据只有一个，但是在微服务架构中有两个，一个是Questions Service数据库，一个是Sessions Service数据库。为什么呢？一个微服务的黄金准则就是保持每个服务器彼此独立。如果两个服务共享同一个数据库，那就不是真正的独立。因为数据的变化和问题都会影响到另一个或共同的服务。因此，每个微服务都需要一个自己的数据库来进行数据持久化。这本身引入了一系列的新问题，其中之一就是为什么微服务架构要比单一架构更加复杂。最具有挑战性的问题是介绍数据的一致性问题，因为你可能需要在两个不同的数据库中分别存储同样的数据。大多数微服务应用采用的解决方案是采用[最终数据一致的原则](http://www.ben-morris.com/eventual-consistency-and-the-trade-offs-required-by-distributed-development/)，这意味着在不同数据库的数据在不同时间段可能是不一样的，但最终会是一样的。这个话题已经在其他博客中有所探讨，所以我在这里就不再深究。但是可以尝试搜索一下“Internets”，你肯定会找到各种关于这个问题解决方案的信息。

> What about the code base of the application? Once I split the monolithic application up into microservices I actually created several code bases. Each microservice has its own git repo, its own build pipeline, its own defect tracking system. Remember above where we talked about how each microservice needs to be independent of each other? Well this not only applies to data storage but also source control. If I put all the code for each microservice in a single git repo (which is what I did at first) than changes to that git repo effect all microservices. For example, if for some reason I need to create a branch just to work on a defect in one microservice I end up creating a branch for all microservices. This is not really what I want to do and can have effects on the other services (ie merging).

那这种应用的代码库如何呢？一旦我将单一应用分解成微服务，实际上就创建了多个代码库。每个微服务都有属于自己的git仓库，自己的构建流程，自己的问题追踪系统。记住在这之前我们所讨论的，每个微服务为何需要独立于其他服务？这不仅仅是可以采用不同的数据存储，也包括资源掌控。如果我将每个微服务的所有代码都放到一个git仓库中（我最开始所做的那样），那么git仓库的改变将会影响所有的微服务。例如，如果我只是想为一个微服务的defect创建一个分支，结果却为所有的微服务都创建了分支。这并不是我真正想做的事情，会对其他服务产生影响（即merge）。

> Since each microservice has a very small footprint from a code point of view, on boarding new developers to work on a microservice is much easier. The smaller code base makes it much easier to learn. In addition I can do releases of each microservice independent of the others. I no longer have the problem of a bug being found at the last minute in a single component that blocks the entire release. If one microservice has a bug we can go back and address that bug while the other microservices continue to move forward unaffected.

由于每个微服务都有非常小的代码记录点，对于新的微服务开发者来说就变得简单了，这种更小的代码库也更容易学习。除此之外，我也可以对每个微服务进行独立发布，不会在最后一分钟只是因为一个组件的小bug就停止了所有的发布。如果一个微服务有bug我们可以回去讨论这个bug，而其他的微服务则可以继续向前而不用受影响。

> Wow that was a lot to take in right? And guess what, we are only part way there! My application’s architecture is certainly better now that it is using microservices but not perfect, there are still one or two problems we need to address. I think I will let everyone digest this blog post first before we dive into part two and address some of these issues.

到这里已经很多了，对吧？猜猜怎么着，这只是其中的一部分。我的应用就使用了微服务架构，虽然并不完美而且依然存在问题，但是现在看起来确实好多了。我想我会让大家先消化完这篇博客，然后再进入到第二部分来讨论其中的问题。

* * *

> For more detailed information on microservices I suggest you read [Marin Fowlers and James Lewis post on the topic](http://martinfowler.com/articles/microservices.html). There are many other resources on the internet that discuss the topic in great detail. If you are one of those people that fancies reading books, I suggest you check out this [one on microservices](http://shop.oreilly.com/product/0636920033158.do). I haven’t read the whole thing yet, but so far so good in my opinion. There is also a recently released [RedBook from IBM on microservices](http://www.redbooks.ibm.com/redpieces/abstracts/sg248275.html?Open), I have not read this one yet so can’t offer any thoughts on it. In addition to the RedBook there is a nice interview with[Constant Contact](http://www.constantcontact.com/home-page?s_tnt=68097:20:0) done by my colleague [Carlos M Ferreira](https://bluemixstirred.wordpress.com/) where they discuss how Constant Contact is using microservices.

有关于微服务的更多信息，我推荐你去阅读[Marin Fowlers和James Lewis有关于这个话题的文章](http://martinfowler.com/articles/microservices.html)。在网络上有很多其他有关于此话题细节的资源。如果你是热衷于读书的人，我向你推荐这本书[one on microservices](http://shop.oreilly.com/product/0636920033158.do)。我还没有完全读完，但是目前为止我感觉非常不错。这还有一本刚发布的[RedBook from IBM on microservices](http://www.redbooks.ibm.com/redpieces/abstracts/sg248275.html?Open)，我还没读过，所以无法提供任何意见。除了这本RedBook以外还有一个非常不错的访谈[Constant Contact](http://www.constantcontact.com/home-page?s_tnt=68097:20:0)，这是在我的大学[Carlos M Ferreira](https://bluemixstirred.wordpress.com/)中他们所讨论的Constant Contact是如何使用微服务的。