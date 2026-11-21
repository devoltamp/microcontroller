/* 12379.5973 */
#include <reg51.h>

unsigned char result[9];    /* Stores 5 integer digits + 4 fractional digits */

unsigned int my_pow(unsigned int base, unsigned char exp) {
    unsigned int res = 1;
    unsigned char j;
    for (j = 1; j <= exp; j++) {
        res *= base;
    }
    return res;
}

void separate_digit(float *my_number2, unsigned char precision) {
    long N1;                /* Use long so numbers > 32767 don't overflow signed int */
    float N2;
    unsigned int z;
    unsigned char i, j;
    unsigned char n = 4;    /* 5 integer digits -> start at 10^4 */

    /* 1. Split integer (N1) and fractional (N2) parts */
    N1 = (long)(*my_number2);           /* N1 = 12379 */
    N2 = (*my_number2) - (float)N1;     /* N2 = 0.5973 */

    /* 2. Segregate integer digits into result[0..4] */
    for (i = 0; i < 5; i++) {
        z = my_pow(10, n);
        result[i] = (unsigned char)(N1 / z);
        N1 = N1 % z;
        n--;
    }

    /* 3. Segregate fractional digits into result[5..8] */
    for (j = 0; j < precision; j++) {
        N2 = N2 * 10.0;
        result[j + 5] = (unsigned char)N2;
        N2 = N2 - (float)result[j + 5]; /* Remove extracted integer digit */
    }
}

void main(void) {
    float my_n = 12379.5973;
    unsigned char precision = 4;

    separate_digit(&my_n, precision);   /* result = {1, 2, 3, 7, 9, 5, 9, 7, 3} */

    while (1) {
        ;
    }
}
