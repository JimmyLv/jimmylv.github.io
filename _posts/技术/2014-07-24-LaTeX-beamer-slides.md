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
\documentclass[xcolor=dvipsnames]{beamer}  %定义文件类型
\usetheme{Copenhagen}                      %使用主题
\usecolortheme{wolverine}                  %使用颜色主题
\usepackage{utopia}                        %字体
\usecolortheme[named=brown]{structure}     %改变主题内嵌结构的颜色
\usepackage{CJK}                           %中文包，如果全部英文可以不用

\begin{document}                           %总的开始

\end{document}                             %总的结束
```

你好