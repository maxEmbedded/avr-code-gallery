// Post: "AVR Timers - TIMER0" - Polling
// URL: http://maxembedded.com/2011/06/24/avr-timers-timer0-2/
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

void timer0_init()
{
    // set up timer with no prescaling
    TCCR0 |= (1 << CS00);

    // initialize counter
    TCNT0 = 0;
}

int main(void)
{
    // connect led to pin PC0
    DDRC |= (1 << 0);

    // initialize timer
    timer0_init(); 

    // loop forever 
    while(1) 
    { 
        // check if the timer count reaches 191 
        if (TCNT0 >= 191)
        {
            PORTC ^= (1 << 0);    // toggles the led
            TCNT0 = 0;            // reset counter
        }
    }
}