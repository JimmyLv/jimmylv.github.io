---
layout: post
title: LaTeX beamer制作幻灯片
category: 技术
tags: LaTeX
keywords: 
description: 
---

用LaTeX beamer制作幻灯片简洁优美，在需要很多数学公式的情况下很实用。这里我用我的第一份LaTeX beamer幻灯片代码为例说明。学习使用任何一种语言编程时，最重要的是对整个代码框架的理解，本文重点讲框架。


###代码框架理解

beamer制作幻灯片的框架大致可分三级（其中for语句仅为便于理解，实际的LaTeX语句中并不会出现）如下：

- 定义文件类型
- 放入所有需要使用的主题和包
- 总的开始
	- 编辑幻灯片首页
	- for i = 1,2,...,N
		- 开始编辑第i张幻灯片
		- 结束编辑第i张幻灯片
	- end for
- 总的结束


###一级结构代码

具体从代码看，首先是一级结构：

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


###二级结构代码

在`总的开始`与`总的结束`之间写入如下代码，是二级结构：

```tex
\title[幻灯片缩略名]{幻灯片全名}           %以下是幻灯片首页的编辑
\subtitle{副标题}
\author{作者姓名}
\institute{作者所属学校}
\date[\initclock\tdtime]{\today}                     %总是显示当前的日期
\logo{\includegraphics[height=10mm]{yellowdeer.jpg}} %这是我的logo，如果不需要删掉词句即可
\begin{frame}
\titlepage
\end{frame}                                %幻灯片首页的编辑到此结束

\begin{frame}                              %开始编辑第i张幻灯片

\end{frame}                                %结束编辑第i张幻灯片

```


###三级结构代码

在`开始编辑第i张幻灯片`与`结束编辑第i张幻灯片`之间，写入第i张幻灯片的编辑代码，即三级结构。
这里我以如下图所示的幻灯片的编辑代码为例说明一些基本的、常用的语法：

![slide_eg](/public/img/slide_eg.JPG)

```tex
\begin{frame}{Decentralized low-rank matrix completion problem}  %大括号中是这页幻灯片的标题
\begin{columns}[onlytextwidth]                                   %将幻灯片分为两栏
\begin{column}{0.4\textwidth}                                    %开始左边的一栏，该栏占宽比为40%
\includegraphics[height=40mm]{networki2.jpg}                     %插入图片，图片大小可通过高度自定义
\begin{itemize}                                                  %开始列出清单
\footnotesize \item A network of $L$ agents\\                    %清单第一项。其中\footnotesize控制字体大小
\item Each agent $i$ observes some entries of $\mathbf{W}_{i}$   %清单第二项
\end{itemize}                                                    %结束列出清单
\end{column}                                                     %结束左边的这栏
\begin{column}{0.6\textwidth}                                    %开始右边的一栏，与左栏类似
\begin{itemize}
\vbox{}                                                          %空一行
\item Consider a low-rank matrix $\mathbf{W}$
\scriptsize \begin{itemize}
                   \item $\mathbf{W} \in \mathbb{R}^{N \times M}$
                   \item $rank(\mathbf{W})\le r$
                   \item $\mathbf{W}_{n,m}$ is known for $(n,m) \in \Omega$
                   \item $\mathbf{W} = [\mathbf{W}_{1}, \mathbf{W}_{2}, ...,
\mathbf{W}_{L}] $
                 \end{itemize}
\normalsize \vbox{}
\item An estimate matrix of $\mathbf{W}$: $\mathbf{Z}$
\scriptsize \begin{itemize}
                \item $\mathbf{Z} \in \mathbb{R}^{N \times M}$
                \item $rank(\mathbf{Z})\le r$
                \item $\mathbf{Z}=\mathbf{X}\mathbf{Y}= \mathbf{X} [\mathbf{Y}_{1}, \mathbf{Y}_{2}, ..., \mathbf{Y}_{L}]$
                \item $\mathbf{X}\in \mathbb{R}^{N \times r},\mathbf{Y} \in \mathbb{R}^{r \times M}$
              \end{itemize}
\end{itemize}
\normalsize \vbox{}                                             %\normalize使字体恢复正常大小
\end{column}                                                    %结束右边栏
\end{columns}                                                   %结束分栏
\end{frame}
```

以上就是LaTex beamer制作幻灯片的主要内容。
再次强调，在理解细节之前应先对代码框架有一个大的把握，具体编辑所需的语句可查阅书籍或互联网。

其实一句话就可以概括啦：不断的begin，不断的end。

