#include <iostream>
#include <stdio.h>

const int QueueMAX = 100000; // キュー配列の最大サイズ
int que[QueueMAX]; // キューを表す配列
int tail = 0, head = 0; // キューの要素区間を表す変数
// キューを初期化する
void queueInitialize() {
	head = tail = 0;
}
// キューが空かどうかを判定する
bool isQueueEmpty() {
	return (head == tail);
}
// キューが満杯かどうかを判定する
bool isQueueFull() {
	return (head == (tail + 1) % QueueMAX);
}
// enqueue (tail に要素を入れてインクリメント)
void enqueue(int v) {
	if (isQueueFull()) {
		printf("error:オーバーフロー\n");
		return;
	}
	que[tail++] = v;
	tail = (tail >= QueueMAX) ? 0 : tail;
	return;
}
// dequeue (head にある要素を出して head をインクリメント)
int dequeue() {
	if (isQueueEmpty()) {
		printf("error:アンダーフロー\n");
		return -1;
	}
	int tmp = que[head++];
	head = (head >= QueueMAX) ? 0 : head;
	return tmp;
}

int prog205() {
	queueInitialize();
	char tmp;
	for (;;) {
		scanf_s("%c\n", &tmp);
		if ('0' <= tmp && tmp <= '9') {
			enqueue((int)(tmp-'0'));
		}else{
			printf("%c\n", dequeue());
		}
	}
	return 0;
}
