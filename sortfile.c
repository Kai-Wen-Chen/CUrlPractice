#include <stdio.h>
#include <stdlib.h>
#include "fileItem.h"


FileItem* initFileItem(FILE* file) {
    unsigned int seq;
    unsigned short len;
    char* data;

    if (fread(&seq, sizeof(unsigned int), 1, file) > 0) {
        fread(&len, sizeof(unsigned short), 1, file);

        char* data = (char*)malloc(sizeof(char) * len);
        fread(data, sizeof(char) * len, 1, file);
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
    FileItem* fileItem1 = (FileItem*)a;
    FileItem* fileItem2 = (FileItem*)b;

    return (fileItem1->seq < fileItem2->seq);
}

void sortFileItems(FileItem* files, size_t file_num) {
    qsort(files, file_num, sizeof(FileItem), compare);
}