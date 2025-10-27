#include <stdio.h>
#include <stdlib.h>

// #define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L04/E03/easy_test_set.txt"
#define nfin "./easy_test_set.txt"
#define Nstones 4

void free_vet(int **vet, int n);
int leggiFile(FILE *fin, int **all_stones, int n);
int necklace_maker(int *stones, int pos);

int main(void){
    FILE *fin;
    int len = 0, n, **all_stones;

    if((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }

    if(fscanf(fin,"%d",&n) != 1){
        printf("Manca il numero di collane");
        fclose(fin);
        return 1;
    }

    all_stones = malloc(n*sizeof(int *));
    if (all_stones == NULL) {
        perror("malloc");
        fclose(fin);
        return 1; //Fermo la lettura e do errore.
    }

    if (!leggiFile(fin, all_stones, n)) { // Leggo i dati e li metto in playlist
        free(all_stones);
        fclose(fin);
        return 1;
    }
    fclose(fin);

    for(int k = 0; k<n; k++){
        printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",all_stones[k][0],all_stones[k][1],all_stones[k][2],all_stones[k][3],all_stones[k][0]+all_stones[k][1]+all_stones[k][2]+all_stones[k][3]);
        len = necklace_maker(all_stones[k], -1);
        printf("Collana massima di lunghezza %d\n",len);
        free(all_stones[k]);
    }
    
    // for(int i = 0, j; i<n; i++){
    //     for(j = 0; j<Nstones;j++) printf("%d ",stones[i][j]);
    //     printf(" -> %d pietre",stones[i][j]);
    //     printf("\n");
    // }

    // free_vet(all_stones, n);
    free(all_stones);
    return 0;
}

void free_vet(int **vet, int n){
    for (int i = 0; i < n; i++) { 
        free(vet[i]); 
    }
}

int leggiFile(FILE *fin, int **all_stones, int n){
    int i, j, sum;
    for(i = 0; i < n; i++){

        all_stones[i] = malloc(Nstones*sizeof(int));
        if (all_stones[i] == NULL) {
            perror("malloc");
            free_vet(all_stones, i);
            return 0; //Fermo la lettura e do errore.
        }

        // leggo le pietre
        for (j = 0; j < Nstones; j++) {
            if (fscanf(fin,"%d",&all_stones[i][j]) != 1) {
                printf("Errore in lettura delle pietre alla voce %d\n",i);
                // cleanup completo (incl. corrente i)
                free_vet(all_stones, i + 1);
                return 0;
            }
        }
        
    }

    return 1;
}

// Indici: 0=Z, 1=R, 2=T, 3=S
int is_ZS(int x) { return x == 0 || x == 3; }
int is_RT(int x) { return x == 1 || x == 2; }

int can_follow(int last, int nxt) {
    if (last < 0) return 1;            // primo elemento libero
    return (is_ZS(last) && is_RT(nxt)) ||
           (is_RT(last) && is_ZS(nxt));
}

int best_necklace(int last, int cnt[4]) {
    int best = 0, moved = 0;
    for (int nxt = 0; nxt < 4; ++nxt) {
        if (cnt[nxt] == 0) continue;
        if (!can_follow(last, nxt)) continue;
        moved = 1;
        cnt[nxt]--;
        int len = 1 + best_necklace(nxt, cnt);
        if (len > best) best = len;
        cnt[nxt]++;
    }
    return moved ? best : 0; // nessuna mossa: termina
}

int necklace_maker(int *stones, int pos) {
    int cnt[4] = { stones[0], stones[1], stones[2], stones[3] };

    if (pos >= 0) {
        if (cnt[pos] == 0) return 0;
        cnt[pos]--;
        return 1 + best_necklace(pos, cnt);
    }

    int best = 0;
    for (int start = 0; start < 4; ++start) {
        if (cnt[start] == 0) continue;
        cnt[start]--;
        int len = 1 + best_necklace(start, cnt);
        if (len > best) best = len;
        cnt[start]++;
    }
    return best;
}

// Ordine: z, r, t, s
// Disposizioni ripetute con criterio
// int necklace_maker(int *stones, int pos){
//     int len = 0;
//     printf("%d\n",pos);
//     if(stones[pos] != 0){
//         stones[pos]--;
//         for(int j = 0; j<Nstones;j++) printf("%d ",stones[j]);
//         printf("\n");
//         return 1;
//     }

//     if(pos == 0) pos = stones[pos] == 0 ? 1 : 0; //Finisco gli zaffiri e passo ai rubini
//     else if(pos == 1) pos = stones[3] == 0 ? 2 : 3; // Finisco gli smeraldi poi passo ai topzai
//     else if(pos == 2) pos = stones[0] == 0 ? 1 : 0;
//     else if(pos == 3) pos = stones[pos] == 0 ? 2 : 3; //Finisco gli smeraldi e passo a topazi

//     len += necklace_maker(stones, pos);

//     return len;

// }