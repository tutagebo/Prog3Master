#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)

//ノードの構造体
typedef struct node {
	int id;
	int score;
	node* left;
	node* right;
} node;

//木をたどって値を昇順に出力する
void print_value(node* now) {
	if (now == NULL) return;
	print_value(now->left);
	printf("%d\n", now->score);
	print_value(now->right);
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
	draw_tree(fpt, p1->left, x - width, y + 1, width);
	fprintf(fpt, "%8.5f, %8.5f, %d \n", x, -y, score);
	width *= 2;
	draw_tree(fpt, p1->right, x + width, y + 1, width);
	fprintf(fpt, "%8.5f, %8.5f, %d \n", x, -y, score);
}

//木の高さを計算する関数
int height_tree(node* now) {
	if (now == NULL) return 0;
	int left = height_tree(now->left) + 1;
	int right = height_tree(now->right) + 1;
	return (left > right) ? left : right;
}

//木にノードを追加する関数
void maketree(node* p1, int id, int score) {
	node* p2;
	if (p1->score <= score) {
		if (p1->right == NULL) {
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
/*
int search_node(node* p1, int score) {
	if (p1 == NULL)return -1;
	if (score == p1->score)return p1->id;
	return (score < p1->score) ? search_node(p1->left, score) : search_node(p1->right, score);
}*/

int search_node(node* p1, int score) {
	if (p1 == NULL) return -1;  // ノードが存在しない場合、-1を返す
	if (p1->score == score) return p1->id;  // スコアが一致すればIDを返す
	if (score < p1->score)
		return search_node(p1->left, score);  // 左部分木に移動
	else
		return search_node(p1->right, score); // 右部分木に移動
}

void prog501() {
	int target_ary[10] = {
		30391024, 328291059, 501372422, 637875300, 311223120,
		603117998, 621736584, 140666598, 31012956, 935691960
	};
	FILE* fpi; //入力ファイル
	if (fopen_s(&fpi, "data_huge.txt", "r") != 0) {
		printf("Failed to open file: data_huge.txt\n");
		return;
	}
	//二分木作成
	int data, i = 0;
	node* p1; //根(root)ノード
	fscanf_s(fpi, "%d", &data);
	p1 = (node*)malloc(sizeof(node));
	p1->id = 0;
	p1->score = data;
	p1->left = p1->right = NULL;
	i++;
	while (fscanf_s(fpi, "%d", &data) != EOF){
		maketree(p1, i, data);
		i++;
	}
	print_value(p1);
	//ここまで
	for (i = 0; i < 10; i++) {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER start, end;
		QueryPerformanceCounter(&start);
		// koko
		int res = search_node(p1, target_ary[i]);
		printf("%d", res);
		// kokomade
		QueryPerformanceCounter(&end);
		LONGLONG span = end.QuadPart - start.QuadPart;
		double sec = (double)span / (double)frequency.QuadPart;
		printf("%d:%lf\n", res, sec);
	}
	finish(p1);
	fclose(fpi);
	return;
}