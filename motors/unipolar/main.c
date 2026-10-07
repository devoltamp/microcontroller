#include <reg51.h>

sbit dir_pie = P2^0;    /* 0 = forward, 1 = reverse */

unsigned char sw_seq[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
unsigned char p, n = 0, i;

void modify_n();
void my_delay();

void main() {
    dir_pie = 1;    /* as input */
    P1 = 0x00;      /* as output -- four wires for motor */

    while (1) {
        for (i = 0; i <= 7; i++) {
            P1 = sw_seq[n];
            modify_n();
            my_delay();
        }
    }
}

/* ?? */
void my_delay() {
    unsigned int j;
    for (j = 0; j < 20; j++);
}

/* modifies the index 'n' based on direction pin dir_pie */
void modify_n() {
    if (dir_pie == 0) {
        /* forward direction (increment index) */
        n++;
        if (n >= 8) {
            n = 0;
        }
    }
    else {
        /* reverse direction (decrement index) */
        if (n == 0) {
            n = 7;
        } else {
            n--;
        }
    }
}
