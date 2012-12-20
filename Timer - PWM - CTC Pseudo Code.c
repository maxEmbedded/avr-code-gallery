// Post: "AVR Timers - PWM Mode - Part II" - CTC Pseudo Code
// URL: http://maxembedded.com/2012/01/07/avr-timers-pwm-mode-part-ii/
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

// IMPORTANT:: THIS IS JUST A PSEUDO CODE AND SHOULD NOT BE COMPILED AS IT IS.
// VIEW THE TUTORIAL FOR MORE DETAILS

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t count = 0;               // global counter

// initialize timer, interrupt and variable
void timerX_init()
{
    // set up timerX with suitable prescaler and CTC mode
    // initialize counter
    // initialize compare value
    // enable compare interrupt
    // enable global interrupts
}

// process the ISR that is fired
ISR (TIMERx_COMPA_vect)
{
    // do whatever you want to do here
    // say, increment the global counter
    count++;

    // check for the global counter
    // if count == odd, delay required = 11 ms
    // if count == even, delay required = 9 ms
    // thus, the value of the OCRx should be constantly updated
    if (count % 2 == 0)
        OCRx = 9999;      // calculate and substitute appropriate value
    else
        OCRx = 10999;     // calculate and substitute appropriate value
}

int main(void)
{
    // initialize the output pin, say PC0
    DDRC |= (1 << 0);

    // initialize timerX
    timerX_init();

    // loop forever
    while(1)
    {
        // do nothing

    }
}