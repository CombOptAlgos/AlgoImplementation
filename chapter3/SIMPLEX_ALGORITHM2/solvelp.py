import numpy as np
from utils import make_tableau, get_indices, sweep_out, renew


class Symplex:
    """SIMPLEX ALGORITHM
    Input:
        int m, n
        A: m * n matrix
        b: vector length m
        c: vector length n
    Output:
        A vertex x of P := {x | Ax <= b, x >= 0} attaining max{cx | x in P}
        of vector w with Aw <= 0 and cw > 0

    Examples
    --------
    >>> import numpy as np
    >>> from solvelp import Symplex
    >>> A = np.array([[1, -1],[1, 1],[-1, 1],[-1, -1]])
    >>> b = np.array([1, 1, 1, 1])
    >>> c = np.array([[2, -1]])
    >>> solver = Symplex().fit(A, b, c)
    >>> print(solver.result())
    2.0
    >>> print(solver.tableau)
    [[ 1.   0.   0.5  0.5  0.   0.   1. ]
    [ 0.   2.  -1.   1.   0.   0.   0. ]
    [ 0.   0.   1.   0.   1.   0.   2. ]
    [ 0.   0.   0.   1.   0.   1.   2. ]
    [ 0.   0.   1.5  0.5  0.   0.   2. ]]
    """

    def __init__(self):
        self.tableau = None

    def fit(self, A, b, c):
        """set matrix and vectors and solve LP by updatind tableau table

        Parameters
        ----------
        A : sparse matrix shape = [n_inequalities, n_variables]
            Coefficient matrix of inequality system

        b : array-like, shape = [n_inequalities]
            Intercept vector of inequality system

        c : array-like, shape = [n_variables]
            Coefficient vector of objective function

        Returns
        -------
        self : object

        """
        self.tableau = make_tableau(A, b)
        i, j = get_indices(self.tableau)
        while i is not None and j is not None:
            self.tableau = sweep_out(self.tableau, i, j)
            i, j = get_indices(self.tableau)

        self.tableau = renew(A, b, c, self.tableau)

        assert self.tableau[-1][-1] == sum([-i for i in b if i < 0]), \
            "LP has no solution (infeasible)"

        i, j = get_indices(self.tableau)
        while i is not None and j is not None:
            self.tableau = sweep_out(self.tableau, i, j)
            i, j = get_indices(self.tableau)
        if i is not None:
            assert j is not None, "LP has no solution (unbounded)"
        return self

    def result(self):
        return self.tableau[-1][-1]


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
