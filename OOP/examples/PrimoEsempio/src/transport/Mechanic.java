package transport;

class Mechanic {
    private String name;

    public Mechanic(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String repair(Car c){
        return "Mechanic "+ this.name + " is mech-ing with "+ c.getBrand();
    }
}
