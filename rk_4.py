from sympy import *
x, y = symbols('x y')

y_dash = (x - y) / 2
x0 = 0
y0 = 1
h = 0.1

X = 0.2

while X > x0:
    k1 = h * y_dash.subs(x, x0).subs(y, y0)
    k2 = h * y_dash.subs(x, x0 + h / 2).subs(y, y0 + k1 / 2)
    k3 = h * y_dash.subs(x, x0 + h / 2).subs(y, y0 + k2 / 2)
    k4 = h * y_dash.subs(x, x0 + h).subs(y, y0 + k3)
    y0 = y0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6
    print(f"f({x0 + h}) = {y0}")
    x0 += h
