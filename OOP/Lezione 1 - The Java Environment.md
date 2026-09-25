OO language provides constructs to: 
- **Define classes** (types) in a **hierarchic way** (inheritance)
- **Create/destroy objects** dynamically 
- Send **messages** (w/ dynamic binding) 

>No procedural constructs (pure OO language) 
- no functions, class methods only 
- no global vars, class attributes only
##### Features of Java
**Platform independence** (portability) 
- Write once, run everywhere 
- Translated to intermediate language (bytecode) 
- Interpreted (with optimizations, i.e. JIT) 

**High dynamicity** 
- Run time loading and linking 
- Dynamic array sizes

**Robust language**, less error prone 
- Strong type model and no explicit pointers – Compile-time checks --> **strongly Typed**
- Run-time checks – No array overflow 
- **Garbage collection** – No memory leaks 
- Exceptions as a pervasive mechanism to check errors

**Shares many syntax elements w/ C++** 
- Learning curve is less steep for C/C++ programmers 

**Quasi-pure OO language** 
- Only classes and objects (no functions, pointers, and so on) 
- Basic types deviates from pure OO... 

**Easy to use**

**Supports “programming in the large”** 
- JavaDoc 
- Class libraries (Packages) 

**Lots of standard utilities included** 
- Concurrency (thread) 
- Graphics (GUI) (library) 
- Network programming (library) 
	- socket, RMI 
	- applet (client side programming)
---
#### Classes
Only one first level concept: the class.
The source code of a class sits in a .java file having the **same name**:
- Rule: one file per class 
- Enforced automatically by IDEs 
- Case-wise name correspondence

```java
public class First { 
}
```
#### Methods
In Java there are no functions, but only methods within classes.
The execution of a Java program starts from a special method:
```java
public static void main(String[] args)
// In C: int main(int argc, char* argv[])
```
>return type is void.
>args[0] is the first argument on the command line (after the program name).

---
The portability of Java it is due to the Java Compiler which convert the java file into a class file, then the Java Virtual Machine interpret the class and produce the output.
![[img/java_working.png]]
#### Java compiler
Command: javac First.java 
- takes a list of source files (e.g. *.java) 
- generates the corresponding .class 
- For each reference to a class 
	- looks in the predefined libraries 
	- then looks for the source file locally and adds it to the list 
- After all files have been compiled, the checks for cross-reference integrity.
>You can do it from the terminal or simply launching the project.

---
#### Coding conventions
- Use **camelBackCapitalization** for compound names, not underscore 
- Class name must be **Capitalized** 
- Method names, object instance names, attributes, method variables **must all start in lowercase** 
- Constants **must be all uppercases** (w/ underscore) 
- Indent **properly**

```java
class ClassName { 

final static double PI = 3.14; 

private int attributeName; 

	public void methodName(){ 
		int var; 
		if ( var==0 ) { 
		} 
	} 
}
```
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
