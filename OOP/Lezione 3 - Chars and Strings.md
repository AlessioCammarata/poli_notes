>Characters
- Primitive type **char**
- Wrapper class Character
>String
- No primitive representation
- Class **String**
- Class **StringBuffer** and **StringBuilder**
---
#### Wrapper 'Character'
Encapsulates a single character 
- **Immutable** (like all wrapper classes) 
Utility methods for the char category
- isLetter()
- isDigit() 
- isSpaceChar() 
Utility methods for conversions 
- toUpperCase() 
- toLowerCase()
---
#### Charset
Class **Charset** allows handling different charsets.
A few static methods 
 - defaultCharset() 
 - forName(..) − Returns the corresponding charset 
 - availableCharsets() − Returns a map of all charsets by name
---
#### Encoding and Decoding
>**Encoding mismatch**: Using an encoding scheme to decode a string encoded with a different scheme
---
#### Strings
```java
String s = new String("literal"); 
StringBuffer sb = new StringBuffer("lit");
```
##### Operator **+**
It is used to concatenate 2 strings
	"This is " + "a concatenation"
>Remember: strings are immutable, therefore + creates a new string object with the concatenation

Works also with other types.
Everything is **automatically converted to a string representation** and **concatenated**:
```java
System.out.println("pi = " + 3.14); 
System.out.println("x = " + x);
```
##### Methods
###### int Length()
Returns string length
```java
int len = h.length();
```
###### boolean equals(String s)
Compares contents of two strings
```java
String h = "Hello"; 
String w = "World"; 
String hw = "Hello World"; 
String h_w = h + " " + w; 
hw.equals(h_w) // -> true, same content
hw == h_w // -> false, two different reference
```
###### toUpperCase()
Converts string to  upper case
###### String toLowerCase() 
Converts string to lower case 
###### String concat(String str) 
Creates a concatenation with the given string 
###### int compareTo(String str) 
Compare to another string returning 
- < 0 : if this string precedes the other 
- == 0 : if this string equals the other 
- 0 : if this string follows the other
###### String subString(args)
```java
"Human".subString(2) → "man" //-> String subString(int startIndex)

"Greatest".subString(0,5) →"Great" // String subString(int start,int end)
```
###### int indexOf(String str)
Returns the index of the first occurrence of str
###### int lastIndexOf(String str)
The same as before but search starts from the end
###### String valueOf(..) 
Converts any primitive type into a String. 
Overloads defined for all primitive types.
###### String format(String fmt, …)
- Static method 
- Builds a string using the format string 
>Ex. answer = String.format("%d",42);
###### String formatted(...)
Builds format in the string it is called
>Ex. answer = "%d".formatted(42);
---
#### StringBuffer
Represents a string of characters.
It is mutable and allows operation that modify the content.
Can be converted to the corresponding **String** using the method **toString()**.

- **append**(String str) 
  Inserts **str** at the end of string 

- **insert**(int offset, String str) 
  Inserts **str** starting from offset position 

- **delete**(int start, int end) 
   Deletes character from **start to end** (excluded) 

- **reverse()** 
  Reverses the sequence of characters

>They all return a StringBuffer enabling chaining.
---
#### StringBuilder
Method-level compatible with StringBuffer.
Non thread safe and non reentrant.
More efficient: ~30% faster
```java
//Example with N = 100k
// 2 sec
String s=""; 
for(i=0;i<N; ++i){
	s += 1;
}

// 2.9 ms
StringBuffer sb = new StringBuffer(); 
for(i=0;i<N; ++i){
	sb.append(i);
}

// 2.2 ms
StringBuilder sb = new StringBuilder(); 
for(i=0;i<N; ++i){
	sb.append(i);
} 
```
---
