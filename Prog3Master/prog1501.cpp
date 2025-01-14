#include <stdio.h>
#define STACKSIZE 100
#define NODE 11 // 0--10
#define PRINTG(GRAPH)\
do {\
	printf(#GRAPH "\n"); \
	PrintGraph((int*)GRAPH, sizeof(GRAPH) / sizeof(GRAPH[0]), \
				sizeof(GRAPH[0]) / sizeof(GRAPH[0][0])); \
} while (0);

void PrintGraph(int g[], int row, int column) {
	for (int i = 1; i < row; i++) {
		printf("%d ", i);
		for (int j = 1; j < column; j++)
			if (g[i * column + j] != 0) printf("-> %d", j);
		printf("\n");
	}
	printf("---\n");
}

int stack[STACKSIZE], top;
void InitStack() {
	top = 0;
}
void Push(int x) {
	stack[top++] = x;
}
int Pop() {
	return stack[--top];
}
void PrintStack() {
	printf("\nStack:");
	for (int i = 0; i < top; i++) printf("%d ", stack[i]);
	printf("\n");
}
int EmptyStack() {
	return !(top);
}

int queue[STACKSIZE], head, tail;
void InitQueue() {
	head = tail = 0;
}
void Enqueue(int x) {
	queue[tail++] = x;
}
int Dequeue() {
	return queue[head++];
}
int EmptyQueue() {
	return head == tail;
}
void PrintQueue() {
	printf("\nQueue:");
	for (int i = head; i < tail; i++) printf("%d ", queue[i]);
	printf("\n");
}

int G[][NODE] = {
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

int C[NODE];
int InQ[NODE];

// •—Dæ’Tõ (BFS)
void BFS101(int G[][NODE], int s) {
	for (int i = 1; i < NODE; i++) C[i] = InQ[i] = 0;
	InitQueue();
	Enqueue(s); InQ[s] = 1;
	while (!EmptyQueue()) {
		int v = Dequeue();
		printf("¨%d", v);
		for (int k = 1; k < NODE; k++) {
			if (G[v][k] != 0 && !InQ[k]) {
				Enqueue(k);
				InQ[k] = 1;
			}
		}
	}
}

// [‚³—Dæ’Tõ (DFS)
void DFS102(int G[][NODE], int s) {
	for (int i = 1; i < NODE; i++) C[i] = 0;
	InitStack();
	Push(s);
	while (!EmptyStack()) {
		int v = Pop();
		if (!C[v]) {
			C[v] = 1;
			printf("¨%d", v);
			for (int k = NODE - 1; k >= 1; k--) {
				if (G[v][k] != 0 && !C[k]) {
					Push(k);
				}
			}
		}
	}
}

int prog1501() {
	PRINTG(G);
	printf("BFS:\n");
	BFS101(G, 7);
	printf("DFS:\n");
	DFS102(G, 7);
	return 0;
}
