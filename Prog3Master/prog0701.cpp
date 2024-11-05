#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

void PrintD(int D[], int D_SIZE, FILE* fp) {
	for (int i = 0; i < D_SIZE; i++) {
		fprintf(fp, "%2d ", D[i]);
	}
	printf("\n");
}
int hash_func(int D[], int D_SIZE) {
	char buff[12];
	unsigned int value = 1;
	for (int i = 0; i < D_SIZE; i++) {
		sprintf(buff, "%d", D[i]);
		for (int n = 0; buff[n] != '\0'; n++) {
			int temp = (buff[n] * (i + 77)) % 6700417 + 1;
			value = ((value)*temp) % 6700417;
		}
	}
	return value;
}
void swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void SelectionSort(int D[], int D_SIZE) {
	for (int i = D_SIZE - 1; i > 0; i--) {
		int index = 0, min = D[index];
		for (int j = 1; j <= i; j++) {
			if (D[j] <= min) {
				index = j;
				min = D[index];
			}
		}
		swap(&D[index], &D[i]);
	}
	return;
}

void InsertionSort(int D[], int D_SIZE) {
	for (int i = 1; i < D_SIZE; i++) {
		int x = D[i], j = i;
		while (D[j - 1] > x && j > 0) {
			D[j] = D[j - 1];
			j--;
		}
		D[j] = x;
	}
	return;
}

int main() {
	const int D_SIZE = 200000;
	int* D = (int*)malloc(sizeof(int) * D_SIZE);
	FILE* fpi;
	if (fopen_s(&fpi, "random_200k.txt", "r") != 0) {
		printf("Failed to open file\n");
		return 0;
	}
	for (int i = 0; fscanf_s(fpi, "%d", &D[i]) != EOF; i++);
	fclose(fpi);
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);
	// koko
	SelectionSort(D, D_SIZE);
	// kokomade
	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	printf("%lf", sec);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	// koko
	InsertionSort(D, D_SIZE);
	// kokomade
	QueryPerformanceCounter(&end);
	span = end.QuadPart - start.QuadPart;
	sec = (double)span / (double)frequency.QuadPart;
	printf(":%lf", sec);


	if (fopen_s(&fpi, "sort_200k.txt", "r") != 0) {
		printf("Failed to open file\n");
		return 0;
	}
	for (int i = 0; fscanf_s(fpi, "%d", &D[i]) != EOF; i++);
	fclose(fpi);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	// koko
	SelectionSort(D, D_SIZE);
	// kokomade
	QueryPerformanceCounter(&end);
	span = end.QuadPart - start.QuadPart;
	sec = (double)span / (double)frequency.QuadPart;
	printf(":%lf", sec);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	// koko
	InsertionSort(D, D_SIZE);
	// kokomade
	QueryPerformanceCounter(&end);
	span = end.QuadPart - start.QuadPart;
	sec = (double)span / (double)frequency.QuadPart;
	printf(":%lf", sec);

	if (fopen_s(&fpi, "rsort_200k.txt", "r") != 0) {
		printf("Failed to open file\n");
		return 0;
	}
	for (int i = 0; fscanf_s(fpi, "%d", &D[i]) != EOF; i++);
	fclose(fpi);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	// koko
	SelectionSort(D, D_SIZE);
	// kokomade
	QueryPerformanceCounter(&end);
	span = end.QuadPart - start.QuadPart;
	sec = (double)span / (double)frequency.QuadPart;
	printf(":%lf", sec);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	// koko
	InsertionSort(D, D_SIZE);
	// kokomade
	QueryPerformanceCounter(&end);
	span = end.QuadPart - start.QuadPart;
	sec = (double)span / (double)frequency.QuadPart;
	printf(":%lf", sec);
	free(D);
	return 0;
}
