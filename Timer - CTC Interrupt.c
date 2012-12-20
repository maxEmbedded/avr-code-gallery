// Post: "AVR Timers - CTC Mode" - Interrupt
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

    // initialize counter
    TCNT1 = 0;

    // initialize compare value
    OCR1A = 24999;

    // enable compare interrupt
    TIMSK |= (1 << OCIE1A);

    // enable global interrupts
    sei();
}

// this ISR is fired whenever a match occurs
// hence, toggle led here itself..
ISR (TIMER1_COMPA_vect)
{
    // toggle led here
    PORTC ^= (1 << 0);
{

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
        // whenever a match occurs, ISR is fired
        // toggle the led in the ISR itself
        // no need to keep track of any flag bits here
        // done!
    }
}