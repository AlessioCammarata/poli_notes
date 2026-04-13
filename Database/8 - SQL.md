**Linguaggio per gestire le basi di dati relazionali** 
- Structured Query Language 
SQL include istruzioni per 
- definire lo schema di una base di dati relazionale 
- leggere e scrivere i dati 
- definire lo schema di tabelle derivate 
- definire i privilegi di accesso degli utenti 
- gestire le transazioni 
Il linguaggio è utilizzabile in modalità
- **interattiva** 
- **compilata** 
	- un linguaggio ospite (host) contiene le istruzioni SQL 
	- le istruzioni SQL si distinguono dalle istruzioni del linguaggio ospite per mezzo di opportuni artifici sintattici
---
#### Definizioni
Il linguaggio SQL è un linguaggio a **livello di set** 
- gli operatori operano su relazioni 
- il risultato è sempre una relazione 
Il linguaggio SQL è **dichiarativo** 
- descrive **cosa fare** e non come fare 
- si pone ad un livello di astrazione superiore rispetto ai linguaggi di programmazione tradizionali
- ---
### Istruzioni del linguaggio
Può essere diviso in 
- **DML** (Data Manipulation Language) 
	linguaggio di manipolazione dei dati 
- **DDL** (Data Definition Language) 
	linguaggio di definizione della struttura della base di dati
#### DML
Interrogazione di una base dati per estrarre i dati di interesse 
- SELECT 
Modifica dell’istanza di una base dati 
- INSERT: inserimento di nuove informazioni in una tabella 
- UPDATE: aggiornamento di dati presenti nella base dati 
- DELETE: cancellazione di dati obsoleti
#### DDL
Definizione dello schema di una base di dati 
- creazione, modifica e cancellazione di tabelle: CREATE, ALTER, DROP TABLE 
Definizione di tabelle derivate 
- creazione, modifica e cancellazione di tabelle il cui contenuto è ottenuto da altre tabelle della base dati: CREATE, ALTER, DROP VIEW 
Definizione di strutture dati accessorie per recuperare efficientemente i dati 
- creazione e cancellazione di indici: CREATE, DROP INDEX 
Definizione dei privilegi di accesso degli utenti 
- concessione e revoca di privilegi sulle risorse: GRANT, REVOKE 
Definizione di transazioni 
- terminazione di una transazione: COMMIT, ROLLBACK
---
### SELECT
**SELECT** [DISTINCT] ElencoAttributiDaVisualizzare 
**FROM** ElencoTabelleDaUtilizzare 
\[**WHERE** CondizioniDiTupla ] 
\[**GROUP BY** ElencoAttributiDiRaggruppamento ] 
\[**HAVING** CondizioniSuAggregati ] 
\[**ORDER BY** ElencoAttributiDiOrdinamento ]

Esempio:
	 Trovare il codice e il numero di soci dei fornitori di Milano:
```sql
SELECT CodF, NSoci -- Proiezione
FROM F -- Da dove prendo i dati
WHERE Sede='Milano'; -- Condizione di selezione
```
Esempio2:
	Trovare il codice di tutti i prodotti
```sql
SELECT CodP --Proiezione
FROM P;
```
>La select **non effettua la rimozione dei duplicati** in automatico, bisognerebbe mettere il valore distinct.

Esempio:
	Trovare il codice dei prodotti diversi forniti da almeno un fornitore
```sql
SELECT DISTINCT CodP --Proiezione come in algebra relazionale
FROM FP;
```

>Se non si vuole effettuare una proiezione (si vogliono tutti i dati) si mette l'asterisco \*.

Trovare il codice dei prodotti e la taglia espressa con la misura americana:
```sql
SELECT CodP, Taglia-14 [AS TagliaUSA] 
FROM P;
```
>Definizione di una **nuova colonna temporanea** per l’espressione calcolata, il nome della colonna temporanea può essere definito con la parola chiave **AS** (Alias).
#### WHERE
Permette di esprimere condizioni di selezione espresse singolarmente ad ogni tupla
Espressione booleana di predicati
Predicati semplici 
- espressioni di confronto tra attributi e costanti 
- ricerca testuale 
- valori NULL
Esempio:
	Trovare il codice dei fornitori di Milano
```sql
SELECT CodF 
FROM F 
WHERE Sede='Milano';
```
Nella where si possono utilizzare gli operatori:
- AND
- OR
- <>
- =
- LIKE/NOT LIKE
- IS NULL /NOT NULL
###### LIKE (Ricerca Testuale)
**NomeAttributo LIKE StringaDiCaratteri** 
il carattere ==\_== rappresenta un singolo carattere qualsiasi (obbligatoriamente presente) 
il carattere ==%== rappresenta una sequenza qualsiasi di n caratteri (anche vuota)

Esempio:
	Trovare il codice e il nome dei prodotti il cui nome inizia con la lettera C
```sql
SELECT CodP, NomeP 
FROM P 
WHERE NomeP LIKE 'C%'; --Condizione su NomeP
```
>Con la LIKE possiamo rispondere a query che ci chiedono se un nome è contenuto in un altro ed altre cose, tra l'altro si puo abbinare al NOT se non si vuole l'esepressione tra ''.

###### IS
**NomeAttributo IS \[NOT] NULL** 
In presenza di valori NULL qualsiasi predicato di confronto è falso.
Esempio:
	Trovare il codice e il nome dei prodotti con taglia maggiore di 44
```sql
SELECT CodP, NomeP 
FROM P 
WHERE Taglia>44;
```
>Le tuple per cui la taglia è NULL non sono selezionate: il predicato Taglia>44 è falso 
>In presenza di valori NULL qualsiasi predicato di confronto è falso.

Esempio2:
	Trovare il codice e il nome dei prodotti per cui la taglia non è indicata
```sql
SELECT CodP, NomeP 
FROM P 
WHERE Taglia IS NULL; --Vedo tutti quelli non NULL
```
#### Order By
**ORDER BY** NomeAttributo \[ASC | DESC] 
	{, NomeAttributo \[ASC | DESC] } -> SE HO PIU ATTRIBUTI
	
L’ordinamento può essere **crescente (ASC) o decrescente (DESC)** 
L’ordinamento implicito è crescente (ASC).
>**Gli attributi di ordinamento devono comparire nella clausola SELECT** 
- anche implicitamente (come SELECT \*)
Esempio:
	Trovare il codice dei prodotti e la loro taglia ordinando il risultato in ordine decrescente di taglia
```sql
SELECT CodP, Taglia 
FROM P 
ORDER BY Taglia DESC; --Descrivo come voglio vedere l'ordinamento
```

Esempio2:
	Trovare tutte le informazioni sui prodotti ordinando il risultato in ordine crescente di nome e decrescente di taglia.
```sql
SELECT * 
FROM P 
ORDER BY NomeP, Taglia DESC; --Ordina prima per nome e poi per taglia
```

>Posso usare **solo attributi ordinabili**, come interi, stringhe o temporali.

Esempio3 (alias):
	Trovare il codice dei prodotti e la taglia espressa come taglia americana, ordinando il risultato in ordine crescente di taglia
```sql
SELECT CodP, Taglia-14 AS TagliaUSA 
FROM P 
ORDER BY TagliaUSA; -- Non si puo scrivere qui Taglia-14
```
#### Join
Definito mediante le clausole **FROM e WHERE**.
Il risultato e l’**efficienza** dell’interrogazione
- sono **indipendenti** dall’ordine delle tabelle nella clausola FROM 
- sono **indipendenti** dall’ordine dei predicati nella clausola WHERE 
- l’ordine di esecuzione ottimale è selezionato dal **DBMS** (modulo ottimizzatore) 
Clausola FROM con N tabelle 
- almeno N-1 condizioni di join nella clausola WHERE
##### Prodotto cartesiano
Trovare il nome dei fornitori che forniscono il prodotto P2
```sql
SELECT NomeF 
FROM F, FP;
```
>Faccio il prodotto cartesiano tra le due tabelle F e FP.
##### Join
Trovare il nome dei fornitori che forniscono il prodotto P2
```sql
SELECT NomeF 
FROM F, FP 
WHERE F.CodF=FP.CodF; --Condizione di Join (legame semantico)
```
>Poi posso mettere le altre condizioni come per esempio P2
```sql
SELECT NomeF 
FROM F, FP 
WHERE F.CodF=FP.CodF AND CodP='P2';
```

>**Lo schema risultante è l'unione degli schemi delle due Tabelle**
---
###### Dichiaratività del linguaggio SQL
In algebra relazionale (linguaggio procedurale) **si definisce l’ordine** in cui sono applicati gli operatori.
In SQL (linguaggio dichiarativi) **l’ordine migliore è scelto dall’ottimizzatore** indipendentemente 
- dall’ordine delle condizioni nella clausola WHERE 
- dall’ordine delle tabelle nella clausola FROM
---
Altro esempio con 3 tabelle:
	Trovare il nome dei fornitori che forniscono almeno un prodotto rosso
```sql
SELECT NomeF 
FROM F, FP, P 
WHERE F.CodF=FP.CodF AND P.CodP=FP.CodP AND Colore='Rosso'; -- 2 condizioni di Join
```
>Notiamo che ci sono almeno N-1 condizioni di join nella clausola WHERE, dove N è il numero di tabelle nella FROM (In questo caso N=3 e quindi ci saranno 2 condizioni di join)
###### Sintassi Alternativa
Permette di specificare diversi tipi di join 
- outer join 
Permette di distinguere 
- condizioni di join 
- condizioni di selezione sulle tuple
```sql
SELECT [DISTINCT] Attributi 
FROM Tabella TipoJoin JOIN Tabella ON CondizioneDiJoin --Applico la join nella FROM
[WHERE CondizioniDiTupla];
```
>**TipoJoin** = < INNER | [FULL | LEFT | RIGHT] OUTER >
##### INNER join
Trovare il nome dei fornitori che forniscono almeno un prodotto rosso
```sql
SELECT NomeF 
FROM P INNER JOIN FP ON P.CodP=FP.CodP INNER JOIN F ON F.CodF=FP.CodF 
WHERE P.Colore='Rosso';
```
>Equivale alla Theta-Join
##### OUTER join
Trovare il codice e il nome dei fornitori insieme al codice dei relativi prodotti forniti, visualizzando anche i fornitori che non hanno forniture
```sql
SELECT F.CodF, NomeF, CodP 
FROM F LEFT OUTER JOIN FP ON F.CodF=FP.CodF;
```
>Rappresento tutte le tuple della tabella di sinistra (LEFT OUTER) che sono o non sono associate ad una tupla della tabella di destra, se non sono associate nel valore si mette NULL.
#### Funzione aggregata
Opera su un insieme di valori 
Produce come risultato un unico valore (aggregato) 
E’ indicata **nella clausola SELECT** 
- **non si possono indicare anche attributi non aggregati** 
- possono essere richieste **più funzioni aggregate contemporaneamente** 
>Le funzioni aggregate sono valutate solo dopo l’applicazione di tutti i predicati nella clausola WHERE
- **COUNT**: conteggio degli elementi in un attributo
- **SUM**: somma dei valori di un attributo
- **AVG**: media dei valori di un attributo
- **MAX**: massimo valore di un attributo
- **MIN**: minimo valore di un attributo
##### COUNT
Conteggio del numero di elementi di un insieme 
- righe di una tabella 
- valori (eventualmente distinti) di uno o più attributi 

    COUNT (<\*| [DISTINCT | ALL] ListaAttributi >)} 

>Se l’argomento della funzione è preceduto da **DISTINCT**, conta il numero di valori distinti dell’argomento.

Esempio:
	Trovare il numero di fornitori
```sql
SELECT COUNT(*) -- Conta le righe della tabella
FROM F;
```
Esempio 2:
	Trovare il numero di fornitori che hanno almeno una fornitura
```sql
SELECT COUNT(DISTINCT CodF)
FROM FP;
```
---
#### Funzioni aggregate e WHERE
Le funzioni aggregate sono valutate solo **dopo l’applicazione di tutti i predicati nella clausola WHERE.**

SUM, MAX, MIN e AVG 
- ammettono come argomento **un attributo o un’espressione** 
SUM e AVG 
- ammettono come argomento **solo attributi di tipo numerico o intervallo di tempo** 
MAX e MIN 
- richiedono che l’espressione **sia ordinabile** 
- possono essere applicate **anche su stringhe di caratteri e istanti di tempo**
Esempio: SUM:
	Trovare la quantità totale di pezzi forniti per il prodotto P2
```sql
SELECT SUM(Qta) -- Restituisce la Somma di Qta dopo l'applicazione della WHERE
FROM FP 
WHERE CodP='P2';
```
---
#### Group By
Clausola di raggruppamento 
		**GROUP BY** ElencoAttributiDiRaggruppamento 

L’ordine degli attributi di raggruppamento è **ininfluente.**
Nella clausola SELECT possono comparire solo 
- **attributi presenti nella clausola GROUP BY** 
- **funzioni aggregate** 

>Gli attributi univocamente determinati da attributi già presenti nella clausola GROUP BY possono essere aggiunti senza alterare il risultato.

Esempio:
	Per ogni prodotto, trovare la quantità totale di pezzi forniti
```sql
SELECT CodP, SUM(Qta) 
FROM FP 
GROUP BY CodP;
```
>In pratica ordino in gruppi in base a CodP e poi per ogni gruppo calcolo la Somma.

Esempio 2:
	Per ogni prodotto, trovare la quantità totale di pezzi forniti da fornitori con sede a Milano
```sql
SELECT CodP, SUM(Qta) 
FROM FP, F 
WHERE FP.CodF=F.CodF AND Sede='Milano' -- Join e selezione per la sede di Milano
GROUP BY CodP;
```
>I prodotti senza forniture non sono inclusi nel risultato.

Esempio3 :
	Per ogni prodotto, trovare il codice, il nome e la quantità totale fornita
```sql
SELECT P.CodP, NomeP, SUM(Qta) 
FROM P, FP 
WHERE P.CodP=FP.CodP 
GROUP BY P.CodP, NomeP
```
>Gli attributi univocamente determinati da attributi già presenti nella clausola GROUP BY possono essere aggiunti **senza alterare il risultato**
#### Having
Non è possibile utilizzare la clausola WHERE per definire condizioni di selezione sui gruppi.
Condizione di selezione sui gruppi espressa in clausola HAVING: 
				**HAVING** Condizioni di gruppo 
>permette di specificare condizioni **solo** su funzioni aggregate.

Esempio:
	Trovare la quantità totale di pezzi forniti per i prodotti per cui sono forniti in totale almeno 600 pezzi
```sql
SELECT CodP, SUM(Qta) 
FROM FP 
GROUP BY CodP 
HAVING SUM(Qta)>=600; -- Selezione sui dati aggregati
```

Esempio 2:
	Trovare il codice dei prodotti rossi forniti da più di un fornitore
```sql
SELECT FP.CodP 
FROM FP, P 
WHERE FP.CodP=P.CodP AND Colore='Rosso' 
GROUP BY FP.CodP 
HAVING COUNT(*)>1; -- Condizione di gruppo
```