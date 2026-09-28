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
---