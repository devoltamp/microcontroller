/* code is still broken */
#include <reg51.h>
#include <stdio.h>

/* counts are calculated accordingly */
unsigned int lowcount = 49995;
unsigned int highcount = 5250;

sbit led1 = P1^0;
sbit led2 = P1^1;

bit INT_NO = 0;
bit measure = 0;
bit invalid_speed = 0;
void lcd_display(float m);  /* gotta write it later */

void ex0_isr() interrupt 0 {
    if (INT_NO == 0){
        TR0 = 1;            /* to start the timer */
        INT_NO =~ INT_NO;   /* to toggle the flag */
    }
    else{
        TR0 = 0;
        INT_NO =~ INT_NO;
        measure = 1;
    }
} /* †(1) */

void timer0_isr() interrupt 1 {
    invalid_speed = 1;
    TR0 = 0;            /* to stop timer */
    TL0, TH0 = 0x00;
    INT_NO = 0;         /* if not done the event will slip out */
    measure = 0;
} /* †(2) */

void measurespeed(){

    unsigned int x;
    float actual_speed;
    float multi_factor;

    x = (TH0 << 8) + TL0;
    if (x < lowcount){
        led1 = 1;
        led2 = 0;
    }
    else if (x < highcount){
        led1 = 0;
        led2 = 0;
    }
    else{
        actual_speed = (float)x * multi_factor;
        lcd_display(actual_speed);
    }
}

void main(){

    EA = 1;
    EX0 = 1;
    ET0 = 1;
    TMOD = 0x05;
    IT0 = 1;        /* to make it edge triggered */

    while (1){

        led1, led2 = 0;
        if (measure == 1 && invalid_speed == 0){
            measurespeed();
            measure = 0;
        }
    }
}

/* note;
 *
 * - TMOD value
 * gate | C/Ŧ | M1 | M0
 *   0  |  1  |  0 |  1 >> meaning 0x05
 * C/Ŧ is set to operate timer 0 in counter mode M1 M0 - 0 1 to enable 16 bit timer
 * (rest everything is zero no need to explicitly make them zero)
 *
 * †(1)
 * pulses on T0 pin is allowed to reach TH0:TL0,
 * so content will increase on each new pulse
 * - TF0 is autoclear so no need to write
 *
 * †(2)
 * shit related to the T0, will it overflow if not then what's the point?
 * S1 ----------------------------- S2
 * if the speed is too slow, then the counter will overflow
 *
 * †(others)
 *
 */
