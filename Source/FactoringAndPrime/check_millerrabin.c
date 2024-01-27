#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

// Function to perform the Miller-Rabin primality test
int miller_rabin(mpz_t n, int rounds) {
    if (mpz_cmp_ui(n, 2) < 0) return 0;
    if (mpz_cmp_ui(n, 2) == 0) return 1;
    if (mpz_even_p(n)) return 0;

    mpz_t r, s, a, y, j, n_minus_one;
    mpz_inits(r, s, a, y, j, n_minus_one, NULL);

    // Write n - 1 as 2^s * r
    mpz_sub_ui(n_minus_one, n, 1);
    mpz_set(r, n_minus_one);
    mpz_set_ui(s, 0);

    while (mpz_even_p(r)) {
        mpz_fdiv_q_2exp(r, r, 1);
        mpz_add_ui(s, s, 1);
    }

    gmp_randstate_t state;
    gmp_randinit_default(state);

    for (int i = 0; i < rounds; ++i) {
        mpz_urandomm(a, state, n_minus_one);
        mpz_add_ui(a, a, 1);
        mpz_powm(y, a, r, n);

        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, n_minus_one) != 0) {
            mpz_set_ui(j, 1);
            while (mpz_cmp(j, s) < 0 && mpz_cmp(y, n_minus_one) != 0) {
                mpz_powm_ui(y, y, 2, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(r, s, a, y, j, n_minus_one, NULL);
                    gmp_randclear(state);
                    return 0;
                }
                mpz_add_ui(j, j, 1);
            }

            if (mpz_cmp(y, n_minus_one) != 0) {
                mpz_clears(r, s, a, y, j, n_minus_one, NULL);
                gmp_randclear(state);
                return 0;
            }
        }
    }

    mpz_clears(r, s, a, y, j, n_minus_one, NULL);
    gmp_randclear(state);
    return 1;
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

    int is_prime = miller_rabin(n, rounds);
    if (is_prime) {
        printf("%s is probably prime.\n", argv[1]);
    } else {
        printf("%s is not prime.\n", argv[1]);
    }

    mpz_clear(n);
    return 0;
}

