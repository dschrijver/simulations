#include <stdio.h> // printf()
#include <time.h> // time()
#include <unistd.h> // usleep()
#include <math.h> // sqrt(), exp()

#include "rand.h"
#include "ising.h"


double delta_E(unsigned int i, unsigned int j) {
    double result = 2*H*mu_b*(double)grid[i][j];
    result += 2*J*grid[i][j]*(grid[(i-1)%L][j] + grid[(i+1)%L][j] + 
                              grid[i][(j-1)%L] + grid[i][(j+1)%L]);
    return result;
}

double p(double del_E) {
    if (del_E < 0) return 1.0;
    return exp(-del_E/(k_b*T));
}

void print_grid() {
    for (unsigned int i = 0; i < L; i++) {
        for (unsigned int j = 0; j < L; j++) {
            if (grid[i][j] == 1) printf("🟥");
            else printf("🟦");
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    srand((unsigned int)time(NULL));

    // Initialize grid
    double x;
    unsigned int i, j;
    for (i = 0; i < L; i++) {
        for (j = 0; j < L; j++) {
            x = (double)rand15() / RAND_MAX;
            if (x < 0.5) grid[i][j] = -1;
            else grid[i][j] = 1;
        }
    }

    // Start of Ising simulation
    int broken = 0;
    for (int y = 0; y < steps; y++) {
        broken = 0;
        for (unsigned int z = 0; z < N; z++) {
            i = randrange(L); 
            j = randrange(L);
            x = rand_uniform();
            // printf("%.15f\n", delta_E(i,j));
            if (x <= p(delta_E(i,j))) {
                grid[i][j] *= -1;
                broken = 1;
                break;
            }
        }
        if (!broken) {
            printf("Stable configuration found!\n");
            break;
        }
        if ((y % 500) == 0) {
            print_grid();
        }
        usleep(200); // Microseconds
    }

    return 0;
}
