from sympy import *

x = symbols('x')

f = 3*x + cos(x) - x

def fixed(f, a, b):
    
    phi = -(f - f.coeff(x, 1) * x) / f.coeff(x, 1)
    dphi = diff(phi, x)

    if dphi.subs(x, a) < 1 and dphi.subs(x, b) < 1:
        pass
    else:
        print("No Fixed")
        return
    
    t = float(a)

    while f.subs(x, t) > 1e-5 or f.subs(x, t) < -1e-5:
        t = phi.subs(x, t)
    
    print(t)

fixed(f, -1, 0)