---
layout: post
title: Python基础如何学习Java[04]之Java的基本语法
category: 编程
tags: Python
keywords: Python
description: null
published: true
---

##基本语法

- 大小写敏感：Java是大小写敏感的，这就意味着标识符Hello与hello是不同的。
- 类名：对于所有的类来说，类名的首字母应该大写。如果类名由若干单词组成，那么每个单词的首字母应该大写，例如 MyFirstJavaClass 。
- 方法名：所有的方法名都应该以小写字母开头。如果方法名含有若干单词，则后面的每个单词首字母大写。
- 源文件名：源文件名必须和类名相同。当保存文件的时候，你应该使用类名作为文件名保存（切记Java是大小写敏感的），文件名的后缀为.java。（如果文件名和类名不相同则会导致编译错误）。
- 主方法入口：所有的Java 程序由public static void main(String args[])方法开始执行。

###注释

`//java`

```java
/*这是注释。
* 这是一个java多行注释的示例
这是注释。*/
```

`#python`

```python
'''
这是注释。
这是一个java多行注释的示例
这是注释。
'''
```

`#ruby`

```ruby
=begin
这是注释。
这也是注释。
这还是注释。
=end
```

###声明变量

在Java中一定要先声明变量，然后再使用变量。 

`type var-name; ` type表示所要声明的变量的类型，var-name是所要声明变量的名称。

###标识符（identifiers） 

`//java`: 标识符是赋给**类、方法或是变量**的名字。

所有的标识符都应该以字母（A-Z或者a-z）,美元符（$）、或者下划线（_）开始，首字符之后可以是任何字符的组合。

- 合法标识符举例：age、$salary、_value、__1_value
- 非法标识符举例：123abc、-salary

`#python`: 所有标识符可以包括英文、数字以及下划线（_），但不能以数字开头。

以下划线开头的标识符是有特殊意义的。

以单下划线开头（_foo）的代表不能直接访问的类属性，需通过类提供的接口进行访问，不能用`from xxx import *`而导入；

以双下划线开头的（__foo）代表类的私有成员；

以双下划线开头和结尾的（__foo__）代表python里特殊方法专用的标识，如__init__（）代表类的构造函数。

`#ruby`: 标识符的名称可以包含字母、数字和下划线字符（ _ ）。

###空白分隔符（whitespace）

`//java`：Java 是一种形式自由的语言。 这意味着你不需要遵循任何特殊的缩进书写规范。在Java中，空白
分隔符可以是空格，Tab跳格键或是换行符。 

`#python`：Python的代码块不使用大括号（`{}`）来控制类，函数以及其他逻辑判断。python最具特色的就是用缩进来写模块。

```
#python
if True:
	print "True"
else:
    print "False"
```

在python中空行也是程序代码的一部分。函数之间或类的方法之间用空行分隔，表示一段新的代码的开始。类和函数入口之间也用一行空行分隔，以突出函数入口的开始。

`#ruby`：在 Ruby 代码中的空白字符，如空格和制表符一般会被忽略，除非当它们出现在字符串中时才不会被忽略。然而，有时候它们用于解释模棱两可的语句。当启用 -w 选项时，这种解释会产生警告。

```
#ruby
a + b 被解释为 a+b （这是一个局部变量）
a  +b 被解释为 a(+b) （这是一个方法调用）
```

###分隔符（separators） 

![Java separators](/public/img/tech/Java separators.png)

`//java`：在Java中最常用的分隔符是分号(；)，用来分隔语句，作为该行的结束。

`#ruby`：Ruby 把分号和换行符解释为语句的结尾。但是，如果 Ruby 在行尾遇到运算符，比如 +、- 或反斜杠，它们表示一个语句的延续。

`#python`：Python语句中一般以新行作为为语句的结束符。使用斜杠（ \）将一行的语句分为多行显示，如下所示：

```
#python
total = item_one + \
    item_two + \
    item_three
```