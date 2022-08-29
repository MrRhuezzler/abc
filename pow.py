import numpy as np

def inversePowerIteration(matrix, iterations):
    matrix = np.linalg.inv(matrix)
    x = np.random.rand(matrix.shape[1])
    for _ in range(iterations):
        x = np.dot(matrix, x)
        l = np.linalg.norm(x)
        x = x / l

    return x

def powerIteration(matrix, iterations):
    x = np.random.rand(matrix.shape[1])
    for _ in range(iterations):
        x = np.dot(matrix, x)
        l = np.linalg.norm(x)
        x = x / l

    return x

def rayleighQuotient(matrix, eigenVector):
    num = np.dot(np.dot(matrix, eigenVector), eigenVector)
    dem = np.dot(eigenVector, eigenVector)
    return num / dem

matrix = np.array([[2, 1], [0, -4]])

print(a := powerIteration(matrix, 100))
print(rayleighQuotient(matrix, a))