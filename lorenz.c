#include <stdio.h>

#include "gnuplot_i/gnuplot_i.h" // For plotting
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
    double output_T[3][N];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            output_T[i][j] = output[j][i];
        }
    }

    // Plotting
    gnuplot_ctrl *h1;
    h1 = gnuplot_init();
    gnuplot_cmd(h1, "set title 'Lorenz system'");
    gnuplot_set_axislabel(h1, "x", "x");
    gnuplot_set_axislabel(h1, "y", "y");
    gnuplot_set_axislabel(h1, "z", "z");
    gnuplot_setterm(h1, "wxt", 1000, 700);
    gnuplot_setstyle(h1, "lines");
    char title[64];
    sprintf(title, "σ=%.2f, ρ=%.2f, β=%.2f", sigma, rho, beta);
    gnuplot_splot(h1, output_T[0], output_T[1], output_T[2], N, title);

    printf("Press enter to close the program: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }

    gnuplot_close(h1);

    return 0;
}