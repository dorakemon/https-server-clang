#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

#include "Server.h"

// HTTPS用のサーバの関数
int Server(int sock) {
    int requestLen, responseLen;
    char requestBuffer[REQMAX];
    char responseBuffer[RESMAX];
    char httpMethod[10];
    char urlPath[100];
    char httpHeader[500];

    int sd;
    SSL_CTX *ctx;
    SSL *ssl;

    char crt_file[] = "secret/server.crt";
    char key_file[] = "secret/server.key";

    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();

    ctx = SSL_CTX_new(SSLv23_server_method());
    SSL_CTX_use_certificate_file(ctx, crt_file, SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, key_file, SSL_FILETYPE_PEM);

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_accept(ssl) > 0) {
        // SSLを用いた受信
        SSL_read(ssl, requestBuffer, REQMAX);
        ParseRequest(requestBuffer, httpMethod, urlPath);
        responseLen = CreateResponse(responseBuffer, httpMethod, urlPath);
        // SSLを用いた送信
        SSL_write(ssl, responseBuffer, responseLen);
    }
    sd = SSL_get_fd(ssl);
    SSL_free(ssl);
    close(sd);

    return 0;
}