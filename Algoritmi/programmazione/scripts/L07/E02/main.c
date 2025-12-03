#include <stdlib.h>
#include <stdio.h>

// #define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L07/E02/elementi.txt"
#define nfin "./elementi.txt"
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
void find_best_program(Elements **e, int pos, int sol[], int mark_t[], float score, int dif, int tot_dif, float *b_score, int DD, int DP, int k, int n);

int main(void){
    FILE *fin;
    int n, DD = 10, DP = 20;
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
    // int k = n;
    int *mark_t = calloc(n, sizeof *mark_t);
    int *sol = calloc(N_DIAG*N_E_DIAG, sizeof *sol);
    if (!mark_t || !sol) {
        perror("malloc");
        free(mark_t); free(sol);
        free_all(elements, n);
        fclose(fin);
        return 1;
    }
    float best = -1.0f;
    find_best_program(elements, 0, sol, mark_t, 0, 0, 0, &best, DD, DP, 0, n);
    printf("Best score: %.2f\n", best);
    printf("END\n");

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

            if(j>0 && e[sol[i*N_E_DIAG+j-1]]->type != 0 && e[sol[i*N_E_DIAG+j]]->type != 0) sequence = 1;
            if(acr_diag && back && forward && sequence) break;
        }
    }

    return acr_diag && back && forward && sequence;
}

void find_best_program(Elements **e, int pos, int sol[], int mark_t[], float score, int dif, int tot_dif, float *b_score, int DD, int DP, int k, int n){
    
    if(pos!= 0 && pos%N_E_DIAG ==  0){
        if(dif > DD) return;
        tot_dif += dif;
        dif = 0;
        if (tot_dif > DP) return;
    }

    if(pos >= N_DIAG*N_E_DIAG){
        // if(k >= N_DIAG*N_E_DIAG){
            if(tot_dif > DP) return;
            printf("%d\n",tot_dif);

            if(is_valid(e,sol)){
                if(score > *b_score) *b_score = score;
                printf("%f",*b_score);
                // for(int i = 0; i < k; ++i){
                //     if(mark_t[i]){
                //         // if(i) printf(" | ");
                //         // printf("%.2f:%s", e[sol[i]]->value, e[i]->name);
                //     }
                // }
                printf("\n");
            }
        // }
        return;
    }
    // printf("%f",e[k]->value);
    // printf("%d %d\n",k,pos);
    
    //Ricorsione prendo uno di ognuno
    // score += e[pos]->value;
    // dif += e[pos]->difficulty;
    // mark_t[pos] = 1;
    // sol[k] = pos;
    // find_best_program(e, pos+1, sol, mark_t, score, dif, tot_dif, b_score, DD, DP, k+1, n);
    
    // score -= e[pos]->value;
    // dif -= e[pos]->difficulty;
    // mark_t[pos] = 0;
    // find_best_program(e, pos+1, sol, mark_t, score, dif, tot_dif, b_score, DD, DP, k, n);

    //Ricorsione corretta
    for (int i=k; i<n; ++i) { 
		sol[pos] = i;
		find_best_program(e, pos+1, sol, mark_t, score + e[i]->value, dif + e[i]->difficulty, tot_dif, b_score, DD, DP, i, n);
	}
    
    return;
}