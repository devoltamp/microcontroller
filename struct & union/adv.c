#include <reg51.h>

/* 1. Union + Struct for 16-bit to 8-bit register splitting */
union timer_val {
    unsigned int full_16bit;    /* 2 bytes (e.g., 64536 = 0xFC18) */
    struct {
        unsigned char high_byte; /* MSB -> 0xFC (Keil C51 is Big-Endian) */
        unsigned char low_byte;  /* LSB -> 0x18 */
    } bytes;
};

/* 2. Struct with Bit-Fields to pack status flags into 1 byte */
struct system_flags {
    unsigned char motor_on   : 1;
    unsigned char fault      : 1;
    unsigned char mode       : 2;
    unsigned char reserved   : 4;
};

void main(void) {
    union timer_val t0_reload;
    struct system_flags status = {1, 0, 2, 0};

    /* Assign 16-bit value once; access split bytes immediately */
    t0_reload.full_16bit = 0xFC18;  /* 64536 -> 1 ms delay @ 12 MHz */

    TMOD = 0x01;
    TH0 = t0_reload.bytes.high_byte; /* Loads 0xFC */
    TL0 = t0_reload.bytes.low_byte;  /* Loads 0x18 */
    TR0 = 1;

    if (status.motor_on && !status.fault) {
        P1 = status.mode;
    }

    while (1);
}
