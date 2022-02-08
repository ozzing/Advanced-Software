#define _USE_MATH_DEFINES
#include <math.h>


double _f1(double x) {
	return pow(x, 2) - 4 * x + 4.0 - log(x);
}

double _fp1(double x) {
	return 2 * x - 4.0 - (1 / x);
}

double _f2(double x) {
	return x + 1 - 2 * sin(M_PI * x);
}

double _fp2(double x) {
	return 1 - 2 * M_PI * cos(M_PI * x);
}

double _f3(double x) {
	return pow(x, 4) - 11.0 * pow(x, 3) + 42.35 * pow(x, 2) - 66.55 * x + 35.1384;
}

double _fp3(double x) {
	return 4 * pow(x, 3) - 33 * pow(x, 2) + 84.7 * x - 66.55;
}

double _f_sqrt(double x) {
	return x * x - 2.0;
}

double _fp_sqrt(double x) {
	return 2.0 * x;
}

double _f_vehicle(double x) {
	double rad = 11.5 * M_PI / 180;
	x = x * M_PI / 180;
	double A = 89 * sin(rad);
	double B = 89 * cos(rad);
	double C = ((49 + (0.5 * 55)) * sin(rad)) - (0.5 * 55 * tan(rad));
	double E = ((49 + (0.5 * 55)) * cos(rad)) - (0.5 * 55);
	return (A * sin(x) * cos(x)) + (B * pow(sin(x),2)) - (C * cos(x)) - (E * sin(x));
}

double _fp_vehicle(double x) {
	double rad = 11.5 * M_PI / 180;
	x = x * M_PI / 180;
	double A = 89 * sin(rad);
	double B = 89 * cos(rad);
	double C = ((49 + (0.5 * 55)) * sin(rad)) - (0.5 * 55 * tan(rad));
	double E = ((49 + (0.5 * 55)) * cos(rad)) - (0.5 * 55);
	return (A * (pow(cos(x),2) - pow(sin(x), 2)))+ (B * (2 * cos(x) * sin(x))) - (C * -sin(x)) - (E * cos(x));
}

double _f_comp(double x) {
	return log(x) - 1;
}

double _fp_comp(double x) {
	return (1/x);
}
