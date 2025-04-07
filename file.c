#include <stdio.h>
#include <stdlib.h>
#define SIZE 11

int main(void){
    int i, dati[SIZE],result[SIZE];

    for(i=0;i<SIZE;i++){
        dati[i] = rand() % 100;
        result[i] = 0;
    }
    i = 0;

    for(i=0;i<SIZE;i++){
        result[dati[i]/10] ++;
    }

    for(i=0;i<SIZE;i++){
        printf("%d0 %d\n",i,result[i]);
    }
}