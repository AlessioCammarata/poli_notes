#### Tabelle derivate
Definisce una **tabella temporanea** che può essere utilizzata per ulteriori operazioni di calcolo.
La tabella derivata 
- ha la struttura di una SELECT 
- è definita all'interno di una clausola FROM 
- può essere referenziata come una normale tabella 
La tabella derivata permette di 
- calcolare più livelli di aggregazione 
- formulare in modo equivalente le interrogazioni che richiedono la correlazione

Esempio 1:
STUDENTE (Matricola, AnnoIscrizione) 
ESAME-SUPERATO (Matricola, CodC, Data, Voto)
	Trovare la media massima (conseguita da uno studente)
```sql
--Passo1: trovare la media per ogni studente (Tabella derivata)
SELECT Matricola, AVG(Voto) AS MediaStudente 
FROM ESAME-SUPERATO 
GROUP BY Matricola

--Passo2:trovare il valore massimo della media
SELECT MAX(MediaStudente) 
FROM (SELECT Matricola, AVG(Voto) AS MediaStudente 
		FROM ESAME-SUPERATO 
		GROUP BY Matricola) AS MEDIE;
```
Esempio 2:
	Per ogni anno di iscrizione, trovare la media massima (conseguita da uno studente)
```sql
--Passo1: trovare la media per ogni studente (Tabella derivata)
SELECT Matricola, AVG(Voto) AS MediaStudente 
FROM ESAME-SUPERATO 
GROUP BY Matricola

--Passo2: raggruppare gli studenti per anno di iscrizione e calcolare la media massima
SELECT AnnoIscrizione, MAX(MediaStudente)
FROM STUDENTE S, (SELECT Matricola, AVG(Voto) AS MediaStudente 
		FROM ESAME-SUPERATO 
		GROUP BY Matricola) AS MEDIE;
WHERE S.Matricola = Medie.Matricola
GROUP BY AnnoIscizione;
```
##### Correlazione con tabella derivata
Per ogni prodotto, trovare il codice del fornitore che ne fornisce la quantità massima
F (CodF, NomeF, NSoci, Sede) 
P (CodP, NomeP, Colore, Taglia, Magazzino) 
FP (CodP, CodF, Qta)
```sql
--Passo1: calcolare la Qta massima fornita per ogni prodotto
SELECT CodP, MAX(Qta) AS MQta 
FROM FP 
GROUP BY CodP

--Passo2: selezionare i fornitori che forniscono la Qta massima, prodotto per prodotto
SELECT CodP, CodF
FROM FP, (SELECT CodP, MAX(Qta) AS MQta 
			FROM FP 
			GROUP BY CodP) AS MQ;
WHERE FP.CodP = MQ.CodP --Condizione di join
		AND FP.CodF = MQ.CodF; --Correlazione 
```

---
#### Common Table Expression
Definisce una tabella temporanea che può essere utilizzata per ulteriori operazioni di calcolo.
La CTE 
- ha la struttura di una **SELECT** 
- è definita mediante la clausola **WITH** 
- può essere referenziata come una normale tabella 
La CTE è usata per 
- calcolare più livelli di aggregazione 
- formulare in modo equivalente le interrogazioni che richiedono la correlazione
Riferimenti 
- a CTE **precedentemente** definite nella stessa clausola WITH 
- ricorsivo
##### CTE vs Tabelle derivate
La CTE è preferita quando 
- è necessario fare riferimento a una tabella derivata più volte in una singola query 
- è necessario eseguire lo stesso calcolo più volte in più parti della query 
- si vuole aumentare la leggibilità di query complesse
#### Sintassi per definizione di CTE
WITH
cte_1 [(campo_A, ...)] AS 
(CTE query 1)  -> ==Query associata alla CTE==
{, cte_X AS (CTE query X) } 
SELECT campo_A, campo_B, ...  ==Query==
FROM cte_1 

Esempio:
	Trovare la media massima (conseguita da uno studente)
STUDENTE (Matricola, AnnoIscrizione) 
ESAME-SUPERATO (Matricola, CodC, Data, Voto)
```sql
--Passo 1: trovare la media per ogni studente 
WITH MEDIE AS 
	(SELECT Matricola, AVG(Voto) AS MediaStudenti 
	FROM ESAME-SUPERATO 
	GROUP BY Matricola)

--Passo 2: trovare il valore massimo della media
WITH MEDIE AS 
	(SELECT Matricola, AVG(Voto) AS MediaStudenti 
	FROM ESAME-SUPERATO 
	GROUP BY Matricola)
SELECT MAX(MediaStudenti) 
FROM MEDIE;
```

Esempio 2:
	Trovare tutte le compagnie aeree in cui il salario medio di tutti i piloti di quella compagnia è superiore alla media dei salari totali di tutti i piloti del database
PILOTI (CodP, Nome, Cognome, Compagnia, Salario)
```sql
WITH AVGSalarCompa AS 
	(SELECT Compagnia, AVG(Salario) AS AvgSalComp --Salario medio
	FROM PILOTI 
	GROUP BY Compagnia)
	mediaSalario AS
	(SELECT AVG(Salario) AS MediaSal
	FROM PILOTI)
SELECT Compagnia
FROM AVGSalarCompa AS SCM, mediaSalario MS
WHERE SCM.AvgSalComp > MS.MediaSal;
```
###### CTE referenziate
CITTA (CodC, NomeC, Provincia) 
AUTISTA (CodA, NomeA, Cognome, CodC) 
CORSA_GIORNALIERA (Data, CodA, Importo, Distanza)
>Considerando le distanze medie percorse per ciascuna città, calcolare la distanza massima percorsa per ciascuna provincia
```sql
--Distanza totale percorsa
WITH totDistanzaAutista AS
(SELECT SUM(Distanza) AS distanzaTot, CG.CodA, CG.CodC, NomeC, Provincia
 FROM CORSA_GIORNALIERA CG, CITTA C, AUTISTA A
 WHERE CG.CodA = A.CodA AND A.CodC = C.CodC
 GROUP BY CG.CodA,CG.CodC, NomeC, Provincia)
--Distanza media per ogni citta
distanzaMedia AS
(SELECT AVG(Distanza) AS avgDist, CodC, NomeC, Provincia
 FROM totDistanzaAutista
 GROUP BY CodC, NomeC, Provincia)
--Distanza massima per provincia
SELECT MAX(avgDist), Provincia
FROM distanzaMedia
GROUP BY Provincia;
```
###### CTE ricorsive
Non serve saperle

#### Query Spaziali
Si possono fare su DBMS che accettano dati spaziali, per esempio in MySQL.

#### Query JSON
Dati rappresentati attraverso file JSON.
Vengono di solito utilizzati nei **DBMS NO-SQL.**

---