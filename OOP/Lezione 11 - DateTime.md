##### System timestamps
System class provides two methods: 
- **currentTimeMillis**() 
	- the difference, measured in milliseconds, between the current time and midnight, January 1, 1970 UTC 
- **nanoTime()** 
	- current value of the running JVM's highresolution time source, in nanosecond  There is no absolute reference
---
>Date is deprecated
---
##### Calendar
Abstract class, with one concrete implementation: **GregorianCalendar** 
Represents a date with fields 
	-YEAR, MONTH, DAY_OF_MONTH, HOUR… 

Can be manipulate 
- get(field) 
- set(field, value) 
- add(field, delta)
---
### Date and Time
All classes are immutable.
	Package java.time

**Temporal points** 
- Instant 
- LocalDate 
- LocalDateTime 
- LocalTime 
- ZonedDateTime 

**Temporal intervals** 
- Duration (time based) 
- Period (date based)
#### Temporal points factory methods

| Method  | Purpose                                                                          |
| ------- | -------------------------------------------------------------------------------- |
| **of()**    | Create instance from a set of specific parameters, with validation               |
| **from()**  | Convert from another class with possible loss of information                     |
| **parse()** | Parse a string to build an instance                                              |
| **now()**   | Create an instance representing the current time / date. Can accept a **ZoneId** |
##### Comparison
| **Method**      | Purpose                                                         |
| ----------- | --------------------------------------------------------------- |
| **isBefore()**  | Checks if this time/date is before the specified time/date      |
| **isAfter()**   | Checks if this time/date is after the specified time/date       |
| **isEqual()**   | Checks if this time/date is the same as the specified time/date |
| **compareTo()** | Compares to to other time/date                                  |
##### Changing
| Method      | Purpose                                                                  |
| ----------- | ------------------------------------------------------------------------ |
| **minus()** | Returns a new date/time built by removing a specific amount of date/time |
| **plus()**  | Returns a new date/time built by adding a specific amount of date/time   |
| **with()**  | Returns a new date/time modified as specified by a temporal adjuster     |
###### Plus / Minus
Plus/Minus work with:
- Amount of temporal unit 
	- long amountToSubtract, 
	- **TemporalUnit** unit 
		- E.g. ChronoUnit.DAYS 
- Temporal amount 
	- **TemporalAmount** amount 
		- Either a Duration or a Period
#### Temporal adjusters
Factory methods in class **TemporalAdjusters**, e.g. 
- firstDayOfMonth() 
- firstDayOfNextMonth() 
- firstInMonth(DayOfWeek dayOfWeek) 
- lastDayOfMonth() 
- … 
>Can be used as arguments to with().
##### DoW and Month
Are represented by enums: 
- **DayOfWeek** 
- **Month** 
Can be converted to string 
- **getDisplayName**(style,locale) 
- style is one of 
	- TextStyle.FULL 
	- TextStyle.NARROW 
	- TextStyle.SHORT
```java
LocalDate today = LocalDate.now(); // 2026-11-26
LocalDate tomorrow = today.plus(1,ChronoUnit.DAYS); // 2026-11-27
LocalDate inTwoWeeks = today.plusDays(14); // 2026-12-10
LocalDate firstMon = today
				.with(TemporalAdjusters 
					.firstInMonth(DayOfWeek.MONDAY)); // 2026-11-02
```
##### Locale
Class Locale represents a specific geographical, political, or cultural region.
Used to perform locale-sensitive operations
- Date formats 
- DoW, Month names 
- Decimal separators

---
##### DateTime String Format

1970-01-01T00:00:00Z
>Year|Month|DayTHour:Minute:SecondsZ
---
#### Time Intervals factory methods
| Method        | Purpose                                                                               |
| ------------- | ------------------------------------------------------------------------------------- |
| **of()**      | Creates interval from specified amount of **TemporalUnits**                           |
| **ofXxxx()**  | Creates interval from specified amount of units (Xxxx is : **Days**, **Hours**, etc.) |
| **between()** | Creates interval between two temporal points                                          |
```java
Instant start = Instant.now(); 
//… 
Instant end = Instant.now(); 
Duration elapsed = Duration.between(start, end); 
System.out.println(elapsed);
// PT2.005S
//PT is Period of Time
```
---
### Testing
Testing code that is time dependent can be difficult.
For this purpose, there is class **Clock** 
- Can be used as argument of now()
It represent an alternate time and date.

Clocks can be created with factory methods: 
- **fixed**(instant, zone) 
- **offset**(base, offset) 
- **systemDefaultZone**() 
- **systemUTC**()

Examples:
```java
static double totalDue(double amount, LocalDate begin, double monthlyRate){ 
	LocalDate today = LocalDate.now(); // Depends on time of test execution
	Period interval = Period. between(begin, today); 
	int months = interval.getMonths(); 
	double compoundRate = Math.pow(1.0+monthlyRate, months); 
	return amount*compoundRate; 
}
```
>To test this function:
```java
static double totalDue(double amount, LocalDate begin, double monthlyRate, Clock clock){ 
	LocalDate today = LocalDate.now(clock); 
	Period interval = Period. between(begin, today); 
	int months = interval.getMonths(); 
	double compoundRate = Math.pow(1.0+monthlyRate, months); 
	return amount*compoundRate; 
}


//TEST
@Test 
public static void testTotalDue(){ 
	LocalDate begin = LocalDate.of(2025,4,10); 
	LocalDate in4 = begin.plusMonths(4); // Date of 4 months from begin
	ZoneId zone = ZoneId.systemDefault(); // Get the time zone
	Clock clock = Clock.fixed(in4 
					.atStartOfDay(zone).toInstant(),zone); 
	//We have initialized the clock to an instant of 4 months starting from begin
	double r = 0.01; 
	int amount = 1000; 
	double t = totalDue(amount, begin, r, clock); //We pass the clock
	assertEquals(amount*Math.pow(1+r, 4), t, 1); 
}
```