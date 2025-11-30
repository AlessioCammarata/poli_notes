#include <stdlib.h>
#include <stdio.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L07/E02/elementi.txt"
#define MAX 100
#define N_DIAG 3
#define N_E_DIAG 5

typedef struct{
    char name[MAX];
    int type, start_dir, end_dir, prec, final;
    float value;
    int difficulty; 
} Elements;

void free_all(Elements **e, int n);
int leggiFile(FILE *fin, Elements **e, int n);
void find_best_program(Elements **e, int pos, int sel[], int sol[N_DIAG*N_E_DIAG], int mark_t[], int mark_di[], int mark_du[], int score, int dif, int k);

int main(void){
    FILE *fin;
    int n;
    Elements **elements;

    if((fin = fopen(nfin,"r")) == NULL){
        perror("Errore in apertura del file");
        return 1;
    }

    if(fscanf(fin,"%d",&n) != 1){
        perror("Errore in lettura del file");
        return 1;
    }

    elements = malloc(n*sizeof(Elements *));
    if (!elements) {
        perror("malloc");
        fclose(fin);
        return 1;
    } 

    if(!leggiFile(fin, elements ,n)){
        perror("Errore in lettura del file");
        fclose(fin);
        return 1;
    }

    // for(int i = 0; i<n; i++) 
    //     printf("%s %d %d %d %d %d %.2f %d\n", elements[i]->name, elements[i]->type, elements[i]->start_dir, 
    //                                     elements[i]->end_dir, elements[i]->prec, elements[i]->final, 
    //                                     elements[i]->value, elements[i]->difficulty);
    int k = n;
    int *mark_t = calloc(n, sizeof *mark_t);
    int *sol = calloc(N_DIAG*N_E_DIAG, sizeof *sol);
    if (!mark_t || !sol) {
        perror("malloc");
        free(mark_t); free(sol);
        free_all(elements, n);
        fclose(fin);
        return 1;
    }
    find_best_diag(elements, 0, sol, mark_t, k);
    free(mark_t);
    free(sol);


    free_all(elements, n);
    fclose(fin);
    return 0;
}

void free_all(Elements **e, int n){
    for(int i = 0; i<n; i++) free(e[i]);
    free(e);
}

int leggiFile(FILE *fin, Elements **e, int n){
    int i;
    for(i = 0; i<n; i++){
        e[i] = malloc(sizeof(Elements));
        if(!e[i]){
            free_all(e, i);
            return 0;
        }

        if(fscanf(fin,"%s %d %d %d %d %d %f %d", 
                                e[i]->name, 
                                &e[i]->type, 
                                &e[i]->start_dir, 
                                &e[i]->end_dir, 
                                &e[i]->prec, 
                                &e[i]->final, 
                                &e[i]->value, 
                                &e[i]->difficulty) != 8 ){
            free(e[i]);
            free_all(e, i);
            return 0;
        }
    }

    return i==n;
}

int calc_score(Elements **e, int v[], int n){
    int score = 0;
    for(int i = 0; i<n; i++){
        if(v[i]) score += e[i]->value;
    }
    return score;
}

int calc_difficulty(Elements **e, int v[]){
    int score = 0;
    for(int i = 0; i<N_DIAG*N_E_DIAG; i++){
        if(v[i]) score += e[i]->difficulty;
    }
    return score;
}

void reverse(int v[]){
    for(int i = 0; i<N_DIAG*N_E_DIAG; i++){
        v[i] = v[i] ? 0 : 1; 
    }
}

int is_valid(Elements **e, int sol[]){
    int acr_diag, back, forward, sequence;
    acr_diag = back = forward = sequence = 0;

    for(int i = 0; i<N_DIAG; i++){
        for(int j = 0; j<N_E_DIAG; j++){
            if(e[sol[i*N_E_DIAG+j]]->type != 0 && acr_diag == i) acr_diag++;
        
            if(e[sol[i*N_E_DIAG+j]]->type == 1) back = 1;
            if(e[sol[i*N_E_DIAG+j]]->type == 2) forward = 1;

            if(i*N_E_DIAG+j != i*N_E_DIAG && e[sol[i*N_E_DIAG+j-1]]->type != 0 && e[sol[i*N_E_DIAG+j]] != 0) sequence = 1;
            if(acr_diag && back && forward && sequence) break;
        }
    }

    return acr_diag && back && forward && sequence;
}

void find_best_program(Elements **e, int pos, int sol[], int mark_t[], int mark_di[], int mark_du[], int score, int dif, int k){
    if(pos == N_DIAG*N_E_DIAG){
        if(is_valid(e,sol)){
        // for(int i = 0; i < k; ++i){
        //     if(i) printf(" | ");
        //     printf("%d:%s", mark_t[i], e[i]->name);
        // }
        // printf("\n");
        }
        return;
    }

    
    score += e[pos]->value;
    dif += e[pos]->difficulty;
    mark_t[pos] = 1;
    sol[pos] = pos;
    find_best_diag(e, pos+1, sol, mark_t, score, dif, k);
    
    score -= e[pos]->value;
    dif -= e[pos]->difficulty;
    mark_t[pos] = 0;
    find_best_diag(e, pos+1, sol, mark_t, score, dif, k);
    
    return;
}