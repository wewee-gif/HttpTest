#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "curl/curl.h"
#include "uv.h"


int main(void)
{
  CURL *curl = curl_easy_init();
  if(curl) {
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "data");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); 
    res = curl_easy_perform(curl);
    if(res == CURLE_OK) {
      char *method = NULL;
      curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_METHOD, &method);
      if(method)
        printf("Redirected to method: %s\n", method);

      char *ct;
      /* ask for the content-type */
      curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
      printf("We received Content-Type: %s\n", ct);

      char *data;
      curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
      printf("We received data: %s\n", ct);
    }else
      printf("curl code: %s\n",curl_easy_strerror(res));//
      printf("curl code: %d\n", res);
    curl_easy_cleanup(curl);
  }
}