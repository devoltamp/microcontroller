/* 12794 --> {1, 2, 7, 9, 4} */
#include <reg51.h>

unsigned char result_seg[5] = {0, 0, 0, 0, 0};
unsigned int my_n = 12794;

void seg_my_n(unsigned int x);
unsigned int my_pow(unsigned int x2, unsigned int x3);

void main(void){
    while (1){
        seg_my_n(my_n);
    }
}

void seg_my_n(unsigned int x){
    unsigned int temp = x;
    unsigned int z;
    unsigned char i;
    unsigned char n = 4;            /* N - 1 where N = 5 digits */

    for (i = 0; i < 5; i++){
        z = my_pow(10, n);          /* 10^4, 10^3, 10^2, 10^1, 10^0 */
        result_seg[i] = temp / z;   /* Extract leftmost digit */
        temp = temp % z;            /* Remove extracted digit */
        n--;
    }
}

unsigned int my_pow(unsigned int x2, unsigned int x3){
    unsigned int result = 1;[cite: 13, 16]
    unsigned char j;

    for (j = 1; j <= x3; j++)
    {
        result *= x2;               /* result = result * 10 */
    }
    return result;
}
