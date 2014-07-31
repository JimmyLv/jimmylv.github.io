---
layout: post
title: LaTeX beamer制作幻灯片
category: 技术
tags: LaTeX
keywords: 
description: 
---

用LaTeX beamer制作幻灯片简洁优美，在需要很多数学公式的情况下很实用。这里我用我的第一份LaTeX beamer幻灯片代码为例说明。学习使用任何一种语言编程时，最重要的是对整个代码框架的理解。

beamer制作幻灯片的框架大致可分三级（其中for语句仅为便于理解，实际的LaTeX语句中并不会出现）如下：
>- 定义文件类型
>- 放入所有需要使用的主题和包
>- 总的开始
>>- 编辑幻灯片首页
>>- for i = 1,2,...,N
>>>- 开始编辑第i张幻灯片
>>>- 结束编辑第i张幻灯片
>>- end for
>- 总的结束

具体从代码看，首先是第一级结构：

```tex
\documentclass[xcolor=dvipsnames]{beamer}  %定义文件类型
\usetheme{Copenhagen}                      %此句及以下是我使用的主题和包
\usecolortheme{wolverine}                       %颜色主题
\usepackage{utopia}                             %字体
\usecolortheme[named=brown]{structure}          %改变主题内嵌结构的颜色
\usepackage{CJK}                                %中文包，如果全部英文可以不用

\begin{document}                           %总的开始

\end{document}                             %总的结束
```

在`总的开始`与`总的结束`之间写入如下代码，是为第二级结构：

```tex
\title[幻灯片缩略名]{幻灯片全名}           %以下是幻灯片首页的编辑
\subtitle{副标题}
\author{作者姓名}
\institute{作者所属学校}
\date[\initclock\tdtime]{\today}                     %总是显示当前的日期
\logo{\includegraphics[height=10mm]{yellowdeer.jpg}} %这是我的logo，如果不需要删掉词句即可
\begin{frame}
\titlepage
\end{frame}

\begin{frame}                              %开始编辑第i张幻灯片

\end{frame}                                %结束编辑第i张幻灯片

```

在`开始编辑第i张幻灯片`与`结束编辑第i张幻灯片`之间，写入具体第i张幻灯片的编辑代码，即第三级结构：

