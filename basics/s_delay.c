#include <stdio.h>
#include <reg51.h>

void _delay(){
    unsigned int x, y = 0;
    for (; x <= 10; x++){
        y++;
    }
}
/* 2^16 -- a lot of time 
for 10 time ~ 0.000281s */

void main(void){
	
    unsigned char portdata;
    P1 = 0xFF;
    while(1){
        portdata = 0x0F;
        _delay();
        P1 = portdata;
    }
}
