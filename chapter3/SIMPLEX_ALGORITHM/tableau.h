#ifdef __TABLEAU_H_
#define __TABLEAU_H_


int search_i(double *tableau, int n_rows, int n_columns);

int search_j(double *tableau, int n_rows, int n_columns);

void devide_row(double **tableau, int devided_row_idx, int devisor_column_idx);

void sweap_tableau(double **tableau, int swaped_row_idx, int n_columns, double sweap_scale);


#endif
