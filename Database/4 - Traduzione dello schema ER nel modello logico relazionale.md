Si esegue sullo schema ***ER ristrutturato***, **senza gerarchie, attributi multivalore e composti**.
## Traduzione di entità
Ad ogni entità corrisponde una tabella con gli stessi attributi, gli attributi dell’Entità costituiscono lo schema della tabella.
L’identificatore (**semplice o composto**) dell’Entità diventa la **chiave primaria** della tabella.
Gli attributi opzionali dell’Entità sono attributi che possono assumere il valore NULL, sono evidenziati con «\*» nello schema della tabella.
Esempio:
	Persona(~~CodiceFiscale~~, Nome, Cognome, Professione*).
>Chiave primaria sottolineata
>Attributi opzionali indicati con asterisco
## Traduzione di Relazione
Per la traduzione di una Relazione 
1. Passo 1: Vengono prima tradotte le Entità che partecipano alla Relazione 
2. Passo 2: Viene quindi tradotta la Relazione. 
	1. Diverse regole di traduzione per **Relazione binaria e ternaria** 
	2. Per una Relazione binaria occorre **considerare la cardinalità massima e minima** con cui le Entità partecipano alla Relazione
### Traduzione di Relazione Binaria
#### Relazione binaria Molti a Molti
Esempio:
	Studente (~~Matricola~~, Nome, Cognome) 
	Corso (~~CodC~~, Nome) 
	Esame (~~Matricola~~, ~~CodC~~, Voto) -->Relazione

>Ogni relazione molti a molti corrisponde a una tabella 
- la **chiave primaria è la combinazione degli identificatori delle due entità collegate**. 
- è possibile ridenominare gli attributi della tabella che corrisponde alla relazione (necessario in caso di relazioni ricorsive)
##### Relazione binaria molti a molti ricorsiva
Esempio:
	Prodotto (~~CodP~~,, Nome, Costo) 
	Composizione (~~,CodComposto~~, ~~,CodComponente~~,, Quantità)
#### Relazione binaria uno a molti
Sono possibili due modalità di traduzione 
- **mediante attributi** 
- **mediante una nuova tabella**
##### (1,1)-(0,N):
Mediante attributi
Esempio:
	Persona (~~CF~~, Nome, Cognome, NomeComune, Data) 
	Comune ((~~Nome~~, Provincia)
>Si effettua quando l'entità che partecipa con cardinalità massima pari a 1 alla relazione, partecipa obbligatoriamente alla relazione (**cardinalità minima pari a 1**).
##### (0,1)-(0,N):
Alternativa 1: Traduzione mediante attributi 
	Studente (~~Matricola~~, Nome, Cognome, NomeFacoltà* , Data*) 
	Facoltà (~~Nome~~, Città) 
Alternativa 2: Traduzione mediante una nuova tabella 
	Studente (~~Matricola~~, Nome, Cognome) 
	Facoltà (~~Nome~~, Città) 
	Laurea (~~Matricola~~, NomeFacoltà, Data)
>Si effettua quando l'entità che partecipa con cardinalità massima pari a 1 alla relazione, partecipa opzionalmente alla relazione (**cardinalità minima pari a 0**).
#### Relazione binaria uno a uno
Sono possibili più traduzioni, **dipende dal valore della cardinalità minima**.
###### (1,1)-(1,1)
Alternativa 1 
	Rettore (~~Matricola~~, Nome, Cognome, NomeFacoltà, Data) 
	Università (~~Nome~~, Città) 
Alternativa 2 
	Rettore (~~Matricola~~, Nome, Cognome) 
	Università (~~Nome~~, Città, Matricola, Data)
>Si effettua quando entrambe le entità partecipano con cardinalità massima pari a 1 alla relazione, ed **entrambe le entità partecipano obbligatoriamente** alla relazione (**cardinalità minima pari a 1**)
###### (0,1)-(1,1)
Esempio
	Professore (~~Matricola~~, Nome, Cognome) 
	Università (~~Nome~~, Città, Matricola, DataElezione)
	
>Si effettua quando entrambe le entità partecipano con **cardinalità massima pari a 1** alla relazione, ma **solo una delle due entità partecipa obbligatoriamente** alla relazione (cardinalità minima pari a 1)
###### (0,1)-(0,1)
Alternativa 1 
	Professore (~~Matricola~~, Nome, Cognome) 
	Università (~~Nome~~, Città) 
	Rettore (~~Matricola~~, NomeUniversità, DataElezione) 
Alternativa 2 
	Professore (~~Matricola~~, Nome, Cognome) 
	Università (~~Nome~~, Città) 
	Rettore (Matricola, ~~NomeUniversità~~, DataElezione) 
Alternativa 3 
	Professore (~~Matricola~~, Nome, Cognome) 
	Università (~~Nome~~, Città, Matricola* , DataElezione*)

>Si effettua quando entrambe le entità partecipano con cardinalità massima pari a 1 alla relazione, ed **entrambe le entità partecipano opzionalmente** alla relazione (cardinalità minima pari a 0)
---
#### Relazione ternaria
Esempio:
	Studente (~~Matricola~~, Nome, Cognome) 
	Corso (~~CodC~~, Nome) 
	Tempo (~~Data~~) 
	Esame (~~Matricola, CodC, Data~~, Voto)
>Abbiamo messo le chiavi all'interno della tabella dell'associazione, aggiungendo l'attributo proprio voto.
>Aldilà delle tabelle le occorrenze sono rappresentate da una tabella che ha come PK le FK delle relazioni.

### Traduzione di Entità con Identificatore Esterno
Esempio:
	Cinema (~~CodC~~, Nome, Indirizzo) 
	Sala (~~Numero~~, ~~CodC~~, Capienza)
>La relazione è rappresentata **insieme all’identificatore** 
>La relazione contribuisce alla definizione dell’identificatore dell’**entità debole**.
### Vincoli di integrità referenziale
Esempio:
	Studente (~~Matricola~~, Nome, Cognome) 
	Corso (~~CodC~~, Nome) 
	Esame (~~Matricola~~, ~~CodC~~, Voto)
- Le relazioni rappresentano vincoli d’integrità referenziale
Esame(Matricola) REFERENCES Studente(Matricola) 
Esame(CodC) REFERENCES Corso(CodC)

Esempio 2:
	Stanza (~~CodStanza~~) 
	Libreria (~~CodLibreria, CodStanza~~, Nome) 
	Scaffale (~~CodScaffale, CodLibreria, CodStanza~~)

>Nel caso la chiave referenziata sia costituita da più attributi il vincolo è imposto sull'insieme degli attributi 

Libreria (CodStanza) REFERENCES Stanza (CodStanza) 
Scaffale (CodLibreria, CodStanza) REFERENCES Libreria (CodLibreria, CodStanza)

Ha piu FK perche fa riferimento ad una FK che compone la PK dell'altra relazione.
