#include <iostream>
#include <stdlib.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
typedef struct {
	int Id;
	char Name[100];
	int w;
	int v;
	float z;
} Table;
void Sort(Table T[], int size) {
	Table tmp;
	for (int i = 1; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (T[j + 1].z > T[j].z) {
				tmp = T[j];
				T[j] = T[j + 1];
				T[j + 1] = tmp;
			}
		}
	}
}
int ReadTable(Table Table[]) {
	FILE* fp;
	const char* fname = "coffee_10types.csv";
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("Not open %s\n", fname);
		exit(EXIT_FAILURE);
	}
	int i = 1;
	while ((fscanf(fp, "%d,%[^,],%d,%d", &(Table[i].Id),
		Table[i].Name, &(Table[i].w), &(Table[i].v))) != EOF) {
		Table[i].z = (float)Table[i].v / (float)Table[i].w;
		i = i + 1;
	}
	fclose(fp);
	return i - 1;
}

void PrintTable(Table T[], int size) {
	for (int i = 1; i <= size; i++)
		printf("(%d) beans-%d, %-12s, % d[kg], % d[YEN], % 7.2f[YEN / Kg]\n",
			i, T[i].Id, T[i].Name, T[i].w, T[i].v, T[i].z);
	printf("\n");
}
// Algorithm 8.1
void GreedyKnapsack(int C, float X[], Table T[], int size) {
	Sort(T, size);
	float sum = 0;
	for (int i = 1; i < size + 1; i++) {
		if (sum > C) {
			X[i] = 0;
		}
		else if (sum + T[i].w > C) {
			X[i] = (C - sum) / T[i].w;
			sum += T[i].w;
		}
		else {
			X[i] = 1.0;
			sum += T[i].w;
		}
	}
	return;
}

#define NUMTYPE 10
#define CAPACITY 40
int prog1201(int argc, const char* argv[]) {
	Table T81[NUMTYPE + 1];// T81[0] is NOT used.
	float X[NUMTYPE + 1];
	int size = ReadTable(T81);
	PrintTable(T81, size);
	GreedyKnapsack(CAPACITY, X, T81, size);
	PrintTable(T81, size);
	double psum = 0;
	for (int i = 1; i <= size; i++) {
		printf("%s %lf %lf \n", T81[i].Name, T81[i].z, X[i]);
		psum += T81[i].v * X[i];
	}
	printf("price: %lf", psum);
	return 0;
}
