#include <stdio.h>
#include <reg51.h>

void main(void){
	
	unsigned char portdata;
	P1 = 0xFF;
	
	while(1){
		portdata = 0xf0;
		P1 = portdata;
	}
}
/* at a time only one file 
in the source group */
