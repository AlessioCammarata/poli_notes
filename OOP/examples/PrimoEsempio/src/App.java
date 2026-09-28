import transport.Car;
// import transport.Mechanic;

public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");

        Car c1 = new Car("Blue","Audi");
        Car c2 = new Car("Pink", "SchifoFiat");

        c2.fillFuelLevel();
        c1.paint("Red");
        c1.printState();

        c1.fillFuelLevel(3);

        IO.println(c2.getFuelState());
        c1.fillFuelLevel(c2);
        IO.println("Benzina dell'"+ c1.getBrand() +": "+ c1.getFuelState() + "\nMentre la "+ c2.getBrand() + ": " + c2.getFuelState());
        

        // Mechanic m1 = new Mechanic("Mattew"); if public mechanic
        // IO.println(m1.repair(c2));

        c1.setMyMechanic("Matthew");
        IO.println(c1.sendToRepair());

        //Wrapper type
        Integer number = new Integer(10); //Deprecated
        Integer number1 = 10; //Autoboxing

        int nonWrapper = number.intValue(); //Primitive corrisponding, deprecated
        int nonWrapper1 = number;

        //Conversion among types
        String word = "121.1";
        Float decimal = Float.valueOf(nonWrapper1);

        //Arrays
        int size = 5;
        int [] numbers = new int[size];
        IO.println(numbers); //Print the reference
        IO.println(numbers[0]); //Print the firts element of the array

        for (int j = 0; j<numbers.length; j++){
            IO.print(numbers[j]);
            numbers[j] = j;
        }
        for (int n : numbers){ //You can only read with this, it's making a copy of the elements
            IO.print(n);
        }
        IO.println();

        //Example with cars
        Car [] cars = new Car[2];
        cars[0] = c1;
        cars[1] = c2;
        for(Car tempCar : cars){
            tempCar = c1;
            IO.println(tempCar.getBrand());
        }
        cars[1].printState();


        //Matrix
        int [][] binaryMatrix = new int [2][5];

        for(int [] row : binaryMatrix){
            for(int e: row){
                IO.print(e);
            }
            IO.println();
        }

        //Switch rows -> I'm switching the references
        // int [] temp = binaryMatrix[1];
        // binaryMatrix[1] = binaryMatrix[0];
        // binaryMatrix[0] = temp;

    }
}
