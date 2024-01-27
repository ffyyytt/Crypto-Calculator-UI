#include "sha1.h"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
    char *msg;
    msg = (char*)malloc(256*sizeof(char));
    char output[200];
    memcpy(msg, argv[1], strlen(argv[1]));
    //std::cout << msg << " ---------- " << strlen(msg) << std::endl;

    sha1 sha1_ctx;
    uint8 sha1sum[sha1::DIGEST_SIZE];
    sha1_ctx.init();
    sha1_ctx.update((uint8*)msg, strlen(msg));
    sha1_ctx.final(sha1sum);
    Hash::bytesToHex(sha1sum, sha1::DIGEST_SIZE, output);
    std::cout << output << std::endl;

    free(msg);
}