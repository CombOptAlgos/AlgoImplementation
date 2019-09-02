import numpy as np

eps = 1e-10

def gaussian_elimination(A):
    """GAUSSIAN ELIMINATION ALGORITHM.
    
    Parameters
    ----------
    A : array-like or sparse matrix, shape = [n_rows, n_columns]
            The input matrix. Internally, its dtype will be converted to
            ``dtype=np.float32``.

    Returns
    -------


    """

    A = A.astype("float32")

    #STEP1
    M, N = A.shape
    r = -1
    d = 1
    row = [i for i in range(M)]
    col = [j for j in range(N)]
    Z = np.c_[A, np.diag([1]*M)]

    p, q = indices_nonzero(Z, r+1)

    # Both p and q are or are not N, r)
    while not both_p_and_q_is_None(p, q):
        
        # Step2

        r += 1
        if p != r:
            Z = swap_row(Z, p, r)
            Z = swap_col(Z, N+p, N+r)
            row = swap_idx(row, p, r)
        if q!= r:
            Z = swap_col(Z, q, r)
            col = swap_idx(col, q, r)
        # Step3

        d *= Z[r][r]
        for i in range(r+1, M):
            assert abs(Z[r][r])>=eps, "Division by zero"
            alpha = Z[i][r]/Z[r][r]
            for j in range(r, N+r+1):
                Z[i][j] -= alpha * Z[r][j]
        p, q = indices_nonzero(Z, r+1)        

        print(Z)
    
    # Step4

    for k in range(r, 0, -1):
        for i in range(k):
            assert abs(Z[k][k])>=eps, "Division by zero"
            alpha = Z[i][k] / Z[k][k]
            for j in range(k-1, N+r+1):
                Z[i][j] -= alpha*Z[k][j]

    # Step5

    for k in range(r+1):
        z_kk = Z[k][k]
        for j in range(N+r+1):
            assert abs(z_kk)>=eps, "Division by zero"
            Z[k][j] /= z_kk
    
    r+=1

    A_ = np.empty((r,r))
    inv_A_ = np.empty((r,r))
    for i in range(r):
        for j in range(r):
            A_[i][j] = A[row[i]][col[j]]
            inv_A_[i][j] = Z[i][N+j]    

    print(Z)
    return r, A_, d, inv_A_


def both_p_and_q_is_None(p, q):
    """

    Parameters
    ----------


    Returns
    -------

    """

    return p is None and q is None

def indices_nonzero(Z, r):
    """

    Parameters
    ----------


    Returns
    -------

    """
    M, N_ = Z.shape
    N = N_ - M

    p = None
    q = None
    
    has_nonzero = False

    for i in range(r, M):
        for j in range(r, N):
            if Z[i][j] != 0:
                p, q = i, j
                has_nonzero = True
                break
        if has_nonzero:
            break

    assert (p is None and q is None) or (p is not None and q is not None), \
        "Both p and q should or should not be None."

    return p, q

def swap_row(Z, i, j):
    """

    Parameters
    ----------


    Returns
    -------

    """
    if i == j:
        return Z
    else:
        i, j = (i, j) if i < j else (j, i)
        return np.r_[Z[:i], Z[j].reshape(1,-1), Z[i+1:j], Z[i].reshape(1,-1), Z[j+1:]]


def swap_col(Z, i, j):
    """

    Parameters
    ----------


    Returns
    -------

    """
    if i == j:
        return Z
    else:
        return swap_row(Z.T, j, i).T

def swap_idx(indices, p, r):
    """

    Parameters
    ----------


    Returns
    -------

    """
    if p == r:
        return indices
    else:
        tmp = indices[p]
        indices[p] = r
        indices[r] = tmp
        return indices


if __name__=="__main__":
    A = np.array([
         [1,2,3],
         [0,4,6],
         [7,8,9]
    ])
    # A = np.random.randint(10, size=10000).reshape(100,-1)
    M, N = A.shape
    Z = np.c_[A, np.diag([1]*M)]
    Z[0][0] = 0
    r, A_ ,d, inv_A_ = gaussian_elimination(A)
    print("rank(A):", r)
    print("detA':", d)
    print("A':", A_)
    print("inverse A':", inv_A_)
    #print(np.linalg.det(inv_A_@A_))
    #print(np.linalg.det(A_@inv_A_))
    print(np.linalg.det(A))
    print(np.linalg.inv(A))
