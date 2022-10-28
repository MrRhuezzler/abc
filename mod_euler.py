from sympy import *
x, y = symbols('x y')

y_dash = (x - y) / 2
x0 = 0
y0 = 1
h = 0.1

X = 0.2

while X > x0:
    _x = x0 + 0.5 * h
    _y = y0 + 0.5 * y_dash.subs({x : x0, y : y0})
    y0 = y0 + h * y_dash.subs({x : _x, y : _y})
    print(f"f({x0 + h}) = {y0}")
    x0 += h