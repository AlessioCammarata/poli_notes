### Java Syntax
Java code blocks are the same as in C 
Each block is enclosed by braces { } and starts a new scope for the variables 
Variables can be declared both at the beginning and in the middle of a block.
```java
for (int i=0; i<10; i++){ 
	int x = 12; 
	... 
	int y; 
	... 
}
```
#### Control statements
Similar to C 
- if-else 
- switch, 
- while 
- do-while 
- for 
- break 
- continue
#### Boolean
Java has an explicit type (boolean) to represent logical values (true, false) 
Conditional constructs require boolean conditions.
It is illegal to evaluate integer condition 
	int x = 7; if(x){…} //NO 

>Use relational operators if (x != 0).
>Avoids common mistakes, e.g. if(x=0)
#### Passing parameters
Parameters are **always passed by value**.
They can be **primitive types or object references**.  

>only the object reference is copied not the whole object.
#### PRIMITIVE TYPES
Defined in the language: 
- int, double, boolean, etc. 

Instance declaration: 
- Declares instance name 
- Declares the type 
- Allocates memory space for the value

boolean 1 bit - char 16 bits Unicode UTF16 byte 8 bits Signed integer 2C short 16 bits Signed integer 2C int 32 bits Signed integer 2C long 64 bits Signed integer 2C float 32 bits IEEE 754 sp double 64 bits IEEE 754 dp void -

| Type    | Size    | Encoding          |
| ------- | ------- | ----------------- |
| boolean | 1 bit   | -                 |
| char    | 16 bits | Unicode UTF16     |
| byte    | 8 bits  | Signed integer 2C |
| short   | 16 bits | Signed integer 2C |
| int     | 32 bits | Signed integer 2C |
| long    | 64 bits | Signed integer 2C |
| float   | 32 bits | IEEE 754 sp       |
| double  | 64 bits | IEEE 754 dp       |
| void    | -       |                   |
##### Literals
Literals of type int, float, char, strings follow C syntax 
- 123 256789L 0xff34 123.75 0.12375e+3 
- ’ a ’ ’%’ ’\n ’ "prova" "prova\n"

Boolean literals (do not exist in C) are 
- true, false

#### Logical operators
Works only on boolean data:
- &&   ||    !     ^
- Type int is NOT treated like a boolean: this is a key difference from C 
- Relational operators return boolean values
### CLASSES AND OBJECTS
#### Class
Defined by developer (e.g., Exam) or in the Java runtime libraries (e.g., String).
The declaration:
```java
Exam e;   // e null
```
allocates memory for the **reference** (‘pointer’) …and sometimes it initializes it with **null** 
Allocation and initialization of the object value are made later by new and constructor.
```java
e = new Exam();  // e oXffe1 -> Object Exam
```

**Object descriptor** 
- Defines the common structure of a set of objects 
- Similar to typedef struct in C 
Consists of a set of **members** 
- **Attributes** 
- **Methods** 
- **Constructors**
##### definition
```java
public class Car { // Name
	String color; // Attribute
	String brand; // Attribute
	boolean turnedOn; // Attribute
	
	// Methods
	void turnOn() { 
		turnedOn = true; 
	} 
	void paint (String newCol) { 
		color = newCol; 
	} 
	boolean isOn(){ 
		return turnedOn; 
	} 
	void printState () { 
		IO.println(“Car “ + brand + “ “ + color); 
		IO.println(“the engine is” +(turnedOn?” on ” : ”off”)); 
	} 
}
```
##### Attributes
Attributes or Fields describe the data that can be stored within objects. 
They are like variables, defined by: 
- Type 
- Name 
- Like fields of struct in C 
>Each object has its own copy of the attributes.
##### Methods
Methods represent the messages that an object can accept 
- turnOn 
- paint 
- printState 

They may accept arguments. 
- paint(String ) 
They may return values.
##### Objects
An object is identified by: 
- Class, which defines its structure (in terms of attributes and methods) 
- **State** (values of attributes) 
- **Internal unique identifier** 

An object can be accessed through a **reference** 
- Any object can be pointed to by one or more references − Aliasing

###### Keyword 'new'
Creates a new instance of the specific class.
Allocates the required memory in the heap.
Calls the constructor of the object 
- a special method without return type and named like the class 
Returns a reference to the new object 
	Car m = new Car(); 

Constructor may have parameters, 
- e.g. String s = new String("ABC");
###### Heap
The part of the program memory used by an executing program to store data dynamically created at run-time.

C: malloc, calloc and free 
- Instances of types in static memory or in heap 

Java: new 
- Instances (Objects) are always in the heap
##### Constructor
Constructor is a special method containing the operations (e.g. initialization of attributes) to be executed on each object as soon as it is created.
Attributes are always initialized.
If no constructor **at all** is declared, a default one with no arguments is provided by the compiler.

Attributes are always initialized before any possible constructor 
- **Attributes are initialized with default values** 
	- Numeric: 0 (zero) 
	- Boolean: false 
	- Reference: null 

Return type **must not be declared for constructors** 
	If present, the constructor is considered as a regular method, therefore it is not invoked upon instantiation (new)

>Overloading of constructors is often used

---
##### Operations on references
The dot . operator is used to dereference object references.
- Obtain the object pointed by the reference 
Two comparison operators are defined 
- == and != 
>**There is NO pointer arithmetic**
##### Comparing objects
The relational operators check whether the references points to the same object in memory 
- **They check identity** -> Same pointer/reference
- No check on the objects’ contents 
To compare contents an ad-hoc method must be defined 
- The criteria to compare the contests
##### Overloading
Several methods in a class can share the same name.
Provided they have distinct **signature**.
Signature of a method consists of: 
- Method name 
- Ordered list of argument types − Does not include the return type
###### Disambiguation
Invocation of an overloaded method is potentially ambiguous.
Disambiguation is performed by the compiler based on actual parameters.
- The method definition whose formal argument types list matches the actual parameter list, is selected
```java
class Car { 
	String color; 
	void paint(){ 
		color = "white"; 
	} 
	void paint(int i){ … } 
	void paint(String newCol){ 
		color = newCol; 
	} 
}

//Constructors with overloading

class Car { // … 
	// Default constructor, creates a red Ferrari 
	public Car(){ 
		color = "red"; 
		brand = "Ferrari"; 
	} 
	// Constructor accepting the brand only 
	public Car(String carBrand){ 
		color = "white”; 
		brand = carBrand; 
	} 
	// Constructor accepting the brand and the color 
	public Car(String carBrand, String carColor){ 
		color = carColor; 
		brand = carBrand; 
	} 
}
```
##### Destruction of objects
Memory release, in Java, is no longer a programmer’s concern.
- Managed memory language 
- There is no equivalent of C free() 
Before the object is eventually really destroyed the method finalize, if defined, is invoked: 
	**public void finalize()**

---
#### Scope and Syntax
Visibility modifiers 
- Applicable to members of a class 
**private** 
- Member is visible and accessible from instances of the same class only 
**public** 
- Member is visible and accessible from everywhere

**Information hiding** is the approach of making information contained in objects non accessible from outside.
It is implemented using the visibility modifiers.
>By default all attributes **should be** **declared private**.
##### Getters and setters
Methods used to read/write a private attribute.
Allow to better control in a single point each write access to a private field.
```java
public String getColor() { 
	return color; 
} 
public void setColor(String newColor) { 
	color = newColor; 
}
```
##### Modifier vs. Query methods
**Modifiers** − e.g., setters 
- Change the state of the object but do not return a value 
**Query**  - e.g, getters
- Return a result and do not change the state of the object 
- No side-effects 

Invocations to 
- **queries** can be added, removed, and swapped without affecting the overall behavior
- **modifiers** cannot be touched without affecting the behavior 

>Important to clearly separate them: 
- Queries return a value 
- Modifiers return void
##### Mutable vs. Immutable
Classes that have **only query methods are called immutable** 
- Once initialized (by the constructor) their status cannot be changed 
Other classes that have modifiers, conversely, **are called mutable** 
- Their status can be changed through modifier methods
---
#### Package
Class is a better mechanism of modularization than a procedure -> Like libraries in C.
For the purpose of code organization and structuring Java provides the **package feature**.
A package is a logic set of class definitions.

>You can also put all together into a folder, that's also called package, more files/class can be inside a package.
```java
import transport.Car; // Car inside folder "transport"
```
##### Access to a class in a package
Referring to a method/class of a package
```java
String in = java.lang.IO.readLine();
```
>If two packages define a class with the same name, they cannot be both imported.

If you need both classes you have to use one of them with its fully-qualified name:
```java
import java.sql.Date; 
Date d1; // java.sql.Date 
java.util.Date d2 = new java.util.Date();
```

>Usage of **default package is a bad practice and is discouraged**.

###### Package Visibility
New kind of visibility, you can access to it from the same Package, not from different packages though. -> **Private**
```java
//Package P
public class A { }
class B {}
//Package Q
class C { }

//You can create an A object in C because A is public, you can create a B object in A because it's in the same package but C cannot create a B object.
```
#### Wrapper Classes
Wrapper classes are object versions of the primitive types.
They define **conversion** operations between different types.
Defined in java.lang package:

boolean Boolean 
char Character 
byte Byte 
short Short 
int Integer 
long Long 
float Float 
double Double 
void Void
```java
Integer obj = new Integer(88); 
String s = obj.toString(); 
int i = obj.intValue(); 

int j = Integer.parseInt("99"); 
int k=(new Integer(99)).intValue();
```
##### Autoboxing
Since Java 5, the conversion between primitive types and wrapper classes is performed automatically (autoboxing):
```java
Integer i= Integer.valueOf(2); 
int j; 
j = i + 5; 
//instead of: 
j = i.intValue()+5; 
i = j + 2; 
//instead of: 
i = Integer.valueOf(j+2);
```
#### Array
An array is an ordered sequence of variables of the same type which are accessed through an index.
Can contain **both primitive types or object references** (but no object values). 
>Array dimension can be defined at run-time, during object creation (cannot change afterwards).

```java
int[] a; 
int a[];
```
In Java an array is an Object and it is stored in the heap, the declaration allocates space for a **reference**, whose default is 'null'.
```java
int[] a; 
a = new int[10]; 
String[] s = new String[5];

//or using static initialization
int[] primes = {2,3,5,7,11,13}; 
Person[] p = { new Person(“John”), new Person(“Susan”) };
```
##### Operations on arrays (non scrivo tutto)
Array length (number of elements) is given by attribute length:
```java
for (int i=0; i < a.length; i++) 
	a[i] = i;
```
>An array reference is a **pointer to the array object**, that's also why arithmetic on pointers does not exist in java
###### For each
New loop construct:
	for( Type var : set_expression )
set_expression can be 
- either an array 
- a class implementing Iterable

```java
for(String arg : args){ 
//... 
}
```
---
#### Multidimensional Array
Array of arrays:
```java
Person[][] table = new Person[2][3]; 
table[0][2] = new Person(“Mary”);
```
>Since rows are **not stored in adjacent positions** in memory they can be **easily exchanged**.
```java
double[][] balance = new double[5][6]; 
... 
double[] temp = balance[i]; 
balance[i] = balance[j]; 
balance[j] = temp;
```
---
#### Variable arguments
It is possible to pass a variable number of arguments to a method using the **varargs** notation 
	method( type ... args ) 

 The compiler assembles an array that can be used to scan the actual arguments 
 - Type can be primitive or class
```java
static int min(int... values){ 
	int res = Integer.MAX_VALUE; 
	for(int v : values){ 
		if(v < res) res=v; 
	} 
	return res; 
} 

public static void main(String[] args) { 
	int m = min(9,3,5,7,2,8); 
	System.out.println("min=" + m); 
	int[] numbers = {9,3,5,7,2,8}; 
	min(numbers); // also ok! 
}
```
---
### STATIC ATTRIBUTES AND METHODS
#### Static attributes
Represent properties which are common to all instances of a class 
- A single copy of a static attribute is shared by all instances of the class 
- Sometimes called **class attributes** as opposed to **instance attributes** 
- Static attributes exists before any object is created 
- A change performed by any object is visible to all instances at once 
They are defined with the **static** modifier.

Why?
Used to keep a shared property 
- A count of created instances 
- A pool of all instances 
Keep a common constant value.
```java
class Car { 
	static int countBuiltCars = 0; // Common to all the istances
	public Car(){ 
		countBuiltCars++; 
	} 
}
```
#### Static methods
Static methods are not related to any instance.
They are defined with the **static** modifier 
Used to implement functions:
```java
public class HelloWorld { 
	public static void main (String args[]) { 
		System.out.println("Hello World!"); 
	} 
}
public class Utility { 
	public static int inverse(double n){ 
		return 1 / n; 
	} 
}
```
The name of the class is used to access the member: 
	Car.countCountBuiltCars 
	Utility.inverse(10); 
It is possible to import all static items: 
	**import static** package.Utility.\*; 
Then all static members are accessible without specifying the class name 
>Impossible if class in default package.

Why static methods?
Implement functions 
- Avoid creating an object just to invoke the method (see e.g., main()) 
- Collected in utility classes 
Provide ideal factory method 
- Method to create an instance
##### Function method
A method whose return value depends only on the arguments 
- Typically defined as static 
Often collected within a **utility** class 
- Class containing static function methods 
Wrapper types include several function methods for conversion purposes.
##### Utility classes
- Math: Mathematical functions 
- Arrays: Functions to operate on arrays 
- Objects: Functions to operate on object 
- IO: Functions to perform console I/O 
- System: Interact with the operating system
###### Math
Math-related function methods 
- Trigonometric functions − sin(), cos(), tan() 
- Min-max − min(), max() 
- Exponential and logarithms − exp(), log() 
- Truncations − round(), ceil(), floor() 
- Random number generation − random() 
- Powers − pow(), sqrt()
###### Arrays
Arrays utility functions 
- Binary search (binarySearch()) 
- Copy (copyOf(), copyOfRange()) 
- Equality (equals(), deepEquals()) 
- Fill-in (fill()) 
- Sorting (sort()) 
- String representation (toString())
###### IO
Input-Output utilities
- static void **print**(Object obj); − Prints an object value (also primitives) 
- static void **println**(Object obj); − Prints an object value (also primitives) with newline 
- static void **println**(); − Prints a new line 
- static String **readln**(String prompt); − Read a string from the console with a prompt 
- static String **readln**(); − Read a string from the console
###### System
General purpose utilities 
- static long currentTimeMillis() − Current system time in milliseconds 
- static void exit(int code) − Terminates the execution of the JVM 
- static final PrintStream out − Standard output stream, Also err for standard error
---
#### Factory method
A method used to create an object 
- Encapsulates an explicit object creation with the **new** operator 
Can be used to: 
- Simplify creation 
	− E.g., when alternative classes can be created 
- Return objects from a pool 
	− Requires immutable objects 
	− Either pre-allocated or cached 
- Maintain a collection of created objects 
- Control new objects allocation 
	− See e.g., Singleton pattern
###### Integer
**valueOf**(int) 
- Replaces new Integer(int) 
- Caches values in the range -128 to 127 
**valueOf**(String) 
- Returns the integer corresponding to the parsed string 
- Same as: new Integer(Integer.parseInt(s))
---
#### Final Attributes
An attribute declared as **final**: 
- cannot be changed after object construction 
- can be initialized inline or by the constructor
```java
class Student { 
	final int years=3; 
	final String id; 
	public Student(String id){ 
		this.id = id; 
	} 
}
```
**Final parameters** cannot be changed 
- Non final parameters are treated as local variables (initialized by the caller) 
**Final variables** 
- Cannot be modified after initialization 
- Initialization can occur at declaration or later
---
#### Constants
Use **static final** modifiers 
- static implies no redundant copies 
- final implies not modifiable
```java
final static float PI = 3.14; 
… 
PI = 16.0; // ERROR, no changes 
final static int SIZE; // missing init
```
>All uppercase (coding conventions)
##### Static initialization block
Block of code preceded by static 
Executed at class loading time
```java
public final static double 2PI; 
static { 
	2PI = Math.acos(-1); 
}
```

---
### Singleton Pattern
Context: 
- A class represents a concept that requires a single instance 
Problem: 
- Clients could use this class in an inappropriate way
```java
private Singleton() { } 
private static Singleton instance; 
public static Singleton getInstance(){ 
	if(instance==null) 
		instance = new Singleton(); 
	return instance; 
}
```
