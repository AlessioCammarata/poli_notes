file_name = "estremi.dat"
# result = []

# with open(file_name,"r",encoding="utf-8") as file:
#     for row in file:
#         row = row.split()
#         result.append(int(row[0])-int(row[1]))

# with open(file_name,"a") as file:
#     print("\n-------------",file=file)
#     for item in result:
#         print(f"{item:>5}",file=file)

# OPPURE
 
with open(file_name,"r",encoding="utf-8") as file1,open(file_name,"a") as file2:
    print("\n-------------",file=file2)
    for row in file1:
        row = row.split()
        result = int(row[0])-int(row[1])
        print(f"{result:>5}",file=file2)
            