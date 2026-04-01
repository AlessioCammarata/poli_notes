I registri t0-t6 sono effettivamente utilizzati come registri **temporanei**.
I registri s0-s11 sono registri di uso generale che a differenza dei t vengono trattati in modo differente durante la scrittura (e poi esecuzione del programma) ovvero **durante le chiamate a funzione**.
(I registri s vengono usati dal programma  chiamante per gestire i dati della routine)
Per passare dei valori ad una procedura si utilizzano i registri da a2-a7, mentre i valori di ritorno vengono memorizzati all'interno di a0 o a1.

```asm
.data 
# dichiarazione dati 
op1: .byte 3 
op2: .byte 2 
 .bss # allocazione spazio in memoria per risultato res: .zero 1 
 .text 
main: 
	lb t1,op1 # caricamento dati 
	la s11,op2 
	lb t2,0(s11) 
	add t1,t1,t2 # esecuzione somma 
	la s11,res 
	sb t1,0(s11) # salvataggio del risultato in memoria 
exit: 
	li a7,10 
	ecall
```
>data segment ->Dichiarazioni delle variabili.
>bss segment -> Dichiarazioni variabili globali e statiche non inizializzate
>text segment -> Di seguito sono riportate le istruzioni
>main procedure -> Punto di partenza del programma.

---
L’architettura RISC-V utilizza le seguenti dimensioni di data/memory : 
- Byte (8 bit) 
- Halfword (semplicemente half) (16 bit) 
- Word (32 bit) 
**Character** ha tipicamente dimensioni di 1 byte e una stringa è una serie di byte in sequenza.
```asm
.data 
	w1: .word 14 #Valore di inizizalizzazione -> 14
	b1: .byte 120 
	h1: .half 22 
	string: .string "\nThis is another string“ 
.bss 
	space: .zero 32
```
>.zero -> 1 bit, percio 32 bit.

