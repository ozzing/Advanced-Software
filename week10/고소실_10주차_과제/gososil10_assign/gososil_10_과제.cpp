#include <stdio.h>
#include <string.h>
#include <random>
#include <time.h>

#include <math.h>
#include <time.h>
#include <Windows.h>

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;
float compute_time1, compute_time2;


#define MATDIM 1024
#define HW1_N 100000
double *hw1_x, hw1_E, hw1_var1, hw1_var2;
float hw2_a, hw2_b, hw2_c, hw2_naive_ans[2], hw2_pre_ans[2];
float hw3_1, hw3_2, hw3_3_a, hw3_3_b, hw3_4, hw3_5;

/* hw1 */
void init_hw1(int fixed);
void hw1_calc_e();
void hw1_calc_var1();
void hw1_calc_var2();
/* hw2 */
void hw2_naive();
void hw2_safe();
float hw2_verify(float x);
/* hw3 */
void h3_1();
void h3_2();
void h3_3();
void h3_4();
void h3_5();


void main(void)
{
	srand((unsigned)time(NULL));

	/* hw1 */
	puts("====== hw1 ======");
	init_hw1(1);
	hw1_calc_e();
	CHECK_TIME_START;
	hw1_calc_var1();
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw1_calc_var1 = %f ms\n", compute_time);
	printf("hw1_calc_var1 value = %.15f\n", hw1_var1);


	CHECK_TIME_START;
	hw1_calc_var2();
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw1_calc_var2 = %f ms\n", compute_time);
	printf("hw1_calc_var2 value = %.15f\n", hw1_var2);
	puts("");
	
	/* hw2 */
	puts("====== hw2 ======");
	printf("a, b, c : ");
	scanf("%f %f %f", &hw2_a, &hw2_b, &hw2_c);
	hw2_naive();
	hw2_safe();
	printf("naive result    : %.15f, %.15f\n", hw2_naive_ans[0], hw2_naive_ans[1]);
	printf("advanced result : %.15f, %.15f\n", hw2_pre_ans[0], hw2_pre_ans[1]);
	puts("");
	printf("Verifying naive ans    : %.15f, %.15f\n", hw2_verify(hw2_naive_ans[0]), hw2_verify(hw2_naive_ans[1]));
	printf("Verifying advanced ans : %.15f, %.15f\n", hw2_verify(hw2_pre_ans[0]), hw2_verify(hw2_pre_ans[1]));
	puts("");

	/* hw3 */
	h3_1();
	h3_2();
	h3_3();
	h3_4();
	h3_5();
}
void init_hw1(int fixed)
{
	double *ptr;
	hw1_x = (double *)malloc(sizeof(double)*HW1_N);

	if (fixed)
	{
		double tmp = HW1_N;
		for (int i = 0; i < HW1_N; i++)
		{
			if( i & 1) tmp -= 0.0001;
			hw1_x[i] = tmp;
		}
	}
	else
	{
		srand((unsigned)time(NULL));
		ptr = hw1_x;
		for (int i = 0; i < HW1_N; i++)
			*ptr++ = ((double)rand() / (double)RAND_MAX) * 2;
	}
}
/*
void init_hw1(int fixed)
{
	float* ptr;
	hw1_x = (float*)malloc(sizeof(float) * HW1_N);

	if (fixed)
	{
		float tmp = HW1_N;
		for (int i = 0; i < HW1_N; i++)
		{
			if (i & 1) tmp -= 0.0001;
			hw1_x[i] = tmp;
		}
	}
	else
	{
		srand((unsigned)time(NULL));
		ptr = hw1_x;
		for (int i = 0; i < HW1_N; i++)
			*ptr++ = ((float)rand() / (float)RAND_MAX) * 2;
	}
}
*/
void hw1_calc_e()
{
	hw1_E = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_E += hw1_x[i];
	}
	hw1_E /= HW1_N;  
}

void hw1_calc_var1()
{
	hw1_var1 = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_var1 += pow(hw1_x[i]-hw1_E, 2);
	}
	hw1_var1 /= (HW1_N - 1);
}
void hw1_calc_var2()
{
	hw1_var2 = 0;
	double temp = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_var2 += pow(hw1_x[i], 2);
		temp += hw1_x[i];
	}
	hw1_var2 = (hw1_var2 - pow(temp, 2) / HW1_N) / (HW1_N - 1);
}

/* hw2 */
void hw2_naive()
{
	hw2_naive_ans[0] = (-hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c)) / (2 * hw2_a);
	hw2_naive_ans[1] = (-hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c)) / (2 * hw2_a);
}
void hw2_safe()
{
	if (hw2_b >= 0) {
		hw2_pre_ans[0] = (-2 * hw2_c) / (hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c));
		hw2_pre_ans[1] = (-1 * hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c)) / (2 * hw2_a);
	}
	else {
		hw2_pre_ans[0] = (-1 * hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c)) / (2 * hw2_a);
		hw2_pre_ans[1] = (-2 * hw2_c) / (hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c));
	}
}
float hw2_verify(float x)
{
	return hw2_a * x * x + hw2_b*x + hw2_c;
}

void h3_1() {
	puts("====== code motion ======");
	float x = 0.125;
	CHECK_TIME_START;
	hw3_1 = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw3_1 += hw1_x[i] + 2 * pow(x, 2) - 3 * x + 5;
	}
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw3_1-1 = %f ms\n", compute_time1);
	printf("hw3_1-1 value = %.15f\n", hw3_1);

	CHECK_TIME_START;
	hw3_1 = 0;
	float t = 2 * pow(x, 2) - 3 * x + 5;
	for (int i = 0; i < HW1_N; i++) {
		hw3_1 += hw1_x[i] + t;
	}
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw3_1-2 = %f ms\n", compute_time2);
	printf("hw3_1-2 value = %.15f\n", hw3_1);
	puts("");

}

#define max(a, b) ((a > b) ? a : b)
void h3_2() {
	puts("====== function inlining ======");
	CHECK_TIME_START;
	hw3_2 = 0;
	for (int i = 0; i < HW1_N - 1; i++) {
		hw3_2 = max(hw3_2, hw1_x[i]);
	}
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw3_2-1 = %f ms\n", compute_time1);
	printf("hw3_2-1 value = %.15f\n", hw3_2);

	CHECK_TIME_START;
	hw3_2 = 0;
	for (int i = 0; i < HW1_N - 1; i++) {
		if (hw3_2> hw1_x[i]) {
			hw3_2 = hw3_2;
		}
		else {
			hw3_2 = hw1_x[i];
		}
	}
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw3_2-2 = %f ms\n", compute_time2);
	printf("hw3_2-2 value = %.15f\n", hw3_2);
	puts("");

}
void h3_3() {
	puts("====== common subexpression elimination ======");
	int x = 2, y = 20;
	CHECK_TIME_START;
	hw3_3_a = 0;
	hw3_3_b = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw3_3_a += (pow(x, 2) / 3 * y) + hw1_x[i];
		hw3_3_b += (pow(x, 2) / 3 * y) * hw1_x[i];
	}
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw3_3-1 = %f ms\n", compute_time1);
	printf("hw3_3-1_a value = %.15f\n", hw3_3_a);
	printf("hw3_3-1_b value = %.15f\n", hw3_3_b);

	CHECK_TIME_START;
	hw3_3_a = 0;
	hw3_3_b = 0;
	float temp = pow(x, 2) / 3 * y;
	for (int i = 0; i < HW1_N; i++) {
		hw3_3_a += temp + hw1_x[i];
		hw3_3_b += temp * hw1_x[i];

	}
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw3_3-2 = %f ms\n", compute_time2);
	printf("hw3_3-2_a value = %.15f\n", hw3_3_a);
	printf("hw3_3-2_b value = %.15f\n", hw3_3_b);
	puts("");
}
void h3_4() {
	puts("====== reduction in strength ======");
	CHECK_TIME_START;
	hw3_4 = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw3_4 += pow(hw1_x[i], 2) + 2 * hw1_x[i];
	}
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw3_4-1 = %f ms\n", compute_time1);
	printf("hw3_4-1 value = %.15f\n", hw3_4);

	CHECK_TIME_START;
	hw3_4 = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw3_4 += hw1_x[i] * hw1_x[i] + hw1_x[i] + hw1_x[i];
	}
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw3_4-2 = %f ms\n", compute_time2);
	printf("hw3_4-2 value = %.15f\n", hw3_4);
	puts("");

}
void h3_5() {
	puts("====== constant propagation ======");
	CHECK_TIME_START;
	hw3_5 = 0;
	char num[9] = "100000";
	for (int i = 0; i < atoi(num); i++) {
		hw3_5 += hw1_x[i];
	}
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw3_5-1 = %f ms\n", compute_time1);
	printf("hw3_5-1 value = %.15f\n", hw3_5);

	CHECK_TIME_START;
	hw3_5 = 0;
	int number = 100000;
	for (int i = 0; i < number; i++) {
		hw3_5 += hw1_x[i];
	}
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw3_5-2 = %f ms\n", compute_time2);
	printf("hw3_5-2 value = %.15f\n", hw3_5);
	puts("");

}
