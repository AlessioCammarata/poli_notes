/*
Una ditta di trasporti deve organizzare un insieme di minibus per trasportare dall’aeroporto a casa un gruppo di N persone. 
Ogni persona è caratterizzata da nome e indirizzo (due stringhe contenenti eventuali spazi e o caratteri di punteggiatura), 
numero di valige e distanza da percorrere per il trasporto (in chilometri). E’ poi disponibile un ulteriore elenco di coppie di persone (non necessariamente tutte, 
solo quelle per cui esistono informazioni significative) in cui, per ogni coppia, è possibile indicare:
-	Che abitano allo stesso indirizzo (informazione binaria SI/NO)
-	Che vanno trasportati sullo stesso minibus (per vari motivi, che non interessano in questo problema) (informazione binaria SI/NO)
-	Il tratto di strada in comune tra l’aeroporto e la casa: il dato non è significativo nel caso di persone che abitano allo stesso indirizzo 
    e può non essere riportato se il tratto comune è nullo.
Una persona può comparire in nessuna una o più coppie, come pure in nessuna.

Occorre pianificare il trasporto delle persone, tenendo conto che 
-	sono disponibili minibus (tutti uguali) aventi capienza massima di MP persone e MV valige. Al fine di questo problema si può supporre che il numero di minibus sia illimitato.
-	Occorre rispettare il vincolo per coppie di persone che vanno trasportate sullo stesso minibus (compreso il caso di persone che abitano allo stesso indirizzo)
*/

/*
Struttura dati

Definire e implementare delle opportune strutture dati per rappresentare, come ADT di prima classe:

- L’elenco delle persone (tipo PERSONS)
- I vincoli, compresa l`eventuale indicazione di una parte di percorso in comune,  tra coppie di persone (tipo CONSTRAINTS)
- una soluzione al problema di ottimizzazione (tipo SOL)

In aggiunta alle tre strutture dati esplicitamente richieste, è possibile definire tutti i tipi ausiliari ritenuti opportuni, 
a supporto delle tre strutture principali. 
NON è richiesta la funzione di lettura da file.
*/
#define MAXC 21

typedef struct person_s *person_t;
struct person_s{
    char name[MAXC], address[MAXC];
    int n_luggages, distance;
};

typedef struct persons_s *PERSONS;
struct persons_s{
    person_t *list;
    int n_people;
};

typedef struct constraints_s *CONSTRAINTS;
struct constraints_s{
    int *group_id; //Tutti quelli che hanno stesso is devono viaggiare insieme
    int **common_path; //Si inserisce quanti chilometri in comune fanno
    int n_people;       // Comodo da avere qui per scorrere la matrice
    int n_groups;
};

typedef struct solution_s *SOL;
struct solution_s{
    int *best_disposition;
    int min_km;
    int n_pullman;
};


/*
Problema di verifica

Un insieme di persone è valido se la capienza di un minibus (volume e peso) è tale da 
poter contenere nello stesso carico tutte le persone che, in base ai vincoli, debbono stare insieme. 
Si scriva una funzione di verifica che, dato l`elenco (complessivo) di N persone , l’insieme di vincoli (tipo CONSTRAINTS), 
e due numeri indicanti MP e MV, verifichi la validità. 

ATTENZIONE: l’elenco di persone è quello complessivo da suddividere nei minibus, non un elenco già calcolato per un particolare minibus. 
Una persona A può essere vincolata a viaggiare con B, come pure C con D, ma non è necessario che le 4 persone stiano insieme:
è sufficiente che A stia con B, e che C stia con D.
*/

int checkValidity(PERSONS el, CONSTRAINTS c, int MP, int MV){
    int *people_c  = malloc(c->n_groups*sizeof(int));
    int *luggage_c = malloc(c->n_groups*sizeof(int));
    int valid = 1;
    for(int i = 0; i<c->n_groups; i++){
        people_c[i] = 0;
        luggage_c[i] = 0;
    }
    
    for(int i = 0; i<el->n_people && valid; i++){
        int id = c->group_id[i];
        people_c[id] += 1;
        luggage_c[id] += el->list[i]->n_luggages;
        if(people_c[id] > MP || luggage_c[id] > MV) 
            valid = 0;
    }
    free(people_c); free(luggage_c);
    return valid;
}

/*
Problema di ricerca e ottimizzazione

Scrivere una funzione ricorsiva in grado di individuare, a partire da un elenco di persone (tipo OBJECTS), 
un insieme di vincoli (tipo CONSTRAINTS), e due numeri indicanti MP e MV, la distribuzione ottima delle persone nei minibus.

Occorre
-  minimizzare il numero di minibus utilizzati (ogni minibus effettua un solo carico di persone all’aeroporto)

-  a parità di numero di minibus, occorre minimizzare i chilometri percorsi: nel valutare il chilometraggio di un minibus, 
    si sommano le distanze (aeroporto-casa) dei singoli passeggeri, sottraendo poi le distanze conteggiate più volte 
    (perché due o più passeggeri abitano allo stesso indirizzo, oppure perché un pezzo del percorso è in comune.

Il modello del calcolo combinatorio scelto va indicato e spiegato/motivato.
*/

/*
Il modello di calcolo combinatorio sono le partizioni in quanto bisogna suddividere un certo numero di persone in gruppi diversi
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int getMinibusKm(int bus_index, PERSONS el, CONSTRAINTS c, int *sol) {
    int total_km = 0;
    
    // Scorriamo tutte le persone
    for(int i = 0; i < el->n_people; i++) {
        int group_i = c->group_id[i];
        
        // Se la persona 'i' è su questo minibus
        if(sol[group_i] == bus_index) {
            total_km += el->list[i]->distance; // Sommo la sua distanza
            
            for(int j = 0; j < i; j++) {
                int group_j = c->group_id[j];
                
                if(sol[group_j] == bus_index) {
                    total_km -= c->common_path[i][j]; // Sottraggo il tratto in comune
                }
            }
        }
    }
    
    return total_km;
}

void solveR(int pos, int *sol, int *best_sol, int *min_km, int *n_pullman, int *p_people, int *p_luggage, int *g_people, int *g_luggage, int n_groups, PERSONS el, CONSTRAINTS c, int MP, int MV){
    if(pos >= n_groups){
        int current_buses = 0;
        int current_km = 0;
        
        // Calcoliamo quanti bus stiamo usando e i km totali
        for(int k = 0; k < n_groups; k++){
            if(p_people[k] > 0){ // Se il minibus non è vuoto
                current_buses++;
                current_km += getMinibusKm(k, el, c, sol);
            }
        }

        if(current_buses < *n_pullman || (current_buses == *n_pullman && current_km < *min_km)){
            *min_km = current_km;
            *n_pullman = current_buses;
            for(int i = 0; i<n_groups; i++){
                best_sol[i] = sol[i];
            }
        }
        return;
    }

    for(int k = 0; k<n_groups; k++){

        //Pruning
        if(p_people[k] + g_people[pos] > MP || p_luggage[k] + g_luggage[pos] > MV)
            continue;

        sol[pos] = k;
        p_people[k] += g_people[pos];
        p_luggage[k] += g_luggage[pos];
        solveR(pos+1, sol, best_sol, min_km, n_pullman, p_people, p_luggage, g_people, g_luggage, n_groups, el, c, MP, MV);
        p_people[k] -= g_people[pos];
        p_luggage[k] -= g_luggage[pos];

        if(p_people[k] == 0) break;
    }
}

SOL bestPartition(PERSONS el, CONSTRAINTS c, int MP, int MV){
    int *group_people = malloc(c->n_groups*sizeof(int));
    int *group_luggage = malloc(c->n_groups*sizeof(int));
    for(int i = 0; i<c->n_groups; i++){
        group_people[i] = 0;
        group_luggage[i] = 0;
    }
    
    for(int i = 0; i<el->n_people; i++){
        int id = c->group_id[i];
        group_people[id] += 1;
        group_luggage[id] += el->list[i]->n_luggages;

        //Controllo se si supera MP o MV gia nel gruppo
        if(group_people[id] > MP || group_luggage[id] > MV){
            printf("Impossibile: Il gruppo %d supera la capacità del mezzo.\n", i);
            free(group_people); free(group_luggage);
            return NULL;
        }
    }

    int *pullman_people =  malloc(c->n_groups*sizeof(int));
    int *pullman_luggage = malloc(c->n_groups*sizeof(int));
    int *best_sol = malloc(c->n_groups*sizeof(int));
    int *sol = malloc(c->n_groups*sizeof(int));
    int n_pullman = INT_MAX;
    int min_km = INT_MAX;

    for(int i = 0; i<c->n_groups; i++){
        pullman_people[i] = 0;
        pullman_luggage[i] = 0;
    }
    solveR(0, sol, best_sol, &min_km, &n_pullman, pullman_people, pullman_luggage, group_people, group_luggage, c->n_groups, el, c, MP, MV);

    SOL final_sol = malloc(sizeof(*final_sol));
    final_sol->best_disposition = best_sol;
    final_sol->min_km = min_km;
    final_sol->n_pullman = n_pullman;

    free(group_people); free(group_luggage);
    free(pullman_people); free(pullman_luggage); free(sol);

    return final_sol;
}