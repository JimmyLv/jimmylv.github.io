---
layout: post
title: LaTeX beamer制作幻灯片
category: 技术
tags: LaTeX
keywords: 
description: 
---

用LaTeX beamer制作幻灯片简洁优美，在需要很多数学公式的情况下很实用。这里我用我的第一份LaTeX beamer幻灯片代码为例说明。学习使用任何一种语言编程时，最重要的是对整个代码框架的理解。

beamer制作幻灯片的框架是：

```
\documentclass[xcolor=dvipsnames]{beamer}
\usetheme{Copenhagen}%Warsaw,Berkeley,AnnArbor,Berkeley好看,Pittsburgh好看,Luebeck,JuanLesPins,
%Dresden,Marburg,Dresden,Antibes,Berlin,Ilmenau,Singapore,Copenhagen好看,Frankfurt,Madrid,Hannover,boxes,
%Szeged,Montpellier,Goettingen,Boadilla,PaloAlto,Rochester好看
\usecolortheme{wolverine}%crane黄,albatross全蓝,wolverine黄&橘黄,
%\usefonttheme{serif}%字体
\usepackage{utopia}%字体,times,helvet,bookman,chancery,euler,utopia,palatino,newcent
\usepackage[timeinterval=1]{tdclock}
%\beamersetaveragebackground{black!10}%设置背景色
\usecolortheme[named=brown]{structure}
\usepackage{CJK}
```

你好