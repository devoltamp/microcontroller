#include <stdio.h>
#include <reg51.h>

void main(void){
	
	unsigned char port_data;
	P1 = 0xFF;	
	/* setting it up for reading */
	
	while(1){	
		port_data = P1;
		P2 = port_data;
	}
}