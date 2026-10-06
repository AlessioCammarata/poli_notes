package packages;

import java.nio.charset.Charset;

public class Scribe {

    //Attributes

    private String name;

    //Constructor

    public Scribe(String name){
        this.name = name;
    }

    //Getters and setters

    public void setName(String name){
        this.name = name;
    }

    public String getName(){
        return this.name;
    }

    //Character analysis
    public String analyseCharacter(Character character){
        if(Character.isDigit(character)){
            return "Digit";
        }

        return "I don't know";
    }

    //Encoding revelation

    public void revealEncoding(){
        IO.println("My default encoding is " + Charset.defaultCharset());
        IO.println("I can use also:");
        int i = 1;
        for(String str : Charset.availableCharsets().keySet()) {
            IO.println(" "+ i + " "+str);
            i++;
        }
    }

    //Measuring words

    

    public int measureLength(String word){
        return word.length();
    }

    //Word combination

    public String combineWords(String firstWord, String secondWord){
        return firstWord + " " + secondWord;
        // return firstWord.concat(secondWord); //Without space though
    }

    //Word comparison
    public Boolean wordComparison(String firstWord, String secondWord){
        if(firstWord.compareTo(secondWord) == 0)
            return true;
        return false;
    }

    //Scribing race

    public void scribingRace(int size){

        String base = "";
        StringBuffer sbuf = new StringBuffer();
        StringBuilder sbuild = new StringBuilder();

        long PreString = System.nanoTime();
        for(int i = 0; i<size; ++i){
            base = base + i;
        }
        long AfterString = System.nanoTime();
        IO.println(AfterString-PreString);

        PreString = System.nanoTime();
        for(int i = 0; i<size; ++i){
            sbuf.append(i);
        }
        AfterString = System.nanoTime();
        IO.println(AfterString-PreString);

        PreString = System.nanoTime();
        for(int i = 0; i<size; ++i){
            sbuild.append(i);
        }
        AfterString = System.nanoTime();
        IO.println(AfterString-PreString);
        
    }

    
    

}
