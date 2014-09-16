---
layout: post
title: 对于一致平均问题的理解
category: 科研
tags: 矩阵补全
keywords: 矩阵补全，一致平均
description: 
---


最近几个月在研究分布式低秩矩阵补全的问题，参考文章[《低秩矩阵补全》][1]。

低秩矩阵补全问题的各类算法中，很关键的一个子问题叫做一致平均问题(Average Consensus)，而上一篇文章并没有对这个问题进行说明。那么，什么叫做“一致平均”呢？


###问题阐释：
<div>考虑一个有<img src="http://latex.codecogs.com/gif.latex?L" title="L" />个节点的网络，每个节点上存储一个关于自己的数值信息，叫做初值。一致平均问题就是使所有节点在算法停止的时候收敛到<img src="http://latex.codecogs.com/gif.latex?L" title="L" />个初值的平均。
</div>

<div>在分布式算法中，通常会存在这样一个变量<img src="http://latex.codecogs.com/gif.latex?\mathbf{X}" title="\mathbf{X}" />，它作为公有信息在网络中传递，每个节点储存自己的<img src="http://latex.codecogs.com/gif.latex?\mathbf{X}_{(i)}" title="\mathbf{X}_{(i)}" />。在总算法的每一次迭代中，每个节点<img src="http://latex.codecogs.com/gif.latex?i" title="i" />接收自己邻居节点传递过来的公有信息，然后与自己的私有信息共同计算出新的公有信息，并传给自己的邻居。我们需要保证每个节点上的公有信息<img src="http://latex.codecogs.com/gif.latex?\mathbf{X}_{(i)}=\mathbf{X}_{(j)}" title="\mathbf{X}_{(i)}=\mathbf{X}_{(j)}" />，使分布的算法以某种方式交流合作，以便获得最优解。这就是分布式算法中的一致平均问题。</div>

###问题分类：
根据节点上的数值信息是否随时间变化，又把一致平均问题分为：

- 静态一致平均 (Static average consensus)
- 动态一致平均 (Dynamic average consensus)

<div>
顾名思义，静态一致平均指节点上的初值不会发生变化，只需要保证最后每个节点都收敛到<img src="http://latex.codecogs.com/gif.latex?L" title="L" />个初值的平均值即可；而动态一致平均则是，节点上的数值不断发生变化，即<img src="http://latex.codecogs.com/gif.latex?\mathbf{X}_{(i)}" title="\mathbf{X}_{(i)}" />在<img src="http://latex.codecogs.com/gif.latex?t" title="t" />时刻的值并不一定与0时刻的值（初值）相同，我们使用不断变化的公有信息（因为公有信息不断在被更新），仍需要保证最后每个节点都收敛到<img src="http://latex.codecogs.com/gif.latex?L" title="L" />个初值的平均。相比于静态一致平均，动态一致平均问题更为棘手。
</div>

###求解方法分类：
在文章《低秩矩阵补全》的最后，提供一种求解方法的分类概念，将方法分为：

- 精确一致平均 (Exact average consensus)
- 不精确一致平均 (Inexact average consensus)

这又是什么意思呢？

<div>
在解决分布式低秩矩阵补全问题的时候，我们将算法分解两个子问题不断求解，一是交替极小化(Alternating minimization)得到每个节点的新的<img src="http://latex.codecogs.com/gif.latex?\mathbf{X}" title="\mathbf{X}" />,<img src="http://latex.codecogs.com/gif.latex?\mathbf{Y}" title="\mathbf{Y}" />；二是在网络中对<img src="http://latex.codecogs.com/gif.latex?L" title="L" />个节点的<img src="http://latex.codecogs.com/gif.latex?\mathbf{X}" title="\mathbf{X}" />求一致平均。对于第二个子问题，在每一次算法总的迭代中，都去求解精确的一致平均显然能够解决问题，但是因为一致平均也需要一定次数的迭代才能被解除，如果在总算法的每一次迭代中都去求精确的一致平均，则相当耗费计算资源，增加了算法的时间复杂度。
</div>

很自然地，我们会想到，既然一致平均只是矩阵补全的一个子问题，我们是不是可以通过某种松弛，来降低算法的时间复杂度并节省计算资源，同时仍旧保证总算法的收敛呢。这样，就提出了不精确的一致平均。

<div>
不精确一致平均，就是在每一次求解一致平均子问题时，只迭代一次或者若干次，而不是迭代所有<img src="http://latex.codecogs.com/gif.latex?N" title="N" />次（<img src="http://latex.codecogs.com/gif.latex?N" title="N" />可以很大），使每个节点`近似`的达到它们初值的均值。
</div>

###精确一致平均与不精确一致平均优缺点比较:

- 精确(Exact)求解：理论上容易证明，但计算代价通常比inexact方法高
- 不精确(Inexact)求解：理论分析上不好证明，除此之外具有exact不具有的所有优点，比如算法时间复杂度低，节省计算资源等等。

  [1]: http://painterlin.com/2014/07/25/matrix-completion.html
