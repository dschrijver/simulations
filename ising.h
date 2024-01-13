#ifndef ISING_H
#define ISING_H

#define            L (unsigned int) 50 // CHANGE HERE!
#define            N (unsigned int) L*L

const int      steps = 200000; // CHANGE HERE!
const double       T = 293.0; // Room temperature
const double    mu_b = 9.274E-24;
const double     k_b = 1.380649E-23;

// On the onset of ordening, correlation between spins starts to show.
// J = 0.1*k_b*T is completely unordened, J = 0.43*k_b*T shows domains, 
// and if J is any bigger, i.e. J = 1.0*k_b*T, all spins will allign. 
const double       J = 0.43*k_b*T; // CHANGE HERE!
const double       H = 0.0; // CHANGE HERE!

signed int grid[L][L] = {0};

double delta_E(unsigned int i, unsigned int j);
double p(double del_E);
void print_grid();

#endif