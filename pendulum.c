#include <stdio.h> // printf(), getchar()
#include <math.h> // sin()

#include "gnuplot_i/gnuplot_i.h" // For plotting
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

    double theta_T[2][N];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            theta_T[i][j] = theta[j][i];
        }
    }

    // Plotting
    gnuplot_ctrl *h1;
    h1 = gnuplot_init();
    gnuplot_cmd(h1, "set title 'd^2θ/d^t2= -g/l*sin(θ), θ(0)=π/2'");
    gnuplot_set_axislabel(h1, "x", "t");
    gnuplot_set_axislabel(h1, "y", "θ");
    char cmd_string[64];
    sprintf(cmd_string, "set xrange [%f:%f]", t0, t1);
    gnuplot_cmd(h1, cmd_string);

    gnuplot_setterm(h1, "wxt", 1000, 700);
    gnuplot_setstyle(h1, "lines");
    gnuplot_plot_coordinates(h1, t, theta_T[0], N, "θ");

    gnuplot_ctrl *h2;
    h2 = gnuplot_init();
    gnuplot_cmd(h2, "set title 'd^2θ/d^t2= -g/l*sin(θ), θ(0)=π/2'");
    gnuplot_set_axislabel(h2, "x", "t");
    gnuplot_set_axislabel(h2, "y", "dθ/dt");
    // char cmd_string[64];
    sprintf(cmd_string, "set xrange [%f:%f]", t0, t1);
    gnuplot_cmd(h2, cmd_string);

    gnuplot_setterm(h2, "wxt", 1000, 700);
    gnuplot_setstyle(h2, "lines");
    gnuplot_plot_coordinates(h2, t, theta_T[1], N, "dθ/dt");
    
    printf("Press enter to close the program: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }

    gnuplot_close(h1);
    gnuplot_close(h2);

    return 0;
}