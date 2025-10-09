#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);
int calcolaLunghezzaRegex(char *regexp);
int verificaRegex(char *word, char *regexp);
int control_letter(char *letters, int n, char l);

int main() {
    char *str = NULL; // Puntatore per la stringa allocata dinamicamente
    char *regexp = NULL; // Puntatore per la regex allocata dinamicamente
    size_t size_str = 16, size_regexp = 16; // Dimensioni iniziali arbitrarie
    char *result;

    // Allocazione iniziale per la stringa
    str = (char *)malloc(size_str * sizeof(char));
    if (!str) {
        printf("Errore di allocazione memoria per la stringa.\n");
        return 1;
    }

    printf("Inserire la stringa da analizzare:\n");
    int c, len_str = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len_str >= size_str - 1) {
            size_str *= 2; // Raddoppia la dimensione per farlo il meno possibile nel tempo
            str = (char *)realloc(str, size_str * sizeof(char));
            if (!str) {
                printf("Errore di realloc per la stringa.\n");
                free(str);
                return 1;
            }
        }
        str[len_str++] = (char)c;
    }
    str[len_str] = '\0'; // Termina la stringa

    printf("Inserire l'espressione regolare:\n");

    // Allocazione iniziale per la regex
    regexp = (char *)malloc(size_regexp * sizeof(char));
    if (!regexp) {
        printf("Errore di allocazione memoria per la regex.\n");
        free(str);
        return 1;
    }

    // Lettura dinamica della regex
    int len_regexp = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len_regexp >= size_regexp - 1) {
            size_regexp *= 2; // Raddoppia la dimensione
            regexp = (char *)realloc(regexp, size_regexp * sizeof(char));
            if (!regexp) {
                printf("Errore di realloc per la regex.\n");
                free(regexp);
                free(str);
                return 1;
            }
        }
        regexp[len_regexp++] = (char)c;
    }
    regexp[len_regexp] = '\0'; // Termina la regex

    result = cercaRegexp(str, regexp);
    if (result) {
        printf("Match trovato: %s\n", result);
    } else {
        printf("Nessun match trovato.\n");
    }

    free(str);    // Libera la memoria allocata per la stringa
    free(regexp); // Libera la memoria allocata per la regex
    return 0;
}

char *cercaRegexp(char *src, char *regexp) {
    char word[256]; // Buffer per la parola corrente
    int len_reg = calcolaLunghezzaRegex(regexp); // Calcola la lunghezza effettiva della regex
    int offset = 0, n;

    while (sscanf(src + offset, "%255s%n", word, &n) == 1) { // Leggi una parola alla volta
        if (strlen(word) == len_reg) { // Controlla la lunghezza della parola (non uso n perche si porta dietro anche gli spazi)
            if (verificaRegex(word, regexp)) { // Verifica se la parola rispetta la regex
                return src + offset; // Restituisci il puntatore alla posizione in src
            }
        }
        offset += n; // Avanza l'offset per la prossima parola
    }

    return NULL; // Nessuna corrispondenza trovata
}

int calcolaLunghezzaRegex(char *regexp) {
    int len = 0, i = 0;

    while (regexp[i]) {
        if (regexp[i] == '[') {
            // Salta i caratteri tra parentesi quadre
            while (regexp[i] && regexp[i] != ']') i++;
            len++; // Conta come un singolo carattere
        } else if (regexp[i] == '\\') {
            // Salta il metacarattere e il carattere successivo
            i++;
            len++;
        } else if (regexp[i] == '.') {
            len++; // Punto rappresenta un singolo carattere
        } else {
            len++; // Carattere normale
        }
        i++;
    }

    return len;
}

int verificaRegex(char *word, char *regexp) {
    int i = 0, j = 0, nc;
    char letters[52+1]; // Array per lettere tra parentesi quadre

    while (regexp[i] && word[j]) { //Finche una delle due non finisce
        if (regexp[i] == word[j]) {
            // Carattere normale: match
            i++;
            j++;
        } else {
            switch (regexp[i]) {
                case '.':
                    // Punto: matcha qualsiasi lettera
                    if (isalpha(word[j])) {
                        i++;
                        j++;
                    } else {
                        return 0;
                    }
                    break;
                case '[':
                    nc = 0;
                    if (regexp[i + 1] == '^') {
                        // Negazione: [^abc]
                        i += 2; // Salta [^
                        while (regexp[i] && regexp[i] != ']') letters[nc++] = regexp[i++];
                        if (!control_letter(letters, nc, word[j])) {
                            j++;
                        } else {
                            return 0;
                        }
                    } else {
                        // Positivo: [abc]
                        i++; // Salta [
                        while (regexp[i] && regexp[i] != ']') letters[nc++] = regexp[i++];
                        if (control_letter(letters, nc, word[j])) {
                            j++;
                        } else {
                            return 0;
                        }
                    }
                    i++; // Salta ]
                    break;
                case '\\':
                    // \a: minuscola, \A: maiuscola
                    if (regexp[i + 1] == 'a' && islower(word[j])) {
                        i += 2;
                        j++;
                    } else if (regexp[i + 1] == 'A' && isupper(word[j])) {
                        i += 2;
                        j++;
                    } else {
                        return 0;
                    }
                    break;
                default:
                    // Carattere/metacarattere non riconosciuto
                    return 0;
            }
        }
    }

    // Verifica che entrambi siano terminati
    return !regexp[i] && !word[j];
}

//Controlla se la lettera è nel letters
int control_letter(char *letters, int n, char l) {
    for (int i = 0; i < n; i++) {
        if (letters[i] == l) {
            return 1;
        }
    }
    return 0;
}
