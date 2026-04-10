Un registro è una raccolta di **edge-triggered flip-flop o latch** (Useremo solo FF)
- I registri, **acquisiscono e memorizzano i dati in base a un trigger**, un fronte di salita o di discesa 
- Fungono da elementi di archiviazione temporanea dei dati 

Per codificare un registro utilizzando la modellazione comportamentale in Verilog, se ne replica il comportamento utilizzando una variabile a cui assegnare un valore **da memorizzare fino al successivo trigger.**

In Verilog si usa il tipo **reg** per dichiarare le variabili che modellano gli elementi di memoria e possono rappresentare logica combinatoria o sequenziale.
Esempio: per un registro a 4 bit che consente una sola operazione alla volta, di lettura o di scrittura, possono servire: 
- Una variabile di tipo reg da 4 bit per modellare i circuiti di memoria del registro 
- Un segnale di lettura/scrittura come ingresso (di più se si ammettono operazioni multiple) 
- Un segnale di reset che consente di impostare il valore nel registro a 0 
- Porte d’ingresso: 
	- write_data per il trasferimento dei dati da scrivere nel registro 
	- read_write che indica che si fa una scrittura nel registro (== 0) o lettura del suo dato (== 1) 
	- clock per sincronizzazione e reset per azzeramento del valore memorizzato 
- Porta d’uscita: 
	- read_data su cui il dato memorizzato nel registro è disponibile quando si fa una lettura

**Il comportamento del registro è completamente sincrono** 
- Letture e scritture avvengono solo sul fronte di salita del clock 
- Anche il reset è sincronizzato allo stesso fronte
```verilog
module reg4b (output [3:0] read_data, 
			input [3:0] write_data, 
			input clk, rst, rw); 
	reg [3:0] storage;
	
	//Se rw == 1, assegno storage senno metto alta impedenza, (porta tri-state)
	assign read_data = rw ? storage : {default:'bz}; 
	
	always @(posedge clk) //Solo nel fronte di salita
		//Assegnazione non bloccante con reset sincrono
		if (!rst)
			storage <= 0; 
		else if (!rw) 
			storage <= write_data; 
endmodule
```

>Si può estendere il comportamento per supportare operazioni multiple, a seconda delle specifiche
- Piu porte di lettura/scrittura
- Letture simultanee alle scritture
- Scritture simultanee sono ammesse alternando le porte (solo una attiva per volta).
```verilog
module reg4b (output [3:0] rd1, rd2,
			input [3:0] wd1, wd2, 
			input clk, rst, rw);
...
endmodule
```
---
Realizzazione del registro a 4 bit precedente con flip-flop di tipo D 
- Si istanziano 4 FF (uno per bit) 
- Per scrittura (rw == 0): si propaga l’input ip agli ingressi D dei flip-flop 
- Per lettura (rw == 1): si propaga il valore memorizzato dai flip-flop all’uscita out 
- Siccome non si possono fare istanziazioni condizionali, si usa un costrutto ternario (multiplexer) per selezionare l’input dei flip-flop
```verilog
module ffD (output reg op, input ip, clk); 
	always @(posedge clk) 
		op <= ip; 
endmodule

module reg4b (output [3:0] out, 
			input [3:0] ip, clk, rw); 
	wire [3:0] d; 
	
	ffD d3(d[3], rw ? d[3] : ip[3], clk); 
	ffD d2(d[2], rw ? d[2] : ip[2], clk); 
	ffD d1(d[1], rw ? d[1] : ip[1], clk);
	ffD d0(d[0], rw ? d[0] : ip[0], clk); 
	
	assign out <= d; 
endmodule
```

Esempio: registro parametrico:
```verilog
module regNb #(parameter WIDTH = 4) ( 
	output [WIDTH-1:0] read_data, 
	input [WIDTH-1:0] write_data, 
	input clk, rst, rw); 
	 
	 reg [WIDTH-1:0] storage; 
	 
	 assign read_data = rw ? storage : {default:'bz}; 
	 
	 always @(posedge clk) 
		if (!rst) 
			storage <= 0; 
		else if (!rw) 
			storage <= write_data; 
endmodule
```
>Possiamo generalizzare il registro a 4 bit visto in precedenza parametrizzando la larghezza della parola memorizzata, in questo modo possiamo decidere la dimensione quando lo creiamo.
---
#### Register file
I register files contengono una **matrice di registri**. 
- È necessario fornire **indirizzi di lettura e scrittura** per determinare da quale registro si leggono o scrivono i dati 
- Le porte di dato e d’indirizzo d’ingresso e d’uscita possono essere **multiple**
- Ciò significa che possono esserci **diverse** porte read_address, write_address, read_data e write_data che **consentono eseguire più di un’operazione alla volta su diversi registri del register file** 
- Se sono consentite più operazioni contemporaneamente, devono essere prese in considerazione le **priorità tra le varie operazioni** 
**Esempio** per un register file con 8 registri a 8 bit, 1 porta di scrittura e 2 di lettura 
- Due letture contemporanee ammesse 
- Lettura e scrittura in mutua esclusione
Esempio:
	register file 8x8, 2 read / 1 write.
Le uscite r1 ed r2 spesso sono sempre pilotate (sotto invece in 𝑍 se non attive)
```verilog
module regFile (output [7:0] r1, r2
				input [7:0] data,
				input clk, rst,
				input [1:0] r1r2w,
				input [2:0] p1, p2, p3);
				
	reg [7:0] storage [7:0];
	
	assign r1 = (r1r2w == 1) ? storage[p2] : {default:'bz};
	assign r2 = (r1r2w == 2) ? storage[p3] : {default:'bz};
	
	always @(posedge clk)
		if(!rst)
			storage <= 0
		else if (r1r2w == 0)
			sorage[p1] <= data; //Write
	
endmodule
```
---
Esempio:
	register file 4x32 strutturale
Definizione strutturale di un register file 4x32, combinando insieme 
- 4 registri da 32 bit con output enable 
- 2 decoder 2:4 con enable per abilitare letture e scritture nei singoli registri interni 
	- L’enable attivo abilita l’uscita decodificata dal decoder e inattivo imposta tutte le uscite a 0
```verilog
module reg4x32 (r_data , w_data, r_addr, w_addr, r_en, w_en, clk, rst);
	output [31:0] r_data,
	input [31:0] w_data;
	input [1:0] r_addr, w_addr;
	input r_en, w_en, clk, rst;
				
	wire w_r3, w_r2, w_r1, w_r0, r_r3, r_r2, r_r1, r_r0;
	
	dec2x4en r_dec (r_addr[1], r_addr[0], r_en, r_r3, r_r2, r_r1, r_r0);
	dec2x4en w_dec (w_addr[1], w_addr[0], w_en, w_r3, w_r2, w_r1, w_r0);
	
	reg32en r0 (r_data, w_data, r_r0, w_r0, clk, rst);
	reg32en r1 (r_data, w_data, r_r1, w_r1, clk, rst);
	reg32en r2 (r_data, w_data, r_r2, w_r2, clk, rst);
	reg32en r3 (r_data, w_data, r_r3, w_r3, clk, rst);
	
endmodule
```
---
#### Memorie RAM
**RAM (Random Access Memory) è memoria leggibile e scrivibile**:
- Nome «particolare», ideato diversi decenni fa per contrastare storage ad accesso sequenziale come le unità a nastro 
Logicamente è uguale a un register file: **memoria con ingressi di indirizzo, ingressi/uscite di dato e opportuni segnali di controllo** 
- RAM di solito **ha una porta**, mentre il register file ha di solito due o più 
- RAM è in genere **più grande delle circa 512 o 1024 parole** dei register file 
- RAM in genere memorizza i bit con approcci di archiviazione più efficienti dei flip-flop 
- RAM è tipicamente implementata su un chip in una forma quadrata anziché rettangolare per ridurre le lunghezze (e quindi i ritardi) delle connessioni più lunghe
Esempio:
	RAM con una porta, lettura e scrittura sincrone, abilitazione per memoria e output
```verilog
module RAM_sp_sr_sw ( data, // Data input/output 
					  addr, // Address input 
					  clk, // Clock input 
					  cs, // Chip select, se attivo si possono fare le operazioni
					  we, // Write/Read enable 
					  oe); // Output enable
					  
	parameter DATA_WIDTH = 8; //Dimensione ciascuna parola in bit
	parameter ADDR_WIDTH = 8; // dimensione indirizzo in bit
	parameter RAM_DEPTH = 1 << ADDR_WIDTH: // 2^8, sto shiftando a sinistra di 8
	
	inout [DATA_WIDTH-1:0] data; 
	input [ADDR_WIDTH-1:0] addr;
	input                  clk;
	input                  cs;
	input                  we;
	input                  oe;
	
	
	reg [DATA_WIDTH-1:0] data_out; 
	//Creo una matrice di 256 righe (0:255) e ciascun elemento è un vettore di 8         bit (7:0)
	reg [DATA_WIDTH-1:0] mem [0:RAM_DEPTH-1]; //256X8 bit
	reg oe_r;
	
	//Gestisce l'operazione di scrittura, quando we è ad 1, prendo il valore di          ingresso (data) e lo metto nella memoria nell'indirizzo addr
	always @(posedge clk) : MEM_WR 
		if (cs && we) 
			mem[addr] = data;
	
	//Gestisce l'operazione di lettura, quando oe è 1 e we è 0 metto in data_out         il valore che sta nella cella all'indirizzo addr, e metto oe_r ad 1 per            attivare l'assign che sta in fondo
	always @(posedge clk) : MEM_RD 
		if (cs && oe && !we) begin //Unica porta, non puoi r o w contemporaneamente
			data_out = mem[addr]; 
			oe_r = 1; 
		end 
		else 
			oe_r = 0; 
	
	//Assign che serve a collegare data_out all'uscita se voglio l'output
	assign data = (cs && oe_r && !we) ? data_out : 'bz;

endmodule
```
#### Memorie ROM
Memoria che **può essere letta, ma non può essere scritta** 
- Linee di dato sono solo delle uscite 
- Non è necessario un ingresso di selezione read/write 
**Vantaggi** rispetto a RAM:
- **Compattezza** → possono essere più piccole 
- **Non volatile** → conserva i dati memorizzati anche se l'alimentazione è spenta 
- **Velocità** → possono essere più veloci, soprattutto rispetto a determinati tipi di RAM (DRAM) 
- **Bassa potenza** → non necessita di alimentazione per conservare i bit 
>Si preferisce usare ROM invece di RAM se i dati memorizzati non cambiano (o cambiano raramente) 
  Ad esempio, la tabella di conversione da gradi Celsius a Fahrenheit in un termometro digitale.

Modulo ROM con inizializzazione dei dati tramite il task di sistema $readmemb
```verilog
module ROM ( 
					data, // Data input/output 
					addr, // Address input 
					clk,  // Clock input 
					cs,   // Chip select, se attivo si possono fare le operazioni
					re, );// Read Enable
					  
	parameter DATA_WIDTH = 8; //Dimensione ciascuna parola in bit
	parameter ADDR_WIDTH = 8; // dimensione indirizzo in bit
	parameter RAM_DEPTH = 1 << ADDR_WIDTH: // 2^8, sto shiftando a sinistra di 8
	
	output [DATA_WIDTH-1:0] data; //Dati solo in output
	input  [ADDR_WIDTH-1:0] addr;
	input                   clk;
	input                   cs;
	input                   re;
	
	
	//Creo una matrice di 256 righe (0:255) e ciascun elemento è un vettore di 8         bit (7:0)
	reg [DATA_WIDTH-1:0] mem [0:RAM_DEPTH-1]; //256X8 bit
	reg                      re_r;
	
	initial : MEM_INIT
		$readmemb ("mem_i.data", mem);
	
	//Gestisce l'operazione di lettura, quando re è 1 metto re_r ad 1 per                attivare l'assign che sta in fondo, che utilizza l'indirizzo in input
	always @(posedge clk) : MEM_RD 
		if (cs && re)
			re_r = 1; 
		else 
			re_r = 0; 
	
	//Assign che serve a collegare data_out all'uscita
	assign data = (cs && re_r) ? mem[addr] : 'bz;

endmodule
```
---
####  Inizializzazione delle memorie
È comune che una simulazione o un firmware richiedano il **caricamento di dati in un array di memoria, RAM o ROM**. 
I dati si possono caricare con i task di sistema **\$readmemh** (per dai in formato **esadecimale**) e **$readmemb** (per dati in formato **binario**).
```verilog
$readmemh("hex_mem_file.mem", mem_array, [start_addr], [end_addr]);
$readmemb("bin_mem_file.mem", mem_array, [start_addr], [end_addr]);
```
Il file di input consiste in una **serie di valori in formato esadecimale o binario, separati da caratteri di spaziatura** (singolo spazio, TAB, newline, ecc., anche mischiati tra loro) 
- Si possono includere commenti dopo **«//» fino a fine riga** 
I dati nel file non devono superare la capienza dell'array di destinazione 
- Gli eccedenti vengono troncati, con o senza avvertimenti da parte del compilatore
|**In caso di problemi** con la lettura dei dati da un file di inizializzazione 
- **Eliminare i commenti** 
- **Uniformare la tipologia di caratteri usati per gli spazi**
#### Introduzione al TestBench
Finito il design del sistema, bisogna verificarne il corretto comportamento.
Lo scopo principale è assicurarsi che il comportamento del design sia coerente con le specifiche di progetto.
**A tale scopo, si usano dei «testbench».**
Sono fatti da codice extra, che non fa parte del sistema da controllare, ma che mediante l’applicazione di una opportuna sequenza di stimoli è in grado di verificare il corretto funzionamento del sistema da ispezionare 
**Terminologia**:
- **MUT** – Module Under Test (modulo da controllare) 
- **DUT** – Design Under Test (design da controllare)
##### Come scriverlo
- Definire gli **input per DUT/MUT come reg** e le **uscite come wire**.
- Definire una porzione di codice dedicata all’**inizializzazione del sistema** in esame, solitamente tramite un **blocco initial** 
	- In questa porzione, generalmente sono considerate solo **variabili di tipo reg** 
	- Questo blocco viene eseguito **una sola volta** 
- Definire i **blocchi always** necessari a descrivere il comportamento dell’unità di **benchmark** (modulo che genera stimoli di test e verifica le risposte del DUT) 
	- Una parte dell’inizializzazione o della generazione degli stimoli può apparire anche in blocchi di questo tipo, ad esempio i segnali periodici/clock 
- Applicare gli stimoli al componente da testare per **verificare il relativo comportamento** e la sua evoluzione 
- Confrontare i risultati ottenuti con un **set di output predefinito e/o un oracolo**
##### Schema di base
- Il blocco responsabile di **generare gli stimoli** li fornisce al DUT
- Il blocco di controllo degli output **verifica la coerenza coi risultati attesi**
**PASSI**:
- Il primo passo consiste nella creazione di un modulo di top-level 
	- Il modulo di testbench deve risultare completamente auto-contenuto 
	→ Solitamente non ha né input, né output 
Esempio:
```verilog
module <module_name> (); //Ha senso mettere tb_(nome del modulo da testare)
	// Testbench body 
endmodule
```
- Allo stesso modo, si procede ad istanziare il modulo per il DUT
```verilog
<module_name> #(
	.<param_name>(<param_value>)
 )
 <instance_name> (
	.<port_name>(<signal_name>),
);
```
- Una parte fondamentale del modulo di testbench è quella responsabile della **generazione degli stimoli** 
	- Clock, reset, dati di input, ecc. 
Si usano costrutti nativi del linguaggio 
- Blocchi initial, always, cicli forever e istruzioni per lo scorrimento temporale 
**Poiché il codice di un testbench non deve essere sintetizzabile, è possibile usare statement che «consumano» tempo** 
- Si usa l’operatore # per modellare ritardi assieme alla direttiva \`timescale per definire l’unità di tempo
```verilog
#5 // Attesa per 5 unità di tempo (non metto punto e virgola)

#10 a = 1'b1; // Assegna ad a il valore 1 dopo 10 unità di tempo
```
###### Blocco initial
Sintassi 
- initial begin 
  …istruzioni… 
  end
Simile a un blocco always, permette di definire un blocco procedurale .
Ogni frammento di codice contenuto in un blocco initial **viene eseguito una sola volta**, all’inizio della simulazione.
A differenza di un blocco always, il codice incluso in un blocco initial non è sintetizzabile 
- Può essere comunque utilizzato anche nel caso di design RTL come strumento di inizializzazione dei segnali
```verilog
initial begin 
	gate_in = 2b'00; 
	#10 
	gate_in = 2b'01; 
	#10 
	gate_in = 2b'10; 
	#10 
	gate_in = 2b'11; 
end
```
###### Ciclo forever
Un ciclo forever può modellare un ciclo infinito
- Il codice è eseguito indefinitamente durante la simulazione 
Sintassi 
- forever begin 
  …istruzioni… 
  end 
>È tipicamente utilizzato in blocchi procedurali che **generano segnali di clock**
```verilog
initial begin 
	clk = 1b'0; 
	forever begin 
		#1 clk = ~clk; //Esempio clock, ogni secondo cambia da 1 a 0.
	end 
end
```
###### System tasks
>è possibile stampare i valori con **\$display e $monitor.**
 Display stampa una informazione quando viene chiamata, mentre monitor stampa quando un valore cambia mettendo il valore che ha assunto.
>Sono simili al C.

| Modificatore | Descrizione                                    |
| ------------ | ---------------------------------------------- |
| %h, %H       | Rappresentazione in esadecimale                |
| %d, %D       | Rappresentazione in decimale                   |
| %b, %B       | Rappresentazione in binario                    |
| %o, %O       | Rappresentazione in ottale                     |
| %m, %M       | Visualizza nome gerarchico del modulo corrente |
| %s, %S       | Rappresentazione come stringa di testo         |
| %t, %T       | Rappresentazione come tempo                    |
| %f, %F       | Rappresentazione in virgola mobile             |
| %e, %E       | Rappresentazione in formato esponenziale       |
**System task $time**, invece permette di stampare l'istante corrente di simulazione, si usa spesso in combinazione per capire quando avviene quella stampa.
system task **$time** ritorna il tempo come vettore su 64 bit. Varianti:
- **$stime** ritorna il tempo come intero a 32 bit 
- **$realtime** ritorna il tempo come numero reale
Si può applicare un modificatore di formato globale alla rappresentazione testuale
- **$timeformat(unit, precision, "suffix", min_width)**
```verilog
$display("x (bin) = %b, x (dec) = %d", x, x); //Stampoa quando chiamata

$monitor("in_1=%b, in_2=%d, in_3=%h", a, b, c); //Stampa quando cambiano

// Time as multiples of 1ns, two decimal positions and at least 10 digits
$timeformat(-9, 2, "ns", 10); // 10E-9s, 2 decimali, suffisso «ns», campo da 10 
$display("in_1=%b @ time = %t", a, $time);
```
