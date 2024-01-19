#include <stdio.h> // printf(), getchar(), fopen(), popen(), fclose(), pclose(), fprintf(), fflush(), 
#include <math.h> // cos(), sin()
#include <unistd.h> // usleep()

#include "runge_kutta.h" // ode_solve_n()
#include "multiple_double_pendulums.h"

void double_pendulum(double t, double *y, double *dy) {
    (void) t;
    double theta1 = y[0];
    double dtheta1 = y[1];
    double theta2 = y[2];
    double dtheta2 = y[3];
    dy[0] = dtheta1;
    dy[1] = (-g*(2.0*m1+m2)*sin(theta1)-m2*g*sin(theta1-2.0*theta2)-2.0*sin(theta1-theta2)*m2*(dtheta2*dtheta2*l2+dtheta1*dtheta1*l1*cos(theta1-theta2)))/
            (l1*(2.0*m1+m2-m2*cos(2.0*theta1-2.0*theta2)));
    dy[2] = dtheta2;
    dy[3] = (2.0*sin(theta1-theta2)*(dtheta1*dtheta1*l1*(m1+m2)+g*(m1+m2)*cos(theta1) + dtheta2*dtheta2*l2*m2*cos(theta1-theta2)))/
            (l2*(2.0*m1+m2-m2*cos(2.0*theta1-2.0*theta2)));
}

int main(void) {
    double t;
    double theta[N_p][4] = {0};
    t = t0;
    for (int j = 0; j < N_p; j++) {
        theta[j][0] = theta0 - j*dp;
        theta[j][2] = theta[j][0];
    }

    int sleep_time = (int)(dt*1000000.0);
    int i_step;
    if (dt > 1.0/fps) i_step = 1;
    else {
        i_step = (int)(1.0/fps/dt);
    }

    FILE *temp = fopen("data.temp", "w");
    fclose(temp);
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    fprintf(gnuplotPipe, "set terminal wxt size 900,900\n");
    fprintf(gnuplotPipe, "set xrange [%f:%f]\n", -(l1+l2)-0.2*l2, l1+l2+0.2*l2);
    fprintf(gnuplotPipe, "set yrange [%f:%f]\n", -(l1+l2)-0.2*l2, l1+l2+0.2*l2);

    double color_step = ((double)0xff/((double)N_p));
    for (int j = 0; j < N_p; j++) {
        fprintf(gnuplotPipe, "set style line %d linecolor rgb '#%02x00%02x' linetype 1 linewidth 2 pointtype 7 pointsize 1.5\n",
                j+1, (int)(color_step*((double)j)), (int)((double)0xff - color_step*((double)j)));
    }

    
    fflush(gnuplotPipe);

    double x[N_p][3]={0};
    double y[N_p][3]={0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N_p; j++) {
            runge_kutta_nstep(double_pendulum, dt, 4, t, theta[j], theta[j]);
        }
        t+=dt;
        if ((i % i_step) == 0) {
            temp = fopen("data.temp", "w");

            for (int j = 0; j < N_p; j++) {
                x[j][1] = l1*sin(theta[j][0]);
                x[j][2] = x[j][1]+l2*sin(theta[j][2]);
                y[j][1] = -l1*cos(theta[j][0]);
                y[j][2] = y[j][1]-l2*cos(theta[j][2]);
                for (int k = 0; k < 3; k++) { 
                    fprintf(temp, "%lf %lf\n", x[j][k], y[j][k]);
                }
                fprintf(temp, "\n\n");
            }
            fflush(temp);
            fprintf(gnuplotPipe, "plot ");
            for (int j = 0; j < (N_p-1); j++) {
                fprintf(gnuplotPipe, "\"data.temp\" index %d title '' with linespoints linestyle %d, ", j, j+1);
            }
            fprintf(gnuplotPipe, "\"data.temp\" index %d title '' with linespoints linestyle %d\n", N_p-1, N_p);

            fflush(gnuplotPipe);
            usleep(sleep_time*i_step);
            fclose(temp);
        }
    }
    pclose(gnuplotPipe);
    
    return 0;
}