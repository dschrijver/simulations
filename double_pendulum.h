#ifndef DOUBLE_PENDULUM_H
#define DOUBLE_PENDULUM_H

#define pi  (double) 3.14159265358979323846
#define g   (double) 9.81 // gravitational acceleration [m/s^2]
#define m1  (double) 1.0 // [kg]
#define m2  (double) 1.0 // [kg]
#define l1  (double) 1.0 // [m]
#define l2  (double) 1.0 // [m]

#define t0 (double) 0.0
#define t1 (double) 30.0
#define dt (double) 0.01
#define N  (int)    ((t1-t0)/dt)
double theta0_1[4] = {0.5*pi, 0, 0.5*pi, 0}; // {θ_1, d(θ_1)/dt, θ_2, d(θ_2)/dt}
double theta0_2[4] = {0.5*pi-0.001, 0, 0.5*pi-0.001, 0};

#endif