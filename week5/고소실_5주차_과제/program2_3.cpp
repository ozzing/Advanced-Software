#include "my_solver.h"
#include <time.h>
#include <math.h>
#define MY_RAND_MAX 32767

// HOMEWORK
void program2_3()
{
	FILE* fp_p, * fp_r, * fp_w;
	fp_p = fopen("pdf_table.txt", "r");
	fp_r = fopen("random_event_table.txt", "r");
	fp_w = fopen("histogram.txt", "w");
	/***************************************************/

	int n; double h; int rnum; double val;
	fscanf(fp_p, "%d %lf", &n, &h);
	fscanf(fp_r, "%d", &rnum);
	double* samplex, * sampley;
	samplex = (double*)malloc(sizeof(double) * n);
	sampley = (double*)malloc(sizeof(double) * n);
	int sum[10] = { 0, };
	double max = 0, min = 1000;
	int high = 0;
	for (int i = 0; i < n; i++) {
		fscanf(fp_p, "%lf %lf", &samplex[i], &sampley[i]);
		if (samplex[i] > max) max = samplex[i];
		if (samplex[i] < min) min = samplex[i];
	}
	for (int i = 0; i < rnum; i++) {
		fscanf(fp_r, "%lf", &val);
		if (val < min || val > max) continue;
		int x = (int)(val * 10) % 10;
		sum[x]++;
	}
	for (int i = 0; i < 10; i++) {
		fprintf(fp_w, "| %.2f~%.2f ", i / 10.0, (i + 1) / 10.0);
		printf("\n%.2f~%.2f | %d", i / 10.0, (i + 1) / 10.0, sum[i]);
		if (sum[i] > high) high = sum[i];
	}
	fprintf(fp_w, "|\n");
	printf("\n");
	for (int j = 0; j < high; j++) {
		for (int i = 0; i < 10; i++) {
			if (sum[i] > 0) {
				fprintf(fp_w, "       *       ");
				sum[i]--;
			}
			else {
				fprintf(fp_w, "               ");
			}
		}
		fprintf(fp_w, "\n");
	}

	/***************************************************/
	if (fp_p != NULL) fclose(fp_p);
	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}

// HOMEWORK

void program2_2_a()
{
	__int64 start, freq, end;
	float resultTime = 0;


	// something to do...
	
	FILE* fp_r, * fp_w;
	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");
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

		if (i != 0 || i != n - 1) {
			newy[i] = (sampley[0] + 2 * sum + y) * (h / 2);
		}
		sum += y;
	}
	int nr;
	printf("난수 개수 n: ");
	scanf("%d", &nr);
	fprintf(fp_w, "%d\n", nr);
	printf("%d\n", nr);
	CHECK_TIME_START;
	for (int i = 0; i < nr; i++) {
		double x0 = samplex[0], x1 = samplex[n-1], temp;
		double random = (double)rand() / MY_RAND_MAX;
		for (int j = 0; j < Nmax; j++) {
			temp = x0 + ((x1 - x0) / 2);
			if (_f(x0, n, samplex, sampley, newy, random) * _f(temp, n, samplex, sampley, newy, random) < 0) {
				x1 = temp;
			}
			else {
				x0 = temp;
			}
			if (fabs(_f(temp, n, samplex, sampley, newy, random)) < DELTA) break;
			if (j >= Nmax) break;
			if (fabs(x1 - x0) < EPSILON) break;
		}
		fprintf(fp_w, "%.15e\n", temp);
		printf("%.15e\n", temp);
	}
	CHECK_TIME_END(resultTime);

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
	// end


	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
}


void program2_2_b()
{
	__int64 start, freq, end;
	float resultTime = 0;

	// something to do...
	FILE* fp_r, * fp_w;
	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");
	
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

		if (i != 0 || i != n - 1) {
			newy[i] = (sampley[0] + 2 * sum + y) * (h / 2);
		}
		sum += y;
	}
	int nr;
	printf("난수 개수 n: ");
	scanf("%d", &nr);
	fprintf(fp_w, "%d\n", nr);
	printf("%d\n", nr);
	CHECK_TIME_START; 
	for (int i = 0; i < nr; i++) {
		double x0 = samplex[0], x1 = samplex[n - 1], temp;
		double random = (double)rand() / MY_RAND_MAX;
		for (int j = 0; j < 25; j++) {
			temp = x0 + ((x1 - x0) / 2);
			if (_f(x0, n, samplex, sampley, newy, random) * _f(temp, n, samplex, sampley, newy, random) < 0) {
				x1 = temp;
			}
			else {
				x0 = temp;
			}
			if (fabs(_f(temp, n, samplex, sampley, newy, random)) < DELTA) break;
			if (j >= Nmax) break;
			if (fabs(x1 - x0) < EPSILON) break;
		}
		for (int j = 1; j < Nmax; j++) {
			temp = x1 - _f(x1, n, samplex, sampley, newy, random) * ((x1 - x0) / (_f(x1, n, samplex, sampley, newy, random) - _f(x0, n, samplex, sampley, newy, random)));
			if (fabs(_f(temp, n, samplex, sampley, newy, random)) < DELTA) break;
			if (i >= Nmax) break;
			if (fabs(temp - x1) < EPSILON) break;
			x0 = x1;
			x1 = temp;
		}
		fprintf(fp_w, "%.15e\n", temp);
		printf("%.15e\n", temp);
	}
	CHECK_TIME_END(resultTime);

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
	// end


	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);
}


void assignment2_1() {
	srand((unsigned int)time(NULL));
	int lambda; double iter;
	printf("put a lambda value : ");
	scanf("%d", &lambda);
	printf("**avg: %lf\tvar: %lf**\n", (1.0 / lambda), (1.0 / pow(lambda, 2)));
	while (1) {
		printf("put a number to iterate (to stop, put -1) : ");
		scanf("%lf", &iter);
		if (iter == -1) break;
		double* samplex;
		samplex = (double*)malloc(sizeof(double) * iter);
		long double avg = 0, var = 0;
		for (int i = 0; i < iter; i++) {
			double random = (rand() % 32767) / 32767.0; //(double)rand() / MY_RAND_MAX;
			samplex[i] = - (log(fabs(1 - random)) / lambda);
			double temp = samplex[i] / iter;
			avg += temp;
		}
		for (int i = 0; i < iter; i++) {
			double vari = pow(samplex[i] - avg, 2);
			double temp = vari / iter;
			var += temp;
		}
		printf("avg: %Lf\tvar: %Lf\n", avg, var);
	}
}