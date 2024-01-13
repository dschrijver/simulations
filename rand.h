#ifndef RAND_H
#define RAND_H

extern const unsigned int RAND_MAX;

void srand(unsigned int seed);
unsigned int rand15(void);
unsigned int rand16(void);
unsigned int rand32(void);
unsigned int randrange(unsigned int max);
double rand_uniform();
double rand_normal(double mu, double sigma);
void test_rand();

#endif