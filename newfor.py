x = [1891, 1901, 1911, 1921, 1931]
y = [46, 66, 81, 93, 101]
X = 1895

h = x[1] - x[0]
p = (X - x[0]) / h

table = []
table.append(y)

for i in range(len(x) - 1):
    nextRow = []
    for j in range(1, len(table[i])):
        nextRow.append(table[i][j] - table[i][j - 1])
    table.append(nextRow)

def fact(n):
    factorial = 1
    for i in range(1, n + 1):
        factorial *= i
    return factorial

Y = 0
for i in range(len(table)):
    prod = 1
    for j in range(i):
        prod *= (p - j)
    Y += prod * table[i][0] / fact(i)

print(Y)