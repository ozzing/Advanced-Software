#ifndef __MY_SOLVER_H__
#define __MY_SOLVER_H__

#include <stdio.h>
#include <Windows.h>

#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);

#define DELTA 0.000001
#define Nmax 50
#define EPSILON 0.00001

void program2_1();
void program2_2();

// HOMEWORK
void program2_2_a(void);
void program2_2_b(void);
void program2_3();
void assignment2_1(void);
double _f(double temp, int n, double* x, double* y, double* newy, double rand);

#endif  // __MY_SOLVER_H__
