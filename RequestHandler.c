#include <stdio.h>
#include <string.h>

// HTTPリクエストを解析
void ParseRequest(char *requestBuffer, char *httpMethod, char *urlPath) {
    char version[20];
    // 1行目のみ取得
    char *requestLine = strtok(requestBuffer, "\n");
    // GET /dict/index.html HTTP/1.1
    sscanf(requestLine, "%s %s %s", httpMethod, urlPath, version);
    printf("%s: %s\n", httpMethod, urlPath);
}

// int main(void) {
//     char requestBuffer[] = "GET /dict/index.html HTTP/1.1\nsomething\nsomething\n";
//     char httpMethod[100];
//     char urlPath[100];
//     ParseRequest(requestMessage, method, urlPath);
// }
