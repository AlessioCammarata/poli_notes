I vettori sono insiemi di dati omogenei e può essere utilizzato come contenitore di dati.
- Senza alcun criterio di ordine
- Con un criterio di ordine
- Sfruttando la corrispondenza dato-indice

La corrispondenza da indice a dato è teta(1), molto veloce con complessità costante.
Invece il processo inverso ha una complessità diversa, poiche bisogna cercare nei valori e non negli indici, la complessita sarà al massimo N.

Utilizzo:
- Problemi in cui esistono corrispondenze tra numeri interi e dati
- L'intero è associato all'indice di una casella
-  È possibile che occorra un dato vuoto (nullo) per le caselle non utilizzate
---
### Problemi numerici

I vettori possono essere utilizzati nei problemi aritmetici: 
- per collezionare e manipolare (insiemi di) numeri 
- per rappresentare dati con struttura lineare (vettori) o tabellare (matrici) 
- per gestire corrispondenze tra numeri (indice e dato).

Problemi su insiemi di numeri:
- Problemi nei quali si gestiscono insiemi (gruppi) di dati numerici, con operazioni di I/O, unione, intersezione, … NON CONTA L'ORDINE 
- La soluzione spesso si basa su costrutti iterativi (eventualmente annidati) tali da: opercorrere gli elementi di un insieme opercorrere, per ogni elemento di un insieme, tutti gli elementi di un altro insieme.
---
### Intersezione tra 2 vettori

Bisogna controllare se ogni elemento di un vettore appartiene ad un altro.

---

### Menu con scelta su una parola

Il programma deve ottenere una stringa in input se la parola è fine termini senno chiami la funzione corrispondente.

- Facciamo una conversione da parola a numero, cosi utilizziamo lo switch case sui numeri convertiti che vengono utilizzati come selettori

```C
#include 
#include 
#define c_cerca 0 
#define c_modifica 1 
#define c_stampa 2 
#define c_fine 3 
#define c_err 4 

const int MAXL=51; 
int leggiComando (void); 
void menuParola (void); 
void cerca (char r[]) { 
	printf("cerca: %s\n", r); 
} 
void modifica (char r[]) { 
	printf("modifica: %s\n", r);
} 
void stampa (char r[]) { 
	printf("stampa: %s\n", r); 
}

void menuParola (void){ 
	int comando; 
	char riga[MAXL]; 
	int i, continua=1; 
	while (continua) { 
		comando = leggiComando(); 
		fgets(riga,MAXL,stdin); /* resto della riga */ 
		switch (comando) { 
			case c_cerca:
				cerca(riga); 
				break; 
			
			case c_modifica: 
				modifica(riga); 
				break; 
			case c_stampa: 
				stampa(riga); 
				break; 
			case c_fine: 
				continua=0;
				break; 
			case c_err: 
			default: 
				printf("comando errato\n"); 
		} 
	} 
}


int leggiComando (void) { 
	int c; 
	char cmd[MAXL]; 
	char tabella[4][9] = { 
		"cerca","modifica","stampa","uscita" 
	}; 
	printf("comando (cerca/modifica"); 
	printf("/stampa/uscita): "); 
	scanf("%s",cmd); strToLower(cmd); 
	
	c=c_cerca; 
	while(c<c_err && strcmp(cmd,tabella[c])!=0) 
		c++; 
	return (c); 
}
```

### Variante che utilizza il tipo Enum

È una specie di definizione che significa che tra parentesi graffe noi non mettiamo i campi come nelle struct ma i valori che puo assumere.
Stiamo definendo un tipo di dato che puo avere solo quei valori, è un intero limitato.

```c
enum semaforo {verde,rosso,giallo}; // 0 -> verde, 1 -> rosso, 2 -> giallo

//Di solito si definisce cosi:
typedef enum semaforo {verde,rosso,giallo} semaforo_e;

```