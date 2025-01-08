#Esercizio su
from operator import itemgetter
from sys import exit

def conta_valori(tabellone,valore):
    serie = {player:0 for player in tabellone}
    for player in tabellone:
        serie[player] += tabellone[player].count(valore)

    return max(serie.items(),key=itemgetter(1))

def calcola_punteggio(punteggi):
    return sum(punteggi)

def main():
    try:
        file_name = 'bowling.txt'
        with open(file_name,'r',encoding='utf-8') as file:
            try:
                tabellone = {}
                for row in file:
                    row = row.rstrip().split(';')
                    name = row[0] + " " + row[1]
                    # if name not in tabellone:
                    tabellone[name] = [int(row[i]) for i in range(2,len(row))]

                punti = []
                for player in tabellone:
                    punti.append((player,calcola_punteggio(tabellone[player])))

                punti.sort(key=itemgetter(1),reverse=True)
                for player,punteggio in punti:
                    player = player.split()
                    print(f"{player[0]:<13} {player[1]:<10} {punteggio:<4}")


                player_forte = conta_valori(tabellone,10)
                player_scarso = conta_valori(tabellone,0)
                print(f"{player_forte[0]} ha abbattuto tutti i birilli {player_forte[1]} volta/e")
                print(f"{player_scarso[0]} ha abbattuto tutti i birilli {player_scarso[1]} volta/e")

            except Exception as e:
                exit(f"Errore di esecuzione, {e}")
    except FileNotFoundError as e:
        exit(f"Errore in apertura del file, {e}")

if __name__ == '__main__':
    main()       