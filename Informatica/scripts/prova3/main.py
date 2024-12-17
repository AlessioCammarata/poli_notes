from sys import exit

def calculate_points(field):
    points = 0
    for item in field:
        match item:
            case "Giallo":
                points+=1
            case "Verde":
                points+=3
            case "Rosso":
                points+=5
            case _:
                pass
                
    return points

def dealing(file,player1,player2):
    """Do la carta con indice pari al giocatore 1 e viceversa, in questo modo la carta 0 andrà al primo"""
    for i,row in enumerate(file):
        if i % 2 == 0: 
            player1.append(row.rstrip())
        else:
            player2.append(row.rstrip())

def simulate(player1,player2):
    TURNS = len(player1)
    match_points = {
        True:0,
        False:0
    }

    campo = []

    for i in range(TURNS):

        print("Punteggio giocatore 1:", match_points[True])
        print("Punteggio giocatore 2:", match_points[False])
        print("\n\nMano n.",i+1)

        carta1 = player1.pop(0)
        carta2 = player2.pop(0)

        print("Carta giocatore 1:", carta1)
        print("Carta giocatore 2:", carta2)

        # Flag che mi dice se la mano l'ha vinta il p1, 
        p1   = False
        draw = False
        
        # Se p1 ha il rosso, e l'altro no, vince il p1
        if carta1[0]  == "R" and carta2[0] != "R":
            p1 = True
        
        # Se p1 ha il verde, e l'altro no, bisogna controllare se hanno il rosso o no
        elif carta1[0] == "V" and carta2[0] !="V":

            # Se p2 ha il rosso, e l'altro no, vince il p2 altrimenti il contrario dato che nessuno dei due ha la verde
            if carta2[0] == "R":
                p1 = False
            else:
                p1 = True

        # Se p1 ha il giallo, e l'altro no, vince il p2
        elif carta1[0] == "G" and carta2[0] !="G":
            p1 = False

        #Altrimenti pareggio
        else:
            draw = True

        campo.append(carta1)
        campo.append(carta2)
        print("Risultato: ", end="")
        if draw:
            print("Pareggio")
        else:
            print("Vince la mano il giocatore ", end="" )
            print("1" if p1 else "2")

            points = calculate_points(campo)
            campo  = []

            # Aggiungo i punti a chi ha vinto
            match_points[p1] += points
    
    print()
    if match_points[True] == match_points[False]: 
        print("Pareggio. Non vince nessuno!")
    else:
        #Stampo chi ha vinto, e i suoi punti.
        print("Vince il giocatore " + "1" if match_points[True] > match_points[False] else "2" ,f"con {max(match_points[False],match_points[True])} punti.")


def main():
    try:
        file_name = "mazzo.txt"
        with open(file_name,'r',encoding="utf-8") as file:
            try:
                carteplayer1 = []
                carteplayer2 = []
                dealing(file,carteplayer1,carteplayer2)

                simulate(carteplayer1,carteplayer2)
            
            except Exception as e:
                exit(f"Errore, {e}")
    except FileNotFoundError as e:
        exit(f"Errore, {e}")

if __name__ == "__main__":
    main()