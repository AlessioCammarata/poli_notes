/*
Dato un grafo non orientato non pesato G = (V,E) si definisce triangle packing una collezione V1, V2 .. Vk di 
sottoinsiemi disgiunti di vertici, ognuno contenente esattamente tre vertici, 
tali per cui per ogni V_i = {u_i, v_i, w_i} con 1 <= i <= k 
tutti e tre gli archi (u_i, v_i), (u_i, w_i) e (v_i, w_i) esistono e appartengono a E. 

Un triangle packing può non coprire tutti i vertici del grafo. 
Per gli scopi del problema si è interessati all'individuazione di un triangle packing a cardinalità massima.

*/

#include <stdio.h>
#include <stdlib.h>

/*
Strutture dati e acquisizione

Fornire la definizione e implementazione delle strutture dati reputate necessarie a modellare le informazioni del problema, 
quali il grafo e un triangle packing, e le funzioni di acquisizione dei dati stessi. 

In caso di organizzazione delle strutture dati su più file, indicare esplicitamente il modulo di riferimento.
Si assuma che il grafo in input sia riportato in un file di nome grafo.txt, organizzato come segue:
   - Sulla prima riga appare il numero $V$ di vertici
   - Seguono un numero indefinito di righe riportanti coppie $(u, v)$ di interi, con 0 <= u, v < V a rappresentare gli archi del grafo

*/
#define TRIO 3

typedef struct node *link;
struct node{
    int v;
    link next;
};

typedef struct trianglePacking *TP;
struct trianglePacking{
    int *id; //Contiene id dei vertici, inteso a quale gruppo appartengono
    int **trio; //Ad ogni itd corrisponde un triangle packing
    int n;
};

typedef struct graph_s *graph_t;
struct graph_s{
    int V, E;
    link *ladj;
    link z;
    TP tp; //Contiene la struttura per il triangle packing (soluzione finale)
};


/*
Problema di verifica

Data una soluzione proposta, verificare che questa rappresenti effettivamente un triangle packing, 
tenendo in considerazione la definizione teorica proposta in precedenza. 

Si trascuri la richiesta di cardinalità massima in questo contesto. 
La soluzione proposta deve essere letta da file il cui nome e formato è a discrezione del candidato, 
che è tenuto a fornire anche una breve spiegazione dei contenuti del file stesso.
*/

/*
Descrizione file di input:
si chiama solution.txt,
Per me il file letto ha all'inizio il numero di trio che sono presenti nel file e poi si seguito i vari trii di indici
*/

TP readSolution(FILE *f, int V){
    int n;
    if(fscanf(f,"%d",&n) != 1) return NULL;
    TP tp = malloc(sizeof(*tp));
    tp->id = malloc(V*sizeof(int));
    for(int i = 0; i<V; i++) 
        tp->id[i] = -1;
    tp->trio = malloc(n*sizeof(*tp->trio));
    tp->n = n;
    for(int i = 0; i<n; i++){
        int u,v,w;
        tp->trio[i] = malloc(TRIO*sizeof(int));
        if(fscanf(f,"%d %d %d", &u, &v, &w) != 3){
            //Free
            return NULL;
        }

        if(tp->id[u] != -1 || tp->id[v] != -1 || tp->id[w] != -1) {
            printf("Errore: Insiemi non disgiunti (vertice ripetuto).\n");
            return NULL;
        }

        tp->trio[i][0] = u;
        tp->trio[i][1] = v;
        tp->trio[i][2] = w;
        tp->id[u] = tp->id[v] = tp->id[w] = i;
    }

    return tp;
}

int edgeExists(graph_t g, int u, int v) {
    // Scorre la lista di adiacenza di u (assumo che g->z sia la sentinella o NULL)
    for (link t = g->ladj[u]; t != g->z; t = t->next) {
        if (t->v == v) {
            return 1; // Arco trovato
        }
    }
    return 0; // Arco non esiste
}

int checkSolution(graph_t g){
    FILE *fin;
    if((fin = fopen("solution.txt","r")) == NULL){
        perror("Apertura file");
        return 0;
    }
    TP tp = readSolution(fin, g->V);
    fclose(fin);

    if(tp == NULL) 
        return 0;

    for(int i = 0; i<tp->n; i++){
        if(!edgeExists(g, tp->trio[i][0], tp->trio[i][1]) || !edgeExists(g, tp->trio[i][1], tp->trio[i][2]) || !edgeExists(g, tp->trio[i][0], tp->trio[i][2])){
            return 0;
        }
    }

    return 1;
}

/*
Problema di ricerca e ottimizzazione

Identificare, se possibile, un triangle packing a cardinalità massima per il grafo dato in input.
*/

//Utilizzo il partitioning
void findBestTP(graph_t g, int u, int *used, int current_k, int *best_k, int *sol, int *best_sol){
    if(u == g->V){
        if(current_k > *best_k){
            *best_k = current_k;
            for(int i = 0; i<current_k*3; i++){
                best_sol[i] = sol[i];
            }
        }
        return;
    }

    //Pruning - non abbastanza vertici per 
    if(current_k + (g->V - u)/3 <= *best_k)
        return; 

    if(used[u]){
        findBestTP(g, u + 1, used, current_k, best_k, sol, best_sol);
        return;
    }

    //Escludo u
    findBestTP(g, u + 1, used, current_k, best_k, sol, best_sol);

    /*
    Imponendo che v > u e che w > v, tu costringi l'algoritmo a cercare i triangoli solo in ordine strettamente crescente.
    Delle 6 combinazioni viste sopra, l'unica che rispetta la regola 1 < 4 < 5 è la prima. 
    Le altre 5 vengono scartate sul nascere senza far partire la ricorsione.
    */
    for(link x = g->ladj[u]; x != g->z; x = x->next){
        int v = x->v;
        if(v > u && !used[x->v]){
            for(link y = g->ladj[v]; y != g->z; y = y->next){
                int w = y->v;
                //Definisco il triangolo
                if(w > v && !used[w] && edgeExists(g, u, w)){
                    sol[current_k * 3] = u; 
                    sol[current_k * 3 + 1] = v;
                    sol[current_k * 3 + 2] = w;
                    used[u] = 1;
                    used[v] = 1;
                    used[w] = 1;
                    findBestTP(g, u + 1, used, current_k + 1, best_k, sol, best_sol);
                    used[u] = 0;
                    used[v] = 0;
                    used[w] = 0;
                }
            }
        }

    }
}

void bestTP(graph_t g){
    // N.B. g->tp e g->tp->id allocati in GRAPHinit
    int *used = malloc(g->V*sizeof(int));
    int *best_sol = malloc(g->V*sizeof(int));
    int *sol = malloc(g->V*sizeof(int));
    int best_k = 0;

    for(int i = 0; i<g->V; i++){
        used[i] = 0;
        best_sol[i] = -1;
        sol[i] = -1;
    }

    findBestTP(g, 0, used, 0, &best_k, sol, best_sol);

    for(int i = 0; i<best_k; i++){
        g->tp->trio[i][0] = best_sol[i*3];
        g->tp->trio[i][1] = best_sol[i*3 + 1];
        g->tp->trio[i][2] = best_sol[i*3 + 2];
        //Assegnazioni
        g->tp->id[g->tp->trio[i][0]] = g->tp->id[g->tp->trio[i][1]] = g->tp->id[g->tp->trio[i][2]] = i;
    }

    free(sol); free(best_sol); free(used);
}