#include <iostream>
#include <Windows.h>
#include <math.h>
#define a 3

int pow1(long n);
int pow2(long n);

int prog402() {
	long long int n = 1;
	for (int i = 1; i < 6; i++) {
		n *= 2;
		//printf("%lld\n", pow1(n));
		//
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER start, end;
		QueryPerformanceCounter(&start);
		// kokokara
		for (int j = 0; j < 100000; j++) {
			pow2(n);
		}
		// kokomade
		QueryPerformanceCounter(&end);
		LONGLONG span = end.QuadPart - start.QuadPart;
		long double sec = (double)span / (double)frequency.QuadPart;
		printf("%16.14lf \n", sec/100000);
	}
	//printf("pow2: %d\n", pow2(2));
	return 0;
}

int pow1(long n) {
	if (n == 1)return a;
	else return pow1(n / 2) * pow1(n / 2);
}

int pow2(long n) {
	if (n == 1)return a;
	else {
		int p = pow2(n / 2);
		return p * p;
	}
}
