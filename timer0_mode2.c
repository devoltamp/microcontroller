/* ref.
 * https://www.geeksforgeeks.org/electronics-engineering/8051-timers-and-counters/ */
#include <stdio.h>
#include <reg51.h>

sbit mosfet = 0x90;

/* interrupt service routine
 * TF0's auto reload so, if this line is nto written that's fine
 */
void timer0_isr() interrupt 1 {
    TF0 = 0;
    mosfet =~ mosfet;
}

/* EA - enable all &
 * ET0 - enables the timer 0
 * M1, 0 - mode selection bits (mode - 2; M0 = 1; M1 = 0)
 */
void main(){

    EA = 1;
    ET0 = 1;
    P1 = 0x90;
    TMOD = 0x02;    /* 10 - tha's why two */

    TH0 = 0x9C;     /* for 100 counts (256-100 = 156 = 9C = 100111100) */
    TL0 = 0x9C;     /* same */
    TR0 = 1;        /* to run the timer */

    while(1){
        ;
    }
}

/* note;
 * - change the xtal's freq. - 12MHz
 * as the timer will reach FD to FF -- it'll set the flag
 * & the mosfet will be toggled
 * so, in the logic analyzer can be seened
 * & in the peripherals open up the ports and all
 */
