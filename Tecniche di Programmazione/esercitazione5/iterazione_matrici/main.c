#include <stdio.h>
#define nfin "./test.txt" 

void print_matrix(int nc, int nr,int matrix[nr][nc]){
    int i,j;
    for(i = 0;i<nr;i++){
        for(j = 0;j<nc;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

int calc_matrix(int val,int i, int j, int nr, int nc, int matrix[nr][nc]){
    int sum=0;
    
    // while(t<val && c<val){
    //     printf("%d ",matrix[i+c][j+t]);
    //     sum = sum + matrix[i+c][j+t];

    //     if(t==val-1 && c!= val){
    //         printf("\n");
    //         c++;
    //         t=0;
    //     }else{
    //         t++;
    //     }
    // }
    for (int r = 0; r < val; r++) {
        for (int c = 0; c < val; c++) {
            printf("%d ", matrix[i + r][j + c]);
            sum += matrix[i + r][j + c];
        }
        printf("\n");
    }
    return sum;
}

int main(void){
    FILE *fin;
    int nr,nc,val,l,ok=1,i=0,j=0,t=0,c=0,nl,nv,max,sum,index_x,index_y;

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    fscanf(fin,"%d",&nr);
    fscanf(fin,"%d",&nc);

    l = nc < nr ? nc : nr;
    int matrix[nr][nc];
    for(i = 0;i<nr;i++){
        for(j = 0; j < nc; j++) {
            if (fscanf(fin, "%d", &matrix[i][j]) != 1) {
                printf("Errore nella lettura della matrice\n");
                return 1;
            }
        }
    }

    print_matrix(nc,nr,matrix);

    do{
        printf("Inserisci un valore da controllare\n");
        ok = scanf("%d",&val) == 1 && val<=l;
        if(ok){
            max = 0;
            sum = 0;
            //Per trovare i quadrati per ogni riga
            nl = nc - val +1; //1
            nv = nr - val +1; //2


            for(i=0;i<nv;i++){
                for(j=0;j<nl;j++){
                    
                    sum = calc_matrix(val,i,j,nr,nc,matrix);
                    //Assegniamo il valore al max
                    if(sum > max){
                        max = sum;
                        index_x = i;
                        index_y = j;
                    }

                    printf("\n");
                }
            }

            printf("La matrice che ha la somma maggiore (%d) è: \n",max);
            calc_matrix(val,index_x,index_y,nr,nc,matrix);
            
        }
        
    }while(ok);

    fclose(fin);
    return 0;
}