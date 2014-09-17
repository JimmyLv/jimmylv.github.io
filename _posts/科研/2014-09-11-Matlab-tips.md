---
layout: post
title: Matlab科研小贴士
category: 科研
tags: 矩阵补全 Matlab
keywords: 矩阵补全，Matlab
description: 
---

使用MATLAB运行算法程序时，可能遇到各种各样的报错。比如，为了保护隐私数据，我在分布式矩阵补全算法中加入随机矩阵之后，某项变量在运行几百步之后会出现NaN报错。我只根据算法顺序去分析问题出现的可能原因，并修改程序。感觉并没有很好地利用MATLAB的强大功能去锁定症结所在。幸运的是，[施伟](http://home.ustc.edu.cn/~shiwei00/index.html)大师兄当时和我在一起，他非常热心地帮我分析问题，教我以后遇到类似状况应该怎么去分析与思考。和大师兄讨论了半小时，感觉自己收获不少。

这篇文章会陆续记录下自己使用MATLAB的体会，以及解决问题的一些技巧。

### Clear
运行一段代码前通常需要将工作空间里的已有数据清除掉。只需要在编辑有实际意义的代码之前写下如下代码：

```matlab
clc; clear; close all;
```

### Random Seed 
为了保证程序在相同环境下运行以便测试某一个或几个改变对于算法的影响，在使用各种random命令时，需要设定固定种子。这样就不会因为每次随机产生的序列不同而影响程序运行结果。设置随机种子的代码如下：

```matlab
%% random seed
%seed=round(5000*rand);       % use this line if you set a random seed
seed=3302;    % use this line if you set a fixed seed. 3302 can be replaced by other numbers.
fprintf('Seed = %d\n',seed);  % print the current seed 
if exist('RandStream','file')
   RandStream.setGlobalStream(RandStream('mt19937ar','seed',seed));
else
   rand('state',seed); 
   randn('state',seed^2);
end
```

### NaN
NaN是Not a Number的缩写。当某变量显示NaN时，表示该变量是不明确的数值结果。比如0/0、inf/inf等运算会出现NaN报错。遇到这种情况，首先判断NaN出现在哪一步：

```matlab
if isnan(norres)    %括号里是变量名。判断norres是否为NaN，若是，则在该步暂停程序。
    keyboard;
end
```
再在命令窗里单独查看与该变量有关的其他变量，从而排除正常变量，获知究竟是哪个或哪几个变量出了问题，变为无穷大或无穷小。再检查与这些变量有关的算法。


### SaveAs
若需要比较各参数对算法性能的影响，通常是在程序中修改参数运行，得到算法收敛精度与迭代次数的曲线图。再根据曲线图反向思考修改哪些参数有效。这个过程需要保存产生的大量图片。可以使用`hold on`命令将所有虚线画在同一张图上，也可以使用`saveas`将所有图片自动保存。

```matlab
%% plot
figure(1)
semilogy(1:iter,y_axis(1:iter),'b-');  %b：蓝色。－：线段形状
set(gca,'fontsize',12);
grid on;
xlabel('\fontsize{12}\it Iteration'); ylabel('\fontsize{12}\it Normalized residual');
legend('\fontsize{12}\it text');       %text：这条蓝色代表什么
hold on
saveas(gcf,'filename','fig')           %filename：将图片保存为这个名字。fig：保存为fig格式
```

注意，在使用`hold on`命令时，应该保留上次程序运行后产生的各种数据。即不能在程序中写类似与`clear all`之类的清除语句，否则上次曲线图也将被删除。

### 矩阵规范化
已知满秩矩阵A，进行下面操作使其所有奇异值均为1。

```matlab
[u s v]=svd(A);
A=u*v';
```


