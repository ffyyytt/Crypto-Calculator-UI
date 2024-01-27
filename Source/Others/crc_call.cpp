#include "md5.h"
#include "crc.h"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
    char *msg;
    msg = (char*)malloc(256*sizeof(char));
    char output[200];
    memcpy(msg, argv[1], strlen(argv[1]));
    //std::cout << msg << " ---------- " << strlen(msg) << std::endl;
    
    std::cout << crc::crc32buf(msg, strlen(msg)) << std::endl;

    free(msg);
}