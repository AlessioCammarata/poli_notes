Un registro è una raccolta di **edge-triggered flip-flop o latch** (Useremo solo FF)
- I registri, **acquisiscono e memorizzano i dati in base a un trigger**, un fronte di salita o di discesa 
- Fungono da elementi di archiviazione temporanea dei dati 

Per codificare un registro utilizzando la modellazione comportamentale in Verilog, se ne replica il comportamento utilizzando una variabile a cui assegnare un valore e da memorizzare fino al successivo trigger.

In Verilog si usa il tipo reg per dichiarare le variabili che modellano gli elementi di memoria e possono rappresentare logica combinatoria o sequenziale.
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

Il comportamento del registro è completamente sincrono 
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
