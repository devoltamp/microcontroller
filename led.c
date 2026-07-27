/* https://coursecontent.indusuni.ac.in/wp-content/uploads/sites/8/2020/03/MMI_EL0502_Unit1.pdf */
#include <stdio.h>
#include <reg51.h>

sbit _key = P1^0;
sbit led  = P1^1;
bit key_flag = 0;       /* flag remains unglagged */
void keyscan();
void changeout();

void main(){

    /* P1.0 configured as i/p
     * by default all the port pins will be high FF */
    _key = 1;
    while(1){
        keyscan();
        changeout();
    }
}

/* at P1 port the internal architecture is like having
 * two mosfets vertically with lower one connected to
 * via not gate -- at a time only one can be turned on */

void keyscan(){

    /* P1.0 constantly read
     * cause the in the ckt the logic is reverse
     * when we'll apply 0v to the P1.1
     * the led will turn on -- cause the led is already connected to VCC
     */
    if (_key == 0){
        /* debouncing condition */
        for (int i = 0; i<=200; i++){
            ;
        }
        if (_key == 0)
            key_flag = 1;
        else
            key_flag = 0;
    }
}

void changeout(){

    /* after the signal's been recieved -- take action on it */
    if (key_flag == 1){
        led =~ led;
        key_flag = 0;   /* other wise for next time it'll be 1 that's not good */
    }
}

/* i know that it's a lot of comments but
 * but trust me the clown meme is correct
 */
