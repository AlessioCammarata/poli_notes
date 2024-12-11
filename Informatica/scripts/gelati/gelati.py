from operator import itemgetter

def printes(dizio):
    for item in sorted(dizio):
        print(f"{item:<15}", end="")
        for j in range(len(dizio[item])):
            print(f"{dizio[item][j]:>15.2f}", end="")
        print("\t",sum(dizio[item]))
        
    for i in range(len(dizio["vanilla"])):
        somma = 0
        for item in dizio:
            somma += dizio[item][i]
        print(f"{somma:>15.2f}", end="")
    print()

def main():
    try:
        file_name = "gelati.txt"
        with open(file_name,"r",encoding="utf-8") as file:
            try:
                dizio = {}
                for row in file:
                    row = row.rstrip().split(":")

                    # for item in row[1:]:
                    #     if row[0] not in dizio:
                    #         dizio[row[0]] = [float(item)]
                    #     else:
                    #         dizio[row[0]].append(float(item))
                    for item in row[1:]:
                        dizio.get(row[0], [])
                        dizio[row[0]] = dizio.get(row[0], []) + [float(item)]
                    counter = len(row) -1 

                # print(dizio)
                printes(dizio)



            except Exception as e:
                exit(f"ERROre {e}")

    except FileNotFoundError as e:
        exit(f"Errore {e}")


if __name__ == "__main__":
    main()