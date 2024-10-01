#include <iostream>
#include "prog.h"

const int StackMAX = 100000; // スタック配列の最大サイズ
int stack[StackMAX]; // スタックを表す配列
int top = 0; // スタックの先頭を表す要素番号
// スタックを初期化する
void stackInitialize() {
	top = 0;
}
// スタックが空かどうかを判定する
bool isStackEmpty() {
	return (top == 0); // スタックサイズが 0 かどうか
}
// スタックが満杯かどうかを判定する
bool isStackFull() {
	return (top == StackMAX); // スタックサイズが MAX かどうか
}
// push (top を進めて要素を格納)
void push(int v) {
	if (isStackFull()) {
		printf("error: オーバーフロー.");
		return;
	}
	stack[top++] = v;
	return;
}
// pop (top をデクリメントして、top の位置にある要素を返す)
int pop() {
	if (isStackEmpty()) {
		printf("error: アンダーフロー.");
		return -1;
	}
	return stack[--top];
}

int prog204() {
	stackInitialize();
	int target[] = { 47, 578, 58873, 677877, 733498699 };
	int tmp;
	for (int x : target) {
		while (x!=0) {
			push(x % 2);
			x /= 2;
		}
		while (1) {
			tmp = pop();
			if (tmp == -1)break;
			printf("%d", tmp);
		}
		printf("\n");
	}
	return 0;
}
