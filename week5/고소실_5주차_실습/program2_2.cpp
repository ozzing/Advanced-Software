#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MY_RAND_MAX 32767

double _f(double temp, int n, double *x, double*y, double*newy, double rand) {
	double res=0;
	for (int i = 0; i < n - 1; i++) {
		if (x[i + 1] > temp) {
			res = (y[i] + ((y[i + 1] - y[i]) / (x[i + 1] - x[i])) * ((temp - x[i]) / 2)) * (temp - x[i]);
			res = res + newy[i] - rand;
			break;
		}
	}
	return res;
}


void program2_2()
{
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/
	srand((unsigned int)time(NULL));

	int n; double h;
	fscanf(fp_r, "%d %lf", &n, &h);
	double x, y;
	double* samplex, * sampley, * newy;
	samplex = (double*)malloc(sizeof(double) * n);
	sampley = (double*)malloc(sizeof(double) * n);
	newy = (double*)malloc(sizeof(double) * n);
	newy[0] = 0; newy[n - 1] = 1;
	double sum = 0;

	for (int i = 0; i < n; i++) {
		fscanf(fp_r, "%lf %lf", &x, &y);
		samplex[i] = x; sampley[i] = y;

		if (i != 0 || i != n-1) {
			newy[i] = (sampley[0] + 2 * sum + y) * (h / 2);
		}
		sum += y;
	}

	int nr;
	printf("난수 개수 n: ");
	scanf("%d", &nr);
	fprintf(fp_w, "%d\n", nr);
	printf("%d\n", nr);
	for (int i = 0; i < nr; i++) {
		double x0 = 0, x1 = 1, temp;
		double random = (double)rand() / MY_RAND_MAX;
		for (int i = 0; i < Nmax; i++) {
			temp = x0 + ((x1 - x0) / 2);
			if (_f(x0, n, samplex, sampley, newy, random) * _f(temp, n, samplex, sampley, newy, random) < 0) {
				x1 = temp;
			}
			else {
				x0 = temp;
			}
			if (fabs(_f(temp, n, samplex, sampley, newy, random)) < DELTA) break;
			if (i >= Nmax) break;
			if (fabs(x1 - x0) < EPSILON) break;
		}
		fprintf(fp_w, "%.15e\n", temp);
		printf("%.15e\n", temp);
	}

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
