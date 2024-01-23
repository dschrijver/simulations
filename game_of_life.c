#include <stdio.h>
#include <math.h> // Raylib requires math.h
#include <raylib.h>
#include <stdlib.h> // malloc()

#include "game_of_life.h"


void update_grid_size() {
    num_cells_x = screen_width / cell_size;
    num_cells_y = screen_height / cell_size;
    margin_x = (screen_width%cell_size)/2;
    margin_y = (screen_height%cell_size)/2;
}

int mod_neg(int x, int y) {
    if (x < 0) {
        return x+y;
    } else {
        return x;
    }
}

void evolve_grid(int grid[num_cells_x][num_cells_y]) {
    int grid_copy[num_cells_x][num_cells_y], num_live_neighbors;
    for (int i = 0; i < num_cells_x; i++) {
        for (int j = 0; j < num_cells_y; j++) {
            num_live_neighbors = grid[mod_neg(i-1, num_cells_x)][mod_neg(j-1, num_cells_y)] + grid[i][mod_neg(j-1, num_cells_y)] + grid[(i+1)%num_cells_x][mod_neg(j-1, num_cells_y)] + 
                                 grid[mod_neg(i-1, num_cells_x)][j] + grid[(i+1)%num_cells_x][j] + 
                                 grid[mod_neg(i-1, num_cells_x)][(j+1)%num_cells_y] + grid[i][(j+1)%num_cells_y] + grid[(i+1)%num_cells_x][(j+1)%num_cells_y];
            if (grid[i][j]) {
                if ((num_live_neighbors < 2) || (num_live_neighbors > 3)) {
                    grid_copy[i][j] = 0;
                } else {
                    grid_copy[i][j] = 1;
                }
            } else {
                if (num_live_neighbors == 3) {
                    grid_copy[i][j] = 1;
                } else {
                    grid_copy[i][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < num_cells_x; i++) {
        for (int j = 0; j < num_cells_y; j++) {
            grid[i][j] = grid_copy[i][j];
        }
    }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen_width, screen_height, "Double Pendulum");

    double start_time, end_time, frame_time, dt = 1.0/FPS;
    int evo_freq = EVO_FREQ_INI;

    cell_size = CELL_SIZE_INI;
    num_cells_x = SCREEN_WIDTH_INI / cell_size;
    num_cells_y = SCREEN_HEIGHT_INI / cell_size;
    margin_x = (SCREEN_WIDTH_INI%cell_size)/2;
    margin_y = (SCREEN_HEIGHT_INI%cell_size)/2;

    float mouse_wheel_movement;

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
        if ((mouse_wheel_movement == -1.0) && (cell_size > 10)) {
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

            DrawText("Press ESCAPE to exit, use SCROLL_WHEEL to change cell size, hit ENTER to continue", 
                     20, 20, 20, DARKGRAY);
        EndDrawing();
        SwapScreenBuffer(); // Flip the back buffer to screen (front buffer)

        end_time = GetTime();
        frame_time = end_time - start_time;
        if ((dt-frame_time) > 0) WaitTime(dt-frame_time);
    }

    // Initialize grid
    int grid[num_cells_x][num_cells_y], mouse_x, mouse_y, grid_i, grid_j;
    for (int i = 0; i < num_cells_x; i++) {
        for (int j = 0; j < num_cells_y; j++) {
            grid[i][j] = 0;
        }
    }

    while (!WindowShouldClose()) { // Detect window close button or ESC key
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)
        start_time = GetTime();

        if (IsKeyReleased(KEY_ENTER)) {
            break;
        }

        if (IsKeyReleased(KEY_BACKSPACE)) {
            for (int i = 0; i < num_cells_x; i++) {
                for (int j = 0; j < num_cells_y; j++) {
                    grid[i][j] = 0;
                }
            }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            mouse_x = GetMouseX();
            mouse_y = GetMouseY();
            if (!(mouse_x < margin_x || mouse_x > (margin_x + cell_size*num_cells_x) ||
                  mouse_y < margin_y || mouse_y > (margin_y + cell_size*num_cells_y))) {
                grid_i = (mouse_x - margin_x)/cell_size;
                grid_j = (mouse_y - margin_y)/cell_size;
                grid[grid_i][grid_j] = !grid[grid_i][grid_j];
            } 
            
        }

        BeginDrawing();
            ClearBackground(BLACK);

            for (int i = 0; i < num_cells_x; i++) {
                for (int j = 0; j < num_cells_y; j++) {
                    if (grid[i][j]) {
                        DrawRectangle(margin_x+i*cell_size, margin_y+j*cell_size, 
                                    cell_size, cell_size, LIGHTGRAY);
                        DrawRectangle(margin_x+i*cell_size+cell_size/10, margin_y+j*cell_size+cell_size/10, 
                                    4*cell_size/5, 4*cell_size/5, RAYWHITE);
                    }
                }
            }

            DrawText("Press ESCAPE to exit, BACKSPACE to clear the grid, LEFT_CLICK to toggle a cell, hit ENTER to start", 
                     20, 20, 20, DARKGRAY);
        EndDrawing();
        SwapScreenBuffer(); // Flip the back buffer to screen (front buffer)

        end_time = GetTime();
        frame_time = end_time - start_time;
        if ((dt-frame_time) > 0) WaitTime(dt-frame_time);
    }

    // MAIN GAME LOOP
    int paused = 0;
    double last_evo = GetTime();
    char evo_speed_string[64];
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)
        start_time = GetTime();

        if (IsKeyReleased(KEY_SPACE)) {
            paused = !paused;
        }

        if (IsKeyReleased(KEY_BACKSPACE)) {
            for (int i = 0; i < num_cells_x; i++) {
                for (int j = 0; j < num_cells_y; j++) {
                    grid[i][j] = 0;
                }
            }
            paused = 1;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            mouse_x = GetMouseX();
            mouse_y = GetMouseY();
            if (!(mouse_x < margin_x || mouse_x > (margin_x + cell_size*num_cells_x) ||
                  mouse_y < margin_y || mouse_y > (margin_y + cell_size*num_cells_y))) {
                grid_i = (mouse_x - margin_x)/cell_size;
                grid_j = (mouse_y - margin_y)/cell_size;
                grid[grid_i][grid_j] = !grid[grid_i][grid_j];
            }    
        }

        mouse_wheel_movement = GetMouseWheelMove();
        if (mouse_wheel_movement == 1.0) {
            if ((evo_freq < ((int)FPS))) {
                evo_freq++;
            } else {
                evo_freq += (int)FPS;
            }
        } 
        if ((mouse_wheel_movement == -1.0) && (evo_freq > 1)) {
            if ((evo_freq <= ((int)FPS))) {
                evo_freq--;
            } else {
                evo_freq -= (int)FPS;
            }
        } 

        if (!paused) {
            if (evo_freq > FPS) {
                for (int i = 0; i < (evo_freq/((int)FPS)); i++) {
                    evolve_grid(grid);
                }
            } else {
                if ((GetTime() - last_evo) > 1.0/((double)evo_freq)) {
                    evolve_grid(grid);
                    last_evo = GetTime();
                }
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);

            for (int i = 0; i < num_cells_x; i++) {
                for (int j = 0; j < num_cells_y; j++) {
                    if (grid[i][j]) {
                        DrawRectangle(margin_x+i*cell_size, margin_y+j*cell_size, 
                                    cell_size, cell_size, LIGHTGRAY);
                        DrawRectangle(margin_x+i*cell_size+cell_size/10, margin_y+j*cell_size+cell_size/10, 
                                    4*cell_size/5, 4*cell_size/5, RAYWHITE);
                    }
                }
            }

            DrawText("Press ESCAPE to exit, LEFT_CLICK to toggle a cell, hit SPACE to toggle pause, BACKSPACE to clear the grid", 
                     20, 20, 20, DARKGRAY);
            sprintf(evo_speed_string, "SCROLL_WHEEL to change the evolution speed (%d evo/s)", evo_freq);
            DrawText(evo_speed_string, 20, 40, 20, DARKGRAY);
        EndDrawing();
        SwapScreenBuffer(); // Flip the back buffer to screen (front buffer)

        end_time = GetTime();
        frame_time = end_time - start_time;
        if ((dt-frame_time) > 0) WaitTime(dt-frame_time);
    }

    CloseWindow();
    return 0;
}