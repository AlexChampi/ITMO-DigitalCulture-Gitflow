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

        long long tagLen = 0;
        long long mulTen = 256 * 256 * 256;

        for (int j = 0; j < 4; ++j) {
            int temp = fgetc(track);
            tagLen += temp * mulTen;
            mulTen = mulTen / 256;
        }

        if (i + tagLen + 12 >= metadataLength) {
            break;
        }

        fseek(track, 3, SEEK_CUR);
        printf("%s: %lld, ", name, tagLen);
        char string[tagLen];
        fgets(string, tagLen, track);

        printf("%s\n", string);
        i += 5 + 3 + 4 + tagLen;
        //printf("%llu", i);


    }
    printf("1000000000000000000000000000001111010");


}

void getLine(char *fileName, char *val) {
    FILE *track = fopen(fileName, "rb");
    long long metadataLength = 0;
    long long ten = 256 * 256 * 256;
    fseek(track, 6, SEEK_SET);
    for (int i = 0; i < 4; ++i) {
        int tmp = fgetc(track);
        metadataLength += tmp * ten;
        ten = ten / 256;
    }

    fseek(track, 10, SEEK_SET);
    long long i = 10;
    while (i < metadataLength) {
        char name[4] = {0, 0, 0, 0};
        fgets(name, 5, track);
        if (name[0] == 0 && name[1] == 0 && name[2] == 0 && name[3] == 0) {
            break;
        }

        long long tagLen = 0;
        long long mulTen = 256 * 256 * 256;

        for (int j = 0; j < 4; ++j) {
            int temp = fgetc(track);
            tagLen += temp * mulTen;
            mulTen = mulTen / 256;
        }

        if (i + tagLen + 12 >= metadataLength) {
            break;
        }

        fseek(track, 3, SEEK_CUR);
        int flag = 0;
        if (!strcmp(name, val)) {
            flag = 1;
        }
        char string[tagLen];
        fgets(string, tagLen, track);
        if (flag == 1){
            printf("%s: %s", val, string);
            return;
        }

        i += 5 + 3 + 4 + tagLen;
        //printf("%llu", i);


    }
    printf("Undefind behavour");
    exit(1);

}

void setLine(char* fileName, char* tag, char* val){
    FILE *track = fopen(fileName, "rb+");
    long long metadataLength = 0;
    long long ten = 256 * 256 * 256;
    fseek(track, 6, SEEK_SET);
    for (int i = 0; i < 4; ++i) {
        int tmp = fgetc(track);
        metadataLength += tmp * ten;
        ten = ten / 256;
    }

    fseek(track, 10, SEEK_SET);
    long long i = 10;
    while (i < metadataLength) {
        char name[4] = {0, 0, 0, 0};
        fgets(name, 5, track);
        if (name[0] == 0 && name[1] == 0 && name[2] == 0 && name[3] == 0) {
            break;
        }

        long long tagLen = 0;
        long long mulTen = 256 * 256 * 256;

        for (int j = 0; j < 4; ++j) {
            int temp = fgetc(track);
            tagLen += temp * mulTen;
            mulTen = mulTen / 256;
        }

        if (i + tagLen + 12 >= metadataLength) {
            break;
        }

        fseek(track, 3, SEEK_CUR);
        int flag = 0;
        if (!strcmp(name, tag)) {
            fwrite(val, 1, sizeof(val), track);
            return;
        }
        char string[tagLen];
        fgets(string, tagLen, track);


        i += 5 + 3 + 4 + tagLen;
        //printf("%llu", i);


    }
    printf("Undefind behavour");
    exit(1);
}

int main(int argc, char *argv[]) {

    setlocale(LC_ALL, "Russian");
    if (argc < 2) {
        printf("Undefind behavour");
        return 1;
    } else {
        int show = 0, get = 0, set = 0;
        char fileName[256];
        for (int i = 0; i < 256; ++i) fileName[i] = 0;
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "--show") == 0) {
                show = 1;
            }
            if (strstr(argv[i], "--get") != NULL) {
                get = 1;
            }
            if (strstr(argv[i], "--set") != NULL) {
                set = 1;
            }
        }
        char filpath[100];
        strcpy(filpath, argv[1]);
        int j = 0;
        while (filpath[j++] != '=') {

        }
        int p = 0;
        for (int i = j; argv[1][i]; ++i) {
            fileName[p++] = argv[1][i];
        }

        if (show) {
            showInfo(fileName);
        }
        if (get) {
            char value[100];
            for (int i = 0; i < 100; ++i) value[i] = 0;
            char filpath[100];
            strcpy(filpath, argv[2]);
            int j = 0;
            while (filpath[j++] != '=') {

            }
            int p = 0;
            for (int i = j; argv[2][i]; ++i) {
                value[p++] = argv[2][i];
            }
            getLine(fileName, value);
        }
        if (set){
            char tag[100], val[100];
            for (int i = 0; i < 100; ++i) {
                tag[i] = 0;
                val[i] = 0;
            }
            for (int i = 0; i < argc; ++i){
                if (strstr(argv[i], "--set") != NULL){
                    int p = 0;
                    for (int j = 6; argv[i][j]; j++){
                        tag[p++] = argv[i][j];
                    }
                }
                if (strstr(argv[i], "--value") != NULL){
                    int p = 0;
                    for (int j = 8; argv[i][j]; j++){
                        val[p++] = argv[i][j];
                    }
                }
            }

            setLine(fileName, tag, val);
        }
    }

    return 0;
}