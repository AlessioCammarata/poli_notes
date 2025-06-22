#include <stdio.h>

int main(void){

    int n = 5, occ_sempl[4] = {0,0,0,0},occ_mult[4] = {0,0,0,0};
    int vet[5] = {2, 4, 5, 3, 4}, B[5];
    int offset = 2;

    for(int i =0; i<n; i++){
        occ_sempl[vet[i]-offset]++;
    }

    occ_mult[0] = occ_sempl[0];
    for(int i = 1;i<4;i++){
        occ_mult[i] = occ_mult[i - 1] + occ_sempl[i];
    }
    
    for(int i = 0; i<4;i++) printf("%d",occ_sempl[i]);
    printf("\n");
    for(int i = 0; i<4;i++) printf("%d",occ_mult[i]);
    printf("\n");

    for(int i = n - 1; i >= 0; i--) {
        B[occ_mult[vet[i]-offset] - 1] = vet[i];
        occ_mult[vet[i]-offset]--;
    }


    for(int i = 0; i<n; i++) printf("%d",B[i]);

    //Se sono numeri interi per ricostruire il vettore ordinato.
    // for(int i = 0; i<n;i++){ 
        
    //     for(int j = 0; j<occ_mult[i]-occ_mult[i-1];j++) printf("%d",i+offset);
    // }

    return 0;
}