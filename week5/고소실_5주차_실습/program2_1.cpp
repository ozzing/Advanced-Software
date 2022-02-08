#include "my_solver.h"

double get_integral(int n, double * x, double* y, double newh, double start, double end) {
		double ctr = 0;
	int i = 0;
	while(1){
		if (x[i] >= start) {
			ctr = y[i++];
			break;
		}
		i++;
	}
	while (1) {
		if (x[i] > end || i >= n) {
			break;
		}
		ctr += 2 * y[i++];
	}
	ctr += y[i];
	ctr *= (newh / 2);
	return ctr;
}


void program2_1()
{
	FILE* fp_r, * fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/
	int n; double h;
	fscanf(fp_r, "%d %lf", &n, &h);
	double x, y, ctr;
	double* samplex, * sampley, *newx, *newy;
	samplex = (double*)malloc(sizeof(double) * n);
	sampley = (double*)malloc(sizeof(double) * n);
	newx = (double*)malloc(sizeof(double) * n);
	newy = (double*)malloc(sizeof(double) * n);

	for (int i = 0; i < n; i++) {
		fscanf(fp_r, "%lf %lf", &x, &y);
		samplex[i] = x; sampley[i] = y;
	}
	for (int i = 0; i < n; i++) {
		newx[i] = (samplex[i] - samplex[0]) / (samplex[n - 1] - samplex[0]);
	}
	double newh = h / (samplex[n-1] - samplex[0]);
	double integral = get_integral(n, samplex, sampley, newh, samplex[0], samplex[n-1]);

	fprintf(fp_w, "%d %lf\n", n, newh);
	for (int i = 0; i < n; i++) {
		newy[i] = sampley[i] / integral;
		fprintf(fp_w, "%lf %llf\n", newx[i], newy[i]);
	}

	printf("*** Integrating the pdf from 0.0 to 1.0 = %llf\n", get_integral(n, newx, newy, newh, 0.0, 1.0));
	printf("*** Integrating the pdf from 0.0 to 0.25 = %llf\n", get_integral(n, newx, newy, newh, 0.0, 0.25));
	printf("*** Integrating the pdf from 0.25 to 0.5 = %llf\n", get_integral(n, newx, newy, newh, 0.25, 0.5));
	printf("*** Integrating the pdf from 0.5 to 0.75 = %llf\n", get_integral(n, newx, newy, newh, 0.5, 0.75));
	printf("*** Integrating the pdf from 0.75 to 1.0 = %llf\n", get_integral(n, newx, newy, newh, 0.75, 1.0));


	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
