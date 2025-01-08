import random
from operator import itemgetter

def scala(valori):
    sequenza = "".join(valori)
    scala = "A2345678910JQKA"
    return sequenza in scala

def controlla_punteggio(carte):
    scala_punti = ['carta_alta', 'coppia', 'doppia coppia', 'tris', 'scala', 'colore', 'full','poker','scala_reale']
         
    carte.sort(key=itemgetter(0),reverse = True)
    valori = [carta[0] for carta in carte]
    seme = [carta[1] for carta in carte]
    
    val = 0
    i = 0
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

    #Controllo le carte che dipendono dalla sequenza e non dallo stesso numero
    is_scala = scala(valori)
    #Controllo se hai colore
    if seme.count(seme[0]) == 5:
        #Controllo se hai scala_colore
        if is_scala:
            val = 8
        else:
            val = 5
    
    elif is_scala:
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
        
        for i in range(len(mazzo)//5):
            cards = take_cards(mazzo,i+5)
            punteggio = controlla_punteggio(cards)
            for item in cards:
                print(item[0]+item[1],end=" ")
            print(f"{punteggio}")


    except FileNotFoundError as e:
        exit(f"Errore, {e}")

if __name__ == '__main__':
    main()