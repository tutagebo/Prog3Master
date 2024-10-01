#include <iostream>
#include "prog.h"

const int StackMAX = 100000; // �X�^�b�N�z��̍ő�T�C�Y
int stack[StackMAX]; // �X�^�b�N��\���z��
int top = 0; // �X�^�b�N�̐擪��\���v�f�ԍ�
// �X�^�b�N������������
void stackInitialize() {
	top = 0;
}
// �X�^�b�N���󂩂ǂ����𔻒肷��
bool isStackEmpty() {
	return (top == 0); // �X�^�b�N�T�C�Y�� 0 ���ǂ���
}
// �X�^�b�N�����t���ǂ����𔻒肷��
bool isStackFull() {
	return (top == StackMAX); // �X�^�b�N�T�C�Y�� MAX ���ǂ���
}
// push (top ��i�߂ėv�f���i�[)
void push(int v) {
	if (isStackFull()) {
		printf("error: �I�[�o�[�t���[.");
		return;
	}
	stack[top++] = v;
	return;
}
// pop (top ���f�N�������g���āAtop �̈ʒu�ɂ���v�f��Ԃ�)
int pop() {
	if (isStackEmpty()) {
		printf("error: �A���_�[�t���[.");
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
