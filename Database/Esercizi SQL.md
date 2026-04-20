#### Esercizi parte 1
 1.  
```sql
--a
/*
Per ogni studente, visualizzare la matricola e il voto massimo, minimo e medio conseguito negli esami
*/
SELECT S.MatrS, max(voto), min(voto), avg(voto)
FROM STUDENTE AS S, ESAME AS E
WHERE S.MatrS = E.MatrS
GROUP BY S.MatrS;

--b
/*
Per ogni studente, visualizzare la matricola, il nome e il voto massimo, minimo e medio conseguito negli esami
*/
SELECT S.MatrS, NomeS, max(voto), min(voto), avg(voto)
FROM STUDENTE AS S, ESAME AS E
WHERE S.MatrS = E.MatrS
GROUP BY S.MatrS, NomeS;

--c
/*
Per ogni studente che ha una media voti superiore al 28, visualizzare la matricola, il nome e il voto massimo, minimo e medio conseguito negli esami
*/
SELECT S.MatrS, NomeS, max(voto), min(voto), avg(voto) as media
FROM STUDENTE AS S, ESAME AS E
WHERE S.MatrS = E.MatrS
GROUP BY S.MatrS, NomeS
HAVING media > 28;

--d
/*
Per ogni studente che ha una media voti superiore al 28 e ha sostenuto esami in almeno 10 date diverse, visualizzare la matricola, il nome e il voto massimo, minimo e medio conseguito negli esami
*/
SELECT S.MatrS, NomeS, max(voto), min(voto), avg(voto) as media
FROM STUDENTE AS S, ESAME AS E
WHERE S.MatrS = E.MatrS
GROUP BY S.MatrS, NomeS
HAVING media > 28 AND COUNT(DISTINCT Data) >= 10;
```
---
2. ```sql
--d) Per ogni persona nata dopo il 1970 che ha frequentato almeno 5 lezioni, visualizzare il codice fiscale, il nome, il numero di lezioni frequentate e il numero di istruttori (diversi) con cui ha fatto lezione

SELECT P.CodFisc, NomeP, COUNT(*), COUNT(DISTINCT CodI)
FROM PERSONA P, LEZIONE_PRIVATA LP
WHERE P.CodFisc = LP.CodFisc AND P.DataNascita >= 1/1/1971
GROUP BY P.CodFisc, NomeP
HAVING COUNT(*) >= 5;
```
---
3. ```sql
--Trovare codice corso, nome corso e numero totale di ore di lezione settimanali per i corsi del terzo anno per cui il numero complessivo di ore di lezione settimanali è superiore a 10 e le lezioni sono in piu` di tre giorni diversi della settimana.

SELECT C.CodCorso, NomeC, sum(OraFine - OraInizio) as Ore_Sett
FROM CORSO C, ORARIO-LEZIONI OL
WHERE C.CodCorso = OL.CodCorso AND Anno = 3
GROUP BY C.CodCorso, NomeC
HAVING Ore_Sett > 10 AND COUNT(DISTINCT GiornoSettimana) > 3;

```
---
#### Esercizi query annidate
ORCHESTRA (CodO, NomeO, NomeDirettore, NumElementi) 
SALA (CodS, NomeS, Città, Capienza) 
CONCERTI (CodC, Data, CodO, CodS, PrezzoBiglietto)
1. ```sql
--Trovare il codice e il nome delle orchestre con più di 30 elementi che hanno tenuto concerti sia a Torino, sia a Milano e non hanno mai tenuto concerti a Bologna.

SELECT CodO, NomeO
FROM OSCHESTRA O
WHERE O.NumElementi > 30 
				AND CodO IN (
					SELECT CodO 
					FROM CONCERTI C, SALA S
					WHERE C.CodS = S.CodS AND S.Citta = "Torino")
				AND CodO IN(
					SELECT CodO 
					FROM CONCERTI C, SALA S
					WHERE C.CodS = S.CodS AND S.Citta = "Milano")   
				AND CodO NOT IN (
					SELECT CodO 
					FROM CONCERTI C, SALA S
					WHERE C.CodS = S.CodS AND S.Citta = "Bologna"); 


--Con operatore Join:
SELECT CodO, NomeO
FROM OSCHESTRA O, CONCERTI C, SALA S
WHERE O.NumElementi > 30 AND S.Citta = "Torino" AND C.CodS = S.CodS                                           AND O.CodO = C.CodO;
--La condizione su Milano diventa complicata, quindi non conviene.

--Con operatori EXISTS
SELECT CodO, NomeO
FROM OSCHESTRA O
WHERE O.NumElementi > 30 
				AND EXISTS (
					SELECT * 
					FROM CONCERTI C, SALA S
					WHERE C.CodS = S.CodS AND C.CodO = O.CodO AND S.Citta = "Torino")
				AND EXISTS (
					SELECT * 
					FROM CONCERTI C, SALA S
					WHERE C.CodS = S.CodS AND C.CodO = O.CodO AND S.Citta = "Milano")
				AND NOT EXISTS (
					SELECT * 
					FROM CONCERTI C, SALA S
					WHERE C.CodS = S.CodS AND C.CodO = O.CodO AND S.Citta="Bologna");
```
---
CORSO (CodCorso, NomeC, Anno, Semestre) 
ORARIO-LEZIONI (CodCorso, GiornoSettimana, OraInizio, OraFine, Aula)
2. ```sql
--Trovare le aule in cui non si tengono mai lezioni di corsi del primo anno.

SELECT DISTINCT OL1.Aula
FROM ORARIO-LEZIONI OL1
WHERE OL1.Aula NOT IN(
				SELECT OL.Aula 
				FROM CORSO C, ORARIO-LEZIONI OL
				WHERE C.CodCorso = OL.CodCorso AND Anno = 1); 

--Con NOT EXISTS
SELECT DISTINCT OL1.Aula
FROM ORARIO-LEZIONI OL1
WHERE NOT EXISTS(
				SELECT * 
				FROM CORSO C, ORARIO-LEZIONI OL2
				WHERE C.CodCorso = OL2.CodCorso AND OL2.Aula = OL1.Aula 
					AND Anno = 1); 
```
#### Esercizi foglio 2
GARA (CodG, Luogo, Data, Disciplina) 
ATLETA (CodA, Nome, Nazione, DataNascita) 
PARTECIPAZIONE (CodG, CodA,PosizioneArrivo, Tempo)
1. ```sql
--Trovare le nazioni per cui concorrono almeno 5 atleti nati prima del 1980, ciascuno dei quali abbia partecipato ad almeno 10 gare di sci di fondo.

SELECT DISTINCT A.Nazione
FROM ATLETA A
WHERE DataNascita < 1/1/1980 AND A.CodA IN(
				SELECT P.CodA 
				FROM PARTECIPAZIONE P, GARA G
				WHERE P.CodG = G.CodG AND G.Disciplina = "Sci di fondo"
				GROUP BY P.CodA
				HAVING COUNT(*) >= 10)
GROUP BY Nazione
HAVING COUNT(*) >= 5;
```
---
**EDITORE (CodE, NomeEditore, Indirizzo, Città) 
PUBBLICAZIONE (CodP, Titolo, NomeAutore, CodE) 
LIBRERIA (CodL, NomeLibreria, Indirizzo, Città) 
VENDITA (CodP, CodL, Data, CopieVendute)**
2. ```sql
--Trovare il nome degli editori per cui almeno 10 pubblicazioni sono state vendute nel 2002 nelle librerie di Roma in più di 2.000 copie.

SELECT DISTINCT E.Nome
FROM EDITORE E, PUBBLICAZIONE P
WHERE E.CodE = P.CodE AND E.CodP IN(
				SELECT V.CodP
				FROM VENDITA V, LIBRERIA L
				WHERE V.CodL = L.CodL AND Data >= 1/1/2002 AND Data <= 31/12/2002 
										AND L.Citta = "Roma"
				GROUP BY V.CodP
				HAVING SUM(V.CopieVendute) > 2000)
GROUP BY E.CodE, E.NomeEditore
HAVING COUNT(*) >= 10;
```
---
SALA_RIUNIONI(CodS, NumeroMaxPosti, Proiettore) 
PRENOTAZIONE_SALA(CodS, Data, OraInizio, OraFine, CodDip) 
DIPENDENTE(CodDip, Nome, Cognome, DataNascita, Città)
6. ```sql
--Visualizzare il codice e il numero massimo di posti delle sale dotate di proiettore che sono state prenotate almeno 15 volte per riunioni che iniziano prima delle ore 15:00, ma non sono mai state prenotate per riunioni che cominciano dopo le ore 20:00

SELECT SR.CodS, SR.NumeroMaxPosti
FROM SALA_RIUNIONI SR
WHERE SR.Proiettore = 1 AND SR.CodS IN (
							SELECT PS.CodS
							FROM PRENOTAZIONE_SALA PS
							WHERE OraInizio < '15:00'
							GROUP BY PS.CodS
							HAVING COUNT(*) >= 15)
						AND SR.CodS NOT IN (
							SELECT PS.CodS
							FROM PRENOTAZIONE_SALA PS
							WHERE OraInizio > '20:00');

```