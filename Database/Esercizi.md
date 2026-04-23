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


WITH Partecipazioni AS(
	SELECT CodFiscale, COUNT(DISTINCT CodCampo) AS N_Campi
	FROM ISCRIZIONE-PER-ATTIVITA’-IN-CAMPO-ESTIVO IPA
	WHERE IPA.CodAttivita IN (
				SELECT CodAttivita
				FROM ATTIVITA A
				WHERE A.Categoria = 'Tennis'
			)
	GROUP BY IPA.CodFiscale
)
SELECT Nome, Cognome
FROM Partecipazioni P, RAGAZZO R
WHERE P.CodFiscale = R.CodFiscale AND P.N_Campi = (
									SELECT MAX(P1.N_Campi)
									FROM Partecipazioni P1
								);

--OPPURE

SELECT Nome, Cognome
FROM ISCRIZIONE-PER-ATTIVITA’-IN-CAMPO-ESTIVO IPA, ATTIVITA A, RAGAZZO R
WHERE A.Categoria = 'Tennis' AND IPA.CodAttivita = A.CodAttivita AND R.CodFiscale = IPA.CodFiscale
GROUP BY R.CodFiscale, Nome, Cognome
HAVING COUNT(DISTINCT CodCampo) = (
			SELECT MAX(N_CAMPI_PER_RAGAZZO.N_Campi)
			FROM (
SELECT R.CodFiscale, COUNT(DISTINCT CodCampo) AS N_Campi
FROM ISCRIZIONE-PER-ATTIVITA’-IN-CAMPO-ESTIVO IPA, ATTIVITA A, RAGAZZO R
WHERE A.Categoria = 'Tennis' AND IPA.CodAttivita = A.CodAttivita AND R.CodFiscale = IPA.CodFiscale
GROUP BY R.CodFiscale
			) AS N_CAMPI_PER_RAGAZZO
		);

--OPPURE

SELECT Nome, Cognome
FROM RAGAZZO R,(
	SELECT R.CodFiscale, COUNT(DISTINCT CodCampo) AS N_Campi
	FROM ISCRIZIONE-PER-ATTIVITA’-IN-CAMPO-ESTIVO IPA, ATTIVITA A, RAGAZZO R
	WHERE A.Categoria = 'Tennis' AND IPA.CodAttivita = A.CodAttivita AND               R.CodFiscale = IPA.CodFiscale
	GROUP BY R.CodFiscale --Raggruppamento nella tabella derivata
) AS N_CAMPI_PER_RAGAZZO2
WHERE R.CodFiscale = N_CAMPI_PER_RAGAZZO2.CodFiscale AND N_CAMPI_PER_RAGAZZO2.CodFiscale = --QUERY NIDIFICATA DI SOPRA PER TROVARE MAX
;

--OPPURE

WITH NUM_CAMPI_PER_RAGAZZO AS(
	SELECT CodFiscale, COUNT(DISTINCT CodCampo) AS N_Campi
	FROM ATTIVITA A, ISCRIZIONE-PER-ATTIVITA’-IN-CAMPO-ESTIVO IPA
	WHERE Categoria = 'Tennis' AND A.CodAttivita = IPA.CodAttivita
	GROUP BY CodFiscale
)
SELECT Nome, Cognome
FROM RAGAZZO R, NUM_CAMPI_PER_RAGAZZO NCPR
WHERE R.CodFiscale = NCPR.CodFiscale.CodFiscale AND NCPR.N_Campi = (
									SELECT MAX(N_Campi)
									FROM NUM_CAMPI_PER_RAGAZZO
)
```
---
5) BLOCCO 3
LUOGO (CodL, Nome, Città, Regione, CapienzaMax) 
EVENTO (CodE, Titolo, Tipo) 
EDIZIONE (CodE, Data, CodL, NumeroPartecipanti)
```sql
--Tra gli eventi per cui sono state organizzate edizioni in almeno 3 città diverse, visualizzare il titolo dell’evento a cui ha complessivamente (considerando tutte le edizioni dell’evento) partecipato il maggior numero di persone.
WITH EventiPossibili AS (
	SELECT EV.CodE, Titolo, COUNT(Citta) AS N_EVENTI, SUM(NumeroPartecipanti) AS Persone
	FROM EVENTO EV, EDIZIONE ED, LUOGO L
	WHERE EV.CodE = ED.CodE AND ED.CodL = L.CodL
	GROUP BY EV.CodE, Titolo
	HAVING COUNT(DISTINCT L.Citta) >= 3
)
SELECT EP.Titolo, EP.Persone, EP.N_EVENTI
FROM EventiPossibili EP
WHERE Persone = (
	SELECT MAX(Persone)
	FROM EventiPossibili EP1
);
```
6) BLOCCO 3
FILM (CodF, Titolo, Data_uscita, Genere, DurataMinuti) 
CINEMA (CodC, Nome, Indirizzo, Città) 
SALA (CodC, NumeroSala, Capienza) 
PROIEZIONE (CodC, NumeroSala, Data, OraInizio, OraFine, CodF)
```sql
--Visualizzare il titolo di ciascun film che ha una durata inferiore della durata media dei film appartenenti allo stesso genere, e che è stato proiettato un numero di volte maggiore del numero medio di proiezioni dei film appartenenti allo stesso genere.
WITH ProiezioniPerFilm AS ( --Raggruppo le proiezioni e le conto x ogni film
	SELECT CodF, COUNT(*) AS N_Proiezioni 
	FROM PROIEZIONE 
	GROUP BY CodF 
)
SELECT F.Titolo
FROM FilmCandidati PF, FILM F
WHERE F.CodF = PF.CodF AND F.DurataMinuti < ( 
				SELECT AVG(F1.DurataMinuti) 
				FROM FILM F1 
				WHERE F1.Genere = F.Genere 
			) AND PF.N_Proiezioni > (
				SELECT AVG(PF2.N_Proiezioni) 
				FROM FILM F2, ProiezioniPerFilm PF2 
				WHERE F2.CodF = PF2.CodF AND F2.Genere = F.Genere
			);

--OPPURE

-- 1: Conto le proiezioni per ogni singolo film
WITH ProiezioniPerFilm AS (
    SELECT CodF, COUNT(*) AS N_Proiezioni
    FROM PROIEZIONE
    GROUP BY CodF
),
-- 2: Raggruppamento per genere per la DURATA
MedieDurata AS (
    SELECT Genere, AVG(DurataMinuti) AS Media_D
    FROM FILM
    GROUP BY Genere
),
-- 3: Raggruppamento per genere per le PROIEZIONI
MedieProiezioni AS (
    SELECT F.Genere, AVG(PF.N_Proiezioni) AS Media_P
    FROM FILM F, ProiezioniPerFilm PF
    WHERE F.CodF = PF.CodF
    GROUP BY F.Genere
)
--Unisco tutti i pezzi!
SELECT F.Titolo
FROM FILM F, ProiezioniPerFilm PF, MedieDurata MD, MedieProiezioni MP
WHERE F.CodF = PF.CodF
  AND F.Genere = MD.Genere
  AND F.Genere = MP.Genere
  AND F.DurataMinuti < MD.Media_D
  AND PF.N_Proiezioni > MP.Media_P;

```