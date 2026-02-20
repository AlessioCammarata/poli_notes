#define BUF 21
#define NPRED 2
#include <stdio.h>
#include <stdlib.h>

typedef struct Activity_s *Activity;
struct Activity_s{
    char name[BUF]; //Univoco
    int start, duration, profit;
    char *preds[NPRED]; //Indici dei precedenti
    int n_preds; // 0,1 o 2
};

//Solo nel IBST.c
typedef struct iBSTnode *link;
struct iBSTnode{
    Activity data;
    link l,r;
    int size;
};

typedef struct activities *ACT;
struct activities{
    int NA, NP;
    Activity *vet; //Inizializzato nella init
    link root;
    link z;
};

// ITEMlt per l'albero
// int ITEMlt(Activity a, Activity b) {
//     return strcmp(a->name, b->name) < 0;
// }

char *my_strdup(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

int compareActivitiesByStart(const void *a, const void *b){
    Activity actA = *(Activity *)a;
    Activity actB = *(Activity *)b;
    return actA->start - actB->start;
}

ACT activityRead(FILE *f){ //Si assume che il file sia aperto
    int NA, NP;
    if(fscanf(f,"%d %d",&NA,&NP) != 2 ){
        perror("Formato file errato");
        return NULL;
    }
    ACT ibst = ibstInit(NA,NP);

    for(int i = 0; i<NA; i++){
        Activity act = malloc(sizeof(*act));
        if(act == NULL){
            for(int j = 0; j<i; j++) free(ibst->vet[j]);
            return NULL;
        }
        if(fscanf(f,"%s %d %d %d",act->name, &act->start, &act->duration, &act->profit) != 4){
            for(int j = 0; j<i; j++) free(ibst->vet[j]);
            free(act);
            return NULL;
        }
        for(int j = 0; j<2; j++)
            act->preds[j] = NULL;
        act->n_preds = 0;
        ibst->vet[i] = act;
        IBSTinsert(ibst, act);
    }

    char line[100];
    fgets(line,sizeof(line),f); //Pulisco il buffer
    for(int i = 0; i<NP; i++){
        if(fgets(line,sizeof(line),f) == NULL) break;

        char n_target[BUF], n_p1[BUF], n_p2[BUF];
        int read = sscanf(line, "%s %s %s",n_target, n_p1, n_p2);

        if(read > 1){
            int idx_target = ibstSearchByName(ibst, n_target);
            ibst->vet[idx_target]->preds[0] = my_strdup(n_p1);
            ibst->vet[idx_target]->n_preds = 1;
            if(read == 3){
                ibst->vet[idx_target]->preds[1] = my_strdup(n_p2);
                ibst->vet[idx_target]->n_preds++;
            }
        }
    }
    //Le ordino in base all'inizio per la ricerca successiva
    qsort(ibst->vet, ibst->NA, sizeof(Activity), compareActivitiesByStart);
    return ibst;
}

int checkSelection(ACT a, char **selected, int nsel); 

/*
Si scriva una funzione avente prototipo 
int checkSelection(ACT a, char **selected, int nsel); 
che, date le attività e un sottoinsieme selezionato, rappresentato da un elenco di nomi 
(e dal relativo numero), verifichi se la selezione è compatibile con i vincoli del problema. 
La selezione non deve necessariamente essere ottima.
*/

int checkSelection(ACT a, char **selected, int nsel){
    if(a == NULL || selected == NULL) return -1; //Oppure 0

    Activity *choices = malloc(nsel * sizeof(Activity));
    for (int i = 0; i < nsel; i++) {
        int id = IBSTsearchByName(a, selected[i]); // Restituisce l'indice in a->vet
        if (id == -1) { //Non esiste l'attvità in questione 
            free(choices); 
            return 0; 
        }
        choices[i] = a->vet[id];
    }

    //Controllo se rispettano il tempo
    for(int i = 0; i<nsel; i++){
        for(int j = 0; j < nsel; j++){
            int end_i = choices[i]->start + choices[i]->duration;
            int end_j = choices[j]->start + choices[j]->duration;
        
            //Se si overlappano non vanno bene
            if(!(end_i <= choices[j]->start || end_j <= choices[i]->start)){
                free(choices);
                return 0;
            }
        }
    }

    //Controllo precedenze
    for(int i = 0; i<nsel; i++){
        for(int p = 0; p < choices[i]->n_preds; p++){
            char *requested_name = choices[i]->preds[p];
            int found = 0;

            for(int k = 0; k<nsel; k++){
                if(strcmp(choices[k]->name, requested_name) == 0){
                    int end = choices[k]->start + choices[k]->duration;
                    if(end <= choices[i]->start){
                        found = 1;
                    }
                    break;
                }
            }

            if(!found){
                free(choices);
                return 0; //Precedenza non soddisfatta
            }
        }
    }

    int profit = 0;
    for(int i = 0; i<nsel; i++){
        profit += choices[i]->profit;
    }

    free(choices);
    return profit;
}


/*
Si scriva la funzione bestSelection, che, date le attività e i vincoli, 
determini un sottoinsieme ottimo di attività tale da rispettare i vincoli. 
La funzione deve tornare l’elenco delle attività selezionate 
(un vettore di nomi e il numero di attività), ordinate per tempo di inizio, 
nonché il profitto complessivo ottenuto.

Si noti che nell’esempio proposto il massimo profitto è 250, 
ottenuto selezionando Act1 e Act4, nonostante esista una sequenza compatibile 
più lunga/numerosa (Act1, Act2, Act3) ma con profitto inferiore (170).
*/

int isCompatible(ACT a, int pos, int *sol) {
    Activity curr = a->vet[pos];

    for (int i = 0; i < pos; i++) {
        if (sol[i]) { // Se l'attività i è stata selezionata
            Activity prev = a->vet[i];

            // Controllo Sovrapposizione Temporale
            int end_curr = curr->start + curr->duration;
            int end_prev = prev->start + prev->duration;
            if (curr->start < end_prev && prev->start < end_curr) {
                return 0; // Incompatibile: si sovrappongono
            }
        }
    }

    // 2. Controllo Precedenze
    for (int j = 0; j < curr->n_preds; j++) {
        char *required = curr->preds[j];
        int found = 0;
        for (int i = 0; i < pos; i++) {
            // Cerchiamo se il predecessore è stato preso E finisce prima
            if (sol[i] && strcmp(a->vet[i]->name, required) == 0) {
                if (a->vet[i]->start + a->vet[i]->duration <= curr->start) {
                    found = 1;
                }
                break;
            }
        }
        if (!found) return 0; // Incompatibile: manca un predecessore o tempo errato
    }

    return 1;
}

void solve_r(int pos, ACT a, int *sol, int *best_sol, int *max_profit, int sum){
    if(pos >= a->NA){
        if(sum > *max_profit){
            *max_profit = sum;
            for(int i = 0; i < a->NA; i++){
                best_sol[i] = sol[i];
            }
        }
        return;
    }

    if(isCompatible(a, pos, sol)){
        sol[pos] = 1;
        solve_r(pos +1, a, sol, best_sol, max_profit, sum + a->vet[pos]->profit); 
        sol[pos] = 0;
    }
    solve_r(pos +1, a, sol, best_sol, max_profit, sum);
    return;
}

//Names passato by value, n by reference
char **bestSelection(ACT a, int *n){
    int *sol = calloc(a->NA, sizeof(int));
    int *best_sol = calloc(a->NA, sizeof(int));
    int max_profit = 0;
    *n = 0;

    solve_r(0, a, sol, best_sol, &max_profit, 0);

    for(int i = 0; i<a->NA; i++)
        if(best_sol[i])
            (*n)++; 
    
    if (*n == 0) {
        free(sol);
        free(best_sol);
        return NULL; 
    }
    
    char **names = malloc((*n)*sizeof(*names));
    if(names == NULL){
        free(sol);
        free(best_sol);
        return NULL;
    }

    int c = 0;
    for(int i = 0; i<a->NA; i++){
        if(best_sol[i]){
            names[c++] = a->vet[i]->name; //Uso gli stessi elementi nell'ADT
        }
    }

    free(sol);
    free(best_sol);
    return names;
}