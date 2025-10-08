#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);
int control_letter(char *letter, int n, char l);

#define MAX_LEN 100

int main() {
    char str[MAX_LEN], regexp[MAX_LEN], *p = regexp;

    printf("Inserire la stringa da analizzare:\n");
    if (fgets(str, MAX_LEN, stdin) == NULL) {
        printf("Errore nella lettura dell'input.\n");
        return 1;
    }

    printf("Inserire l'espressione regolare:\n");
    scanf("%s",regexp);

    p = cercaRegexp(str,regexp);
    if( p != NULL) printf("%s",p);


    return 0;
}

int control_letter(char *letters, int n, char l){
    /**
     control_letter - Controlla se un carattere è presente in un array di lettere
     @letters: array di lettere da confrontare
     @n: numero di lettere valide nell'array
     @l: carattere da cercare
     
     Restituisce 1 se il carattere l è presente nell'array letters[0..n-1],
     altrimenti restituisce 0.
    */
    for(int i = 0; i<n; i++) 
        if (letters[i] == l)
            return 1;

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    /**
     cercaRegexp - Cerca la prima occorrenza di una regexp in una stringa
     @src: stringa sorgente in cui cercare
     @regexp: espressione regolare
    
     Implementa la ricerca carattere per carattere, gestendo i metacaratteri:
       .      -> qualsiasi lettera
       [abc]  -> una lettera tra quelle indicate
       [^abc] -> una lettera non tra quelle indicate
       \a     -> lettera minuscola
       \A     -> lettera maiuscola
    
     La funzione restituisce un puntatore alla prima occorrenza della regexp
     nella stringa src, o NULL se non viene trovata alcuna corrispondenza.
    
     La ricerca considera solo lettere alfabetiche e parole delimitate da spazio o newline(\n).
 */
    int c = 0, i = 0, nc;
    char char1, letters[52];

    while (sscanf(src+c,"%c", &char1) == 1) {
        if(char1 == regexp[i]){
            i++;
        }else{

            switch(regexp[i]){
                case '.':
                    if (isalpha(char1) != 0) i++;
                    else i = 0;
                    break;
                case '[':
                    nc = 0;

                    if(regexp[i+1] == '^'){ //Negazione
                        while (isalpha(regexp[i+nc+2]) != 0) letters[nc++] = regexp[i+nc+2];

                        if (control_letter(letters, nc, char1) == 0) i++;
                        else i = 0;
                    }else{ // positivo
                        while (isalpha(regexp[i+nc+1]) != 0) letters[nc++] = regexp[i+nc+1];

                        if (control_letter(letters, nc, char1) == 1) i++;
                        else i = 0;
                    }
                    break;
                case '\\':
                    // if(islower(regexp[i+1]) && islower(char1)){ // minuscolo
                    if(regexp[i+1] == 'a' && islower(char1)){
                        i+=2;
                    // }else if(isupper(regexp[i+1]) && isupper(char1)){ // maiuscolo
                    }else if(regexp[i+1] == 'A' && isupper(char1)){ // maiuscolo
                        i+=2;
                    }else{
                        printf("Errore nella battitura della regex\n");
                        i = 0;
                    }
                    break;
                default:
                    printf("Carattere non identificato: %c, %d\n",char1,i);
                    i = 0;
                }
        }
        // printf("%d %d %d\n",src[c+1] == ' ', src[c+1] == '\0',i);
        c++;
        // se la parola finisce (spazio o newline) e la regexp è stata matchata
        if((src[c] == ' ' || src[c] == '\n') && i!=0)  return src + c - i + 1;
    }

    return NULL;
}

