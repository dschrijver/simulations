#ifndef PENDULUM_H
#define PENDULUM_H

#define pi (double) 3.14159265358979323846
#define g (double) 9.81 // gravitational acceleration [m/s^2]
#define l (double) 1.0 // length of the pendulum [m]

#define t0 (double) 0.0
#define t1 (double) 20.0
#define dt (double) 0.01
#define N  (int)    ((t1-t0)/dt)
double theta0[2] = {0.5*pi, -5.0};

#endif