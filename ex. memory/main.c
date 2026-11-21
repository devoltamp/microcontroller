#include <reg51.h>

/* Stored in External Code Memory (accessed via PSEN / MOVC) */
code unsigned char rom_lut[5] = {10, 20, 30, 40, 50};

/* Allocated in External Data RAM at 0x0000 (accessed via RD/WR / MOVX) */
unsigned char xdata ext_ram_buffer[5] _at_ 0x0000;

void main(void) {
    unsigned char i;
    unsigned char temp;

    /* Copy data from External ROM to External RAM */
    for (i = 0; i < 5; i++) {
        ext_ram_buffer[i] = rom_lut[i];
    }

    /* Read back from External RAM and send to Port 1 */
    for (i = 0; i < 5; i++) {
        temp = ext_ram_buffer[i];
        P1 = temp;
    }

    while (1);
}
