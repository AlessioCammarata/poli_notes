#include <stdio.h>
#include <stdlib.h>

/* Non definito perche classico*/
typedef struct edge_s *edge_t;
struct edge_s{
    int u, v;
    int w;
};

typedef struct nodeG *link;
struct nodeG{
    //vertex_t
    link next;
    int v;
};

typedef struct graph_s *graph_t;
struct graph_s { 
  int V; 
  int E; 
  edge_t *edges; // Lista di archi
  link *ladj;
  link z; 
};

// Struttura per il Tree Partitioning (Union-Find) 
typedef struct { 
  int *parent;  
  int *size; 
} partition_t;

void caricaDati(FILE *fin){
    int V, E;
    fscanf(fin,"%d",&V);

    graph_t G = graphInit(V);

    for(int i = 0; i<V; i++){
        int u,v, w;
        fscanf(fin,"(%d,%d) %d",&u, &v, &w);
        addEdge(G, u, v, w);
    }
}


/*
Data una soluzione proposta, verificare che questa rappresenti effettivamente un k-capacitated tree partitioning, 
tenendo in considerazione la definizione teorica proposta in precedenza. Si trascuri la richiesta di minimalità della 
somma complessiva dei pesi per gli archi scelti.

La soluzione proposta deve essere letta da file il cui nome e formato è a discrezione del candidato, 
che è tenuto a fornire anche una breve spiegazione dei contenuti del file stesso.
*/

/*Definizione di queue data*/
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

/*Soluzione*/
int bfs(graph_t G, int start, int visited[], int k){
 int n = 0, edges = 0;
 queue_t q = qInit();
 qput(q, start); 
 visited[start] = 1;

 while(!qEmpty(q)){
  int id = qget(q);
  n++;
  for(link x = G->ladj[id]; x != G->z; x = x->next){
   int w = x->v;
   edges++;

   if(!visited[w]){
      visited[w] = 1;
      qput(q,w);
    }
  }

 // In un albero non orientato, gli archi contati (due volte ciascuno) // devono essere pari a 2 * (nodi - 1). 
  if (edges != 2 * (n - 1)) { 
    return -1; // Indica che non è un albero (presenza di cicli) 
  }
  return n;
 }
}

int bfsWrapper(graph_t G, int k){
 int *visited = calloc(G->V,sizeof(int));

 for(int i = 0; i<G->V; i++){
   if(!visited[i])
    if(bfs(G, i, visited, k) < k){
           free(visited);  
           return 0;
       } 
}

 free(visited);
 return 1;
}

/*
Identificare, se possibile, un k-capacitated tree partitioning 
che rispetti anche la condizione di minimalità della somma dei pesi per gli archi scelti, 
per il grafo dato in input e il relativo parametro  passato come argomento.
*/

/* Definizione non necessaria */
partition_t UF_init(){

}

void kruskalM(graph_t G, int k){
  edge_t *edges = malloc(G->E*sizeof(*edges));
  partition_t UF = UF_init(G->V); // parent[i]=i, size[i]=1

  int dim = 0;
  ordEdges(G->edges); //Ordina in base al peso

  for(int i = 0; i<G->E; i++){
   int u = G->edges[i].u; 
   int v = G->edges[i].v;

   int rootU = find(UF, u); int rootV = find(UF, v);

   if(rootU != rootV){
     if (UF->size[rootU] < k || UF->size[rootV] < k) { 
        union(UF, rootU, rootV); 
        edges[dim++] = G->edges[i]; 
     }
  }

  if (checkAllComponents(UF, G->V, k)) { 
    saveSolution(result_edges, count);
  } else { 
    printf("Soluzione non possibile per k=%d\n", k);  
  }

 }
}