x = [300, 304, 305, 307]
y = [2.4771, 2.4829, 2.4843, 2.4871]
X = 301

Y = 0
for i in range(len(y)):
    num = 1
    dem = 1
    for j in range(len(y)):
        if j != i:
            num *= (X - y[j])
            dem *= (y[i] - y[j])
    Y += ((num * x[i]) / dem)

print(Y)