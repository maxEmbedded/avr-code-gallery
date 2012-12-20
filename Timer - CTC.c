// Post: "AVR Timers - CTC Mode"
// URL: http://maxembedded.com/2011/07/14/avr-timers-ctc-mode/
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

// initialize timer, interrupt and variable
void timer1_init()
{
    // set up timer with prescaler = 64 and CTC mode
    TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);

    // initialize counter
    TCNT1 = 0;

    // initialize compare value
    OCR1A = 24999;
}

int main(void)
{
    // connect led to pin PC0
    DDRC |= (1 << 0);

    // initialize timer
    timer1_init();

    // loop forever
    while(1)
    {
        // check whether the flag bit is set
        // if set, it means that there has been a compare match
        // and the timer has been cleared
        // use this opportunity to toggle the led
        if (TIFR & (1 << OCF1A)) // NOTE: '>=' used instead of '=='
        {
            PORTC ^= (1 << 0); // toggles the led
        }

        // wait! we are not done yet!
        // clear the flag bit manually since there is no ISR to execute
        // clear it by writing '1' to it (as per the datasheet)
        TIFR |= (1 << OCF1A);

        // yeah, now we are done!
    }
}