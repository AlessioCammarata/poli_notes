#include <stdio.h>
// #define filein "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/ver_seq_numeri/seq.txt" 
#define filein "./seq.txt" 
/*
Occorre verificare che l’i-esimo numero xi (con i ≥2)
sia, rispetto ai due numeri precedenti (xi-1 e xi-2), pari alla loro somma (xi-2 + xi-1), differenza (xi-2 - xi-1),
prodotto (xi-2 * xi-1) o quoziente (xi-2 / xi-1)
*/
int verifica(int num,int num1,int num2){
    int diff = num2-num1, sum = num2 + num1, x = num2*num1;
    float div = num1 != 0 ? div = num2 / num1 : sum;

    return num == diff || num == sum || num == x || num == div ;
}

void controlla(FILE *fin){
    /*
    num -> numero corrente
    num1 -> numero precedente
    num2 -> numero 2 volte precedente
    numr -> numero di recupero
    err -> contatore degli errori
    */
    int num,num1,num2,numr,max = 0,min = 100000,i=1,err=0;

    while(fscanf(fin,"%d",&num) == 1){
        if(i>2){
            if(verifica(num,num1,num2)){
                if(num>max) max = num;
                if(num<min) min = num;
            }else{ 
                //Utilizzo il numero di recupero per tornare indietro di 1, mper i calcoli
                num = num1; 
                num1 = num2; 
                num2 = numr; 
                err++;
            }
        }else{
            if(num>max) max = num;
            if(num<min) min = num;
            i++;
        }

        numr = num2;
        num2 = num1;
        num1 = num;
        
    }
    printf("%d",i);
    printf("\nNumero massimo: %d\n Numero minimo: %d\n Numeri scartati: %d",max,min,err);
}

int main(void){
    FILE *fin;

    if((fin = fopen(filein,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }

    controlla(fin);

    fclose(fin);
    return 0;
}