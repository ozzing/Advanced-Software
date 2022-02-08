#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

double C, b;
double p[4][3];
double tr[4][2];

void fcn3_1_1(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/

		fvec[0] = pow(x[0] - p[0][0], 2) + pow(x[1] - p[0][1], 2) + pow(x[2] - p[0][2], 2) - pow((C * (tr[0][1] + x[3] - tr[0][0])), 2);
		fvec[1] = pow(x[0] - p[1][0], 2) + pow(x[1] - p[1][1], 2) + pow(x[2] - p[1][2], 2) - pow((C * (tr[1][1] + x[3] - tr[1][0])), 2);
		fvec[2] = pow(x[0] - p[2][0], 2) + pow(x[1] - p[2][1], 2) + pow(x[2] - p[2][2], 2) - pow((C * (tr[2][1] + x[3] - tr[2][0])), 2);
		fvec[3] = pow(x[0] - p[3][0], 2) + pow(x[1] - p[3][1], 2) + pow(x[2] - p[3][2], 2) - pow((C * (tr[3][1] + x[3] - tr[3][0])), 2);

		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/

		fjac[0] = 2 * (x[0] - p[0][0]);
		fjac[1] = 2 * (x[0] - p[1][0]);
		fjac[2] = 2 * (x[0] - p[2][0]);
		fjac[3] = 2 * (x[0] - p[3][0]);
		fjac[4] = 2 * (x[1] - p[0][1]);
		fjac[5] = 2 * (x[1] - p[1][1]);
		fjac[6] = 2 * (x[1] - p[2][1]);
		fjac[7] = 2 * (x[1] - p[3][1]);
		fjac[8] = 2 * (x[2] - p[0][2]);
		fjac[9] = 2 * (x[2] - p[1][2]);
		fjac[10] = 2 * (x[2] - p[2][2]);
		fjac[11] = 2 * (x[2] - p[3][2]);
		fjac[12] = -2 * pow(C, 2) * (x[3] + tr[0][1] - tr[0][0]);
		fjac[13] = -2 * pow(C, 2) * (x[3] + tr[1][1] - tr[1][0]);
		fjac[14] = -2 * pow(C, 2) * (x[3] + tr[2][1] - tr[2][0]);
		fjac[15] = -2 * pow(C, 2) * (x[3] + tr[3][1] - tr[3][0]);

		/********************************/
	}
}

void fcn3_1_2(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/

	fvec[0] = pow(x[0] - p[0][0], 2) + pow(x[1] - p[0][1], 2) + pow(x[2] - p[0][2], 2) - pow((C * (tr[0][1] + x[3] - tr[0][0])), 2);
	fvec[1] = pow(x[0] - p[1][0], 2) + pow(x[1] - p[1][1], 2) + pow(x[2] - p[1][2], 2) - pow((C * (tr[1][1] + x[3] - tr[1][0])), 2);
	fvec[2] = pow(x[0] - p[2][0], 2) + pow(x[1] - p[2][1], 2) + pow(x[2] - p[2][2], 2) - pow((C * (tr[2][1] + x[3] - tr[2][0])), 2);
	fvec[3] = pow(x[0] - p[3][0], 2) + pow(x[1] - p[3][1], 2) + pow(x[2] - p[3][2], 2) - pow((C * (tr[3][1] + x[3] - tr[3][0])), 2);

	/********************************/
}


void program3_1(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.0, 0.0, 0.0, 0.0};	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	for (int t = 0; t < 3; t++) {
		char readfile[256];
		char hybrjfile[256];
		char hybrdfile[256];

		sprintf(readfile, "GPS_signal_%d.txt", t);
		sprintf(hybrjfile, "GPS_position_3-1_%d.txt", t);
		sprintf(hybrdfile, "GPS_position_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}
		FILE* fp_j = fopen(hybrjfile, "w");
		if (fp_j == NULL) {
			printf("%s file open error...\n", hybrjfile);
			return;
		}
		FILE* fp_d = fopen(hybrdfile, "w");
		if (fp_d == NULL) {
			printf("%s file open error...\n", hybrdfile);
			return;
		}

		/********************************/
		fscanf(fp_r, "%lf %lf", &C, &b);
		for (int i = 0; i < SOLNUMS; i++) {
			fscanf(fp_r, "%lf %lf %lf %lf %lf", &p[i][0], &p[i][1], &p[i][2], &tr[i][0], &tr[i][1]);
		}

		printf("초기값 x1, x2, x3, x4 입력: ");
		scanf("%lf %lf %lf %lf", &x[0], &x[1], &x[2], &x[3]);
		x[3] = b;

		hybrj1_(fcn3_1_1, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
		fprintf(fp_j, "x[0] = %f, x[1] = %f, x[2] = %f, x[3] = %f\n", x[0], x[1], x[2], x[3]);
		fprintf(fp_j, "f(x) : %lf\n", pow(x[0] - p[0][0], 2) + pow(x[1] - p[0][1], 2) + pow(x[2] - p[0][2], 2) - pow((C * (tr[0][1] + x[3] - tr[0][0])), 2));
		fprintf(fp_j, "f(x) : %lf\n", pow(x[0] - p[1][0], 2) + pow(x[1] - p[1][1], 2) + pow(x[2] - p[1][2], 2) - pow((C * (tr[1][1] + x[3] - tr[1][0])), 2));
		fprintf(fp_j, "f(x) : %lf\n", pow(x[0] - p[2][0], 2) + pow(x[1] - p[2][1], 2) + pow(x[2] - p[2][2], 2) - pow((C * (tr[2][1] + x[3] - tr[2][0])), 2));
		fprintf(fp_j, "f(x) : %lf\n", pow(x[0] - p[3][0], 2) + pow(x[1] - p[3][1], 2) + pow(x[2] - p[3][2], 2) - pow((C * (tr[3][1] + x[3] - tr[3][0])), 2));

		hybrd1_(fcn3_1_2, &n, x, fvec, &tol, &info, wa, &lwa);
		fprintf(fp_d, "x[0] = %f, x[1] = %f, x[2] = %f, x[3] = %f\n", x[0], x[1], x[2], x[3]);
		fprintf(fp_d, "f(x) : %lf\n", pow(x[0] - p[0][0], 2) + pow(x[1] - p[0][1], 2) + pow(x[2] - p[0][2], 2) - pow((C * (tr[0][1] + x[3] - tr[0][0])), 2));
		fprintf(fp_d, "f(x) : %lf\n", pow(x[0] - p[1][0], 2) + pow(x[1] - p[1][1], 2) + pow(x[2] - p[1][2], 2) - pow((C * (tr[1][1] + x[3] - tr[1][0])), 2));
		fprintf(fp_d, "f(x) : %lf\n", pow(x[0] - p[2][0], 2) + pow(x[1] - p[2][1], 2) + pow(x[2] - p[2][2], 2) - pow((C * (tr[2][1] + x[3] - tr[2][0])), 2));
		fprintf(fp_d, "f(x) : %lf\n", pow(x[0] - p[3][0], 2) + pow(x[1] - p[3][1], 2) + pow(x[2] - p[3][2], 2) - pow((C * (tr[3][1] + x[3] - tr[3][0])), 2));

		/********************************/
		fclose(fp_r);
		fclose(fp_j);
		fclose(fp_d);
	}
}
