#define _CRT_SECURE_NO_WARNINGS
#include "md5.h"
#include "sha1.h"
#include "sha2.h"
#include "base64.h"
#include "md5collgen.h"
#include "LengthExtensionAttack.h"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
        char output[200];
        int mode =atoi(argv[1]);
        
        if(mode == 0){
            md5 h;
            uint8 digest[h.DIGEST_SIZE+1];
            md5::hexToBytes(argv[2], 2 * h.DIGEST_SIZE, digest);
            uint8 outputLEA[h.DIGEST_SIZE+1];
            LengthExtensionAttack::hashLengthExtensionAttack(h, (unsigned char*)digest, (unsigned char*)argv[3], strlen(argv[3]), outputLEA);
            Hash::bytesToHex(outputLEA, h.getDigestSize(), output);
            std::cout << output << std::endl;
        }
                        
        else if(mode == 1){
            sha1 h;
            uint8 digest[h.DIGEST_SIZE+1];
            md5::hexToBytes(argv[2], 2 * h.DIGEST_SIZE, digest);
            uint8 outputLEA[h.DIGEST_SIZE+1];
            LengthExtensionAttack::hashLengthExtensionAttack(h, (unsigned char*)digest, (unsigned char*)argv[3], strlen(argv[3]), outputLEA);
            Hash::bytesToHex(outputLEA, h.getDigestSize(), output);
            std::cout << output << std::endl; 
        }

        else if(mode == 2){
            sha256 h; //sha512 h;
            uint8 digest[h.DIGEST_SIZE+1];
            md5::hexToBytes(argv[2], 2 * h.DIGEST_SIZE, digest);
            uint8 outputLEA[h.DIGEST_SIZE+1];
            LengthExtensionAttack::hashLengthExtensionAttack(h, (unsigned char*)digest, (unsigned char*)argv[3], strlen(argv[3]), outputLEA);
            Hash::bytesToHex(outputLEA, h.getDigestSize(), output);
            std::cout << output << std::endl;
        }

        else {
            sha512 h;
            uint8 digest[h.DIGEST_SIZE+1];
            md5::hexToBytes(argv[2], 2 * h.DIGEST_SIZE, digest);
            uint8 outputLEA[h.DIGEST_SIZE+1];
            LengthExtensionAttack::hashLengthExtensionAttack(h, (unsigned char*)digest, (unsigned char*)argv[3], strlen(argv[3]), outputLEA);
            Hash::bytesToHex(outputLEA, h.getDigestSize(), output);
            std::cout << output << std::endl; 
        }

    return 0;
}