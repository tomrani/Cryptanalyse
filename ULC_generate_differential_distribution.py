sBox = [6, 5, 12, 10, 1, 14, 7, 9, 11, 0, 3, 13, 8, 15, 4, 2]

max=16
 
tab = [[0]*max for i in range(max)]

for i in range(max):
    for j in range(max):
        tab[j][i]= 0

print(tab)
print("\n")


for i in range(0, max):
    for j in range(0, max):
        k=i^j
        deltay= sBox[j] ^ sBox[k]
        #print((deltay))
        tab[i][deltay]=tab[i][deltay]+1 
print(tab)

print(bin(62))
