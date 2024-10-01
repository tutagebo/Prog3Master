#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)

int prog203() {
    char Filename[FILENAME_MAX];
    FILE* readFp;
    int numArray[1000];
    int count = 0;
    int targetNums[] = { 170724396, 19683398, 618600040, 859407684, 236536470, 33751602, 37387288, 16374600, 118231107, 192515622};

    if ((readFp = fopen("data.txt", "r")) == NULL) {
        printf("Not found such as ReadFile");
        exit(EXIT_FAILURE);
    }

    while (fscanf_s(readFp, "%d", &numArray[count]) != EOF)count++;

    for (int x : targetNums) {
        int i;
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        LARGE_INTEGER start, end;
        QueryPerformanceCounter(&start);
        //
        for (i = 0; i < 10000;i++) {
            if (x == numArray[i]) {
                printf("%d %d ", x, i);
                break;
            }
        }
        // kokomade
        QueryPerformanceCounter(&end);
        LONGLONG span = end.QuadPart - start.QuadPart;
        double sec = (double)span / (double)frequency.QuadPart;
        printf("%lf\n", sec);
    }

    fclose(readFp);
    return 0;
}
