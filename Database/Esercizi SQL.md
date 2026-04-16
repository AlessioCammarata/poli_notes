1)
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

2)
```sql
--d) Per ogni persona nata dopo il 1970 che ha frequentato almeno 5 lezioni, visualizzare il codice fiscale, il nome, il numero di lezioni frequentate e il numero di istruttori (diversi) con cui ha fatto lezione

SELECT P.CodFisc, NomeP, COUNT(*), COUNT(DISTINCT CodI)
FROM PERSONA P, LEZIONE_PRIVATA LP
WHERE P.CodFisc = LP.CodFisc AND P.DataNascita >= 1/1/1971
GROUP BY P.CodFisc, NomeP
HAVING COUNT(*) >= 5;
```
3)
```sql
--Trovare codice corso, nome corso e numero totale di ore di lezione settimanali per i corsi del terzo anno per cui il numero complessivo di ore di lezione settimanali è superiore a 10 e le lezioni sono in piu` di tre giorni diversi della settimana.

SELECT C.CodCorso, NomeC, sum(OraFine - OraInizio) as Ore_Sett
FROM CORSO C, ORARIO-LEZIONI OL
WHERE C.CodCorso = OL.CodCorso AND Anno = 3
GROUP BY C.CodCorso, NomeC
HAVING Ore_Sett > 10 AND COUNT(DISTINCT GiornoSettimana) > 3;

```