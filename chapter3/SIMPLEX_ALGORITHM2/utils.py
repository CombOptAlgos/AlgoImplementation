import numpy as np


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
    middle = np.c_[-A__, np.diag([-1]*m__), np.zeros(m__, m_), np.diag([1]*m__), -b__]
    lower = np.c_[np.ones((1,m__))@A__, np.ones((1, m__)), np.zeros((1, m+1))]

    tableu = np.r_[
        upper,
        middle,
        lower
        ]

    return tableu


def get_indices(tableu):

    n_rows, n_cols = tableu.shape

    i, j = (None, None)

    for i_ in range(n_cols-1):
        if tableu[-1][i_] < 0:
            i = i_
            break
    if i is None:
        return i, j # ともにNone

    for j_ in range(n_rows-1):
        if tableu[j_][i] > 0:
            if j is None:
                j = j_
            else:
                lambda_j = culc_lambda(tableu, i, j_)
                min_lambda = culc_lambda(tableu, i, j)
                if lambda_j < min_lambda:
                    j = j_
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

if __name__=="__main__":
    A = -np.random.randint(6, 100, (3,3))
    # A = np.arange(9)
    # A = A.reshape(3,3)
    # b = np.random.randint(6, 100, (3,1))
    b = np.array([-2,-2,3])
    c = np.random.randint(6, 100, (3,1))
    tableu = make_tableu(A, b)
    print(tableu)
    i, j = get_indices(tableu)
    while i is not None and j is not None:
        tableu = sweep_out(tableu, i, j)
        i, j = get_indices(tableu)
        print(tableu)
    print(tableu)