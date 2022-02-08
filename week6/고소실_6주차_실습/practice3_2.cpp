#include "my_solver.h"

extern "C" {
	int rpoly_(double*, int*, double*, double*, long int*);
}

void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;

	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		fscanf(fp_r, "%d", &DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);

		/********************************/

		for (int i = 0; i < NCOEF; i++) fscanf(fp_r, "%lf", &poly[i]);

		rpoly_(poly, &DEGREE, zeror, zeroi, &fail);
		if (fail) {
			fprintf(fp_w, "fail\n");
			continue;
		}
		for (i = 0; i < DEGREE; i++)
			fprintf(fp_w, "%10f ", zeror[i]);
		fprintf(fp_w, "\n");
		for (i = 0; i < DEGREE; i++)
			fprintf(fp_w, "%10f ", zeroi[i]);
		fprintf(fp_w, "\n");

		for (int i = 0; i < DEGREE; i++) {
			double resr = 0, resi = 0;
			double xr, xi;
			for (int k = 0; k < NCOEF; k++) {
				double a = zeror[i], bi = zeroi[i];
				for (int j = 0; j < NCOEF - k - 2; j++) {
					xr = a * zeror[i] - bi * zeroi[i];
					xi = a * zeroi[i] + bi * zeror[i];
					a = xr; bi = xi;
				}
				if (k == NCOEF - 1) {
					resr += poly[k];
				}
				else {
					if (k == NCOEF - 2) { xr = a; xi = bi; }
					resr += xr * poly[k] - xi * 0;
					resi += xr * 0 + xi * poly[k];
				}
			}
			float res = pow(resr, 2) + pow(resi, 2);
			res = sqrt(res);
			fprintf(fp_w, "|f(x*)| = %10f\n", res);
		}
		
		/********************************/


		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}