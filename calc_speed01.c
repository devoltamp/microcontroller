#include <reg51.h>

/* LED connections */
sbit low_speed_led  = P1^0;
sbit high_speed_led = P1^1;

/* Flags */
bit count_ready = 0;
bit measuring = 0;
bit invalid_speed = 0;

unsigned int count;
unsigned int low_speed_threshold  = 50000;
unsigned int high_speed_threshold = 5000;
void calculate_display_speed(void);

void main(void)
{
    /* external interrupt 0 */
    IT0 = 1;        // INT0 edge triggered
    EX0 = 1;        // enable external interrupt 0

    /* timer 0 */
    TMOD = 0x05;    // Timer 0, Mode 1, external counter -- 16 bit
    ET0 = 1;        // enable Timer 0 overflow interrupt
    EA = 1;         // global interrupt enable
    TR0 = 0;        // counter initially OFF

    low_speed_led = 0;
    high_speed_led = 0;

    while (1){
        if (count_ready == 1){
            count_ready = 0;
            if (invalid_speed == 0){
                calculate_display_speed();
            }
            invalid_speed = 0;
        }
    }
}


/* --- External Interrupt 0 ISR; INT0 = P3.2 --- */
void ex0_isr(void) interrupt 0 {
    if (measuring == 0) {
        /* First pulse: start counting */
        TH0 = 0x00;
        TL0 = 0x00;

        TR0 = 1;
        measuring = 1;
    }
    else {
        /* Second pulse: stop counting */
        TR0 = 0;
        measuring = 0;
        count_ready = 1;
    }
}

/* --- Timer 0 Overflow ISR --- */
void tmr0_isr(void) interrupt 1
{
    TR0 = 0;

    invalid_speed = 1;
    measuring = 0;
    count_ready = 1;

    TH0 = 0x00;
    TL0 = 0x00;
}


/* --- calculate and display speed --- */
void calculate_display_speed(void){
    count = ((unsigned int)TH0 << 8) | TL0;

    /* Low speed */
    if (count >= low_speed_threshold){
        low_speed_led = 1;
        high_speed_led = 0;
    }
    /* High speed */
    else if (count <= high_speed_threshold){
        low_speed_led = 0;
        high_speed_led = 1;
    }
    /* Medium speed */
    else{
        low_speed_led = 0;
        high_speed_led = 0;
    }
}

/* note;
 * P3.3 toggle so the P1.0 will be toggled
 * https://chatgpt.com/share/6aa2ff75-4e3c-83e8-967d-d36b8f2be2f3
 */
