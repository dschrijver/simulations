#ifndef LORENZ_H
#define LORENZ_H

#define sigma (double) 10.0
#define rho   (double) 28.0
#define beta  (double) (8.0/3.0)

#define t0 (double) 0.0
#define t1 (double) 100.0
#define dt (double) 0.01
#define N  (int)    ((t1-t0)/dt)
double input[3] = {1.0, 0.0, 0.0};

#endif