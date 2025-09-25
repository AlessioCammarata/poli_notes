#include <stdio.h>

int find_mcd(int n1 ,int n2){
    int res,n,var;

    if(n1 > n2) {
        n = n2;
        res = n1%n2;
    }else {
        n = n1;
        res = n2%n1;
    }

    while (res != 0){
        var = res;
        res = n%res;
        n = var;
    }

    return n;
}

int main(void){
    int n1,n2,mcd;

    printf("Inserire due numeri interi, ti trovo il MCD:");
    scanf("%d %d",&n1,&n2);

    if (n1!=0 && n2!=0)
        mcd = find_mcd(n1,n2);
    else mcd = 0;

    if (mcd != 0)
        printf("Risultato: MCD = %d",mcd);
    else  printf("Non puoi inserire 0");

    return 0;
}
