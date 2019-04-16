/*
 * serial.c
 *
 * Created: 09/04/2019 15:36:47
 * Author : Joe Joe Ngigi
 */ 

//#include <asf.h>
#include <avr/io.h>

#define FOSC 1000000 //oscillating frequency
#define BAUDRATE 9600
#define MYUBRR FOSC/16/BAUDRATE-1



unsigned char USART_Receive(void)
{
	/*wait for data to be received*/
	while ( !(UCSR0A & (1<<RXC0)))
	;
	/*Get and return received data from buffer*/
	return UDR0;
}

void USART_Transmit(unsigned char data)
{
	/*wait for empty transmit buffer*/
	while (!(UCSR0A & (1<<UDRE0)));
	
	/*put data into buffer, sends the data*/
	UDR0 = data;
}
/*
void usart_pstr(char *s) {
	//loop through entire string
	
	while (*s) {
		USART_Transmit(*s);
		s++;
	}
}
*/

void USART_Init(unsigned int UBRR)
{
	
	/*set baud rate*/
	UBRR0H = (unsigned char)(UBRR>>8);
	UBRR0L = (unsigned char)UBRR;
	
	/*enable receiver and transmitter*/
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	/*set frame format: 8data, 2stop bit */
	//UCSR1C = (1<<USBS1) | (3<<UCSZ10);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	/*For double speed */
	UCSR0A = (1<<U2X0);
}



int main(void)
{
	
	USART_Init(MYUBRR);
   
    while (1) 
    {
//usart_pstr("Hello, I am Atmega1284P\n");
		USART_Transmit(USART_Receive());
    }
}






