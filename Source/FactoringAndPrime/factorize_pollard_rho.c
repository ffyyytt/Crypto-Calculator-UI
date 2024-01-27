#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void f(mpz_t result, mpz_t x, mpz_t n) {
    mpz_mul(result, x, x);
    mpz_add_ui(result, result, 1);
    mpz_mod(result, result, n);
}

void pollard_rho(mpz_t factor, mpz_t n, int max_seconds) {
    if (mpz_cmp_ui(n, 1) == 0 || mpz_cmp_ui(n, 0) == 0) {
        mpz_set_ui(factor, 0);
        return;
    }

    if (mpz_even_p(n)) {
        mpz_set_ui(factor, 2);
        return;
    }

    mpz_t x, y, d, abs_diff;
    mpz_inits(x, y, d, abs_diff, NULL);
    mpz_set_ui(x, 2);
    mpz_set_ui(y, 2);
    mpz_set_ui(d, 1);

    time_t start_time = time(NULL);
    time_t current_time;
    int elapsed_seconds = 0;

    while (mpz_cmp_ui(d, 1) == 0) {
        f(x, x, n);
        f(y, y, n);
        f(y, y, n);
        mpz_sub(abs_diff, x, y);
        mpz_abs(abs_diff, abs_diff);
        mpz_gcd(d, abs_diff, n);

        current_time = time(NULL);
        elapsed_seconds = (int)difftime(current_time, start_time);

        if (elapsed_seconds >= max_seconds) {
            mpz_set_ui(factor, 0); // Timeout, no factor found
            break;
        }

        printf("\rTime elapsed: %d seconds", elapsed_seconds);
        fflush(stdout);
    }

    if (mpz_cmp(d, n) != 0 && mpz_cmp_ui(d, 0) != 0 && mpz_cmp_ui(d, 1) != 0) {
        mpz_set(factor, d);
    } else {
        mpz_set_ui(factor, 0); // Failure to find a factor
    }

    printf("\n");
    mpz_clears(x, y, d, abs_diff, NULL);
}

int main(int argc, char *argv[]) {
    mpz_t n, factor;
    mpz_inits(n, factor, NULL);

    // printf("Enter the number to factorize: ");
    // gmp_scanf("%Zd", n);

    if (mpz_set_str(n, argv[1], 10) != 0) {
    // Handle error: the function returns non-zero if the string is not a valid number
        perror("Error to assign number");
        return 1;
    }   

    pollard_rho(factor, n, 30); // Set a 30-second timer

    if (mpz_cmp_ui(factor, 0) == 0) {
        printf("Failed to find a nontrivial factor within 30 seconds.\n");
    } else {
        gmp_printf("A nontrivial factor: %Zd\n", factor);
    }

    mpz_clears(n, factor, NULL);
    return 0;
}

