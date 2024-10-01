#include <iostream>
#include <stdlib.h>
#pragma warning(disable:4996)

int prog202() {
    char Filename[FILENAME_MAX];
    FILE* readFp;
    int numArray[1000];
    int count = 0, targetNum;

    if ((readFp = fopen("data.txt", "r")) == NULL) {
        printf("Not found such as ReadFile");
        exit(EXIT_FAILURE);
    }

    int max=0, min=2147483647;
    double sum = 0;
    while (fscanf_s(readFp, "%d", &numArray[count]) != EOF) {
        sum += numArray[count];
        max = (max < numArray[count]) ? numArray[count] : max;
        min = (min > numArray[count]) ? numArray[count] : min;
        count++;
    }

    printf("heikin: %lf\n", sum/(double)count);
    printf("max: %d\nmin: %d\n", max, min);
    fclose(readFp);
    return 0;
}
