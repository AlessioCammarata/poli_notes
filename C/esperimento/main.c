#include <stdio.h>

int main(void) {
    int c = 3,p = 13,s;

    s = c*p;
    printf("%d %d\n",s,2);
    printf("%d %d",s,s /= 10);

    return 0;
}