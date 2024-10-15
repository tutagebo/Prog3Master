#include <iostream>
#include <Windows.h>
#define N 100000

long long int fibo(long long int n);
long long int fiboFor(long long int n);

int prog403() {
	for (int i = 0; i<N; i++) {
		long long int res;
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER start, end;
		QueryPerformanceCounter(&start);
		// kokokara
		/*long long int an[N] = {};
		an[0] = 1, an[1] = 1;
		int j;
		for (j = 0; j < i; j++) {
			if (j < 2)continue;
			an[j] = an[j - 1] + an[j - 2];
		}
		res = an[j-1];*/
		res = fiboFor(i);
		// kokomade
		QueryPerformanceCounter(&end);
		LONGLONG span = end.QuadPart - start.QuadPart;
		long double sec = (double)span / (double)frequency.QuadPart;
		printf("%lld: %lf\n", res, sec);
	}
	return 0;
}

long long int fibo(long long int n) {
	if (n < 2)return 1;
	else return fibo(n - 1) + fibo(n - 2);
}

long long int fiboFor(long long int n) {
	long long int an[N] = {};
	an[0] = 1, an[1] = 1;
	int j;
	for (j = 0; j < n; j++) {
		if (j < 2)continue;
		an[j] = an[j - 1] + an[j - 2];
	}
	return an[j-1];
}