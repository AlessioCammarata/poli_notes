Esercizio 1:
	ALLOGGIO (CodA, Indirizzo,Città, Superficie) 
	CONTRATTO-AFFITTO (CodC, DataInizio, DataFine, NomePersona, CodA, RettaMensile)
```sql
--a) Trovare il codice, l’indirizzo e la città degli alloggi che hanno una superficie superiore alla superficie media degli alloggi delle città in cui si trovano.

SELECT CodA, Indirizzo, Citta
FROM ALLOGGIO A
WHERE Superficie > (SELECT AVG(A1.Superficie)
					FROM ALLOGGIO A1
					WHERE A.Citta = A1.Citta)
					
--OPPURE

SELECT A.CodA, A.Indirizzo, A.Citta
FROM ALLOGGIO A, (SELECT A1.Citta, AVG(A1.Superficie) AS Media
					FROM ALLOGGIO A1
					GROUP BY A1.Citta) AS MediaSuperfici
WHERE A.Citta = MediaSuperfici.Citta AND A.Superficie > MediaSuperfici.Media;

```
---
AEREI (Matr, Modello, NumPosti) 
ORARIO (Sigla, CittàPartenza, CittàArrivo, OraPart, OraArr) 
VOLI (Sigla, Matr, Data, PostiPren)
```sql
--a) Trovare le tratte (città di partenza, città di arrivo) che non sono state mai effettuate con un aereo modello Boing-747.

SELECT DISTINCT CittaPartenza, CittaArrivo
FROM ORARIO
WHERE Sigla NOT IN (SELECT V.Sigla
						FROM VOLI V, AEREO A
						WHERE V.matr = A.matr AND A.modello = 'Boing-747')
```
---
SALA_RIUNIONI (CodS, NumeroMaxPosti, Proiettore) 
DIPENDENTE (CodDip, Nome, Cognome, DataNascita, Città) 
PRENOTAZIONE_SALA (CodS, Data, OraInizio, OraFine, CodDip)
```sql
--b) Visualizzare per ogni sala il codice della sala, il numero massimo di posti e il numero di prenotazioni considerando solo l’ultima data in cui la sala è stata prenotata.

SELECT SR.CodS, SR.NumeroMaxPosti, COUNT(*)
FROM SALA_RIUNIONI SR, PRENOTAZIONE_SALA PS
WHERE SR.CodS = PS.CodS AND Data = (SELECT MAX(Data)
									FROM PRENOTAZIONE_SALA PS2
									WHERE PS2.CodS = PS.CodS)
GROUP BY SR.CodS, NumeroMaxPosti;

--OPPURE

SELECT SR.CodS, SR.NumeroMaxPosti, COUNT(*)
FROM SALA_RIUNIONI SR, PRENOTAZIONE_SALA PS, (SELECT CodS, MAX(Data) AS MAXDATA
									FROM PRENOTAZIONE_SALA PS2
									GROUP BY CodS) AS NP
WHERE SR.CodS = PS.CodS AND PS.Data = NP.MAXDATA AND PS.CodS = NP.CodS
GROUP BY SR.CodS, NumeroMaxPosti;

--OPPURE

SELECT SR.CodS, NumeroMaxPosti, Nprenotazioni.N
FROM SALA_RIUNIONI SR, (
				SELECT CodS, COUNT(*) AS N
				FROM PRENOTAZIONE_SALA PS
				WHERE (CodS, Data) IN ( 
						SELECT CodS, MAX(Data) 
						FROM PRENOTAZIONE_SALA 
						GROUP BY CodS 
				)
				Group BY CodS
			) Nprenotazioni
WHERE SR.CodS = Nprenotazioni.CodS;
```
---
RAGAZZO(CodFiscale, Nome, Cognome, DataNascita, CittàResidenza) 
ATTIVITA’(CodAttività, NomeA, Descrizione, Categoria) 
CAMPO-ESTIVO(CodCampo, NomeCampo, Città) 
ISCRIZIONE-PER-ATTIVITA’-IN-CAMPO-ESTIVO(CodFiscale, CodAttività, CodCampo, DataIscrizione)
```sql
--b) Visualizzare il nome e cognome del ragazzo che ha partecipato al maggior numero di campi estivi per l’attività della categoria «Tennis».



```