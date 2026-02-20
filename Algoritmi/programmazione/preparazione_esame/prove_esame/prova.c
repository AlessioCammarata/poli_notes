/*
Descrizione del problema
Un grafo diretto aciclico (DAG) descrive un albero genealogico, in cui i nodi rappresentano persone, caratterizzate da nome
(si usa in questo contesto il termine nome per indicare la coppia cognome-nome), data di nascita e di morte (posta
convenzionalmente a 0/0/0 se la persona è in vita), mentre gli archi diretti rappresentano relazioni genitore-figlio/a.
Si noti che sono possibili persone aventi lo stesso nome: in tal caso si può assumere che la data di nascita sia sufficiente a
identificare una persona in modo univoco.
Si vogliono risolvere un problema di verifica e uno di ottimizzazione, così come specificato nel seguito.
Strutture dati

Si supponga di utilizzare il tipo ADT visto a lezione per i grafi. Si indichi come va estesa la struttura dati per gestire nomi e
date di nascita. È necessario fornire la definizione del tipo Graph. Va definito un tipo Date (quasi ADT), per rappresentare
le date, e un tipo Key, che va usato per la tabella di simboli. Va infine scritta la funzione KEYcmp, che ritorni 0 per
uguaglianza, oppure un risultato <0 o >0 a seconda del confronto tra le chiavi (si confrontano prima i nomi, poi le date di
nascita). Non sono richieste le funzioni di gestione della tabella di simboli, né quelle di gestione del grafo, a meno che
richiedano variazioni per la soluzione del problema proposto.
NON è richiesta la funzione di lettura da file.

*/
#include <stdlib.h>

#define MAXC 30

typedef struct {
    int y,m,d;
} date;

typedef struct {
    // char *name; //Cognome nome, meglio usare un buffer cosi è piu semoplice la lettura dei dati, non bisogna allocare nulla
    char name[MAXC];
    date birth;
} key;

typedef struct parents *p;
struct parents{
    int p1, p2;
};

typedef struct vertex_s *vertex_t;
struct vertex_s{
    key id; //Cognome nome + data nascita se serve
    date death;
    p p;
};

typedef struct node *link;
struct node{
    // vertex_t v; -> si preferisce l'indice di dove si trova nella lista
    int v;
    link next;
};

typedef struct st_s *st_t;

typedef struct graph_s *graph_t;
struct graph_s
{
    int E, V;
    vertex_t *tab; // Usanod una ST questi dati dovrebbero essere interni ad essa
    link *ladj;
    link z;
    st_t st; // -> per mappare key -> indice 
};

int datecmp(date d1, date d2) {
    if (d1.y != d2.y) return d1.y - d2.y;
    if (d1.m != d2.m) return d1.m - d2.m;
    return d1.d - d2.d;
}

int KEYcmp(key v, key w){
    int res = strcmp(v.name,w.name);
    if(res == 0)
        return datecmp(v.birth,w.birth);
    return res;
}

int relationshipK(graph_t G, char *name1, date d1, char *name2, date d2, int k);

/*
Problema di verifica
Date due persone, caratterizzate ognuna da nome e data di nascita, determinare se sono parenti di grado massimo k. Ci sono
due possibilità:
• una delle due è antenata dell’altra e il cammino che le connette nel grafo ha lunghezza <=k
• le persone hanno un/a antenato/a comune e le lunghezze dei due cammini che le connettono all’antenato/a, sommate
tra loro non superano k.
La funzione abbia prototipo:
int relationshipK(Graph G, char *name1, Date d1, char *name2, Date d2, int k);
*/

typedef struct qNode_s *qNode_t;
struct qNode_s{
    int data;
    qNode_t next;
};

typedef struct queue_s{
    qNode_t head, tail;
} *queue_t;

static queue_t queue_init(){
    queue_t q = malloc(sizeof(*q));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

static void qput(queue_t q, int id){
    qNode_t x = malloc(sizeof(*x));
    x->data = id;
    x->next = NULL;

    if(q->tail == NULL){
        q->head = q->tail = x;
    }else{
        q->tail->next = x;
        q->tail = x;
    }
}

static int qget(queue_t q){
    qNode_t x;
    x = q->head;
    int id = x->data;
    q->head = q->head->next;
    if(q->head == NULL)
        q->tail = NULL;
    free(x);
    return id;
}

static int queue_empty(queue_t q) {
    return q->head == NULL;
}

static void qFree(queue_t q){
    qNode_t t;
    for(qNode_t x = q->head; x != NULL; x = t){
        t = x->next;
        free(x);
    }
    free(q);
}

/* Soluzione proposta */

void get_ancestor_distances(graph_t G, int start_node, int *dist, int k) {
    queue_t q = queue_init();
    for(int i = 0; i < G->V; i++) dist[i] = -1;

    dist[start_node] = 0;
    qput(q, start_node);

    while(!queue_empty(q)) {
        int curr = qget(q);

        // Se siamo già a distanza k, non ha senso guardare i genitori
        if (dist[curr] < k) {
            // Prendo i genitori dalla tua struttura vertex_t
            int genitori[2] = { 
                G->tab[curr]->p->p1, 
                G->tab[curr]->p->p2 
            };
            
            for (int i = 0; i < 2; i++) {
                int p = genitori[i];
                // Se il genitore esiste ed è la prima volta che lo vedo
                if (p != -1 && dist[p] == -1) {
                    dist[p] = dist[curr] + 1;
                    qput(q, p);
                }
            }
        }
    }
    qFree(q);
}

int relationshipK(graph_t G, char *name1, date d1, char *name2, date d2, int k) {
    // 1. Trova gli ID tramite ST (Symbol Table)
    int id1 = STsearch(G->st, name1, d1);
    int id2 = STsearch(G->st, name2, d2);
    if (id1 == -1 || id2 == -1) return 0;

    // 2. Alloca array per le distanze dagli antenati
    int *dist1 = malloc(G->V * sizeof(int));
    int *dist2 = malloc(G->V * sizeof(int));

    // 3. Calcola quanto distano gli antenati da id1 e da id2
    get_ancestor_distances(G, id1, dist1, k);
    get_ancestor_distances(G, id2, dist2, k);

    // 4. Controlla se esiste un antenato comune entro il grado k
    // Questo copre sia antenati diretti che cugini/fratelli
    for (int i = 0; i < G->V; i++) {
        if (dist1[i] != -1 && dist2[i] != -1) { // i è un antenato comune
            if (dist1[i] + dist2[i] <= k) {
                free(dist1); free(dist2);
                return 1; // Parenti trovati!
            }
        }
    }

    free(dist1); free(dist2);
    return 0; // Nessuna parentela entro k
}

/*
Problema di ricerca e ottimizzazione
Trovare la persona con più discendenti fino al grado k. Il grado di un/a discendente è la sua distanza dall’antenato/a nel grafo.
È sufficiente che la persona venga stampata. La funzione abbia prototipo
void largestLineageK(Graph G, int k);
ATTENZIONE: il numero di discendenti di grado k di una persona non è calcolabile a partire dai discendenti di grado k
dei figli e delle figlie (e neppure, se lo si fosse calcolato, dei discendenti di grado k-1, perché potrebbero esserci discendenti
comuni. 
*/

int bfs(graph_t G, int start, int k){
    queue_t q = queue_init();
    int n = 0;
    int *dist = malloc(G->V*sizeof(int));
    int *visit = malloc(G->V*sizeof(int));
    for(int i = 0; i<G->V; i++){
        dist[i] = 0;
        visit[i] = 0;
    }
    visit[start] = 1;
    qput(q, start);
    
    while(!queue_empty(q)){
        int id = qget(q);

        // if(dist[v] > k) break; Si esplora a livelli percio il primo nodo per cui è valido,lo sarà anche per i successivi nella coda
        if(dist[id] < k){
            for(link x = G->ladj[id]; x != G->z; x = x->next){
                int w = x->v;
                if(!visit[w]){
                    visit[w] = 1;
                    dist[w] = dist[id] + 1;
                    qput(q, w);
                    n++;
                }
            }
        }
    }
    free(dist); free(visit);
    qFree(q);
    return n;
}

void largestLineageK(graph_t G, int k){
    int id = -1, max = 0;
    for(int i = 0; i<G->V; i++){
        // G->tab[i]; //Nodo da analizzare
        int val = bfs(G, i, k);
        if(val > max){
            max = val;
            id = i;
        }
    }
    if(id != -1)
        printf("La persona con piu discendenti è %s, con ben %d discendenti. Complimenti!\n",G->tab[id]->id.name, max);
    else printf("Non esiste massimo\n");
    /*
    Sarebbe meglio dare il compito alla ST per separazione delle responsabilità, ma il concetto è lo stesso
    key k_max = STsearchByIndex(G->tab,vmax);
    printf("la persona con più discendenza di grado %d è %s\n", k, k_max.name);
    printf("nata il %d/%d/%d\n", k_max.bd.dd,k_max.bd.mm,k_max.bd.yy);
    */
}