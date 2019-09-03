import numpy as np
from solvelp import Symplex

if __name__ == "__main__":
    A = np.array([
            [1, -1],
            [1, 1],
            [-1, 1],
            [-1, -1]
        ])
    b = np.array([1, 1, 1, 1])
    c = np.array([[2, -1]])
    solver = Symplex().fit(A, b, c)
    print(solver.result())
    print(solver.tableau)