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


>**this** references the current object
>super references the parent **class**

##### Final method
The keyword **final** applied to a method makes it not overridable by subclasses.

---
#### Class object
- java.lang.Object 
- All classes are subtypes of Object

Why?
**Generality**: 
- *any instance of any class can be seen as an **Object** instance 
- Object is the universal reference type 
**Common behavior**: 
- Object defines some common **operations** which are inherited by all classes 
- Often, they are **overridden** in sub-classes

>toString() : String 
>equals(Object) : boolean
##### Generality
Each class is either directly or indirectly a subclass of **Object**.
It is always possible to upcast any instance to Object type
```java
AnyClass foo = new AnyClass(); 
Object obj; 
obj = foo;
```
>References of type Object play a role similar to void* in C

We can collect heterogeneous objects into a single container:
```java
Object[] objects = new Object[4]; 
objects[0]= "First!"; 
objects[2]= new Employee(); 
objects[1]= new Integer(2); // Note: wrappers must be used instead of primitive types
Objects[3]= 42; 
for(Object obj : objects){ 
	IO.println(obj); 
}
```
##### Object class methods
- **toString**() -> Returns string representation of the object 
- **equals**() -> Checks if two objects have same contents 
- **hashCode**() -> Returns a unique code 
- Protected: 
	- **clone**() – Creates a copy of the current object 
	- **finalize**() – Invoked by GC upon memory reclamation
>Examples:
###### toString
```java
class Employee { 
// … 
    //toString
	@Override 
	public String toString(){ 
		return "Employee: " + name; 
	} 
}
```
>The default (Object) implementation returns:
>	ClassName@#hashcode#
###### equals()
Tests equality of values. 
Default implementation compares references:
```java
public boolean equals(Object other){ 
	return this == other; 
}
```
>Must be overridden to compare contents
- **Reflexive**: x.equals(x) == true
- **Symmetric**: x.equals(y)\==y.equals(x) 
- **Transitive**: for any reference x, y and z 
	- if x.equals(y)\==true && y.equals(z)\==true => x.equals(z)\==true 
- **Consistent**: multiple calls x.equals(y) consistently return true (or false) 
	- No information used in the comparison should be changed (immutables) 
- **Robust**: x.equals(null) == false
```java
class Employee { 
// … 	
	//equals
	@Override 
	public boolean equals(Object o){ 
		if( !(o instanceof Employee)){ // null instanceof X → false
			return false; 
		} 
		Employee other = (Employee) o; 
		return this.name.equals(other.name); 
	}
}
```
###### hashcode()
Returns a (fairly) unique code for the object.
Can be used as 
- index in hash tables 
- quick approximation for equality 

The default implementation (Object) converts the internal address of the object into an integer.
- **Consistent**: hashCode() must return the same value, if no information used in equals() is modified.
- **Equal compliant**: if two objects are equal for equals() method, then calling hashCode() on the two objects must return the same value
---
##### Variable arguments - example
```java
static void plst(String pre, Object...args){ // ...args
	IO.print(pre + " "); 
	for(Object o : args){ //args
		if(o!=args[0]) IO.print(", "); 
		IO.print(o); 
	} 
	IO.println(); 
} 

public static void main(String[] args) { 
	plst("List:", "A", 'b', 123, "hi!"); // Character, Integer
}
```
---
#### Abstract classes
Often, a superclass is used to define common behavior for children classes.
In this case some methods may have no obvious meaningful implementation in the superclass.
>Abstract classes leave the behavior partially unspecified, the abstract class cannot be instantiated.
```java
public abstract class Shape { 
	private int color; 
	
	public void setColor(int color){ 
		this.color = color; 
	} 
	
	// to be implemented in child classes 
	public abstract void draw(); //No method body
}

class Circle extends Shape { 
	public void draw() { 
		// body goes here 
	} 
} 

Object a = new Shape(); // Illegal: abstract 
Object a = new Circle();// OK: concrete
```
>The abstract modifier marks the method as non-complete / undefined 
>The modifier must be applied to all incomplete method and to the class
```java
public abstract class Shape { 
	public void setColor(int color){…} 
	
	// implemented in child classes 
	protected abstract void draw(); //No method body
}
```
>A class must be declared abstract if any of its methods is **abstract**.

A class that extends an abstract class should implement (i.e. override) all the base class abstract methods.
If any abstract method is not implemented, then the class must be declared abstract itself.
###### Example: Sorter
```java
public class Sorter { 
	public void sort(Object v[]){ 
		for(int i=1; i<v.length; ++i) 
			for(int j=0; j<v.length-i; ++j){
				if(compare(v[j],v[j+1])>0){
					Object o=v[j]; 
					v[j]=v[j+1]; 
					v[j+1]=o; 
				}
			}
	} 
	protected int compare(Object a, Object b){ 
		IO.println("Someone forgot about" + 
					"the compare() method!"); 
		return 0; // why not 42? 
	} 
}

public abstract class Sorter { 
	public void sort(Object v[]){ 
		for(int i=1; i<v.length; ++i) 
			for(int j=0; j<v.length-i; ++j){
				if(compare(v[j],v[j+1])>0){
					Object o=v[j]; 
					v[j]=v[j+1]; 
					v[j+1]=o; 
				}
			}
	} 
	abstract int compare(Object a, Object b); 
}

//StringSorter
class StringSorter extends Sorter { 
	@Override
	int compare(Object a, Object b){ 
		String sa=(String)a; 
		String sb=(String)b; 
		return sa.compareTo(sb); 
	} 
}

//main
Sorter ssrt = new StringSorter(); 
String[] v={"g","t","h","n","j","k"}; 
ssrt.sort(v);
```
---
#### Java Interfaces
Special type of class where 
- Methods are implicitly abstract (no body) 
- Attributes are implicitly static and final 
- Members are implicitly public 

Defined with keyword **interface**, Instead of class.
Cannot be instantiated -> i.e. no new (like abstract classes) 
Can be used as a type for references -> Like abstract class

All methods are implicitly 
- abstract 
- public
```java
public interface Expression{ 
	double eval(); 
	String formula(); 
}
```
A class **implements** interfaces.
A class implementing an interface must override all interface methods, unless the class is declared abstract:
```java
class Value implements Expression { 
	@Override void value(){ … } 
	@Override void formula(){ … } 
}
```

>An interface cannot extend a class:
```java
interface Bar extends String { // class, not doable
	void print(); 
}
```

>An interface can extend many interfaces:
```java
interface Bar extends Orderable, Comparable{ //interfaces
	... 
}
```

>Inheritance:
```java
class Employee extends Person implements Cloneable, Comparable {
	…
}
```
#### Functional Interface
An interface containing **only one regular method** (abstract)
- May include any additional static or default methods 
Method’s semantics is purely functional 
- The result of the method is based solely on the arguments
- E.g., java.lang.Comparator

Predefined interfaces are defined in
- java.util.function 
- Specific for different primitive types 
- Generic version (see Generics) 

>The predefined interfaces can be used to define behavioral parameterization arguments
##### Functions
Consumer 
- void accept(Object value) 
Supplier 
- Object get() 
Predicate 
- boolean test(Object value) 
Function 
- Object apply(Object value) 
BiFunction 
- Object apply(Object l, Object r)
###### Int versions
IntFunction 
- Object apply(int value) 
IntConsumer 
- void accept(int value) 
IntPredicate 
- boolean test(int value) 
IntSupplier 
- int getAsInt() 
IntBinaryOperator 
- int applyAsInt(int left, int right)
##### Interface Usage Patterns
- Define a **common “interface”**  
- Provide a **common behavior** -> Define method(s) to be called by algorithms 
- Enable **behavioral parameterization** -> Encapsulate behavior in an object parameter 
- Enable **communication decoupling** -> Define a set of callback method(s) 
- Allow **class flagging**
```java
public interface Complex { 
	double real(); 
	double im(); 
	double mod(); 
	double arg(); 
}

//ComplexRect
class ComplexRect implements Complex { 
	private double im, re; 
	public ComplexRect(double re, double im) { 
		this.im = im; 
		this.re = re; 
	} 
	
	@Override public double real() { 
		return re; 
	} 
	
	@Override public double im() { 
		return im; 
	} 
	
	@Override public double arg() { 
		return Math.atan2(im, re); 
	} 
	
	@Override public double mod() { 
		return Math.sqrt(re*re+im*im); 
	} 
}

//ComplexPolar
class ComplexPolar implements Complex { 
	private double mod, arg; 
	public ComplexPolar(double mod, double arg) { 
		this.mod = mod; 
		this.arg = arg; 
	} 
	
	@Override public double real() { 
		return mod*cos(arg); 
	} 
	
	@Override public double im() { 
		return mod*sin(arg); 
	} 
	
	@Override public double mod() { 
		return mod; 
	} 
	
	@Override public double arg() { 
		return arg; 
	} 
}

//Main
Complex c1 = new ComplexRect(4,3); 
IO.println(c1 + " -> Module " + c1.mod() + " argument: " + c1.arg()); 


Complex c2 = new ComplexPolar(5,0.6435); IO.println(c2 + " -> Real " + c1.real() + " Imaginary: " + c1.im());
```
###### Static method in Interface
If alternatives are known in advance, static methods can serve as factory methods
```java
public interface Complex { 
	double real(); 
	double im(); 
	double mod(); 
	double arg(); 
	
	static Complex fromRect(double re, double im){ 
		return new ComplexRect(re,im); 
	} 
	
	static Complex fromPolar(double mod, double arg){ 
		return new ComplexPolar(mod,arg); 
	} 
}
```
###### Default methods in interface
These are not abstract methods, but method written inside the interface:
```java
//add advertisement (default method)
public default void playWithADV(String adv){
	IO.println(adv);
	play();
}
```
>You can still have some code inside in order to mantain compatibility with legacy code.
>You have to call these from the object, while the static are callable from the class.
---
##### Common behaviour
Context 
- An algorithm requires its data to provide a predefined set of common operations 
Problem 
- The algorithm must work on diverse classes 
Solution 
- An interface defines the required methods 
- Classes implement the interface and provide methods that are used by the algorithm
###### Sorting
Class java.utils.Arrays provides the static method sort()
```java
int[] v = {7, 2, 5, 1, 8, 5}; 
Arrays.sort(v);
```
Sorting object arrays requires a means to compare two objects: 
- java.lang.Comparable
##### Comparable
```java
public interface Comparable{ 
	int compareTo(Object obj); 
}
```
Returns 
- <0 if this precedes obj 
- =0 if this equals obj 
- >0 if this follows obj
Example
```java
public class Student implements Comparable { 
	int id; Student(int id){ 
		this.id=id; 
	} 
	
	@Override 
	public int compareTo(Object o){ 
		Student other = (Student)o; 
		return this.id - other.id; 
	} 
}
```
##### Iteration
```java
public interface Iterable{ 
	Iterator iterator(); 
}
```
Any class implementing Iterable can be the target of a for-each construct 
- Uses the Iterator interface
```java
public interface Iterator { 
	boolean hasNext(); 
	Object next(); 
}
```
Semantics: 
- Initially positioned before the first element 
- **hasNext**() tells if a next element is present 
- **next**() returns the next element and advances by one position
###### Using an iterator
```java
Iterator it = seq.iterator(); 
while( it.hasNext() ){ 
	Object element = it.next(); 
	IO.println(el); 
}
//OR
for(Object element : seq){ 
	IO.println(el); 
}
```
---
##### Anonymous Classes
Classes without name, that exists only when you define them in the code.
```java
Comparable obj = new Comparable(){ //Anonymous class implementing comparable behaviour
	public int compare(...){...}
};

Consumer<Song> consumerOfSongs= new Consumer<Song>(){ 
	@Override 
	public void accept(Song s) { 
		for (String v : s.getVerses()) { 
			IO.println(v.toUpperCase()); 
		} 
	} 
};
```
Interfaces can be used to instantiate anonymous local classes.

>Per esempio per oggetti che non sono multipli nel codice (singola istanza), in quel caso ha senso non creare un file a parte ma creare appunto un'anonymous class che implementa i metodi legati alla singola istanza.
>In questo modo anche se fosse un solo metodo, tu puoi richiamare piu volte lo stesso metodo senza dover riscrivere il codice.
##### Lambda functions
We want to reach the same results, but with lambda functions (writing **less code**):
```java
Consumer<Song> anotherMixingOption = s->{ //Anonymous inner class (compressed)
	for(String v : s.getVerses()){
		IO.println(v.toUpperCase());
	}
};
```
Non devi specificare il tipo si capisce che è song perche è un Consumer of songs.

>Once you get a song s, the method should apply the function in the breckets {}.
##### Behavioral parameterization
Context 
- A generic algorithm is fully defined but a few given core operations that vary often 
Problem 
- Multiple implementations with significant code repetitions 
- Complex conditional structures 
Solution 
- The operations are defined in interfaces 
- Objects implementing the interface are used to parameterize the algorithm
Example:
```java
consumerOfSongs2=s->s.playLoud();

//Same with behavioural parameterization
Consumer<Song> metRefMixer = Song::playLoud; //Using the same loop with playLoud method on it (:: is like a pointer to a method)
```
>PlayLoud is a method inside the Song class, which actually does the uppercase print of the song.
>I can simply use the functionality of it, inside the accept method of the Consumer interface.
>The compiler will create the Anonymous inner class and implement the previous code.

Why should I care if I can modify the method??
**Example:**
```java
static void performConcert(Iterable<Song> playlist, Consumer<Song> behaviour){
	IO.println("=== Concert starts! ===);
	for(Song s : playlist){
		behaviour.accept(s);
	}
	
	IO.println("=== Concert finished ===");
}

performConcert(playlist, Song::play); //Normal concert
performConcert(playlist, mrtRefMixer); //Rock concert
performConcert(playlist, s->s.playWithADV(adv)); //Sponsor concert
```
>This way I can parametrized the behaviour of the concert based on the Consumer I pass as a paremeter.
---
