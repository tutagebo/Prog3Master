#include <iostream>
#include <stdlib.h>
#pragma warning(disable:4996)
#define N 50

//ノードの構造体
typedef struct node {
	int id;
	int score;
	node* left;
	node* right;
} node;
//木をたどって値を昇順に出力する
void print_value(FILE* fpw, node* now) {
	if (now == NULL) return;
	print_value(fpw, now->left);
	printf("%d\n", now->score);
	print_value(fpw, now->right);
	return;
}
//木をたどってメモリを解放
void finish(node* p1) {
	if (p1 == NULL) {
		return;
	}
	finish(p1->left);
	finish(p1->right);
	free(p1);
}
//木を描く関数
void draw_tree(FILE* fpt, node* p1, float x, float y, float width) {
	if (p1 == NULL) return;
	int score = p1->score;
	fprintf(fpt, "%8.5f, %8.5f, %d \n", x, -y, score);
	width /= 2;
	draw_tree(fpt, p1->left, x-width, y+1, width);
	fprintf(fpt, "%8.5f, %8.5f, %d \n", x, -y, score);
	width *= 2;
	draw_tree(fpt, p1->right, x+width, y+1, width);
	fprintf(fpt, "%8.5f, %8.5f, %d \n", x, -y, score);
}

//木の高さを計算する関数
int height_tree(node* now) {
	if (now == NULL) return 0;
	int left = height_tree(now->left)+1;
	int right = height_tree(now->right)+1;
	return (left > right) ? left : right;
}

//木にノードを追加する関数
void maketree(node* p1, int id, int score) {
	node* p2;
	if (p1->score <= score) {
		if(p1->right==NULL){
			p2 = (node*)malloc(sizeof(node));
			p2->id = id;
			p2->score = score;
			p2->left = NULL;
			p2->right = NULL;
			p1->right = p2;
		}
		else {
			maketree(p1->right, id, score);
		}
	}
	else {
		if (p1->left == NULL) {
			p2 = (node*)malloc(sizeof(node));
			p2->id = id;
			p2->score = score;
			p2->left = NULL;
			p2->right = NULL;
			p1->left = p2;
		}
		else { 
			maketree(p1->left, id, score);
		}
	}
}

// main関数
int main()
{
	FILE* fpi; //入力ファイル
	FILE* fpw; //昇順にソートしたファイル
	FILE* fpt; //木を描くためのファイル
	if (fopen_s(&fpi, "data_huge.txt", "r") != 0) {
		printf("Failed to open file: data_small.txt\n");
		return -1;
	}
	if (fopen_s(&fpw, "order.txt", "w") != 0) {
		printf("Failed to open file: order.txt\n");
		return -1;
	}
	if (fopen_s(&fpt, "tree.xls", "w") != 0) {
		printf("Failed to open file: tree.xls\n");
		return -1;
	}
	int data[100000],i=0;
	while (fscanf_s(fpi, "%d", &data[i++]) != EOF);
	for (int e : data) {
		printf("%d\n", e);
	}
	fclose(fpi);
	node* p1; //根(root)ノード
	p1 = (node*)malloc(sizeof(node));
	p1->id = 0;
	p1->score = data[0];
	p1->left = p1->right = NULL;
	for (i = 0; i < N; i++) {
		maketree(p1, i, data[i]);
	}
	print_value(fpw, p1);
	draw_tree(fpt, p1, 0, 0, 1);
	int height;
	height = height_tree(p1);
	printf("height: %d\n", height);
	finish(p1);
	return 0;
}

