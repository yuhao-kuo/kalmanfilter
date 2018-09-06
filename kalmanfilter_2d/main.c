
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include "kalman.h"

#define ARRAR_SIZE(arr)     (sizeof(arr)/sizeof(arr[0]))

struct option long_option[] = {
    { "input",         1, NULL, 'i' },
    { "output",        1, NULL, 'o' },
    { "show",          0, NULL, 's' },
    { "help",          0, NULL, 'h' },
    { 0,               0,    0,  0  },
};

char short_option[] = "i:o:sh";

int main(int argc, char *argv[])
{
    FILE *pf, *pof;
    int c = 0;
    char *input_path = (char *)NULL;
    char *output_path = (char *)NULL;
    Kalman_t kalmanobj;
    bool show = false;
    uint16_t a = 0, b = 0;
    uint16_t *pNumber;
    char value;
    char number[10];
    char *ptr;
    uint16_t nextline = 0;
    uint32_t count = 0;
    double answser = 0;

    while((c = getopt_long(argc, argv, short_option, long_option, NULL)) != -1) {
        switch(c) {
            case 'i':   // 來源資料資料
                input_path = optarg;
                break;
            case 'o':   // 輸出資料
                output_path = optarg;
                break;
            case 's':   // 顯示在螢幕上
                show = true;
                break;
            case 'h':   // 使用說明
            default:
                printf("help");
                return EXIT_SUCCESS;
        }
    }

    if(input_path == NULL) {
        printf("not input data!!\n");
        return EXIT_FAILURE;
    }

    kalmanInit(&kalmanobj);

    pf = fopen(input_path, "r");
    if(pf == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    if(output_path != NULL) {
        pof = fopen(output_path, "w+");
        if(pof == NULL) {
            perror("fopen");
            return EXIT_FAILURE;
        }
    }

    
    // 讀取檔案
    while((value = fgetc(pf)) != EOF) {
        if(value == '\n') {
            continue;
        }
        
        if(value != ',') {
            number[nextline] = value;
            nextline++;
        } else {
            if(nextline != 0) {
                switch(number[0]) {
                    case 'A':
                        pNumber = &a;
                        break;
                    case 'L':
                        pNumber = &b;
                        break;
                }
                
                ptr = strchr(number, '=');
                ptr++;

                if(ptr != NULL) {
                    *pNumber = (unsigned int)atoi(ptr);   // char to int
                    if(a != 0 && b != 0) {
                        answser = kalmanfilter(&kalmanobj, a, b);
                        if(show == true) {
                            printf("%d\t%u\t%u\t%f\n", count, a, b, answser);
                        }
                        if(output_path != NULL) {
                            fprintf(pof, "%d\t%u\t%u\t%f\n", count, a, b, answser);
                        }
                        a = 0;
                        b = 0;
                        count++;
                    }
                }
            }
            memset(number, '\0', ARRAR_SIZE(number));
            nextline = 0;
        }
    }

    fclose(pf);
    if(output_path != NULL) {
        fclose(pof);
    }


    return EXIT_SUCCESS;
}