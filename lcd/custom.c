/* broken code */
#include <reg51.h>
#include <intrins.h>            /* For _nop_() intrinsic */

/* LCD Control Pins on Port 2 */
sbit rs = P2^0;                 /* Data / Command (Register Select) */
sbit rw = P2^1;                 /* Read (1) / Write (0) */
sbit cs = P2^4;                 /* Enable / Chip Select */

/* LCD 8-bit Data Bus on Port 0 (SFR 0x80) */
sfr lcdbus = 0x80;

/* System Timer Counters (decremented in 10 ms Timer ISR) */
volatile unsigned int sys_10ms_counter;
volatile unsigned char sys_1init_counter;

/* Custom 5x8 CGRAM Character Patterns (8 bytes each) */
unsigned char pat1[8] = {0x00, 0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x1F};
unsigned char pat2[8] = {0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00};
unsigned char pat3[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
unsigned char pat4[8] = {0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09};

/* LCD Status & Display State Variables */
unsigned char dx, lcdcounter;
bit lcdusing1, lcdusing2;

/* Short No-Operation Delay */
void soft_no(void) {
    _nop_();
}

/* Software ~10 ms Delay */
void soft_10ms(void) {
    register int i;
    for (i = 0; i < 711; i++) {
        ;
    }
}

/* Software ~20 ms Delay */
void soft_20ms(void) {
    soft_10ms();
    soft_10ms();
}

/* Hardware Timer-Based Delay (multiples of 10 ms) */
void hard_10ms(unsigned int delaytime) {
    sys_10ms_counter = delaytime;
    while (sys_10ms_counter) {
        ;
    }
}

/* Read LCD Busy Flag (DB7 / 0x80): returns 1 if busy, 0 if ready */
bit lcd_checkbusy(void) {
    register unsigned char lcdstate;

    lcdbus = 0xFF;              /* Configure Port 0 as input before reading */
    rs = 0;                     /* Command/status register */
    rw = 1;                     /* Read mode */
    cs = 1;                     /* Enable LCD read */

    soft_no();                  /* Small setup delay */

    lcdstate = lcdbus;          /* Read status byte */
    cs = 0;                     /* Disable LCD */

    return (bit)(lcdstate & 0x80);  /* Mask DB7 busy flag */
}
