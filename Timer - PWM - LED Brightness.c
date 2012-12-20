// Post: "AVR Timers - PWM Mode - Part II" - LED Brigtness
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

// program to change brightness of an LED
// demonstration of PWM

#include <avr/io.h>
#include <util/delay.h>

// initialize PWM
void pwm_init()
{
    // initialize timer0 in PWM mode
    TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);

    // make sure to make OC0 pin (pin PB3 for atmega32) as output pin
    DDRB |= (1<<PB3);
}

void main()
{
    uint8_t brightness;

    // initialize timer0 in PWM mode
    pwm_init();

    // run forever
    while(1)
    {
        // increasing brightness
        for (brightness = 0; brightness < 255; ++brightness)
        {
            // set the brightness as duty cycle
            OCR0 = brightness;

            // delay so as to make the user "see" the change in brightness
            _delay_ms(10);
        }

        // decreasing brightness
        for (brightness = 255; brightness > 0; --brightness)
        {
            // set the brightness as duty cycle
            OCR0 = brightness;

            // delay so as to make the user "see" the change in brightness
            _delay_ms(10);
        }

    // repeat this forever
    }
}