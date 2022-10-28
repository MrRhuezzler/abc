from sympy import *
x, y = symbols('x y')

def fact(n):
    factorial = 1
    for i in range(1, n + 1):
        factorial *= i
    return factorial

def taylor_series(y_diff, x0, y0, h):
    sum = 0
    for i in range(1, 5):
        sum += (h ** i) * y_diff.subs({x : x0, y : y0}) / fact(i)
        y_diff = diff(y_diff, x)
    return sum

x0 = 0
y0 = -3
h = 0.5
y_dash = exp(x**2-1) / (1 + x*y + x**3)

for _ in range(5):
    y0 = y0 + taylor_series(y_dash, x0, y0, h)
    print(f"f({x0 + h:2.1f}) = {N(y0)}")
    x0 += h
