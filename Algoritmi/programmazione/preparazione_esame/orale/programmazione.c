#include <stdio.h>

typedef struct st_s *st_t;

typedef struct vertex_s{
    int id;
    char *val;
} *vertex_t;

typedef struct node_s *link; 
struct node_s{
    vertex_t info;
    int weight;        // peso dell'arco (usato nelle liste di adiacenza)
    link next;
};
typedef struct graph_s *graph_t;
struct graph_s
{
    int V, E;
    vertex_t *nodes;
    link *ladj;
    link z; // sentinalle
    st_t tab;
};

// Fare una funzione che riconosce se un grafo è un DAG
void dfs(graph_t g, int act_id, int *visited, int *found){
    visited[act_id] = 1; //Grigio inzio esplorazione
    for(link x = g->ladj[act_id]; x != g->z; x = x->next){
        int next_id = x->info->id;
        if(!visited[next_id])
            dfs(g, next_id, visited, found);
        else if (visited[next_id] == 1){
            *found = 1;
            printf("Trovato arco Back -> non DAG");
            return;
        }
    }
    visited[act_id] = 2; //Nero -> Finito di esplorare
}

int is_dag(graph_t g){
    //Controllo che non ci siano cicli
    int *visited = malloc(g->V*sizeof(int));
    int found = 0;
    for(int i = 0; i<g->V; i++){
        visited[i] = 0; //Metto tutti bianchi
    }

    for(int i = 0; i<g->V; i++)
        if(!visited[i]){
            dfs(g, i, visited, &found);
            if (found) break;
        }

    free(visited);
    return !found;
}

/*
Una griglia è rappresentata mediante una matrice in cui se la casella i,j è piena allora matr[i][j]==1 e se matr[i][j]==0 la casella è vuota. 
Se ci si trova in una casella piena →posso spostarmi verso le altre caselle a N,S,E,O (se i vertici in quelle direzioni esistono, 
ovvero nella matrice il loro valore è 1 e se rispettano le dimensioni della matrice). 
Scrivere una funzione che effettui una dfs completa della griglia tenendo presente questo modo per rappresentare i ‘vertici’ e gli archi (che sono impliciti).
*/

void dfs2(int **grid, int n_dir, int id_r, int id_c, int dim, int dr[], int dc[], int **visited){
    visited[id_r][id_c] = 1;

    for(int i = 0; i<n_dir; i++){
        int new_id_r = id_r + dr[i];
        int new_id_c = id_c + dc[i];
        if(new_id_r < 0 || new_id_c < 0 || new_id_c >= dim || new_id_r >= dim)
            continue;

        if(!visited[new_id_r][new_id_c] && grid[new_id_r][new_id_c])
            dfs2(grid, n_dir, new_id_r, new_id_c, dim, dr, dc, visited);
    }
}

void checkMatr(int **grid, int V, int n_dir){
    int dr[] = {-1, 1, 0, 0}; // Variazioni delle righe
    int dc[] = {0, 0, 1, -1}; // Variazioni delle colonne
    int **visited = malloc(V * sizeof(int *));
    for(int i = 0; i < V; i++){
        visited[i] = calloc(V, sizeof(int)); 
    }

    for(int i = 0; i<V; i++){
        for(int j = 0; j<V; j++){
            if(!visited[i][j] && grid[i][j])
                dfs2(grid, n_dir, i, j, V, dr, dc, visited);
        }
    }

    for(int i = 0; i < V; i++){
        free(visited[i]); 
    }
    free(visited);
}

/*
Implementazione di un BST con duplicati (funzione di inserimento)
(a voce) Cosa restituirebbe la search in questa situazione (voleva sapere la gestione dei duplicati)
*/
typedef struct bst_s *bst_t;
typedef struct item_s{
    int id;
    char *val;
} *Item;

typedef struct node *link2;
struct node{ 
	Item item; 
	link2 l; 
	link2 r;
    int count;
};

struct bst_s{
    link2 root;
    link2 z;
};

//In questo modo sto incrementando il valore count
/*
Metodo alternativo, utilizzare la insert classica senza count, e decidere se inserire a destra o a sinistra.
Durante la ricerca la search si fermerebbe al primo valore, sapendo di averne di piu bisogna controllare oltre alla corrispondenza della chiave,
altri parametri che distinguono gli elementi.
*/
link2 insertR(link2 x, Item item, link2 z){
    if(x == z)
        return NEW(item, z, z);

    int act_key = x->item->id;
    if(act_key == item->id){
        x->count++;
        return x;
    }else if(item->id > act_key)
        x->r = insertR(x->r, item, z);
    else
        x->l = insertR(x->l, item, z);

    return x;
}

void BSTinsert(bst_t bst, Item item){
    bst->root = insertR(bst->root, item, bst->z);
}

/*
Scrivere una funzione che dato un grafo rappresentante un insieme di amici ed un vertice v, determinare il numero di amici di amici del vertice v, 
senza contare gli amici a distanza 1, solo quelli a distanza 2 (ha voluto usassi un doppio ciclo iterativo)
*/
int findFriends(graph_t g, int v){
    int *visited = calloc(g->V, sizeof(int));
    int count  = 0;
    visited[v] = 1;
    //Guardo chi sono gli amici di v
    for(link x = g->ladj[v]; x != g->z; x = x->next){
        int id_friend = x->info->id;
        if(!visited[id_friend]){
            visited[id_friend] = 1;
        }
    }

    //Ora posso andare a controllare gli amici di amici
    for(link x = g->ladj[v]; x != g->z; x = x->next){
        int id_friend = x->info->id;
        for(link t = g->ladj[id_friend]; t != g->z; t = t->next){
            if(!visited[t->info->id]){
                count++;
                visited[t->info->id] = 1;
            }
        }
    }

    free(visited);
    return count;
}

/*
Implementa una funzione che dato un BST calcola a quale profondità sono presenti il maggior numero di nodi
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

static void qput(queue_t q, link2 id){
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

void BSTbfs(bst_t bst, int *max, int *b_depth){
    queue_t q = queue_init();
    int current_depth = 0;
    int nodes_in_current_level = 1;
    qput(q, bst->root);

    while(!queue_empty(q)){
        if (nodes_in_current_level > *max) {
            *max = nodes_in_current_level;
            *b_depth = current_depth;
        }

        int next_level_count = 0;

        for(int i = 0; i<nodes_in_current_level; i++){
            link2 t = qget(q);
            if(t->l != bst->z) {
                qput(q, t->l);
                next_level_count++;
            }
            if(t->r != bst->z) {
                qput(q, t->r);
                next_level_count++;
            }
        }

        current_depth++;
        nodes_in_current_level = next_level_count;
    }
    qFree(q);
}

int depthMax(bst_t bst){
    int max = 0;
    int depth = 0;
    BSTbfs(bst, &max, &depth);
    return depth;
}

/*
Implementare una funzione che dato un BST trovi la profondità minima tra le foglie 
Poi a voce mi ha chiesto cosa avrei dovuto fare se avessi anche voluto contare le foglie (mettere un contatore)
*/
#include <limits.h>
void BSTbfs2(bst_t bst, int *min, int *depth){
    queue_t q = queue_init();
    int current_depth = 0;
    int level_count = 1;
    qput(q, bst->root);
    while(!queue_empty(q)){
        int next_level_count = 0;
        for(int i = 0; i<level_count; i++){
            link2 x = qget(q);
            if(x->l == bst->z && x->r == bst->z){
                while(!queue_empty(q)){
                    link2 t = qget(q);
                }
                break;
            }

            if(x->l != bst->z){
                qput(q, x->l);
                next_level_count++;
            } 
            if(x->r != bst->z){
                qput(q, x->r);
                next_level_count++;
            }
        }
        current_depth++;
    }

    *depth = current_depth;
    qFree(q);
}

int depthMinLeaf(bst_t bst){
    int min;
    int depth;
    BSTbfs2(bst, &min, &depth);
    return depth;
}

/*
Implementare una funzione che esegua la potatura di un albero dato un BST e un livello p (vale a dire eliminare tutti i valori di livello > p)
*/

void free_tree(link2 x, link2 z) {
    if (x == z) return;

    free_tree(x->l, z);
    free_tree(x->r, z);
    
    free(x); 
}

void BSTdfs3(bst_t bst, int p){
    queue_t q = queue_init();
    int depth = 0;
    int n_level = 1;
    qput(q, bst->root);
    while(!queue_empty(q)){
        int current_nodes = 0;
        for(int i = 0; i<n_level; i++){
            link2 x = qget(q);

            if(depth == p){
                free_tree(x->l, bst->z);
                free_tree(x->r, bst->z);

                //Metto i cerotti, cioe dico che i figli non esistono piu
                x->l = bst->z; 
                x->r = bst->z;
                continue;
            }

            if(x->l != bst->z){
                current_nodes++;
                qput(q, x->l);
            }

            if(x->r != bst->z){
                current_nodes++;
                qput(q, x->r);
            }
        }
        n_level = current_nodes;
        depth++;
    }
    qFree(q);
}

void potateBST(bst_t bst, int p){
    BSTdfs3(bst, p);
}

/*Dato un vertice V ed un Grafo orientato, eliminare tutti gli archi entranti ed uscenti da V, usando il grafo con listaDiAdiacenze.*/
void isolateNode(graph_t g, int v){
    //Elimino tutti gli archi che lo collegano e se è lui tutti quelli che ha
    for(int i = 0; i<g->V; i++){
        link prev = NULL;
        for(link x = g->ladj[i]; x != g->z;){
            if(i == v || x->info->id == v){
                link t = x;
                x = x->next;
                if(prev == NULL)
                    g->ladj[i] = x;
                else
                    prev->next = x;
                free(t);
            }else{
                prev = x;
                x = x->next;
            }
        }
    }
}

/*Inserimento di item in tabella di hash con linear chaining + a voce come avrei potuto fare con linear probing*/
typedef struct ht_entry_s *ht_entry_t;
typedef struct ht_entry_s {
    char *key;
    int heap_pos;
    int occupied;  // 1 se occupata, 0 se libera
    ht_entry_t next;   
};

typedef struct ht_s *ht_t;
struct ht_s{
    ht_entry_t *table;
    int heapsize;
    int maxSize;
};

void insertValueHT(ht_t ht, ht_entry_t item){
    if(ht == NULL || item == NULL) return -1;
    
    int i = hash(item->key, ht->maxSize);
    //Inserimento in testa alla linked list:
    item->next = ht->table[i];
    ht->table[i] = item;

    return 1;
}
/*
Con linear probing la funzione di hash è uguale ma bisogna scorrere finche non si trova una casella libera a partire da quella data dalla funzione di hash.
Bisogna inoltre controllare la dimensione della tabella (percio vedere se è possibile aggiungere un nuovo elemento).
*/
////////////////////////////////////////////////////////
/*
Scrivere una funzione BstNext(Bst b, key k) che ritorni il successore di k.
(a voce) Modifica la funzione precedente affinché ritorni gli n successori k (uso la visita in-order)
*/
link2 BSTfindmin(link2 root, link2 z){
    if(root == z) return NULL;
    if(root->l == z) return root;
    return BSTfindmin(root->l, z);
}

Item BstNext(bst_t b, int k){
    //Devo scendere trovare il nodo con chiave k.
    // link2 x = BSTsearch(b, k);
    link2 succ = NULL, p_succ = NULL;
    link2 x = b->root;
    while (x != b->z)
    {
        if(x->item->id == k) break;
        else if(k > x->item->id)
            x = x->r;
        else{
            p_succ = x;
            x = x->l;
        }
    }
    
    if(x == b->z) return NULL;
    if(x->r == b->z){
        succ = p_succ;
    }else{
        succ = BSTmin(x->r, b->z);
    }

    if(succ == NULL) return NULL;
    return succ->item;
}

/*
Per ritornare gli n successori di k, bisogna fare una visita in-order, tutti gli elementi dopo k sono suoi successori.
*/
////////////////////////////////////////////////////////
/*
Dato un BST, stabilire se è un albero completo.
*/
//Farei una bfs per controllare i livelli minimi e massimi dalla radice e se tutti i nodi (apparte l'ultimo) hanno 0 o 2 figli
void BSTbfs3(bst_t bst, int *complete){
    if(bst->root == bst->z){
        *complete = 1; // Un albero vuoto, per definizione matematica, è completo
        return;
    }
    queue_t q = queue_init();
    int act_nodes = 1;
    int found_hole = 0;
    *complete = 1;
    qput(q, bst->root);

    while(!queue_empty(q)){
        int count_nodes = 0;
        for(int i = 0; i<act_nodes; i++){
            link2 x = qget(q);

            if(x->l != bst->z){
                if(found_hole == 1) {
                    *complete = 0;
                    break; 
                }
                qput(q, x->l);
                count_nodes++;
            }else found_hole = 1;

            if(x->r != bst->z){
                if(found_hole){
                    *complete = 0;
                    break;
                }
                qput(q, x->r);
                count_nodes++;
            }else found_hole = 1;
            
        }

        act_nodes = count_nodes;

        if(*complete == 0){
            //Svuoto
            while(!queue_empty(q)){ 
                link2 x = qget(q);
            }
        }
    }
    qFree(q);
}

int is_complete(bst_t bst){
    int complete = 0;
    BSTbfs3(bst, &complete);

    return complete;
}

/*Funzione per calcolare la profondità media delle foglie di un BST*/
void BSTbfs4(bst_t bst, float *ratio){
    if(bst->root == bst->z){
        *ratio = 0.0;
        return;
    }
    int n_nodes = 1, depth = 0, sum_depth = 0, n_leaf = 0;
    queue_t q = queue_init();
    qput(q, bst->root);
    while(!queue_empty(q)){
        int act_nodes = 0;
        for(int i = 0; i<n_nodes; i++){
            link2 x = qget(q);
            int lchild = 1, rchild = 1;

            if(x->l != bst->z){
                qput(q, x->l);
                act_nodes++;
            }else lchild = 0;
            if(x->r != bst->z){
                qput(q, x->r);
                act_nodes++;
            }else rchild = 0;

            if(!rchild && !lchild){
                n_leaf++;
                sum_depth += depth;
            }
        }

        n_nodes = act_nodes;
        depth++;
    }
    *ratio = (float)sum_depth/n_leaf;
    qFree(q);
}

float avg_leaf_depth(bst_t bst){
    float ratio = 0;
    BSTbfs4(bst, &ratio);
    return ratio;
}

/*Mi ha chiesto di scrivere una funzione che prende in input un grafo e un insieme di vertici e stampa i vertici adiacenti all’insieme.*/
void printAdjacent(graph_t g, int *vertexes, int n){
    int *visited = calloc(g->V,sizeof(int));
    for(int i = 0; i<n; i++){
        visited[vertexes[i]] = 1;
    }

    for(int i = 0; i<n; i++){
        for(link x = g->ladj[vertexes[i]]; x != g->z; x = x->next){
            int id = x->info->id;
            if(!visited[id]){
                visited[id] = 1;
                printf("Vertice: %d", id);
            }
        }
    }

    free(visited);
}

/*
Inserimento in radice di un BST
Come modificare la funzione per avere una partition? 
La partition a quale funzione si “rifà” e cosa cambia? (select, rotazioni)
*/
static link2 rotR(link2 x){
    link2 left = x->l;
    x->l = left->r;
    left->r = x;
    return left;
}

static link2 rotL(link2 x){
    link2 right = x->r;
    x->r = right->l;
    right->l = x;
    return right;
}


link2 BSTinsertR(link2 x, Item item, link2 z){
    if(x == z) return NEWnode(item, z, z);

    if(item->id > x->item->id){
        x->r = BSTinsertR(x->r, item, z);
        x = rotL(x);
    }else{
        x->l = BSTinsertR(x->l, item, z);
        x = rotR(x);
    }
    return x;
}

void BSTinsertRoot(bst_t bst, Item item){
    bst->root = BSTinsertR(bst->root, item, bst->z);
}

//Per ottenere la partition (Uso il rango), si rifà alla select (Utilizzata negli Augmented BST)
link2 PartitionR(link2 x, int r, link2 z){
    if(x == z) return z; //Non trovato

    int t = (x->l == z) ? 0 : x->l->count;
    if(t > r){
        x->l = PartitionR(x->l, r, z);
        x = rotR(x);
    }
    if(t < r){
        x->r = PartitionR(x->r, r-t-1, z);
        x = rotL(x);
    }
    return x;
}

////////////////////////////////////////////////////////

/*
Data una lista concatenata semplice (con singolo link) che contiene valori interi, scrivi (o descrivi passo passo) una funzione che elimini tutti i nodi con valore dispari. 
Fai molta attenzione a come gestisci i puntatori se il nodo da eliminare è la testa della lista.
*/

typedef struct ListNode *link3;
struct ListNode{
    int id;
    link3 next;
};

typedef struct LinkedList *LL;
struct LinkedList{
    link3 head;
    int N;
};

void deleteSpare(LL list){
    for(link3 x = list->head, prev = NULL; x != NULL;){
        if(x->id%2 == 1){
            link3 t = x;
            if(prev == NULL)
                x = list->head = x->next;
            else 
                x = prev->next = x->next;
            list->N--;
            free(t);
        }else{
            prev = x;
            x = x->next;
        }
    }
}

////////////////////////////////////////////////////////////
int findFriends(graph_t g, int v){
    int *visited = calloc(g->V,sizeof(int));
    int count = 0;
    //Marco se stesso e gli amici primi
    visited[v] = 1;
    for(link x = g->ladj[v]; x != g->z; x = x->next)
        visited[x->info->id] = 1;

    for(link x = g->ladj[v]; x != g->z; x = x->next){
        int w = x->info->id;
        for(link y = g->ladj[w]; y != g->z; y = y->next){
            int u = y->info->id;
            if(!visited[u]){
                count++;
                visited[u] = 1;
            }
        }
    }

    free(visited);
    return count;
}
//////////////////////////////////////////
/*
Dato un Albero Binario generico (BT, che ha solo figlio destro e sinistro ma nessuna garanzia sull'ordine),
scrivi o descrivi la logica di una funzione che verifichi se questo albero rispetta rigorosamente le proprietà di un Binary Search Tree (BST).
*/

void is_BST(link2 x, link2 z, int *found, int max, int min){
    if(x == z || *found) return;

    if(x->l != z)
        if(x->l->item->id < x->item->id && x->l->item->id > min){ //Deve essere compreso tra il valore del node e quello del valore minimo
            is_BST(x->l, z, found, x->item->id, min);
        }else *found = 1;
    
    if(x->r != z)
        if(x->r->item->id > x->item->id && x->r->item->id < max){ //Deve essere compreso tra il valore del nodo e quello del valore massimo
            is_BST(x->r, z, found, max, x->item->id);
        }else *found = 1;
}

int WRAPPERis_BST(bst_t tree){
    int found = 0;
    is_BST(tree->root,tree->z, &found, INT_MAX, INT_MIN);
    if(found) return 0;
    return 1;
}

//////////////////////////////////////////////////////
/*

*/

typedef struct node4 *link4;
struct node4{
    int val;
    link4 next;
};

typedef struct pqueue *PQ;
struct pqueue{
    link4 head;
    link4 z;
    int n;
};

void PQinsert(PQ pq, int val){
    link4 x = pq->head;
    link4 prev = NULL;
    while(x != pq->z && x->val < val){ 
        prev = x;
        x = x->next;
    }
    link4 y = NEW(val, x);
    if (prev == NULL) {
        pq->head = y;
    } else {
        prev->next = y;
    }
}

///////////////////////////////////////
/*
Scrivi (o descrivi in modo dettagliato) la logica di una funzione che, dato un Albero Binario (BST) e un intero p (che rappresenta un livello di profondità), 
esegua la potatura dell'albero. Devi eliminare (liberare la memoria) di tutti i nodi che si trovano a un livello maggiore di p.
(Suggerimento: fai attenzione a cosa deve ritornare la funzione al padre quando un nodo viene "potato").
*/

link2 pruning(link2 x, link2 z, int p, int current_lvl){
    if(x == z) return z;

    x->l = pruning(x->l, z, p, current_lvl+1);
    x->r = pruning(x->r, z, p, current_lvl+1);

    if(current_lvl > p){
        free(x);
        return z;
    }
    return x;
}

/*
Dato un Heap memorizzato in un vettore, scrivi una funzione o descrivi la logica per estrarre non solo il massimo, 
ma i due dati più grandi presenti nella struttura. Dove si trova sicuramente il secondo massimo?
*/

//Uso un bst solo come albero in realtà non è un bst ma non mi va di riscrivere la struttura dati
void heapify(int *heap, int val, int n){
    int l, r, largest;
    l = val*2+1;
    r = val*2+2;
    if(l < n && heap[val] < heap[l])
        largest = l;
    else
        largest = val;
    
    if(r < n && heap[val] < heap[r])
        largest = r;
    
    if(largest != val){
        int tmp = heap[val];
        heap[val] = heap[largest];
        heap[largest] = tmp;
        heapify(heap, largest, n);
    }
}

int *getMax(int *heap, int *n){
    int max[2];
    for(int i = 0; i<2; i++){
        max[i] = heap[0];
        heap[0] = heap[*n-1];
        (*n)--;
        heapify(heap, 0, *n);
    }

    return max;
}