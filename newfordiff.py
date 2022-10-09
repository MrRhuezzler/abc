from sympy import *

x = [0.0, 0.1, 0.2, 0.3, 0.4]
y = [1.0000, 0.9975, 0.9900, 0.9776, 0.8604]
X = 0

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
t = symbols('t')

for i in range(len(table)):
    temp = table[i][0]
    for j in range(i):
        temp *= (t - j)
    temp /= fact(i)
    Y += temp

dydx = diff(Y, t).subs(t, p) / h
dy2dx2 = diff(diff(Y, t), t).subs(t, p) / h ** 2

print(dydx)
print(dy2dx2)