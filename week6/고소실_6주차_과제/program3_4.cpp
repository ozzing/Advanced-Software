#include "my_solver.h"
#define index(row, col, dim) row*dim+col
#define max 32

extern "C" {
    int gespp_(int*, float*, int*, int*, float*);
    int solve_(int*, float*, int*, int*, float*, float*);
}

void program3_4() {
	int i, ia, j, n, l[max];
	float a[max * max], b[max], x[max], s[max];
	float copya[max * max], copyb[max];
	char readfile[256];
	char writefile[256];
	/*
	for (int f = 0; f < 2; f++) {
		for (int t = 2; t <= 32; t++) {
			if (t != 2 && t != 3 && t != 4 && t != 5 && t != 7 && t != 9 && t != 12 && t != 16 && t != 24 && t != 32) {}
			else {
				if (f == 0) {
					sprintf(readfile, "General_%d.txt", t);
					sprintf(writefile, "General_solution_%d.txt", t);
				}
				else {
					sprintf(readfile, "Hilbert_%d.txt", t);
					sprintf(writefile, "Hilbert_solution_%d.txt", t);
				}
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
				*/
				/********************************/
				
	FILE* fp_r = fopen("linear_system_3-4.txt", "r");
	if (fp_r == NULL) {
		printf("%s file open error...\n", "linear_system_3-4.txt");
		return;
	}
	FILE* fp_w = fopen("solution_3-4.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "solution_3-4.txt");
		return;
	}

	fscanf(fp_r, "%d\n", &n);
	if (n > 32) {
		fprintf(fp_w, "fail");
		return;
	}
	ia = n;
	float f;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(fp_r, "%f\n", &a[index(j, i, n)]);
			copya[index(j, i, n)] = a[index(j, i, n)];
		}
	}
	for (int i = 0; i < n; i++) {
		fscanf(fp_r, "%f", &b[i]);
		copyb[i] = b[i];
	}

	gespp_(&n, a, &ia, l, s);
	solve_(&n, a, &ia, l, b, x);

	fprintf(fp_w, "%d\n", n);
	for (i = 0; i < n; i++) {
		fprintf(fp_w, "%.6f\n", x[i]);
	}

	double numer = 0, denom = 0, temp;
	for (int i = 0; i < n; i++) {
		temp = 0;
		for (int j = 0; j < n; j++) {
			temp += copya[index(j, i, n)] * x[j];
		}
		temp -= copyb[i];
		numer += pow(temp, 2);
		denom += pow(copyb[i], 2);
	}
	fprintf(fp_w, "%.6f\n", sqrt(numer) / sqrt(denom));
	/********************************/

	fclose(fp_r);
	fclose(fp_w);

}
