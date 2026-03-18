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
![[accorpamento_padre.png]]
##### Eliminazione del padre
L’accorpamento dell’entità padre nelle entità figlie è appropriato quando 
- la **generalizzazione è totale** 
- le operazioni d’accesso distinguono tra occorrenze delle diverse entità figlie (accesso più efficiente)
Nell'esempio la minima diventa 0 perché non è detto che un medico debba essere associato ad un reparto a cui è associato un volontario perciò non ha senso avere 1 ma **la minima diventa 0**.
![[kill_padre.png]]

>Non adatta per **copertura parziale** 
>- Possibilità di trasformarla in copertura totale aggiungendo un’entità figlia «Altri».
>Non stai rappresentando l'insieme completo mancano le altre rappresentanze.
>
>Non adatta per **copertura sovrapposta** 
>- Problema con ***identificatori duplicati***.
>Persone possono essere sia medici che volontari e quindi andranno in entrambe le tabelle.
##### Soluzioni miste
Le operazioni d’accesso distinguono tra occorrenze di alcune entità figlie (accesso più efficiente)

Si mantengono sia le entità figlie sia le padre, ma stabilisco un collegamento (associazione) che rappresenta l'appartenenza (per esempio personale is a medico o personale is a volontario).
![[padre&figli.png|645]]
>Utilizzo un identificatore esterno perciò, verso i figli mentre verso il padre la cardinalità sarà (0,1) perché appunto può appartenere o no.

Soluzione più generale e sempre applicabile 
- può essere dispendiosa per ricostruire l’informazione di partenza
---
>**Per le generalizzazioni a più livelli, si procede nello stesso modo, partendo dal livello inferiore**.
---
#### Analisi delle ridondanze
Rappresentano informazioni significative, ma derivabili da altri concetti 
- decisione se conservarle 
**Effetti delle ridondanze sullo schema logico** 
- semplificazione e velocizzazione delle interrogazioni 
- maggiore complessità e rallentamento degli aggiornamenti 
- maggiore occupazione di spazio

Esempio:
	L’attributo Media_voti è ridondante 
	- utile per velocizzare le interrogazioni relative al calcolo della media dei voti degli studenti 
	- se conservato, occorre integrare lo schema relazionale con l’indicazione di ridondanza dell’attributo
![[redundancy.png]]

---
#### Partizionamento di concetti
Partizionamento di entità o relazioni 
- rappresentazione migliore di concetti separati 
- separazione di attributi di uno stesso concetto che sono utilizzati da operazioni diverse 
- maggiore efficienza delle operazioni

>Raramente lo incontrerai.
---
#### Scelta degli identificatori primari 
Necessaria per definire la chiave primaria delle tabelle 
Un buon identificatore:
- **non assume valore nullo** 
- è costituito da **pochi attributi** (meglio 1!) 
- **possibilmente è interno** 
- è utilizzato da molte operazioni d’accesso 

Può essere opportuno introdurre codici identificativi.