#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Generate a large prime number of 'num_bits' bits
void generate_large_prime(mpz_t prime, unsigned int num_bits, int mr_rounds) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL)); // Seed the random number generator

    while (1) {
        mpz_urandomb(prime, state, num_bits); // Generate a random number of 'num_bits' bits
        mpz_setbit(prime, num_bits - 1); // Ensure the number is of 'num_bits' bits
        mpz_setbit(prime, 0); // Ensure the number is odd

        // Check if the number is prime with a specified level of certainty
        if (mpz_probab_prime_p(prime, mr_rounds) > 0) {
            break; // The number is likely a prime
        }
    }

    gmp_randclear(state); // Clear the random state
}

void generate_rsa_keys(mpz_t n, mpz_t e, mpz_t d, mpz_t p, mpz_t q, unsigned int num_bits, int mr_rounds) {
    mpz_t phi_n, p_minus_one, q_minus_one;
    mpz_inits(phi_n, p_minus_one, q_minus_one, NULL);

    // Generate a large prime p
    generate_large_prime(p, num_bits, mr_rounds);

    // Generate a large prime q, different from p
    do {
        generate_large_prime(q, num_bits, mr_rounds);
    } while (mpz_cmp(p, q) == 0);
    
    // Print
    gmp_printf("Large primes (p, q): (%Zd, %Zd)\n", p, q);
    
    // Compute n = p * q
    mpz_mul(n, p, q);

    // Compute phi(n) = (p-1) * (q-1)
    mpz_sub_ui(p_minus_one, p, 1);
    mpz_sub_ui(q_minus_one, q, 1);
    mpz_mul(phi_n, p_minus_one, q_minus_one);

    // Compute d, the modular inverse of e modulo phi(n)
    if (!mpz_invert(d, e, phi_n)) {
        fprintf(stderr, "Error: e and phi(n) are not coprime\n");
        exit(1);
    }

    mpz_clears(phi_n, p_minus_one, q_minus_one, NULL);
}


int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <num_bits> <mr_rounds> <e>\n", argv[0]);
        return 1;
    }

    unsigned int num_bits = atoi(argv[1]);
    if (num_bits <= 1024) {
        fprintf(stderr, "Number of bits must be greater than 1024\n");
        return 1;
    }

    int mr_rounds = atoi(argv[2]);
    if (mr_rounds <= 25) {
        fprintf(stderr, "Number of Miller-Rabin rounds must be greater than 25\n");
        return 1;
    }

    mpz_t n, e, d, p, q;
    mpz_inits(n, e, d, p, q, NULL);

    mpz_set_str(e, argv[3], 10); // Set e to the value provided in the command line

    generate_rsa_keys(n, e, d, p, q, num_bits, mr_rounds);

    gmp_printf("Public Key (n, e): (%Zd, %Zd)\n", n, e);
    gmp_printf("Private Key (d): (%Zd)\n", d);

    FILE *key_file = fopen("public_key.txt", "w");
    if (key_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    gmp_fprintf(key_file, "%Zd\n%Zd\n", n, e);
    fclose(key_file);

    FILE *priv_key_file = fopen("private_key.txt", "w");
    if (priv_key_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    gmp_fprintf(priv_key_file, "%Zd\n%Zd\n%Zd\n%Zd\n", p, q, n, d);
    fclose(priv_key_file);

    gmp_printf("\nWrote to private_key.txt and public_key.txt\n");
    mpz_clears(n, e, d, p, q, NULL);
    return 0;
}

