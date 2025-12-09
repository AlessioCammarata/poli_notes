/*
Idea: 
    provare a dividere gli elementi in base al fatto se possono 
    essere final o no in quanto cosi costruisci le diagonali sapendo già come finirle, e quindi ciclando su quelle che non possono finire.
    Ciclando per ogni elemento interno al vettore dei final, che indicano appunto il numero massimo diagonali creabili, 
    creo al contrario partendo dal fondo le diagonali e prendo le migliori 3 compatibili, dove metto la migliore in 3 posizione 
    per prendere il bonus.
*/

/*
Pesco da 3 vettori differenti ordinati per value/difficulty, prendo prima il finale dopo prendo lo start provo,
Creo diversi percorsi che hanno elementi fino a massimo 4 e vedo li ordino per peso anche loro (facendoli diventare dei singoli elementi)
Le chiamo sequenze
*/

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

typedef struct{
    int n; //Numero di elementi
    Elements **e; //Puntatori di elementi
} Sequence;

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
    if(ea->final > eb->final)
        return 1;
    if(ea->final < eb->final)
        return -1;
    if (a_density < b_density) 
        return 1; 
    if (a_density > b_density) 
        return -1; 
    return 0; 
}

void find_best_program_greedy(Elements **e, int *sol[], int n, int DD, int DP){
    int act_dif, tot_dif, c = 0, idx, prev_end_d, prev_acro, final, start;
    float act_value, tot_value, max = 0;
    // int *e_f, *e_s, *e_n;
    int n_f, n_s, n_n;
    n_f = n_s = n_n = 0;
    //Leggo i dati per dividere in 3 diversi vettori.
    // for(int i = 0; i<n; i++){
    //     if(!e[i]->final) n_s++;
    //     else if(e[i]->final) n_f++;
    //     // printf("%d %d\n",elements[i]->prec,elements[i]->final);
    //     // if(elements[i]->final) n_f++;
    // }
    //Prec = 1 -> deve avere un elemento prima
    //Quindi posso inserirli ovunque ma non all'inizio
    // printf("%d elementi che hanno prec ma non final.\n",n_n); // Quindi

    // // Quindi posso inserirli in fondo e aggiungerci cose dietro, o niente se raggiungono gia il massimo
    // printf("%d elementi hanno final\n",n_f); 

    // //Devo metterli all'inizio e poi pesco dal massimo tra quelli che stanno qua e quelli in n_n
    // printf("%d elementi che non hanno final e non hanno prec\n",n_s);
    // e_f = malloc(n_f*sizeof(int));
    // if (!e_f) {
    //     perror("malloc");
    //     free_all(e, n);
    //     return ;
    // }
    // e_s = malloc(n_s*sizeof(int));
    // if (!e_s) {
    //     perror("malloc");
    //     free_all(e, n);
    //     free(e_f);
    //     return ;
    // }
    // e_n = malloc(n_n*sizeof(int));
    // if (!e_n) {
    //     perror("malloc");
    //     free_all(e, n);
    //     free(e_s); free(e_f);
    //     return ;
    // }

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
            // free(e_s); free(e_f); free(e_n);
            return ;
        }
        for(int j = 0; j<N_E_DIAG; j++) tmp[i][j] = -1;
    }
    
    qsort(e, n, sizeof(*e), cmp_elem_by_value_desc);
    // Inizializzo i valori di n_f e n_s.
    for(n_s = 0; n_s<n; n_s++){
        if(e[n_s]->final) break;
    }
    n_f = n-n_s;
    // Quindi posso inserirli in fondo e aggiungerci cose dietro, o niente se raggiungono gia il massimo
    printf("%d elementi hanno final\n",n_f); 

    //Devo metterli all'inizio e poi pesco dal massimo tra quelli che stanno qua e quelli in n_n
    printf("%d elementi che non hanno final\n",n_s);

    // n_f = n_s = n_n = 0;
    // for(int i = 0; i<n; i++){
    //     if(e[i]->prec && !e[i]->final) e_n[n_n++] = i;
    //     else if(e[i]->final) e_f[n_f++] = i;
    //     else e_s[n_s++] = i;
    // }

    // for(int i = 0; i<n; i++){
    //     printf("%.2f ",e[i]->value/e[i]->difficulty);
    //     // printf(" %d",i,e[i]->difficulty);
    //     // printf("%d ",e[i]->final);
    // }
    // printf("\n");
    // for(int i = 0; i<n; i++){
    //     printf("%d ",e[i]->final);
    // }
    // printf("\n");
    // for(int i = 0; i<n; i++) printf("%d: %.2f - %d\n",i, e[i]->value,e[i]->difficulty);

    int valid = 1, has_acro = 0, has_b = 0, has_f = 0, has_acro_seq = 0;
    for(int i = N_DIAG-1; i>=0; i--){
        final = 0;
        for(int j = 0; j<N_E_DIAG; j++) tmp[i][j] = -1;
        tot_dif = 0;
        tot_value = 0;
        // if(!e[(k)%n]->prec) continue; //Non puoi cominciare con questo
        for(int k = n_s; k<n; k++){
            int next_start_d = e[k]->start_dir;
            has_acro = e[k]->type != 0;
            int next_acro = has_acro;
            act_dif = e[k]->difficulty;
            act_value = e[k]->value;
            c = 0;
            tmp[i][c++] = k;
            if(e[k]->type == 1) has_b = 1; 
            if(e[k]->type == 2) has_f = 1;
            for(int j = 0; j<n-n_f; j++){
                if(c == N_E_DIAG) break;

                if(next_start_d != e[j]->end_dir) continue;
            
                int nd = e[j]->difficulty;
                if (act_dif + nd >= DD) continue;
                if (tot_dif + act_dif + nd >= DP) continue;

    // printf("%d ",e[idx]->difficulty);
                //Controlli finali di validità
                if(e[j]->type != 0) has_acro = 1;
                if(e[j]->type != 0 && next_acro) has_acro_seq = 1;
                if(e[j]->type == 1) has_b = 1; 
                if(e[j]->type == 2) has_f = 1; 
                printf("%s %d %.2f - %d\n",e[j]->name,e[j]->difficulty,e[j]->value,act_dif);
                printf("%d %d - %d\n",e[j]->type,has_b,has_f);
                act_dif += nd;
                act_value += e[j]->value;
                next_start_d = e[j]->start_dir;
                next_acro = e[j] != 0 ? 1 : 0;

                tmp[i][c++] = j;
                j = 0;
                // if(e[j]->final) break;
            }
            printf("\n");
            // printf("\n%d - %d - %d\n",i,c,tot_dif);
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
            printf("Aggiungo la diagonale\n");
            // bonus 1.5 sulla “prima” che poi leggerai al contrario
            tot_value += (i == 0) ? act_value * 1.5f : act_value;
            //Controlli su sol[i]

            if (!valid) continue;
            printf("%.2f - %.2f\n",tot_value,max);
            printf("%d - %d - %d\n",has_b , has_f , has_acro_seq);
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
    }


    printf("%.2f\n",max);
    // for(int i = 0; i<n; i++) printf("%d: %.2f\n",i,e[i]->value);
    for(int i= 0; i<N_DIAG; i++) {
        for(int j = 0; j<N_E_DIAG; j++) printf("%f ", sol[i][j] != -1 ? e[sol[i][j]]->value : -1);
        // for(int j = 0; j<N_E_DIAG; j++) printf("%d ",tmp[i][j]);
        printf("\n");
    }

    for (int i = 0; i < N_DIAG; i++) 
        free(tmp[i]);
    free(tmp);
    // free(e_s); free(e_f); free(e_n);

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