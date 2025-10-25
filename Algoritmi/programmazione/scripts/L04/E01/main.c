#include <stdio.h>
#include <stdlib.h>

#define nfin "D:/politecnico/poli_notes/Algoritmi/programmazione/scripts/L04/E01/grafo.txt"

typedef struct{
    int l,r;
}edge;

void leggiFile(FILE *fin, edge *vet);
int is_vertex_cover(int *in_cover, edge *edges, int E);
void print_cover(int *in_cover, int N);
void find_vertex_cover(edge *edges, int E, int N, int pos, int *in_cover);


int main(void){
    FILE *fin;
    edge *vet;
    int N, E;

    if ((fin = fopen(nfin,"r")) == NULL){
        printf("Errore in apertura del file\n");
        return 1;
    }
    
    if(fscanf(fin,"%d %d",&N,&E) != 2){
        printf("Manca la N o la E");
        fclose(fin);
        return 1;
    }

    //Preparo gli archi
    vet = malloc(E * sizeof(edge));
    if (vet == NULL) {
        perror("malloc"); //Stampa -> malloc: "Cannot allocate memory"
        fclose(fin);
        return 1;
    }

    leggiFile(fin, vet);
    fclose(fin);

    int *in_cover = calloc(N, sizeof(int)); // (0, 0, 0, 0)
    find_vertex_cover(vet, E, N, 0, in_cover);

    free(in_cover);
    return 0;
}

void leggiFile(FILE *fin, edge *vet){
    int i = 0;
    while(fscanf(fin,"%d %d",&vet[i].l,&vet[i].r) == 2){
        i++;
    }
}

//Controllo se è un vertex-cover
int is_vertex_cover(int *in_cover, edge *edges, int E) {
    for (int e = 0; e < E; e++) {
        if (!in_cover[edges[e].l] && !in_cover[edges[e].r]) 
            return 0; // Se trovo un valore non contenuto significa che non è un Vertex Cover
    }
    return 1;
}

//Stampa, l'indice
void print_cover(int *in_cover, int N) {
    printf("{");
    int first = 1;
    for (int i = 0; i < N; i++) 
        if (in_cover[i]) {
            if (!first) printf(",");
            printf("%d", i);
            first = 0;
        }
    printf("}\n");
}

/*
Funzione ricorsiva che in generale crea l'insieme delle parti e stampa i vertex-cover
Ordine:
    0000 - 0001 - 0010 - 0011 - 0100 - 0101 - 0110 - 0111
    1000 - 1001 - 1010 - 1011 - 1100 - 1101 - 1110 - 1111 
*/
void find_vertex_cover(edge *edges, int E, int N, int pos, int *in_cover) {
    if (pos == N) {
        if (is_vertex_cover(in_cover, edges, E)) 
            print_cover(in_cover, N); //Stampo soluzione
        return;
    }

    in_cover[pos] = 0; // Escludo il valore il nodo pos
    find_vertex_cover(edges, E, N, pos + 1, in_cover);

    in_cover[pos] = 1; // includo il valore il nodo pos
    find_vertex_cover(edges, E, N, pos + 1, in_cover);
}
