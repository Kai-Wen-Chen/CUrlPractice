#include <stdio.h>
#include <stdlib.h>
#include "url2file.c"

int main(int argc, char *argv[]) {
    static const char *pagefilename = "page.out";
    FILE *pagefile;

    if(argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    //curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    CURL *curl_handle = initCURLHandle();

    /* set URL to get here */
    setURL(curl_handle, argv[1]);
    enableHTTP09(curl_handle, 1L);

    /* Switch on full protocol/debug output while testing */
    enableVerbose(curl_handle, 1L);

    /* disable progress meter, set to 0L to enable it */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

    /* send all data to this function  */
    setWriteFunction(curl_handle, NULL);

    /* open the file */
    pagefile = fopen(pagefilename, "wb");
    if(pagefile) {

        /* write the page body to this file handle */
        writeData(curl_handle, pagefile);

        /* close the header file */
        fclose(pagefile);
    }

    /* cleanup curl stuff */
    uninitCURLHandle(curl_handle);
    return 0;
}