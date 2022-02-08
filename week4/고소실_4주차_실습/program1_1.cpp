#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	double x0, x1;
	int n=Nmax;
	printf("x0: ");
	scanf("%lf", &x0);
	if (fp == NULL)
		return;

	fprintf(fp, "n\txn1\t\t|f(xn1)|\n");
	fprintf(fp, "0 %.15e %.15e\n", x0, fabs(_f(x0)));
	for (int i = 1; i < n; i++) {
		x1 = x0 - (_f(x0) / _fp(x0));
		fprintf(fp, "%d %.15e %.15e\n", i, x1, fabs(_f(x1)));
		if (fabs(_f(x1)) < DELTA) break;
		if (i >= Nmax) break;
		if (fabs(x1 - x0) < EPSILON) break;
		x0 = x1;
	}

}
