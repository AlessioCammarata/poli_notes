
### 8 luglio 2024

###### Esercizio 3:

Assumendo una memoria da 4 GB byte-addressable con celle di 1 Byte e parole di 4 Byte, una codifica per gli interi su 32 bit e puntatori che occupano 8 Byte, analizzare il seguente spezzone di codice:

```C
int **p;
char m[3][4], *pm[5];
```

e fornire lo spazio occupato in memoria (in Byte) dalle seguenti espressioni, motivando la risposta:

>I float sono 4 byte.
>I puntatori sono 8 byte
>Matrice 3\*4 di char = 12 byte
>M[0] -> la prima riga della matrice 
>pm -> vettore di puntatori -> 5\*8 Byte

###### Esercizio 4:

Un programma prende come parametri da linea di comando –s filename o –c filename. Nel primo caso,. deve stampare a video le parole lette dal file. Nel secondo caso, deve controllare se le righe del file sono ordinate (ogni riga contiene una sola parola); in caso contrario, deve stampare un messaggio di errore e il contenuto della prima riga che non rispetta l’ordinamento lessicografico. Le parole sono al più 20, e ciascuna parola è di al massimo 50 caratteri. Completa il seguente codice, inserendo le espressioni corrispondenti alle caselle numerate nella tabella sottostante:

```C
int **p;
char m[3][4], *pm[5];
```

###### Esercizio 5:

Per ciascuno dei programmi in tabella, dire se il codice può essere compilato ed eseguito: in caso affermativo, riportare cosa verrebbe stampato a video, altrimenti spiegare quale problema non consente di compilare e/o eseguire. Assumere un’architettura a 32 bit Little Endian, in cui gli interi sono codificati su 4Byte.

###### Esercizio 6:

Un programma gestisce le prenotazioni di visite ed esami di un ospedale. La funzione main riceve da linea di comando il nome di due file, e usa una struttura dati chiamata prestazione, che descrive una prestazione (cioè una visita o un esame) come nome della prestazione e contatore del numero di richieste.

La funzione main fa le seguenti operazioni: 
- funzione leggiPrestazioni: lettura delle prestazioni erogate dall’ospedale (massimo 50) dal primo file passato da linea di comando. Ogni riga riporta il nome della prestazione (massimo 29 caratteri) e un codice identificativo univoco (numero intero). Le righe sono in ordine casuale. La funzione salva i dati delle prestazioni in un vettore di strutture di tipo prestazione, usando la corrispondenza indice-valore. Tale funzione è già implementata. 
- funzione leggiPazienti: lettura delle richieste dei pazienti, contenute nel il secondo file passato da linea di comando. Ogni riga riporta l’identificativo di un paziente (6 caratteri) seguito da un numero variabile di numeri interi, identificativi delle prestazioni richieste per il paziente. La funzione deve incrementare il contatore di ciascuna prestazione richiesta. 
- funzione prestazionePiuRichiesta: ricerca della prestazione più richiesta nella giornata. La funzione deve stampare a video identificativo e nome della prestazione maggiormente richiesta. In caso di parità, scegliere la prestazione con identificativo minore. 
- funzione stampaStatistiche: stampare nome e numero di richieste delle prestazioni in ordine crescente di identificativo.

Implementare le funzioni leggiPazienti, prestazionePiuRichiesta e stampaStatistiche. I prototipi delle funzioni devono essere coerenti con il codice del main fornito.


---


