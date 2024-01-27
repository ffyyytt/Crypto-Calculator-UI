#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Fermat's Primality Test
int fermat_test(mpz_t n, int rounds) {
    if (mpz_cmp_ui(n, 2) < 0) return 0;
    if (mpz_cmp_ui(n, 2) == 0) return 1;
    if (mpz_even_p(n)) return 0;

    mpz_t a, n_minus_one;
    mpz_inits(a, n_minus_one, NULL);
    mpz_sub_ui(n_minus_one, n, 1);

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    for (int i = 0; i < rounds; ++i) {
        mpz_urandomm(a, state, n_minus_one); // a in the range [1, n-1]
        mpz_add_ui(a, a, 1);

        mpz_powm(a, a, n_minus_one, n); // a^(n-1) mod n
        if (mpz_cmp_ui(a, 1) != 0) {
            mpz_clears(a, n_minus_one, NULL);
            gmp_randclear(state);
            return 0; // Composite
        }
    }

    mpz_clears(a, n_minus_one, NULL);
    gmp_randclear(state);
    return 1; // Probably prime
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <rounds>\n", argv[0]);
        return 1;
    }

    mpz_t n;
    mpz_init(n);
    if (mpz_set_str(n, argv[1], 10) != 0) {
        fprintf(stderr, "Invalid number: %s\n", argv[1]);
        mpz_clear(n);
        return 1;
    }

    int rounds = atoi(argv[2]);
    if (rounds <= 0) {
        fprintf(stderr, "Invalid number of rounds: %s\n", argv[2]);
        mpz_clear(n);
        return 1;
    }

    int is_prime = fermat_test(n, rounds);
    if (is_prime) {
        printf("%s is probably prime.\n", argv[1]);
    } else {
        printf("%s is not prime.\n", argv[1]);
    }

    mpz_clear(n);
    return 0;
}

