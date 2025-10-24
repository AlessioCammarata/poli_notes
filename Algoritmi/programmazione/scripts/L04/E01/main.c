#include <stdio.h>
#include <stdlib.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L04/E01/grafo.txt"

typedef struct{
    int *neighbours;
    int n;
} node;

void leggiFile(FILE *fin, node **vet);
int powerset(int pos, int *val, int *sol, int n, int start, int cnt, node **vet);
void find_vertex_cover(node **vet, int n);

int main(void){
    FILE *fin;
    node **vet;
    int N, E;

    if ((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }
    
    if(fscanf(fin,"%d %d",&N,&E) != 2){
        printf("Manca la N o la E");
        fclose(fin);
        return 1;
    }

    //Preparo i nodi
    vet = malloc(N * sizeof(node *));
    if (vet == NULL) {
        perror("malloc");
        fclose(fin);
        return 1;
    }
    for (int i = 0; i < N; ++i) {
        vet[i] = malloc(sizeof(node));
        if (vet[i] == NULL) {
            for(int j = 0; j<i; j++){
                free(vet[j]->neighbours);
                free(vet[j]);
            }
            free(vet);
            perror("malloc");
            fclose(fin);
            return 1;
        }
        vet[i]->neighbours = malloc(E*sizeof(int));
        if (vet[i]->neighbours == NULL) {
            int j;
            for(j = 0; j<i; j++){
                free(vet[j]->neighbours);
                free(vet[j]);
            }
            free(vet[j+1]);
            free(vet);
            perror("malloc");
            fclose(fin);
            return 1;
        }
        vet[i]->n = 0; //Nessun vicino per ora
    }

    leggiFile(fin, vet);
    // for(int i = 0; i<N; i++) printf("%d\n",vet[i]->n);
    // find_vertex_cover(vet, N);
    int *sol = malloc(N*sizeof(int));
    int *val = malloc(N*sizeof(int));
    for(int i = 0; i<N; i++) val[i] = i;
    int n = powerset(0, val, sol, N, 0, 0, vet); 

    return 0;
}

void leggiFile(FILE *fin, node **vet){
    int val1,val2;
    while(fscanf(fin,"%d %d",&val1,&val2) == 2){
        vet[val1]->neighbours[vet[val1]->n++] = val2;
        vet[val2]->neighbours[vet[val2]->n++] = val1;
    }
}

int powerset(int pos, int *val, int *sol, int n, int start, int cnt, node **vet) {
    int i;
    if (start >= n) {
        int m = 0;
        printf("( ");
        for (i = 0; i < pos; i++){
            printf("%d, ", sol[i]);
        }
        printf(")\n");
        return cnt+1;
    }
    for (i = start; i < n; i++) {
        sol[pos] = val[i];
        cnt = powerset(pos+1, val, sol, n, i+1, cnt, vet);
    }
    cnt = powerset(pos, val, sol, n, n, cnt, vet);
    return cnt;
}


// void find_vertex_cover(node **vet, int n){
//     for(int i = 0; i<n; i++){
//         for(int j = 0; j<vet[i]->n; j++){
//             if(vet[i]->neighbours[j] != i){ // Controllo che sia diverso da i

//             }
//         }
//     }
// }

// void find_vertex_cover(node **vet, int n){
//     if (n <= 0) return;
//     if (n > 30) {
//         printf("n troppo grande per brute-force (%d)\n", n);
//         return;
//     }

//     long long limit = 1LL << n;
//     int *in_cover = malloc(n * sizeof(int));
//     if (!in_cover) return;

//     for (long long mask = 0; mask < limit; ++mask) {
//         for (int i = 0; i < n; ++i) in_cover[i] = (mask >> i) & 1;

//         int ok = 1;
//         for (int u = 0; u < n && ok; ++u) {
//             for (int k = 0; k < vet[u]->n && ok; ++k) {
//                 int v = vet[u]->neighbours[k];
//                 if (!in_cover[u] && !in_cover[v]) ok = 0;
//             }
//         }

//         if (ok) {
//             printf("{");
//             int first = 1;
//             for (int i = 0; i < n; ++i) if (in_cover[i]) {
//                 if (!first) printf(",");
//                 printf("%d", i);
//                 first = 0;
//             }
//             printf("}\n");
//         }
//     }

//     free(in_cover);
// }