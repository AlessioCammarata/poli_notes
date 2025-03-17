#include <stdio.h>

float calcola_media(char *value, FILE *file) {
    char t[3];  // Serve almeno 3 caratteri per "T1\0" o "T2\0"
    int num, sum = 0, n = 0;

    // printf("Sono dentro la funzione\n");

    while (fscanf(file, "%2s", t) == 1) {  // Legge i primi due caratteri
        if (t[0] != value[0] || t[1] != value[1]) continue;  // Confronta "T1" o "T2"

        // Salta i due punti ":" dopo "T1:" o "T2:"
        char c;
        while ((c = fgetc(file)) != EOF && c != ':');

        // Legge numeri finché non trova ',' o EOF
        while (fscanf(file, "%d", &num) == 1) {
            sum += num;
            n++;
        }

        // Se trova una virgola, consuma il carattere
        if ((c = fgetc(file)) == ',') {
            fgetc(file); // Salta lo spazio dopo la virgola
        }
    }

    // printf("Somma: %d, Numero di elementi: %d\n", sum, n);

    return (n == 0) ? 0 : (float) sum / n;
}

int main(void){
    FILE *file;

    
    if ((file = fopen("C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione3/temperatura/temperatura.txt", "r")) == NULL) {
		printf("Error opening file\n");
		return 1;
	}
    // printf("Sto andando a calcolare");
    float tm1 = calcola_media("T1",file);
    rewind(file);
    float tm2 = calcola_media("T2",file);

    printf("media T1: %.1f",tm1);
    printf("media T2: %.1f",tm2);
    // print(media)
    fclose(file);
    return 0;

}