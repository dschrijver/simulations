#include <stdio.h> // printf(), getchar(), fopen(), popen(), fclose(), pclose(), fprintf(), fflush(), 
#include <math.h> // cos(), sin()
#include <unistd.h> // usleep()

#include "runge_kutta.h" // ode_solve_n()
#include "double_pendulum.h"

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
    double t[N];
    double theta_1[N][4], theta_2[N][4];
    ode_solve_n(double_pendulum, t0, t1, dt, theta0_1, 4, t, theta_1);
    ode_solve_n(double_pendulum, t0, t1, dt, theta0_2, 4, t, theta_2);

    int sleep_time = (int)(dt*1000000.0);
    int i_step;
    if (dt > 1.0/60.0) i_step = 1;
    else {
        i_step = (int)(1.0/60.0/dt);
    }

    FILE *temp = fopen("data.temp", "w");
    fclose(temp);
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    fprintf(gnuplotPipe, "set terminal wxt size 900,900\n");
    fprintf(gnuplotPipe, "set xrange [%f:%f]\n", -(l1+l2)-0.2*l2, l1+l2+0.2*l2);
    fprintf(gnuplotPipe, "set yrange [%f:%f]\n", -(l1+l2)-0.2*l2, l1+l2+0.2*l2);
    fprintf(gnuplotPipe, "set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pointtype 7 pointsize 1.5\n");
    fprintf(gnuplotPipe, "set style line 2 linecolor rgb '#ff0000' linetype 1 linewidth 2 pointtype 7 pointsize 1.5\n");
    fflush(gnuplotPipe);

    double x_1[3]={0}, y_1[3]={0};
    double x_2[3]={0}, y_2[3]={0};

    for (int i = 0; i < N; i+=i_step) {
        temp = fopen("data.temp", "w");

        x_1[1] = l1*sin(theta_1[i][0]);
        x_1[2] = x_1[1]+l2*sin(theta_1[i][2]);
        y_1[1] = -l1*cos(theta_1[i][0]);
        y_1[2] = y_1[1]-l2*cos(theta_1[i][2]);

        x_2[1] = l1*sin(theta_2[i][0]);
        x_2[2] = x_2[1]+l2*sin(theta_2[i][2]);
        y_2[1] = -l1*cos(theta_2[i][0]);
        y_2[2] = y_2[1]-l2*cos(theta_2[i][2]);

        for (int j = 0; j < 3; j++) {
            fprintf(temp, "%lf %lf\n", x_1[j], y_1[j]);
        }
        fprintf(temp, "\n\n");
        for (int j = 0; j < 3; j++) {
            fprintf(temp, "%lf %lf\n", x_2[j], y_2[j]);
        }
        fflush(temp);
        fprintf(gnuplotPipe, "plot \"data.temp\" index 0 title \"θ_{1,2}(0) = π/2\" with linespoints linestyle 1, ");
        fprintf(gnuplotPipe, "'' index 1 title \"Δθ_{1,2}(0) = 0.001\" with linespoints linestyle 2\n");
        fflush(gnuplotPipe);

        usleep(sleep_time*i_step);

        fclose(temp);
    }
    pclose(gnuplotPipe);
    
    return 0;
}