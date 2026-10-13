A class can be a sub-type of another (**base**) class:
```java
//Addition
class Employee{ 
	String name; 
	double wage; 
	void incrementWage(){…} 
}

class Manager extends Employee{ 
	String managedUnit; 
	void changeUnit(){…} 
}
//Overritde
class Employee{ 
	String name; 
	public void print(){ 
		IO.println(name); 
	} 
} 

class Manager extends Employee{ 
	private String managedUnit; 
	public void print(){ //override 
		IO.println(name + ", manages " + managedUnit); 
	} 
}

Manager m = new Manager(); 
m.incrementWage();
```
Why inheritance??
###### Reuse
Often, a class is a minor modification of an already existing class.
Inheritance avoids code repetitions. 
Localization of code: 
- Fixing a bug in the base class automatically fixes it in all the subclasses 
- Adding a new functionality in the base class automatically adds it in the subclasses too 
- Less chances of different (and inconsistent) implementations of the same operation
###### Flexibility
Often, we need to treat objects from different classes in a similar way 
- Polymorphism allows feeding algorithms with objects of different classes  
- Dynamic binding allows accommodating different behavior behind the same interface
---
##### Depth of Inheritance Tree
DIT = # levels below root base class 
Too deep inheritance trees **reduces code understandability**.
General rule is to **keep DIT ≤ 5**  {Empirical limit}
###### Terminology
- Class one above -> Parent class 
- Class one below -> Child class 
- Class one or more above -> Superclass, Ancestor class, Base class 
- Class one or more below -> Subclass, Descendent class
---
#### Polymorphism 
A reference of type T can point to an object of type S if-and-only-if 
- S is equal to T or 
- S is a subclass of T
```java
Employee e; 

e = new Employee(); // same class 
e = new Manager(); // subclass
```

>You can treat indifferently objects of different classes, provided they derive from a common base class.
```java
Employee[] team = {
	 new Manager("Mary Black",25000,"IT"), 
	 new Employee("John Smith",12000), 
	 new Employee("Jane Doe",12000) 
};
```
##### Static type checking
The compiler performs a check on method invocation on the basis of the reference type:
```java
for(Employee it : team){ 
	it.print(); //Does the type of it (i.e. Employee) provide method print()?
}
```
---
#### Dynamic Binding
Association message – method (Performed by JVM at run-time) 
Constraint -> Same signature.
1. The JVM retrieves the effective class of the target object 
2. If that class defines the required method, it is executed 
3. Otherwise, consider the parent class and repeat step 2

Why having dynamic bindings??
- Several objects from different classes, sharing a common ancestor class 
- Objects can be treated uniformly 
- Algorithms can be written for the base class (using the relative methods) and applied to any subclass
---
Using annotation **@Override** 
- Informs the compiler that a method is intended as an override 
- Generates an error if not a proper override
```java
class Employee{ 
	public void print(){ … } 
}

//Unexpected behavior at runtime since this method is no used
class Manager extends Employee{ 
	public void Print(){…} //Capital P
}

//Error at compile-time this is not an override
class Manager extends Employee{ 
	@Override 
	public void Print(){…} //Capital P
}
```
---
#### Casting
Java is a strictly typed language:
- each variable has a type 
- a variable can host only value of that type
```java
float f; 
f = 4.7; // legal 
f = "string";// illegal 

Car c; 
c = new Car(); // legal 
c = new String(); // illegal
```
##### Type conversion
Explicit or implicit:
```java
int i = 44; 
float f = i; // implicit cast 2c -> fp 
f = (float) 44; // explicit cast
```
##### Upcast
Assignment from a more specific type (subtype) to a more general type (supertype):
```java
Employee e = new Employee(…); 
Manager m = new Manager(…); 
Employee em = (Employee) m; //Up-Casting the Manager to Employee
```
>Upcasts are always type-safe and are performed implicitly by the compiler 
>- Employee em = m;
###### Cast and Conversion
A reference cast only affects the reference.

>In the previous example the object referenced to by ‘ em ’ continues to be of Manager type.

Notably, in contrast: 
- a primitive type cast causes a value conversion 
- a class type cast does not affect the object
##### Downcast
Assignment from a more general type (supertype) to a more specific one (subtype):
```java
Employee em = …; 
Manager mm = (Manager)em; //Down-Casting the Employee to Manager
```
By default, it is not safe, no automatic conversion is provided by the compiler
- **Must be explicit** 
- Forces the programmer to take responsibility of checking the cast is valid

>To access a member defined in a class you need a reference of that class type:
```java
Employee emp = team[0]; 
s = emp.getDepartment(); //Syntax Error: The method getDepartment() is undefined for the type Employee
Manager mgr = (Manager) team[0]; 
s = mgr.getDepartment();
```
>Be careful: Compiler trusts any downcast.
```java
mgr = (Manager)team[1];
//ClassCastException: Employee cannot be cast to Manager
```
###### Downcast safety
Use the instanceof operator 
	aReference instanceof aClass 
It Returns true if the object pointed by the reference can be cast to the class.
```java
if(team[1] instanceof Manager){ 
	Manager mgr = (Manager)team[1]; 
}

//OR

if(team[1] instanceof Manager mgr){ 
	// mgr is in scope here 
}
```
---
#### Visibility
```java
class Employee { 
	private String name; 
	private double wage; 
}

class Manager extends Employee { 
	void print() { 
		IO.println("Manager " + name + " " + wage); //Not visible
	} 
}
```
Attributes and methods marked as 
- **public** are always accessible 
- **protected** are accessible from within the class, classes in the package and subclasses 
- ***package*** are accessible from within the class, classes in the package 
- **private** are accessible from within the declaring class only
---
#### Inheritance and Constructors
Execution of constructors proceeds **top-down** in the inheritance hierarchy. 

>As a consequence, when a method of the child class is executed (constructor included), the super-class is completely initialized already.
```java
class Employee { 
	Employee() { 
		IO.println(“ctor Employee”); 
	} 
} 

class Manager extends Employee { 
	Manager() { 
		IO.println(“ctor Manager”); 
	} 
} 

class CEO extends Manager { 
	CEO() { 
		IO.println(“ctor CEO”); 
	} 
}

new CEO() // ctor Employee -> ctor Manager -> ctor CEO
```
###### Explicit constructors
If any constructor is explicitly defined the default constructor “disappears”. 
- Derived class constructor implicitly invokes the base class constructor that cannot be resolved.
```java
class Employee{ 
	… 
	Employee(String name, double wage){} // no default ctor is defined 
}

class Manager extends Employee{ } //Error: Implicit constructor is undefined
```
>An explicit constructor without arguments can be defined:
```java
class Employee{ 
	… 
	Employee(String name, double wage){} 
	Employee(){} // explicit constructor
}

class Manager extends Employee{ } // works
```
##### Super
The child class constructor must call the right constructor of the parent class, explicitly ▪ Use super() to invoke the constructor of parent class and pass the appropriate arguments ▪ Must be the first statement in child constructors