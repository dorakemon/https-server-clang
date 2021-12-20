#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define HTTP_SUCCESS 200
#define HTTP_ERROR 404

bool ExistFile(const char* path);
int GetFileSize(const char* path);

int CreateResponse(char* responseBuffer, const char* httpMethod, const char* _urlPath) {
    int httpStatus;
    char httpHeader[100];
    FILE* fp;
    int contentSize = 0;
    char contentBuffer[512 * 1024];
    char urlPath[strlen(_urlPath) + 1];

    // printf("%s\n\n", responseBuffer);

    // /pathを./pathにして相対パスにする
    sprintf(urlPath, ".%s", _urlPath);

    if (strcmp("GET", httpMethod) == 0) {
        if (ExistFile(urlPath)) {
            contentSize = GetFileSize(urlPath);
            fp = fopen(urlPath, "r");
            fread(contentBuffer, sizeof(char), contentSize, fp);
            fclose(fp);
            httpStatus = HTTP_SUCCESS;
        } else
            httpStatus = HTTP_ERROR;
    } else {
        httpStatus = HTTP_ERROR;
    }
    sprintf(httpHeader, "Content-Length: %d\r\n", contentSize);
    if (httpStatus == HTTP_SUCCESS) {
        sprintf(responseBuffer, "HTTP/1.1 200 OK\r\n%s\r\n %s", httpHeader, contentBuffer);
    } else {
        sprintf(responseBuffer, "HTTP/1.1 404 Not Found\r\n%s\r\n", httpHeader);
    }
    return strlen(responseBuffer);
}

// int main(void) {
//     char responseBuffer[1024 * 1024];

//     int size = CreateResponse(responseBuffer, "GET", "/dist/index.html");
//     printf("%s\n", responseBuffer);
//     printf("%d\n", size);
//     return 0;
// }
