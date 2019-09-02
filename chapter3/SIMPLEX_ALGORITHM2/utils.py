import numpy as np
import pandas as pd

eps = 1e-5

def make_tableu(A, b):
    """make initial tableu table

    Parameters
    ----------
    A : ndarray

    Return
    ------

    """
    A = A.astype(np.float32)

    m, _ = A.shape
    is_nonnegative = b.flatten()>=0
    is_negative = b.flatten() < 0
    A_ = A[is_nonnegative]
    b_ = b[is_nonnegative].reshape(-1,1)
    A__ = A[is_negative]
    b__ = b[is_negative].reshape(-1,1)
    m_ = sum(is_nonnegative)
    m__ = sum(is_negative)

    upper = np.c_[A_, np.zeros((m_, m__)), np.diag([1]*m_), np.zeros((m_, m__)), b_]
    middle = np.c_[-A__, np.diag([-1]*m__), np.zeros((m__, m_)), np.diag([1]*m__), -b__]
    lower = np.c_[np.ones((1,m__))@A__, np.ones((1, m__)), np.zeros((1, m+1))]
    tableu = np.r_[
        upper,
        middle,
        lower
        ]

    return tableu


def get_indices(tableu):
    """get i, j from tableu

    >>> import numpy as np
    >>> tableu = np.array([
        [1, 2, 3],
        [4, 5, 6],
        [-1, 7, 8]
        ])
    >>> get_indices(tableu)
    1, 0
    """

    n_rows, n_cols = tableu.shape

    i, j = (None, None)

    for i_ in range(n_cols-1):
        if tableu[-1][i_] < -eps:
            i = i_
            break
    if i is None:
        return i, j # ともにNone
    
    for j_ in range(n_rows-1):
        if tableu[j_][i] > eps:
            if j is None:
                j = j_
            else:
                lambda_j_ = culc_lambda(tableu, i, j_)
                lambda_j = culc_lambda(tableu, i, j)
                if lambda_j_ < lambda_j:
                    j = j_
    print(i,j)
    assert i is not None, "i is None"
    assert j is not None, "j is None"
    return i, j


def culc_lambda(tableu, i, j):
    return tableu[j][-1] / tableu[j][i]


def sweep_out(tableu, i, j):
    """sweep out tableu table

    Arguments:
        tableu {ndarray} -- tableu table
        i {int} -- pivot index of column
        j {int} -- pivot index of row

    Returns:
        tableu {ndarray} -- swept out tableu table
    """
    n_rows, n_cols = tableu.shape
    for j_ in range(n_rows):
        if j_ != j:
            alpha = tableu[j_][i] / tableu[j][i]
            tableu[j_] -= alpha * tableu[j]

    return tableu

def reuse(A, b, c, tableu):

    A = A.astype(np.float32)

    m, n = A.shape
    is_nonnegative = b.flatten()>=0
    is_negative = b.flatten() < 0
    A_ = A[is_nonnegative]
    b_ = b[is_nonnegative].reshape(-1,1)
    A__ = A[is_negative]
    b__ = b[is_negative].reshape(-1,1)
    m_ = sum(is_nonnegative)
    m__ = sum(is_negative)

    for i in range(n+m, n+m+m__):
        # i列目が単位行列か判定
        is_unit = True
        idx_one = None
        for j in range(m+1):
            if abs(tableu[j][i] - 1) < eps:
                if idx_one is None:
                    idx_one = j #i列目で1が立っている行のindex
                else:
                    break
            elif (tableu[j][i]) >= eps:
                break

        # i列目は単位行列
        tableu[idx_one] *= -1

    tableu = np.c_[tableu[:,:n+m].reshape(m+1,-1), tableu[:, -1].reshape(m+1, -1)]
    tableu[-1] = np.c_[-c, np.zeros((1, m+1))]

    for i in range(n):
        idx_nonzero = None
        n_zero = 0
        for j in range(m):
            if tableu[j][i] < eps:
                n_zero += 1
            else:
                idx_nonzero = j
        if n_zero == m-1:
            assert abs(tableu[idx_nonzero][i]) >= eps, "Error!"
            assert idx_nonzero is not None, "Error!"
            tableu = sweep_out(tableu, i, idx_nonzero)
            tableu[idx_nonzero] /= tableu[idx_nonzero][i]

    return tableu


def symplex():
    A = np.array([
        [1,2,-3],
        [-4,5,2],
        [5,-3,-2]
    ])
    b = np.array([0,-1,0])
    c = np.array([[-2,2,1]])
    tableu = make_tableu(A, b)

    i, j = get_indices(tableu)
    while i is not None and j is not None:
        tableu = sweep_out(tableu, i, j)
        i, j = get_indices(tableu)

    print(pd.DataFrame(tableu))
    tableu = reuse(A, b, c, tableu)
    print(pd.DataFrame(tableu))
    i, j = get_indices(tableu)
    while i is not None and j is not None:
        tableu = sweep_out(tableu, i, j)
        print(i,j)
        print(pd.DataFrame(tableu))
        i, j = get_indices(tableu)
        # print(pd.DataFrame(tableu))
        

if __name__=="__main__":
    symplex()
