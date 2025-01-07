#include <iostream>
#include <Windows.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define N_PAINTING 25 // Number of Painting
#define CheckA (w > c)
#define CheckB (w == c)
#define CheckC (v + (c - w) * Vmax(level) < z)

typedef struct {
	int Id;
	char Name[100];
	int w;
	int p;
	int v;
} PTable;
// global variable.
PTable T91[N_PAINTING + 1];
const int n = N_PAINTING;
int X[N_PAINTING + 1];
int ZX[N_PAINTING + 1];
int z;
int c;
int ReadPTable() {
	FILE* fp;
	const char* fname = "paint_25types.csv";
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("Not open %s\n", fname);
		exit(EXIT_FAILURE);
	}
	int i = 1;
	while ((fscanf(fp, "%d,%[^,],%d,%d", &(T91[i].Id),
		T91[i].Name, &(T91[i].w),
		&(T91[i].p))) != EOF) {
		T91[i].v = T91[i].p / T91[i].w;
		i = i + 1;
	}
	fclose(fp);
	return i - 1;
}
void PrintPTable() {
	for (int i = 1; i <= n; i++)
		printf("(%d) P-%d, %2s, %2d[kg], %2d[YEN],%2d[YEN/Kg]\n", i,
			T91[i].Id, T91[i].Name, T91[i].w, T91[i].p, T91[i].v);
	printf("\n");
}
void ClearX(int X[]) {
	for (int i = 0; i <= n; i++) X[i] = 0;
}
int SumW(int X[]) {
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += T91[i].w * X[i];
	return sum;
}
int SumP(int X[]) {
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += T91[i].p * X[i];
	return sum;
}
int Vmax(int level) {
	int Vmax = 0;
	for (int i = level; i <= n; i++) {
		if (T91[i].v > Vmax) Vmax = T91[i].v;
	}
	return Vmax;
}

void BB_01knapsack(int level) {
	int w = SumW(X);
	int v = SumP(X);
	if (level > n) {
		if ((w <= c) && (v > z)) {
			z = v;
			for (int i = 1; i <= N_PAINTING; i++) {
				ZX[i] = X[i];
			}
		}
	}
	else {
		if (!CheckA) {
			if (CheckB) {
				if (v > z) {
					z = v;
					for (int i = 1; i <= N_PAINTING; i++) {
						ZX[i] = X[i];
					}
				}
			}
			else if (!CheckC) {
				X[level] = 1;
				BB_01knapsack(level + 1);
				X[level] = 0;
				BB_01knapsack(level + 1);
			}
		}
	}/*
	for (int i = 1; i <= N_PAINTING; i++) {
		printf("%d\t", ZX[i]);
	}
	printf("\n");*/
}
int main(int argc, const char* argv[]) {
	// int X[N_PAINTING + 1];
	if (ReadPTable() != n) {
		printf("Error\n");
		exit(0);
	}
	PrintPTable();
	ClearX(X); ClearX(ZX);
	z = 0; c = 125;

	long long sum;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);
	//koko
	BB_01knapsack(1);
	//kokomade
	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	printf("%lf", sec);

	int sump = 0, sumw = 0;
	for (int i = 1; i <= n; i++) {
		sump += ZX[i] * T91[i].p;
		sumw += ZX[i] * T91[i].w;
	}
	printf("\n");
	for (int i = 1; i <= n; i++) printf("%d", ZX[i]);
	printf("\tPrice=%d\tWeight=%d\n", sump, sumw);
	return 0;
}
