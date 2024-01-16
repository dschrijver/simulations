#include <stdio.h> // printf()
#include <stdlib.h> // malloc() 

#include "gnuplot_i/gnuplot_i.h"
#include "rungekutta.h"


void print_list(int len, double *x) {
    printf("[");
    for (int i = 0; i < len-1; i++) {
        printf("%f, ", x[i]);
    }
    printf("%f", x[len-1]);
    printf("]\n");
}

double runge_kutta(double t, double y) {
    double c1, c2, c3, c4;
    c1 = tau*f(t, y);
    c2 = tau*f(t+0.5*tau, y+0.5*c1);
    c3 = tau*f(t+0.5*tau, y+0.5*c2);
    c4 = tau*f(t+tau, y+c3);
    return y + CONST*(c1 + 2*c2 + 2*c3 + c4);
}

double f(double t, double y) {
    (void) t; (void) y; // Removes unused variable warnings. 
    return y;
}

int main(void) {
    double t[N];
    double y[N];
    t[0] = t0;
    y[0] = y0;
    for (int i = 0; i < N-1; i++) {
        y[i+1] = runge_kutta(t[i], y[i]);
        t[i+1] = t[i]+tau;
    }

    // Plotting
    gnuplot_ctrl *h;
    h = gnuplot_init();
    gnuplot_cmd(h, "set title 'Title'");
    gnuplot_set_axislabel(h, "x", "t");
    gnuplot_set_axislabel(h, "y", "y");
    char cmd_string[64];
    sprintf(cmd_string, "set xrange [%f:%f]", t0, t1);
    gnuplot_cmd(h, cmd_string);
    sprintf(cmd_string, "set yrange [%f:%f]", y0, y[N-1]);
    gnuplot_cmd(h, cmd_string);

    gnuplot_setterm(h, "wxt", 1000, 700);
    gnuplot_setstyle(h, "points");
    gnuplot_plot_coordinates(h, t, y, N, "dy/dt = y, y(0)=1");
    gnuplot_setstyle(h, "lines");
    gnuplot_plot_equation(h, "exp(x)", "fit := exp(x)"); 
    
    printf("Press enter to close the program: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
    gnuplot_close(h);

    return 0;
}