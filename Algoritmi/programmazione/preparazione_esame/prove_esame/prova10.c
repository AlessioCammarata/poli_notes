/*
E’ dato un grafo non orientato. NV indica il numero di vertici e NE indica il numero di archi. I nodi sono numerati da 0 a NV-1. 
A ogni nodo è associato un nome (una stringa di al più 20 caratteri alfabetici, terminatore compreso) e un valore (un numero intero). 
Il nome non è univoco, cioè più nodi possono essere associati allo stesso nome.

Un cammino nel grafo è quindi associato a:
- Una stringa determinata dalla concatenazione dei nomi associati ai nodi nel cammino
- Un valore complessivo, dato dalla somma dei valori dei nodi nel cammino.
*/

/*
Definire opportune strutture dati per rappresentare i dati del problema e tutte le strutture dati ausiliarie ritenute opportune per 
la risoluzione dei problemi di verifica e di ricerca. 
Definire inoltre la funzione di lettura secondo il formato del file descritto nelle  domande a seguire. 
Si chiede di utilizzare l'ADT GRAPH proposto nel corso, adattandolo al problema.
*/
#define BUF 21

typedef struct vertex_s *vertex_t;
struct vertex_s{
    char name[BUF];
    int value;
};

typedef struct node *link;
struct node{
    int v;
    link next;
};

typedef struct graph_s *graph_t;
struct graph_s{
    int NV, NE;
    link *ladj;
    link z;
    vertex_t *vet; //Dove stanno i dati, sarebbe come la ST dato che posso gestire i nodi in base al loro indice
};

/*
Problema di verifica
Si scriva una funzione checkString che, dato il grafo e una stringa, 
verifichi se la stringa può rappresentare la concatenazione dei nomi associati ai nodi su un cammino nel grafo
*/
int checkR(int id, graph_t g, char *str, int len, int act_len){
    if(len-act_len == 0) return 1;

    for(link x = g->ladj[id]; x != g->z; x = x->next){
        int v = x->v;
        int start_len = strlen(g->vet[v]->name);
        if(strncmp(g->vet[v]->name,str + act_len,start_len) == 0 && checkR(v, g, str, len, act_len + start_len)){
            return 1;
        }
    }

    return 0;
}

int checkString(graph_t g, char *str){
    int len = strlen(str);
    /*Devo controllare partendo da ogni nodo ogni volta se la stringa combacia e poi partire da li con le liste di adiacenza*/
    for(int i = 0; i<g->NV; i++){
        int start_len = strlen(g->vet[i]->name);
        if(strncmp(g->vet[i]->name,str,start_len) == 0){
            if(checkR(i, g, str, len, start_len))
                return 1;
        }
    }

    return 0;
}

/*
Problema di ottimizzazione
Si scriva la funzione bestPath, che, dato il grafo e un numero M, determini il cammino 
(eventualmente ciclico, ma con nomi ripetuti nel cammino al più M volte) di valore massimo, 
dove il valore è la somma dei valori associati a ogni vertice nel cammino. 

Esempio: se M valesse 2, significa che ogni nome può comparire al più 2 volte in un cammino: 
se il nome caratterizzasse due vertici, i vertici potranno comparire in un cammino entrambi, una volta sola, 
oppure solo uno dei due, fino a due volte.

Si tenga conto di un ulteriore vincolo: date due parole consecutive nella sequenza, 
se la prima parola termina con vocale, la seconda non può iniziare con vocale, 
se la prima termina con consonante, la seconda non può iniziare con consonante. 
E' sufficiente che il cammino venga stampato.  
*/

int is_vowel(char c) { 
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'); 
} 

//Check vocali
int isPromising(char *str1, char *str2){
    int len1 = strlen(str1);

    if(is_vowel(str1[len1 - 1]) && is_vowel(str2[0]))
        return 0;
        
    if(!is_vowel(str1[len1 - 1]) && !is_vowel(str2[0]))
        return 0;

    return 1;
}

void findBestPath(graph_t g, int M, int id, int *name_freq, int *sol, int *best_sol, int act_val, int *max_val, int step, int *best_steps){
    sol[step] = id;
    
    //Mark
    char *current_name = g->vet[id]->name;
    for(int i = 0; i < g->NV; i++) {
        if(strcmp(g->vet[i]->name, current_name) == 0) {
            name_freq[i]++;
        }
    }

    //Check best
    if(act_val > *max_val){
        *max_val = act_val;
        *best_steps = step;
        for(int i = 0; i<step + 1; i++){
            best_sol[i] = sol[i];
        }
    }

    //Recursion con pruning dinamico
    for(link x = g->ladj[id]; x!=g->z; x = x->next){
        if(name_freq[x->v] < M && isPromising(g->vet[id]->name, g->vet[x->v]->name)){
            findBestPath(g, M, x->v, name_freq, sol, best_sol, act_val + g->vet[x->v]->value, max_val, step + 1, best_steps);
        }
    }
    
    //Backtrack
    for(int i = 0; i < g->NV; i++) {
        if(strcmp(g->vet[i]->name, current_name) == 0) {
            name_freq[i]--;
        }
    }
}

void bestPath(graph_t g, int M){
    int *sol = malloc(g->NV*M*sizeof(int));
    int *best_sol = malloc(g->NV*M*sizeof(int));
    int *name_freq = calloc(g->NV,sizeof(int));
    int max = -1, steps = 0;

    for(int i = 0; i<g->NV*M; i++){
        sol[i] = -1;
        best_sol[i] = -1;
    }

    for(int i = 0; i<g->NV; i++)
        findBestPath(g, M, i, name_freq, sol, best_sol, g->vet[i]->value, &max, 0, &steps);

    printf("Percorso migliore:\n");
    for(int i = 0; i<steps+1; i++){
        printf("%s\n",g->vet[best_sol[i]]->name);
    }
    printf("Il massimo valore ottenuto dal percorso è %d\n",max);

    free(sol); free(best_sol); free(name_freq);
}