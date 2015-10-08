---
layout: post
title: Python基础如何学习Java[09]之包和接口 
category: 编程
tags: Python
keywords: Python
description: null
published: true
---

##包（package）

包（package）是类的容器，用来保存划分的类名空间。不用考虑创建的类和其他地方的某个名为同名的类相冲突。

包既是命名机制也是可见度控制机制。你可以在包内定义类，而且在包外的代码不能访问该类。这使你的类相互之间有隐私，但不被其他世界所知。 

###package的声明

```
package pkg; 
package MyPackage;
//多级包:
package pkg1[.pkg2[.pkg3]];
package java.awt.image; 
```

package语句定义了一个存储类的名字空间。如果你省略package 语句，类名被输入一个默认的没有名称的包。任何你声明的MyPackage中的一部分的类的.class文件被存储在一个MyPackage 目录中。记住这种情况是很重要的，目录名必须和包名严格匹配。 

###一个简短的包的例子

```
// A simple package 
package MyPack; 
 
class Balance { 
  String name; 
  double bal; 
 
  Balance(String n, double b) { 
    name = n; 
    bal = b; 
  } 
 
  void show() { 
    if(bal<0) 
      System.out.print("--> "); 
    System.out.println(name + ": $" + bal); 
  } 
} 
 
class AccountBalance { 
  public static void main(String args[]) { 
    Balance current[] = new Balance[3]; 
 
    current[0] = new Balance("K. J. Fielding", 123.23); 
    current[1] = new Balance("Will Tell", 157.02); 
    current[2] = new Balance("Tom Jackson", -12.33); 
 
    for(int i=0; i<3; i++) current[i].show(); 
  } 
} 
```

称该文件名为 AccountBalance.java，把它存放在MyPack目录中。 

###访问保护 

类和包都是封装和容纳名称空间和变量及方法范围的方法。一个类的private成员仅可以被该类的其他成员访问。包增加了访问控制的另一个维度。包就像盛装类和下级包的容器。类就像是数据和代码的容器。类是Java的最小的抽象单元。因为类和包的相互影响，Java将类成员的可见度分为四个种类： 

- 相同包中的子类 
- 相同包中的非子类 
- 不同包中的子类 
- 既不在相同包又不在相同子类中的类

![object class](/public/img/tech/java package.jpg)

###引入包 

```
import pkg1[.pkg2].(classname|*); 
//例子
import java.util.Date; 
import java.io.*;
```

任何你用到类名的地方，你可以使用它的全名，全名包括它所有的包层次。例如，下面的程序使用了一个引入语句： 

```
import java.util.*; 
class MyDate extends Date { 
} 
//没有import 语句的例子如下： 
class MyDate extends java.util.Date { 
}
```
 
##接口（interface）

用关键字interface，你可以从类的实现中抽象一个类的接口。也就是说，用interface，你可以指定一个类必须做什么，而不是规定它如何去做。一旦接口被定义，任何类成员可以实现一个接口。尽管它们与抽象类相似，接口有一个特殊的功能：类可以实现多个接口。与之相反，类只能继承一个超类（抽象类或其他）。 要实现一个接口，接口定义的类必须创建完整的一套方法。然而，每个类都可以自由的决定它们自己实现的细节。

###定义接口 

```
access interface name { 
	return-type method-name1(parameter-list); 
	return-type method-name2(parameter-list); 
	type final-varname1 = value; 
	type final-varname2 = value; 
	// ... 
	return-type method-nameN(parameter-list); 
	type final-varnameN = value; 
} 
```
access要么是public，要么就没有用修饰符。当没有访问修饰符时，则是默认访问范围，而接口是包中定义的惟一的可以用于其他成员的东西。当它声明为public时，则接口可以被任何代码使用。

注意定义的方法没有方法体。它们以参数列表后面的分号作为结束。它们本质上是抽象方法；在接口中指定的方法没有默认的实现。每个包含接口的类必须实现所有的方法。

接口声明中可以声明变量。它们一般是final 和static型的，意思是它们的值不能通过实现类而改变。它们还必须以常量值初始化。如果接口本身定义成public ，所有方法和变量都是public的。

```
interface Callback { 
  void callback(int param); 
}
```

###实现接口

```
access class classname [extends superclass] 
                         [implements interface [,interface...]] { 
     // class-body 
} 
```

如果一个类实现多个接口，这些接口被逗号分隔。如果一个类实现两个声明了同样方法的接口，那么相同的方法将被其中任一个接口客户使用。实现接口的方法必须声明成public。而且，实现方法的类型必须严格与接口定义中指定的类型相匹配。 

```
class Client implements Callback { 
  // Implement Callback's interface 
  public void callback(int p) { 
    System.out.println("callback called with " + p); 
  } 
}

class AnotherClient implements Callback { 
  // Implement Callback's interface 
  public void callback(int p) { 
    System.out.println("Another version of callback"); 
    System.out.println("p squared is " + (p*p)); 
  } 
｝
```

###通过接口引用实现接口

你可以把变量定义成使用接口的对象引用而不是类的类型。任何实现了所声明接口的类的实例都可以被这样的一个变量引用。当你通过这些引用调用方法时，在实际引用接口的实例的基础上，方法被正确调用。这是接口的最显著特性之一。被执行的方法在运行时动态操作，允许在调用方法代码后创建类。调用代码在完全不知“调用者”的情况下可以通过接口来调度。

```
class TestIface { 
  public static void main(String args[]) { 
    Callback c = new Client();  //引用变量c被定义成接口类型Callback
    c.callback(42);  //根据c引用的对象类型调用Client类中的方法

    AnotherClient ob = new AnotherClient(); 
 
    c = ob; // c now refers to AnotherClient object 
    c.callback(42); //根据c引用的对象类型调用AnotherClient类中的方法
	} 
}
```

尽管c可以用来访问Callback（）方法，它不能访问Client类中的任何其他成员。一个接口引用变量仅仅知道被它的接口定义声明的方法。

程序输出如下： 

```
callback called with 42 
Another version of callback 
p squared is 1764 
```

###抽象类局部实现接口

如果一个类包含一个接口但是不完全实现接口定义的方法，那么该类必须定义成abstract型。

```
abstract class Incomplete implements Callback { 
  int a, b; 
  void show() { 
    System.out.println(a + " " + b); 
  } 
  // ... 
} 
```

这里，类Incomplete没有实现callback( )方法，必须定义成抽象类。任何继承Incomplete的类都必须实现callback( )方法或者它自己定义成abstract类。  

###接口中的变量 

使用接口来引入多个类的共享常量，这样做只需要简单的声明包含变量初始化想要的值的接口就可以了。如果你的一个类中包含那个接口（就是说当你实现了接口时），所有的这些变量名都将作为常量看待。

```
interface SharedConstants { 
  int NO = 0; 
  int YES = 1; 
  int MAYBE = 2; 
  int LATER = 3; 
  int SOON = 4; 
  int NEVER = 5; 
} 
```

###接口的继承

```
// One interface can extend another. 
interface A { 
  void meth1(); 
  void meth2(); 
} 
 
// B now includes meth1() and meth2() -- it adds meth3(). 
interface B extends A { 
  void meth3(); 
} 
```

当一个类实现一个继承了另一个接口的接口时，它必须实现接口继承链表中定义的所有方法。





