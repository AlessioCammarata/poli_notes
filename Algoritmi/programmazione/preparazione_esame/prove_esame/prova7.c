/*
E' dato un insieme di N oggetti, ognuno caratterizzato da costo, peso e volume: un file di testo contiene, per ogni oggetto, su una riga, 4 campi separati da spazi: 
il nome (stringa univoca, priva di spazi di massimo 30 caratteri), il costo, il peso e il volume (tre numeri reali).

E' dato un secondo file in cui sono riportati, uno per riga, dei vincoli tra coppie di oggetti: 
ogni riga del file contiene due nomi di oggetti vincolati fra loro (un oggetto può comparire nessuna o più volte nel file).
Occorre pianificare il trasporto degli oggetti, tenendo conto che è disponibile un solo mezzo di trasporto con capienza massima sia in peso (Pmax) che in volume (Vmax).

Il mezzo può essere riempito una sola volta al giorno (il carico giornaliero), per il conseguente trasporto giornaliero: 
il carico giornaliero non deve superare dati limiti di peso e volume.

Coppie di oggetti vincolati vanno trasportate insieme nello stesso carico giornaliero.
Si vuole organizzare la distribuzione degli oggetti in più carichi giornalieri, minimizzando il numero di carichi (cioè di giorni) necessari. 
A parità di giorni, si vuole minimizzare la differenza tra il costo complessivo massimo per un giorno e quello minimo (relativo a un altro giorno).
*/


/*
Rappresentare come ADT di I classe:
- L'elenco degli oggetti (OBJECTS)  
- Vincoli (CONSTRAINTS)  
- Una soluzione al problema di ottimizzazione (SOL)  
*/

#include <stdio.h>
#define MAXC 31

typedef struct constraints_s *CONSTRAINTS;
struct constraints_s{
    int *group_id; //Tutti quelli che hanno stesso is devono viaggiare insieme
    int num_groups;
};  

typedef struct object_s{
    char name[MAXC];
    float cost, weight, volume; //Weight and volume
} *object_t;

typedef struct objects_s *OBJECTS;
struct objects_s{
    object_t *list;
    int n;
};

typedef struct solution_s *SOL;
struct solution_s{
    int *day_assigned;
    int n_days;
    float best_diff;   // La differenza minima tra il giorno che costa di più e quello che costa di meno
};

/*
Un insieme di oggetti è valido se la capienza del mezzo di trasporto (volume e peso) è tale da poter contenere nello stesso carico
tutti gli oggetti che, in base ai vincoli, debbono stare insieme.
Si scriva una funzione di verifica che, dato un elenco degli oggetti (OBJECTS), un insieme di vincoli (CONSTRAINTS) 
e due numeri indicanti peso e capienza massima, verifichi la validità.
*/

int checkValidity(OBJECTS objs, CONSTRAINTS c, float maxP, float maxV){
    float *group_weight = malloc(c->num_groups*sizeof(float));
    float *group_volume = malloc(c->num_groups*sizeof(float));
    int valid = 1;
    for(int i = 0; i<c->num_groups; i++){
        group_volume[i] = 0;
        group_weight[i] = 0;
    }

    for(int i = 0; i<objs->n && valid; i++){
        int id = c->group_id[i];
        group_weight[id] += objs->list[i]->weight;
        group_volume[id] += objs->list[i]->volume;
        if(group_weight[id] > maxP || group_volume[id] > maxV)
            valid = 0;
    }

    free(group_volume); free(group_weight);
    return valid;
}

/*
Scrivere una funzione ricorsiva in grado di individuare, a partire da un elenco di oggetti (tipo OBJECTS), un insieme di vincoli (tipo CONSTRAINTS), 
e due numeri indicanti peso e capienza massima, la distribuzione ottima degli oggetti in più carichi giornalieri.

Si deve minimizzare il numero di carichi (cioè di giorni) necessari. 
A parità di giorni, si minimizzi la differenza tra il costo complessivo massimo per un giorno e quello minimo (relativo a un altro giorno). 
Il costo relativo a un carico/giorno è la sommatoria degli oggetti inseriti nel carico.

Il modello del calcolo combinatorio scelto va indicato e spiegato/motivato.
*/

#include <float.h>

//Minimizzare il numero di giorni significa avere gruppi piu grandi possibile
//A parità di giorni, bisogna controllare(CAmbiare gruppo agli oggetti) Cmax-Cmin che sia minimo.

void solveR(int pos, int *sol, int k, int n_groups, int *best_sol, float *best_diff, float *day_costs, float *day_weight, float *day_volume, float maxV, float maxP, float *group_weight, float *group_volume, float *group_cost){
    if(pos >= n_groups){
        float max = 0, min = FLT_MAX;
        for(int i = 0; i<k; i++){
            if(day_costs[i] > 0.0f){
                if(day_costs[i] > max) max = day_costs[i];
                if(day_costs[i] < min) min = day_costs[i];
            }
        }
        if(*best_diff > (max-min)){
            *best_diff = max-min;
            for(int i = 0; i<n_groups; i++){
                best_sol[i] = sol[i];
            }
        }
        return;
    }

    for(int i = 0; i<k; i++){

        if(day_weight[i] + group_weight[pos] > maxP || day_volume[i] + group_volume[pos] > maxV) 
            continue; // Se non ci sta, passo al prossimo giorno

        sol[pos] = i;
        day_costs[i]  += group_cost[pos];
        day_weight[i] += group_weight[pos];
        day_volume[i] += group_volume[pos];
        solveR(pos+1, sol, k, n_groups, best_sol, best_diff, day_costs, day_weight, day_volume, maxV, maxP, group_weight, group_volume, group_cost);
        day_costs[i]  -= group_cost[pos];
        day_weight[i] -= group_weight[pos];
        day_volume[i] -= group_volume[pos];

        //Evita di ricreare l'albero della ricorsione per ogni giorno k, (ogni giorno vuoto equivale ad un altro)
        if (day_costs[i] == 0.0f) {
            break; 
        }
    }
}

/*
    Scelgo le partizioni in quanto devo minimizzare valori appartenenti a giorni diversi che posso facilmente indicare con dei gruppi diversi,
    Dividere in gruppi l'insieme di oggetti è proprio il principale motivo di utilizzo delle partizioni.
*/
SOL bestDistribution(OBJECTS objs, CONSTRAINTS c, float maxV, float maxP){ //Wrapper
    float *group_weight = malloc(c->num_groups*sizeof(float));
    float *group_volume = malloc(c->num_groups*sizeof(float));
    float *group_cost = malloc(c->num_groups*sizeof(float));

    for(int i = 0; i<c->num_groups; i++){
        group_weight[i] = 0;
        group_volume[i] = 0;
        group_cost[i] = 0;
    }

    for(int i = 0; i<objs->n; i++){
        group_weight[c->group_id[i]] += objs->list[i]->weight;
        group_volume[c->group_id[i]] += objs->list[i]->volume;
        group_cost[c->group_id[i]] += objs->list[i]->cost;
    }

    // Controllo di sicurezza: se un gruppo sfora da solo, fermiamo tutto
    for(int i = 0; i < c->num_groups; i++){
        if(group_weight[i] > maxP || group_volume[i] > maxV){
            printf("Impossibile: Il gruppo %d supera la capacità del mezzo.\n", i);
            free(group_weight); free(group_volume); free(group_cost);
            return NULL;
        }
    }

    float *day_costs = malloc(c->num_groups*sizeof(float));
    float *day_weight = malloc(c->num_groups*sizeof(float));
    float *day_volume = malloc(c->num_groups*sizeof(float));
    int *sol = malloc(c->num_groups*sizeof(int));
    int *best_sol = malloc(c->num_groups*sizeof(int));
    float best_diff;
    int k_best = -1;

    for(int k = 1; k<=c->num_groups; k++){
        best_diff = FLT_MAX;
        for(int i = 0; i < c->num_groups; i++) {
            day_weight[i] = 0;
            day_volume[i] = 0;
            day_costs[i]  = 0;
        }
        solveR(0, sol, k, c->num_groups, best_sol, &best_diff, day_costs, day_weight, day_volume, maxV, maxP, group_weight, group_volume, group_cost);

        if (best_diff != FLT_MAX) {
            k_best = k;
            break;
        }
    }

    free(group_weight); free(group_volume); free(group_cost); free(day_costs); free(day_weight); free(day_volume); free(sol);

    if(k_best != -1){
        SOL final_sol = malloc(sizeof(*final_sol));
        final_sol->day_assigned = best_sol;
        final_sol->best_diff = best_diff;
        final_sol->n_days = k_best;

        return final_sol;
    }

    free(best_sol);
    return NULL;
}   