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