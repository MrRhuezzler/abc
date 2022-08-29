# Gauss Jordan Elimination

from inspect import isclass
from re import L
import numpy as np

def non_zero(row):
    for i in range(row):
        if row[i] != 0:
            return i

def rref(matrix):

    rows = len(matrix)
    columns = len(matrix[0])
    non_zero_index = -1

    # arrange the matrix rows in the order of leftmost non-zero entry
    matrix.sort(key=non_zero)

    for i in range(rows):
        for j in range(columns):
            if np.isclose(matrix[i][j], 0.0):
                non_zero_index = j
                matrix[i] = [x / matrix[i][j] for x in matrix[i]]
                break
        
        for k in range(rows):
            if k != i:
                ratio = matrix[k][non_zero_index]
                multiplied_key_row = [x * ratio for x in matrix[i]]
                matrix[k] = [x - y for x,y in zip(matrix[k], multiplied_key_row)]
    
    return matrix

