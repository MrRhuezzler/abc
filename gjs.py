# Given the augumented matrix

# Jacobi
def jacobi(aug):
    aug = []
    rows = len(aug)
    columns = len(aug)
    prev = [0] * (columns - 1)
    solutions = [0] * (columns - 1)

    for k in range(10):
        for i in range(rows):
            b = aug[i][columns - 1]
            for j in range(columns):
                if j != i:
                    b -= aug[i][j] * prev[j]
            solutions[i] = b / aug[i][i]
        
        prev = solutions
        print("Iteration", k + 1)
        print(solutions)


# Seidal
def seidal():
    aug = []
    rows = len(aug)
    columns = len(aug)
    solutions = [0] * (columns - 1)

    for k in range(10):
        for i in range(rows):
            b = aug[i][columns - 1]
            for j in range(columns):
                if j != i:
                    b -= aug[i][j] * solutions[j]
            solutions[i] = b / aug[i][i]
        
        print("Iteration", k + 1)
        print(solutions)
