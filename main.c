#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "url2file.c"
#include "sortfile.c"

#define FILE_NAME "data.out"
#define RESULT_NAME "result.out"


void getDataFromURL(char* url) {
    const char *filename = FILE_NAME;
    FILE *file;

    /* init the curl session */
    CURL *curl_handle = initCURLHandle();
    setURL(curl_handle, url);
    enableHTTP09(curl_handle, 1L);
    enableVerbose(curl_handle, 1L);

    /* send all data to file */
    setWriteFunction(curl_handle, NULL);
    file = fopen(filename, "w");
    if(file) {
        writeData(curl_handle, file);
        fclose(file);
    }

    /* cleanup curl stuff */
    uninitCURLHandle(curl_handle);
}

void reorderFile() {
    FILE* file = fopen(FILE_NAME, "r");
    int count = 0;
    FileItem** fileitems = initFileItems(file, &count);
    if (ferror(file) || !fileitems) {
        printf("Read data.txt failed\n");
        fclose(file);
        return;
    }
    fclose(file);

    /* reorder file data */
    sortFileItems(fileitems, count);

    /* write result */
    FILE* res = fopen(RESULT_NAME, "wb");
    for (int i=0; i<count; ++i) {
        printf("seq = %u, len = %d\n", fileitems[i]->seq, fileitems[i]->len);
        if (fwrite(fileitems[i]->data, sizeof(unsigned char), sizeof(unsigned char) * fileitems[i]->len, res) <= 0) {
            printf("Write result.out failed\n");
            break;
        }
    }

    fclose(res);
    free(fileitems);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    getDataFromURL(argv[1]);
    reorderFile();
    return 0;
}
