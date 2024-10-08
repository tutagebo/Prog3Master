#include <iostream>
#pragma warning(disable:4996)
/*
typedef struct record {
	char name[30];
	int population;
	double surface;
	struct record* next;
}record;
typedef struct queue {
	record* head;
	record* tail;
}queue;

void initialize(queue* queue) {
	queue->head = NULL;
	queue->tail = NULL;
}
//キューの終了処理をする
/*
void finish(queue* queue) {
	record* p, * next;
	p = queue->head;
	while (p != NULL) {
		next = p->next;
		free(p);
		p = next;
	}
}

int prog301() {
    FILE* readFp, * writeFp;
    record pref[47] = {};
    int count = 0;

    if ((readFp = fopen("popu.txt", "r")) == NULL) {
        printf("Not found such as ReadFile");
        exit(EXIT_FAILURE);
    }
    if ((writeFp = fopen("log.txt", "w")) == NULL) {
        printf("Not found such as WriteFile");
        exit(EXIT_FAILURE);
    }

    double sum = 0;
    double popuPerSur[47];
    while (fscanf_s(readFp, "%s",pref[count].name, 30) != EOF) {
        fscanf_s(readFp, "%d", &pref[count].population);
        fscanf_s(readFp, "%lf", &pref[count].surface);
        popuPerSur[count] = pref[count].population / pref[count].surface;
        sum += popuPerSur[count];
        count++;
    }

    for (int i = 0; i < 10; i++) {
        printf("%s %lf(人/km2)\n",pref[46-i].name, popuPerSur[46-i]);
    }
    printf("平均値: %lf", sum / 47);
    fclose(writeFp);
    fclose(readFp);
    return 0;}*/