==Limiti della ricorsione:==
- Ipotesi di indipendenza dei sottoproblemi
- Memoria occupata


Paradigma alternativo: **Programmazione Dinamica**: 
- memorizza le soluzioni ai sottoproblemi man mano che vengono trovate 
- prima di risolvere un sottoproblema, controlla se è già stato risolto 
- **riusa le soluzioni ai sottoproblemi già risolti** 
- meglio del divide et impera per sottoproblemi condivisi

>Vogliamo ridurre il numero di sottoproblemi che si ripetono inutilmente.

###### Come lavora
Conviene lavorare in un modello di **composizione** (bottom->up).
Ma si può lavorare anche in top-down, e si dice **ricorsione con memorizzazione**.
È applicabile a problemi di **ottimizzazione** e solo se sono verificate certe **condizioni**.
Si svolge in 3 passi: 
- **verifica di applicabilità** 
- **soluzione ricorsiva** come «ispirazione» 
- **costruzione bottom-up iterativa** della soluzione.
---
>***Esempio***: le catene di montaggio -> Slide 5-31
>***Esempio***: Prodotto di matrici (Parentesizzazione)-> Slide 31-68 (SOLO SULLE SLIDE)

Passo ricorsivo ottengo $O(2^n)$. (Brute- Force)
Passiamo alla programmazione dinamica:
- verifica di applicabilità: **caratterizzazione** della struttura di una soluzione ottima
- ispirazione: **definizione ricorsiva** del valore di una soluzione ottima
- Soluzione:
	- calcolo bottom-up del **valore di una soluzione ottima** 
	- **costruzione** di una soluzione ottima.

>==Principio di ottimalità di Bellman==: la **soluzione ottima** del problema comporta che siano ottime le soluzioni ai suoi sottoproblemi --> **sottostruttura ottima**. 
>La Programmazione Dinamica è applicabile solo a quei problemi di ottimizzazione che hanno una sottostruttura ottima.

Cio significa che ci possono essere piu strade per arrivare all'ottimo, ma l'ottimo è uno solo ed ogni soluzione è ottima per arrivare alla soluzione finale.

---
##### Applicabilità della programmazione dinamica
- Esistenza di una **sottostruttura ottima** 
- Esistenza di **molti sottoproblemi in comune**: 
	- vantaggio rispetto al divide et impera che assume l’indipendenza dei sottoproblemi 
	- numero di sottoproblemi polinomiale nella dimensione dei dati in ingresso 
	- sottoproblemi di complessità polinomiale 
- Approccio **bottom-up** (parte da tutti i problemi elementari)

###### Esistenza della sottostruttura ottima
1. Dimostrare che una soluzione del problema consiste nel fare una scelta. Questa scelta genera uno o più sottoproblemi da risolvere 
2. Per un dato problema, supporre di conoscere la scelta che porta a una soluzione ottima. Non interesse sapere come è stata determinata tale scelta 
3. Fatta la scelta, determinare quali sottoproblemi ne derivano e quale sia il modo migliore per caratterizzare lo spazio di sottoproblemi risultante
4. Dimostrare per assurdo che le soluzioni dei sottoproblemi utilizzate all’interno della soluzione ottima del problema devono essere necessariamente ottime con la tecnica del «taglia & incolla»:
	1. supporre che le soluzioni dei sottoproblemi non siano ottime 
	2. «tagliare» la sotto-soluzione non ottima e «incollare» una sotto-soluzione ottima 
	3. verificare che si è generata una contraddizione

>***Non assumere l’esistenza della sottostruttura ottima se non è possibile farlo.***

Esempio: 
	Dato un grafo orientato e non pesato e 2 suoi vertici u e v, trovare il cammino: 
	- **minimo** (formato dal minimo numero di archi). È necessariamente semplice: se non lo fosse, si potrebbe eliminare il ciclo e ridurre il numero di archi 
	- **massimo**: cammino semplice formato dal massimo numero di archi. Se non fosse semplice, percorrendo il ciclo infinite volte il problema perderebbe di significato
>La programmazione dinamica è applicabile?
>Descriviamo il problema:
	Quando cerco il cammino minimo posso **scartare a priori gli archi ricorsivi** perche allungano il cammino.
	Partendo dalla soluzione ottima posso spezzare il problema dicendo che il cammino per arrivare al penultimo nodo sia ottimo, e cosi via, 
	ricostruendo il percorso ottimo. -> **Sottostruttura ottima**.
	.
	Quando cerco il cammino massimo **non ho una** **Sottostruttura ottima** in quanto il grafo è aciclico, non è detto che la soluzione ottima al valore n-1 sia la ottima anche per arrivare ad n.
---
#### Memoization
Approccio simile al divide et impera ricorsivo, quindi top-down
- Memorizzazione delle soluzioni ai sottoproblemi 
- Lookup: evita di risolvere problemi già trattati 
- NB: alcuni autori la denominano Programmazione dinamica top-down

>***Esempio***: numeri di Fibonacci slide 118.
---
