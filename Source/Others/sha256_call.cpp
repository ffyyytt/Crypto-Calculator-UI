#include "sha2.h"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
    char *msg;
    msg = (char*)malloc(256*sizeof(char));
    char output[200];
    memcpy(msg, argv[1], strlen(argv[1]));
    //std::cout << msg << " ---------- " << strlen(msg) << std::endl;
    
    sha256 h; //sha512 h;
    uint8 hsum[h.DIGEST_SIZE];
    h.init();
    h.update((uint8*)msg, strlen(msg));
    h.final(hsum);
    Hash::bytesToHex(hsum, h.getDigestSize(), output);
    std::cout << "sha256: " << output << std::endl;

    sha224 h1; //sha512 h;
    uint8 hsum1[h1.DIGEST_SIZE];
    h1.init();
    h1.update((uint8*)msg, strlen(msg));
    h1.final(hsum);
    Hash::bytesToHex(hsum1, h1.getDigestSize(), output);
    std::cout << "sha224: " << output << std::endl;

    sha512 h2; //sha512 h;
    uint8 hsum2[h2.DIGEST_SIZE];
    h2.init();
    h2.update((uint8*)msg, strlen(msg));
    h2.final(hsum);
    Hash::bytesToHex(hsum2, h2.getDigestSize(), output);
    std::cout << "sha512: " << output << std::endl;
    
    sha384 h3; //sha512 h;
    uint8 hsum3[h3.DIGEST_SIZE];
    h3.init();
    h3.update((uint8*)msg, strlen(msg));
    h3.final(hsum);
    Hash::bytesToHex(hsum3, h3.getDigestSize(), output);
    std::cout << "sha384: " << output << std::endl;

    free(msg);
}