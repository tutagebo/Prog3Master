#include <iostream>
#pragma warning(disable:4996)
#include <setjmp.h>
jmp_buf env;
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

void PrintA(int Y[], int n) {
	for (int i = 1; i <= n; i++) printf("%4d\t", Y[i]);
	printf("\n");
}
void ClearA(int M[], int n) {
	for (int i = 0; i <= n; i++) M[i] = 0;
}
void BB_subsetsum(int s, int level, int X[], int Y[], int n) {
	if (level > n) {		int sum = 0;		for (int i = 1; i <= n; i++) {			sum += Y[i] * X[i];		}		if (sum == s) {			for (int i = 1; i <= n; i++) {				printf("%4d\t", Y[i]);			}
			printf("\n");
			longjmp(env, 1);		}	}	else {		int sum1 = 0, sum2 = 0;		for (int i = 1; i <= n; i++) {			if (i < level) {				sum1 += Y[i] * X[i];				sum2 = sum1;			}			else {				sum2 += X[i];			}		}		if ((sum1 <= s) && (sum2 >= s)) {			Y[level] = 0;			BB_subsetsum(s, level + 1, X, Y, n);			Y[level] = 1;			BB_subsetsum(s, level + 1, X, Y, n);		}	}	if (level == 1)printf("sÇ…ìôÇµÇ¢ëIÇ—ï˚Ç™ë∂ç›ÇµÇ»Ç¢\n");}int prog1401() {
	int X[] = { 0, 1, 12, 4, 8, 9, 11, 13, 17, 7, 21, 15, 2, 23,
	6, 31, 10, 3, 18, 19, 5 }; // X[0] is not used.
	int sum = 223;
	int n = COUNTOF(X) - 1;
	//int Y[n + 1]; // VAL
	int* Y = (int*)malloc(sizeof(int) * (n + 1));
	ClearA(Y, n);
	PrintA(X, n);
	if (!setjmp(env)) BB_subsetsum(sum, 1, X, Y, n);
	return 0;
}