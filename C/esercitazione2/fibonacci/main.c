#include <stdio.h>

int fibonacci(int x, int x1){
    return x+x1;
}

int main(void){
    int n,x = 0,x1 = 1;

    printf("Inserire il numero di numeri che si vogliono vedere dalla serie:\n");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        printf("%d ",x);

        x1 = fibonacci(x,x1);
        x = x1-x;

    }
    return 0;
}