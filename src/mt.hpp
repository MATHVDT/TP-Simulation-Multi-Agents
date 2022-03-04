/**
 * @file mt.hpp
 * @brief
 */
#ifndef MT_HPP
#define MT_HPP

void initMT();
void testMT();

unsigned long genrand_int32(void);
long genrand_int31(void);

double genrand_real1(void);
double genrand_real2(void);
double genrand_real3(void);

double genrand_res53(void);

double uniform(double a, double b);
double negExp(double mean);
int dice_6();
int dice_n(int n);

#endif