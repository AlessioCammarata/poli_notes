#include <stdio.h>

int sequenza(FILE *file){
    int num, prev, count = 1, max_count = 1;
    
    if (fscanf(file, "%d", &prev) != 1) {
        return 0; // File vuoto o errore di lettura
    }

    while (fscanf(file, "%d", &num) == 1) {
        // printf("%d %d ",prev,num);
        if (num == prev) {
            count++;
        } else {
            if (count > max_count) {
                max_count = count;
            }
            count = 1; // Reset della sequenza
        }
        prev = num;
    }

    if (count > max_count) { // Verifica dell'ultima sequenza
        max_count = count;
    }

    return max_count;
}

int main(void){
    int seq;
    FILE *file;

    if ((file = fopen("./sorgente.txt", "r")) == NULL) {
		printf("Error opening file\n");
		return 1;
	}

    seq = sequenza(file);
    printf("La lunghezza massima è %d",seq);

    fclose(file);
    return 0;
}

