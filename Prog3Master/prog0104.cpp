#include <iostream>
#include <Windows.h>
#include <math.h>

int prog104() {


	// kokokara
	for (int N = 1000; N <= 10000; N += 1000) {
		long long result = 0;
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER start, end;
		QueryPerformanceCounter(&start);
		for (int i = 1; i <= N; i++) {
			result += (long long)(2 * (long long)i + ((long long)(N - 1) * (long long)i * (long long)N)) / 2;
		}
		printf("%d result: %lld\n", N, result);
		// kokomade
		QueryPerformanceCounter(&end);
		LONGLONG span = end.QuadPart - start.QuadPart;
		double sec = (double)span / (double)frequency.QuadPart;
		printf("used time = % lf \n", sec);
	}
	return 0;
}