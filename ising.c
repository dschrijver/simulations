#include <stdio.h> // printf()
#include <math.h> // sqrt(), exp()
#include <time.h> // time()
#include <raylib.h>

#include "rand.h"
#include "ising.h"


int mod_neg(int x, int y) {
    if (x < 0) {
        return x+y;
    } else {
        return x;
    }
}

void update_grid_size() {
    num_cells_x = screen_width / cell_size;
    num_cells_y = screen_height / cell_size;
    margin_x = (screen_width%cell_size)/2;
    margin_y = (screen_height%cell_size)/2;
}

double delta_E(unsigned int i, unsigned int j, int grid[num_cells_x][num_cells_y]) {
    double result = 2*H*mu_b*(double)grid[i][j];
    result += 2*J*grid[i][j]*(grid[mod_neg(i-1, num_cells_x)][j] + grid[(i+1)%num_cells_x][j] + 
                              grid[i][mod_neg(j-1, num_cells_y)] + grid[i][(j+1)%num_cells_y]);
    return result;
}

double p(double del_E) {
    if (del_E < 0) return 1.0;
    return exp(-del_E/(k_b*T));
}

void evolve_spins(int grid[num_cells_x][num_cells_y]) {
    int i, j;
    double x;
    for (int z = 0; z < 100; z++) {
        i = randrange(num_cells_x); 
        j = randrange(num_cells_y);
        x = rand_uniform();
        if (x <= p(delta_E(i,j,grid))) {
            grid[i][j] *= -1;
            break;
        }
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen_width, screen_height, "Ising model");
    double start_time, end_time, frame_time, dt = 1.0/FPS;
    int evo_freq = EVO_FREQ_INI;

    num_cells_x = SCREEN_WIDTH_INI / cell_size;
    num_cells_y = SCREEN_HEIGHT_INI / cell_size;
    margin_x = (SCREEN_WIDTH_INI%cell_size)/2;
    margin_y = (SCREEN_HEIGHT_INI%cell_size)/2;

    Color colors[2] = {{0, 0, 255, 255}, {255, 0, 0, 255}};
    float mouse_wheel_movement;
    char cell_size_string[32];

    // Select grid size
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)
        start_time = GetTime();

        if (IsKeyReleased(KEY_ENTER)) {
            break;
        }

        if (IsWindowResized()) {
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();
            update_grid_size();
        }

        mouse_wheel_movement = GetMouseWheelMove();
        if ((mouse_wheel_movement == 1.0) && (screen_width>3*cell_size) && (screen_height>3*cell_size)) {
            cell_size++;
            update_grid_size();
        } 
        if ((mouse_wheel_movement == -1.0) && (cell_size > 5)) {
            cell_size--;
            update_grid_size();
        } 

        BeginDrawing();
            ClearBackground(BLACK);

            for (int i = 0; i < num_cells_x; i++) {
                for (int j = 0; j < num_cells_y; j++) {
                    DrawRectangle(margin_x+i*cell_size, margin_y+j*cell_size, 
                                  cell_size, cell_size, LIGHTGRAY);
                    DrawRectangle(margin_x+i*cell_size+cell_size/10, margin_y+j*cell_size+cell_size/10, 
                                  4*cell_size/5, 4*cell_size/5, RAYWHITE);
                }
            }
            sprintf(cell_size_string, "CELL_SIZE = %d px", cell_size);
            DrawText(cell_size_string, 20, 40, 20, DARKGRAY);
            DrawText("Press ESCAPE to exit, use SCROLL_WHEEL to change cell size, hit ENTER to continue", 
                     20, 20, 20, DARKGRAY);
        EndDrawing();
        SwapScreenBuffer(); // Flip the back buffer to screen (front buffer)

        end_time = GetTime();
        frame_time = end_time - start_time;
        if ((dt-frame_time) > 0) WaitTime(dt-frame_time);
    }

    // Initialize grid
    int grid[num_cells_x][num_cells_y], paused = 0;
    double last_evo = GetTime(), last_frame = GetTime(), new_frame;
    char info_string[128], constants_string_1[64], constants_string_2[128];
    Color background_color = {200, 200, 200, 200};
    for (int i = 0; i < num_cells_x; i++) {
        for (int j = 0; j < num_cells_y; j++) {
            grid[i][j] = (int)(rand_uniform()*2.0)*2-1;
        }
    }
    T = 293.0, J = 0.43*k_b*T, H = 0.0;

    while (!WindowShouldClose()) { // Detect window close button or ESC key
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)
        start_time = GetTime();

        if (IsKeyReleased(KEY_BACKSPACE)) {
            for (int i = 0; i < num_cells_x; i++) {
                for (int j = 0; j < num_cells_y; j++) {
                    grid[i][j] = (int)(rand_uniform()*2.0)*2-1;
                }
            }
        }

        if (IsKeyReleased(KEY_SPACE)) {
            paused = !paused;
        }

        if (IsKeyReleased(KEY_UP)) {
            H += 1;
        }
        if (IsKeyReleased(KEY_DOWN)) {
            H -= 1;
        }
        if (IsKeyReleased(KEY_RIGHT)) {
            T += 10;
        }
        if (IsKeyReleased(KEY_LEFT) && (T > 10)) {
            T -= 10;
        }

        mouse_wheel_movement = GetMouseWheelMove();
        if (mouse_wheel_movement == 1.0) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                if ((evo_freq < ((int)FPS))) {
                    evo_freq++;
                } else if (evo_freq > 1200) {
                    evo_freq += evo_freq/10/((int)FPS)*((int)FPS);
                } else {
                    evo_freq += (int)FPS;
                }
            } else {
                J += 0.01*k_b*T;
            }
        } 
        if ((mouse_wheel_movement == -1.0) && (evo_freq > 1)) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                if ((evo_freq <= ((int)FPS))) {
                    evo_freq--;
                } else if (evo_freq > 1200) {
                    evo_freq -= evo_freq/10/((int)FPS)*((int)FPS);
                } else {
                    evo_freq -= (int)FPS;
                }
            } else {
                J -= 0.01*k_b*T;
            }
        } 

        if (!paused) {
            if (evo_freq > FPS) {
                for (int i = 0; i < (evo_freq/((int)FPS)); i++) {
                    evolve_spins(grid);
                }
            } else {
                if ((GetTime() - last_evo) > 1.0/((double)evo_freq)) {
                    evolve_spins(grid);
                    last_evo = GetTime();
                }
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);

            for (int i = 0; i < num_cells_x; i++) {
                for (int j = 0; j < num_cells_y; j++) {
                    DrawRectangle(margin_x+i*cell_size, margin_y+j*cell_size, 
                                cell_size, cell_size, colors[(grid[i][j]+1)/2]);
                }
            }
            DrawRectangle(10, 10, 950, 100, background_color);
            DrawText("Press ESCAPE to exit, SPACE to pause, BACKSPACE to randomize the spins", 
                     20, 20, 20, BLACK);
            sprintf(constants_string_1, "SCROLL_WHEEL to change J = %.02f k_b T (T_c at 0.43 k_b T)", J/(k_b*T));
            DrawText(constants_string_1, 20, 40, 20, BLACK);
            sprintf(constants_string_2, "UP/DOWN ARROW to change H = %.02f A/m, LEFT/RIGHT ARROW to change T = %.02f K", H, T);
            DrawText(constants_string_2, 20, 60, 20, BLACK);
            new_frame = GetTime();
            sprintf(info_string, "CTRL+SCROLL_WHEEL to change the evolution speed (%d evo/s), FPS = %.02f", 
                    evo_freq, 1.0/(new_frame-last_frame));
            DrawText(info_string, 20, 80, 20, BLACK);
            last_frame = new_frame;


        EndDrawing();
        SwapScreenBuffer(); // Flip the back buffer to screen (front buffer)

        end_time = GetTime();
        frame_time = end_time - start_time;
        if ((dt-frame_time) > 0) WaitTime(dt-frame_time);
    }

    CloseWindow();
    return 0;
}
