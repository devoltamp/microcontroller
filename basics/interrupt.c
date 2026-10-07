#include <stdio.h>
#include <reg51.h>

/* def'n of sensors & leds */
sbit s1 = P3^2;
sbit s2 = P3^3;
sbit l1 = P2^1;
sbit l2 = P2^2;

/* interrupt routines
 * as INT0 & INT1
 * the inter. #n's are given accordingly */
void sensor1() interrrupt 0 {
    l1 = 1;
}

void sensor2() interrupt 2 {
    l2 = 1;
}

void main(){

    /* look at the IE diagram and see the pins being high
     * & binary is also fine to write there */
    IE = 0x85;
    while(1){
        ;
    }
}

/* main thing is that in while there's nothing
 * the interrupt will be done on its own that's great */
