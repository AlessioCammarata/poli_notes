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
int leggiFile_board(FILE *fin, int r, int c, ceil **b, ceil **cur_b, int **mark, int *used);
void get_segment(piece *p, int idx, int rot, int horiz, char *out_col, int *out_val);
int calcola_punteggio(ceil **b, piece *p, int r, int c);
void calcola_max(ceil **b, piece *p, int pos, int *best, ceil **cur_b, int **mark, int *used, int r, int c, int n);

int main(void){
    FILE *fin;
    int n, r, c, *used, **mark, best = 0;
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
    mark = malloc(r*sizeof(int *));
    cur_b = malloc(r*sizeof(ceil *));
    used = calloc(n,sizeof(int));
    if(!board || !mark || !cur_b || !used){
        perror("malloc");
        free(pieces);
        free(board); free(mark); free(cur_b); free(used);
        fclose(fin);
        return 1;
    }

    //Inizializzo tutto cio che riguarda la board mentre leggo i dati dal file
    /*
        board -> campo effettivo
        mark  -> matrice significativa associata
        cur_b -> campo utilizzato per valutare le soluzioni
        used -> vettore significativo associato, lo passo perche metto ad 1 quelli gia usati 
    */
    if (!leggiFile_board(fin, r, c, board, cur_b, mark, used)){
        printf("Errore in lettura del file: %s", nfin1);
        fclose(fin);
        free(pieces);
        free(board); free(mark); free(cur_b); free(used);
        return 1;
    }
    fclose(fin);

    // board, pieces, pos, best_value, cur_b, mark, used, rows, columns, n tails
    calcola_max(board, pieces, 0, &best, cur_b, mark, used, r, c, n);
    printf("%d\n",best);

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
    free(cur_b); free(mark); free(board); free(used);
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


int leggiFile_board(FILE *fin, int r, int c, ceil **b, ceil **cur_b, int **mark, int *used){
    int i,j;
    for(i = 0, j = 0;i<r;i++){
        b[i] = malloc(c*sizeof(ceil));
        mark[i] = calloc(c,sizeof(int));
        cur_b[i] = malloc(c*sizeof(ceil));
        if(!b[i] || !mark[i] || !cur_b[i]){
            for(int k = 0; k<i; k++){
                free(b[k]);
                free(cur_b[k]);
                free(mark[k]);
            }break;
        }

        for(j = 0; j<c; j++){
            //Leggo da file i dati
            if (fscanf(fin,"%d/%d",&b[i][j].idx, &b[i][j].rot ) != 2){
                for(int k = 0; k<=i; k++){
                    free(b[k]);
                    free(cur_b[k]);
                    free(mark[k]);
                }
                break;
            }
            //Se la casella è vuota me lo segno in mark, altrimenti segno che la casella è presente in used e la metto gia in cur_b
            if(b[i][j].idx == -1){
                mark[i][j] = 1;
            } else {
                used[b[i][j].idx] = 1;
                cur_b[i][j] = b[i][j];
            }

        }
    }

    return i==r && j == c;
}

void get_segment(piece *p, int idx, int rot, int horiz, char *out_col, int *out_val){
    /* 
        horiz==1 -> voglio il segmento orizzontale della tessera
        horiz==0 -> voglio il segmento verticale 
    */
    if(rot == 0){
        if(horiz){ 
            *out_col = p[idx].col_o; 
            *out_val = p[idx].val_o; 
        } else{ 
            *out_col = p[idx].col_v; 
            *out_val = p[idx].val_v; 
        }
    }else {
        if(horiz){ 
            *out_col = p[idx].col_v; 
            *out_val = p[idx].val_v; 
        } else{ 
            *out_col = p[idx].col_o; 
            *out_val = p[idx].val_o; 
        }
    }
}

int calcola_punteggio(ceil **b, piece *p, int r, int c){
    int i, j, sum, val_j, score = 0;
    char color, col_j;
    int val;

    //Punteggio orizzontale
    for(i = 0; i<r; i++){
        get_segment(p, b[i][0].idx, b[i][0].rot, 1, &color, &val);
        sum = val; //Inizializzo la somma
        for(j = 1; j<c; j++){
            get_segment(p, b[i][j].idx, b[i][j].rot, 1, &col_j, &val_j);
            if(col_j != color){ sum = 0; break; }
            sum += val_j;
        }
        score += sum;
    }

    //Punteggio verticale
    for(i = 0; i<c; i++){
        get_segment(p, b[0][i].idx, b[0][i].rot, 0, &color, &val);
        sum = val; //Inizializzo la somma
        for(j = 1; j<r; j++){
            get_segment(p, b[j][i].idx, b[j][i].rot, 0, &col_j, &val_j);
            if(col_j != color){ sum = 0; break; }
            sum += val_j;
        }
        score += sum;
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