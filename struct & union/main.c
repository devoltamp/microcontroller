/* for explination just ai this */
#include <reg51.h>

union joshi {
    unsigned int j;             /* 2-byte 16-bit value (e.g., 2000 = 0x07D0) */

    struct jivan {
        unsigned char j1;       /* High byte (MSB -> 0x07) */
        unsigned char j2;       /* Low byte  (LSB -> 0xD0) */
    } x, y;                     /* 2-byte struct overlaid onto 'j' */
} reg_x, reg_y;

void main(void) {
    /* Load 16-bit integer directly into the union */
    reg_x.j = 2000;             /* 2000 = 0x07D0 -> j1 = 0x07 (7), j2 = 0xD0 (208) */

    /* Load Timer 0 registers directly from the split bytes */
    TH0 = reg_x.x.j1;           /* TH0 = 0x07 */
    TL0 = reg_x.x.j2;           /* TL0 = 0xD0 */

    /* Modifying a single byte updates the 16-bit integer automatically */
    reg_x.x.j2 = 50;            /* 50 = 0x32 -> reg_x.j becomes 0x0732 (1842) */

    while (1) {
        ;
    }
}
