#include <iostream>

const int MAX = 100000; // �X�^�b�N�z��̍ő�T�C�Y
int stack[MAX]; // �X�^�b�N��\���z��
int top = 0; // �X�^�b�N�̐擪��\���v�f�ԍ�
// �X�^�b�N������������
void initialize() {
	top = 0;
}
// �X�^�b�N���󂩂ǂ����𔻒肷��
bool isEmpty() {
	return (top == 0); // �X�^�b�N�T�C�Y�� 0 ���ǂ���
}
// �X�^�b�N�����t���ǂ����𔻒肷��
bool isFull() {
	return (top == MAX); // �X�^�b�N�T�C�Y�� MAX ���ǂ���
}
// push (top ��i�߂ėv�f���i�[)
void push(int v) {
	if (isFull()) {
		printf("error: �I�[�o�[�t���[.");
		return;
	}
	stack[top++] = v;
	return;
}
// pop (top ���f�N�������g���āAtop �̈ʒu�ɂ���v�f��Ԃ�)
int pop() {
	if (isEmpty()) {
		printf("error: �A���_�[�t���[.");
		return -1;
	}
	return stack[--top];
}