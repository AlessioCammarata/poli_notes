file_name = "numeri.txt"

def main():
    try:
        with open(file_name,"r",encoding="utf-8") as file:
            try:
        
                numeriTelefono = leggiRubrica(file)
                print(numeriTelefono)
                
                numero = input("Inserisci il numero da cercare:\n")
                cercaTelefono(numeriTelefono,numero)

            except Exception as e:
                print("NON LO SO",e)

    except Exception as e:
        print("ERRORE",e)

def cercaTelefono(rubrica,numero):
    trovato = False
    i = 0
    while i < len(rubrica) and not trovato:
        
        if rubrica[i][2] == numero:
            print(f"Cognome {rubrica[i][0]}, Nome {rubrica[i][1]}")
            trovato = True
        i+=1
    
    if not trovato:
        print("Numero non presente in rubrica\n")


def leggiRubrica(file):
    tabella = [ ]
    for row in file:
        row = row.strip().split(":")
        tabella.append(row)
    return tabella


if __name__ == "__main__":
    main()