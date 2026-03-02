#### Ciclo di vita di un sistema informativo
La progettazione di una base di dati è una delle attività del processo di sviluppo di un sistema informativo.

1. **Studio di Fattibilità**
Determinazione dei costi delle diverse alternative e delle priorità di realizzazione delle componenti del sistema.
2. **Raccolta e analisi dei requisiti**
- Definizione delle proprietà e delle funzionalità del sistema informativo 
- Richiede interazione con l’utente 
- Produce una descrizione completa, ma informale del sistema da realizzare
3. **Progettazione**
- Suddivisa in progettazione dei dati e delle applicazioni 
- Produce descrizioni formali

>Dopo si può fare Implementazione o Prototipazione.
- **Implementazione**: Realizzazione del sistema informativo secondo le caratteristiche definite nella fase di progettazione, doo si fa validazione testing e funzionamento.
- **Prototipazione**: Realizzazione rapida di una versione semplificata del sistema per valutarne le caratteristiche. Può portare a modifiche dei requisiti o revisione del progetto.
---
#### Progettazione della base di dati
La progettazione della base di dati precede quella delle applicazioni che lo utilizzano.
Si da maggiore attenzione alla **fase di progettazione** rispetto alle altre fasi.

##### Fasi della progettazione
**Specifiche informali** della realtà d'interesse: (Requisiti applicativi)
- Proprietà dell'applicazione
- Funzionalità dell'applicazione
**Progettazione concettuale**: Si rappresentano le specifiche informali sotto forma di schema concettuale
- descrizione formale e completa, che fa riferimento ad un modello concettuale 
- indipendenza dagli aspetti implementativi (modello dei dati) 
- obiettivo è la rappresentazione del **contenuto informativo** della base di dati
**Progettazione logica**: Traduzione dello schema concettuale nello schema logico
- fa riferimento al **modello logico dei dati** prescelto (Si sceglie se usare relational o non)
- si usano **criteri di ottimizzazione** delle operazioni da fare sui dati 
- **qualità dello schema** verificata mediante tecniche formali (normalizzazione)
---
### Modello E-R
#### Entità
Rappresenta classi di oggetti del mondo reale (persone, cose, eventi, ...), che hanno
- proprietà comuni 
- esistenza autonoma 
Esempi: dipendente, studente, articolo 
>Un’occorrenza di un’entità è un oggetto della classe che l’entità rappresenta
#### Relazione
Rappresenta un legame logico tra due o più entità. 
Esempi: esame tra studente e corso, residenza tra persona e comune 
>Da non confondere con la relazione del modello relazionale, a volte indicata con il termine associazione.

Un’occorrenza di una relazione è una n-upla (coppia nel caso di relazione binaria) costituita da occorrenze di entità, una per ciascuna delle entità coinvolte.
Non vi possono essere n-uple identiche.

##### Cardinalità delle relazioni binarie
Sono specificate per ogni entità che partecipa ad una relazione.
Descrivono numero **minimo** e **massimo** di occorrenze di una relazione a cui può partecipare una occorrenza di un’entità 
- **minimo** assume i valori 
	- 0 (partecipazione opzionale) 
	- 1 (partecipazione obbligatoria) 
- **massimo** varia tra 
	- 1 (al più una occorrenza) 
	- N (numero arbitrario di occorrenze)
###### Corrispondenza 1 a 1 (uno a uno)
Un professore può essere rettore in una sola università, e l'università ha solo un rettore.
La minima è 0 perché non è per forza un professore ad essere rettore.
>**Per entrambe le entità la partecipazione massima è 1**
![[1-1.png]]
###### Corrispondenza 1 a N (uno a molti)
Una persona deve avere una residenza e al massimo una sola, mentre una residenza può essere associata a qualsiasi città, ma una residenza è unica per la città.
>**Una entità a cardinalità massima N mentre l'altra 1**.
![[1-n.png]]
###### Corrispondenza N a N (molti a molti)
Uno studente può superare N esami e ogni esame è associato a N corsi.
>**Entrambe le entità hanno cardinalità massima N**
![[n-n.png]]
**Limite di una relazione Binaria:**
>Non è possibile che uno studente sostenga lo stesso esame più di una volta.
###### Relazioni ternarie
Uno studente può sostenere lo stesso esame più di una volta in momenti diversi.
(Non spiegato bene)
>Le cardinalità minime raramente sono 1 per tutte le entità coinvolte in una relazione.
>Le cardinalità massime di una relazione **n-aria sono (praticamente) sempre N**
>- se la partecipazione di un’entità E ha cardinalità massima 1, è possibile eliminare la relazione n-aria e legare l’entità E con le altre mediante relazioni binarie
###### Relazione ricorsiva
Relazione di un’entità con se stessa.
Se la relazione non è simmetrica, occorre definire i due ruoli dell’entità.
>Per esempio un dipendente puo essere anche un superiore, percio bisogna usare una relazione ricorsiva.
---
#### Attributo
Descrive una proprietà elementare di un’entità o di una relazione.
Esempi:
	- cognome, nome, matricola sono attributi che descrivono l’entità studente
	- voto è un attributo che descrive la relazione esame 
>Ogni attributo è caratterizzato dal ***dominio*** l’insieme dei valori ammissibili per l’attributo.
###### Attributi composti (non atomici)
Esistono degli attributi che sono composti, per esempio si può pensare all'indirizzo che è composto da via numero civico e CAP oppure un orario che è fatto da ore minuti e secondi.
###### Cardinalità di un Attributo
Può essere specificata per gli attributi di entità o relazioni.
Descrive numero minimo e massimo di valori dell’attributo associati ad una occorrenza di un’entità o di una relazione:
- **se è omessa corrisponde ad (1,1)** 
- **minima 0** corrisponde ad attributo che ammette il valore nullo 
- **massima N** corrisponde ad attributo che può assumere più di un valore per la stessa occorrenza (attributo multivalore)
---
#### Identificatore (chiave primaria)
È specificato per ogni entità.
Descrive i concetti (attributi e/o entità) dello schema che permettono di individuare in modo univoco le occorrenze delle entità 
- ogni entità deve avere almeno un identificatore 
- può esistere più di un identificatore appropriato per un’entità 
>L’identificatore può essere 
- **interno o esterno** 
- **semplice o composto**
>Si dice semplice se è costituito da un solo attributo.
>Si dice composto se è costituito da più attributi.

###### Identificatore esterno
L’entità che non dispone internamente di attributi sufficienti per definire un identificatore è denominata **entità debole**.
**L’entità debole deve partecipare con cardinalità** (1,1) in ognuna delle relazioni che forniscono parte dell’identificatore.
La matricola identifica univocamente uno studente all'interno dell'Università, ma è possibile che in un'altra università possa esistere uno studente con la stessa matricola. (localmente al contesto)
![[external_id.png]]
>Un identificatore esterno può coinvolgere un'entità che è a sua volta identificata esternamente, non si devono generare cicli di identificazione
![[external_id_oss.png]]
>Inoltre è utile ricordare che le Relazioni non hanno identificatori.
#### Generalizzazione
Descrive un collegamento logico tra un’entità E, e una o più entità E1, E2,…, En, in cui E comprende come casi particolari E1, E2,…, En 
- E, detta **entità padre**, è una **generalizzazione** di E1, E2,…, En 
- E1, E2,…, En , dette **entità figlie**, sono una **specializzazione** di E
In pratica si suddivide un insieme in 2 o piu sottoinsiemi, per esempio l'insieme persona che può essere suddiviso in studente e docente (ma ci sono anche coloro che non sono studenti o docenti, o coloro che lo sono entrambi), dove ogni entità figlia ha i propri attributi.
###### Proprietà
- Ogni occorrenza di un’entità figlia è anche un’occorrenza dell’entità padre 
- Ogni proprietà dell’entità padre (attributi, identificatori, relazioni, altre generalizzazioni) è anche una proprietà di ogni entità figlia 
	- **proprietà nota come ereditarietà** 
- Un’entità può essere coinvolta in più generalizzazioni diverse
>Se i figli hanno stessi attributi questi si tolgono e vengono messi nel padre.
>Se nel padre ci sono attributi specifici dei figli vengono spostati nei figli.

- **Caratteristiche ortogonali** 
	- generalizzazione **totale** se ogni occorrenza dell’entità padre è un’occorrenza di almeno una delle entità figlie, **parziale** altrimenti 
	- **esclusiva** se ogni occorrenza dell’entità padre è al più un’occorrenza di una delle entità figlie, **sovrapposta** altrimenti
##### Sottoinsieme
**Caso particolare di generalizzazione con una sola entità figlia.** 
La generalizzazione è sempre parziale ed esclusiva.

---