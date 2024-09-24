#include <iostream>
#include <Windows.h>
#include <math.h>
#define N 90000

int prog102() {
	bool flag = true;
	long long target;
	int result = 1;
	double targetSqrt;

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);

	// kokokara
	for(target=3;target<N;target+=2){
		targetSqrt = floor(sqrt(target));
		for (int i = 3; i <= targetSqrt; i++) {
			if (target % i == 0) {
				flag = false;
				break;
			}
		}
		if (flag) {
			result++;
		}
		flag = true;
	}
	printf("%d\n", result);
	// kokomade
	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	printf("used time = %lf \n", sec);
	return 0;

}