#ifndef ISING_H
#define ISING_H

#define SCREEN_WIDTH_INI    (int) 1280
#define SCREEN_HEIGHT_INI   (int) 720
#define CELL_SIZE_INI       (int) 5                 // [pixels/cell]
#define FPS              (double) 60.0              // [1/s]
#define EVO_FREQ_INI        (int) 2000*((int)FPS)   // [evolutions/s]


const double    mu_b = 9.274E-24;
const double     k_b = 1.380649E-23;

// On the onset of ordening, correlation between spins starts to show.
// J = 0.1*k_b*T is completely unordened, J = 0.43*k_b*T shows domains, 
// and if J is any bigger, i.e. J = 1.0*k_b*T, all spins will allign. 
double T, J, H; // Room temperature

int screen_width = SCREEN_WIDTH_INI, screen_height = SCREEN_HEIGHT_INI;
int cell_size = CELL_SIZE_INI;
int num_cells_x, num_cells_y, margin_x, margin_y;

int mod_neg(int x, int y);
void update_grid_size();
double delta_E(unsigned int i, unsigned int j, int grid[num_cells_x][num_cells_y]);
double p(double del_E);
void evolve_spins(int grid[num_cells_x][num_cells_y]);

#endif