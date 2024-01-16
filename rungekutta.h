#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H


#define y0  (double) 1.0 // Initial value
#define t0  (double) 0.0 // Initial time
#define t1  (double) 2.0 // Final time
#define tau (double) 0.01 // Timestep 
#define N   (int)    ((t1 - t0) / tau)

#define CONST (double) 1.0/6.0

void print_list(int len, double *x);
double runge_kutta(double t, double y);
double f(double t, double y);

#endif