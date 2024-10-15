#include <iostream>
#include <string.h>
#pragma warning(disable:4996)

typedef struct record {
    char name[30];
    int population;
    double area;
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

void finish(queue* queue) {
    record* p, * next;
    p = queue->head;
    while (p != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
}

//都道府県情報をエンキューする関数
void enqueue(queue* queue, char* name, int population, double area) {
    record* add;
    add = (record*)malloc(sizeof(record));
    if (add == NULL) {
        printf("memory cannot alloc! ¥n");
        return;
    }
    strcpy_s(add->name,name);
    add->population = population;
    add->area = area;
    add->next = NULL;
    if (queue->head == NULL) {
        queue->head = add;
        queue->tail = add;
        return;
    }
    queue->tail->next = add;
    queue->tail = add;
}

record* dequeue(queue* queue) {
    //キューが空なら何もせずに関数終了
    if (queue->head == NULL) {
        printf("queue is empty \n");
        exit(0);
    }
    //デキューするデータをheadから取得しdrecordに保存
    record* drecord;
    drecord = (record*)malloc(sizeof(record));
    strcpy(drecord->name, queue->head->name);
    drecord->population = queue->head->population;
    drecord->area = queue->head->area;
    drecord->next = NULL;
    //デキューするデータのnextポインタを一旦保存しておく
    record* tmpNext;
    tmpNext = queue->head->next;
    //headを削除（メモリーを解放）
    free(queue->head);
    queue->head = tmpNext;
    return drecord;
}


int prog302() {
    //queueを初期化
    queue queue;
    initialize(&queue);
    FILE* readFp;
    record pref[47] = {};

    if ((readFp = fopen("popu.txt", "r")) == NULL) {
        printf("Not found such as ReadFile");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 47; i++) {
        fscanf_s(readFp, "%s", pref[i].name, 30);
        fscanf_s(readFp, "%d", &pref[i].population);
        fscanf_s(readFp, "%lf", &pref[i].area);
        printf("%d\n", pref[i].population);
        enqueue( &queue ,pref[i].name, pref[i].population, pref[i].area);
    }
    record* the_record;
    for (int i = 0; i < 47; i++) {
        the_record = dequeue(&queue);
        printf("%s %d %lf\n", the_record->name, the_record->population, the_record->area);
    }
    fclose(readFp);
    return 0;
}