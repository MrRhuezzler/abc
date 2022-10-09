x = [2, 2.5, 3]
y = [0.69315, 0.91629, 	1.09861]
X = 2.7

numberOfIteration = len(x) - 1

table = []
table.append(y)

for i in range(numberOfIteration):
    nextRow = []
    for j in range(len(table[i]) - 1):
        value = (table[i][j + 1] - table[i][j]) / (x[j + 1 + i] - x[j])
        nextRow.append(value)
    table.append(nextRow)


Y = 0
for i in range(len(table)):
    prod = 1
    for j in range(i):
        prod *= (X - x[j])
    Y += (prod * table[i][0])
print(Y)