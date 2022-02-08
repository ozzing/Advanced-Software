#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_2_1(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/

	fvec[0] = x[0] + 10 * x[1] + 9;
	fvec[1] = sqrt(5) * (x[2] - x[3]) - 2 * sqrt(5);
	fvec[2] = pow(x[1] - 2 * x[2], 2) - 9;
	fvec[3] = sqrt(10) * pow(x[0] - x[3], 2) - 2 * sqrt(10);

	/********************************/
}

void program3_2(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.9, -0.9, 1.25, -1.25 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_found_3-2.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_found_3-2.txt");
		return;
	}

	/********************************/

	hybrd1_(fcn3_2_1, &n, x, fvec, &tol, &info, wa, &lwa);
	fprintf(fp_w, "x = %f, y = %f, z = %f, w = %f\n", x[0], x[1], x[2], x[3]);
	fprintf(fp_w, "f(x) : %lf\n", x[0] + 10 * x[1] + 9);
	fprintf(fp_w, "f(x) : %lf\n", sqrt(5) * (x[2] - x[3]) - 2 * sqrt(5));
	fprintf(fp_w, "f(x) : %lf\n", pow(x[1] - 2 * x[2], 2) - 9);
	fprintf(fp_w, "f(x) : %lf\n", sqrt(10) * pow(x[0] - x[3], 2) - 2 * sqrt(10));

	/********************************/

	fclose(fp_w);
}