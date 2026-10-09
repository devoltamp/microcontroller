#include <reg51.h>

sfr lcd_data_port = 0x90;   /* port 1 */
sbit rs = P2^0;
sbit rw = P2^1;
sbit en = P2^2;

void lcd_init();
void lcd_command(unsigned char cmd);
void lcd_char(unsigned char char_data);
void lcd_print(char *str);
void lcd_string(char row, char pos, char *str);
void delay(unsigned int count);

void main(){

    lcd_init();
    lcd_string(0, 0, "Hello There!");
    lcd_string(1, 0, "General Kernobi");
    while (1) {
        ;
    }
}

/* †(1) */
void lcd_init(){
    delay(20);
    lcd_command(0x38);      /* 8-bit mode, 2 lines, 5x7 matrix */
    lcd_command(0x0C);      /* display ON, cursor OFF */
    lcd_command(0x06);      /* increment cursor */
    lcd_command(0x01);      /* clear display */
    delay(2);
    lcd_command(0x80);      /* move cursor to line 1, pos 0 */
}

void lcd_string(char row, char pos, char *str) {
    if (row == 0) {
        lcd_command((pos & 0x0F) | 0x80);   /* line 1 base offset 0x80 */
    }
    else if (row == 1) {
        lcd_command((pos & 0x0F) | 0xC0);
        /* line 2 base offset 0xC0 (Fixed) */
    }
    lcd_print(str);     /* call renamed string printing function */
}

void lcd_command(unsigned char cmd){

    /* here the cmd is given */
    lcd_data_port = cmd;
    rs = 0;     /* command mode */
    rw = 0;     /* write mode */

    en = 1;
    delay(1);
    en = 0;

    delay(5);
}

void lcd_char(unsigned char char_data){

    lcd_data_port = char_data;
    rs = 1;     /* data mode (fixed) */
    rw = 0;     /* write mode */

    en = 1;
    delay(1);
    en = 0;

    delay(5);
}

void lcd_print(char *str) {
    unsigned int i;
    for (i = 0; str[i] != '\0'; i++) {
        lcd_char(str[i]);
    }
}

void delay(unsigned int count){

    unsigned int i, j;
    for (i = 0; i < count; i++){
        for (j = 0; j < 112; j++){
            ;
        }
    }
}

/* notes;
 *
 * †(1)
 * according to the hex #n passed,
 * things will happen accordingly
 *
 */
