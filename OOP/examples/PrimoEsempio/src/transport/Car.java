package transport;

public class Car { // Name
	private String color = "blue"; // Attribute
	private String brand; // Attribute
	private boolean turnedOn; // Attribute -> Standard to false
	int fuelLevel;
    Mechanic myMechanic;

    enum fuelState {EMPTY, LOW, HALF, FULL}
    //Final -> Cannot be modified
    //Static -> It belong to the class
    private final static int MAX_FUEL=10; // Constant definition

    public void setMyMechanic(String mName){
        this.myMechanic = new Mechanic(mName);
    }

    public String sendToRepair(){
        return this.myMechanic.repair(this);
    }

    public void fillFuelLevel(){
        if(fuelLevel < MAX_FUEL)
            fuelLevel = MAX_FUEL;
    }

    public void fillFuelLevel(int recharge){
        if(fuelLevel + recharge <= MAX_FUEL)
            fuelLevel += recharge;
        else
            fuelLevel = MAX_FUEL;
    }

    public void fillFuelLevel(Car c){
        if(c.getFuelState() == fuelState.EMPTY){
            IO.println("This guy is poorer than you :/");
            return;
        }
        int stolenFuel = c.fuelLevel;
        c.fuelLevel = 0;
        fillFuelLevel(stolenFuel);
    }


    public fuelState getFuelState(){
        if(fuelLevel <= 0) return fuelState.EMPTY;
        if(fuelLevel <= 3) return fuelState.LOW;
        if(fuelLevel <= 7) return fuelState.HALF;
        
        return fuelState.FULL;
    }

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
    public void setBrand(String brand){
        this.brand = brand;
    } 

	public void turnOn() { 
		turnedOn = true; 
	} 
    public void turnOff() { 
		turnedOn = false; 
	} 
	public void paint (String newCol) { 
		color = newCol; 
	} 

    //getter
    public String getColor(){
        return color;
    }
    public String getBrand(){
        return brand;
    }
	public boolean isOn(){ 
		return turnedOn; 
	} 

	public void printState () { 
		IO.println("Car " + brand + " " + color); 
		IO.println("the engine is" +(turnedOn?" on " : " off ")); 
	} 
}