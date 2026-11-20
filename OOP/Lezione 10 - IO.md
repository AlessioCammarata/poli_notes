All I/O operations rely on the abstraction of **stream** (flow of elements).
>Nothing to deal Stream API.

An I/O stream can be linked to: 
- A file on the disk 
- Standard input, output, error 
- A network connection 
- A data-flow from/to different hardware devices 
I/O operations work in the same way with **all** stream from any source.
"Package: java.io"

Streams of **chars** (Unicode - 16 bit) 
- Reader / Writer − All characters 

Streams of **bytes** (8 bit) 
- InputStream / OutputStream − Binary data, e.g., sounds, images, videos 

>All related exceptions are subclasses of **IOException**.
##### Reader (abstract)
void close() 
	− Close the stream. 

int **read()** 
	− Read a single character: 
	− Returns -1 when end of stream

int read(char[] cbuf) 
	− Read characters into an array. 

int read(char[] cbuf, int off, int len) 
	− Read characters into a portion of an array.

boolean ready() 
	− Tell whether the stream is ready to be read. 

void reset() 
	− Reset the stream, restart from beginning 

long skip(long n) 
	− Skip n characters
###### Read a char
```java
int ch = r.read(); 
char unicode = (char) ch; 
System.out.print(unicode); 
r.close();
// ‘A’ -> 0…00000000 01000001bin = 65dec -> 65 in unicode
```

Examples:
```java
//Read a char
//hello.txt contains the word hello in different languages and ideographic
Reader reader = new FileReader("hello.txt");
int firstChar = reader.read();
IO.println(firstChar); 
// 67 -> since is the unicode of C
IO.println((char)firstChar);
// C
reader.close(); //Everytime close it
```

```java
//Read a file -> not efficient to read single character
//In IOUtils
public static String readLine(Reader reader) throws IOException{
	StringBuilder sb = new StringBuilder();
	int character = reader.read();
	//Check if the file is empty
	if(character == '\n'){
		return sb.toString();
	}
	while(character != -1){
		sb.append((char)character); // Every character is appended to the sb
		if(character == '\n'){
			return sb.toString();
		}
		character = reader.read();	
	}
	return null;
}

//In the main
//Read a line
Reader reader2 = new FileReader("hello.txt"); //Create a new reader
//OR
// reader.reset(); didn't work during lesson
String line = IOUtils.readLine(reader2);
while(line != null){
	IO.println(line);
	line = IOUtils.readLine(reader2);
}
//We read all the lines in the file
reader2.close();
```
---
##### Writer (abstract)
void **write**(int c) 
- Write a single character. 
void write(char\[] cbuf) 
- Write an array of characters. 
void write(char\[] cbuf, int off, int len) 
- Write a portion of an array of characters.
void write(String str) 
- Write a string. 
close() 
- Close the stream, flushing it first. 
abstract void flush() 
- Flush the stream.
###### Output buffers
Output streams typically write to a memory buffer
- Much faster than writing e.g. to file (leverage memory hierarchy) 
- When buffer is full a large chunk is written, as a whole, to the destination 

Program termination wipes buffers; Must explicitly ensure buffers are flushed using method close() or flush().

```java
// Write a string
Writer writer = new FileWriter("output.txt"); //Will create the file
writer.write("Hello"); //Doesn't write anything, it is placed in a buffer
writer.flush(); //To print stuff on the file
writer.close(); //Close does also the flush
```
---
##### InputStream
void close() 
- Closes this input stream and releases any system resources associated with the stream.
int read() 
- Reads the next byte of data from the input stream. 
int read(byte\[] b) 
- Reads some bytes from the input stream and stores them into the buffer array b. 
int read(byte\[] b, int off, int len) 
- Reads up to len bytes of data from the input stream into an array of bytes.
int available() 
- Number of bytes that can be read (or skipped over) from this input stream without blocking. 
void reset() 
- Repositions this stream to the position at the time the mark method was last called.
long skip(long n) 
- Skips over and discards n bytes of data from this input stream.

```java
//Reading bytes
InputStream fileInputStream = new FileInputStream("hello.txt");
int nextByte;

while((nextByte = fileInputStream.read()) != -1){
	IO.println(nextByte); // This is in bytes
	IO.println("%02X".formatted(nextByte)); //This format in exadecimal
}
fileInputStream.close();

// ISR
InputStream fileInputStream2 = new FileInputStream("output.txt");
InputStreamReader isr = new InputStreamReader(fileInputStream2, UTF_8);
IO.println(isr.read());
isr.close();
```
##### OutputStream
void write(byte[] b) 
- Writes b.length bytes from the specified byte array to this output stream. void 
write(byte[] b, int off, int len) 
- Writes len bytes from the specified byte array starting at offset off to this output stream. 
void write(int b) 
- Writes the specified byte to this output stream. 
void close() 
- Closes this output stream and releases any system resources associated with this stream. 
void flush() 
- Flushes this output stream and forces any buffered output bytes to be written out.
```java
//Writing bytes
OutputStreamReader fileByteWriter = new FileOutputStream("output.txt");
fileByteWriter.write(67); //This method has 3 overloads
fileByteWriter.write(100);
//Cd
```
---
##### Conversion byte <-> char
- InputStreamReader 
 char <- byte 
 - OutputStreamWriter 
 char → byte 
 
  >The constructors allow specifying a charset to decode/encode the byte to/from characters. 
---
### Stream specializations
- Memory 
- Pipe 
- File 
- Buffered 
- Printed 
- Interpreted
#### Read/Write in memory
- **CharArrayReader** 
- **CharArrayWriter** 
- **StringReader** 
- **StringWriter** 
	- R/W chars from/to array or String 
- **ByteArrayInputStream** 
- **ByteArrayOutputStream** 
	- R/W bytes from/to array in memory
#### R/W of Pipe
won't use
#### R/W of files
Used for reading/writing files
- **FileReader** 
- **FileWriter** 
	- R/W chars from file 
- **FileInputStream** 
- **FileOutputStream** 
	- R/W bytes from file
##### Copy text file
```java
Reader src = new FileReader(args[0]); 
Writer dest = new FileWriter(args[1]); 
int in; 
while( (in=src.read()) != -1){ // One char at a time is higly inefficient
	dest.write(in); 
} 
src.close(); dest.close();
```
With buffer:
```java
Reader src = new FileReader(args[0]); 
Writer dest = new FileWriter(args[1]); 
char[] buffer = new char[4096]; 
int n; 
while((n = src.read(buffer))!=-1){ // 10 times faster
	dest.write(buffer,0,n); 
} 
src.close(); dest.close();
```
---
#### Printed streams
**PrintStream**(OutputStream o) 
Provides general printing methods for all primitive types, String, and Object 
	− **print()** 
	− **println()** 

Designed to work with basic byteoriented console.
>Does not throw IOException, but it sets a bit, to be checked with method checkError()

##### Standard in & out
Default input and output streams are defined in class System
```java
class System { 
	//… 
	static InputStream in; 
	static PrintStream out; 
	static PrintStream err; 
}
```
---
#### Interpreted streams
Translate primitive types into / from standard format -> Typically on a file 

- **DataInputStream**(InputStream i) 
	- readByte(), readChar(), readDouble(), readFloat(), readInt(), readLong(), readShort(), 
- **DataOutputStream**(OutputStream o) 
	- like write()
---
### Stream as Resources
Streams consume OS resources.
Such resources are limited, a program can open only a given number of files at once.
Streams should be closed as soon as possible to release resources.

```java
String readFirstLine(String path) throws IOException { 
	BufferedReader br=new BufferedReader( new FileReader(path)); 
	try { 
		String l = br.readLine(); 
		br.close(); 
		return l; 
	} catch(IOException e){ 
		br.close(); // Complex and does not close in case of other Exceptions
		throw e; 
	} finally { //Better: Executed in any case before exiting the method
		if(br!=null) br.close(); 
	}
}
```

Try-with-resource
```java
String readFirstLine(String path) throws IOException { 
	try( // Works since BuffereReader implements Autocloseable
		BufferedReader br=new BufferedReader( 
			new FileReader(path)
		)
	){ 
		return br.readLine(); 
	} 
}
// More compact and readable form, equivalent to the one with finally
public interface AutoCloseable{ 
	public void close(); 
}
```
Example
```java
InputStream fileInputStream2 = new FileInputStream("output.txt");
InputStreamReader isr = new InputStreamReader(fileInputStream2, UTF_8);
IO.println(isr.read());
isr.close();

//Not riskink anything, the stream is closed
try{
	isr.read();
} catch (IOException ioe){
	IO.println(ioe.getMessage());
}

//2 example

// IOUtils
public static void diskFailure() throws IOException {
	throw new IOException("Oh no something went wrong");
}

//Main
try{
	Writer writer = new FileWriter("output.txt");
	writer.write("Hello"); 
	IOUtils.diskFailure(); //Throw an exception
	writer.close(); // The program doesn't execute since exception occurred
} catch (IOException ioe){
	IO.println(ioe.getMessage());
	writer.close();
} //Use finally would be better

// 3 example

try( Writer writer = new FileWriter("output.txt")){
	writer.write("Hello"); 
	IOUtils.diskFailure(); //Throw an exception
} catch (IOException ioe){ //You still need the catch
	IO.println(ioe.getMessage());
}
//This way it close anyway
```
---
### SERIALIZATION
Read / write of an object imply: 
- read/write attributes (and optionally the type) of the object 
- Correctly separating different elements 
- When reading, create an object and set all attributes values 

These operations (serialization) are automated by 
- **ObjectInputStream** 
- **ObjectOutputStream**

Methods to read/write objects are: 
- void writeObject(Object) 
- Object readObject()

>**ONLY** objects implementing interface **Serializable** can be serialized 
- This interface is empty 
- IT is a marker interface -> Just used to avoid serialization of objects, without permission of the class developer.

Example:
```java
//I have a class Bottle
Bottle implements Seriazable{
	String from;
	String hello;
	String message;
	
	public Bottle(String from. String hello, String message){

	}

	@override
}

//Serialization
Bottle bottle = new Bottle("Ana","Hola","coffee");
try(ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("bottle.dat"))){
	out.writeObject(bottle);
}

//To open the file with means
ObjectInputStream deserializer = new ObjectInputStream((new FileInputStream("bottle.dat"));

Object retrieved = deserializer.readObject(); //Safe cast
deserializer.close();
//This is a way to share objects using files, if you have the same class you can open and have the object on your system.

Bottle found = (Bottle) retrieved; //Downcast
if( retrieved instanceof Bottle bo){

}
```
##### For references?
Serialization is applied recursively to object in references.
Referenced objects must implement the Serializable interface.
Specific fields can be excluded from serialization by marking them as **transient**

An ObjectOutputStream saves all objects referred by its attributes 
- objects serialized are numbered in the stream 
- references are saved as ordering numbers in the stream 

If two saved objects point to a common one, this is saved just once 
- Before saving an object, ObjectOutputStream checks if it has not been already saved 
- Otherwise it saves just the reference
---
