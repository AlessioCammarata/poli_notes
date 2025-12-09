#include <stdlib.h>
#include <stdio.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L07/E02/elementi.txt"
// #define nfin "./elementi.txt"
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
    int act_dif, tot_dif, c = 0, idx, prev_end_d = -1, prev_acro = 0, final;
    float act_value, tot_value, max = 0;
    
    qsort(e, n, sizeof(*e), cmp_elem_by_value_desc);
    
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
            final = -1;
            int prev_final = 0, prev_start_d = 0, mul = 1, prev_index = -1, prev_mul = 1;
            // if(!e[(k)%n]->prec) continue; //Non puoi cominciare con questo
            for(int j = k; j<n; j++){
                if(c == N_E_DIAG) break;
                idx = (k+j)%n;
                // if(c == 0 && e[idx]->prec) continue; //Non puoi cominciare con questo
                
                if(final != -1 && e[idx]->final){ //Se ho gia il final skippa
                    continue;
                }
                
                // if(e[idx]->final) { //Al primo final che trovo lo tengo e ci aggiungo il resto
                //     final = idx;
                //     //Non finito
                // }
                
                if(final != -1){
                    if(prev_start_d != e[idx]->end_dir) continue;
                }else
                    if(j!=k && prev_end_d != e[idx]->start_dir) continue;

                // printf("%.2f %d %d %d - ",e[idx]->value,e[idx]->end_dir, prev_start_d,prev_start_d != e[idx]->end_dir);

                printf("%.2f %d %d %d - ",e[idx]->value,e[idx]->type, prev_start_d,prev_start_d != e[idx]->end_dir);

                int p = 1;
                //Controllo se il valore dopo puo stare due volte e se in quel caso ha valore maggiore del primo
                if(idx < n-1 && mul == 1 && prev_index != -1){
                    int max_mul = N_E_DIAG - c;
                    if (max_mul < 1) max_mul = 1;
                    p = c; // N_E_DIAG - c
                    while(p<=max_mul){
                        if(!e[idx]->final                                       &&
                            e[idx]->end_dir == e[idx]->start_dir                && 
                            e[idx]->difficulty * p + act_dif <= DD              &&  //DEvo sistemare qua perche è sempre maggiore
                            e[idx]->difficulty * p + tot_dif + act_dif <= DP    &&  //DEvo sistemare qua perche è sempre maggiore
                            e[prev_index]->value/e[prev_index]->difficulty*prev_mul + e[idx+1]->value/e[idx+1]->difficulty < e[idx]->value/e[idx]->difficulty * p
                        ) mul = p;
                        p++;
                    }
                    // if(mul != 1) continue;
                }
                prev_index = idx;
                prev_mul = mul;
                printf("(%d) ",mul);
                //Controllo che ancora non va bene ma serve per contare cose, devo controllare che il valore attuale*p > precedente*prev_mul + next
                // if(mul != 1 && prev_mul != 1){
                //     for(int v = 0; v<prev_mul; v++){
                //         tmp[i][--c] = -1;
                //         act_dif -= e[prev_index]->difficulty;
                //     }
                // }

                
                int nd = e[idx]->difficulty;
                if (act_dif + nd > DD) continue;
                if (tot_dif + act_dif + nd > DP) continue;

                //Controlli finali di validità
                if(e[idx]->type != 0) has_acro = 1;
                if((j != k && e[idx]->type != 0 && prev_acro) || e[idx]->type != 0 && mul > 1) has_acro_seq = 1;
                if(e[idx]->type == 1) has_b = 1; 
                if(e[idx]->type == 2) has_f = 1; 

                for(int val = 0; val < mul && c < N_E_DIAG; val++){  
                    // if(c == N_E_DIAG) break;       
                    act_dif += nd;
                    act_value += e[idx]->value;
                    prev_end_d = e[idx]->end_dir;
                    prev_start_d = e[idx]->start_dir;
                    prev_acro = (e[idx]->type != 0) ? 1 : 0;

                    tmp[i][c++] = idx;
                    printf("Adding: %d - %d\n",e[idx]->difficulty,c);
                }
                if(e[idx]->final){
                    final = idx;
                    prev_final = 1;
                }
                
                // j = k;
                printf("\n");
            }
            printf("----\n\n");

            printf("%d - %d - %d\n",i,c,tot_dif);
            if (c == 0) {
                // if(final != -1)
                //     tmp[i][c++] = final;
                // else{
                    valid = 0; 
                    break; 
                // }
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
            printf("%d - %d - %d\n",i,c,tot_dif);
            printf("\n----------------------------\n\n");
        }
                printf("%d - %.2f\n",valid,tot_value);
        // break;
        // printf("%d - %d",valid,valid);

        if (!valid) continue;
        printf("%.2f - %.2f\n",tot_value,max);
        printf("%d - %d - %d\n",has_b,has_f, has_acro_seq);

        if(tot_value > max && has_b && has_f && has_acro_seq) {
            max = tot_value;
            //Soluzione valida quindi copio
            for(int j = 0; j<N_DIAG; j++){
                for(int m = 0; m<N_E_DIAG; m++){
                    printf("%d ",tmp[j][m]);
                    sol[j][m] = tmp[j][m];
                }
                printf("\n");
            }
        }
        printf("%.2f - %.2f\n",tot_value,max);

        break;


    }
    for(int i = 0; i<n; i++){
        printf("%.2f ",e[i]->value/e[i]->difficulty);
        printf("%.2f ",e[i]->value);
        printf("%d ",e[i]->difficulty);
        printf(" %s\n",e[i]->name);
        // printf("%d ",e[i]->final);
    }
    // int dif = 0;
    printf("%.2f\n",max);


    // for(int i = 0; i<n; i++) printf("%d: %.2f\n",i,e[i]->value);
    for(int i= 0; i<N_DIAG; i++) {
        for(int j = 0; j<N_E_DIAG; j++) printf("%s ", tmp[i][j] != -1 ? e[tmp[i][j]]->name : "");
            // dif += sol[i][j] != -1 ? e[sol[i][j]]->difficulty : 0;
        printf("\n");
    }
    
    for (int i = 0; i < N_DIAG; i++){
        free(tmp[i]);
    }
    free(tmp);
    // printf("%d",dif);
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