//VERSIONE CHE CONSIDERA GLI APOSTROFI
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define nfin "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione7/occorrenze_parole/sequenze.txt"
#define nfin1 "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione7/occorrenze_parole/testo.txt"
// #define nfin "./sequenze.txt"
// #define nfin1 "./testo.txt"
#define maxRIGA 200
#define maxWORD 25
#define maxNseq 20
#define maxSEQ 5
#define maxOCC 10

#define outputS 1000


void leggiFile(FILE *fin, char seq[][maxSEQ]);
// void leggiTesto(FILE *fin, char text[][maxWORD]);

int cercaParola(FILE *fin, char word[maxSEQ], char output[outputS]);

int main(void){
    FILE *fin,*fin1;
    int n;

    if((fin = fopen(nfin,"r")) == NULL || (fin1 = fopen(nfin1,"r")) == NULL){
        printf("Errore nell'apertura di uno dei due file\n");
        return 1;
    }

    fscanf(fin,"%d",&n);
    if(n>maxNseq) n=maxNseq;
    char seq[n][maxSEQ], output[outputS] = "";
    int find = 0;

    leggiFile(fin, seq);

    for(int i=0; i<n; i++){
        printf("--------------------------------------\n");
        printf("Analizzando %s\n\n",seq[i]);
        find = cercaParola(fin1,seq[i],output);
        rewind(fin1);
        if(!find) printf("Sequenza non trovata");
        else printf("%s",output);

        printf("\n");
    }

    fclose(fin);
    fclose(fin1);
    return 0;
}

void leggiFile(FILE *fin, char seq[][maxSEQ]){
    int i=0;
    while(fscanf(fin,"%s",seq[i]) == 1){
        i++;
    }
}

int cercaParola(FILE *fin, char word[maxSEQ], char output[outputS]){

    int f=0,Nword=0,len_seq=strlen(word);
    char riga[maxRIGA + 1];
    output[0] = '\0'; // resettiamo l'output

    sprintf(output, "La sequenza %s è contenuta in: ", word);

    // Leggo il file dall'inizio alla fine
    while (fgets(riga, sizeof(riga), fin) != NULL) {
        // printf("%s -- %s _%d\n",word,act_word,i); //DEBUG
        int row_len = strlen(riga),match = 0,i=0;
        char act_word[maxWORD] = "";

        while(riga[i] != '\0'){
            // Salta finché non troviamo un carattere alfanumerico
            while (riga[i] != '\0' && !isalnum(riga[i])) i++;

            // Inizio di una parola
            int j = 0;
            while (riga[i] != '\0' && isalnum(riga[i]) && j < maxWORD) {
                act_word[j++] = riga[i++];
            }
            act_word[j] = '\0';

            //Se ho una parola, incremento il numero di parole
            if(j>0){
                Nword++;

                // Confronta la parola corrente con la sequenza (case-insensitive)
                for (int k = 0; act_word[k]; k++) act_word[k] = tolower(act_word[k]);

                char lower_seq[maxSEQ + 1];
                for (int k = 0; k < len_seq; k++) lower_seq[k] = tolower(word[k]);
                lower_seq[len_seq] = '\0';

                //La funzione strstr() in C serve a cercare una sottostringa all'interno di una stringa.
                if (strstr(act_word, lower_seq) != NULL) {
                    char temp[100];
                    sprintf(temp, "\n- %s (posizione %d)", act_word, Nword);
                    strcat(output, temp);
                    f++;
                    if (f >= 10) return f;
                }
            }
        }
        
    }

    return f;
}   
