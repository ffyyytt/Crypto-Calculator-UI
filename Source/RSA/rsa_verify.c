#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

void rsa_verify(mpz_t computed_message, mpz_t signature, mpz_t e, mpz_t n) {
    mpz_powm(computed_message, signature, e, n); // computed_message = signature^e mod n
}

int main(int argc, char *argv[]) {
    mpz_t n, e, message, signature, computed_message;
    mpz_inits(n, e, message, signature, computed_message, NULL);

    // Read public key (n, e) from file
    FILE *pub_key_file = fopen(argv[1], "r");
    if (pub_key_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    gmp_fscanf(pub_key_file, "%Zd\n%Zd\n", n, e);
    fclose(pub_key_file);

    // printf("Enter the original message (as a number): ");
    // gmp_scanf("%Zd", message);

    // printf("Enter the signature: ");
    // gmp_scanf("%Zd", signature);
    if (mpz_set_str(message, argv[2], 10) != 0) {
    // Handle error: the function returns non-zero if the string is not a valid number
        perror("Error to assign message");
        return 1;
    }

    if (mpz_set_str(signature, argv[3], 10) != 0) {
    // Handle error: the function returns non-zero if the string is not a valid number
        perror("Error to assign signature");
        return 1;
    }      

    // Verify the signature
    rsa_verify(computed_message, signature, e, n);

    // Check if the computed message matches the original message
    if (mpz_cmp(computed_message, message) == 0) {
        printf("Signature is valid.\n");
    } else {
        printf("Signature is invalid.\n");
    }

    mpz_clears(n, e, message, signature, computed_message, NULL);
    return 0;
}

