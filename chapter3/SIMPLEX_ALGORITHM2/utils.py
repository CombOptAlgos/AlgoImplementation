import numpy as np
import pandas as pd

eps = 1e-5

def make_tableau(A, b):
    """make initial tableau table

    Parameters
    ----------
    A : ndarray

    b : 

    Return
    ------
    tableu : ndarray

    Examples
    --------
    >>> A = np.arange(9).reshape(3,3)
    >>> b = np.zeros(3)
    >>> make_tableau(A, b)
    array([[0., 1., 2., 1., 0., 0., 0.],
           [3., 4., 5., 0., 1., 0., 0.],
           [6., 7., 8., 0., 0., 1., 0.],
           [0., 0., 0., 0., 0., 0., 0.]])
    """
    A = A.astype(np.float32)

    m, _ = A.shape
    is_nonnegative = b.flatten() >= 0
    is_negative = b.flatten() < 0
    A_ = A[is_nonnegative]
    b_ = b[is_nonnegative].reshape(-1, 1)
    A__ = A[is_negative]
    b__ = b[is_negative].reshape(-1, 1)
    m_ = sum(is_nonnegative)
    m__ = sum(is_negative)

    upper = np.c_[A_, np.zeros((m_, m__)), np.diag(
        [1]*m_), np.zeros((m_, m__)), b_]
    middle = np.c_[-A__, np.diag([-1]*m__),
                   np.zeros((m__, m_)), np.diag([1]*m__), -b__]
    lower = np.c_[np.ones((1, m__))@A__, np.ones((1, m__)), np.zeros((1, m+1))]
    tableau = np.r_[
        upper,
        middle,
        lower
    ]

    return tableau


def get_indices(tableau):
    """get i, j from tableau

    Parameters
    ----------
    tableu : ndarray
    
    Returns
    -------
    i : int
    j : int
    
    Examples
    --------
    >>> import numpy as np
    >>> tableau1 = np.array([[1, 2, 3],[4, 5, 6],[-1, -7, 8]])
    >>> get_indices(tableau1)
    (0, 1)
    >>> tableau2 = np.array([[1, 2, 3],[4, 5, 10],[1, -7, -8]])
    >>> get_indices(tableau2)
    (1, 0)
    """

    n_rows, n_cols = tableau.shape

    i, j = (None, None)

    for i_ in range(n_cols-1):
        if tableau[-1][i_] < -eps:
            i = i_
            break
    if i is None:
        return i, j  # ともにNone

    for j_ in range(n_rows-1):
        if tableau[j_][i] > eps:
            if j is None:
                j = j_
            else:
                lambda_j_ = culc_lambda(tableau, i, j_)
                lambda_j = culc_lambda(tableau, i, j)
                assert lambda_j is not None, "Error!"
                assert lambda_j_ is not None, "Error!"
                if lambda_j_ < lambda_j:
                    j = j_
    return i, j


def culc_lambda(tableau, i, j):
        """get i, j from tableau

    Parameters
    ----------
    tableu : ndarray
    
    Returns
    -------
    i : int
    j : int
    
    Examples
    --------
    >>> import numpy as np
    >>> tableau1 = np.array([[1, 2, 3],[4, 5, 6],[-1, -7, 8]])
    >>> get_indices(tableau1)
    (0, 1)
    >>> tableau2 = np.array([[1, 2, 3],[4, 5, 10],[1, -7, -8]])
    >>> get_indices(tableau2)
    (1, 0)
    return tableau[j][-1] / tableau[j][i]
    """


def sweep_out(tableau, i, j):
    """sweep out tableau table

    Arguments:
        tableau {ndarray} -- tableau table
        i {int} -- pivot index of column
        j {int} -- pivot index of row

    Returns:
        tableau {ndarray} -- swept out tableau table
    """
    n_rows, n_cols = tableau.shape
    for j_ in range(n_rows):
        if j_ != j:
            alpha = tableau[j_][i] / tableau[j][i]
            tableau[j_] -= alpha * tableau[j]

    return tableau


def reuse(A, b, c, tableau):
    """
    get i, j from tableau

    Parameters
    ----------
    tableu : ndarray
    
    Returns
    -------
    i : int
    j : int
    
    Examples
    --------
    >>> import numpy as np
    >>> tableau1 = np.array([[1, 2, 3],[4, 5, 6],[-1, -7, 8]])
    >>> get_indices(tableau1)
    (0, 1)
    >>> tableau2 = np.array([[1, 2, 3],[4, 5, 10],[1, -7, -8]])
    >>> get_indices(tableau2)
    (1, 0)
    """
    A = A.astype(np.float32)

    m, n = A.shape
    is_nonnegative = b.flatten() >= 0
    is_negative = b.flatten() < 0
    A_ = A[is_nonnegative]
    b_ = b[is_nonnegative].reshape(-1, 1)
    A__ = A[is_negative]
    b__ = b[is_negative].reshape(-1, 1)
    m_ = sum(is_nonnegative)
    m__ = sum(is_negative)

    for i in range(n+m, n+m+m__):
        # i列目が単位行列か判定
        is_unit = True
        idx_one = None
        for j in range(m+1):
            if abs(tableau[j][i] - 1) < eps:
                if idx_one is None:
                    idx_one = j  # i列目で1が立っている行のindex
                else:
                    break
            elif (tableau[j][i]) >= eps:
                break

        # i列目は単位行列
        tableau[idx_one] *= -1

    tableau = np.c_[
        tableau[:, :n+m].reshape(m+1, -1), tableau[:, -1].reshape(m+1, -1)]
    tableau[-1] = np.c_[-c, np.zeros((1, m+1))]

    for i in range(n):
        idx_nonzero = None
        n_zero = 0
        for j in range(m):
            if tableau[j][i] < eps:
                n_zero += 1
            else:
                idx_nonzero = j
        if n_zero == m-1:
            assert abs(tableau[idx_nonzero][i]) >= eps, "Error!"
            assert idx_nonzero is not None, "Error!"
            tableau = sweep_out(tableau, i, idx_nonzero)
            tableau[idx_nonzero] /= tableau[idx_nonzero][i]

    return tableau


if __name__ == "__main__":
    import doctest
    doctest.testmod(verbose=True)