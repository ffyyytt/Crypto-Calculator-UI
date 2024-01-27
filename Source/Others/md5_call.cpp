#include "md5.h"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
    char *msg;
    msg = (char*)malloc(256*sizeof(char));
    char output[200];
    memcpy(msg, argv[1], strlen(argv[1]));
    //std::cout << msg << " ---------- " << strlen(msg) << std::endl;

    md5 md5_ctx = md5();
    uint8 md5sum[md5::DIGEST_SIZE];
    md5_ctx.init();
    md5_ctx.update((uint8*)msg, strlen(msg));
    md5_ctx.final(md5sum);
    Hash::bytesToHex(md5sum, md5::DIGEST_SIZE, output);
    std::cout << output << std::endl;

    free(msg);
}