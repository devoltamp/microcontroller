/* ref.
 * https://www.ahstu.edu.cn/__local/2/18/CC/E0D24AB2F6452DB4BEA28513DA7_2D9B8AB0_4C2862.pdf
 * -- national cheng kung university
 */
#include <reg51.h>

sbit SW = P1^7;
sbit IND = P1^0;
sbit WAVE = P2^5;

void timer0(void) interrupt 1 {
    WAVE =~ WAVE;
}

void main(){
    SW = 1;
    TMOD = 0x02;
    TH0 = 0xA4;
    IE = 0x82;

    while(1){
        IND = SW;
    }
}
