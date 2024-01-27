#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

void rsa_encrypt(mpz_t cipher, mpz_t message, mpz_t n, mpz_t e) {
    mpz_powm(cipher, message, e, n); // cipher = message^e mod n
}

int main(int argc, char *argv[]) {
    mpz_t n, e, message, cipher;
    mpz_inits(n, e, message, cipher, NULL);

    // Read public key (n, e) from file
    FILE *key_file = fopen(argv[1], "r");
    if (key_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    gmp_fscanf(key_file, "%Zd\n%Zd\n", n, e);
    fclose(key_file);

    // printf("Enter a number to encrypt: ");
    // gmp_scanf("%Zd", message);
    if (mpz_set_str(message, argv[2], 10) != 0) {
    // Handle error: the function returns non-zero if the string is not a valid number
        perror("Error to assign message");
        return 1;
    }   

    // Encrypt the message
    rsa_encrypt(cipher, message, n, e);

    gmp_printf("Encrypted message: %Zd\n", cipher);

    mpz_clears(n, e, message, cipher, NULL);
    return 0;
}

