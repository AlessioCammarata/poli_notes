import random

def print_word(word,letters):
    for letter in word:
        print(letter if letter in letters else "_",end="")
    print()

def play(word):
    
    letter_word = set(letter for letter in word)
    alphabet = [chr(97+i) for i in range(26)]
    letters = []
    guess_letter = []
    punti = 10

    end = False
    while not end:
        print_word(word,letters)

        letters.append(alphabet.pop(alphabet.index(random.choice(alphabet))))
        print("Lettera scelta dal bot: ", letters[-1])
        print(alphabet)


        if letters[-1] in word:
            print(f"Lettera '{letters[-1]}' presente: ",end="")
            print_word(word,letters)
            guess_letter.append(letters[-1])
        else:
            print(f"Lettera '{letters[-1]}' non presente")
            punti -= 1
        print()
        bot_win = len(guess_letter) == len(letter_word)
        end = punti == 0 or bot_win
    
    return bot_win

def main():
    matches = [0,0]
    restart = True
    while restart:
        # difficulty = input("Inserisci il file:")
        # while file_name != 'akinator.txt':
        #     difficulty = input("Reinserisci il file:")
        # file_name = difficulty+'.txt'
        difficulty = 'facile'
        file_name = 'akinator.txt'

        parole = []
        with open(file_name,'r',encoding='utf-8') as file:
            for row in file:
                parole.append(row.rstrip().lower())

        print("Partita numero",matches[0]+matches[1] +1)
        print("Il bot seleziona la difficolta",difficulty,end="\n\n")

        word = random.choice(parole)
        winner = play(word)
        print(f"VINCE IL BOT, la parola {word.upper()} è stata indovinata" if winner else "HAI VINTO TU")
        matches[winner] += 1
        restart = input("Rivincita? Y/N")
        while restart not in ['Y','N']:
            restart = input("Rivincita? Y/N")
        
        restart = False if restart == 'N' else True
    
    print("SESSIONE TERMINATA")
    print(f"\t il bot ha vinto {matches[1]} partita/e")
    print(f"\t il bot ha perso {matches[0]} partita/e")


if __name__ == '__main__':
    main()