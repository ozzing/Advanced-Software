#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/
void sp_program1_1(FILE* fp) {
	float x0, x1;
	int n = Nmax;
	printf("x0: ");
	scanf("%f", &x0);
	if (fp == NULL)
		return;

	fprintf(fp, "n\txn1\t\t|f(xn1)|\n");
	fprintf(fp, "0 %.15e %.15e\n", x0, fabs(_sp_f(x0)));
	for (int i = 1; i < n; i++) {
		x1 = x0 - (_sp_f(x0) / _sp_fp(x0));
		fprintf(fp, "%d %.15e %.15e\n", i, x1, fabs(_sp_f(x1)));
		if (fabs(_sp_f(x1)) < DELTA) break;
		if (i >= Nmax) break;
		if (fabs(x1 - x0) < EPSILON) break;
		x0 = x1;
	}
	printf("±Ù : %.15e\n", x1);
}
