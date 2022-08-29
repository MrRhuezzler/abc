from sympy import *

x = symbols('x')

f = 3*x + cos(x) - 1

def bisection(f, a, b):
    k = (a + b) / 2
    while f.subs(x, k) > 1e-5 or f.subs(x, k) < -1e-5:
        if f.subs(x, k) * f.subs(x, a) < 0:
            b = k
        else:
            a = k
        k = (a + b) / 2
    print(k)

bisection(f, -1, 0)