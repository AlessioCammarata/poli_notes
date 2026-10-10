JUnit is a testing framework for Java programs.
Written by Kent Beck and Erich Gamma
It is a framework with unit-testing functionalities, integrated in most IDEs.

For each test (method) Junit: 
- calls **pre-test** fixture 
	- Intended to acquire resources and create any objects that may be needed for testing 
- calls the test method
	- The actual test that checks the output of the element under test 
- calls **post-test** fixtures 
	- Intended to release resources and remove any objects created that is no longer needed
---
#### Test method
A test method returns no result.
It performs operations on the code under test and checks the results .
Checks are performed using a set of **assert*()** methods.
The JUnit framework detects the **anomalies** and reports them.
```java
assertTrue(boolean test) 
assertFalse(boolean test)
assertEquals(expected, actual) 
assertSame(Object exp, Object actual) 
assertNotSame(Object exp, Object act) 
assertNull(Object object) 
assertNotNull(Object object) 
fail()
```
>You can also put a text to print in case of error, the optional message
---
#### Fixtures
Portions of test cases that are cloned 
- For initializing or releasing resources 
They are called fixtures 
- Pre-test (set up) 
- Post-test (tear down) ▪

Can be collected in separate methods 
- Avoid duplication 
- Shorten test cases 
- Automatically executed before tests
#### Failures vs Errors
**Failure** 
- An assert*() method found the condition it checked is not verified 
- The program produced an output, but it is not the expected one 
**Error** 
- During the execution of the tests an error was found (e.g., NullPointerException) 
- The program could not produce any output due to an error
```java
public class Stack { 
	private int[] stack; 
	private int next = 0; 
	public Stack(){ this(10);} 
	public Stack(int size){ 
		stack = new int[size];
	} 
	public boolean isEmpty(){ 
		return next==0; 
	} 
	public boolean push(int i) { 
		if(next==stack.length) return false; 
		stack[next++] = i; 
		return true; 
	} 
	public int pop() throws StackException { 
		if(next==0) throw new StackException() 
		return stack[--next]; 
	}
}
```
#### Test stack
```java
public class TestStack { 
	@Test //Test annotation
	void testStack() throws StackException{ 
		Stack aStack = new Stack(); 
		assertTrue(aStack.isEmpty(), "Stack should be empty"); 
		aStack.push(10); 
		assertFalse(aStack.isEmpty(), "Stack should not be empty!"); 
		aStack.push(-4); 
		assertEquals(-4, aStack.pop()); 
		assertEquals(10, aStack.pop()); 
	} 
}
```
- @BeforeEach -> pre-test fixture
- @AfterEach   -> post-test fixture
---