#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

long long Bproduct(int X[], int Y[], int n) {
	int sum = 0, power = 1;
	for (int i = 0; i < n; i++) {
		int s = 0, p = power;
		for (int j = 0; j < n; j++) {
			s += p * X[i] * Y[j];
			p *= 10;
		}
		sum += s;
		power *= 10;
	}
	return sum;
}

long long Product(int X[], int Y[], int n) {
	if (n == 1) return X[0] * Y[0];
	int h = n / 2;
	int* X1 = (int*)malloc(sizeof(int) * h); int* Y1 = (int*)malloc(sizeof(int) * h);
	int* X2 = (int*)malloc(sizeof(int) * h); int* Y2 = (int*)malloc(sizeof(int) * h);
	int* X12 = (int*)malloc(sizeof(int) * h); int* Y12 = (int*)malloc(sizeof(int) * h);
	for (int i = 0; i < h; i++) {
		X12[i] = X[i] + X[h + i]; Y12[i] = Y[i] + Y[h + i];
		X2[i] = X[h + i]; Y2[i] = Y[h + i];
		X1[i] = X[i]; Y1[i] = Y[i];
	}
	long long c = Product(X1, Y1, h);
	long long b = Product(X12, Y12, h);
	long long a = Product(X2, Y2, h);
	free(X12); free(Y12); free(X2);
	free(Y2); free(X1); free(Y1);
	return a * pow(10, n) + (b - (a + c)) * pow(10, n / 2) + c;
}


int main(int argc, const char* argv[]) {
	int X[] = { 7 };
	int Y[] = { 9 };
	int size = COUNTOF(X);
	if ((size & (size - 1))) {
		printf("Size is not a power of 2. ¥n");
		exit(0);
	}
	int repeat = 10000000;
	long long prod;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);
	for (int i = 0; i < repeat; i++) {
		prod = Bproduct(X, Y, size);
	}
	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	printf("sec = %lf", sec);
	return 0;
}