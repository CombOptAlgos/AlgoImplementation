#include <stdio.h>
#include <stdbool.h>

void sweap_tableau(double **tableau, int *swaped_row, int *n_columns, double *scale) {
    int j = 0;
    for (j=0; j<n_columns; j++) {
