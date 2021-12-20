#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int PrintTime(const char *debugInfo) {
    int hours, minutes, seconds, day, month, year;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;

    printf("\033[0;32m%s", debugInfo);
    printf("\033[0;34m @ %02d:%02d:%02d \n", hours, minutes, seconds);
    printf("\033[0;37m");

    return 0;
}