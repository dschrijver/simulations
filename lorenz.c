#include <stdio.h>

#include "runge_kutta.h" // ode_solve_n()
#include "lorenz.h"


void lorenz(double t, double *y, double *dy) {
    (void) t;
    dy[0] = sigma*(y[1] - y[0]);
    dy[1] = y[0]*(rho - y[2]) - y[1];
    dy[2] = y[0]*y[1] - beta*y[2];
}


int main(void) {
    double t[N];
    double output[N][3];
    ode_solve_n(lorenz, t0, t1, dt, input, 3, t, output);
    

    // Plotting
    FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
    FILE *temp = fopen("data.temp", "w");
    for (int j = 0; j < N; j++) {
        fprintf(temp, "%lf %lf %lf\n", output[j][0], output[j][1], output[j][2]);
    }
    fprintf(gnuplot_pipe, "set terminal wxt size 1000, 700\nset xlabel \"x\"\nset ylabel \"y\"\nset zlabel \"z\"\n");
    fprintf(gnuplot_pipe, "splot \"data.temp\" title \"Lorenz system\" with lines\n");

    fclose(temp);
    pclose(gnuplot_pipe);
    return 0;
}