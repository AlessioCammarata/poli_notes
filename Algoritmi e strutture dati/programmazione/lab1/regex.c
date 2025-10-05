#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    for(int i = 0; i<n; i++) 
        if (letters[i] == l)
            return 1;

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    char word[MAX_LEN], let, letters[52];
    int n, bef=0, nc = 0;

    while(isalpha(*(regexp++))) bef++;

    printf("%c\n",*regexp);
    switch(*(regexp-1)){
        case '.':
            while (sscanf(src,"%s%n", word, &n) == 1) {
                if (strncmp(word, regexp-bef, bef) == 0 && strncmp(word + bef + 1, regexp+1, n - bef - 1) == 0) return src;
                src+=n;
            }
            break;
        case '[':
            if(*(regexp+1) == '^'){
                // Incremento il numero di (oc)currences, e inserisco i valori delle stesse in un vettore
                while (isalpha(*(regexp + nc + 2)) != 0) letters[nc++] = *(regexp + nc + 2);
                
                //Controllo in modo da prendere le parole che non contengano le lettere
                while (sscanf(src,"%s%n", word, &n) == 1) {
                    if (strncmp(word, regexp-bef, bef) == 0 && control_letter(letters,nc,*(word+bef)) == 0 && strncmp(word + bef + 1, regexp+nc+3, n - bef - 1) == 0) return src;
                    src+=n;
                }
            }else{
                // Incremento il numero di (oc)currences, e inserisco i valori delle stesse in un vettore
                while (isalpha(*(regexp + nc + 1)) != 0) letters[nc++] = *(regexp + nc + 1); 

                //Controllo il resto sapendo cio che cerco
                while (sscanf(src,"%s%n", word, &n) == 1) {
                    if (strncmp(word, regexp-bef, bef) == 0 && control_letter(letters,nc,*(word+bef)) != 0 && strncmp(word + bef + 1, regexp+nc+2, n - bef - 1) == 0) return src;
                    src+=n;
                }
            }
            break;
        case '\\':
            if(islower(*(regexp+1)) != 0){
                while (sscanf(src,"%s%n", word, &n) == 1) {
                    if (strncmp(word, regexp-bef, bef) == 0 && islower(*(word+bef)) != 0 && strncmp(word + bef + 1, regexp+2, n - bef - 1) == 0) return src;
                    src+=n;
                }

            }else{
                while (sscanf(src,"%s%n", word, &n) == 1) {
                    if (strncmp(word, regexp-bef, bef) == 0 && isupper(*(word+bef)) != 0 && strncmp(word + bef + 1, regexp+2, n - bef - 1) == 0) return src;
                    src+=n;
                }
            }
            break;
        default:
            printf("Errore nella battitura della regexp\n");
    }
    
    return NULL;
}

