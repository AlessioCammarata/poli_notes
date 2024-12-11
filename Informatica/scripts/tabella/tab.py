# Ordinare secondo un etichetta.
tabella = [
    [2,1],
    [6,3],
    [-2,4],
    [-6,1],
    [6,2],
    [8,1]       
           ]


print(tabella) #[['A', 1], ['B', 3], ['A', 4], ['B', 1], ['A', 2], ['B', 1]]
tabella.sort(key=lambda elemento:elemento[0] * elemento[1])

print(tabella)#[[-6, 1], [-2, 4], [2, 1], [6, 2], [6, 3], [8, 1]]