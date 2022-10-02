#include <stdio.h>
#include <stdlib.h>
#include "url2file.c"

#define FILE_NAME "data.out"


int main(int argc, char *argv[]) {
    const char *filename = FILE_NAME;
    FILE *file;

    if(argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    /* init the curl session */
    CURL *curl_handle = initCURLHandle();
    setURL(curl_handle, argv[1]);
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
    return 0;
}