from sympy import *

x = [1, 2, 3, 4]
y = [1, 5, 11, 8]
X0 = 1.5

h = x[1] - x[0]
n = len(x) - 1
X = symbols('X')
m = symbols(f'm0:{n + 1}')

M = {0 : 0, n : 0}
eqns = []

for i in range(1, n):
    eqn = (m[i - 1] + 4 * m[i] + m[i + 1]) - ((6 * (y[i - 1] - 2 * y[i] + y[i + 1]) / h ** 2))
    eqns.append(eqn)

for i in range(len(eqns)):
    for j in M:
        eqns[i] = eqns[i].subs(m[j], M[j])

sol = solve(tuple(eqns), tuple(m))

for i in range(len(sol)):
    M[i + 1] = sol[m[i + 1]]

index = 1
while index < n:
    if X0 <= x[index]:
        break
    index += 1

Y = (x[index] - X0) ** 3 * M[index - 1] / (6 * h) + (X0 - x[index - 1]) ** 3 * M[index] / (6 * h) + (x[index] - X0) / h * (y[index - 1] - (h ** 2 * M[index - 1]) / 6) + (X0 - x[index - 1]) / h * (y[index] - h ** 2 * M[index] / 6)
print(Y)