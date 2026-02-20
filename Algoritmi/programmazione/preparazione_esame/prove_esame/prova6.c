/*
Si vuole risolvere un problema di pianificazione di attività. 
È dato un elenco di attività. Ogni attività è caratterizzata da nome (stringa di non più di 20 caratteri), tempo di inizio, tempo di fine e costo. 
È poi dato un elenco di dipendenze, ognuna data da due attività: 
la dipendenza $(A_j, A_k)$ indica che l'attività $A_j$ non può iniziare prima che sia terminata $A_k$.

EsempioElenco attività: 
    (A1A,1,4,12), (BB75,12,14,270), (AB12B,0,6,201), (ADD,5,7,45), (A4,3,5,36), (CNT3,5,9,74), (T3B,8,11,130), (YA,6,10,103)
Elenco precedenze: 
    (ADD,A1A), (T3B,ADD), (T3B,AB12B), (CNT3,A4)
    
Ogni attività deve essere eseguita da una persona, più attività possono essere eseguite in (parziale o totale) sovrapposizione nel tempo, 
purché siano assegnate a un numero sufficiente di persone: l'inizio di un'attività nel tempo in cui ne termina un'altra non va considerato come sovrapposizione. 
Si vuole verificare che le attività possano essere eseguite e si vuole determinare un'assegnazione ottima di attività a persone.
*/

/*
Si definisca, come ADT di prima classe, una struttura dati ACT, in grado di rappresentare le attività e le dipendenze 
e di risolvere (nel modo più efficiente possibile), i problemi che seguono. 

Attenzione: non è richiesta alcuna lettura di file o funzione di inizializzazione/allocazione, sono solo richieste le definizioni dei tipi di dato.
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXC 21 //Supponendo nomi non piu lunghi di 20 caratteri
/*Attività: nome, inizio, fine, costo*/
/*Dipendenze: nome1, dipendenza -> nome1 per iniziare, la sua dipendenza deve essere conclusa*/ 
typedef struct st_s *st_t;
typedef struct graph_s *GRAPH;

typedef struct activity{
    char name[MAXC];
    int start, end, cost;
    int worker_id; // per l'assegnazione
} *activity_t;

typedef struct vertex_s *link;
struct vertex_s{
    // activity_t activity;
    int v;
    link next;
};

typedef struct activities *ACT;
struct activities{
    st_t st; //Simble table per associare nome a id
    activity_t *vet;
    link *ldep; //Liste di dipendenza
    link z;
    int V,E;
};



/*
Si scriva una funzione in grado di verificare se un elenco di attività e delle relative dipendenze sia fattibile, 
cioè che nessuna attività inizi prima del termine delle attività da cui dipende: per l'esempio proposto, l'eventuale precedenza (ADD,AB12B) 
farebbe fallire la verifica. 
Si realizzi una seconda funzione che, se la precedente verifica ha avuto successo, 
determini se il grafo delle dipendenze sia un DAG (grafo diretto aciclico) oppure un albero radicato (o foresta) di alberi radicati: 
a tale scopo si noti che una dipendenza (X,Y), in cui l'attività X dipende dalla Y, va intesa come arco orientato X->Y. 

La funzione stampi, oltre al risultato della verifica, nel caso di un DAG le sorgenti (source) e i pozzi (sink), nel caso di albero (o foresta) la(e) radice(i) e le foglie: 
quindi una foglia di albero (o sink/pozzo di DAG) è un'attività priva di dipendenze (ragionamento duale per radici/sorgenti).

Le funzioni richieste abbiano prototipi
int ACTcheckDep(ACT a);
void ACTprintSrcSnk(ACT a);
*/

int ACTcheckDep(ACT a){
    /*Devo controllare che per ogni attività, la sua dipendenza finisca prima di lei che comincia*/
    for(int i = 0; i<a->V; i++){
        for(link x = a->ldep[i]; x!=a->z; x = x->next){
            if(a->vet[i]->start < a->vet[x->v]->end)
                return 0;
        }
    }

    return 1;
}

void dfs(ACT a, int id, int *sinks, int *visited){
    int flag = 0;
    visited[id] = 1;

    for(link x = a->ldep[id]; x != NULL; x->next)
        if(!visited[x->v]){
            flag = 1;
            dfs(a, x->v, sinks, visited);
        }
}

void ACTprintSrcSnk(ACT a){
    if(a == NULL || !ACTcheckDep(a)) return;

    printf("La seguente soluzione è valida\n");
    int *in_degree = malloc(a->V*sizeof(int));
    int *out_degree = malloc(a->V*sizeof(int));
    //Controlli malloc
    int isForest = 1;
    for(int i = 0; i<a->V; i++){
        out_degree[i] = 0;
        in_degree[i] = 0;
    }

    // Calcolo dei gradi scorrendo tutte le liste di adiacenza
    for (int i = 0; i < a->V; i++) {
        for (link x = a->ldep[i]; x != a->z; x = x->next) {
            out_degree[i]++;      // i dipende da qualcun altro
            in_degree[x->v]++;    // qualcun altro dipende da x->v
        }
        // Se un'attività ha più di una dipendenza, non è una foresta
        if (out_degree[i] > 1) isForest = 0;
    }
    
    if(!isForest) printf("Il grafo è un DAG\n");
    else printf("Il grafo è un albero radicato\n");
    
    // Stampa Sorgenti (Source) / Radici: in-degree == 0
    printf("Sorgenti/Radici: ");
    for (int i = 0; i < a->V; i++) 
        if (in_degree[i] == 0) 
            printf("%s ", a->vet[i]->name);
    printf("\n");

    // Stampa Pozzi (Sink) / Foglie: out-degree == 0
    printf("\nPozzi/Foglie: ");
    for (int i = 0; i < a->V; i++) 
        if (out_degree[i] == 0) 
            printf("%s ", a->vet[i]->name);
    printf("\n");
    free(in_degree); free(out_degree);
}

/*
Si scriva una funzione ACTminPers che, dato un elenco di attività, determini il minimo numero di persone N${min}$ in grado di svolgerle tutte. 
Si scriva infine una funzione ACTbestPlan che calcoli un'assegnazione ottima di attività alle N${min}$ persone: la persona P$_j$ riceverà come compenso CP$j$, 
la somma dei costi delle attività svolte/assegnate a P$j$. Il criterio di ottimizzazione è dato dal distribuire i compensi nel miglior modo possibile, 
cioè in modo che sia minimo $SUM_j(|CP_j - CP{avg}|)$, indicando con CP${avg}$ la media aritmetica dei CP$_j$. 

La ripartizione delle attività va memorizzato nella struttura dati (l'ADT): non è quindi necessario che sia stampata.
Le funzioni abbiano prototipo
int ACTminPers(ACT a);
void ACTbestPlan(ACT a);
*/
#include <float.h> // Per FLT_MAX
#include <math.h>

int compareInts(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int ACTminPers(ACT a){
    int *starts = malloc(a->V * sizeof(int));
    int *ends = malloc(a->V * sizeof(int));
    for (int i = 0; i < a->V; i++) {
        starts[i] = a->vet[i]->start;
        ends[i] = a->vet[i]->end;
    }

    qsort(starts, a->V, sizeof(int), compareInts);
    qsort(ends, a->V, sizeof(int), compareInts);
    int i = 0, j = 0, n_pers = 0, max_pers = 0;
    /*
    [0,1,2,3,4,5,6,7,8]
    [4,7,8,10,11,12,15,17,18] 
    In questo esempio servono 4 persone perche 0, 1, 2, 3 sono < 4
    */
    while (i < a->V) {
        if (starts[i] < ends[j]) {
            n_pers++;
            if (n_pers > max_pers) max_pers = n_pers;
            i++;
        } else {
            // Un'attività è finita, una persona si libera, cosi possiamo contare globalmente il totale
            n_pers--;
            j++;
        }
    }
    free(starts); free(ends);
    return max_pers;
}

void partR(int pos, int *sol, int k, ACT a, int *best_sol, int *costs, float *best_diff, float avg){
    if(pos >= a->V){
        float current_diff = 0;
        for(int j = 0; j<k; j++){
            current_diff += fabsf(costs[j]-avg);
        }

        if(current_diff < *best_diff){
            *best_diff = current_diff;
            for(int j = 0; j<a->V; j++) 
                best_sol[j] = sol[j]; 
        }
        return;
    }

    for(int i = 0; i<k; i++){

        //Pruning 
        int overlap = 0;
        for(int j = 0; j<pos; j++){
            if (sol[j] == i) {
                // Controllo sovrapposizione temporale
                /*Guardo se tra le attività assegnate prima ne ho assegnata qualcuna che si sovrappone alla stessa persona*/
                if (a->vet[pos]->start < a->vet[j]->end && a->vet[j]->start < a->vet[pos]->end) {
                    overlap = 1; 
                    break;
                }
            }
        }

        if(overlap) 
            continue;

        sol[pos] = i;
        costs[i] += a->vet[pos]->cost;
        partR(pos+1, sol, k, a, best_sol, costs, best_diff, avg);
        costs[i] -= a->vet[pos]->cost;
    }
    return;
}

void ACTbestPlan(ACT a){
    int n_pers = ACTminPers(a);
    int *sol = malloc(a->V*sizeof(int));
    int *best_sol = malloc(a->V*sizeof(int));
    int *costs = calloc(n_pers,sizeof(int));
    float best_diff = FLT_MAX;
    float avg = 0;
    for(int i = 0; i<a->V; i++){
        avg += a->vet[i]->cost;
    }
    avg = avg/n_pers;

    partR(0, sol, n_pers, a, best_sol, costs, &best_diff, avg);

    for(int i = 0; i<a->V; i++){
        a->vet[i]->worker_id = best_sol[i]; //Memorizzo la soluzione
    }

    free(sol); free(best_sol); free(costs);
    return;
}