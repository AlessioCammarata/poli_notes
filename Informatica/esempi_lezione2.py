file = "film.txt"

with open(file,"r",encoding="utf-8") as file:
    for row in file:
        row = row.split(",")
        if int(row[1]) >= 1992:
            print(row[0])