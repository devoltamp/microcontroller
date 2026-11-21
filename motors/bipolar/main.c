#include <reg51.h>

unsigned char sw_seq[8] = {0x01, 0x05, 0x04, 0x06, 0x02, 0x0F, 0x08, 0x09};
sbit direction = P2^0;
unsigned char p, n = 0, i;

void modify_n(void);
void _delay(void);

void modify_n(void){
    if (direction == 0){
        n++;
        if (n == 8){
            n = 0;
        }
        if (n > 7){
            n = 0;
        }
    }
    else if (direction == 1){
        if (n == 0){
            n = 7;
        }
        else{
            n = n - 1;
        }
        if (n > 7){
            n = 7;
        }
    }
}

void _delay(void){
    for (p = 0; p <= 10; p++){
        ;
    }
}

void main(void){
    direction = 1;
    P1 = 0x00;

    while (1){
        for (i = 0; i <= 7; i++){
            P1 = sw_seq[n];
            modify_n();
            _delay();
        }
    }
}
