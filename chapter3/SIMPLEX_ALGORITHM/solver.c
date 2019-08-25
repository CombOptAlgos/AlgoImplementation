#include <stdio.h>
#include <stdbool.h>


/*
 * SIMPLEX ALGORYTHM
 * Input:
 *      int m, n
 *      A: m * n matrix
 *      b: vector length m
 *      c: vector length n
 * Output:
 *      A vertex x of P := {x | Ax <= b} attaining max{cx | x in P}
 *      of
 *      vector w with Aw <= 0 and cw > 0
 */

int main(void) {
    /* read input data */
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    double A[m][n];
    double b[m];
    double c[n];
    int i, j;
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++)
            scanf("%lf", &A[i][j]);
    }
    for (i=0; i<m; i++)
        scanf("%lf", &b[i]);
    for (i=0; i<n; i++)
        scanf("%lf", &c[i]);

    /* 
     * VERTEX FINDING ALGORYTHM
     *  vertex of P is given as a subvector of the optimum solution of a LP below.
     *      A'' : rows of A whose corresponding entry of b is negative.
     *      A' : rows of A whose corresponding entry of b is non-negative.
     *      b'' : negative entries of b.
     *      b' : non-negative entries of b
     *      min{(1A'')x + 1y | A'x <= b', A''x + y >= b'', x >= 0}
     *  using tableau method here.
     *  starting with the tableau
     *      -----------------------------------------
     *      |   A'  |   0   |   I   |   0   ||  b'  |
     *      -----------------------------------------
     *      |  -A'' |   -I  |   0   |   I   || -b'' |
     *      =========================================
     *      |  1A'' |   1   |   0   |   0   ||  0   |
     *      -----------------------------------------
     */
    bool b_sgn[m];  // if b[i] >= 0 then b_sgn[i] = true else b_sgn[i] = false.
    int _m = 0;     // length of b'.
    int __m = 0;    // length of b''.
    for (i=0; i<m; i++) {
        bool sgn;
        b_sgn[i] = (sgn = (b[i] >= 0));
        if (sgn)
            _m++;
        else
            __m++;
    }
    double _A[_m][n];   // A'
    double _b[_m];      // b'
    double __A[__m][n]; // A''
    double __b[__m];    // b''
    int _i = 0;
    int __i = 0;
    int _j, __j;
    for (i=0; i<m; i++) {
        if (b_sgn[i]) {
            for (_j=0; _j<n; _j++)
                _A[_i][_j] = A[i][_j];
            _b[_i] = b[i];
            _i++;
        } else {
            for (__j=0; __j<n; __j++)
                __A[__i][__j] = A[i][__j];
            __b[__i] = b[i];
            __i++;
        }
    }
    double tableau[m+1][m+n+__m+1]; // tableau
    _i = 0;
    _j = 0;
    __i = 0;
    __j = 0;
    for (i=0; i<_m; i++) {
        if (i<_m) {
            for (j=0; j<m+n+__m+1; j++) {
                if (j<n) {
                    tableau[i][j] = _A[_i][_j];
                    _j++;
                } else if (j<n+__m)
                    tableau[i][j] = 0;
                else if (j<n+m) {
                    if (j-n-__m+1==_i)
                        tableau[i][j] = 1;
                    else
                        tableau[i][j] = 0;
                } else if (j<n+m+__m)
                    tableau[i][j] = 0;
                else {
                    tableau[i][j] = _b[_i];
                    _j = 0;
                }
            }
            _i++;
        } else if (i<m) {
            for (j=0; j<m+n+__m+1; j++) {
                if(j<n) {
                    tableau[i][j] = -__A[__i][__j];
                    __j++;
                } else if (j<n+__m) {
                    if (j-n+1==__j)
                        tableau[i][j] = -1;
                    else
                        tableau[i][j] = 0;
                } else if (j<n+m)
                    tableau[i][j] = 0;
                else if (j<n+m+__m) {
                    if (j-n-m+1==__j)
                        tableau[i][j] = 1;
                    else
                        tableau[i][j] = 0;
                } else {
                    tableau[i][j] = -__b[__i];
                    __j = 0;
                }
            }
            __i++;
        } else {
            for (j=0; j<m+n+__m+1; j++) {
                if (j<n) {
                    double sum = 0;
                    for (__i=0; __i<__m; __i++)
                        sum += __A[__i][j];
                    tableau[i][j] = sum;
                } else if (j<n+__m)
                    tableau[i][j] = 1;
                else
                    tableau[i][j] = 0;
            }
        }
    }
    /* implement here */



    return 0;
}
