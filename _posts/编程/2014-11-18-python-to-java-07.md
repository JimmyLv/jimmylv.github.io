---
layout: post
title: Python基础如何学习Java[06]之三种语言的简单类实现与比较
category: 编程
tags: Python
keywords: Python
description: null
published: true
---

11/18/2014 11:14:22 PM 

##简单类实现

###Java实例
```
//Java
public class Puppy{
   int puppyAge;
   public Puppy(String name){
      // 这个构造器仅有一个参数：name
      System.out.println("Passed Name is :" + name ); 
   }

   public void setAge( int age ){
       puppyAge = age;
   }

   public int getAge( ){
       System.out.println("Puppy's age is :" + puppyAge ); 
       return puppyAge;
   }

   public static void main(String []args){
      /* 创建对象 */
      Puppy myPuppy = new Puppy( "tommy" );
      /* 通过方法来设定age */
      myPuppy.setAge( 2 );
      /* 调用另一个方法获取age */
      myPuppy.getAge( );
      /*你也可以像下面这样访问成员变量 */
      System.out.println("Variable Value :" + myPuppy.puppyAge ); 
   }
}
```

产生如下结果：

```
Passed Name is :tommy
Puppy's age is :2
Variable Value :2
```

###Ruby实例

```
#Ruby
#!/usr/bin/ruby

class Customer
   @@no_of_customers=0
   def initialize(id, name, addr)
      @cust_id=id
      @cust_name=name
      @cust_addr=addr
   end
   def display_details()
      puts "Customer id #@cust_id"
      puts "Customer name #@cust_name"
      puts "Customer address #@cust_addr"
   end
   def total_no_of_customers()
      @@no_of_customers += 1
      puts "Total number of customers: #@@no_of_customers"
   end
end

# 创建对象
cust1=Customer.new("1", "John", "Wisdom Apartments, Ludhiya")
cust2=Customer.new("2", "Poul", "New Empire road, Khandala")

# 调用方法
cust1.display_details()
cust1.total_no_of_customers()
cust2.display_details()
cust2.total_no_of_customers()
```

这将产生以下结果：

```
Customer id 1
Customer name John
Customer address Wisdom Apartments, Ludhiya
Total number of customers: 1
Customer id 2
Customer name Poul
Customer address New Empire road, Khandala
Total number of customers: 2
```

###Python实例

```
#Python
#!/usr/bin/python

class Employee:
   'Common base class for all employees'
   empCount = 0

   def __init__(self, name, salary):
      self.name = name
      self.salary = salary
      Employee.empCount += 1
   
   def displayCount(self):
     print "Total Employee %d" % Employee.empCount

   def displayEmployee(self):
      print "Name : ", self.name,  ", Salary: ", self.salary

#create object of Employee class
emp1 = Employee("Zara", 2000)
emp2 = Employee("Manni", 5000)

emp1.displayEmployee()
emp2.displayEmployee()

print "Total Employee %d" % Employee.empCount
```

输出结果如下：

```
Name :  Zara ,Salary:  2000
Name :  Manni ,Salary:  5000
Total Employee 2
```

##如何理解类与对象

理解类的最重要的事情就是它定义了一种新的数据类型。一旦定义后，就可以用这种新类型来创建该类型的对象。这样，类就是对象的模板（template），而对象就是类的一个实例（instance）。

当你定义一个类时，你要声明它准确的格式和属性。你可以通过指定它包含的数据和
操作数据的代码来定义类。类的代码定义了该类数据的接口。 

```
class classname  { 
	type instance-variable1; 
	// ... 
	type instance-variableN; 
 
	type methodname1(parameter-list) { 
	// body of method 
	} 
	// ... 
	type methodnameN(parameter-list) { 
	// body of method 
	}
}
```

在类中，数据或变量被称为实例变量（instance variables），代码包含在方法（methods）
内，方法决定该类中的数据如何使用。定义在**类中的方法和实例变量**被称为**类的成员**（members）。

> 定义在类中的变量被称为实例变量，这是因为类中的每个实例(也就是类的每个对象)都包含它自己对这些变量的拷贝。这样，一个对象的数据是独立的且是惟一的。改变一个对象的实例变量对另外一个对象的实例变量没有任何影响。

###一个类定义一个新的数据类型

```
class Box { 
  double width; 
  double height; 
  double depth; 
}
```

###真正创建一个对象

```
Box mybox = new Box(); // create a Box object called mybox 
```
new运算符为对象动态分配 （即在运行时分配）内存空间，并返回对它的一个引用。这个引用或多或少的是new分配给对象的**内存地址**。然后这个引用被存储在该变量中。
 


###变量赋值与对象引用


**使用点号 “.” 运算符访问实例变量：**

```
mybox.width = 100;
``` 

每次你创建类的一个实例时，你是在创建一个对象，该对象包含它自己的由类定义的每个实例变量的拷贝。

为什么对整数或字符这样的简单变量不使用new运算符？答案是Java的简单类型不是作为对象实现的。出于效率的考虑，它们是作为“常规”变量实现的。这里与一切皆为对象Python不同，在Python中基本的Numbers数据类型都是一种对象。

**对象引用的拷贝：**

```
Box b1 = new Box(); 
Box b2 = b1; 
b1 = null; 
//b1被设置为空，但是b2仍然指向原来的对象。 
```

###方法一般的形式

```
type name(parameter-list) { 
// body of method 
}
```

type指定了方法返回的数据类型。这可以是任何合法有效的类型，包括你创建的类的类型。自变量(parameter-list)本质上是变量，它接收方法被调用时传递给方法的参数值。

实例本身就拥有这些数据，要访问这些数据，就没有必要从外面的函数去访问，可以直接在类的内部定义访问数据的函数，这样，就把“数据”给封装起来了。这些封装数据的函数是和类本身是关联起来的，我们称之为类的方法。

对于不返回void类型的方法， 使用下面格式的return语句， 方法返回值到它的调用程序： `return value; `			

当`classname.methodname( )`被执行时，Java运行系统将程序控制转移到`methodname( )`定义内的代码。当`methodname( )`内的语句执行后，程序控制返回调用者，然后执行程序调用的下一行语句。

当一个实例变量不是被该实例变量所在类的部分代码访问时，它必须通过该对象加点运算符来访问。但是当一个实例变量被定义该变量的类的代码访问时，该变量可以被直接引用。同样的规则也适用于方法。 

###区分自变量（parameter）和参数（argument）

自变量是方法定义的一个变量，当方法被调用时，它接收一个值。参数是当一个方法被调用时，传递给该方法的值。

在设计的很好的Java程序中，实例变量应该
仅仅由定义类的方法来存取。在后面，你可以改变一个方法的行为，但是你不能改变一个
暴露的实例变量的行为。 

```
// sets dimensions of box 
void setDim(double w，double h，double d) { 
	width = w; 
	height = h; 
	depth = d; 
}
```

###类的构造函数

Java允许对象在他们被创造时初始化自己。构造函数 （constructor） 在对象创建时初始化。 它与它的类同名， 它的语法与方法类似。一旦定义了构造函数，在对象创建后，在new运算符完成前，构造函数立即自动调用。构造函数的任务就是初始化一个对象的内部状态，以便使创建的实例变量能够完全初始化，可以被对象马上使用。

```
class Box { 
	double width; 
	double height; 
	double depth; 

	// This is the constructor for Box. 
	Box() { 
		System.out.println("Constructing Box"); 
		width = 10; 
		height = 10; 
		depth = 10; 
	}

	//带自变量的构造函数 
	Box(double w，double h，double d) { 
		width = w; 
		height = h; 
		depth = d; 
    } 

} 
```

###this关键字

this这个关键字可以在引用当前对象的所有方法内使用。也就是，this总是调用该方法对象的一个引用。你可以在当前类的类型所允许对象的任何地方将this作为一个引用。 

在同一个范围或一个封装范围内，定义二个重名的局部变量在Java中是不合法的。有趣的是，局部变量，包括传递到方法的正式的自变量，可以与类的实例变量的名字重叠。 在这种情况下， 局部变量名就隐藏 （hide） 了实例变量名。 这就是在前面的Box类中， width、height、depth没有作为Box()构造函数自变量名字的原因。

```
	//使用this关键字来存取同名的实例变量：  
	// Use this to resolve name-space collisions. 
	Box(double width，double height，double depth) { 
		this.width = width; 
		this.height = height; 
		this.depth = depth; 
	} 
```

###垃圾回收( garbage collection)技术

使用new运算符来为对象动态地分配内存，而当一个对象的引用不存在时，则该对象被认为是不再需要的，它所占用的内存就被释放掉。

###对封装性的理解

对象编程的最重要的好处之一是对数据和操作该数据的代码的封装。在Java中，就是通过类这样的机制来完成封装性。在创建一个类时，你正在创建一种新的数据类型，不但要定义数据的属性，也要定义操作数据的代码。进一步，方法定义了对该类数据相一致的控制接口。因此，你可以通过类的方法来使用类，而没有必要担心它的实现细节或在类的内部数据实际上是如何被管理的。

一个叫做Stack的类，实现整数的堆栈：

```
// This class defines an integer stack that can hold 10 values. 
class Stack { 
	private int stck[]; 
	private int tos; 
	
	// Initialize top-of-stack 
	Stack(int size) { 
		stck = new int[size]; 
		tos = -1; 
	} 
	
	// Push an item onto the stack 
	void push(int item) { 
		if(tos==stck.length-1)  
			System.out.println("Stack is full."); 
		else  
			stck[++tos] = item; 
	} 
	
	// Pop an item from the stack 
	int pop() { 
		if(tos < 0) { 
			System.out.println("Stack underflow."); 
			return 0; 
		} 
		else  
			return stck[tos--]; 
	} 
}

class TestStack { 
	public static void main(String args[]) { 
		Stack mystack1 = new Stack(10); 
		Stack mystack2 = new Stack(20); 
		
		// push some numbers onto the stack 
		for(int i=0; i<10; i++) mystack1.push(i); 
		for(int i=10; i<20; i++) mystack2.push(i); 
		
		// pop those numbers off the stack 
		System.out.println("Stack in mystack1:"); 
		for(int i=0; i<10; i++)  
			System.out.println(mystack1.pop()); 
		
		System.out.println("Stack in mystack2:"); 
		for(int i=0; i<10; i++)  
			System.out.println(mystack2.pop()); 

		// these statements are not legal，加入了private，在外部无法直接访问tos
		// mystack1.tos = -2; 
		// mystack2.stck[3] = 100;
	} 
}
```

##对比Python中的类

在Java中使用this有时会引起混淆。有些程序员比较小心，不使用和局部变量、 正式的自变量同名的隐藏的实例变量。 当然， 另外的程序员则相反， 相信用this来 “揭开”与局部变量、自变量同名的实例变量是一个好习惯。这取决于你的爱好。

而在定义Python类的时候可以通过定义一个特殊的__init__方法，在创建实例的时候，就可以把一些必须绑定的属性强制绑上去：

```
class Student(object):

    def __init__(self, name, score):
        self.name = name
        self.score = score
```

注意到`__init__`方法的第一个参数永远是`self`，表示创建的实例本身，因此，在`__init__`方法内部，就可以把各种属性绑定到self，因为self就指向创建的实例本身。

有了`__init__`方法，在创建实例的时候，就不能传入空的参数了，必须传入与`__init__`方法匹配的参数，但self不需要传。

在类中定义的函数只有一点不同，就是第一个参数永远是实例变量`self`，并且，调用时，不用传递该参数。除此之外，类的方法和普通函数没有什么区别，所以，你仍然可以用**默认参数、可变参数和关键字参数。**

##对比Ruby中的类

**初始化实例变量:**

在Ruby中使用 `new` 方法创建对象，`new` 方法属于类方法。想要声明带参数的 `new` 方法时，您需要在创建类的同时声明方法 `initialize`。

```
class Customer
	@@no_of_customers=0 #类变量，必须初始化后才能在方法定义中使用
	def initialize(id, name, addr)
		@cust_id=id  #实例变量 = 局部变量
		@cust_name=name  #局部变量的值是随着 new 方法传递给实例变量
		@cust_addr=addr  #局部变量以小写字母或下划线 _ 开头
	end
end
```

可以创建对象，如下所示：

```
cust1=Customer.new("1", "John", "Wisdom Apartments, Ludhiya")
cust2=Customer.new("2", "Poul", "New Empire road, Khandala")
```

**成员函数：**

```	
#!/usr/bin/ruby

$global_variable = 10 #全局变量以 $ 开头。未初始化的全局变量的值为 nil

VAR1 = 100 #常量以大写字母开头。定义在类或模块外的常量可以被全局访问。

#常量不能定义在方法内。引用一个未初始化的常量会产生错误。对已经初始化的常量赋值会产生警告。

class Sample
	VAR2 = 200  #定义在类或模块内的常量可以从类或模块的内部访问
	def hello
		puts "Hello Ruby!"
	end
end

# 使用上面的类来创建对象
object = Sample. new
object.hello
```
