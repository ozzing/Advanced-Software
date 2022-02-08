#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
void program1_2(FILE* fp) {
	double x0, x1, temp;
	int n=Nmax;
	printf("x0, x1: ");
	scanf("%lf %lf", &x0, &x1);
	if (fp == NULL)
		return;

	fprintf(fp, "n\txn1\t\t|f(xn1)|\n");
	fprintf(fp, "0 %.15e %.15e\n", x1, fabs(_f(x1)));
	for (int i = 1; i < n; i++) {
		temp = x1 - _f(x1) * ((x1-x0)/(_f(x1) - _f(x0)));
		fprintf(fp, "%d %.15e %.15e\n", i, temp, fabs(_f(temp)));
		if (fabs(_f(temp)) < DELTA) break;
		if (i >= Nmax) break;
		if (fabs(temp - x1) < EPSILON) break;
		x0 = x1;
		x1 = temp;
	}
	printf("±Ù : %.15e\n", x1);
}
