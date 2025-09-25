#include <stdio.h>
#include <stdlib.h>

int main(void) {

    char file_char,line[50],op = ' ';
    FILE *fp_read, *fp_write;
    float val1 = 0, val2 = 0, result = 0;

    // Apertura file
    if ((fp_read = fopen("./Operations.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    if ((fp_write = fopen("./Results.txt", "w")) == NULL) {
        printf("Errore nell'apertura del file\n");
        fclose(fp_read);
        return 2;
    }

    // Lettura riga per riga
    while (fgets(line, sizeof(line), fp_read) != NULL) {
        // Estrae i dati dalla riga (es: "12 + 5")
        if (sscanf(line, "%c %f %f", &op, &val1, &val2) != 3) {
            fprintf(fp_write, "Errore: formato non valido\n");
            continue;  // Salta al prossimo calcolo
        }

        switch (op) {
            case '+': 
                result = val1 + val2; break;
            case '-': 
                result = val1 - val2; break;
            case '*': 
                result = val1 * val2; break;
            case '/': 
                if (val2 != 0)
                    result = val1 / val2;
                else {
                    fprintf(fp_write, "Errore: divisione per zero\n");
                    continue;  // Evita di scrivere un risultato errato
                }
                break;
            default:
                fprintf(fp_write, "Errore: operazione non valida\n");
                continue;
        }

        // Scrivi il risultato nel file
        // fprintf(fp_write, "%.2f %c %.2f = %.2f\n", val1, op, val2, result);
        fprintf(fp_write, "%c %.2f\n", op, result);
    }
    

    // Chiude i file
    fclose(fp_read);
    fclose(fp_write);

    return 0;
}
