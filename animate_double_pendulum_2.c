#include <stdio.h>
#include <math.h> // Raylib requires math.h
#include <raylib.h>
#include <rlgl.h> // rlSetLineWidth

#include "runge_kutta.h" // ode_solve_n()
#include "animate_double_pendulum_2.h"


void double_pendulum(double t, double *y, double *dy) {
    (void) t;
    double theta1 = y[0];
    double dtheta1 = y[1];
    double theta2 = y[2];
    double dtheta2 = y[3];
    dy[0] = dtheta1;
    dy[1] = (-grav*(2.0*m1+m2)*sin(theta1)-m2*grav*sin(theta1-2.0*theta2)-2.0*sin(theta1-theta2)*m2*(dtheta2*dtheta2*l2+dtheta1*dtheta1*l1*cos(theta1-theta2)))/
            (l1*(2.0*m1+m2-m2*cos(2.0*theta1-2.0*theta2)));
    dy[2] = dtheta2;
    dy[3] = (2.0*sin(theta1-theta2)*(dtheta1*dtheta1*l1*(m1+m2)+grav*(m1+m2)*cos(theta1) + dtheta2*dtheta2*l2*m2*cos(theta1-theta2)))/
            (l2*(2.0*m1+m2-m2*cos(2.0*theta1-2.0*theta2)));
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Double Pendulum");
    rlSetLineWidth(2.0);

    double t = 0.0;
    double theta[N_p][4] = {0};
    for (int j = 0; j < N_p; j++) {
        theta[j][0] = theta0 - j*dp;
        theta[j][2] = theta[j][0];
    }

    double x[2] = {0.0};
    double y[2] = {0.0};
    double start_time = 0.0, end_time = GetTime(), frame_time = GetTime();// For FPS management
    char fps_counter[10];
    Color color = {255, 255, 0, 255};
    double color_step = (((double)255)/((double)N_p));
    int paused = 0;
    
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)

        start_time = GetTime();

        if (IsKeyReleased(KEY_SPACE)) {
            paused = !paused;
        }

        if (IsKeyReleased(KEY_ENTER)) {
            t = 0;
            for (int j = 0; j < N_p; j++) {
                theta[j][0] = theta0 - j*dp;
                theta[j][1] = 0;
                theta[j][2] = theta[j][0];
                theta[j][3] = 0;
            }
            if (paused) paused = 0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        color.g = 255;
        color.b = 0;
        for (int j = 0; j < N_p; j++) {
            x[0] = l1*sin(theta[j][0]);
            x[1] = x[0]+l2*sin(theta[j][2]);
            y[0] = -l1*cos(theta[j][0]);
            y[1] = y[0]-l2*cos(theta[j][2]);
            color.g = 255 - (char)(((double)j)*color_step);
            color.b = (char)(((double)j)*color_step);
            DrawCircle((int)(((double)LENGTH)*x[0] + ((double)SCREEN_WIDTH)/2.0), 
                        (int)(-((double)LENGTH)*y[0] + ((double)SCREEN_HEIGHT)/2.0), 
                        DOT_SIZE, color); 
            DrawCircle((int)(((double)LENGTH)*x[1] + ((double)SCREEN_WIDTH)/2.0), 
                        (int)(-((double)LENGTH)*y[1] + ((double)SCREEN_HEIGHT)/2.0), 
                        DOT_SIZE, color);
            DrawLine((int)(((double)SCREEN_WIDTH)/2.0), (int)(((double)SCREEN_HEIGHT)/2.0), 
                        (int)(((double)LENGTH)*x[0] + ((double)SCREEN_WIDTH)/2.0), 
                        (int)(-((double)LENGTH)*y[0] + ((double)SCREEN_HEIGHT)/2.0), 
                        color);
            DrawLine((int)(((double)LENGTH)*x[0] + ((double)SCREEN_WIDTH)/2.0),
                        (int)(-((double)LENGTH)*y[0] + ((double)SCREEN_HEIGHT)/2.0), 
                        (int)(((double)LENGTH)*x[1] + ((double)SCREEN_WIDTH)/2.0), 
                        (int)(-((double)LENGTH)*y[1] + ((double)SCREEN_HEIGHT)/2.0), 
                        color);
        }
        DrawText("Press ESCAPE to exit, SPACE to pause and ENTER to reset", 20, 20, 20, DARKGRAY);
        sprintf(fps_counter, "%.01f fps", 
                1.0/(GetTime() - frame_time));
        frame_time = GetTime();
        DrawText(fps_counter, SCREEN_WIDTH-100, 20, 20, DARKGRAY);
        DrawCircle((int)(((double)SCREEN_WIDTH)/2.0), (int)(((double)SCREEN_HEIGHT)/2.0), 
                    DOT_SIZE, BLACK); 
        EndDrawing();
        SwapScreenBuffer(); // Flip the back buffer to screen (front buffer)

        if (!paused) {
            for (int i = 0; i < ACCURACY; i++) {
                for (int j = 0; j < N_p; j++) {
                    runge_kutta_nstep(double_pendulum, dt, 4, t, theta[j], theta[j]);
                }
                t += dt;
            }
        }
            
        end_time = GetTime();
        if ((((double)ACCURACY)*dt-(end_time-start_time))>0.0) WaitTime(((double)ACCURACY)*dt-(end_time-start_time));
    }
    CloseWindow();

    return 0;
}