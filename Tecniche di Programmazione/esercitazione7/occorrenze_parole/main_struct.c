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
#define maxSEQ 5+1
#define maxOCC 10

#define outputS 1000
#define MAX_parole 1000

typedef struct {
    char word[maxWORD];
} occurrency;

int leggiFile_seq(FILE *fin, char seq[][maxSEQ]);
int leggiFile_text(FILE *fin, occurrency occ[MAX_parole]);
// void leggiTesto(FILE *fin, char text[][maxWORD]);

int cercaParola(char word[maxSEQ], int n, occurrency occ[MAX_parole], char output[outputS]);

int main(void){
    FILE *fin,*fin1;
    int n;

    if((fin = fopen(nfin,"r")) == NULL || (fin1 = fopen(nfin1,"r")) == NULL){
        printf("Errore nell'apertura di uno dei due file\n");
        return 1;
    }

    // fscanf(fin,"%d",&n);
    char seq[maxNseq][maxSEQ], output[outputS] = "";
    occurrency occ[MAX_parole];
    int find = 0;

    n = leggiFile_seq(fin, seq); // Potrei otteneere il valore di n da qua ma vabbe
    if(n>maxNseq) n=maxNseq;

    int len_occ = leggiFile_text(fin1, occ);

    for(int i=1; i<n+1; i++){
        printf("--------------------------------------\n");
        printf("Analizzando %s\n\n",seq[i]);
        find = cercaParola(seq[i],len_occ,occ,output);

        if(!find) printf("Sequenza non trovata");
        else printf("%s",output);

        printf("\n");
    }

    fclose(fin);
    fclose(fin1);
    return 0;
}

int leggiFile_seq(FILE *fin, char seq[][maxSEQ]){
    int i = 0,n = 0;
    // for(int i = 0;fscanf(fin,"%s",seq[i]) == 1;i++); // Se fossero tutte minuscole andrebbe bene
    while (fgets(seq[i], sizeof(seq[i]), fin) != NULL) {
        int j = 0;
        
        if(i==0){
            sscanf(seq[i], "%d", &n);
        }else{
            while(seq[i][j] != '\n' && seq[i][j] != '\0'){
                // i-1 perchè c'è il vuoto lasciato dalla fscanf
                seq[i][j] = tolower(seq[i][j]);
                j++;
            }
            seq[i][j] = '\0';
        }
        i++;
        
    }

    return n;
}

int leggiFile_text(FILE *fin, occurrency occ[MAX_parole]){
    int Nword = 0;
    // for(i = 0; fscanf(fin,"%s",occ[i].word) == 1;i++); //Non considera gli '
    char riga[maxRIGA + 1];

    // Leggo il file dall'inizio alla fine
    while (fgets(riga, sizeof(riga), fin) != NULL) {
        char act_word[maxWORD] = "";
        int i = 0;

        // Inizio di una parola
        while(riga[i] != '\0'){
            while (riga[i] != '\0' && !isalnum(riga[i])) i++;

            // Inizio di una parola
            int j = 0;
            while (riga[i] != '\0' && isalnum(riga[i]) && j < maxWORD) {
                act_word[j++] = tolower(riga[i++]);
            }
            act_word[j] = '\0';
            if(j>0){
                strcpy(occ[Nword++].word, act_word);
            }
        }

    }
    
    return Nword;
}

int cercaParola(char word[maxSEQ],int n, occurrency occ[n], char output[outputS]){
    int match = 0;
    for(int i = 0; i<n; i++){
        if (strstr(occ[i].word, word) != NULL) {
            char temp[100];
            sprintf(temp, "\n- %s (posizione %d)", occ[i].word, i+1);
            strcat(output, temp);
            match++;
            if (match >= maxOCC) return match;
        }
    }

    return match;
}   
