from sympy import *

x = symbols('x')

f = 3*x + cos(x) - 1

def newton(f, a, b):
    dx = diff(f, x)
    t = (a + b) / 2
    while f.subs(x, t) > 1e5 or f.subs(x, t) > -1e-5:
        t -= (f.subs(x, t) / dx.subs(x, t))
    
    print(t)

newton(f, -1, 0)