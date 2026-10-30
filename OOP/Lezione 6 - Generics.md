#### Generic classes
A class of whatever type you want
```java
public class Pair<T> {
	T a, b;
	public pair (T a, T b){
		this.a = a;
		this.b = b;
	}
	
	public T first(){return a;}
	public T second(){return b;}
}
```
>This is more generic and safe.

Declaration is slightly longer, but usage is **easier**:
```java
Pair<String> sp = new Pair<>("One", "Two");
Pair<Integer> ip = new Pair<>(1,2);
Pair<String> mixp = new Pair<>("one",2);

String a = sp.second();
Integer b = ip.first(); //Integer auto-unboxed
String a = mixp.first(); //So you are requesting a string, from a mixed object
```

Example:
```java
//Generics
Pair<String> stPair = new Pair<String>("The Office", "Stranger Things");
Pair<Integer> intPair = new Pair<>(1,2);
Pair<Song> songPair = new Pair<>(song1, song2);

//I'm handling different type of objects, and i can use the same methods:
IO.println(strPair.getFirst());
IO.println(songPair.getFirst());

//Passing wrong type
Pair<String> stPair = new Pair<>("Daredevil", 1); // Compiler can't infer
Pair<String> stPair = new Pair<String>("Daredevil", 1); // Compiler complain
```
This way compiler complain, and you don't have run-time errors. (**Safer**)

For mixepPair, you need to create a new class:
```java
public class MixedPair<T, U> {
	T a;
	U b;
	public MixedPair(T a, U, b){
		this.a = a;
		this.b = b;
	}
	public T getFirst(){
		return a;
	}
	public U getSecond(){
		return b;
	}
}

MixedPair<String,Song> mx1 = new MixedPair<String,Song>(bestSong.getTitle(), bestSong);
```
- Only one class definition which can handle all possible mixed type pairs
Usually:
- T(ype)
- R(eturn)
- E(lement)
#### Generic interfaces
In java the declaration of comparable interface is:
```java
public interface Comparable<T>{
	int compareTo(T obj);
}
```
This is valid also for Iterable and Iterator.
#### Generic methods
```java
public static Object remove(Object[] ary, Object el){
	for(int i=0; i<ary.length; ++i){
		if(ary[i] != null && ary[i].equals()){
			Object removed = ary[i];
			ary[i] = null;
			return removed;
		}
	}
	return null;
}

String[] words = {...};
String f = (String)remove(words,"fox");

//Generic method
public static <T> T remove(T[] ary, T el){
	for(int i=0; i<ary.length; ++i){
		if(ary[i] != null && ary[i].equals()){
			T removed = ary[i];
			ary[i] = null;
			return removed;
		}
	}
	return null;
}

String f = remove(words,"fox");
//This way we get a compiler error before the down-casting run-time error
```
---
#### Bounded types
Maybe I don't want any type on T, but a certain group.
T is **Unbounded type**, you can put whaterver in it.
```java
public static <T> void max(T ary[]){
	T max = null;
	for(T current : ary){
		if(max == null || max.compareTo(current) < 0){
			max = current;
		}
	}
	return max;
}
```
>This is not safe, because there could be Object not comparable, you need the comparability concept. (Compare means ordering)

**Bounded types:**
- **Upper Bound**
I can only replace T with something extending B including B itself.
	<T **extends** B>
B is called **upper bound**.
It is possible to specify multiple upper bounds:
	<T **extends** B1 & B2>

- **Lower bound**
I can only use a wildcard to represent a type that is `D` or a supertype of `D`.
	<\? **super** D>
D is called **lower bound**.
It is possible to specify only one lower bound.

Example:
```java
public static <T extends Comparable<T>> T max(T ary[]){
	T max = null;
	for(T current : ary){
		if(max == null || max.compareTo(current) < 0){
			max = current;
		}
	}
	return max;
}
```
---
#### Generics Invariance
You can't assign a `Pair<Integer>` to a `Pair<Object>`, even though `Integer` extends `Object`.

This is called **container invariance**: inheritance between element types does not imply inheritance between their containers.
- Elements inheritance does not imply container inheritance.
```java
Pair<Integer> intPair = new Pair<>();
Pair<Object> objPair = intPair; // Compilation error!
```
`Pair<Integer>` is not a subtype of `Pair<Object>`.
#### Arrays Covariance
In Java, arrays are **covariant**: if `Integer` extends `Object`, then an `Integer[]` can be assigned to an `Object[]`.
```java
Integer[] intArray = new Integer[10];
Object[] objArray = intArray; // Allowed!
```

However, storing an object that is not an `Integer` in this array causes an `ArrayStoreException` at runtime.
```java
objArray[0] = "Hello"; // ArrayStoreException!
```
**Key difference:**
- Generics are invariant: `Pair<Integer>` is not a subtype of `Pair<Object>`.
- Arrays are covariant: `Integer[]` is a subtype of `Object[]`.
---
#### Wildcards
Allow to express constraints when using generic types:
- \<?>
	- Unknown, unbounded
```java
void clearFirst(Pair<?> p){
	p.set1st("");
}
```
It's not possible to assign anything to the \<?>. (unknown)
- <>
- <>

Example
```java
<T> void sort(Pair<T> p, Comparator<T> cmp){
	if(cmp.compare(p.first,)){
		T tmp = p.first();
		p.set1st(p.second());
		p.set2nd(tmp);
	}
}


Pair<Integer> pi = new Pair<>(4,2);
Comparator ci = (i1,i2)->i1.compareTo(i2);
sort(pi, ci);
Comparator<
```
---
#### Type erasure
The compiler generates only one class for each generic type declaration 
	Compilation **erases** the type parameters
```java
Pair pi = new Pair<>(1,2); 
Pair ps = new Pair<>("one","two"); 

boolean is = pi instanceof Pair; 
boolean si = ps instanceof Pair;
```
Classes corresponding to generic types are generated by **type erasure**.
The erasure of a generic class is a **raw type** 
- where any reference to the parameters is substituted with the parameter erasure 
- Raw type of generic class G\<T> is G 
Erasure of a parameter is the erasure of its first bound 
- If no bound is provided, then it is Object
Examples:
- For: \<T>: T → Object 
- For: \<T extends Number>: → Number 
- For: \<T extends Number & Comparable>: → Number
##### Consequences
1. Since there is only one class, within the class no information is available about the type parameters ->They have been erased! 

The actual value of type parameter is known only to the user of a generic type 
Compiler applies checks only when a generic type is used, not within it.

2. Whenever a generic or a parameter is used, the compiler automatically adds a cast to its erasure
- To avoid inconsistencies and mistakes:
	- instanceof cannot be used on generic types
	- instanceof is valid for G o G\<?>

3. It is not possible to instantiate an object of the type parameter from within the class
```java
class Triplet { 
	private T[] triplet; 
	Triplet(T a, T b, T c){ 
		triplet = new T[]{a,b,c}; // Compiler cannot create a generic array of T
	} 
}
```
The type parameter cannot be used inside the raw type in any way

4. The compiler checks overloads and overrides after type erasure
```java
class Example { 
	void m(T t, U u){} 
	void m(U u, T t){} //Duplicate method (both object type)
	void mm(T t){} 
	void mm(U u){} //Duplicate method
	U mm(T t){} // Duplicate method, note: return type is not part of signature
}
```
5. Inheritance together with generic types leads to several possibilities
It is not possible to implement twice the same generic interface with different types
```java
class Student implements Comparable<Student>

class MasterStudent extends Student implements Comparable<MasterStudent>
//The interface Comparable cannot be implemented more than once with different arguments
```
##### Type inference
Upon generic method invocation, compiler infers the type argument (**capture**).
Inference is based on 
- Target type 
- Argument type 

It is possible to use a type witness, although often useless 
- Arrays.\<Student>sort(sv);
---
#### Example of Generic Comparator
Interface java.util.Comparator 
	public interface Comparator\<T>{ 
		int compare(T a, T b); 
	}
```java
Arrays.sort(sv, (a,b) -> a.id – b.id );

Arrays.sort(sv, new Comparator<Student>(){ 
	public void compare(Student a, Student b){ 
		return a.id – b.id;
	}
};
```
##### Comparator factory
Most comparators take some information out of the objects to be compared
- Typically through a getter 
- Such values are primitive or are comparable using their natural order (i.e. Comparable) 
Such comparator can be generated starting from a key getter functional object: 

	static <T,U extends Comparable<U>> 
	Comparator<T> comparing(Function<T,U> keyGetter)
```java
Arrays.sort(sv,comparing(Student::getId));

static <T,U extends Comparable<? super U>> 
Comparator<T> comparing(Function<T,U> keyGetter){ 
	return (a,b) -> keyGetter.apply(a).compareTo(keyGetter.apply(b)); 
}
```
>In pratica passi una funzione che sia in grado di gestire l'input e che si occupi del compare.

è possibile fare anche comparator composition usando comparing() e poi thenComparing().
