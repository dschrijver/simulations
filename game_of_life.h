#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#define SCREEN_WIDTH_INI    (int) 1280
#define SCREEN_HEIGHT_INI   (int) 720
#define CELL_SIZE_INI       (int) 20        // [pixels/cell]
#define EVO_FREQ_INI        (int) 4         // [evolutions/s]
#define FPS              (double) 60.0      // [1/s]

int screen_width = SCREEN_WIDTH_INI, screen_height = SCREEN_HEIGHT_INI;
int cell_size, num_cells_x, num_cells_y, margin_x, margin_y;

void update_grid_size();
int mod_neg(int x, int y);
void evolve_grid(int grid[num_cells_x][num_cells_y]);

#endif