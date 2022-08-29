from sympy import *

x = symbols('x')

f = 3*x + cos(x) - 1

def regula_false(f, a, b):
    h = float(abs(f.subs(x, a)) * (b - a)) / float(abs(f.subs(x, a)) + abs(f.subs(x, b)))
    k = float(a + h)
    while f.subs(x, k) > 1e-5 or f.subs(x, k) < -1e-5:
        if f.subs(x, k) * f.subs(x, a) < 0:
            b = k
        else:
            a = k

        h = float(abs(f.subs(x, a)) * (b - a)) / float(abs(f.subs(x, a)) + abs(f.subs(x, b)))
        k = float(a + h)
        print(k)
    print(k)

regula_false(f, -1, 0)