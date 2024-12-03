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

void Merge(record D[], record M[], int left, int mid, int right, int target) {
	int x = left, y = mid + 1;
	for (int i = 0; i <= right - left; i++) {
		if (x == mid + 1)M[i] = D[y++];
		else if (y == right + 1)M[i] = D[x++];
		else if (D[x].data[target] <= D[y].data[target])M[i] = D[x++];
		else M[i] = D[y++];
	}
	for (int i = 0; i <= right - left; i++)D[left + i] = M[i];
}

void MergeSort(record D[], record M[], int left, int right, int target) {
	int mid = (left + right) / 2;
	if (left < mid)MergeSort(D, M, left, mid, target);
	if (mid + 1 < right)MergeSort(D, M, mid + 1, right, target);
	Merge(D, M, left, mid, right, target);
}

int main(void) {
	FILE* fpi;
	fopen_s(&fpi, "city_population.txt", "r");
	if (fpi == NULL) {
		printf("error of reading file.\n");
		return -1;
	}
	int D_SIZE = 1692;
	int target = 5;
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
		double sum = 0;
		for (int j = 0; j < 9; j++)sum += D[i].data[j];
		D[i].data[9] = sum / 9;
	}
	record* M = (record*)malloc(sizeof(record) * D_SIZE);
	MergeSort(D, M, 0, D_SIZE - 1, target);
	for (int i = 101; i < 111; i++) {
		printf("%s %s: %lf\n", D[i].city, D[i].country, D[i].data[target]);
	}
	free(M);
}

