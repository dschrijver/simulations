#ifndef ANIMATE_DOUBLE_PENDULUM_H
#define ANIMATE_DOUBLE_PENDULUM_H


#define SCREEN_WIDTH    (int) 900
#define SCREEN_HEIGHT   (int) SCREEN_WIDTH
#define DOT_SIZE        (int) 10
#define FPS          (double) 60.0 
#define ACCURACY        (int) 2   // Number of physics steps per frame

#define pi           (double) 3.14159265358979323846
#define g            (double) 9.81 // gravitational acceleration [m/s^2]
#define m1           (double) 1.0 // [kg]
#define m2           (double) 1.0 // [kg]
#define l1           (double) 1.0 // [m]
#define l2           (double) 1.0 // [m]
#define MARGIN          (int) 25 // [pixels]
#define LENGTH       (double) ((double)SCREEN_WIDTH)/4.0-((double)MARGIN/2.0) // [pixels/m]

#define N_p             (int) 511      // Number of pendulums
#define dt           (double) (1.0/(((double)ACCURACY)*FPS))  // [s]
#define N               (int) ((t1-t0)/dt)
#define dp           (double) 0.00001   // Starting angle difference between pendulums [rad]
#define theta0       (double) (0.5*pi) // [rad]

#endif