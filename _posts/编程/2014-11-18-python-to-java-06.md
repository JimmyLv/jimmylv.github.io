---
layout: post
title: Python基础如何学习Java[05]之数据类型
category: 编程
tags: Python
keywords: Python
description: null
published: true
---

##Java语言是强类型语言

> 首先，每个变量有类型，每个表达式有类型，而且每种类型是严格定义的。其次，所有的数值传递，不管是直接的还是通过方法调用经由参数传过去的都要先进行类型相容性的检查。

变量就是申请内存来存储值。也就是说，当创建变量的时候，需要在内存中申请空间。内存管理系统根据变量的类型为变量分配存储空间，分配的空间只能用来储存该类型数据。在计算机程序中，变量不仅可以是数字，还可以是任意数据类型。不同的数据，需要定义不同的数据类型。

在Python中，等号`=`是赋值语句，可以把任意数据类型赋值给变量，同一个变量可以反复赋值，而且可以是不同类型的变量，这种变量本身类型不固定的语言称之为动态语言，与之对应的是静态语言。静态语言在定义变量时必须指定变量类型，如果赋值的时候类型不匹配，就会报错。例如Java是静态语言，赋值语句如下：

```java
int a = 123; // a是整数类型变量
a = "ABC"; // 错误：不能把字符串赋给整型变量
```

##Java基本数据类型

Java定义了8个简单（或基本）的数据类型：字节型（byte），短整型（short），整型
（int），长整型（long），字符型（char），浮点型（float），双精度型（double），布尔型（boolean），这些类型可分为4组： 

- 整数：该组包括字节型（byte），短整型（short），整型（int），长整型（long），它们有符号整数。 
- 浮点型数：该组包括浮点型（float），双精度型（double），它们代表有小数精度要求的数字。 
- 字符：这个组包括字符型（char），它代表字符集的符号，例如字母和数字。 
- 布尔型：这个组包括布尔型（boolean），它是一种特殊的类型，表示真/假值。

简单数据类型代表单值，而不是复杂的对象。Java是完全面向对象的，但简单数据类型不是。他们类似于其他大多数非面向对象语言的简单数据类型。这样做的原因是出于效率方面的考虑。

##Java的变量

###变量初始化

变量是Java程序的一个基本存储单元。所有的变量在使用前必须声明。变量由一个标识符，类型及一个可选初始值的组合定义：

`type identifier [ = value][, identifier [= value] ...] ;`

格式说明：type为Java数据类型。identifier是变量名。可以使用逗号隔开来声明多个同类型变量。

Java也允许在变量声明时使用任何有效的表达式来动态地初始化变量。初始化表达式可以使用任何有效的元素，包括方法调用、其他变量或字面量。 

```java
double a = 3.0, b = 4.0; 
// c is dynamically initialized 
double c = Math.sqrt(a * a + b * b); 
```
###变量的作用域

在Java中2个主要的作用域是通过类和方法定义的。

方法定义的作用域以它的左大括号开始。但是，如果该方法有参数，那么它们也被包括在该方法的作用域中。作为一个通用规则，在一个作用域中定义的变量对于该作用域外的程序是不可见（即访问）的。因此，当你在一个作用域中定义一个变量时，你就将该变量局部化并且保护它不被非授权访问和/或修改。实际上，作用域规则为封装提供了基础。

作用域可以进行嵌套。例如每次当你创建一个程序块，你就创建了一个新的嵌套的作用域。外面的作用域包含内部的作用域。外部作用域定义的对象对于内部作用域中的程序是可见的。但是，反过来就是错误的。但是注意：尽管程序块能被嵌套，你不能将内部作用域声明的变量与其外部作用域声明的变量重名。

变量在其作用域内被创建，离开其作用域时被撤消。这意味着一个变量一旦离开它的作用域，将不再保存它的值了。因此，在一个方法内定义的变量在几次调用该方法之间将不再保存它们的值。


```
//age是一个局部变量。定义在pubAge()方法中，它的作用域就限制在这个方法中。
public class Test{ 
   public void pupAge(){
      int age = 0;
      age = age + 7;
      System.out.println("Puppy age is : " + age);
   }
   
   public static void main(String args[]){
      Test test = new Test();
      test.pupAge();
   }
}
```

##Java数组

数组（array）是相同类型变量的集合，可以使用共同的名字引用它。数组可被定义为任何类型，可以是一维或多维。数组中的一个特别要素是通过下标来访问它。

###一维数组 

一维数组（one-dimensional array）实质上是相同类型变量列表。要创建一个数组，你
必须首先定义数组变量所需的类型。

```java
//声明一维数组格式 
type var-name[ ]; 
//声明数组还有第二种格式 
type[ ] var-name; 

eg:
int al[] = new int[3]; 
int[] a2 = new int[3];
```

为了使数组`var-name`成为实际的、物理上存在的整型数组，你必须用运算符new来为其分配地址:

`array-var = new type[size];`


将对数组变量的声明和对数组本身的分配结合起来是可以的，如下所示： 

```java
int month_days[] = new int[12]; //数组中的元素将会被自动初始化为零。
int month_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 
```

###多维数组 

在Java中，多维数组（multidimensional arrays）实际上是数组的数组。

`int twoD[][] = new int[4][5]; `

###Java中的字符串

Java的字符串类型，叫做字符串（String），它不是一种简单的类型，它也不是简单的字符数组（在C/C++中是）。字符串（String）在Java中被定义为对象。

字符串（String）类型被用来声明字符串变量，str是字符串（String）类型的一个对象，它被分配给字符串“this is a test”，该字符串被println( )语句显示。  

```java
String str = "this is a test"; 
System.out.println(str); 
```

##与Python/Ruby的区别

###Python变量赋值

Python中的变量不需要声明，变量的赋值操作既是变量声明和定义的过程。每个变量在使用前都必须赋值，变量赋值以后该变量才会被创建。

```python
#python
name = "John"  
a = b = c = 1
a, b, c = 1, 2, "john"
```

```
#python
name = "John"  
a = b = c = 1
a, b, c = 1, 2, "john"
```

###Python数据类型

Python有五个标准的数据类型：

- **Numbers（数字）**：int（有符号整型）、long（长整型[也可以代表八进制和十六进制]）、float（浮点型）、complex（复数）
- **String（字符串）**：表示文本的数据类型，`s="a1a2···an"(n>=0)`
- **List（列表）**：用`[ ]`标识；复合数据类型，可以完成大多数集合类的数据结构实现。它支持字符，数字，字符串甚至可以包含列表（所谓嵌套）。
- **Tuple（元组）**：用`( )`标识；元素不能二次赋值，相当于只读列表。
- **Dictionary（字典）**:用`{ }`标识；字典由索引(key)和它对应的值value组成。元素是通过键来存取的，而不是通过偏移存取。

而在 Python 中一切均为对象，因此存在像 module［模块］、 function［函数］、 class［类］、 method［方法］、 file［文件］ 甚至 compiled code［已编译代码］ 这样的类型。

###Python数据类型转换

只需要将数据类型作为函数名即可。几个内置的函数可以执行数据类型之间的转换，这些函数返回一个新的对象，表示转换的值。

```python
str(x)  # 将对象 x 转换为字符串
list(s)  # 将序列 s 转换为一个列表
dict(d)  # 创建一个字典。d 必须是一个序列 (key,value)元组。
ord(x)  # 将一个字符转换为它的整数值
```

###Ruby数据类型

Ruby支持的数据类型包括：

- Number：整型（Fixnum实例/Bignum实例）、浮点型
- String：一个 8 位字节序列，它们是类 String 的对象。
- Ranges：一个范围表示一个区间。范围是通过设置一个开始值和一个结束值来表示。范围可使用`s..e`和`s...e`来构造，或者通过`Range.new`来构造。
- Symbols：表示“名字”，比如字符串的名字，标识符的名字。
- Array：数组通过`[]`索引访问，赋值操作插入、删除、替换元素。
- Hash：是在大括号内放置一系列键/值对，键和值之间使用逗号和序列`=>`分隔。尾部的逗号会被忽略。
- 特殊值：true、false和nil

**[Ruby 字符串（String）](http://www.w3cschool.cc/ruby/ruby-string.html)**

可以使用序列`#{ expr }`替换任意 Ruby 表达式的值为一个字符串。在这里，`expr` 可以是任意的 Ruby 表达式。

```ruby
#!/usr/bin/ruby -w
puts "Multiplication Value : #{24*60*60}";
```

这将产生以下结果：

```ruby
Multiplication Value : 86400
```

**[Ruby 哈希（Hash）](http://www.w3cschool.cc/ruby/ruby-hash.html)**

```ruby
#!/usr/bin/ruby
hsh = colors = { "red" => 0xf00, "green" => 0x0f0, "blue" => 0x00f }
hsh.each do |key, value|
   print key, " is ", value, "\n"
end
```

这将产生以下结果：

```
green is 240
red is 3840
blue is 15
```

**[Ruby 数组（Array）](http://www.w3cschool.cc/ruby/ruby-array.html)**

```ruby
#!/usr/bin/ruby
ary = [  "fred", 10, 3.14, "This is a string", "last element", ]
ary.each do |i|
   puts i
end
```

这将产生以下结果：

```ruby
fred
10
3.14
This is a string
last element
```

**[Ruby 范围（Range）](http://www.w3cschool.cc/ruby/ruby-range.html)**

```ruby
#!/usr/bin/ruby
(10..15).each do |n| 
   print n, ' ' 
end
```

这将产生以下结果：

```ruby
10 11 12 13 14 15
```