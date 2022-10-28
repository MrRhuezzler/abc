from sympy import *
x, y, z = symbols('x y z')

f = (x + y) / 2

xs = [0, 0.5, 1, 1.5]
ys = [2, 2.636, 3.595, 4.968]

h = xs[1] - xs[0]

y_dash = []
for _x, _y in zip(xs, ys):
    y_dash.append(f.subs({x: _x, y: _y}))

n = len(y_dash) - 1

predictor = ys[n] + (h / 24) * (55 * y_dash[n] - 59 *
                                y_dash[n-1] + 37 * y_dash[n-2] - 9*y_dash[n-3])
y_dash.append(f.subs({x: xs[-1] + h, y: predictor}))

corrector = ys[n] + (h / 24) * (9 * y_dash[n + 1] + 19 *
                                y_dash[n] - 5 * y_dash[n - 1] + y_dash[n-2])

print(f"y({xs[-1] + h}) = {corrector}")
