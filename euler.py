from sympy import *
x, y = symbols('x y')

y_dash = (x - y) / 2
x0 = 0
y0 = 1
h = 0.1

X = 1.7

while X > x0:
    y0 = y0 + h * y_dash.subs({x : x0, y : y0})
    print(f"f({x0 + h}) = {y0}")
    x0 += h