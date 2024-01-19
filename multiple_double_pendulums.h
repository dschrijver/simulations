#ifndef MULTIPLE_DOUBLE_PENDULUMS_H
#define MULTIPLE_DOUBLE_PENDULUMS_H

#define pi  (double) 3.14159265358979323846
#define g   (double) 9.81 // gravitational acceleration [m/s^2]
#define m1  (double) 1.0 // [kg]
#define m2  (double) 1.0 // [kg]
#define l1  (double) 1.0 // [m]
#define l2  (double) 1.0 // [m]

#define t0      (double) 0.0   // [s]
#define t1      (double) 30.0  // [s]
#define dt      (double) 0.01  // [s]
#define N       (int)    ((t1-t0)/dt)
#define N_p     (int)    40
#define dp      (double) 0.0001   // Starting angle difference between pendulums [rad]
#define theta0  (double) (0.5*pi) // [rad]
#define fps     (double) 30.0  // [1/s]

#endif