#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method -- HOMEWORK
**********************************************/
void program1_3(FILE *fp)
{
	double a0, b0, x0, x1 , temp;
	int n=Nmax;
	printf("a0, b0 (a0 < b0): ");
	scanf("%lf %lf", &a0, &b0);
	if (a0 > b0) {
		double temp = b0;
		b0 = a0;
		a0 = temp;
	}
	x0 = a0; x1 = b0;

	fprintf(fp, "n\txn1\t\t|f(xn1)|\n");
	for (int i = 0; i < n; i++) {
		temp = x0 + ((x1 - x0) / 2);

		if (_f(x0) * _f(temp) < 0) {
			fprintf(fp, "%d %.15e %.15e\n", i, temp, fabs(_f(temp)));
			x1 = temp;
			if (fabs(_f(temp)) < DELTA) break;
			if (i >= Nmax) break;
			if (fabs(temp - x0) < EPSILON) break;
		}
		else {
			fprintf(fp, "%d %.15e %.15e\n", i, x1, fabs(_f(x1)));
			x0 = temp;
			if (fabs(_f(temp)) < DELTA) break;
			if (i >= Nmax) break;
			if (fabs(temp - x1) < EPSILON) break;
		}
	}
	printf("±Ù : %.15e\n", x1);
}