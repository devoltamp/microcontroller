/* que;
 * measuring "three" analog voltages as input - using ADC0809 */
#include <reg51.h>
#include <stdio.h>

void setup();
void main_loop();
void delay();

sbit S0 = P1^0;
sbit S1 = P1^1;
sbit SOC = P1^2;
sbit OE = P1^3;
sbit EOC = P1^4;
sbit sample = P1^5;
sbit ALE = P1^6;

bit ov_no = 0;              /* overflow flag */
bit start_process = 0;      /* from the isr leading to while(1) */

unsigned int i;
unsigned char channel_no;
unsigned char x, y, z;

/* †(1) */
void timer0_isr() interrupt 1{
    TH0 = 0x3C;
    TL0 = 0xB0;

    if (ov_no == 1)
        start_process = 1;
    ov_no =~ ov_no;
}

void main(){

    setup();
    while (1){
        main_loop();
    }
}

void setup(){
    EA = 1;
    ET0 = 1;
    TMOD = 0x01;    /* 16-bit timer */
    EOC = 1;

    P2 = 0xFF;      /* as i/p */
    P1 = 0xFF;      /* not necessary, but still */

    TR0 = 1;
    TH0 = 0x3C;
    TL0 = 0xB0;
    sample = 0;
    SOC = 0;
    ALE = 0;
}

void delay(){
    for (i = 0; i < 6; i++){
        ;
    }
}

void main_loop(){

    start_process = 0;      /* reset the flag */
    /* -------------------------------------- */
    sample = 1;
    delay();
    sample = 0;

    switch (channel_no){
        case '0':
            S0 = 0;
            S1 = 0;
            // S2 = 0; -- by default zero, cause of the combination

            ALE = 1;
            delay();
            ALE = 0;    /* short duration "HIGH" pulse & the channels will be selected */

            SOC = 1;
            delay();
            SOC = 0;    /* short duration "HIGH" pulse so the conversion will be started */

            /* .... waiting for 0.415s max,
            for the EOC to come */

            while (EOC == 1){
                OE = 0;
                delay();
                OE = 1;     /* short duration "LOW" pulse */

                // & with that, result is ready
                x = P2;
                break;
            }
        case '1':
            /* same thing */
            S0 = 1;
            S1 = 0;

            ALE = 1;
            delay();
            ALE = 0;

            SOC = 1;
            delay();
            SOC = 0;

            /* .... waiting for 0.415s max,
            for the EOC to come */

            while (EOC == 1){
                OE = 0;
                delay();
                OE = 1;

                // & with that, result is ready
                y = P2;
                break;
            }
        case '2':
            /* same thing */
            S0 = 0;
            S1 = 1;

            ALE = 1;
            delay();
            ALE = 0;

            SOC = 1;
            delay();
            SOC = 0;

            while (EOC == 1){
                OE = 0;
                delay();
                OE = 1;
                // & with that, result is ready
                z = P2;
                break;
            }
        case default:
            break;
    }
}

/* notes;
 * ------
 *
 * †(1)
 * how the values of the TH0 & TL0 is calculated,
 * 0.1 sec = 100ms = 50 + 50ms
 * 50ms = 50,000 us --> so, max #n is 65536
 * 65536 - 50000 = 15536
 * & convert that number into HEX (0x3CB0)
 * & also giving in TH0 & TL0
 *
 * -> ov_no = 0; so,
 *   0  -  1  -  0  -  1
 * -----|-----|-----|-----
 * 50ms | 50ms| ..
 * & according to that the 0.1 sec delay is achieved
 *
 * †(2)
 * i couldn't think of anything else to write down
 */
