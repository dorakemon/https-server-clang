#include "Server.h"

// HTTP用のサーバの関数
int Server(int sock) {
    int requestLen, responseLen;
    char requestBuffer[REQMAX];
    char responseBuffer[RESMAX];
    char httpMethod[10];
    char urlPath[100];
    char httpHeader[500];

    if ((requestLen = recv(sock, requestBuffer, REQMAX, 0)) < 0) {
        DieWithError("receive error\n");
    }

    // HTTPリクエストから、HTTPメソッドとファイルパスを取得
    ParseRequest(requestBuffer, httpMethod, urlPath);
    // 受け取ったメソッドとパスからHTTPレスポンスを作成
    responseLen = CreateResponse(responseBuffer, httpMethod, urlPath);

    if (send(sock, responseBuffer, responseLen, 0) != responseLen) {
        DieWithError("send error\n");
    }

    return 0;
}