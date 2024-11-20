
- Calcolare 79 - 13 in CA2

N = 8 bit
79 -> 2^7

79/2 -> 39 e 1
	39/2 -> 19 e 1
		19/2 -> 9 e 1
			9/2 -> 4 e 1
				4/2 -> 2 e 0
					2/2 -> 1 e 0
01001111
CA2 = 10110000 + 1 = 10110001

-13
13 = 00001101
CA2 = 11110010 + 1 = 11110011 = -13

 >01001111
 11110011
 01000010 = + 64 + 2 = 66
 
>Non c'è overflow, non può esserci perchè i segni sono discordi.

- Ordinare in ordine crescente:

N = 8
esadecimale BC, F7, AA

BC = 1011 1100 = -128 + 32 +16 + 8+ 4 = -68

F7  = 1111 0111 = -128 + 64 + 32 + 16 + 7 = -9

AA =  1010 1010 = -128 + 32 + 8 + 2 = -86

>AA, BC, F7

- Che cos'è la RAM, a cosa serve?
Random Access Memory -> Può accedere a qualsiasi indirizzo della memoria con lo stesso tempo.

Memoria volatile, serve ad avere accesso i dati in modo veloce si divide in statica e dinamica dove la statica tiene i dati in maniera statica mentre la dinamica esegue cicli di refresh per ricostituire le informazioni che altrimenti si perderebbero.

Serve a memorizzare dati e informazioni  più vicino alla CPU rispetto alle memorie di massa.

- Convertire una stringa in maiuscolo:
upper_str = str.upper()

- Abus Dbus calcola la memoria:
Abus = 10 bit
Dbus = parallelismo = 16 bit

Memoria = 2^10 * 2 byte = 2 kB

- Memoria, calcola Abus e Dbus.

- Clock di sistema e la sua unità di misura
Il clock è l'onda quadra, indica la frequenza su cui si basa la gestione delle operazioni, il clock cadenza le operazioni, si misura in Hz = 1/s, 
In quelli moderni si parla di GHz.
Oscillatore al quarzo, una pietra.

- CA2 e MES

N = 6 bit

A = 100111 in CAZ
B = 110001 in MES

calcolo
A = -32 + 7 = -25
B = -32 + 16 + 1 = - 17

- Ciclo macchina di un elaboratore
è il tempo che ci vuole per eseguire un istruzione, ma ogni istruzione ha tempo diverso.
rappresenta il ciclo di esecuzione delle istruzioni, si compone di 4 fasi:

- Fetch - Retrieve la istruzione da eseguire che è definita dal Program Counter
- Decode - Decodifica dell'istruzione cosi capisco cosa devo usare e cosa devo fare
- Execute  - Esegue l'istruzione
- WriteBack - Scrittura del risultato (opzionale)

- Ruolo dei registri PC, IR nel machine cicle

Il program counter viene incrementato ad ogni istruzione ed indica la posizione in memoria della prossima istruzione da eseguire.

L'istruction register è dove vengono

- Booleane
' = negato
f1 = x'y'z + xy'z + x'yz + xyz
f2 = yz + z + xy'z + x'y'z

x y z 
0 0 0 -> x'y'z'
0 0 1 -> x'y'z
0 1 0 -> x'yz'
0 1 1 -> x'yz
1 0 0 -> xy'z'
1 0 1 -> xy'z
1 1 0 -> xyz'
1 1 1 -> xyz

- Bus interni della CPU
I bus interni della CPU sono dei componenti fisici che permettono di comunicare la CPU con la ALU e la FPU.
La comunicazione avviene una per volta, sono molto veloci non hanno angoli retti, 
all'interno della CPU si viaggia alla frequenza del clock, GHz.
i bus interni sono cortissimi.

- Convertire numeri in base 2 e 8

6B = 0110 1011 = 001 101 011 = 1 5 3
C8 = 1100 1000 = 011 001 000 = 3 1 0

- Elencare i tipi di memoria in ordine di velocità | Gerarchia di memoria

Memorie di massa, memoria principale, cache di secondo livello(Motherboard), cache di primo livello (CPU), registri.

Nella cache ho un chip, accedi ai dati alle frequenze del processore.

- Differenza tra liste e tuple

Le liste sono un insieme di elementi mutabile, le tuple sono immutabili.
Una funzione può restituire una tupla ed anche una lista.

- python liste
lista = []
lista2 = lista[:]

Crea una copia della lista.

- Vantaggi e svantaggi
vantaggi:
	facile da espandere
	 costa poco
	 si standardizza
	
svantaggi:
	si crea il collo di bottiglia

- in quali basi si possono fare queste operazioni

24 + 12 = 41

23 * 3 = 124

Convertiamo con 2^x
2x+ 4 + 1x2 = 4x + 1
3x + 6 = 4x + 1
x = 5

23 x 3 = 124
Convertiamo con 2^x

(2x+3)*3 = x^2 + 2x + 4
6x+9 = x^2 +2x + 4
x^2 - 4x - 5 = 0

5 oppure -2, non si possono avere basi negative, **perciò solo 5.**


- Convertire il numero 746 in binario
base 10 = 746
base 8 = 746
base 16 = 746

base 10 = 746/2, 373 resto 0
			373/2, 186 resto 1
				186/2, 93 resto 0
					93/2, 46 resto 1
						46/2, 23 resto 0
							23/2, 11 resto 1
								11/2, 5 rsto 1
									5/2, 2 rsto 1
										2/2 1 rsto 0
											1/2 resto 1
1011101010

base 8 = 746 = 111 100 110
base 16 = 746 = 0111 0100 0110 

- Cosa fa la enumerate

Serve per associare un indice ad una lista in un ciclo for item in list:
Serve per estrarre posizione ed elemento corrispondente da un contenitore ordinato.

vocali = "aeiou"
i = 0
while i < len(vocali):
	 print(i,vocali[i])
	 +=1

- base esadecimale, base 10

N = 8 bit

D7 = 1101 0111
in base 10 binario puro equivale a = 128 + 64 + 16 + 7 = 215
in MES = -87
complemento a 2 = - 41

- complemento a 2 e MES
N = 5 bit

MES
-16 = 11000 -> Non si può rappresentare
10   = 01010

CA2
-16  = 10000
10   =  01010

- 20+12 = 32

1. base 3 -> No sicuramente
2. in nessuna base -> falso
3. qualunque base -> No sicuramente
4. qualunque base maggiore o uguale a 4 -> Vero

- Trasformare in CA2 
 N = 5 bit
25 ,-32, 32

Non si possono rappresentare con CA2 in 5 bit.

- Le operazioni aritmetiche richiedono tutte lo stesso tempo?

No le operazioni richiedono in tempo diverso a seconda di se si stanno svolgendo operazioni tra interi(ALU) o float(FPU), _questo perché non è possibile approssimare un numero con la virgola con precisione._
La FPU è più lenta della ALU.

La somma è più veloce della sottrazione.
La moltiplicazione il calcolatore la fa con lo shift delle somme.
La divisione è uno shift verso destra.

- Ordinare dal minore al maggiore
CA2 N = 8

AA = 1010 1010 = <
F3  = 1111 0011 =  <>
5F  =  0101 1111 = >

AA, F3, 5F

- RAM di 4 MB Abus = 20 bit

Dbus = 4 * 2^20  / 2^20 = 4 byte = 32 bit

- stampa le parole con lunghezza decrescente

```python
riga = input("Inserisci i nomi in una riga separati da spazi:")

lista_nomi = riga.split()
```

Se invece sei in un ciclo:
```python
lista_nomi = []
nome = input("Introduci nome o Q per uscire: ")
while nome.upper() != "Q":
	lista_nomi.append(nome)
	nome = input("Introduci nome o Q per uscire: ")
	
```

- Stampare tutte le parole in ordine senza le vocali.

```python
lista_nomi = []
vocali = "aeiou"
nome = input("Introduci nome o Q per uscire: ")
while nome.upper() != "Q":
	lista_nomi.append(nome)
	nome = input("Introduci nome o Q per uscire: ")

for nome in nome:
	for carattere in nomi:
		if carattere in "aeiouAEIOU":
			print("*",end="")
		else:
			print(carattere, end="")
	print()
```

- Ogni elemento contiene la lunghezza del nome corrispondente.