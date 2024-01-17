#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H


#define CONST (double) (1.0/6.0)

void ode_solve(double (*f)(double, double), double t0, double t1, double dt, double y0,
               double *t, double *y);
void ode_solve_n(void (*f)(double, double*, double*), 
                 double t0, double t1, double dt, double *y0, int dim,
                 double *t, double y[][dim]);
void print_list(int len, double *x);

#endif