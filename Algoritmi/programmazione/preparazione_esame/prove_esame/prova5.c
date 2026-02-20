/*
Ecco il testo trascritto integralmente dall'immagine:

**Descrizione del problema**

Un campus universitario comprende più edifici, dotati ognuno di una rete locale (LAN). Si vogliono realizzare nuove connessioni in fibra ottica, 
che permettano di espandere le LAN in modo che comprendano più edifici. Le connessioni in fibra ottica possono essere fatte solo tra coppie selezionate 
di edifici (quindi non tutte) e hanno ognuna un costo.

Dato il grafo (non orientato e pesato, coi costi) delle possibili connessioni, si vuole fare in modo che ogni componente connessa 
del grafo (non si garantisce infatti che il grafo sia connesso) diventi un'unica LAN, realizzando un sotto-insieme delle possibili connessioni, 
in modo tale che siano soddisfatti i seguenti criteri:

* per ogni componente connessa, vanno scelti solo archi appartenenti a un albero ricoprente (spanning tree)
* gli alberi ricoprenti vanno scelti in modo che, detti Cmin, Cmax e Cavg i costi minimo, massimo e medio (media aritmetica) delle connessioni selezionate, 
si minimizzi il valore dell'espressione 0.6*Cavg + 0.4*(Cmax-Cmin).

**Struttura dati**

Si utilizzi come struttura dati un grafo standard, realizzato con liste di adiacenza. 
Non è richiesta una funzione di input, in quanto si può supporre di utilizzare una GRAPHload standard. 
Si richiede unicamente la definizione della struct wrapper utilizzata per il grafo.
Si richiede poi di definire una opportuna struttura dati (o una modifica della struttura dati esistente per il grafo) che permetta, 
nella soluzione del problema di ottimizzazione, di disabilitare (o rimuovere temporaneamente) un arco oppure abilitarlo (dopo averlo precedentemente disabilitato): 
la struttura dati va aggiunta all'ADT Graph e vanno scritte le due funzioni GRAPHedgeDisable(Graph g, Edge e), e GRAPHedgeEnable(Graph g, Edge e).

Si definisca, come ADT di prima classe, una struttura dati CC, in grado di rappresentare le componenti connesse del grafo (per ogni componente l'elenco dei vertici appartenenti alla componente) , e si realizzi la funzione CC CCgen(GRAPH g), che, dato il grafo, calcoli le componenti connesse.

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex_s *link;
struct vertex_s{
    int id, w;
    link next;
    // int enable;
};

typedef struct edge_s *Edge;
struct edge_s{
    int u, v;
    int w; //peso
};

typedef struct graph_s *Graph;
struct graph_s{
    int V, E;
    link *ladj;
    link z;
    int **enabled; //Per ogni elemento dici se prenderlo o no
};

typedef struct component *CC;
struct component{
    link *ccNodes;
    link z;
    int n;
};

int GRAPHedgeDisable(Graph g, Edge e){
    int found = 0;
    for(link x = g->ladj[e->u]; x != g->z; x = x->next){
        if(x->id == e->v){
            found = 1;
        }
    }

    if(!found)
        return 0;

    g->enabled[e->u][e->v] = 0;
    return 1;
}

int GRAPHedgeEnable(Graph g, Edge e){
    int found = 0;
    for(link x = g->ladj[e->u]; x != g->z; x = x->next){
        if(x->id == e->v){
            found = 1;
        }
    }

    if(!found)
        return 0;

    g->enabled[e->u][e->v] = 1;
    return 1;
}

void findCC(Graph g, int id, int *visited, CC cc, int nCC){ //Dfs
    visited[id] = 1;
    
    link newNode = malloc(sizeof(struct vertex_s));
    newNode->id = id;
    newNode->next = cc->ccNodes[nCC]; 
    cc->ccNodes[nCC] = newNode;

    for(link x = g->ladj[id]; x != g->z; x = x->next){
        if(g->enabled[id][x->id] && !visited[x->id]){
            findCC(g, x->id, visited, cc, nCC);
        }
    }
}

CC ccGen(Graph g){
    int *visited = calloc(g->V,sizeof(int));
    int nCC = 0;
    CC cc = CCinit(g->V);

    for(int i = 0; i<g->V; i++){
        if(!visited[i]){
            findCC(g, i, visited, cc, nCC);
            nCC++;
        }
    }
    
    free(visited);
    cc->n = nCC;
    return cc;
}
/*
**Problema di verifica**
Si scriva una funzione in grado di verificare se un elenco di archi, ricevuto come parametro, 
contenga tutti e soli gli archi appartenenti a un insieme di alberi ricoprenti (uno per ogni componente connessa). 
La funzione abbia prototipo GRAPHcheckTreeEdges(Graph g, CC comp, Edge *ev, int en);
*/

typedef struct UnionFind *UF;
struct UnionFind {
    int *id;    // Array dei padri
    int *sz;    // Dimensione del sottoalbero (per bilanciamento)
    int n;
};

UF UFinit(int n) {
    UF uf = malloc(sizeof(*uf));
    uf->id = malloc(n * sizeof(int));
    uf->sz = malloc(n * sizeof(int));
    uf->n = n;
    for (int i = 0; i < n; i++) {
        uf->id[i] = i; // All'inizio ogni nodo è padre di se stesso
        uf->sz[i] = 1;
    }
    return uf;
}

// Funzione interna per trovare la radice con compressione dei cammini
static int find(UF uf, int i) {
    while (i != uf->id[i]) {
        uf->id[i] = uf->id[uf->id[i]]; // Path compression (dimezza il cammino)
        i = uf->id[i];
    }
    return i;
}

int UFfind(UF uf, int p, int q) {
    return find(uf, p) == find(uf, q);
}

void UFunion(UF uf, int p, int q) {
    int i = find(uf, p);
    int j = find(uf, q);
    if (i == j) return;
    
    // Weighted Union: attacca l'albero più piccolo sotto quello più grande
    if (uf->sz[i] < uf->sz[j]) {
        uf->id[i] = j; 
        uf->sz[j] += uf->sz[i];
    } else {
        uf->id[j] = i; 
        uf->sz[i] += uf->sz[j];
    }
}

void UFfree(UF uf) {
    free(uf->id);
    free(uf->sz);
    free(uf);
}

int GRAPHcheckTreeEdges(Graph g, CC comp, Edge *ev, int en) {
    // 1. Controllo preliminare sul numero di archi
    // Una foresta ricoprente ha sempre (V - numero_componenti) archi
    if (en != (g->V - comp->n)) {
        return 0; 
    }

    // Creiamo un array d'appoggio per sapere subito ogni vertice a che CC appartiene
    // Questo evita i cicli infiniti sulle liste di CC
    int *vertex_to_cc = malloc(g->V * sizeof(int));
    for (int i = 0; i < comp->n; i++) {
        for (link x = comp->ccNodes[i]; x != NULL; x = x->next) {
            vertex_to_cc[x->id] = i;
        }
    }

    // Inizializziamo Union-Find per il controllo dei cicli
    UF uf = UFinit(g->V); 

    for (int k = 0; k < en; k++) {
        int u = ev[k]->u;
        int v = ev[k]->v;

        // 2. Controllo Appartenenza: u e v devono stare nella stessa componente
        if (vertex_to_cc[u] != vertex_to_cc[v]) {
            UFfree(uf);
            free(vertex_to_cc);
            return 0; // Errore: l'arco scavalca due componenti diverse
        }

        // 3. Controllo Cicli: se u e v sono già connessi, aggiungere questo arco crea un ciclo
        if (UFfind(uf, u, v)) {
            UFfree(uf);
            free(vertex_to_cc);
            return 0; // Errore: si è formato un ciclo
        }
        UFunion(uf, u, v); //Unisco all'albero che sto costruendo (nella scc specifica)
    }

    free(vertex_to_cc);
    UFfree(uf);
    return 1; // Se arriviamo qui, è una foresta ricoprente valida
}
/*
**Problema di ricerca e ottimizzazione**

Si scriva una funzione che, dato il grafo e le relative componenti connesse, permetta di trovare gli alberi ricoprenti, 
secondo il criterio di ottimizzazione richiesto. Si fa notare che, non trattandosi solo di minimizzare la somma dei pesi degli archi, 
le funzioni standard per calcolo di MST (alberi ricoprenti minimi) non possono essere utilizzate. 
È pertanto necessario realizzare un algoritmo ricorsivo in grado di trovare l'insieme ottimo di archi. 
La funzione deve corrispondere al prototipo seguente

Edge *GRAPHgenOptTrees(Graph g, CC comp);

Si chiede inoltre di specificare il modello di calcolo combinatorio usato e lo spazio in cui si cercano le soluzioni. 
Si dica inoltre se la funzione di ottimizzazione viene applicata ad ogni componente connessa individualmente 
(unendo successivamente le soluzioni ottime trovate) oppure su tutto il grafo (le risposta va motivata).

**ATTENZIONE**

Si noti che la differenza (Cmax-Cmin) non fa riferimento a ogni componente connessa ma a tutto il grafo (minimo e massimo potrebbero infatti 
appartenere a due diverse componenti connesse), il che ha conseguenze sulla scelta dell'algoritmo di ottimizzazione.
Si noti poi che, benché la funzione GRAPHcheckTreeEdges possa essere sufficiente per verificare l'eventuale ammissibilità di un sottoinsieme di archi, 
l'eventuale strategia adottata per il pruning sarà oggetto di valutazione.
*/
#include <limits.h>

/*
Sarebbe opportuno fare pruning attraverso la UF, il problema in questo caso non sta nella UFunion ma nel tornare indietro e cancellare la Union.
Dovresti o memorizzare lo stato precedente in modo da poter tornare indietro oppure ricostruire la UF ad ogni passo.
Sarebbe utile togliere la path compression all'interno della UF cosi da poter tornare indietro al parent.
*/

// int find(UF uf, int i) {
//     while (i != uf->id[i])
//         i = uf->id[i];
//     return i;
// }
// // Una funzione Union speciale che restituisce quale nodo è stato "appeso"
// // Restituisce l'indice del nodo modificato, o -1 se erano già connessi
// int UFrelax(UF uf, int p, int q) {
//     int i = find(uf, p);
//     int j = find(uf, q);
//     if (i == j) return -1;

//     // Union by Size: appendiamo l'albero piccolo al grande
//     if (uf->sz[i] < uf->sz[j]) {
//         uf->id[i] = j;
//         uf->sz[j] += uf->sz[i];
//         return i; // i è il nodo che è stato "appeso" a j
//     } else {
//         uf->id[j] = i;
//         uf->sz[i] += uf->sz[j];
//         return j; // j è il nodo che è stato "appeso" a i
//     }
// }
// void UFrollback(UF uf, int child) {
//     if (child == -1) return;
//     uf->sz[uf->id[child]] -= uf->sz[child]; // Sottraiamo la dimensione
//     uf->id[child] = child;                 // Il figlio torna a essere radice
// }

void findMSTr(int pos, int start, Edge *vet, int n_tot_E, int *sol, int k, int act_max, int act_min, int sum, float *min, int *best_sol, CC comp, Graph g){
    if(pos >= k){
        Edge *temp_ev = malloc(k * sizeof(Edge));
        for (int i = 0; i < k; i++) {
            temp_ev[i] = vet[sol[i]]; // vet[sol[i]] è l'arco i-esimo scelto
        }
        if (GRAPHcheckTreeEdges(g, comp, temp_ev, k)) {
            float val = 0.6*((float)sum/k) + 0.4*(act_max-act_min);
            if(*min < 0 || val < *min){
                *min = val;
                for(int i = 0; i<k; i++){
                    best_sol[i] = sol[i];
                }
            }
        }
        FREE(temp_ev);
        return;
    }

    for(int i = start; i<n_tot_E; i++){

        // if (UFfind(uf, vet[i].u, vet[i].v)) {
        //     continue; // Potatura: questo arco creerebbe un ciclo, salto l'intero ramo
        // }
        // int root_u = find(uf, vet[i].u);
        // int root_v = find(uf, vet[i].v);
        //Oppure
        // if (find(uf, vet[i].u) == find(uf, vet[i].v)) continue;
        
        // // Uniamo root_u a root_v (assumendo root_v come nuovo padre)
        // uf->id[root_u] = root_v;
        //Oppure
        // int root_modified = UFrelax(uf, vet[i].u, vet[i].v);

        int new_max = vet[i]->w > act_max ? vet[i]->w : act_max;
        int new_min = vet[i]->w < act_min ? vet[i]->w : act_min;

        sol[pos] = i;
        findMSTr(pos+1, i+1, vet, n_tot_E, sol, k, new_max, new_min, sum + vet[i]->w, min, best_sol, comp, g);
        // uf->id[root_u] = root_u;
        //Oppure
        // UFrollback(uf, root_modified);
    }

    return;
}

/*Minimizza 0.6*Cavg + 0.4*(Cmax-Cmin)*/
Edge *GRAPHgenOptTrees(Graph g, CC comp) {
    int target = g->V - comp->n;
    int n_archi = 0;
    
    // 1. Allocazione vettore archi (usiamo struct per semplicità di gestione memoria)
    // Se Edge è typedef struct edge_s*, usiamo struct edge_s per l'array
    struct edge_s *vettoreArchi = malloc(g->E * sizeof(struct edge_s));
    
    // 2. Estrazione archi dal grafo - Creo un vettore di archi dal grafo
    for (int v = 0; v < g->V; v++) {
        for (link x = g->ladj[v]; x != g->z; x = x->next) {
            // Prendiamo l'arco una sola volta e solo se abilitato
            if (v < x->id && g->enabled[v][x->id]) { 
                vettoreArchi[n_archi].u = v;
                vettoreArchi[n_archi].v = x->id;
                vettoreArchi[n_archi].w = x->w;
                n_archi++;
            }
        }
    }

    int *sol = malloc(target * sizeof(int));
    int *best_sol = malloc(target * sizeof(int)); 
    float min_val = -1.0f;
    UF uf = UFinit(g->V); // Inizializziamo la Union-Find

    // Parametri: pos, start, vettore, n_tot, sol, k, max, min, sum, best_val, best_sol, uf
    findMSTr(0, 0, vettoreArchi, n_archi, sol, target, -1, 1000000, 0, &min_val, best_sol, comp, g);

    // 5. Creazione del risultato finale da restituire
    Edge *res = malloc(target * sizeof(Edge));
    for (int i = 0; i < target; i++) {
        res[i] = malloc(sizeof(*res[i]));
        *res[i] = vettoreArchi[best_sol[i]];
    }

    // Cleanup memoria temporanea
    UFfree(uf); free(vettoreArchi); free(sol); free(best_sol);

    return res;
}

