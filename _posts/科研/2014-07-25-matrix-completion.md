---
layout: post
title: 低秩矩阵补全
category: 科研
tags: 矩阵补全
keywords: 矩阵补全，去中心
description: 
---
<html>
<head>
<script type="text/javascript" src="http://latex.codecogs.com/latexit.js"></script>
</head>
<body>


###问题描述:

如果有这样一个矩阵<a href="http://www.codecogs.com/eqnedit.php?latex=\mathbf{W}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\mathbf{W}" title="\mathbf{W}" /></a>**W**:


- 矩阵中有部分元素缺失
- 矩阵的秩rank(**W**)相较于矩阵维数来说很小，并作为先验已知


我们希望恢复那些缺失的元素，这个问题就是低秩矩阵补全问题。      


###思考过程:

- 需要恢复一个低秩矩阵，直接想法是 min rank(**W**)
- 但是rank(**W**)非凸，不好求解
- 核范数||**W**||是秩的凸近似，所以想到min ||**W**||*

###极小化核范数的集中式算法:

求解min ||**W**||*的集中式算法有很多，比如：


- singular value thresholding algorithm
- fixed-point shrinkage algorithm
- proximal gradient algorithm
- ADMM


但如果矩阵规模和秩增大，以上算法的计算代价也增大，因为它们都需要求解奇异值分解(SVD)。SVD中求伪逆的步骤运算量大，很耗费资源。因此需要想更好的方法，避免极小化核范数。

###极小化||Z-XY||F的集中式方法:

将问题写为min ||**Z-XY**||F，其中**Z**是对**W**的估计，在元素没有缺失的位置上**Z**和**W**的元素相同，**X**,**Y**是对**W**的乘法分解。介绍两种求解该问题的方法：


- nonlinear Gauss-Seidel method
- nonlinear SOR(Successive Over-Relaxation)-like scheme:LMaFit


其中SOR方法是GS方法的拓展，区别仅在于SOR方法中对于**X**的更新加了权重，并对权值进行更新。

###去中心式算法:

当矩阵规模大到一定程度时，集中式算法在计算能力上要求过高，普通计算机也许无法计算。这时，我们需要在由许多普通计算机作为节点组成的网络中运算，这需要实现去中心式计算。去中心式计算式很容易实现的，将**W**,**Z**,**Y**分别切块放在每个节点上，将**X**作为公共信息在网络各个邻居节点间交换，优化问题形式不变，但需要加上**X**(i)=**X**(j)的约束。而这样一个约束就引出了另一个子问题：一致平均(average consensus)问题。

关于一致平均问题的介绍请看：

- [《对于一致平均问题的理解》](http://painterlin.com/2014/08/22/Average-Consensus.html)
- [《动态一致平均问题的4篇论文》](http://painterlin.com/2014/08/31/Papers-about-average-consensus.html)



Here are my formulas
<div lang="latex">1+sin(x)^2+3</div>
<ul>
<li lang="latex">x^2+y^2+z^2</li>
<li>a^2+b^2</li>
</ul>
</body>
</html>



