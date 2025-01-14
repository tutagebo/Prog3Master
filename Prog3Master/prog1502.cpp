#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#define PRINTG(GRAPH) \
do {\
		printf(#GRAPH "\n"); \
		PringGraph((float*)GRAPH, sizeof(GRAPH) / sizeof(GRAPH[0]), \
			sizeof(GRAPH[0]) / sizeof(GRAPH[0][0])); \
} while (0);

void PringGraph(float g[], int row, int column) {
	for (int i = 1; i < row; i++) {
		printf("%d ", i);
		for (int j = 1; j < column; j++)
			if (g[i * column + j] != 0)
				printf("-> [%.1f]%d", g[i * column + j], j);
		printf("\n");
	}
	printf("---\n");
}

#define NODE 11
float G[][NODE] = {
	// 0 1 2 3 4 5 6 7 8 9 10
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //0
	 { 0, 0,33, 0, 0, 9, 0, 0,12, 0, 0 }, //1
	 { 0,33, 0,21, 7, 0, 0,16, 0, 0,13 }, //2
	 { 0, 0,21, 0,13,25, 0, 0,14,11, 0 }, //3
	 { 0, 0, 7,13, 0, 0, 5, 0, 0, 0, 0 }, //4
	 { 0, 9, 0,25, 0, 0,16,22, 0,18, 0 }, //5
	 { 0, 0, 0, 0, 5,16, 0,17,20, 0,27 }, //6
	 { 0, 0,16, 0, 0,22,17, 0, 0, 0, 0 }, //7
	 { 0,12, 0,14, 0, 0,20, 0, 0, 0,21 }, //8
	 { 0, 0, 0,11, 0,18, 0, 0, 0, 0, 0 }, //9
	 { 0, 0,13, 0, 0, 0,27, 0,21, 0, 0 }, //10
};

float D[NODE];
void SetINFINITY_D() {
	for (int i = 1; i < NODE; i++) D[i] = INFINITY;
}
int S[NODE];
void SetEmpty_S() {
	for (int i = 1; i < NODE; i++) S[i] = 0;
}
void AddSET_S(int s) {
	S[s] = 1;
}

void PrintSD() {
	for (int i = 1; i < NODE; i++) printf("%4d\t", i);
	printf("\n");
	for (int i = 1; i < NODE; i++) printf("%4d\t", S[i]);
	printf("\n");
	for (int i = 1; i < NODE; i++) printf("%4.1f\t", D[i]);
	printf("\n---\n");
}

int FindMinVk() {
	int k = 0;
	float minDist = INFINITY;
	for (int i = 1; i < NODE; i++) {
		if (!S[i] && D[i] < minDist) {
			minDist = D[i];
			k = i;
		}
	}
	return k;
}
// Algorithm 10.3
void Dijkstra103(float G[][NODE], int s) {
	SetINFINITY_D();
	SetEmpty_S();
	D[s] = 0;
	for (int i = 1; i < NODE; i++) {
		int u = FindMinVk();
		if (u == -1) break;
		AddSET_S(u);
		for (int v = 1; v < NODE; v++) {
			if (G[u][v] != 0 && !S[v]) {
				if (D[u] + G[u][v] < D[v]) {
					D[v] = D[u] + G[u][v];
				}
			}
		}
		PrintSD();
	}
}

int main() {
	PRINTG(G);
	Dijkstra103(G, 7);
	PrintSD();
	return 0;
}

