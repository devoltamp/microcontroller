/* 4x4 -- keypad */
#include <reg51.h>
#include <stdio.h>

sbit C_0 = P2^0;
sbit C_1 = P2^1;
sbit C_2 = P2^2;
sbit C_3 = P2^3;
sbit r_0 = P1^0;
sbit r_1 = P1^1;
sbit r_2 = P1^2;
sbit r_3 = P1^3;

unsigned char x, y;
unsigned char s_w_no;

void row_scan(void) {
    P1 = 0x0F;
    P2 = 0x00;
    x = (~P1) & 0x0F;
}

void column_scan(void) {
    P2 = 0x0F;
    P1 = 0x00;
    y = (~P2) & 0x0F;
}

void action(void) {
    if (x == 1){
        x = x - 1;
    }
    else{
        x = x >> 1;
    }
    if (y == 1){
        y = y - 1;
    }
    else{
        y = y >> 1;
    }

    s_w_no = (4 * x) + y + 1;
    /* cases */
    switch (s_w_no) {
        case 1:
            break;
        case 2:
            break;
        /* ... */
        case 16:
            break;
        default:
            break;
    }
}

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

void main(void) {
    while (1) {
        row_scan();
        column_scan();

        /* if a key is pressed (either row or col registered a value) */
        if (x != 0 && y != 0) {
            action();
            delay_ms(200);
        }
    }
}
