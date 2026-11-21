/* PCA Configuration for 8-Bit PWM & High-Speed Output */
#include <reg51.h>

/* PCA Special Function Registers (AT89C51RD2 / P89V51RD2) */
sfr CCON   = 0xD8;
sfr CMOD   = 0xD9;
sfr CL     = 0xE9;
sfr CH     = 0xF9;
sfr CCAPM0 = 0xDA;
sfr CCAP0L = 0xEA;
sfr CCAP0H = 0xFA;
sfr CCAPM1 = 0xDB;
sfr CCAP1L = 0xEB;
sfr CCAP1H = 0xFB;

sbit CR  = CCON^6;      /* PCA Counter Run bit */
sbit CCF1 = CCON^1;     /* Module 1 Compare/Capture Flag */

void pca_init(void) {
    CMOD = 0x00;        /* PCA clock = Fosc / 12, disable CF interrupt */
    CL = 0x00;
    CH = 0x00;

    /* Module 0 (P1.3): 8-Bit PWM Mode (25% Duty Cycle) */
    CCAPM0 = 0x42;      /* ECOM0 = 1, PWM0 = 1 */
    CCAP0L = 0xC0;      /* Duty cycle = (256 - 192) / 256 = 25% */
    CCAP0H = 0xC0;      /* Auto-reload shadow register */

    /* Module 1 (P1.4): High-Speed Output Mode (toggles P1.4 every 1000 counts) */
    CCAPM1 = 0x4D;      /* ECOM1 = 1, MAT1 = 1, TOG1 = 1, ECCF1 = 1 */
    CCAP1L = 0xE8;      /* 1000 = 0x03E8 */
    CCAP1H = 0x03;

    CR = 1;             /* Start PCA Counter */
}

void main(void) {
    unsigned int next_match = 1000;
    pca_init();

    while (1) {
        /* Poll Module 1 match flag to advance next toggle interval */
        if (CCF1) {
            CCF1 = 0;
            next_match += 1000;
            CCAP1L = (unsigned char)(next_match & 0xFF);
            CCAP1H = (unsigned char)(next_match >> 8);
        }
    }
}
