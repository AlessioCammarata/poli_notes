#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *cercaRegexp(char *src, char *regexp);
int control_letter(char *letter, int n, char l);

#define INIT_SIZE 100

int main() {
    char *str = NULL, *regexp = NULL, *p = NULL;
    int size_str = INIT_SIZE, size_regexp = INIT_SIZE;
    int len = 0, c;

    // Allocazione iniziale per la stringa
    str = (char *)malloc(size_str * sizeof(char));
    if (!str) {
        printf("Errore di allocazione memoria.\n");
        return 1;
    }

    printf("Inserire la stringa da analizzare:\n");
    // Lettura dinamica della stringa
    len = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len >= size_str - 1) {
            size_str *= 2;
            str = (char *)realloc(str, size_str * sizeof(char));
            if (!str) {
                printf("Errore di realloc.\n");
                return 1;
            }
        }
        str[len++] = (char)c;
    }
    str[len] = '\0';

    // Allocazione iniziale per la regexp
    regexp = (char *)malloc(size_regexp * sizeof(char));
    if (!regexp) {
        printf("Errore di allocazione memoria.\n");
        free(str);
        return 1;
    }

    printf("Inserire l'espressione regolare:\n");
    len = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len >= size_regexp - 1) {
            size_regexp *= 2;
            regexp = (char *)realloc(regexp, size_regexp * sizeof(char));
            if (!regexp) {
                printf("Errore di realloc.\n");
                free(str);
                return 1;
            }
        }
        regexp[len++] = (char)c;
    }
    regexp[len] = '\0';

    // Cerca la regexp nella stringa
    p = cercaRegexp(str, regexp);
    if (p != NULL)
        printf("%s", p);

    // Libera la memoria allocata
    free(str);
    free(regexp);
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
     * cercaRegexp - Cerca la prima occorrenza di una regexp in una stringa
     * @src: stringa sorgente in cui cercare
     * @regexp: espressione regolare
     *
     * Implementa la ricerca carattere per carattere, gestendo i metacaratteri:
     *   .      -> qualsiasi lettera
     *   [abc]  -> una lettera tra quelle indicate
     *   [^abc] -> una lettera non tra quelle indicate
     *   \\a     -> lettera minuscola
     *   \\A     -> lettera maiuscola
     *
     * La funzione restituisce un puntatore all'inizio della prima parola che matcha la regexp
     * nella stringa src, o NULL se non viene trovata alcuna corrispondenza.
     *
     * La ricerca considera solo lettere alfabetiche e parole delimitate da spazio o newline (\n).
     */
    // Prova il match da ogni posizione della stringa sorgente
    int len_src = strlen(src);
    for (int start = 0; start < len_src; start++) {
        int i = 0; // indice regexp
        int j = start; // indice stringa
        int nc; // numero di caratteri tra parentesi quadre
        char letters[52];

        // Prova a matchare regexp da src[start]
        while (regexp[i] && src[j] && src[j] != ' ' && src[j] != '\n') {
            if (regexp[i] == src[j]) {
                // Carattere normale: match
                i++; j++;
            } else {
                switch (regexp[i]) {
                    case '.':
                        // Punto: matcha qualsiasi lettera
                        if (isalpha(src[j])) { 
                            i++; 
                            j++; 
                        } else goto next_start;
                        break;
                    case '[':
                        nc = 0;
                        if (regexp[i+1] == '^') {
                            // Negazione: [^abc]
                            while (isalpha(regexp[i+nc+2])) letters[nc++] = regexp[i+nc+2];
                            if (!control_letter(letters, nc, src[j])) { 
                                i += nc+3; 
                                j++; 
                            } else goto next_start;
                        } else {
                            // Positivo: [abc]
                            while (isalpha(regexp[i+nc+1])) letters[nc++] = regexp[i+nc+1];
                            if (control_letter(letters, nc, src[j])) { 
                                i += nc+2; 
                                j++; 
                            }else goto next_start;
                        }
                        break;
                    case '\\':
                        // \a: minuscola, \A: maiuscola
                        if (regexp[i+1] == 'a' && islower(src[j])) { 
                            i += 2; 
                            j++; 
                        } else if (regexp[i+1] == 'A' && isupper(src[j])) { 
                            i += 2; 
                            j++; 
                        }else goto next_start;

                        break;
                    default:
                        // Carattere/metacarattere non riconosciuto
                        goto next_start;
                }
            }
        }
        // Se la regexp è finita e la parola è finita (spazio, newline o fine stringa)
        if (!regexp[i] && (src[j] == ' ' || src[j] == '\n' || src[j] == '\0'))
            return src + start; // Puntatore all'inizio della parola trovata
        
        // Se il match fallisce, passa alla posizione successiva
        next_start:;
    }
    // Nessun match trovato
    return NULL;
}

