#include <iostream>
#include <math.h>
#include <Windows.h>
#include <math.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

long long Recursive_Sum2(int D[], int left, int right) {
	int mid = (left + right) / 2;
	if (left == right)return D[left];
	long long leftSum = Recursive_Sum2(D, left, mid);
	long long rightSum = Recursive_Sum2(D, mid + 1, right);
	return leftSum + rightSum;
}

long long Simple_Sum(int D[], int n) {
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		sum += D[i];
	}
	return sum;
}

int prog1001(void) {
	const int D_SIZE = 10 * 1000;
	int D[D_SIZE] = {};
	FILE* fpi;
	if (fopen_s(&fpi, "random_10k.txt", "r") != 0) {
		printf("Failed to open file\n");
		return 0;
	}
	for (int i = 0; i < D_SIZE && fscanf_s(fpi, "%d", &D[i]) != EOF; i++);
	fclose(fpi);
	long long sum;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);
	// koko
	sum = Simple_Sum(D, D_SIZE);
	// kokomade
	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	printf("%lf", sec);

	return 0;
}