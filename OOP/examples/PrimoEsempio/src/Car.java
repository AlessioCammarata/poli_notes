public class Car { // Name
	private String color = "blue"; // Attribute
	private String brand; // Attribute
	private boolean turnedOn; // Attribute -> Standard to false
	
    public Car(String color, String brand){ //Constructor
        this.color = color;
        this.brand = brand;
    }

    // Overloading
    public Car(String color){
        this.color = color;
    }

    //Not possible because Java Interpreter can't know what you do whit the string, and so it's equal to the above one
    // public Car(String brand){
    //     this.brand = brand;
    // }

	// Methods

    //setter
    void setBrand(String brand){
        this.brand = brand;
    } 

	void turnOn() { 
		turnedOn = true; 
	} 
    void turnOff() { 
		turnedOn = false; 
	} 
	void paint (String newCol) { 
		color = newCol; 
	} 

    //getter
    String getColor(){
        return color;
    }
    String getBrand(){
        return brand;
    }
	boolean isOn(){ 
		return turnedOn; 
	} 

	void printState () { 
		IO.println("Car " + brand + " " + color); 
		IO.println("the engine is" +(turnedOn?" on " : " off ")); 
	} 
}