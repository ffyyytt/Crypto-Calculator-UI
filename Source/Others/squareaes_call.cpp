#include "aes.h"
#include "md5.h"
#include "base64.h"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
    
    int mode = atoi(argv[1]);
    if (mode == 0){
        AES squareAES(AESKeyLength::SQUARE);
        squareAES.generatePlainTextForSquareAttack(argv[2]);
        squareAES.EncryptListInFile(argv[2], "ciphertexts.txt", 16 * 256, (uint8*)argv[3]);
        std::cout << "Successful! Write ouput to ciphertexts.txt" << std::endl;
    }

    
    else if(mode == 1){
        unsigned char squarekey[] = "AAAAAAAAAAAAAAAA";
        AES::squareAttack(argv[2], squarekey);
        std::cout << "Attack successfully! \nKey: ";
        std::cout << squarekey << std::endl;
    }
    
}