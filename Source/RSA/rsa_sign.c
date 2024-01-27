#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

void rsa_sign(mpz_t signature, mpz_t message, mpz_t d, mpz_t n) {
    mpz_powm(signature, message, d, n); // signature = message^d mod n
}

int main(int argc, char *argv[]) {
    mpz_t p, q, n, d, message, signature;
    mpz_inits(p, q, n, d, message, signature, NULL);

    // Read private key (p, q, n, d) from file
    FILE *priv_key_file = fopen(argv[1], "r");
    if (priv_key_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    gmp_fscanf(priv_key_file, "%Zd\n%Zd\n%Zd\n%Zd\n", p, q, n, d);
    fclose(priv_key_file);

    // printf("Enter a message (as a number) to sign: ");
    // gmp_scanf("%Zd", message);
    if (mpz_set_str(message, argv[2], 10) != 0) {
    // Handle error: the function returns non-zero if the string is not a valid number
        perror("Error to assign message");
        return 1;
    }   

    // Sign the message
    rsa_sign(signature, message, d, n);

    gmp_printf("Signature: %Zd\n", signature);

    mpz_clears(p, q, n, d, message, signature, NULL);
    return 0;
}

