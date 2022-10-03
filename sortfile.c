#include <stdio.h>
#include <stdlib.h>
#include "fileItem.h"


FileItem** initFileItems(FILE* file, int* count) {
    FileItem** fileitems = (FileItem**)malloc(sizeof(FileItem) * 200);
    if (!fileitems) {
        printf("Cannot create file item array\n");
        return NULL;
    }

    do {
        char seq_byte[4];
        char len_byte[2];
        int c;

        for (int i=0; i<4; ++i) {
            c = fgetc(file);
            if (c == EOF) {
                printf("Read seq failed\n");
                return NULL;
            }

            seq_byte[i] = (char)c;
        }

        for (int i=0; i<2; ++i) {
            c = fgetc(file);
            if (c == EOF) {
                printf("Read len failed\n");
                return NULL;
            }

            len_byte[i] = (char)c;
        }

        FileItem* fileItem = (FileItem*)malloc(sizeof(FileItem));
        if (!fileItem) {
            printf("Create file item failed\n");
            return NULL;
        }
        fileItem->seq = *(unsigned int*)seq_byte;
        fileItem->len = *(unsigned short*)len_byte;
        fileItem->data = (unsigned char*)malloc(sizeof(unsigned char) * fileItem->len);
        unsigned short i = 0;
        
        for (; i<fileItem->len; ++i) {
            c = fgetc(file);
            if (c == EOF) {
                printf("Read data EOF\n");
                break;
            }
            fileItem->data[i] = (unsigned char)c;
        }
        if (i != fileItem->len)
            fileItem->len = i;
        fileitems[(*count)++] = fileItem;
        //printf("#chunk %d: seq = %u, len = %d\n", *count, fileItem->seq, fileItem->len);
    } while (!feof(file) && !ferror(file));
    
    return fileitems;
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
