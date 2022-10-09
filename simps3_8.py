from sympy import *
x = symbols('x')

eq = log(x)
limits = [4, 5.2]

h = 0.1
X = []
Y = []
ind = limits[0]

while ind <= limits[1]:
    X.append(ind)
    Y.append(eq.subs(x, ind))
    ind += h

total = 0
total3 = 0
for i in range(1, len(Y) - 1):
    if i % 3 != 0:
        total += Y[i]
    else:
        total3 += Y[i]


value = (3 * h / 8) * (Y[0] + 2 * total3 + 3 * total + Y[-1])

print(N(value))