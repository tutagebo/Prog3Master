#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#define N 50
#pragma warning(disable:4996)

// セル(cell)
typedef struct cell {
	char* score;
	int id;
	struct cell* next;
} cell;
// ハッシュテーブル
typedef struct hashtable {
	int size, count;
	cell** table;
} hashtable;

hashtable* make_hashtable(int size);
int hash_func(hashtable* ht, const char* score);
bool insert_hash(hashtable* ht, const char* score, int id);
cell* make_cell(const char* score, int id, cell* next);

// ハッシュ表の生成・初期化
hashtable* make_hashtable(int size) {
	hashtable* ht = (hashtable*)malloc(sizeof(hashtable));
	if (ht != NULL) {
		ht->size = size;
		ht->count = 0;
		ht->table = (cell**)malloc(sizeof(cell*) * size);
		if (ht->table == NULL) {
			free(ht);
			return NULL;
		}
		for (int i = 0; i < size; i++) ht->table[i] = NULL;
	}
	return ht;
}
// ハッシュ関数
int hash_func(hashtable* ht, const char* score) {
	unsigned int value = 0;
	for (int n = 0; score[n] != '\0'; n++)
		value = (value << 3) + score[n];
	return value % ht->size;
}
// 挿入
bool insert_hash(hashtable* ht, const char* score, int id) {
	int hval = hash_func(ht, score);
	ht->table[hval] = make_cell(score, id, ht->table[hval]);
	ht->count++;
	return true;
}
// セルの生成
cell* make_cell(const char* score, int id, cell* next) {
	cell* cp = (cell*)malloc(sizeof(cell));
	if (cp != NULL) {
		cp->score = (char*)malloc(strlen(score) + 1);
		strcpy(cp->score, score);
		cp->id = id;
		cp->next = next;
	}
	return cp;
}

void print_hashtable(hashtable* ht) {
	for (int hval = 0; hval < ht->size; hval++) {
		printf("hval=%d score ", hval);
		cell* next_cell = ht->table[hval];
		while (next_cell != NULL) {
			printf("%s ", next_cell->score);
			next_cell = next_cell->next;
		}
		printf("\n");
	}
}

int search_hash(hashtable* ht, const char* score) {
	int hash = hash_func(ht, score);
	cell* now_cell = ht->table[hash];
	while (now_cell!=NULL) {
		if (strcmp(score, now_cell->score) == 0) {
			printf("%d\n", now_cell->id);
			return 0;
		}
		now_cell = now_cell->next;
	}
	return 0;
}

// ハッシュ表の廃棄
void delete_hashtable(hashtable* ht) {
	for (int i = 0; i < ht->size; i++) {
		cell* cp = ht->table[i];
		while (cp != NULL) {
			cell* xs = cp->next;
			free(cp->score);
			free(cp);
			cp = xs;
		}
	}
	free(ht);
}

void hash_test0(){
	hashtable* ht = make_hashtable(100003);
	char strings[5][30] = { "ikaho","numata","kusatsu","mizusawa","haruna" };
	for (int i = 0; i < 5;i++) {
		int hash = hash_func(ht, strings[i]);
		printf("%-10s: %d\n", strings[i], hash);
	}
	delete_hashtable(ht);
}

void hash_test1(int num_data) {
	hashtable* ht = make_hashtable(100003);
	for (int i = 0; i < num_data; i++) {
		char string[1000];
		int tar_num = rand() * rand();
		sprintf_s(string, "%d", tar_num);
		insert_hash(ht, string, i);
	}
	delete_hashtable(ht);
}

void hash_test2() {
	FILE* fpi; //入力ファイル
	if (fopen_s(&fpi, "data_small.txt", "r") != 0) {
		printf("Failed to open file: data_small.txt\n");
		return;
	}
	int i=0;
	hashtable* ht = make_hashtable(18);
	int tmp_num;
	char tmp[50];
	while (fscanf_s(fpi, "%d", &tmp_num) != EOF) {
		sprintf_s(tmp, "%d", tmp_num);
		insert_hash(ht, tmp, i);
		i++;
	}
	print_hashtable(ht);
	delete_hashtable(ht);
}

void prog604a(){
//void main() {
	char target_ary[10][12] = {
		"30391024", "328291059", "501372422",
		"637875300", "311223120", "603117998", 
		"621736584", "140666598", "31012956", "935691960"
	};
	FILE* fpi; //入力ファイル
	if (fopen_s(&fpi, "data_huge.txt", "r") != 0) {
		printf("Failed to open file: data_huge.txt\n");
		return;
	}
	//ハッシュ表作成
	int i = 0;
	hashtable* ht = make_hashtable(100003);
	//int tmp_num;
	int tmp_num;
	char tmp[50];
	while (fscanf_s(fpi, "%d", &tmp_num) != EOF) {
		sprintf_s(tmp, "%d", tmp_num);
		insert_hash(ht, tmp, i);
		i++;
	}
	fclose(fpi);
	//ここまで
	for (i = 0; i < 10; i++) {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER start, end;
		QueryPerformanceCounter(&start);
		// koko
		search_hash(ht,target_ary[i]);
		// kokomade
		QueryPerformanceCounter(&end);
		LONGLONG span = end.QuadPart - start.QuadPart;
		double sec = (double)span / (double)frequency.QuadPart;
		printf("%d:%lf\n", i, sec);
	}
	delete_hashtable(ht);
}

int prog602a() {
	for (int i = 10000; i <= 250000; i += 10000) {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER start, end;
		QueryPerformanceCounter(&start);
		// koko
		hash_test1(i);
		// kokomade
		QueryPerformanceCounter(&end);
		LONGLONG span = end.QuadPart - start.QuadPart;
		double sec = (double)span / (double)frequency.QuadPart;
		printf("%d:%lf\n", i, sec);
	}
	return 0;
}