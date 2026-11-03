Delegating error handling to higher levels.
- Methods detecting anomalies might not be able to recover from an error 
- Caller method can handle errors more suitably than the detecting method itself

>Localize error handling code by separating it from operating code.

Anomaly could be managed:
- Detection 
  Check conditions revealing an anomaly (if or catch)
- Signaling 
  Inform the caller about the anomaly 
- Dispatch 
  Receive and redirect the anomaly signal (propagating the signal)
- Handling 
  Perform operation to address an anomaly
##### Signaling
- Program abort (handling) 
  Abrupt termination of the execution 
- Special value 
  Return a special value to indicate error (-1, null)
- Global status 
  Global variable contain error reports 
- Exceptions 
  Throw an exception
###### Abort
If a non-remediable error happens, call System.exit() 
- Abort program execution, VM does not perform any cleanup or resource release 
- A method causing an unconditional program interruption is not very dependable (nor usable)

>Not nice, since is brutal. The JVM doesn't do any cleaning stuff.
###### Special value
▪Special values are distinct from normal values returned 
	pb.find("non-exist”); // null
	"ABCD".indexOf("F");  // 1-
	Math.pow(-1, 0.5); //NaN

>Code is messy to write and hard to read, only the direct caller can intercept the error.
###### Global error variable
in java is never used
##### Exceptions
The code detecting the the error will **throw** an exception, it can be either 
- Developers’ code 
- Third-party library

At some point, up in the hierarchy of method invocations, a caller will **intercept** and **handle** the exception.
In between, dispatching methods can 
- Relay the exception (complete delegation) 
- Intercept and re-throw (partial delegation)
```java
throw  // Thows an exception
throws // Declare a potential exception 
try    // Introduces code to watch for exceptions 
catch  // Defines the exception handling code
```
>It also defines a new type 
>- **Throwable** class

Example:
```java
public class EmptyStack extends Exception{} //Extend the class

public class Stack{ 
	public int pop() throws EmptyStack { 
		if(size == 0) { 
			EmptyStack e = new EmptyStack(); 
			throw e; 
		} 
	... 
	} 
}
```
###### Throw
Performs the exception throw.
When an exception is thrown, the execution of the current method is interrupted immediately:
- The code immediately following the throw statement is not executed 
- Like a return statement 
The catching phase starts
###### Throws
If a method might generate an exception, it must must declare it in its signature 
- All exception type(s) are listed after the throws keyword 

Allow checking dispatching by caller.
Must declare exception thrown both 
- directly by the method, or 
- by called methods and relayed
##### Dispatching
When a fragment of code can possibly generate an exception, the exception must be dispatched: 
- Relay the exception and let it propagate up the call stack 
   Method has a throws declaration, 
- Catch, stop the exception, and handle it  
  Code enclosed in try{}catch(){} statement 
- Catch, partially handle, and re-throw
##### Run-time catching
Once an exception is thrown the normal execution is suspended.
The thrown exception “walks back” the call stack until either: 
- It is caught by one of the methods 
- It overtakes main() 
	  In this case the JVM prints the exception (and the full stack trace) and terminates execution

**Examples**
###### Relay
```java
class Dummy { 
	Stack st; 
	public int foo() throws EmptyStack{ 
		int v = st.pop(); 
		return v + 1; // Not executed in case of an exception
	} 
}
```
###### Catch and Handle
```java
class Dummy { 
	Stack st; 
	public int foo(){ 
		try{ 
			int v = st.pop(); 
			return v + 1; // Not executed in case of an exception
		} catch (StackEmpty se) { 
			// do something 
		} 
		return 0; // default value 
} }
```
###### Catch and re-throw
```java
class Dummy { 
	Stack st; 
	public int foo() throws EmptyStack{
		try{ 
			int v = st.pop(); 
			return v + 1; // Not executed in case of an exception
		} catch (StackEmpty se) { 
			// intermediate handling 
			throw se; 
		}
} }
```
#### Exception classes

##### Class Throwable
Exception classes must extend class **Throwable**.
Contains a snapshot of the call stack.
May contain a message string which provides information about the anomaly. 
May also contain a **cause**, another exception that caused this one to be thrown.

**getMessage()** 
- returns the error message associated with the exception 
**getCause()** 
- Return a possible other exception that caused this one 
**printStackTrace()** 
- Prints the stack trace until the place when the exception was created 
- The traces is automatically filled in by Throwable constructor 
- This is the method called by JVM on uncaught exceptions
![[exceptions_hierarchy.png]]
###### Examples
**Error**
- OutOfMemoryError 
**Exception** 
- ClassNotFoundException 
- InstantiationException 
- IOException 
- InterruptedException 
**RuntimeException** 
- NullPointerException 
- ClassCastException
##### Exceptions and loops
For errors affecting a single iteration, the try-catch blocks is nested in the loop.
In case of exception the execution goes to the catch block and then proceed with the next iteration.
```java
while(true){ 
	try{ 
		// potential exceptions 
	}catch(AnException e){ 
		// handle the anomaly 
	} // and continue with next iteration 
}

//OR

try{ 
	while(true){ 
		// potential exceptions 
	} 
}catch(AnException e){ // exit the loop and … 
	// handle the anomaly 
}
```
>The first one checks at any iterations, while the second one check generically
>- FIrst one is sth related to loop (doesn't make sense to continue)
>- Second one is more related to the result of it

We can see here:
```java
//I'm stopping when i found a string.
try{ 
	int sum = 0; 
	for(String s : strings) { 
		sum += Integer.parseInt(s); 
	} 
	System.out.println("Sum: " + sum);
}catch(Exception e){ // exit the loop and … 
	System.err.println("Error!");
}

//OR

//I'm not stopping when i found a string, it just skip it
int sum = 0; 
for(String s : strings) {
	try{ 
		sum += Integer.parseInt(s);
	}catch(NumberFormatException nfe){ 
		System.err.println("Wrong: "+s);
	} // and continue with next iteration 
}
System.out.println("Sum: " + sum);
```

It is also possible to nest the try catch, for example to solve roman number:

```java
//I'm not stopping when i found a string, it just skip it
int sum = 0; 
for(String s : strings) {
	try{ 
		sum += Integer.parseInt(s);
	}catch(NumberFormatException nfe){ 
		try { 
			sum += parseRoman(s); 
		}catch(NumberFormatException re) { 
			System.err.println("Wrong " + s); 
		}
	} // and continue with next iteration 
}
System.out.println("Sum: " + sum);
```
>It's also possible to have multiple catch bloch.
##### Matching rules
Only **one handler** is executed 
- The first one matching the thrown exception (order matters)
- A catch matches if the thrown exception is instanceof the catch’s exception class 

Catch blocks must be **ordered by their “generality”** 
- From the most specific (derived classes) to the most general (base classes)
---
##### finally
The keyword finally introduces a code block that is executed in any case 
- No exception 
- Caught exception 
- Uncaught exception (Both checked and unchecked)
- Does not work in case of System.exit() 

Can be used to 
- Dispose of resources 
- Close a file
```java
MyFile f = new MyFile(); 
if (f.open("myfile.txt")) { 
	try { 
		exceptionalMethod(); 
	}catch(IOException e){ 
		//… 
	} finally { 
		f.close(); 
	} 
}
```
---