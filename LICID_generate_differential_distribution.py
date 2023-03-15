sBox = [0,7,10,14,4,1,6,13,5,9,8,15,12,2,11,3]

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
