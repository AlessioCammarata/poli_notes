Attività per la ristrutturazione dello schema ER 
- Analisi delle ridondanze 
- Eliminazione delle generalizzazioni 
- Partizionamento di concetti (entità, relazioni) 
- Eliminazione degli attributi composti 
- Eliminazione degli attributi multivalore 
- Scelta degli identificatori primari
---
Lo schema ER ristrutturato tiene conto di aspetti realizzativi
- non è più uno schema concettuale 
**Obiettivi** :
- **eliminazione** dei costrutti per cui non esiste una rappresentazione diretta nel modello relazionale 
- **trasformazioni** volte ad aumentare l’efficienza delle operazioni di accesso ai dati
Attività:
- Eliminazione degli attributi composti 
- Eliminazione degli attributi multivalore 
- Eliminazione delle generalizzazioni 
- Analisi delle ridondanze 
- Partizionamento di concetti (entità, relazioni) 
- Scelta degli identificatori primari
#### Eliminazione degli attributi composti
Gli attributi composti non sono rappresentabili nel modello relazionale.
Eliminazione degli attributi: 
- **si rappresentano in modo separato gli attributi componenti** 
	- adatta se è necessario accedere separatamente a ciascun attributo 
- **si introduce un unico attributo che rappresenta la concatenazione degli attributi componenti** 
	- adatta se è sufficiente l’accesso all’informazione complessiva
>Quale opzione si sceglie?
>Se si accede singolarmente ad ogni attributo si rappresentano tutti se invece basta l'informazione complessiva si utilizza uno unico.

Esempio:
	Devo accedere alla via o al cap di un indirizzo. -> Separo gli attributi
	Devo accedere solo all'indirizzo -> Collasso i singoli attributi all'interno di uno solo
#### Eliminazione degli attributi multivalore
Non possono essere rappresentati nel modello relazionale.
Gli attributi multivalore vengono rappresentati utilizzando una relazione tra: 
- l'entità iniziale 
- una nuova entità 
>**Attenzione** alla cardinalità della nuova relazione

##### Informazione condivisa (1-N)
Esempio:
	Si suppone che una persona possa avere più di un titolo di studio e che lo stesso titolo di studio possa essere in possesso di più persone.
	Si crea una nuova entità Titolo di studio dove la cardinalità sarà (1-N) per la persona (Ed è sempre lo stesso) mentre per il titolo di studio sarà (1-N) dal vincolo:
	"lo stesso titolo di studio possa essere in possesso di più persone".

>**Il titolo è una proprietà di una persona**, devono sempre partecipare alla relazione (1-?), al posto del punto interrogativo abbiamo messo N perché. lo stesso titolo di studio può essere in possesso da più persone.
>Come si traduce poi?

Persona(~~CF~~,Nome,Cognome,professione*)
~~Titolo_di_studio(Titolo_di_studio)~~ ->Contiene solo la PK non è un'entità, la cancelliamo
Ha(~~CF,Titolo_di_studio~~) -> ==Una persona N titoli di studio e viceversa==

>Se una persona ha un titolo di studio avrà una associazione all'interno della tabella, non serve avere una entità Titolo di studio perché è implicità la sua unicità dentro l'associazione.
##### Informazione univoca (1-1)
Esempio:
	Si suppone che una persona possa avere più di un numero di telefono ma che lo stesso numero di telefono possa essere in possesso di una sola persona
>In questo caso un telefono è associato ad una sola persona perciò la cardinalità dell'associazione Ha è (1,N)-(1,1), la minima è sempre 1 perché è un attributo proprio dell'entità.
>Come si traduce poi?

Persona(~~CF~~,Nome,Cognome,professione*)
Telefono(~~Telefono~~,CF) ->==Essendo 1 come massima pilota l'associazione==
#### Eliminazione delle generalizzazioni
Non sono rappresentabili direttamente nel modello relazionale 
- sono sostituite da entità e relazioni 
Metodi di ristrutturazione 
- accorpamento delle entità figlie nell’entità padre -> **Esplosione figli**
- accorpamento dell’entità padre nelle entità figlie -> **Uccisione padre**
- sostituzione della gerarchia con relazioni -> **Tengo le entità**
Esempio:
![[esempio_ristrutturazione.png]]
##### Accorpamento nell'entità padre
Tutte le proprietà delle entità figlie si spostano nell'entità padre, le relazioni in cui partecipavano le figlie vengono ora associate al padre.
>Incide sulla cardinalità minima dell'associazione e degli attributi che si spostano nel padre.

- Ogni attributo che si sposta dal figlio al padre ha **cardinalità minima 0**
- Anche l'associazione adesso che coinvolge l'intero personale adesso ha **cardinalità minima 0** 
- Si aggiunge un informazione per descrivere il tipo di persona (etichetta per distinguere il personale)
