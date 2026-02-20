#include <stdlib.h>
#include <stdio.h>

#define BUF 21

typedef struct elenco_s *ELENCO;
struct elenco_s{
    char **city;
    int n;
};

typedef struct distmatr_s *DISTMATR;
struct distmatr_s{
    int **dist;
    int n;
};

typedef struct sedi_s *SEDI;
struct sedi_s{
    int *id_sedi;
    int n;
};

typedef struct servizi_s *SERVIZI;
struct servizi_s{
    int *assegnazioni; //Assegnazione citta sede, contiene id_sede
    int n;
};

// Funzioni di utilità per allocare (costruttori ADT)
ELENCO ELENCOinit(int n) {
    ELENCO e = malloc(sizeof(struct elenco_s));
    e->n = n;
    e->city = malloc(n * sizeof(char*));
    for(int i=0; i<n; i++) e->city[i] = NULL;
    return e;
}

DISTMATR DISTMATRinit(int n) {
    DISTMATR m = malloc(sizeof(struct distmatr_s));
    m->n = n;
    m->dist = malloc(n * sizeof(int*));
    for (int i=0; i<n; i++) {
        m->dist[i] = malloc(n * sizeof(int));
    }
    return m;
}

int caricaDati(FILE *f, ELENCO *el, DISTMATR *d){
    int V;
    if(fscanf(f,"%d",&V) != 1) return 0;

    *el = ELENCOinit(V);
    for(int i = 0; i<V; i++){
        char temp[BUF];
        if(fscanf(f,"%s",temp) != 1){
            ELENCOfree(*el);
            return 0;
        }
        (*el)->city[i] = strdup(temp);
    }

    *d = DISTMATRinit(V);
    for(int i = 0; i<V; i++){
        for(int j = 0; j<V; j++){
            if(fscanf(f,"%d",&(*d)->dist[i][j]) != 1){
                ELENCOfree(*el);
                DISTMATRfree(*d);
                return 0;
            }
        }
    }

    return 1;
}


/*
Si assuma di voler enumerare i possibili insiemi di M città sedi di pronto soccorso, mediante un algoritmo basato su combinazioni semplici. 
Si scriva la funzione checkSedi, in grado di verificare, nel caso terminale, l’accettabilità di una soluzione: 
NON si chiede l’algoritmo per generare le combinazioni ma solo la checkSedi. 
Questa deve ricevere, tra gli altri parametri (da decidere) la matrice delle distanze, la distanza massima MAXD, il numero minimo MINS, 
l’insieme ottenuto nel caso terminale (la soluzione, di tipo SEDI, da verificare).

- per ognuna delle altre N-M città esiste almeno una sede di pronto soccorso (tra le M scelte) a distanza <= MAXD

- ognuna delle sedi di pronto soccorso è in grado di servire almeno MINS città non sedi di pronto soccorso (rispettando per ognuna il vincolo precedente).
*/

//Devo controllare se esiste un pronto soccorso tra ogni citta a distanza < MAXD
int checkSEDI(DISTMATR d, SEDI s, int MAXD, int MINS){
    int N = d->n;
    int M = s->n;
    int is_hub[N];
    for(int i = 0; i<N; i++) is_hub[i] = 0;
    for(int i = 0; i<M; i++) is_hub[s->id_sedi[i]] = 1;
    

    for(int i = 0; i<N; i++){
        if(is_hub[i]) continue;
        int coperta = 0;

        for(int j = 0; j<M; j++){
            if(d->dist[i][s->id_sedi[j]] <= MAXD){
                coperta = 1;
                break;
            }
        }
        if(!coperta) return 0;
    }

    //Devo controllare tra le sedi, guardando gli indici non presenti che sono i buchi che ho da 0 a d->n.
    for(int i = 0; i<M; i++){
        int covered = 0;

        for(int j = 0; j<N; j++){
            if(!is_hub[j] && d->dist[s->id_sedi[i]][j] <= MAXD){
                covered++;
            }
        }
        if(covered < MINS) return 0;
    }

    return 1;
}

/*
Dato un insieme valido di M sedi (tipo SEDI) di pronto soccorso, già verificato mediante checkSedi, 
si vuole determinare un partizionamento ottimo delle città servite, in modo tale che si rispettino i criteri seguenti:

- ogni città non sede di pronto soccorso viene assegnata a una (sola) sede di pronto soccorso, a distanza <= MAXD

- la distanza media tra le città servite e le sedi di pronto soccorso è minima

- a ognuna delle sedi di pronto soccorso si assegnano almeno MINS città.

 
Si scriva la funzione bestPart, che, utilizzando un algoritmo di partizionamento, dato l’elenco delle città, 
la matrice delle distanze, un insieme di M sedi di pronto soccorso e i valori MAXD e MINS, 
trovi la soluzione ottima e la ritorni come struttura dati (tipo SERVIZI). 
Non è necessario realizzare la funzione wrapper: è sufficiente rappresentare la funzione bestPart, che al suo interno deve usare due funzioni (da scrivere anche queste):

- checkPart: funzione di verifica da chiamare in un caso terminale

- prunePart: chiamata per fare pruning (si dica esplicitamente di quali vincoli o criteri si può fare pruning e di quali no).

 

Nell’esempio proposto in precedenza, supponendo che si siano selezionate come sedi di pronto soccorso {A,C}, 
che  MAXD valga 4 e MINS valga 2, la soluzione sarebbe quella di assegnare {B,D} alla sede A e {E,F} alla sede C. 
Si riporta la matrice delle distanze, avendo evidenziato in rosso (sulle righe) le sedi e in grassetto le distanze compatibili con MAXD. 
Per la soluzione proposta, la distanza media tra le citta servite e le sedi è (2+4+4+3)/4 = 13/4.
*/


// Ritorna 1 se la partizione è valida (rispetta MINS), 0 altrimenti
int checkPart(int *sol, int n_citta, int n_sedi, int MINS) {
    int count[n_sedi];
    for(int k=0; k<n_sedi; k++) count[k] = 0;

    // Conto le assegnazioni
    for(int i=0; i<n_citta; i++) {
        int hub_idx = sol[i]; // sol[i] contiene l'indice della sede (0..M-1)
        if (hub_idx != -1) {   // Se -1 significa che la città i è essa stessa una sede
            count[hub_idx]++;
        }
    }

    // Verifico che ogni sede abbia almeno MINS pazienti
    for(int k=0; k<n_sedi; k++) {
        if(count[k] < MINS) return 0;
    }
    return 1;
}

int prunePart(int current_dist, int best_dist, int dist_citta_sede, int MAXD){
    /*
    Si puo fare pruning sulla distanza media tra le città servite. -> Siccome il denominatore è fisso basta controllare la somma
    Si puo fare pruning per controllare se la soluzione attuale è peggiore del migliore, siccome stiamo sommando valori positivi non si puo tornare indietro.
    */
    if (dist_citta_sede > MAXD) return 1;
    if (current_dist >= best_dist && best_dist != -1) return 1;

    return 0;
}


void bestPart(int pos, int *sol, ELENCO el, DISTMATR d, SEDI M, int MAXD, int MINS, int current_total_dist, int *min_total_dist, SERVIZI best_services, int *is_hub){
    if(pos == d->n){
        if(checkPart(sol, d->n, M->n, MINS))
            if (*min_total_dist == -1 || current_total_dist < *min_total_dist) {
                *min_total_dist = current_total_dist;
 
                for(int i = 0; i<d->n; i++){
                    if (is_hub[i]) 
                        best_services->assegnazioni[i] = -1;
                    else 
                        best_services->assegnazioni[i] = M->id_sedi[sol[i]];
                }
                
            }
        return;
    }

    if (is_hub[pos]) {
        sol[pos] = -1; // Marker per dire che è una sede
        bestPart(pos+1, sol, el, d, M, MAXD, MINS, current_total_dist, min_total_dist, best_services, is_hub);
        return;
    }

    // Se la città 'pos' NON è una sede, proviamo ad assegnarla a ciascuna delle M sedi
    for (int k = 0; k < M->n; k++) {
        int distance = d->dist[pos][M->id_sedi[k]];


        if (prunePart(current_total_dist + distance, *min_total_dist, distance, MAXD)) {
            continue; // Salto questa sede, provo la prossima
        }

        sol[pos] = k; // Assegno la città 'pos' alla k-esima sede della lista M
        bestPart(pos+1, sol, el, d, M, MAXD, MINS, current_total_dist + distance, min_total_dist, best_services, is_hub);
        
    }

    return;
}