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

//Ordino in maniera decrescente
int cmp_elem_by_value_desc(const void* a, const void* b) { 
    const Elements* const* pa = (const Elements* const*)a; 
    const Elements* const* pb = (const Elements* const*)b;
    const Elements* ea = *pa;
    const Elements* eb = *pb;
    //Difficulty > 0, sempre
    float a_density = ea->value/ea->difficulty;
    float b_density = eb->value/eb->difficulty;
    if (a_density < b_density) 
        return 1; 
    if (a_density > b_density) 
        return -1; 
    return 0; 
}

void find_best_program_greedy(Elements **e, int *sol[], int n, int DD, int DP){
    int act_dif, tot_dif, c = 0, idx, prev_end_d, prev_acro;
    float act_value, tot_value, max = 0;
    int **tmp = malloc(N_DIAG*sizeof *tmp);
    if (!tmp) {
        perror("malloc");
        return ;
    }
    for(int i = 0; i<N_DIAG; i++){
        tmp[i] = calloc(N_E_DIAG, sizeof *tmp[i]);
        if (!tmp[i]) {
            perror("calloc");
            for (int j = 0; j < i; j++) free(tmp[j]);
            free(tmp);
            return ;
        }
        for(int j = 0; j<N_E_DIAG; j++) tmp[i][j] = -1;
    }
    
    qsort(e, n, sizeof(*e), cmp_elem_by_value_desc);
    for(int k = 0; k<n; k++){
        // printf("%d\n",tot_dif);
        tot_dif = 0;
        tot_value = 0;
        int valid = 1, has_acro = 0, has_b = 0, has_f = 0, has_acro_seq = 0;

        for(int i = 0; i<N_DIAG; i++){
            for(int j = 0; j<N_E_DIAG; j++) tmp[i][j] = -1;
            act_dif = 0;
            act_value = 0;
            c = 0;
            if(!e[(k)%n]->prec) continue; //Non puoi cominciare con questo
            for(int j = k; j<n; j++){
                if(c == N_E_DIAG) break;
                idx = (k+j)%n;
                int nd = e[idx]->difficulty;
                
                if(e[idx]->type != 0) has_acro = 1;
                if(j != k && e[idx]->type != 0 && prev_acro) has_acro_seq = 1;
                if(e[idx]->type == 1) has_b = 1; 
                if(e[idx]->type == 2) has_f = 1; 
                if(j!=k && prev_end_d != e[idx]->start_dir) continue;
                if (act_dif + nd >= DD) continue;
                if (tot_dif + act_dif + nd >= DP) continue;


                act_dif += nd;
                act_value += e[idx]->value;
                tmp[i][c++] = idx;
                prev_end_d = e[idx]->end_dir;
                prev_acro = e[idx] != 0 ? 1 : 0;

                if(e[idx]->final) break;
            }
            // printf("%d - %d - %d\n",i,c,tot_dif);
            if (c == 0) { 
                valid = 0; 
                break; 
            }  // diagonale vuota: scarta tentativo
            if(!has_acro){
                valid = 0;
                break;
            }
            tot_dif += act_dif;
            if (tot_dif > DP) { 
                valid = 0; 
                break; 
            } // sforato DP complessivo

            // bonus 1.5 sulla “prima” che poi leggerai al contrario
            tot_value += (i == 0) ? act_value * 1.5f : act_value;
            //Controlli su sol[i]
        }

        // printf("%d - %d",valid,valid);

        if (!valid) continue;
        // printf("%d - %d\n",tot_value,max);
        if(tot_value > max && has_b && has_f && has_acro_seq) {
            max = tot_value;
            //Soluzione valida quindi copio
            for(int j = 0; j<N_DIAG; j++){
                for(int m = 0; m<N_E_DIAG; m++){
                    // printf("%d ",tmp[j][m]);
                    sol[j][m] = tmp[j][m];
                }
                // printf("\n");
            }
        }
    }
    for (int i = 0; i < N_DIAG; i++) 
        free(tmp[i]);
    free(tmp);

    printf("%.2f\n",max);
    // for(int i = 0; i<n; i++) printf("%d: %.2f\n",i,e[i]->value);
    for(int i= 0; i<N_DIAG; i++) {
        for(int j = 0; j<N_E_DIAG; j++) printf("%f ", sol[i][j] != -1 ? e[sol[i][j]]->value : -1);
        printf("\n");
    }
    
    printf("\n");
    return;
}
    
// void find_best_program_greedy(Elements **e, int pos, int sol[], int mark_t[], float score, int dif, int tot_dif, float *b_score, int DD, int DP, int k, int n);

int main(void){
    FILE *fin;
    int n, DD = 12, DP = 28;
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
    int **sol = malloc(N_DIAG*sizeof *sol);
    if (!sol) {
        perror("malloc");
        free(sol);
        free_all(elements, n);
        fclose(fin);
        return 1;
    }
    for(int i = 0; i<N_DIAG; i++){
        sol[i] = calloc(N_E_DIAG, sizeof *sol[i]);
        if (!sol[i]) {
            perror("calloc");
            for (int j = 0; j < i; j++) free(sol[j]);
            free(sol);
            return 1;
        }
        for(int j = 0; j<N_E_DIAG; j++) sol[i][j] = -1;
    }
    float best = -1.0f;
    
    find_best_program_greedy(elements, sol, n, DD, DP);
    printf("Best score: %.2f\n", best);
    printf("END\n");

    for(int i = 0; i<N_DIAG; i++){
        free(sol[i]);
    }
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

        if(fscanf(fin,"%99s %d %d %d %d %d %f %d", 
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