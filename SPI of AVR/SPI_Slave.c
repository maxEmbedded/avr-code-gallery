// Post: "The SPI of the AVR" - SPI Slave Code
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
 * SPI_Slave.c
 *
 * Created: 12/13/2013 2:20:06 AM
 *  Author: Yash Tambi
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"

#define ACK 0x7E

void spi_init_slave (void)
{
    DDRB=(1<<6);                                  //MISO as OUTPUT
    SPCR=(1<<SPE);                                //Enable SPI
}

//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;                                  //Load data into buffer
    while(!(SPSR)&(1<<SPIF));                     //Wait until transmission complete
    return(SPDR);                                 //Return received data
}

int main(void)
{
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);           //Initialize LCD
    spi_init_slave();                             //Initialize slave SPI
    
    unsigned char data, buffer[10];
    
    DDRA  = 0x00;                                 //Initialize PORTA as INPUT
    PORTA = 0xFF;                                 //Enable Pull-Up Resistors
    
    while(1)
    {
        lcd_clrscr();                             //LCD Clear screen
        lcd_home();                               //LCD move cursor to home 
        lcd_puts("Testing");
        lcd_gotoxy(0,1);
        data = spi_tranceiver(ACK);               //Receive data, send ACK
        itoa(data, buffer, 10);                   //Convert integer into string
        lcd_puts(buffer);                         //Display received data
        _delay_ms(20);                            //Wait
    }
}