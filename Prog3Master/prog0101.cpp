#include <iostream>
#include <Windows.h>
#include <math.h>

int prog101() {
	bool flag = true;
	long long target = 9007199254740997;
	double targetSqrt;

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);

	// kokokara
	targetSqrt = floor(sqrt(target));
	for (int i = 3; i < targetSqrt; i++) {
		if (target % i == 0) {
			flag = false;
			break;
		}
	}
	printf("result: %s\n", flag ? "true" : "false");
	// kokomade
	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	printf("used time = % lf \n", sec);
	return 0;

}