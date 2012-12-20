// Post: "AVR Timers - CTC Mode" - Hardware CTC
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
#include <avr/interrupt.h>

// initialize timer, interrupt and variable
void timer1_init()
{
    // set up timer with prescaler = 64 and CTC mode
    TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);

    // set up timer OC1A pin in toggle mode
    TCCR1A |= (1 << COM1A0);

    // initialize counter
    TCNT1 = 0;
    // initialize compare value
    OCR1A = 24999;
}

int main(void)
{
    // connect led to pin PD5
    DDRD |= (1 << 5);

    // initialize timer
    timer1_init();

    // loop forever
    while(1)
    {
        // do nothing
        // whenever a match occurs
        // OC1A is toggled automatically!
        // no need to keep track of any flag bits or ISR
        // done!
    }
}