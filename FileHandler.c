#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

// ファイルが存在するか確認
bool ExistFile(const char* path) {
    if (access(path, F_OK) == 0)
        return true;
    else {
        fprintf(stderr, "Not exist '%.20s'\n", path);
        return false;
    }
}

// ファイルのサイズを取得
int GetFileSize(const char* path) {
    int size;

    FILE* fp = fopen(path, "rb");
    if (fp == 0) {
        fprintf(stderr, "Not exist '%.20s'\n", path);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fclose(fp);
    printf("%.20s: size is %d\n", path, size);

    return size;
}

// int main(void) {
//     int exist = ExistFile("./dist/js/chunk-vendors.dc67b9a1.js");
//     printf("%d\n", exist);
//     int size = GetFileSize("./dist/js/chunk-vendors.dc67b9a1.js");
//     printf("%d\n", size);
// }
