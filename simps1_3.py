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

value = (h / 3) * (Y[0] + 4 * sum(Y[1:-1:2]) + 2 * sum(Y[2:-1:2]) + Y[-1])

print(N(value))