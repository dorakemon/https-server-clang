#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXPENDING 5
#define SERV_ADDR "0.0.0.0"
#define DEFAULT_PORT 8080

int Server(int);
void PrintTime(const char *);
void DieWithError(char *errorMessage);

int main(int argc, char *argv[]) {
    int servSock, clntSock;
    struct sockaddr_in servAddr, clntAddr;
    unsigned short servPort;
    unsigned int clntAddrLen;

    /* Set the size of the in-out parameter */
    clntAddrLen = sizeof(clntAddr);

    if (argc == 2)
        servPort = atoi(argv[1]);
    else
        servPort = DEFAULT_PORT;

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithError("socket() failed");
    }

    /* Construct local address structure */
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(SERV_ADDR);
    servAddr.sin_port = htons(servPort);

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    for (;;) {
        PrintTime("\n-------  Server is waiting  ------");
        if ((clntSock = accept(servSock, (struct sockaddr *)&clntAddr,
                               &clntAddrLen)) < 0)
            DieWithError("accept() failed");
        PrintTime("------------  Connected  -----------");

        // ブラウザとの送受信の処理
        Server(clntSock);

        close(clntSock);
        PrintTime("-------  Server task is ended  ------");
    }
    close(servSock);

    return 0;
}