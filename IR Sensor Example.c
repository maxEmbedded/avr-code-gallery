// Post: "How to build an IR sensor"
// URL: http://maxembedded.com/2013/08/04/how-to-build-an-ir-sensor/
// Author: Vishwam Aggarwal, VIT University

/* 	DISCLAIMER

	This is the same code as given in the above URL. Though the code is tested and approved, the author
	is not responsible for any damage, physical, mental or social, which might occur due to the implementation
	of this code and its derivatives, whether in full or part thereof. Use it at your own risk.

	LICENSE
	
	The user is free to modify, reuse, reproduce and distribute the code and its derivatives to any extent,
	whether for free or paid. The user can also use this code for commercial purposes. In other words,
	do whatever you want with the code!
   
*/


#define F_CPU 1000000UL
 
#include <avr/io.h>
 
int ch_prime(int); //Prototyping the function for testing a number to be prime or not
 
int main(void)
{
          uint8_t num=0, res; //Creating variables 'num' & 'res' for storing the number of detections & result of the function respectively
          DDRA &= ~(1<<0); //Setting 0th pin of Port A as input
          DDRD |= (1<<0); //Setting 0th pin of Port D as output
 
          while(1)
          {
                   if (bit_is_set(PINA, 0)) //Checking if the sensor has detected something in front of it
                   {
                            while (bit_is_set(PINA, 0)); // We use the 'While' function to make sure that one detection increments the value of num by only one value
                            res = ch_prime(++num); //Incrementing the value of num and sending it to the function which tests it for being a prime number
 
                            if (res==1)
                            PORTD |= (1<<PIND0); //If returned value is 1, indicate prime number by pulling the 0th pin on Port D High
                            else
                            PORTD &= ~(1<<PIND0); //If returned value is 0, indicate composite number by pulling the 0th pin on Port D Low
                   }
                   else
                   continue; //If sensor has nothing in front of it, continue detecting
          }
}
 
int ch_prime(int num)
{
          int i; //Declaring variable 'i' to use in the for loop
          for (i=2;i<num;i++) //Run the loop for the value of i from '2' to 'num-1'
          {
                   if (num%i==0) //Check and compare to 0 the remainder when dividing num by i, if 0, then composite number
                   return(0); //If Number is composite, return 0
          }
          if (i==num) //Compare the value of i to num, if same, then prime number
          return(1); //If number is prime, return 1
}