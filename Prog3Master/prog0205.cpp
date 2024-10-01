#include <iostream>

const int MAX = 100000; // キュー配列の最大サイズ
int que[MAX]; // キューを表す配列
int tail = 0, head = 0; // キューの要素区間を表す変数
// キューを初期化する
void initialize() {
	head = tail = 0;
}
// キューが空かどうかを判定する
bool isEmpty() {
	return (head == tail);
}
// キューが満杯かどうかを判定する
bool isFull() {
	return (head == (tail + 1) % MAX);
}
// enqueue (tail に要素を入れてインクリメント)
void enqueue(int v) {
	if (isFull()) {
		printf("error:オーバーフロー ¥n");
		return;
	}
}
// dequeue (head にある要素を出して head をインクリメント)
int dequeue() {
	if (isEmpty()) {
		printf("error:アンダーフロー ¥n");
		return -1;
	}
}