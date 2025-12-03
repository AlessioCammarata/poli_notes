Per i problemi di ottimizzazione il paradigma greedy è un’alternativa: 
- all’approccio divide et impera 
- alla programmazione dinamica 
in generale: 
- di minor complessità, quindi più rapido 
- non sempre in grado di ritornare sempre una soluzione ottima.

**Principi**: 
- a ogni passo: per tentare di trovare una soluzione globalmente ottima si scelgono soluzioni localmente ottime 
- le scelte fatte ai singoli passi non vengono successivamente riconsiderate (**no backtrack**) 
- scelte localmente ottime sulla base di una funzione di appetibilità (costo).

>Vantaggi: 
>	algoritmo molto semplice e tempo di elaborazione molto ridotto 
 Svantaggi 
	soluzione non necessariamente ottima, in quanto non è detto che lo spazio delle possibilità sia esplorato in maniera esaustiva.

Appetibilità note in partenza e non modificate: 
- partenza: soluzione vuota 
- si ordinano le scelte per appetibilità decrescenti 
- si eseguono le scelte in ordine decrescente, aggiungendo, ove possibile, il risultato alla soluzione. 
Appetibilità modificabili: 
- come prima con modifica delle appetibilità e coda a priorità.
---
#### Funzioni di appetibilità (Sull'esempio selezione di attività 1)
***Funzioni che non portano sempre a soluzioni ottime***: 
- ordinamento per tempo di inizio crescente: un’attività che inizia presto ma dura a lungo impedisce di selezionarne altre
- ordinamento per durata crescente: un’attività breve che interseca 2 lunghe impedisce di selezionarle
***Funzione che porta sempre a soluzioni ottime***: 
- ordinamento per tempo di fine crescente: 
	supponiamo che k sia l’attività che finisce per prima: 
		- scegliere k non pregiudica nulla circa le attività che iniziano dopo che è finita 
		- se ci sono attività che iniziano prima di k, visto che finiscono dopo k, esse si intersecano e quindi al più se ne può scegliere una, quindi si sceglie proprio k

>In questo caso la soluzione migliore si ottiene solo **contando il numero di attività** e quindi non è importante quanto durino le attività, ma quante ne fai.

Esempio: Il cambiamonete
	Input: monetazione, resto da erogare 
	Output: resto con numero minimo di monete 
	Appetibilità: valore della moneta 
	Approccio greedy: a ogni passo moneta di maggior valore inferiore al resto residuo.
```c
//Soluzione greedy
for (i=0; i < numden; i++) { 
	coins[i] = amount / den[i]; 
	amount = amount - (amount/den[i])*den[i]; 
	printf("n. of %d cent coins = %d\n",den[i],coins[i]);
}
```
>Altri esempi sulle slide.
---
#### Codici di Huffman
Codice: stringa di bit associata a un simbolo s appartenente ad S 
- **a lunghezza fissa** 
- **a lunghezza variabile** 
Codifica: da simbolo a codice 
Decodifica: da codice a simbolo

**Codici a lunghezza fissa:** 
- numero di bit n = floor(log2 (card(S))) 
- vantaggio: facilità di decodifica 
- uso: simboli isofrequenti 
**Codici a lunghezza variabile:** 
- svantaggio: difficoltà di decodifica 
- vantaggio: risparmio di spazio di memoria
- uso: simboli con frequenze diverse.
>Esempio: Codice morse
##### Codici prefissi
Codice (libero da) prefisso: nessuna parola di codice valida è un prefisso di un’altra parola di codice. 
Codifica: giusta posizione di stringhe 
Decodifica: percorrimento di albero binario. 
PS: il codice Morse non è libero da prefisso, ma ci sono le durate e le pause.
>**Esempio slide 47.**
###### Costruzione dell'albero binario
Usiamo una **coda a priorità** (frequenze crescenti, proprietà greedy)
- Inizialmente: simbolo = foglia 
- Passo i-esimo: 
	- estrazione dei 2 simboli (o aggregati) a minor frequenza
	- costruzione dell’albero binario (aggregato di simboli): nodo =simbolo o aggregato, frequenza = somma delle frequenze
	- inserimento nella coda a priorità 
- Terminazione: coda vuota.