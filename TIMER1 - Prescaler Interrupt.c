// Post: "AVR Timers - TIMER1" - Prescaler and Interrupt
// URL: http://maxembedded.com/2011/06/28/avr-timers-timer1/
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

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

// initialize timer, interrupt and variable
void timer1_init()
{
    // set up timer with prescaler = 8
    TCCR1B |= (1 << CS11);

    // initialize counter
    TCNT1 = 0;

    // enable overflow interrupt
    TIMSK |= (1 << TOIE1);

    // enable global interrupts
    sei();

    // initialize overflow counter variable
    tot_overflow = 0;
}

// TIMER1 overflow interrupt service routine
// called whenever TCNT1 overflows
ISR(TIMER1_OVF_vect)
{
    // keep a track of number of overflows
    tot_overflow++;

    // check for number of overflows here itself
    // 61 overflows = 2 seconds delay (approx.)
    if (tot_overflow >= 61) // NOTE: '>=' used instead of '=='
    {
        PORTC ^= (1 << 0);  // toggles the led
        // no timer reset required here as the timer
        // is reset every time it overflows

        tot_overflow = 0;   // reset overflow counter
    }
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
        // do nothing
        // comparison is done in the ISR itself
    }
}