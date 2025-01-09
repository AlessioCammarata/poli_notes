import random

def assegna_valori(valore):
    valore = valore[0]

    match valore:
        case 'J':
            valore = 11
        case 'Q':
            valore = 12
        case 'K':
            valore = 13
        case 'A':
            valore = 14

    return int(valore)

def scala(valori):
    sequenza = "".join(valori)

    if 'A' in sequenza and 'K' not in sequenza:
        sequenza = sequenza[1:] + 'A' 

    scala = "AKQJ1098765432A"
    return sequenza in scala

def controlla_punteggio(carte):
    scala_punti = ['carta alta', 'coppia', 'doppia coppia', 'tris', 'scala', 'colore', 'full','poker','scala reale']
   
    # itemgetter(0)
    carte.sort(key=assegna_valori,reverse = True)
    valori = [carta[0] for carta in carte]
    seme = [carta[1] for carta in carte]
    
    val = 0
    i = 0
    #Controllo le carte che dipendono dalla sequenza e non dallo stesso numero
    is_scala = scala(valori)

    if not is_scala:
        while i<len(carte):
            
            match valori.count(valori[i]):
                
                case 2:
                    #Coppia
                    i += 2
                    val += 1

                case 3:
                    #Tris
                    i += 3
                    val += 3

                case 4:
                    #Poker
                    i+=4
                    val = 7
                
                case _:
                    i+=1    

        #Se hai full, ti assegno il full
        if val == 4:
            val = 6
        
        #Controllo se hai colore
        if val < 5 and seme.count(seme[0]) == 5:
            val = 5

    #Controllo se hai scala_colore
    elif seme.count(seme[0]) == 5:
        val = 8
        
    else:
        #controllo se hai scala
        val = 4

    return scala_punti[val]

def take_cards(mazzo,i):
    return mazzo[i:i+5]

def dealing(mazzo):
    random.shuffle(mazzo)

def main():
    try:
        file_name = 'mazzo.txt'
        with open(file_name,'r',encoding='utf-8') as file:
            try:
                mazzo = []
                for row in file:
                    row = row.rstrip().split()
                    mazzo.append((row[0],row[1]))

            except Exception as e:
                exit(f"Errore, {e}")

        dealing(mazzo)

        with open(file_name,'w') as file:
            try:
                for valore,seme in mazzo:
                    print(f"{valore} {seme}",file=file)
            except Exception as e:
                exit(f"Errore, {e}")
        
        j = 0
        for i in range(len(mazzo)//5):
            cards = take_cards(mazzo,j)
            # if i == 3:
            #     cards = [('Q', 'C'), ('A', 'C'), ('Q', 'C'), ('Q', 'C'), ('Q', 'C')]
            punteggio = controlla_punteggio(cards)
            for item in cards:
                print(item[0]+item[1],end=" ")
            print(f"{punteggio}")
            j+=5


    except FileNotFoundError as e:
        exit(f"Errore, {e}")

if __name__ == '__main__':
    main()