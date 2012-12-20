// Post: "Using AVR Studio 5 Simulator and Debugger"
// URL: http://maxembedded.com/2011/06/13/using-the-avr-studio-5-simulator-and-debugger/
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

int main(void)
{
    uint8_t counter;
    DDRB = 0xFF;
    while(1)
    {
        counter++;    // insert breakpoint here <-----
        PORTB = counter;
    }
}