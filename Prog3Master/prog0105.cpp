#include <iostream>
#include <Windows.h>
#include <math.h>

int prog105() {
	for (int N = 1000; N <= 10000; N += 1000) {
		long long result;
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER start, end;
		QueryPerformanceCounter(&start);

		// kokokara
		result = 0;
		int tmp = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j < i; j++) {
				tmp += i * j;
			}
			result += tmp * 2;
			tmp = 0;
			result += i * i;
		}
		//printf("result: %lld\n", result);

		// kokomade
		QueryPerformanceCounter(&end);
		LONGLONG span = end.QuadPart - start.QuadPart;
		double sec = (double)span / (double)frequency.QuadPart;
		printf("%lf\n", sec);
	}
	return 0;
}