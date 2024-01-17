#include <stdio.h>

#include "runge_kutta.h"


void ode_solve(double (*f)(double, double), double t0, double t1, double dt, double y0,
               double *t, double *y) {
    double c1, c2, c3, c4;
    int N = (int)((t1-t0)/dt);
    t[0] = t0;
    y[0] = y0;
    for (int i = 0; i < N-1; i++) {
        c1 = dt*f(t[i], y[i]);
        c2 = dt*f(t[i]+0.5*dt, y[i]+0.5*c1);
        c3 = dt*f(t[i]+0.5*dt, y[i]+0.5*c2);
        c4 = dt*f(t[i]+dt, y[i]+c3);
        y[i+1] = y[i] + CONST*(c1 + 2*c2 + 2*c3 + c4);
        t[i+1] = t[i]+dt;
    }
}

void ode_solve_n(void (*f)(double, double*, double*), 
                 double t0, double t1, double dt, double *y0, int dim,
                 double *t, double y[][dim]) {
    double c1[dim], c2[dim], c3[dim], c4[dim];
    double var2[dim], var3[dim], var4[dim];
    int n = (int)((t1-t0)/dt);
    t[0] = t0;
    for (int i = 0; i < dim; i++) {
        y[0][i] = y0[i];
    }
    for (int i = 0; i < n-1; i++) {
        f(t[i], y[i], c1);
        for (int j = 0; j < dim; j++) {
            var2[j] = y[i][j]+0.5*dt*c1[j];
        }
        f(t[i]+0.5*dt, var2, c2);
        for (int j = 0; j < dim; j++) {
            var3[j] = y[i][j]+0.5*dt*c2[j];
        }
        f(t[i]+0.5*dt, var3, c3);
        for (int j = 0; j < dim; j++) {
            var4[j] = y[i][j]+dt*c3[j];
        }
        f(t[i]+dt, var4, c4);
        for (int j = 0; j < dim; j++) {
            y[i+1][j] = y[i][j] + CONST*dt*(c1[j] + 2*c2[j] + 2*c3[j]+ c4[j]);
        }
        t[i+1] = t[i]+dt;
    }
}

void print_list(int len, double *x) {
    printf("[");
    for (int i = 0; i < len-1; i++) {
        printf("%f, ", x[i]);
    }
    printf("%f]\n", x[len-1]);
}
