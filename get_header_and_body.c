#include <stdio.h>
#include <string.h>
#include "curl/curl.h"

/* 头部回调函数 */
size_t header_callback(void *ptr, size_t size, size_t nmemb, void *data) {

    printf("/n------------------------------------/n header:");
    printf("%.*s", (int)(size*nmemb), (char*)ptr);

    FILE *men=(FILE*) data;
    fwrite(ptr,size,size * nmemb,men);

    return size*nmemb;
}

/* 响应体回调函数 */ 
size_t body_callback(void *ptr, size_t size, size_t nmemb, void *data) {

    printf("/n--------------------------------------------/nbody:");
    printf("%.*s", (int)(size*nmemb), (char*)ptr);

    size_t realsize = size * nmemb;
    FILE *mem = (FILE*)data;
    fwrite(ptr, size, realsize, mem);
    return realsize;
}

int main(int argc, char *argv[]) {
    CURL *curl;
    CURLcode res;
    FILE *headerfile;
    FILE *bodyfile;
    curl = curl_easy_init();
    if(argc<2){
        printf("请输入url");
        return 0;
    }
    char *url=argv[1];
    if(curl) {
        printf("url=%s",url);
        /* 设置URL */
        curl_easy_setopt(curl, CURLOPT_URL,url);
        //curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
        //打印VERBOSE（繁琐的信息）也就是debug时用，把很多信息给打印出来，第三个参数 1：表示开启，2：表示关闭（默认0）
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        //取消SSL检查
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); 

        /* 设置头部回调函数 */
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);

        /* 设置响应体回调函数 */
        bodyfile = fopen("body.txt", "wb");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, body_callback);

        /* 设置响应体写入的文件指针 */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, bodyfile);

        /* 也可以将头部写入到单独的文件 */
        headerfile = fopen("header.txt", "wb");
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, headerfile);

        /* 执行请求 */
        res = curl_easy_perform(curl);

        /* 检查执行结果 */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        /* 关闭文件 */
        fclose(headerfile);
        fclose(bodyfile);

        /* 清理CURL对象 */
        curl_easy_cleanup(curl);
    }

    return 0;
}