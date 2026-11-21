#include <reg51.h>

sbit LED_PIN = P1^0;    // Output pin P1.0 to toggle every 100 bottles

void main(void)
{
    LED_PIN = 0;        // Initialize P1.0 to LOW
    TMOD = 0x06;        // Counter 0 (C/T=1), Mode 2: 8-bit auto-reload (M1=1, M0=0)
    TH0  = 0x9C;        // Load reload value: 256 - 100 = 156 (0x9C)
    TL0  = 0x9C;        // Load initial count value
    TR0  = 1;           // Start Counter 0 (receives pulses on P3.4 / T0)

    while (1)
    {
        while (TF0 == 0);   // Wait until 100 pulses are counted (TF0 sets on overflow)
        TF0 = 0;            // Clear Timer/Counter 0 overflow flag
        LED_PIN = ~LED_PIN; // Toggle status of P1.0 pin
    }
}
