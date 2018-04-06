/*
   04/06/2018 https://github.com/su8/ping-website

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <curl/curl.h>

int main(int argc, char *argv[]) {
  double total = 0.0;

  CURL *curl = NULL;
  CURLcode res;

  if (2 > argc) {
    printf("%s\n", "Missing website as argument.");
    return EXIT_FAILURE;
  }

  const char *const da_url = argv[1];

  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_URL, da_url);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "ping-website/1.0");
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); 
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);

  res = curl_easy_perform(curl);
  if (CURLE_OK != res) {
    goto error;
  }

  res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total);
  if (CURLE_OK != res) {
    goto error;
  }

  printf("Ping %.3fms\n", total);

error:
  if (NULL != curl) {
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return EXIT_SUCCESS;
}
