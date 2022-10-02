/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2022, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/
/* <DESC>
 * Download a given URL into a local file named page.out.
 * </DESC>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

CURL* initCURLHandle() {
  CURL* curl_handle;
  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();
  return curl_handle;
}

void uninitCURLHandle(CURL* curl_handle) {
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();
}

CURLcode setURL(CURL* curl_handle, const char* url) {
  return curl_easy_setopt(curl_handle, CURLOPT_URL, url);
}

CURLcode enableHTTP09(CURL* curl_handle, long allowed) {
  return curl_easy_setopt(curl_handle, CURLOPT_HTTP09_ALLOWED, allowed);
}

CURLcode enableVerbose(CURL* curl_handle, long allowed) {
  return curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, allowed);
}

CURLcode setWriteFunction(CURL* curl_handle, size_t* writeFn) {
  if (!writeFn)
    return curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
  else
    return curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, *writeFn);
}

CURLcode setWriteDataOutputFile(CURL* curl_handle, FILE* file) {
  return curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, file);
}

CURLcode writeData(CURL* curl_handle, FILE* file) {
  if (!file) {
    printf("Invalid file, please check if it exists\n");
    return CURLE_WRITE_ERROR;
  }

  CURLcode code = setWriteDataOutputFile(curl_handle, file);
  if (code != CURLE_OK) {
    printf("Write failed, error code: %d\n", code);
    return code;
  }

  return curl_easy_perform(curl_handle);
}
