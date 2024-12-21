#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define N_COFFEE 25 // Number of coffee types
#define W 125 // Weight
typedef struct {
	int Id;
	char Name[100];
	int w;
	int v;
	float z;
} CofeeTable;
typedef struct {
	int v;
	int x[N_COFFEE + 1]; // X[0] is NOT used.
} Table;
void ClearTable(Table T[][W + 1]) {
	for (int i = 0; i <= N_COFFEE; i++) {
		for (int j = 0; j <= W; j++) {
			T[i][j].v = 0;
			for (int k = 0; k <= N_COFFEE; k++)
				T[i][j].x[k] = 0;
		}
	}
}
void PrintTable(Table T[][W + 1]) {
	for (int i = 1; i <= N_COFFEE; i++) {
		for (int j = 1; j <= W; j++) {
			printf("\nT[%d][%d].v=%d\t", i, j, T[i][j].v);
			for (int k = 1; k <= N_COFFEE; k++)
				printf("%d,", T[i][j].x[k]);
		}
		printf("\n");
	}
}
int ReadTable(CofeeTable T[]) {
	FILE* fp;
	const char* fname = "coffee_20types.csv";
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("Not open %s\n", fname);
		exit(EXIT_FAILURE);
	}
	int i = 1;
	while ((fscanf(fp, "%d,%[^,],%d,%d", &(T[i].Id), T[i].Name,
		&(T[i].w), &(T[i].v))) != EOF)
		i = i + 1;
	fclose(fp);
	return i - 1;
}
void PrintCoffeeTable(CofeeTable T[], int size) {
	for (int i = 1; i <= size; i++)
		printf("(%d) beans-%d, %-12s, %d[kg], %d[YEN]\n", i,
			T[i].Id, T[i].Name, T[i].w, T[i].v);
	printf("\n");
}

void Knapsack_DP(CofeeTable T81[], Table T[][W + 1]) {
	for (int j = T81[1].w; j <= W; j++) {
		T[1][j].v = T81[1].v;
		T[1][j].x[1] = 1;
	}
	for (int i = 2; i <= N_COFFEE; i++) {
		for (int j = 1; j <= W; j++) {
			if (j >= T81[i].w) {
				int v1 = T[i - 1][j - T81[i].w].v;
				int* s1 = T[i - 1][j - T81[i].w].x;
				int v2 = T[i - 1][j].v;
				int* s2 = T[i - 1][j].x;
				if (v1 + T81[i].v > v2) {
					int tmp[N_COFFEE + 1] = { 0 }, t;
					for (t = 1; t < N_COFFEE; t++) {
						if (s1[t] == 0)break;
						tmp[t] = s1[t];
					}
					tmp[t] = i;
					memcpy(T[i][j].x, tmp, sizeof(tmp));
					T[i][j].v = v1 + T81[i].v;
				}
				else {
					T[i][j] = T[i - 1][j];
				}
			}
			else {
				T[i][j] = T[i - 1][j];
			}
		}
	}
}

int main(void) {
	CofeeTable T81[N_COFFEE + 1];
	int size = ReadTable(T81);
	PrintCoffeeTable(T81, size);
	Table T[N_COFFEE + 1][W + 1];
	ClearTable(T);
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);
	//koko
	Knapsack_DP(T81, T);
	//koko
	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	PrintTable(T);
	printf("sec: %lf", sec);
	return 0;
}
