#include <stdio.h>
#include <stdlib.h>
#include "url2file.c"
#include "sortfile.c"

#define FILE_NAME "data.txt"


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
    file = fopen(filename, "wb");
    if(file) {
        writeData(curl_handle, file);
        fclose(file);
    }

    /* cleanup curl stuff */
    uninitCURLHandle(curl_handle);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    getDataFromURL(argv[1]);
    FILE* file = fopen(FILE_NAME, "rb");
    FileItem* fileItem = NULL;
    do {
        if (fileItem) {
            printf("%u, %d\n", fileItem->seq, fileItem->len);
            free(fileItem);
        }
        fileItem = initFileItem(file);        
    } while (fileItem);

    fclose(file);
    return 0;
}
