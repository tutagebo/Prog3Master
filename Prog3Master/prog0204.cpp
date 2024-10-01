#include <iostream>

const int MAX = 100000; // スタック配列の最大サイズ
int stack[MAX]; // スタックを表す配列
int top = 0; // スタックの先頭を表す要素番号
// スタックを初期化する
void initialize() {
	top = 0;
}
// スタックが空かどうかを判定する
bool isEmpty() {
	return (top == 0); // スタックサイズが 0 かどうか
}
// スタックが満杯かどうかを判定する
bool isFull() {
	return (top == MAX); // スタックサイズが MAX かどうか
}
// push (top を進めて要素を格納)
void push(int v) {
	if (isFull()) {
		printf("error: オーバーフロー.");
		return;
	}
	stack[top++] = v;
	return;
}
// pop (top をデクリメントして、top の位置にある要素を返す)
int pop() {
	if (isEmpty()) {
		printf("error: アンダーフロー.");
		return -1;
	}
	return stack[--top];
}