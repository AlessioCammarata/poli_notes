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
Gli attributi di ordinamento devono comparire nella clausola SELECT 
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
