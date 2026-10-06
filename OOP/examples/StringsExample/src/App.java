import packages.Scribe;

public class App {

    
    public static void main(String[] args) {
        Scribe scribe = new Scribe("Matteo");
        
        IO.println(scribe.analyseCharacter('l'));

        // scribe.revealEncoding();

        IO.println(scribe.measureLength("null"));
        IO.println(scribe.combineWords("Marco", "Carta"));
        IO.println(scribe.wordComparison("Marco", "Luca") ? "Sono uguali" : "Sono diverse");
        IO.println(scribe.wordComparison("Marco", "Marco") ? "Sono uguali" : "Sono diverse");

        scribe.scribingRace(100000);

    }
    
}