#include <stdio.h>
#include <stdlib.h>
#include "fileItem.h"


FileItem* initFileItem(FILE* file) {
    unsigned int seq;
    unsigned short len;
    char* data;

    if (fread(&seq, sizeof(unsigned int), 1, file) > 0) {
        if (fread(&len, sizeof(unsigned short), 1, file) <= 0)
            return NULL;

        char* data = (char*)malloc(sizeof(char) * len);
        if (fread(data, sizeof(char) * len, 1, file) <= 0)
            return NULL;
    } else
        return NULL;

    //printf("%u, %d\n", seq, len);

    FileItem* fileItem = (FileItem*)malloc(sizeof(FileItem));
    fileItem->seq = seq;
    fileItem->len = len;
    fileItem->data = data;
    return fileItem;
}

int compare(const void* a, const void* b) {
    FileItem* fileItem1 = *(FileItem**)a;
    FileItem* fileItem2 = *(FileItem**)b;

    if (fileItem1->seq < fileItem2->seq) return -1;
    else if (fileItem1->seq > fileItem2->seq) return 1;
    else return 0;
}

void sortFileItems(FileItem** files, size_t file_num) {
    qsort(files, file_num, sizeof(FileItem*), compare);
}
