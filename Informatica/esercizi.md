
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