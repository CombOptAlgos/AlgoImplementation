import numpy as np
import pandas as pd
from utils import make_tableau, get_indices, sweep_out, reuse


class Symplex:
    """SIMPLEX ALGORYTHM
    Input:
        int m, n
        A: m * n matrix
        b: vector length m
        c: vector length n
    Output:
        A vertex x of P := {x | Ax <= b, x >= 0} attaining max{cx | x in P}
        of
        vector w with Aw <= 0 and cw > 0
    """

    def __init__(self):
        self.tableau = None

    def fit(self, A, b, c):
        self.tableau = make_tableau(A, b)
        i, j = get_indices(self.tableau)
        while i is not None and j is not None:
            self.tableau = sweep_out(self.tableau, i, j)
            i, j = get_indices(self.tableau)

        self.tableau = reuse(A, b, c, self.tableau)

        assert self.tableau[-1][-1] == sum([-i for i in b if i < 0]
                                    ), "LP has no solution (infeasible)"

        i, j = get_indices(self.tableau)
        while i is not None and j is not None:
            self.tableau = sweep_out(self.tableau, i, j)
            print(pd.DataFrame(self.tableau))
            i, j = get_indices(self.tableau)
        if i is not None:
            assert j is not None, "LP has no solution (unbounded)"
        return self


    def result(self):
        print(self.tableau[-1][-1])

if __name__=="__main__":
    A = np.array([
            [1, -1],
            [1, 1],
            [-1, 1],
            [-1, -1]
        ])
    b = np.array([1, 1, 1, 1])
    c = np.array([[-2, -1]])
    solver = Symplex().fit(A, b, c)
    solver.result()
    print(solver.tableau)