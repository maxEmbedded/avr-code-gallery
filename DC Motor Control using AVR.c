// Post: "DC Motor Control using AVR"
// URL: http://maxembedded.com/2011/06/15/dc-motor-control-using-avr/
// Author: Mayank Prasad, VIT University

/* 	DISCLAIMER

	This is the same code as given in the above URL. Though the code is tested and approved, the author
	is not responsible for any damage, physical, mental or social, which might occur due to the implementation
	of this code and its derivatives, whether in full or part thereof. Use it at your own risk.

	LICENSE
	
	The user is free to modify, reuse, reproduce and distribute the code and its derivatives to any extent,
	whether for free or paid. The user can also use this code for commercial purposes. In other words,
	do whatever you want with the code!
   
*/

#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()

int main(void)
{
    DDRC = 0x0F;                       // initialize port C
                                       // motors connected across PC0...Pc3

    while(1)
    {
        // clockwise rotation
        PORTC = 0b00000101;            // PC0 = High = Vcc
                                       // PC1 = Low = 0
                                       // PC2 = High = Vcc
                                       // PC3 = Low = 0

        _delay_ms(500);                // wait 0.5s

        // counter-clockwise rotation
        PORTC = 0b00001010;            // PC0 = Low = 0
                                       // PC1 = High = Vcc
                                       // PC2 = Low = 0
                                       // PC3 = High = Vcc

        _delay_ms(500);                // wait 0.5s
    }
}