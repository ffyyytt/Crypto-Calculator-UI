#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// A simplified version of the ECM algorithm
void ecm_factor(mpz_t factor, mpz_t n, int max_iterations) {
    // Check for even number
    if (mpz_even_p(n)) {
        mpz_set_ui(factor, 2);
        return;
    }

    mpz_t a, b, x, y, gcd, temp;
    gmp_randstate_t state;
    mpz_inits(a, b, x, y, gcd, temp, NULL);
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    for (int i = 0; i < max_iterations; ++i) {
        mpz_urandomm(a, state, n); // Random a in [0, n-1]
        mpz_set_ui(b, 1);
        mpz_set_ui(x, 0);
        mpz_set_ui(y, 1);

        // Simplified curve operation
        for (int j = 1; j <= 100; ++j) { // Fixed number of curve operations
            // Perform a curve operation (this is a simplification)
            mpz_mul(temp, x, x);
            mpz_submul_ui(temp, y, 2);
            mpz_add(temp, temp, a);
            mpz_mod(temp, temp, n);
            mpz_set(x, temp);

            // Check for factor
            mpz_gcd(gcd, x, n);
            if (mpz_cmp_ui(gcd, 1) > 0 && mpz_cmp(gcd, n) < 0) {
                mpz_set(factor, gcd);
                mpz_clears(a, b, x, y, gcd, temp, NULL);
                gmp_randclear(state);
                return;
            }
        }
    }

    mpz_set_ui(factor, 0); // No factor found
    mpz_clears(a, b, x, y, gcd, temp, NULL);
    gmp_randclear(state);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number to factorize>\n", argv[0]);
        return 1;
    }

    mpz_t n, factor;
    mpz_inits(n, factor, NULL);

    if (mpz_set_str(n, argv[1], 10) != 0) {
        fprintf(stderr, "Invalid number: %s\n", argv[1]);
        mpz_clears(n, factor, NULL);
        return 1;
    }

    ecm_factor(factor, n, 30); // Try 30 different curves

    if (mpz_cmp_ui(factor, 0) == 0) {
        printf("Failed to find a nontrivial factor.\n");
    } else {
        gmp_printf("A nontrivial factor: %Zd\n", factor);
    }

    mpz_clears(n, factor, NULL);
    return 0;
}


