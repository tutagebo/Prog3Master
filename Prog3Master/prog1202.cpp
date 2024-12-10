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
	const char* fname = "coffee_4types.csv";
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

void GenerateZ(int Z[], int size) {
	for (int i = 1; i <= (1 << size); i++) {
		for (int j = 1; j < size + 1; j++) {
			Z[i * (size + 1) + j] = (i - 1) >> (j - 1) & 1;
		}
	}
}

void PrintZ(int Z[], int size) {
	for (int i = 1; i <= (1 << size); i++) {
		for (int j = 1; j < size + 1; j++) {
			printf("%d ", Z[i * (size + 1) + j]);
		}
		printf("\n");
	}
}

int Knapsack(int C, Table T[], int X[], int Z[], int size) {
	GenerateZ(Z, size);
	int vmax = 0;
	for (int i = 1; i <= (1 << size); i++) {
		int wsum = 0, vsum = 0;
		for (int j = 1; j < size; j++) {
			wsum += Z[i * (size + 1) + j] * T[j].w;
			vsum += Z[i * (size + 1) + j] * T[j].v;
		}
		if ((wsum <= C) && (vsum > vmax)) {
			vmax = vsum;
			for (int j = 1; j <= size; j++) {
				X[j] = Z[i * (size + 1) + j];
			}
		}
	}
	return vmax;
}

#define NUMTYPE 4
#define CAPACITY 5
int main(void) {
	Table T81[NUMTYPE + 1];
	int X[NUMTYPE + 1]; // X[0] is NOT used.
	int Z[((1 << NUMTYPE) + 1) * (NUMTYPE + 1)];
	int size = ReadTable(T81);
	PrintTable(T81, size);
	int vmax = Knapsack(CAPACITY, T81, X, Z, size);
	PrintZ(Z, size);
	for (int i = 1; i <= size; i++)
		printf("%d %lf %d\n", T81[i].Id, T81[i].z, X[i]);
	printf("\n");
	printf("vmax = %d", vmax);
	return 0;
}

