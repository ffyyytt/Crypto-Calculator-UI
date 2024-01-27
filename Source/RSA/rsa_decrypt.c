#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

void rsa_decrypt(mpz_t message, mpz_t cipher, mpz_t n, mpz_t d) {
    mpz_powm(message, cipher, d, n); // message = cipher^d mod n
}

int main(int argc, char *argv[]) {
    mpz_t p, q, n, d, message, cipher;
    mpz_inits(p, q, n, d, message, cipher, NULL);

    // Read private key (p, q, n, d) from file
    FILE *priv_key_file = fopen(argv[1], "r");
    if (priv_key_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    gmp_fscanf(priv_key_file, "%Zd\n%Zd\n%Zd\n%Zd\n", p, q, n, d);
    fclose(priv_key_file);

    // printf("Enter the encrypted number: ");
    // gmp_scanf("%Zd", cipher);
    if (mpz_set_str(cipher, argv[2], 10) != 0) {
    // Handle error: the function returns non-zero if the string is not a valid number
        perror("Error to assign message");
        return 1;
    } 
    // Decrypt the message
    rsa_decrypt(message, cipher, n, d);

    gmp_printf("Decrypted message: %Zd\n", message);

    mpz_clears(p, q, n, d, message, cipher, NULL);
    return 0;
}

