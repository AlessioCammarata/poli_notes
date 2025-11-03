#include <stdio.h>
#include <stdlib.h>

// #define nfin1 "./tiles.txt"
#define nfin1 "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L05/E02/tiles.txt"
// #define nfin2 "./board.txt"
#define nfin2 "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L05/E02/board.txt"

typedef struct{
    char col_o; int val_o;
    char col_v; int val_v;
} piece;

typedef struct{
    int idx; int rot;
} ceil;

int leggiFile_tiles(FILE *fin, int n, piece *v);
int leggiFile_board(FILE *fin, int r, int c, ceil **b, int *count);
int calcola_punteggio(ceil **b, piece *p, int r, int c);
void calcola_max(ceil **b, piece *p, int pos, int *best, ceil **cur_b, int **mark, int *used, int r, int c, int n);

int main(void){
    FILE *fin;
    int n, r, c, count = 0, *used, **mark;
    piece *pieces;
    ceil **board, **cur_b;

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

    for(int i = 0; i<n; i++) printf("%c %d %c %d\n", pieces[i].col_o, pieces[i].val_o, pieces[i].col_v, pieces[i].val_v);

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

    if (!leggiFile_board(fin, r, c, board, &count)){
        printf("Errore in lettura del file: %s", nfin1);
        fclose(fin);
        free(pieces);
        free(board);
        return 1;
    }
    fclose(fin);

    for(int i = 0; i<r;i++){
        for(int j = 0; j<c;j++) printf("%d/%d, ",board[i][j].idx,board[i][j].rot);
        printf("\n");
    }

    int best = 0;
    // seq = malloc(count*sizeof(piece));
    // best_seq = malloc(count*sizeof(piece));
    mark = malloc(r*sizeof(int *));
    cur_b = malloc(r*sizeof(ceil *));
    used = calloc(n,sizeof(int));

    if(mark != NULL && cur_b != NULL && used != NULL){
        for(int i = 0; i<r; i++){
            mark[i] = calloc(c,sizeof(int));
            cur_b[i] = malloc(c*sizeof(ceil));
            if(!mark[i] || !cur_b[i]){
                for(int k = 0; k<i; k++) free(cur_b[k]);
                for(int k = 0; k<i; k++) free(mark[k]);
                break;
            }
            for(int j = 0; j<c; j++){
                if(board[i][j].idx == -1){
                    mark[i][j] = 1;
                } else {
                    cur_b[i][j] = board[i][j];
                }
            }
        }

        // board, pieces, cur_val, best_value, count
        calcola_max(board, pieces, 0, &best, cur_b, mark, used, r, c, count);
        printf("%d\n",best);

    }else perror("malloc");
    
    for(int i = 0; i<r;i++){
        for(int j = 0; j<c;j++) printf("%d/%d, ",board[i][j].idx,board[i][j].rot);
        printf("\n");
    }

    //Pulisco tutto
    for(int k = 0; k<r; k++){ 
        free(board[k]);
        free(mark[k]);
        free(cur_b[k]);
    }
    free(cur_b);
    free(mark);
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

int leggiFile_board(FILE *fin, int r, int c, ceil **b, int *count){
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
            if(b[i][j].idx == -1) (*count)++; //Conto i valori non inseriti
        }
    }

    return i==r && j == c;
}

int calcola_punteggio(ceil **b, piece *p, int r, int c){
    int i, j, sum_o, sum_v, score = 0;
    char color;
    //Punteggio orizzontale
    for(i = 0; i<r; i++){
        color = p[b[i][0].idx].col_o; //Prendo il colore iniziale
        sum_o = p[b[i][0].idx].val_o; //Inizializzo la somma
        for(j = 1; j<c; j++){
            if(p[b[i][j].idx].col_o != color) break;
            sum_o += p[b[i][j].idx].val_o;
        }
        if(j == c) score += sum_o;
    }

    //Punteggio verticale
    for(i = 0; i<c;i++){
        color = p[b[0][i].idx].col_v; //Prendo il colore iniziale
        sum_v = p[b[0][i].idx].val_v; //Inizializzo la somma
        for(j = 1; j<r; j++){
            if(p[b[j][i].idx].col_v != color) break;
            sum_v += p[b[j][i].idx].val_v;
        }
        if(j == c) score += sum_v;
    }

    return score;
}

//Funzione ricorsiva, disposizioni semplici n(pieces) in k(posizioni) con backtracking
void calcola_max(ceil **b, piece *p, int pos, int *best, ceil **cur_b, int **mark, int *used, int r, int c, int n){ //K = n*c

    // trova prima cella libera
    int i0=-1, j0=-1;
    for (int i=0;i<r && i0==-1;i++)
        for (int j=0;j<c;j++)
            if (mark[i][j]) { i0=i; j0=j; break; }
    if(i0 == -1){ //Condizione di terminazione
        int score = calcola_punteggio(cur_b, p, r, c);
        printf("%d - %d, %d\n",pos,n,score);
        if(score > *best){
            *best = score;
            //Copio la board in b
            for(int i = 0; i<r; i++){
                for(int j = 0; j<c; j++){
                    b[i][j] = cur_b[i][j];
                }
            }
        }
        return;
    }

    // prova tutti i pezzi non ancora usati
    for (int piece_idx = 0; piece_idx < n; piece_idx++) {
        if (!used[piece_idx])
            // prova le rotazioni se rilevanti (es. rot = 0,1)
            for (int rot = 0; rot < 2; ++rot) {
                // applica scelta
                cur_b[i0][j0].idx = piece_idx;
                cur_b[i0][j0].rot = rot;
                used[piece_idx] = 1;
                mark[i0][j0] = 0; // ora è occupata

                // ricorri al prossimo slot
                calcola_max(b, p, pos + 1, best, cur_b, mark, used, r, c, n);

                // undo
                used[piece_idx] = 0;
                mark[i0][j0] = 1;
            }
    }

}