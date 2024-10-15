#include <iostream>
#include <math.h>
#define delta 1.0e-15

double newton(double x, int count);

int prog401(){
	double root = newton(10.0, 0);
	printf("result: %16.14lf\n", root);
	return 0;
}

double newton(double x, int round) {
	if (round >= 20) {
		printf("ŒvZ‚ğI—¹‚µ‚Ü‚µ‚½B");
		return 0;
	}
	double xn = x - (x * x - 3) / (2 * x);
	printf("%18.17lf\n", xn);
	if (fabs(xn - x) < delta)return xn;
	return newton(xn, ++round);
}