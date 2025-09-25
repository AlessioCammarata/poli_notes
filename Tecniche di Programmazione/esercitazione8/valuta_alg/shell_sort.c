#include <stdio.h>
#define n 10

void ShellSort(int A[], int N) {
    int i, j, x, l=0, r=N-1, h=1;
    
    // Utilizzando la sequenza di shell: h = 2^(x-1) - inizializzando h a N/2 e dividendo per 2 ad ogni iterazione fino ad arrivare a 2
    for (h = N/2; h >= 1; h /= 2) {
        // 2) Insertion‐sort “saltando” di h posizioni
        for (i = h; i < N; i++) {
            x = A[i];
            j = i;
            while (j >= h && A[j-h] > x) {
                A[j] = A[j-h];
                j -= h;
            }
            A[j] = x;
        }
    }
}

int main(void){
    int v[n] = {1,2,3,7,8,4,3,0,8,4};

    ShellSort(v,n);

    for(int i = 0; i<n;i++) printf("%d",v[i]);

}