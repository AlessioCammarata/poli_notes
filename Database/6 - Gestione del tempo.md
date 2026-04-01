Necessità di tracciare 
- eventi 
- evoluzione temporale di valori e/o relazioni 
Tipologie di modellazione 
- Attributi temporali 
- Relazione binaria 
- Relazione ternaria 
- Entità storicizzata
##### Attributi temporali
Rappresentazione di informazioni legate ad eventi che coinvolgono una singola entità/relazione.
Rappresentazione di eventi “unici” per ciascuna istanza dell'entità/relazione 
- esempi: data di nascita di una persona, anno di produzione di un film

#### Relazione binaria
![[binary_relationship.png]]
Si vuole rappresentare una serie temporale di eventi legati ad una Entità E del diagramma ER.
L’informazione di interesse è rappresentata mediante l’introduzione di 
- una entità ***Tempo*** 
	- identificata dalla informazione temporale su quando di verifica/inizia l’evento (ad esempio timestamp, data, data e ora) 
- una **relazione binaria R** che collega l’entità ***Tempo*** alla entità E 
	- Le (eventuali) informazioni sulla durata e/o sull’istante temporale di fine dell’evento e/o su altri aspetti che caratterizzano il verificarsi dell’evento nei diversi istanti temporali sono attributi della relazione R