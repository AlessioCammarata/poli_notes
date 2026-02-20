/*
* La Regione deve decidere la localizzazione di un servizio di Pronto Soccorso per N città.
* Tra queste occorre selezionare M < N città che possono essere sede di Pronto Soccorso.
* Obiettivo del problema è determinare le sedi di pronto soccorse ed assegnare ad ognuna di esse il servizio di altre città,
* dati vincoli e criteri per valutare costi e benefici. 
*
* Date:
* - le distanze tra tutte le coppie di città, come matrice NxN di interi (ogni città dista 0 da se stessa);
* - una distanza massima tollerabile MAXD, tra sede di un pronto soccorso e una città servita;
* - un numero minimo MINS di città servibili da ogni sede di pronto soccorso
*	(siccome una sede di pronto soccorso serve ovviamente se stessa, MINS tiene conto solo delle altre città NON sede di pronto soccorso).
*
* un insieme di M città sede di pronto soccorso è accettabile se sono rispettati i vincoli seguenti:
* - per ognuna delle altre N-M città esiste almeno una sede di pronto soccorso (tra le M scelte) a distanza <= MAXD; 
* - ognuna delle sedi di pronto soccorso è in grado di servire almeno MINS città non sedi di pronto soccorso
*	(rispettando per ognuna il vincolo precedente).
*
* Richieste del problema
*
* A seguire una sintesi delle richieste del problema.
* Per ogni richiesta si troverà una domanda dedicata nelle sezioni a seguire con una descrizione più dettagliata per le richieste.
* 
* Strutture dati e letture
*
* Definire opportune strutture dati per rappresentare:
* - L’elenco delle città (tipo ELENCO);
* - La matrice delle distanze (DISTMATR);
* - Un insieme di sedi di pronto soccorso (tipo SEDI, vedere i punti successivi);
* - Un’assegnazione di città alle sedi (tipo SERVIZI, la soluzione del problema di ottimizzazione).
*
* In particolare, tutte le strutture dati precedenti devono essere ADT di prima classe.
* Si scriva la funzione caricaDati che ritorni un elenco di città (tipo ELENCO) e una matrice delle distanze (tipo DISTMATR),
* leggendo un file in cui la prima riga contiene il valore N, le N righe successive i nomi di N città,
* le ulteriori N righe successive la matrice quadrata delle distanze: ogni riga contiene N interi separati da spazi.
*
* Esempio di file (per semplicitá si usano nomi di un solo carattere):
* 6
* A
* B
* C
* D
* E
* F
* 0 2 5 4 2 6
* 2 0 6 6 2 5
* 5 6 0 7 4 3
* 4 6 7 0 6 3
* 2 2 4 6 0 6
* 6 5 3 3 6 0
*
* Problema di verifica
*
* Si assuma di voler enumerare i possibili insiemi di M città sedi di pronto soccorso,
* mediante un algoritmo basato su combinazioni semplici. Si scriva la funzione checkSedi, in grado di verificare,
* nel caso terminale, l’accettabilità di una soluzione: NON si chiede l’algoritmo per generare le combinazioni ma solo la checkSedi.
* Questa deve ricevere, tra gli altri parametri (da decidere) la matrice delle distanze,
* la distanza massima MAXD, il numero minimo MINS, l’insieme ottenuto nel caso terminale (la soluzione, di tipo SEDI, da verificare).
*
* Problema di ricerca e ottimizzazione
*
* Dato un insieme valido di M sedi (tipo SEDI) di pronto soccorso,
* già verificato mediante checkSedi, si vuole determinare un partizionamento ottimo delle città servite,
* in modo tale che si rispettino i criteri seguenti:
* - ogni città non sede di pronto soccorso viene assegnata a una (sola) sede di pronto soccorso, a distanza <= MAXD;
* - la distanza media tra le città servite e le sedi di pronto soccorso è minima;
* - a ognuna delle sedi di pronto soccorso si assegnano almeno MINS città.
*
* Si scriva la funzione bestPart, che, utilizzando un algoritmo di partizionamento, dato l’elenco delle città,
* la matrice delle distanze, un insieme di M sedi di pronto soccorso e i valori MAXD e MINS,
* trovi la soluzione ottima e la ritorni come struttura dati (tipo SERVIZI).
* Non è necessario realizzare la funzione wrapper: è sufficiente rappresentare la funzione bestPart,
* che al suo interno deve usare due funzioni (da scrivere anche queste):
* - checkPart: funzione di verifica da chiamare in un caso terminale;
* - prunePart: chiamata per fare pruning (si dica esplicitamente di quali vincoli o criteri si può fare pruning e di quali no).
*
* Nell’esempio proposto in precedenza, supponendo che si siano selezionate come sedi di pronto soccorso {A,C},
* che  MAXD valga 4 e MINS valga 2, la soluzione sarebbe quella di assegnare {B,D} alla sede A e {E,F} alla sede C.
* Si riporta la matrice delle distanze, avendo evidenziato in rosso (sulle righe) le sedi e in grassetto le distanze compatibili con MAXD.
* Per la soluzione proposta, la distanza media tra le citta servite e le sedi è (2+4+4+3)/4 = 13/4.
*
* | |A|B|C|D|E|F|
* |A|0|2|5|4|2|6|
* |B|2|0|6|6|2|5|
* |C|5|6|0|7|4|3|
* |D|4|6|7|0|6|3|
* |E|2|2|4|6|0|6|
* |F|6|5|3|3|6|0|
*/

#include <stdio.h>
#include "servizi.h"
#include "sedi.h"
#include "elenco.h"
#include "distmatr.h"
#define MAXN 21 //Supponendo nomi di citta non lunghi piu di 20

void caricaDati(FILE *f, DISTMATR *d, ELENCO *el);
int checkSedi(DISTMATR d, SEDI s, int n_cities, int n_sedi, int MAXD, int MINS);


int main(int argc, char **argv) {
	/* your code goes here */
	return 0;
}

void caricaDati(FILE *f, DISTMATR *d, ELENCO *el){
	int n;
	char name[MAXN];
	if(fscanf(f,"%d",&n) != 1) return;

	*el = ELENCOinit(n);
	for(int i = 0; i<n; i++){
		if(fscanf(f,"%s",name) != 1 || !insertELENCO(el, name)){
			ELENCOfree(*el);
			return;
		}
	}

	int buf = 100;
	char line[buf];
	int temp[n][n];
	*d = DISTMATRinit(n);
	fgets(line,sizeof(line),f); //Si mangia lo \n
	for(int i = 0; i<n; i++){
		fgets(line,sizeof(line),f);
		for(int j = 0; j<n; j++){
			if(sscanf(line,"%d",&temp[i][j]) != 1){
				ELENCOfree(*el);
				DISTMATRfree(*d);
				return;
			}
		}
	}

	if(!insertDISTMATR(*d, temp)){
		ELENCOfree(*el);
		DISTMATRfree(*d);
		return;
	}
	
	return;
}


/*Verifica
* Si assuma di voler enumerare i possibili insiemi di M città sedi di pronto soccorso,
* mediante un algoritmo basato su combinazioni semplici. Si scriva la funzione checkSedi, in grado di verificare,
* nel caso terminale, l’accettabilità di una soluzione: NON si chiede l’algoritmo per generare le combinazioni ma solo la checkSedi.
* Questa deve ricevere, tra gli altri parametri (da decidere) la matrice delle distanze,
* la distanza massima MAXD, il numero minimo MINS, l’insieme ottenuto nel caso terminale (la soluzione, di tipo SEDI, da verificare).
* - per ognuna delle altre N-M città esiste almeno una sede di pronto soccorso (tra le M scelte) a distanza <= MAXD; 
* - ognuna delle sedi di pronto soccorso è in grado di servire almeno MINS città non sedi di pronto soccorso
*	(rispettando per ognuna il vincolo precedente).
*/

int checkSedi(DISTMATR d, SEDI s, int n_cities, int n_sedi, int MAXD, int MINS){
	int is_hub[n_cities];
	for(int i = 0; i<n_cities; i++) is_hub[i] = 0;
	for(int i = 0; i<n_sedi; i++) is_hub[getCity(s, i)] = 1;

	for(int i = 0; i<n_cities; i++){
		int id = getCity(s, i);
		int found = 0;
		for(int j = 0; j<n_sedi; j++){ 
			if(getDist(d, id, getCity(s, j)) <= MAXD) 
				found = 1;
		}
		if(!found) return 0;
	}

	for(int i = 0; i<n_sedi; i++){
		int served = 0;
		for(int j = 0; j<n_cities; j++){
			if(!is_hub[j] && getDist(d, getCity(s, i), j) <= MAXD)
				served++;
		}

		if(served < MINS) return 0;
	}

	return 1;
}

/*Ottimizzazione
* Dato un insieme valido di M sedi (tipo SEDI) di pronto soccorso,
* già verificato mediante checkSedi, si vuole determinare un partizionamento ottimo delle città servite,
* in modo tale che si rispettino i criteri seguenti:
* - ogni città non sede di pronto soccorso viene assegnata a una (sola) sede di pronto soccorso, a distanza <= MAXD;
* - la distanza media tra le città servite e le sedi di pronto soccorso è minima;
* - a ognuna delle sedi di pronto soccorso si assegnano almeno MINS città.
*
* Si scriva la funzione bestPart, che, utilizzando un algoritmo di partizionamento, dato l’elenco delle città,
* la matrice delle distanze, un insieme di M sedi di pronto soccorso e i valori MAXD e MINS,
* trovi la soluzione ottima e la ritorni come struttura dati (tipo SERVIZI).
* Non è necessario realizzare la funzione wrapper: è sufficiente rappresentare la funzione bestPart,
* che al suo interno deve usare due funzioni (da scrivere anche queste):
* - checkPart: funzione di verifica da chiamare in un caso terminale;
* - prunePart: chiamata per fare pruning (si dica esplicitamente di quali vincoli o criteri si può fare pruning e di quali no).
*/

int checkPart(SEDI M, int *sol, int n_citta, int MINS){
	/*
 		- a ognuna delle sedi di pronto soccorso si assegnano almeno MINS città.
	*/
	int n = SEDIgetSIZE(M);
	int count_sedi[n];
	for(int i=0; i<n; i++) count_sedi[i] = 0;

	for(int i = 0; i<n_citta; i++){
		if(sol[i] != -1){ //Se non è una sede
			count_sedi[sol[i]]++;
		}
	}	

	for(int i = 0; i<n; i++)
		if(count_sedi[i] < MINS) return 0;

	return 1;
}

int prunePart(int current_dist, int MAXD, int dist, int best){
	/* 
	- la distanza media tra le città servite e le sedi di pronto soccorso è minima;
	SI fa pruning sul minimo migliore ottenuto se si supera allora si taglia.
	*/
	if(dist > MAXD) return 1;
	if(current_dist >= best && best != -1) return 1;
	return 0;
}

void bestPart_r(int pos, int *sol, DISTMATR d, SEDI M, int MAXD, int MINS, int sum, int *best_res, int *best_sol, int *is_hub){
	if(pos >= DISTMATRgetSIZE(d)){
		if(checkPart(M, sol, DISTMATRgetSIZE(d), MINS)){
			if(*best_res == -1 || sum < *best_res){
				*best_res = sum;
				for(int i = 0; i<DISTMATRgetSIZE(d); i++){
					if(!is_hub[i]){
						best_sol[i] = sol[i];
					} 
				}
			}
		}
		return;
	}

	if(is_hub[pos]){ 
		sol[pos] = -1; //Marko la sede
		bestPart_r(pos+1, sol, d, M, MAXD, MINS, sum, best_res, best_sol, is_hub);
		return;
	}

	for(int i = 0; i<SEDIgetSIZE(M); i++){
		int distance = getDist(d, pos, getCity(M, i));

		if(prunePart(distance + sum, MAXD, distance, *best_res)) 
			continue;

		sol[pos] = i;
		bestPart_r(pos+1, sol, d, M, MAXD, MINS, sum, best_res, best_sol, is_hub);
	}

	return;
}


SERVIZI bestPart(ELENCO el, DISTMATR d, SEDI M, int MAXD, int MINS){
	int *sol = malloc(DISTMATRgetSIZE(d)*sizeof(int));
	int *best_sol = malloc(DISTMATRgetSIZE(d)*sizeof(int));
	int *is_hub = malloc(DISTMATRgetSIZE(d)*sizeof(int));
	for(int i = 0; i<DISTMATRgetSIZE(d); i++) is_hub[i] = 0;
	for(int i = 0; i<SEDIgetSIZE(M); i++){
		best_sol[getCity(M, i)] = -1;
		is_hub[getCity(M, i)] = 1;
	}

	int best = -1;
	bestPart_r(0, sol, d, M, MAXD, MINS, 0, &best, best_sol, is_hub);

	SERVIZI s = SERVIZIinit(DISTMATRgetSIZE(d));
	SERVIZIsetVal(s, best_sol, best);

	free(sol); free(is_hub);
	return s;
}