#include <stdio.h>
#include <string.h>

#include "haffman.h"

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Function must have 3 arguments, but %d provided\n", argc-1);
    } else {
        if (strlen(argv[1]) > 1) {
            if (argv[1][0] == '-') {
                if (argv[1][1] == 'c') {
                    Compress(argv[2], argv[3]);
                } else if (argv[1][1] == 'd') {
                    Decompress(argv[2], argv[3]);
                } else {
                    printf("Unknown flag :\"%s\"\n", argv[1]);
                }
            } else {
                printf("Unknown parameter :\"%s\"\n", argv[1]);
            }
        }
    }
    //Compress("test.txt", "output.txt");
}
