#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define REQMAX 4096
#define RESMAX (524 * 1024)

int ParseRequest(char *, char *, char *);
int CreateResponse(char *, const char *, const char *);
void PrintTime(const char *);
void DieWithError(char *errorMessage);