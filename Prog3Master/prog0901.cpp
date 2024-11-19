#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

typedef struct record {
	char city[50];
	char country[50];
	double data[20];
}record;

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
void swap(record* a, record* b) {
	record temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}


int Partition(record D[], int left, int right, int target) {
	int k = (left + right) / 2;
	swap(&D[k], &D[right]);
	int i = left;
	int j = right - 1;
	while (i <= j) {
		while (D[i].data[target] < D[right].data[target])i++;
		while (D[j].data[target] >= D[right].data[target] && j >= i)j--;
		if (i < j)swap(&D[i], &D[j]);
	}
	swap(&D[i], &D[right]);
	return i;
}

int QuickSort(record D[], int left, int right, int target) {
	if (left < right) {
		int pivot_index = Partition(D, left, right, target);
		QuickSort(D, left, pivot_index - 1, target);
		QuickSort(D, pivot_index + 1, right, target);
	}
	return 0;
}

int main(void) {
	FILE* fpi;
	fopen_s(&fpi, "city_population.txt", "r");
	if (fpi == NULL) {
		printf("読み込みエラーです。¥n");
		return -1;
	}
	int D_SIZE = 1692;
	int target = 9;
	record* D = (record*)(malloc(sizeof(record) * D_SIZE));
	if (D == NULL) {
		exit(1);
	}
	for (int i = 0; fscanf_s(fpi, "%s", &D[i].city, (unsigned int)sizeof(D[i].city)) != EOF; i++) {
		fscanf_s(fpi, "%s", &D[i].country, (unsigned int)sizeof(D[i].country));
		fscanf_s(fpi, "%lf", &D[i].data[0]);
		fscanf_s(fpi, "%lf", &D[i].data[1]);
		fscanf_s(fpi, "%lf", &D[i].data[2]);
		fscanf_s(fpi, "%lf", &D[i].data[3]);
		fscanf_s(fpi, "%lf", &D[i].data[4]);
		fscanf_s(fpi, "%lf", &D[i].data[5]);
		fscanf_s(fpi, "%lf", &D[i].data[6]);
		fscanf_s(fpi, "%lf", &D[i].data[7]);
		fscanf_s(fpi, "%lf", &D[i].data[8]);
		D[i].data[9] = D[i].data[7] / D[i].data[5];
	}
	QuickSort(D, 0, D_SIZE - 1, target);
	for (int i = 0; i < D_SIZE; i++) {
		printf("%s %s: %lf\n", D[i].city, D[i].country, D[i].data[target]);
	}
	free(D);
	return 0;
}
