#include <stdio.h> // printf(), getchar()
#include <math.h> // sin()

#include "runge_kutta.h" // ode_solve_n()
#include "pendulum.h"


void pendulum(double t, double *y, double *dy) {
    (void) t;
    dy[0] = y[1];
    dy[1] = -g/l*sin(y[0]);
}

int main(void) {
    double t[N];
    double theta[N][2];
    ode_solve_n(pendulum, t0, t1, dt, theta0, 2, t, theta);

    // Plotting
    FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
    FILE *temp = fopen("data.temp", "w");
    for (int j = 0; j < N; j++) {
        fprintf(temp, "%lf %lf\n", t[j], theta[j][0]);
    }
    fprintf(gnuplot_pipe, "set terminal wxt size 1000, 700\nset xlabel \"t\"\nset ylabel \"θ\"\n");
    fprintf(gnuplot_pipe, "set title 'd^2θ/d^t2= -g/l*sin(θ), θ(0)=π/2'\n");
    fprintf(gnuplot_pipe, "plot \"data.temp\" title \"Pendulum\" with lines\n");

    fclose(temp);
    pclose(gnuplot_pipe);

    return 0;
}