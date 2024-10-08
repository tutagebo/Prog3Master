#include <iostream>
#include <stdlib.h>
#pragma warning(disable:4996)

int prog201() {
    FILE *readFp, *writeFp;
    int numArray[1000];
    int count = 0;

    if ((readFp = fopen("data.txt", "r")) == NULL) {
        printf("Not found such as ReadFile");
        exit(EXIT_FAILURE);
    }
    if ((writeFp = fopen("log.txt", "w")) == NULL) {
        printf("Not found such as WriteFile");
        exit(EXIT_FAILURE);
    }

    while (fscanf_s(readFp,"%d",&numArray[count]) != EOF) {
        fprintf( writeFp,"%d ", numArray[count]);
        if (count % 5 == 4) {
            fprintf(writeFp, "\n");
        }
        count++;
    }

    fclose(writeFp);
    fclose(readFp);
    return 0;
}
