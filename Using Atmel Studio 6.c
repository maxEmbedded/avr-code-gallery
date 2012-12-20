// Post: "Using Atmel Studio 6" and "Using AVR Studio 5"
// URL: http://maxembedded.com/2011/06/12/using-avr-studio-5/
// URL: http://maxembedded.com/2012/06/25/using-atmel-studio-6/
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
	DDRC = 0x01;                       // initialize port C
	while(1)
	{
		// LED on
		PORTC = 0b00000001;            // PC0 = High = Vcc
		_delay_ms(500);                // wait 500 milliseconds

		// LED off
		PORTC = 0b00000000;            // PC0 = Low = 0v
		_delay_ms(500);                // wait 500 milliseconds
	}
}