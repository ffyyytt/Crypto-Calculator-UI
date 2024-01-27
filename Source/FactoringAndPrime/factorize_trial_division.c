#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trial_division(mpz_t factor, mpz_t n, int max_seconds) {
    if (mpz_cmp_ui(n, 1) == 0 || mpz_cmp_ui(n, 0) == 0) {
        mpz_set_ui(factor, 0);
        return;
    }

    mpz_t i, sqrt_n;
    mpz_init_set_ui(i, 2);
    mpz_init(sqrt_n);
    mpz_sqrt(sqrt_n, n);

    time_t start_time = time(NULL);
    time_t current_time;
    int elapsed_seconds = 0;

    while (mpz_cmp(i, sqrt_n) <= 0) {
        current_time = time(NULL);
        elapsed_seconds = (int)difftime(current_time, start_time);

        if (elapsed_seconds >= max_seconds) {
            mpz_set_ui(factor, 0); // Timeout, no factor found
            break;
        }

        if (mpz_divisible_p(n, i)) {
            mpz_set(factor, i);
            mpz_clears(i, sqrt_n, NULL);
            return;
        }
        mpz_add_ui(i, i, 1);
    }

    mpz_set_ui(factor, 0); // No factor found
    mpz_clears(i, sqrt_n, NULL);
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

    trial_division(factor, n, 30); // Set a 30-second timer

    if (mpz_cmp_ui(factor, 0) == 0) {
        printf("No small factors found within 30 seconds.\n");
    } else {
        gmp_printf("A small factor: %Zd\n", factor);
    }

    mpz_clears(n, factor, NULL);
    return 0;
}

