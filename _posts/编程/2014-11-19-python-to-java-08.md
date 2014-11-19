---
layout: post
title: Python基础如何学习Java[07]之类和方法、访问限制
category: 编程
tags: Python
keywords: Python
description: null
published: true
---

##方法重载

###实现多态性

> 在Java中，同一个类中的2个或2个以上的方法可以有同一个名字，只要它们的参数声明不同即可。在这种情况下，该方法就被称为重载（overloaded），这个过程称为方法重载（method overloading）。方法重载是Java实现多态性的一种方式。

每个重载方法的参数的类型和（或）数量必须是不同的，当一个重载的方法被调用时，Java在调用方法的参数和方法的自变量之间寻找匹配。

“一个接口，多个方法”：实现数据类型不同但本质上相同的方法，`abs ( )`返回不同数据类型的绝对值。

###构造函数重载 

```
class Box { 
	double width; 
	double height; 
	double depth; 

	// constructor used when all dimensions specified 
	Box(double w，double h，double d) { 
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

	// constructor used when cube is created 
	Box(double len) { 
		width = height = depth = len; 
	}
}
```

初始化不同的盒子：

```
// create boxes using the various constructors 
Box mybox1 = new Box(10，20，15); 
Box mybox2 = new Box(); 
Box mycube = new Box(7);
```

###把对象作为参数

构造一个新对象，并且使它的初始状态与一些已经存在的对象一样。为了做到这一点，你必须定义一个构造函数，该构造函数将一个对象作为它的类的一个参数。

```
// construct clone of an object 
Box(Box ob) { // pass object to constructor 
	width = ob.width; 
	height = ob.height; 
	depth = ob.depth; 
}
```

初始化一个相同的盒子：

```
Box mybox1 = new Box(10，20，15); 

Box myclone = new Box(mybox1); 
```

###参数是如何传递的

计算机语言给子程序传递参数的方法有两种。第一种方法是按值传递（call-by-value）。这种方法将一个参数值（value）复制成为子程序的正式参数。这样，对子程序的参数的改变不影响调用它的参数。第二种传递参数的方法是引用调用（call-by-reference）。在这种方法中，参数的引用（而不是参数值）被传递给子程序参数。在子程序中，该引用用来访问调用中指定的实际参数。

根据传递的对象不同，Java将使用这两种不同的方法。当你给方法传递一个简单类型时，它是按值传递的。当你给方法传递一个对象时，这种情形就会发生戏剧性的变化，因为对象是通过引用传递的。记住，当你创建一个类类型的变量时，你仅仅创建了一个类的引用。

**方法能够返回任何类型的数据，包括你创建的类的类型。**

##访问控制 

封装将数据和处理数据的代码连接起来。同时，封装也提供另一个重要属性：访问控制（access control）。通过封装你可以控制程序的哪一部分可以访问类的成员。通过控制访问，可以阻止对象的滥用。如果使用得当，可以把类创建一个“黑盒子”，虽然可以使用该类，但是它的内部机制是不公开的，不能修改。

###访问指示符

一个成员如何被访问取决于修改它的声明的访问指示符（access specifier）：`public` （公共的， 全局的） 、 `private` （私有的， 局部的） 、 和`protected`（受保护的）

当一个类成员被`public`指示符修饰时，该成员可以被你的程序中的任何其他代码访问。当一个类成员被指定为`private`时，该成员只能被它的类中的其他成员访问。现在你能理解为什么`main( )`总是被`public`指示符修饰。它被在程序外面的代码调用，也就是由Java运行系统调用。如果不使用访问指示符，该类成员的默认访问设置为在它自己的包内为`public`，但是在它的包以外不能被存取。

```
class Test { 
	int a; // default access 
	public int b; // public access 
	private int c; // private access 
	
	// methods to access c 
	void setc(int i) { // set c's value 
		c = i; 
	} 
	int getc() { // get c's value 
		return c; 
	} 
} 
	
class AccessTest { 
	public static void main(String args[]) { 
		Test ob = new Test(); 
		
		// These are OK，a and b may be accessed directly 
		ob.a = 10; 
		ob.b = 20; 
		
		// This is not OK and will cause an error 
		//  ob.c = 100; // Error! 
		
		// You must access c through its methods 
		ob.setc(100); // OK 
		System.out.println("a，b，and c: " + ob.a + " " + ob.b + " " + ob.getc()); 
	} 
}
```

###关键字static

static变量实质上就是全局变量。它的使用完全独立于该类的任何对象。通常情况下，类成员必须通过它的类的对象访问，但是如果一个成员被声明为static，它就能够在它的类的任何对象创建之前被访问，而不必引用任何对象。static成员的最常见的例子是main( )。

当声明一个对象时，并不产生static变量的拷贝，而是该类所有的实例变量共用同一个static变量。 

如果你需要通过计算来初始化你的static变量，你可以声明一个static块，Static块仅在该
类被加载时执行一次。 

```
class UseStatic { 
	static int a = 3; 
	static int b; 

	static { 
		System.out.println("Static block initialized."); 
		b = a * 4; 
	} 
}
```

static方法和变量能独立于任何对象而被使用。这样，你只要在类的名字后面加点号运算符即可。例如，如果你希望从类外面调用一个static方法，你可以使用下面通用的格式：`classname.method( )`

```
class StaticDemo { 
	static int a = 42; 
	static int b = 99; 
	static void callme() { 
		System.out.println("a = " + a); 
	} 
} 
 
class StaticByName { 
	public static void main(String args[]) { 
		StaticDemo.callme(); 
		System.out.println("b = " + StaticDemo.b); 
	} 
} 
```


###关键字final 

一个变量可以声明为final， 这样做的目的是阻止它的内容被修改。 这意味着在声明final
变量的时候，你必须初始化它。
 
声明为final的变量在实例中不占用内存。这样，一个final变量**实质上是一个常数。** 

##对比Python

###访问限制

在Python中，实例的变量名如果以__开头，就变成了一个私有变量（private），只有内部可以访问，外部不能访问。

```
class Student(object):
    def __init__(self, name, score):
        self.__name = name
        self.__score = score

    def print_score(self):
        print '%s: %s' % (self.__name, self.__score)
```

在方法中，可以对参数做检查，避免传入无效的参数：

```
class Student(object):
    #...
    def set_score(self, score):
        if 0 <= score <= 100:
            self.__score = score
        else:
            raise ValueError('bad score')
```

需要注意的是，在Python中，变量名类似`__xxx__`的，也就是以双下划线开头，并且以双下划线结尾的，是特殊变量，特殊变量是可以直接访问的，不是private变量，所以，不能用`__name__`、`__score__`这样的变量名。

有些时候，你会看到以一个下划线开头的实例变量名，比如`_name`，这样的实例变量外部是可以访问的，但是，按照约定俗成的规定，当你看到这样的变量时，意思就是，“虽然我可以被访问，但是，请把我视为私有变量，不要随意访问”。

双下划线开头的实例变量是不是一定不能从外部访问呢？其实也不是。不能直接访问`__name`是因为Python解释器对外把`__name`变量改成了`_Student__name`。

###函数/方法的参数传递

对于函数的调用者来说，只需要知道如何传递正确的参数，以及函数将返回什么样的值就够了，函数内部的复杂逻辑被封装起来，调用者无需了解。

Python的函数参数除了正常定义的必选参数外，还可以使用默认参数、可变参数和关键字参数。

**默认参数：**

当函数有多个参数时，把变化大的参数放前面，变化小的参数放后面。变化小的参数就可以作为默认参数。

```
def power(x, n=2):
    s = 1
    while n > 0:
        n = n - 1
        s = s * x
    return s
```

**可变参数：**

可变参数允许你传入0个或任意个参数，这些可变参数在函数调用时自动组装为一个tuple。

```
def calc(*numbers):
    sum = 0
    for n in numbers:
        sum = sum + n * n
    return sum

calc(1, 2, 3)

nums = [1, 2, 3]
calc(*nums)
```

**关键字参数：**

关键字参数允许你传入0个或任意个含参数名的参数，这些关键字参数在函数内部自动组装为一个dict。

```
def person(name, age, **kw):
    print 'name:', name, 'age:', age, 'other:', kw

person('Michael', 30)

kw = {'city': 'Beijing', 'job': 'Engineer'}
person('Jack', 24, **kw)
```

**参数组合：**

对于任意函数，都可以通过类似func(*args, **kw)的形式调用它，无论它的参数是如何定义的。

```
def func(a, b, c=0, *args, **kw):
    print 'a =', a, 'b =', b, 'c =', c, 'args =', args, 'kw =', kw

args = (1, 2, 3, 4)
kw = {'x': 99}
func(*args, **kw)
```

