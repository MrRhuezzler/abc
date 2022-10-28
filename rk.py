from sympy import *
x, y = symbols('x y')

y_dash = (x - y) / 2
x0 = 0
y0 = 1
h = 0.1

X = 0.2

while X > x0:
    k1 = h * y_dash.subs({x : x0, y : y0})
    k2 = h * y_dash.subs({x : x0 + 0.5 * h, y : y0 + 0.5 * k1})
    k3 = h * y_dash.subs({x : x0 + h, y : y0 + 2 * k2 - k1})
    y0 = y0 + (1/6) * (k1 + 4 * k2 + k3)
    print(f"f({x0 + h}) = {y0}")
    x0 += h