#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <process.h>
#include <malloc.h>


void showInfo(char *fileName) {

    FILE *track = fopen(fileName, "rb");
    long long metadataLength = 0;
    long long ten = 256 * 256 * 256;
    fseek(track, 6, SEEK_SET);
    for (int i = 0; i < 4; ++i) {
        int tmp = fgetc(track);
        metadataLength += tmp * ten;
        ten = ten / 256;
    }
    printf("%lld\n", metadataLength);

    fseek(track, 10, SEEK_SET);
    long long i = 10;
    while (i < metadataLength) {
        char name[4] = {0, 0, 0, 0};
        fgets(name, 5, track);
        if (name[0] == 0 && name[1] == 0 && name[2] == 0 && name[3] == 0) {
            break;
        }