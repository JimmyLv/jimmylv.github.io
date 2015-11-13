---
layout: post
title: Python基础如何学习Java[08]之类的继承 
category: 编程
tags: Python
keywords: Python
description: null
published: true
---

##超类与子类

继承是面向对象编程技术的一块基石，因为它允许创建分等级层次的类。运用继承，你能够创建一个通用类，它定义了一系列相关项目的一般特性。该类可以被更具体的类继承，每个具体的类都增加一些自己特有的东西。

###创建子类

声明一个继承超类的类的通常形式如下： 

```
class subclass-name extends superclass-name { 
 // body of class 
} 
```

你只能给你所创建的每个子类定义一个超类。 Java不支持多超类的继承。

继承的一个主要优势在于一旦你已经创建了一个超类，而该超类定义了适用于一组对象的属性，它可用来创建任何数量的说明更多细节的子类。每一个子类能够正好制作它自己的分类。

```
class Box { 
  double width; 
  double height; 
  double depth; 

  // construct clone of an object 
  Box(Box ob) { // pass object to constructor 
    width = ob.width; 
    height = ob.height; 
    depth = ob.depth; 
  } 
 
  // constructor used when all dimensions specified 
  Box(double w, double h, double d) { 
    width = w; 
    height = h; 
    depth = d; 
  }  

  // constructor used when no dimensions specified 
  Box() { 
    width = -1;  // use -1 to indicate 
    height = -1; // an uninitialized 
    depth = -1;  // box 
  } 
}

class BoxWeight extends Box { 
  double weight; // weight of box 
 
  // constructor for BoxWeight 
  BoxWeight(double w, double h, double d, double m) { 
    width = w; 
    height = h; 
    depth = d; 
    weight = m; 
  }     
} 
```

###超类变量可以引用子类对象 

超类的一个引用变量可以被任何从该超类派生的子类的引用赋值。引用变量的类型——而不是引用对象的类型——决定了什么成员可以被访问。也就是说，当一个子类对象的引用被赋给一个超类引用变量时，你**只能访问超类定义的对象的那一部分**。

```
class RefDemo { 
	public static void main(String args[]) { 
		//weightbox是BoxWeight对象的一个引用
		BoxWeight weightbox = new BoxWeight(3, 5, 7, 8.37); 
		//plainbox是Box对象的一个引用
		Box plainbox = new Box(); 
		double vol; 
		
		vol = weightbox.volume(); 
		System.out.println("Volume of weightbox is " + vol); 
		System.out.println("Weight of weightbox is " + weightbox.weight); 

		//允许用一个weightbox对象的引用给plainbox赋值
		plainbox = weightbox; 
		
		// OK, plainbox调用volume()实际上是调用weightbox.volume()
		vol = plainbox.volume(); 
		System.out.println("Volume of plainbox is " + vol); 
		
		// plainbox不能访问weight，超类不知道子类增加的属性。
		// System.out.println("Weight of plainbox is " + plainbox.weight); 
	} 
} 
```

##super 关键词

任何时候一个子类需要引用它直接的超类，它可以用关键字super来实现。 

###使用super调用超类构造函数

`BoxWeight( )`调用带w、h和d参数的`super( )`方法。这使`Box( )`构造函数被调用，用w、h和d来初始化width, height, 和 depth。BoxWeight不再自己初始化这些值。它只需初始化它自己的特殊值： weight。

```
class BoxWeight extends Box { 
	double weight; // weight of box 
	
	// initialize width, height, and depth using super() 
	BoxWeight(double w, double h, double d, double m) { 
		super(w, h, d); // call superclass constructor 
		weight = m; 
	}     
} 
```

既然构造函数可以被重载，可以用超类定义的任何形式调用`super( )`，执行的构造函数将是与所传参数相匹配的那一个。

```
class Box { 
	//注意width, height, and depth在Box是私有的。 
	private double width; 
	private double height; 
	private double depth; 
	
	// construct clone of an object 
	Box(Box ob) { // pass object to constructor 
		width = ob.width; 
		height = ob.height; 
		depth = ob.depth; 
	} 
	
	// constructor used when all dimensions specified 
	Box(double w, double h, double d) { 
		width = w; 
		height = h; 
		depth = d; 
	}
}

class BoxWeight extends Box { 
	double weight; // weight of box 
	
	// construct clone of an object 
	BoxWeight(BoxWeight ob) { // pass object to constructor 
		super(ob); 
		weight = ob.weight; 
	} 

	public static void main(String args[]) { 
		BoxWeight mybox1 = new BoxWeight(10, 20, 15, 34.3); 
		BoxWeight myclone = new BoxWeight(mybox1); 
		double vol; 
		
		vol = mybox1.volume(); 
		System.out.println("Volume of mybox1 is " + vol); 
		System.out.println("Weight of mybox1 is " + mybox1.weight); 
		
		vol = myclone.volume();  
		System.out.println("Volume of myclone is " + vol); 
		System.out.println("Weight of myclone is " + myclone.weight);
	}
}
```
分析：`super( )`被用一个BoxWeight类型而不是Box类型的对象调用。 这仍然调用了构造函数`Box(Box ob)`，一个超类变量可以引用作为任何一个从它派生的对象。

注意`super( )`必须是子类构造函数中的第一个执行语句。当一个子类调用`super( )`，它调用它的直接超类的构造函数。这样，`super( )`总是引用调用类直接的超类。

###使用super调用超类中被子类隐藏的方法或者实例变量

```
class A { 
	int i; 
} 
 
class B extends A { 
	int i; // this i hides the i in A 
	
	B(int a, int b) { 
		super.i = a; // i in A 
		i = b; // i in B 
	} 
 
	void show() { 
		System.out.println("i in superclass: " + super.i); 
		System.out.println("i in subclass: " + i); 
	} 
} 
 
class UseSuper { 
	public static void main(String args[]) { 
		B subOb = new B(1, 2); 
		
		subOb.show(); 
		/*
		该程序输出如下： 
		i in superclass: 1 
		i in subclass: 2 
		*/
	} 
} 
```

##创建多级类层次 

给定三个类A，B和C。C是B的一个子类，而B又是A的一个子类。当这种类型的情形发生时，每个子类继承它的所有超类的属性。这种情况下，C继承B和A的所有方面。这体现了继承的部分价值；它允许代码重用。 

###类层次结构

`super( )`总是引用子类最接近的超类的构造函数。在类层次结构中，如果超类构造函数需要参数，那么不论子类它自己需不需要参数，所有子类必须向上传递这些参数。 

在类层次结构中，构造函数以派生的次序调用，从超类到子类。而且，尽管`super( )`必须是子类构造函数的第一个执行语句，无论你用到了`super( )`没有，这个次序不变。如果`super( )`没有被用到，每个超类的默认的或无参数的构造函数将执行。

```
class A { 
	A() {  
		System.out.println("Inside A's constructor."); 
	} 
} 
class B extends A { 
	B() { 
		System.out.println("Inside B's constructor."); 
	} 
} 
class C extends B { 
	C() { 
		System.out.println("Inside C's constructor."); 
	} 
} 

class CallingCons { 
	public static void main(String args[]) { 
		C c = new C(); 
	} 
} 
```

该程序输出如下： 

```
Inside A’s constructor 
Inside B’s constructor 
Inside C’s constructor
```

###方法重载 

类层次结构中， 如果子类中的一个方法与它超类中的方法有相同的方法名和类型声明，称子类中的方法重载（override）超类中的方法。从子类中调用重载方法时，它总是引用子类定义的方法。而超类中定义的方法将被隐藏。如果你希望访问被重载的超类的方法，可以用`super.methodname()`。

```
class A { 
	int a;
	A(int a) {
		this.a = a;
	}
	void callme() { 
		System.out.println("Inside A's callme method"); 
	} 
} 
 
class B extends A { 
	int b;
	B(int a, int b) {
		super(a);
		this.b = b;
	}
	void callme() { 
		System.out.println("Inside B's callme method"); 
	} 
} 
 
class C extends A { 
	int c;
	C(int a, int b, int c) {
		super(a,b);
		this.c = c;
	}
	void callme() { 
	System.out.println("Inside C's callme method"); 
	} 
} 
 
class Dispatch { 
  public static void main(String args[]) { 
    A a = new A(1); // object of type A 
    B b = new B(1, 2); // object of type B 
    C c = new C(1, 2, 3); // object of type C 
    A r; // obtain a reference of type A     
 
    r = a; // r refers to an A object 
	System.out.println("a: "+ r.a);
    r.callme(); // calls A's version of callme 
 
    r = b; // r refers to a B object 
	System.out.println("a: "+ b.a + "b: " + b.b);
	//System.out.println("a: "+ r.a + "b: " + r.b); 
    //错误！
	//r的引用变量类型是A类即超类，所以只能访问到A类定义的那一部分成员。
    r.callme(); // calls B's version of callme
	//而调用方法的时候则是根据其引用对象的类型来决定调用的版本，
	//这里r引用变量类型是A类，但是引用对象的类型是B类，所以调用B类重写的callme()方法
 
    r = c; // r refers to a C object 
	System.out.println("a: "+ c.a + "b: " + c.b + "c: " + c.c); 
	//System.out.println("a: "+ r.a + "b: " + r.b + "c: " + r.c); 
    //错误！
    r.callme(); // calls C's version of callme 
  } 
} 
```

该程序的输出如下： 

```
Inside A’s callme method 
Inside B’s callme method 
Inside C’s callme method
```

「超类的引用变量可以引用子类对象。」Java用这一事实来解决在运行期间对重载方法的调用。过程如下：当一个重载方法通过超类引用被调用，Java根据当前被引用对象的类型来决定执行哪个版本的方法。如果引用的对象类型不同，就会调用一个重载方法的不同版本。换句话说，是被引用对象的类型（而不是引用变量的类型）决定执行哪个版本的重载方法。因此，如果超类包含一个被子类重载的方法，那么当通过超类引用变量引用不同对象类型时，就会执行该方法的不同版本。
 
超类的一个引用变量可以被任何从该超类派生的子类的引用赋值（被覆盖）。引用变量的类型——而不是引用对象的类型——决定了什么成员可以被访问。也就是说，当一个子类对象的引用被赋给一个超类引用变量时，你**只能访问超类定义的对象的那一部分**。；根据当前被**引用对象**的类型来决定执行哪个版本的方法，如果超类包含一个被子类重载的方法，那么当通过超类引用变量引用子类对象类型时，就会执行子类重写的方法。

##抽象类 

抽象类定义了一种给定结构的抽象但是不提供任何完整的方法实现。也就是说，抽象类是一个只定义一个被它的所有子类共享的通用形式，由每个子类自己去填写细节。这样的类决定了子类所必须实现的方法的本性。

指定abstract类型修饰符由子类重载某些方法。这些方法有时被作为子类责任（subclasser responsibility）引用，因为它们没有在超类中指定的实现。这样子类**必须重载**它们——它们不能简单地使用超类中定义的版本。

```
//声明一个抽象方法：
abstract type name(parameter-list);
```

###抽象类没有对象

任何含有一个或多个抽象方法的类都必须声明成抽象类。声明一个抽象类，只需在类声明开始时在关键字class前使用关键字abstract。

一个抽象类不能通过new操作符直接实例化，也就是说，你不能定义抽象构造函数或抽象静态方法。所有抽象类的子类都必须执行超类中的所有抽象方法或者是它自己也声明成abstract。 

```
abstract class A { 
  abstract void callme(); 
 
  // concrete methods are still allowed in abstract classes 
  void callmetoo() { 
    System.out.println("This is a concrete method."); 
  } 
} 
 
class B extends A { 
  void callme() { 
    System.out.println("B's implementation of callme."); 
  } 
} 
 
class AbstractDemo { 
  public static void main(String args[]) { 
    B b = new B(); 
 
    b.callme(); 
    b.callmetoo(); 
  } 
} 
```

##继承中使用final 

###使用final阻止重载

声明成final的方法不能被重载。

```
class A { 
  final void meth() { 
    System.out.println("This is a final method."); 
  } 
} 
 
class B extends A { 
  void meth() { // ERROR! Can't override. 
    System.out.println("Illegal!"); 
  } 
} 
```

###使用final阻止继承 

防止一个类被继承，只需在类声明前加final。声明一个final类含蓄的宣告了它的所有方法也都是final。你可能会想到，声明一个既是abstract的又是final的类是不合法的，因为抽象类本身是不完整的，它依靠它的子类提供完整的实现。 

##Object类 

所有其他的类都是Object的子类。也就是说，Object是所有其他类的超类。这意味着一个Object类型的引用变量可以引用其他任何一个类的对象。

![object class](/public/img/tech/object class.jpg)

`equals( )`方法比较两个对象的内容。如果对象是相等的，它返回`true`，否则返回`false`。`toString( )`方法返回一个包含调用它的对象描述的字符串。而且，该方法在对象用`println( )`输出时自动调用。 很多类重载该方法。 这样做使它们生成它们创建对象类型的一个特殊描述。