#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
void PrintD(int D[], int D_SIZE) {
	for (int i = 0; i < D_SIZE; i++) {
		printf("%2d ", D[i]);
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

void Merge(int D[], int M[], int left, int mid, int right) {
	int x = left, y = mid + 1;
	for (int i = 0; i <= right - left; i++) {
		if (x == mid + 1)M[i] = D[y++];
		else if (y == right + 1)M[i] = D[x++];
		else if (D[x] <= D[y])M[i] = D[x++];
		else M[i] = D[y++];
	}
	for (int i = 0; i <= right - left; i++)D[left + i] = M[i];
}

void MergeSort(int D[], int M[], int left, int right) {
	int mid = (left + right) / 2;
	if (left < mid)MergeSort(D, M, left, mid);
	if (mid + 1 < right)MergeSort(D, M, mid + 1, right);
	Merge(D, M, left, mid, right);
}

int main(void) {
	const int D_SIZE = 10 * 1000;
	int D[D_SIZE] = {};
	FILE* fpi;
	if (fopen_s(&fpi, "random_10k.txt", "r") != 0) {
		printf("Failed to open file\n");
		return 0;
	}
	for (int i = 0; i < D_SIZE && fscanf_s(fpi, "%d", &D[i]) != EOF; i++);
	fclose(fpi);
	int* M = (int*)malloc(sizeof(int) * D_SIZE);
	MergeSort(D, M, 0, D_SIZE - 1);
	PrintD(D, D_SIZE);
	printf("hash value = %d", hash_func(D, D_SIZE));
	free(M);
}

