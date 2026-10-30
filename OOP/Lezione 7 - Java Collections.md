All the collections are based on Object Class.
### Collections Framework
- Interfaces (ADT, Abstract Data Types) 
- Implementations (of ADT) 
- Algorithms (sort) 
- Contained in the package java.util
#### Interfaces
Can be separated in
- Group containers
- Associative containers![[interfaces.png]]
##### Group containers
The father is **Iterable**.
Then there is the **collection**, we have the method add to place the Object in the container.
Then there are some specific ones (Set, Queue, List).
- **List** -> Index or pointer to object
- **Queue** -> FIFO (insert from the tail and extract from the head or viceversa)
- **Set** ->All the objects are unique
	- **SortedSet**, the objects are also ordered
##### Associative containers
Typically map, we can manage object having a key and a value, similar to dictionaries.
- **Map** and **SortedMap**
#### Implementations
Usable implementation of the interfaces:
![[implementations.png]]
- Array List (Can automatically increase the size of the Array)
- Linked List and Priority Queue are below Queue
- HashSet -> we use hash functions to manage data
- Linked HashSet is also Iterable
#### Group Containers (Collections)
**Group** of elements (**references** to objects) 
It is not specified whether they are 
- Ordered / not ordered 
- With Duplicates / without duplicates 
Implements **Iterable**. 
All classes implementing Collection shall provide two constructors 
- C() 
- C(Collection c)
###### Collection Interface
```java
int size() 
boolean isEmpty() 
boolean contains(E element) 
boolean containsAll(Collection<?> c) 
boolean add(E element) 
boolean addAll(Collection<? extends E> c) 
boolean remove(E element) 
boolean removeAll(Collection<?> c) 
void clear() 
Object[] toArray() 
Iterator<E> iterator()
```
###### toArray()
Object[] toArray() 
- Due to type erasure the collections do not know the type of elements 
- For generality, an Object[] is returned 

\<T>T[] toArray(T[]) 
- The correct type of array is passed, If not large enough a new array of the correct type and length is created and returned.
#### List
Can contain **duplicate elements** 
**Insertion order is preserved** 
User can define insertion point 
Elements can be accessed by **position** 
Extends Collection interface
##### List Interface
```java
E get(int index) 
E set(int index, E element) 
void add(int index, E element) 
E remove(int index)

boolean addAll(int index,Collection c) 
int indexOf(E o) 
int lastIndexOf(E o) 
List subList(int from, int to)
```
Extends Collection, inherits allits methods.
Size initially 0 (or size of collection passed to constructor)
Semantics of methods: 
- add(e) appends in position size() 
- add(e,i) insert in position i and shifts right elements for i-th on 
	-  0 <= i <= size() 
- set(e,i) replaces 
	- 0 <= i < size()
##### List Implementations
ArrayList\<E> 
- ArrayList() 
- ArrayList(int initialCapacity) 
- ArrayList(Collection c) 
- void ensureCapacity(int minCapacity) 
LinkedList\<E>
- void addFirst(E o) 
- void addLast(E o) 
- E getFirst() 
- E getLast() 
- E removeFirst() 
- E removeLast()
##### Queue Interface
Collection whose elements are inserted using an 
- Insertion order (FIFO) 
- Element natural order (Priority queue) 
Defines a **head** position where the **first** element is, which can be accessed with: 
- peek() just retrieves first element 
- poll() retrieves and removes it
##### Queue Implementations
**LinkedList** 
- head is the first element of the list 
- FIFO: Fist-In-First-Out 
**PriorityQueue** 
- head is the smallest element 
- “order” is determined either 
	- Natural ordering (Comparable) 
	- Comparator passed to constructor
##### Set Interface
Contains no methods, only those inherited from Collection 
**add()** has the restriction that **no duplicate elements** are allowed 

Iterator 
- The elements are traversed in **no predictable order**.
##### Set Implementations
**HashSet** implements Set 
- Hash tables as internal data structure (faster) 
**LinkedHashSet** extends HashSet 
- Elements are traversed by iterator according to the **insertion order** 
**TreeSet** implements SortedSet 
- R-B trees as internal data structure (computationally expensive) 
- Elements are traversed in element order
#### Associative Containers (Maps)
##### Map
A container that associates **keys to values** (e.g., SSN ⇒ Person) 
Keys and values must be **objects** 
**Keys** must be **unique** -> Only one value per key 

Following constructors are common to all collection implementers 
- M() 
- M(Map m)
##### Map Interface
```java
V put(K key, V value) 
V get(K key) 
Object remove(K key) 
boolean containsKey(K key) 
boolean containsValue(V value) //Checking on values
public Set<K> keySet() 
public Collection<V> values() 
int size() 
boolean isEmpty() 
void clear()
```
##### Map Implementations
Similar to Set 
**HashMap** implements Map 
- No order 
**LinkedHashMap** extends HashMap 
- Insertion order 
**TreeMap** implements SortedMap -> logaritmic access
- Ascending key orde
###### HashMap
Has a **constant time** to access any value.
### Optional
###### Nullability problem
The typical convention in Java APIs is to let a method return a null reference to represent the absence of a result.
The caller must check the return value of the method to detect that case.
In absence of checks NPEs may occur -> NPE is NullPointerException
##### Optional\<T>
**Optional** is a class used to represent a potential value.
Methods returning Optional\<T> make explicit that the return value may be missing
- Forces the clients to deal with potentially empty optional

Access to embedded value through 
- boolean **isPresent**() 
	– checks if Optional contains a value 
-  **ifPresent**(Consumer\<T> block)
	– executes the given code if a value is present. 
- T **get**()
	– returns the value if present; otherwise it throws a NoSuchElementException. 
- T **orElse**(T default) 
	– returns the value if present; otherwise it returns a default value. 
- T **orElse**(Supplier\<T> s) 
	– when empty return the value supplied by s

Creation uses static factory methods: 
- **of**(T v): 
	– throw exception if v is null 
- **ofNullable**(T v):
	– returns an empty Optional when v is null 
- **empty**() 
	– returns an empty Optional 

>Such methods force the programmer to think about what he’s about to return.
### Algorithms
Static methods of java.util.Collections, work on List since it has the concept of position 
- **sort**() - merge sort of List, n log(n) 
- **binarySearch**() – requires ordered sequence 
- **shuffle**() – unsort 
- **reverse**() - requires ordered sequence 
- **rotate**() – of given a distance 
- **min**(), **max**() – in a Collection
##### Search
\<T> int **binarySearch**(List<\? extends Comparable<\? super T>> l, T key) 
- Searches the specified object 
- List must be sorted into ascending order according to natural ordering 

\<T> int **binarySearch**(List<\? super T> l, T key, Comparable<\? super T> c)
- Searches the specified object 
- List must be sorted into ascending order according to the specified comparator
