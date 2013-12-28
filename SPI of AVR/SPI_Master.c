// Post: "The SPI of the AVR" - SPI Master Code
// URL: http://maxembedded.com/2013/11/26/the-spi-of-the-avr/
// Authors: Yash Tambi, VIT University, India
//          Mayank (Max) Prasad, Arizona State University, USA
//          support@maxEmbedded.com

/* 	DISCLAIMER

	This is the same code as given in the above URL. Though the code is tested and approved, the author
	is not responsible for any damage, physical, mental or social, which might occur due to the implementation
	of this code and its derivatives, whether in full or part thereof. Use it at your own risk.

	LICENSE
	
	The user is free to modify, reuse, reproduce and distribute the code and its derivatives to any extent,
	whether for free or paid. The user can also use this code for commercial purposes. In other words,
	do whatever you want with the code!
   
*/


/*
 * SPI_Master.c
 *
 * Created: 12/13/2013 2:19:02 AM
 *  Author: Yash Tambi
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define ACK 0x7E
#define LONG_TIME 10000

//Initialize SPI Master Device
void spi_init_master (void)            
{
    DDRB = (1<<5)|(1<<3);              //Set MOSI, SCK as Output
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, Set as Master
                                       //Prescaler: Fosc/16, Enable Interrupts
}

//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;                       //Load data into the buffer
    while(!(SPSR)&(1<<SPIF));          //Wait until transmission complete
    return(SPDR);                      //Return received data
}

//Function to blink LED
void led_blink (uint8_t i)
{
    //Blink LED "i" number of times
    for (; i>0; --i)
    {
        PORTD|=(1<<0);
        _delay_ms(100);
        PORTD=(0<<0);
        _delay_ms(100);
    }
}

//Main
int main(void)
{
    spi_init_master();                  //Initialize SPI Master
    DDRD |= 0x01;                       //PD0 as Output
    
    unsigned char data;                 //Received data stored here
    uint8_t x = 0;                      //Counter value which is sent
    
    while(1)
    {
        data = 0x00;                    //Reset ACK in "data"
        data = spi_tranceiver(++x);     //Send "x", receive ACK in "data"
        if(data == ACK) {               //Check condition
            //If received data is the same as ACK, blink LED "x" number of times
            led_blink(x);
        }
        else {
            //If received data is not ACK, then blink LED for a long time so as to determine error
            led_blink(LONG_TIME);
        }
        _delay_ms(500);                 //Wait 
    }
}