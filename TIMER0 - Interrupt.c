// Post: "AVR Timers - TIMER0" - Interrupt
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
#include <avr/interrupt.h>

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

// initialize timer, interrupt and variable
void timer0_init()
{
    // set up timer with prescaler = 256
    TCCR0 |= (1 << CS02);

    // initialize counter
    TCNT0 = 0;

    // enable overflow interrupt
    TIMSK |= (1 << TOIE0);

    // enable global interrupts
    sei();

    // initialize overflow counter variable
    tot_overflow = 0;
}

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect)
{
    // keep a track of number of overflows
    tot_overflow++;
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
        // check if no. of overflows = 12 
        if (tot_overflow >= 12)  // NOTE: '>=' is used
        {
            // check if the timer count reaches 53
            if (TCNT0 >= 53)
            {
                PORTC ^= (1 << 0);    // toggles the led
                TCNT0 = 0;            // reset counter
                tot_overflow = 0;     // reset overflow counter
            }
        }
    }
}