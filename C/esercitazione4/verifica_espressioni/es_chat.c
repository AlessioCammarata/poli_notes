#include <stdio.h>

#define filein "C:/Users/aless/Desktop/Polito/poli_notes/C/esercitazione4/verifica_espressioni/espr.txt" 

// Funzione che verifica se il carattere è un operatore
int operando(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

// Funzione che verifica se un carattere è un numero
int e_numero(char c) {
    return c >= '0' && c <= '9';
}

// Funzione che verifica la sintassi di una riga
int controlla_riga(char *str) {
    int i = 0, bilanciamento = 0, spazio = 0, operatore = 0, operandoPrecedente = 0, parentesiAperta = 0;

    while (str[i] != '\0' && bilanciamento >= 0) {
        if (str[i] == '(') {
            if (operandoPrecedente) bilanciamento = -1;  // Errore: un numero non può essere seguito da '(' senza operatore
            bilanciamento++;
            operatore = 0;  
            operandoPrecedente = 0;
        } 
        else if (str[i] == ')') {
            bilanciamento--;
            if (operatore || bilanciamento < 0) bilanciamento = -1;  // Errore: parentesi chiusa dopo un operatore o sbilanciata
            operandoPrecedente = 1;  // Una parentesi chiusa è considerata un operando valido
            parentesiAperta = 1;
        } 
        else if (e_numero(str[i])) {
            if (spazio || parentesiAperta) bilanciamento = -1;
            else {
                if (str[i + 1] == ' ') spazio = 1;
                else spazio = 0;
            }

            if (operatore) operatore = 0;  // Dopo un operatore deve venire un operando
            operandoPrecedente = 1;
        } 
        else if (operando(str[i])) {
            if (operatore || !operandoPrecedente) bilanciamento = -1;  // Errore: due operatori consecutivi o operatore senza operando prima
            operatore = 1;
            spazio = 0;
            operandoPrecedente = 0;
            parentesiAperta = 0;
        }

        i++;
    }

    if (operatore) bilanciamento = -1;  // La riga non può finire con un operatore
    return bilanciamento == 0;
}

int main(void) {
    FILE *fin;
    int ok, riga = 1;
    char buffer[100];  

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fin) != NULL) {
        ok = controlla_riga(buffer);
        printf("%d\n", ok);
        if (ok == 0) printf("Errore nell'espressione %d\n", riga);
        riga++;
    }

    fclose(fin);
    return 0;
}
