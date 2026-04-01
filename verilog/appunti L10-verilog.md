##### Passaggio argomenti e parametri
Passare dei parametri ad un modulo permette di creare dei moduli che hanno costanti diverse, per esemoio in un sommatore modificando il parametro di puo aumentare il numero di bit di ingresso.

Argomenti e parametri possono essere passati 
- **Per posizione** (come in C/C++) 
- **Per nome** 
	- L'ordine non è importante 
	- Utile con elenchi lunghi di argomenti e parametri 
	- Più facile lasciare un valore predefinito per un parametro o una porta scollegata
```verilog
module adder (cout,s, a, b, cin);

	parameter width = 2;
	input [width-1:0] a, b;
	input cin;
	output [width-1:0] s;
	output cout;
	
	assign [cout, s] = a + b + cin;
endmodule

// Nome modulo, #, nome istanza, valori
adder #(8) adder_8 (co, sum, a, b, ci);
```
**Parametro per posizione** 
- C'è solo un parametro in questo esempio e assume il valore 8 per questa istanza

**Argomenti per posizione** 
- I nomi elencati qui sono i nomi **attuali** delle porte 
	- Esempio: co (carry out) •
- I nomi nella definizione del modulo sono i nomi **formali** delle porte 
	- Esempio: cout (carry out)

```verilog
adder #(.width(8)) adder_8 (co, sum, a, b, ci);
```
**Parametro per nome** 
- .nome_param_formale(valore) 
- Il valore deve essere una costante in fase di compilazione
```verilog
//In questo caso non importa l'ordine in cui li metto, perche il riferimento è per nome
adder adder_2 (.a(a), .b(b), .cin(ci), .cout(co),.s(sum));
```

>Nel caso in cui si metta un argomento in meno nella chiamata.
```verilog
adder adder_2 (.s(sum), .a(a), .b(b), .cin(ci));
```
>Manca cout, questo significa che non la collego, questo va bene con le **uscite** non si puo non collegare un ingresso perche quello avrà **valore indeterminato** che si propaga poi nella logica.

```verilog
//Nel caso di argomenti per posizione si salta il valore solo a partire da sinistra senno devi utilizzare il passaggio per nome.
adder #(2) adder_2 (, sum, a, b, ci);
```
---
#### Ordine delle istruzioni
L'ordine delle istruzioni **non è importante in RTL** e nella **modellazione strutturale** .
- **Tutte le istruzioni sono eseguite in parallelo** 
	- Le espressioni sul lato destro sono valutate per prime 
	- Tutti le assegnazioni sono eseguite successivamente 
- Sono sempre equivalenti a uno **schema a blocchi**
```verilog
assign c = a & b; 
assign d = a | c; 
assign s = c ^ d;

//EQUIVALE

assign s = c ^ d; 
assign c = a & b; 
assign d = a | c;
```
---
#### Blocco generate
Il blocco generate è utile quando si hanno tanti blocchi uguali che presentano delle regolarità nelle connessioni.
Come nell'esempio di un sommatore composto da Full-Adder:
```verilog
module adder (s, cout, ci, a, b);

	parameter N=4;
	input [N-1:0] a, b;
	input ci;
	output [N-1:0] s;
	output cout;
	
	wire [N-2:0] co;
	genvar i; //Variabile interna

	generate
		for (i=0; i<N; i=i-1) begin
			if(i==0)            fadd(co[i], s[i], a[i], b[i], ci);
			else if(i==N-1)     fadd(cout, s[i], a[i], b[i], co[i-1]);
			else                fadd(co[i], s[i], a[i], b[i], co[i-1]);
		end
	endgenerate
endmodule
```
>Stiamo utilizzando un parametro N che consente di modificare la dimensione del sommatore.
>i è una variabile interna e viene utilizzata nel ciclo.
>Gli ingressi e le uscite sono vettori di N bit mentre co è un vettore di N-1 bit.
---
#### Modellazione comportamentale
La modellazione comportamentale è ottenuta utilizzando **blocchi always** 
- Un blocco always **descrive cosa fa il circuito a livello funzionale e algoritmico** 
- Descrive un processo 
	- Più blocchi always descrivono processi **indipendenti e simultanei** 
	- Le istruzioni in ogni processo vengono eseguite in modo autonomo 
- **Ogni processo viene eseguito ripetutamente per sempre** 
	- Deve contenere **istruzioni** che **bloccano l'esecuzione** 
		- Altrimenti la simulazione si blocca su un ciclo infinito 
	- **Ritardi** o elenco di sensibilità 
- Consiste in **dichiarazioni procedurali** 
	- Le istruzioni vengono **eseguite in ordine sequenziale** 
	- Alcune dichiarazioni procedurali sono **sintetizzabili** 
		- Altre NON lo sono 
- Può modellare sia circuiti **combinatori**, sia **sequenziali**
##### Blocco always
Sintassi:
>always @(==elenco_sensibilità==) begin 
>… 
>end

L’elenco di sensibilità definisce esattamente **quando** viene eseguito un blocco always, **una volta, dalla prima all'ultima istruzione** 
- Processo attivato quando uno qualsiasi dei segnali nell'elenco di sensibilità cambia valore 
- ***Attivo sui livelli*** (logica latch o combinatoria) 
	- **always** @(a or b) 
		- Logica combinatoria se le espressioni di processo contengono solo a e/o b 
		- Latch se compaiono altri segnali nelle espressioni di processo 
	>Il blocco viene eseguito se a o b cambiano.

- ***Attivo su fronti o misto***, fronti e livelli (flip-flop con reset sincrono o asincrono) 
	- **always** @(**posedge** clock) 
	- **always** @(**negedge** clock or reset)

Tutte le uscite di un blocco always devono essere di tipo **reg** 
- Le assegnazioni usano solo = o <= e non hanno bisogno della parola chiave assign 
- Non si può assegnare a un **wire** 
	- **wire** sono le uscite delle istruzioni assign 
- **reg e wire** possono essere entrambi usati come ingresso nelle espressioni (lato destro)

>reg assomiglia a un registro, ma non rappresenta necessariamente un registro:
```verilog
reg a, b, c; 
wire d, e; 
always @(c or d) 
	a = c & d; // porta logica AND
	
always @(c) // eseguito se cambia c, ma non quando cambia d! 
	a = c & d; // non è una porta logica (logica errata)
	
//Altro caso
always @(*) // Molto meglio! Sensibile per tutti i segnali nelle espressioni 
	a = c & d; // porta logica AND

//Altro caso (qui è effettivamente utile usare always)
always @(posedge clock) // flip-flop attivato sul fronte positivo 
	b = c & d; // porta AND + FF
```
>always @(\*) a = c & d; è Identico a (fuori dal blocco always) 
```verilog
assign e = c & d; // porta logica AND
```
###### Assegnazioni bloccanti e non bloccanti
Due tipi di assegnazione al tipo reg 
- Assegnazioni bloccanti hanno un **effetto immediato** (come in C/C++)
```verilog
always @(a or b) begin 
	a = b; 
	b = a; 
end
```
>1. Supponiamo che all’attivazione del blocco always a = 0 e b = 1 
>2. La prima istruzione viene eseguita, b è uguale a 1, quindi alla variabile a viene immediatamente assegnato il valore a = 1 
>	- La variabile a è cambiata 
>3. La seconda istruzione viene eseguita, a è ora uguale a 1, così alla variabile b viene immediatamente assegnato il valore b = 1 
>	- La variabile b non cambia
>4. Viene raggiunta la fine del blocco always. Poiché le assegnazioni bloccanti vengono risolte immediatamente (durante l’esecuzione del blocco, prima di procedere allo statement successivo), il cambiamento non causa una riattivazione del blocco stesso 
>	- Perché il blocco riesegua, dovrebbe avvenire il cambiamento (di almeno una) delle variabili della sensitivy list «fuori» dal blocco always in esame

- L'assegnazione **non bloccante** avviene **dopo un po' di tempo, assegna un valore futuro**
```verilog
always @(a or b) begin 
	a <= b; 
	b <= a; 
end
```
>1. Supponiamo che all’attivazione del blocco always a = 0 e b = 1 
>2. La prima istruzione viene eseguita, b è uguale a 1, quindi il **valore futuro** della variabile a è impostato a 1 
>	- Ma la variabile a rimane a 0 
>3. La seconda istruzione viene eseguita, a è ancora uguale a 0, così il **valore futuro** della variabile b è impostato a 0 
>	- Ma la variabile b rimane a 1 
>4. Viene raggiunta la fine del blocco always. **I valori futuri vengono solo adesso assegnati ai valori correnti, subito dopo la fine del blocco**. Così ora a = 1 e b = 0. Poiché entrambe le variabili sono cambiate fuori dal blocco always e sono nella lista di sensibilità, il blocco si riattiva e viene eseguito dall'inizio

***Stessa condizione di quella iniziale, quindi il blocco always si attiva di nuovo per sempre. Viene eseguito infinite volte!***

Assegnazioni bloccanti:
	Dopo l'esecuzione del blocco always 
	- a == 1, b == 1 
	- Il blocco always viene eseguito una volta
Assegnazioni non bloccanti:
	Dopo l'esecuzione del blocco always 
	- a == 1, b == 0 
	- Ma allora a == 0, b \== 1 
	- Ma allora a \==1, b \== 0 
	- E così via… 
	- Il blocco always viene eseguito infinite volte

**L'assegnazione non bloccante è semanticamente più accurata** 
- Consente di modellare oscillazioni, come nell'esempio precedente 
- Garantisce un comportamento più deterministico, anche senza clock 
- Si comporta esattamente come i signal in VHDL 
**L'assegnazione bloccante è più facile da usare** 
- Si comporta esattamente come le variabili in C/C++ 
- Con lo stile di modellazione visto in queste diapositive, basato solo su 
	- Blocchi combinatori 
		- **always** @(\*) 
	- Blocchi sequenziali 
		- **always** @(posedge clk) 
		- **always** @(posedge clk or negedge reset) 
		funziona esattamente allo stesso modo della non-bloccante 
>Useremo solo **l'assegnazione bloccante**.
---
###### Istruzione IF
Un'istruzione IF può essere utilizzata per modellare assegnazioni che dipendono da espressioni con segnali o variabili 
- Espressioni con **segnali**: calcolate durante la simulazione 
- Espressioni con **variabili**: calcolate durante la simulazione 
- Possono essere utilizzate **solo all'interno di un blocco always**
Sintassi 
>if (espressione) begin 
>…istruzioni … 
>end 
>else if (espressione) begin 
>…istruzioni … 
>end 
>… 
>else begin 
>…istruzioni … 
>end

Le parole chiave begin ed end non sono necessarie se il blocco è composto da una singola istruzione.
```verilog
if (alu_func == 2'b00)
	aluout = a +b;
else if (alu_func == 2'b01)
	aluout = a - b;
else if (alu_func == 2'b10)
	aluout = a & b;
else // alu_func == 2'b11
	aluout = a | b;
```
###### Istruzione CASE
Un'istruzione CASE può essere usata per modellare le assegnazioni che dipendono dal valore di una singola espressione che viene valutata 
- **IF – ELSE** può valutare invece **diverse espressioni in ogni clausola** 
- Possono essere utilizzate **solo all'interno di un blocco always**
Sintassi
>case (espressione) 
>scelta_case1: begin 
>…istruzioni …
> end 
> scelta_case2: begin 
> …istruzioni … 
> end 
> // altre scelte 
> default: begin 
> …istruzioni … 
> end 
> endcase

L'istruzione break utilizzata in minimizzare la logica generata C/C++ non è necessaria in Verilog.
```verilog
case (alu_ctr) 
	2'b00: aluout = a + b; 
	2'b01: aluout = a - b; 
	2'b10: aluout = a & b; 
	default: aluout = 16'bX; // Trattate come don't cares per minimizzare la logica generata
endcase
```
#### Circuito sequenziale Mealy (FSM)
```verilog
module mealyFSM (z, clk, reset, x); 
	input clk, reset, x; 
	output reg z; 
	reg cs, ns; 
	
	always @(x or cs) 
	begin: outputFunction // Nome del blocco always
		z = f1(x, cs); 
	end 
	always @(x or cs) 
	begin: nextStateTransition // Nome del blocco always
		ns = f2(x, cs); 
	end 
	always @(posedge clk or posedge reset) //Reset asincrono
	begin: stateReg //Nome del blocco always
		if (reset) cs = 0 else cs = ns; 
	end 
endmodule
```
#### Circuito sequenziale Moore (FSM)
```verilog
module mooreFSM (z, clk, reset, x); 
	input clk, reset, x; 
	output reg z; 
	reg cs, ns; 
	
	always @(cs) 
	begin: outputFunction // Nome del blocco always
		z = f1(cs); 
	end 
	always @(x or cs) 
	begin: nextStateTransition // Nome del blocco always
		ns = f2(x, cs); 
	end 
	always @(posedge clk) 
	begin: stateReg //Nome del blocco always
		if (reset) cs = 0 else cs = ns; //Reset sincrono
	end 
endmodule
```
---