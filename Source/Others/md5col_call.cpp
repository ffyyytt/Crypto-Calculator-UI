#include "md5.h"
#include "md5collgen.h"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {

    std::string prefixfn(argv[1]);
    std::string outfn1("out1.bin");
    std::string outfn2("out2.bin");
    std::string defaultIV("0123456789abcdeffedcba9876543210");
    md5collgen(prefixfn, outfn1, outfn2, defaultIV);
    std::cout << "Successful! Wrote output to out1.bin, out2.bin" << std::endl;
}
