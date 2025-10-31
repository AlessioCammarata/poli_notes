#include <stdio.h>
#include <stdlib.h>

#define nfin1 "./tiles.txt"
#define nfin2 "./board.txt"

typedef struct{
    char col_o; int val_o;
    char col_v; int val_v;
} piece;

typedef struct{
    int idx; int rot;
} ceil;

int leggiFile_tiles(FILE *fin, int n, piece *v);
int leggiFile_board(FILE *fin, int r, int c, ceil **b);

int main(void){
    FILE *fin;
    int n, r, c;
    piece *pieces;
    ceil **board;

    if((fin = fopen(nfin1,"r")) == NULL){
        printf("Errore in apertura del file: %s", nfin1);
        return 1;
    }
    if(fscanf(fin,"%d",&n) != 1){
        printf("Errore in lettura del file: %s", nfin1);
        fclose(fin);
        return 1;
    }

    pieces = malloc(n*sizeof(piece));
    if(!pieces){
        perror("malloc");
        fclose(fin);
        return 1;
    }

    if (!leggiFile_tiles(fin, n, pieces)){
        printf("Errore in lettura del file: %s", nfin1);
        fclose(fin);
        free(pieces);
        return 1;
    }
    fclose(fin);

    // for(int i = 0; i<n; i++) printf("%c %d %c %d\n", pieces[i].col_o, pieces[i].val_o, pieces[i].col_v, pieces[i].val_v);

    if((fin = fopen(nfin2,"r")) == NULL){
        printf("Errore in apertura del file: %s", nfin2);
        free(pieces);
        return 1;
    }
    if(fscanf(fin,"%d %d",&r,&c) != 2){
        printf("Errore in lettura del file: %s", nfin2);
        free(pieces);
        fclose(fin);
        return 1;
    }

    board = malloc(r*sizeof(ceil *));
    if(!board){
        perror("malloc");
        free(pieces);
        fclose(fin);
        return 1;
    }

    if (!leggiFile_board(fin, r, c, board)){
        printf("Errore in lettura del file: %s", nfin1);
        fclose(fin);
        free(pieces);
        free(board);
        return 1;
    }
    fclose(fin);

    // for(int i = 0; i<r;i++){
    //     for(int j = 0; j<c;j++) printf("%d/%d, ",board[i][j].idx,board[i][j].rot);
    //     printf("\n");
    // }
    int *best;
    // board, pieces, cur_val, best_value,
    calcola_max(board, pieces, 0, best);

    //Pulisco tutto
    for(int k = 0; k<r; k++) free(board[k]);
    free(board);
    free(pieces);
    return 0;
}

int leggiFile_tiles(FILE *fin, int n, piece *v){
    int i;
    for(i = 0;i<n;i++){
        if (fscanf(fin," %c %d %c %d", &v[i].col_o, &v[i].val_o, &v[i].col_v, &v[i].val_v) != 4) break;
    }

    return i==n;
}

int leggiFile_board(FILE *fin, int r, int c, ceil **b){
    int i,j;
    for(i = 0;i<r;i++){
        b[i] = malloc(c*sizeof(ceil));
        if(!b[i]){
            for(int k = 0; k<i; k++) free(b[k]);
            break;
        }
        for(j = 0; j<c; j++){
            if (fscanf(fin,"%d/%d",&b[i][j].idx, &b[i][j].rot ) != 2){
                for(int k = 0; k<=i; k++) free(b[k]);
                break;
            }
        }
    }

    return i==r && j == c;
}