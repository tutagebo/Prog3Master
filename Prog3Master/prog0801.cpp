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
		for (int n = 0; buff[n] != '¥0'; n++) {
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

// PushHeap Algorithm 5.3
void PushHeap(int T[], int* size, int x) {
	*size = *size + 1;
	T[*size] = x;
	int k = *size;
	while (T[k] > T[k / 2]) {
		swap(&T[k], &T[k / 2]);
		k /= 2;
	}
}

// DeleteMaxinum Algorithm 5.2
int DeleteMaxinum(int T[], int* size) {
	int max, k, big;
	max = T[1];
	T[1] = T[*size];
	T[*size] = 0;
	*size = *size - 1;
	k = 1;
	while (2 * k <= *size) {
		if(!T[k*2]||!T[k*2+1]) {
			if (T[k] < T[k * 2])swap(&T[k], &T[k * 2]);
			else break;
		}
		else {
			big = (T[k * 2] > T[k * 2 + 1]) ? k * 2 : k * 2 + 1;
			if (T[k] < T[big])swap(&T[k], &T[big]);
			else break;
		}
	}
	return max;
}

int prog801(void) {
	FILE* fpi;
	const int D_SIZE = 100000;
	int D[100000] = {};
	if (fopen_s(&fpi, "random_100k.txt", "r") != 0) {
		printf("Failed to open file\n");
		return 0;
	}
	for (int i = 0; fscanf_s(fpi, "%d", &D[i]) != EOF; i++);
	for (int x : D) {
		printf("%d\n", x);
	}
	//タイマースタート
	//配列Tの初期化
	int* T = (int*)malloc((D_SIZE + 1) * sizeof(int));
	if (T != NULL) {
		for (int i = 0; i <= D_SIZE; i++) {
			T[i] = 0;
		}
	}
	int size = 0;
	for (int i = 0; i < D_SIZE; i++) {
		PushHeap(T, &size, D[i]);
	}
	for (int i = D_SIZE - 1; i >= 0; i = i - 1) {
		D[i] = DeleteMaxinum(T, &size);
	}
	//タイマー終了 計算時間出力
	//ソート後の配列に対するハッシュ値
	printf("hash value = %d", hash_func(D, D_SIZE));
	free(T);
	free(D);
}
