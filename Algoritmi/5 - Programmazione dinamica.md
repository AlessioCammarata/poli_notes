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
