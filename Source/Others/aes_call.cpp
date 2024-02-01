#include "aes.h"
#include "md5.h"
#include "base64.h"
//#include "LengthExtensionAttack.h"
#include <iostream>
#include <cstdint>

int main(int argc, char *argv[])
{
    // for(int i = 1; i <=7; ++i){
    //     std::cout << argv[i] << std::endl;
    // }
    char msg[1000];
    std::string ciphertext, key, iv;
    key = argv[1];
    int inputType = atoi(argv[7]);
    if(inputType == 1){
        std::string s(argv[1]);
        //std::cout << s << std::endl;
        if(strcmp(argv[3], "n/a")){
            std::string s2(argv[3]);
            //std::cout << s2 << std::endl;
            iv = base64().base64_decode(s2);
        }
        if(atoi(argv[6]) == 0){
            std::string s1(argv[2]);
            //std::cout << s1 << std::endl;
            strcpy(msg, base64().base64_decode(s1).c_str());
        }
        else{
            std::string s1(argv[2]);
            ciphertext = base64().base64_decode(s1);
        }
            
    }
    else{
        if(strcmp(argv[3], "n/a")){
            iv = argv[3];
        }
        if(atoi(argv[6]) == 0){
            strcpy(msg, argv[2]);
        }
        else{
            ciphertext = argv[2];
        }
    }

    int keyLength = atoi(argv[4]);
    //std::cout << keyLength << std::endl;
    
    

    int mode = atoi(argv[5]);
    //  Encryption
    if(keyLength == 0){
        AES aes(AESKeyLength::AES_128);
        if(atoi(argv[6]) == 0){
            std::cout << "Encryption mode 128" << std::endl;
            uint8* msgpad = AES::pkcs7_padding((uint8*)msg, strlen(msg));
            if(mode == 0){ //ECB
                uint8* aesoutput = aes.EncryptECB((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;
            }
            else if(mode == 1){ //CBC
                uint8* aesoutput = aes.EncryptCBC((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str(), (uint8*)iv.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;
            }
            else{   //CFB
                uint8* aesoutput = aes.EncryptCFB((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str(), (uint8*)iv.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;
            }
            
        }
        else{
            std::cout << "Decryption mode"  << std::endl;
            if(mode == 0){ //ECB
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptECB((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
            else if(mode == 1){ //CBC
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptCBC((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str(), (uint8*)iv.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
            else{   //CFB
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptCFB((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str(), (uint8*)iv.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
            
        }
    }


    else if(keyLength == 1){
        AES aes(AESKeyLength::AES_192);
        if(atoi(argv[6]) == 0){
            std::cout << "Encryption mode 192" << std::endl;
            uint8* msgpad = AES::pkcs7_padding((uint8*)msg, strlen(msg));
            if(mode == 0){ //ECB
                std::cout << "Hello" << std::endl;
                uint8* aesoutput = aes.EncryptECB((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;
            }
            else if(mode == 1){ //CBC
                uint8* aesoutput = aes.EncryptCBC((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str(), (uint8*)iv.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;
            }
            else{   //CFB
                std::cout << "Hello" << std::endl;
                uint8* aesoutput = aes.EncryptCFB((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str(), (uint8*)iv.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;

            }
            
        }
        else{
            std::cout << "Decryption mode"  << std::endl;
            if(mode == 0){ //ECB
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptECB((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
            else if(mode == 1){ //CBC
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptCBC((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str(), (uint8*)iv.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
            else{   //CFB
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptCFB((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str(), (uint8*)iv.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
            
        }
    }
    else{
        AES aes(AESKeyLength::AES_256);
        if(atoi(argv[6]) == 0){
            std::cout << "Encryption mode 256" << std::endl;
            uint8* msgpad = AES::pkcs7_padding((uint8*)msg, strlen(msg));
            if(mode == 0){ //ECB
                uint8* aesoutput = aes.EncryptECB((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;
            }
            else if(mode == 1){ //CBC
                uint8* aesoutput = aes.EncryptCBC((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str(), (uint8*)iv.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;
            }
            else{   //CFB
                uint8* aesoutput = aes.EncryptCFB((uint8*)msgpad, AES::pkcs7_padding_length(strlen(msg)), (uint8*)key.c_str(), (uint8*)iv.c_str());
                std::cout << base64().base64_encode(aesoutput, AES::pkcs7_padding_length(strlen(msg))) << std::endl;
            }
            
        }
        else{
            std::cout << "Decryption mode"  << std::endl;
            if(mode == 0){ //ECB
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptECB((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
            else if(mode == 1){ //CBC
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptCBC((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str(), (uint8*)iv.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
            else{   //CFB
                uint8* decrypted = AES::pkcs7_unpad(aes.DecryptCFB((uint8*)ciphertext.c_str(), ciphertext.length(), (uint8*)key.c_str(), (uint8*)iv.c_str()), ciphertext.length());
                std::cout << decrypted << std::endl;
            }
        }    
    }
}
