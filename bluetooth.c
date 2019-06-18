/*
 * GccApplication44.c
 *
 * Created: 18-06-2019 10:23:47
 * Author : pratyusha
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define LED PORTB
char buffer[10];
void USARTInit(uint16_t ubrr_value)
{
	//Set Baud rate
	UBRRL = ubrr_value;

	UBRRH = (ubrr_value>>8);

	UCSRC=(1<<URSEL)|(3<<UCSZ0);

	//Enable The receiver and transmitter

	UCSRB=(1<<RXEN)|(1<<TXEN);

}



char USARTReadChar()

{

	//Wait until a data is available

	while(!(UCSRA & (1<<RXC)))

	{

		//Do nothing

	}

	return UDR;

}



void USARTWriteChar(char data)

{

	while(!(UCSRA & (1<<UDRE)))

	{

		//Do nothing

	}

	UDR=data;

}

int main()

{

	USARTInit(77);

	DDRB=0b11111111;//PORTB as output

	char data;

	LED = 0;

	while(1)

	{

		data=USARTReadChar();

		if(data =='1')

		{

			LED |= (1<<PB0);	/* Turn ON LED */

			//USART_SendString("LED_ON");/* send status of LED i.e. LED ON */

			

		}

		else if(data =='2')

		{

			LED &= ~(1<<PB0);	/* Turn OFF LED */

			//USART_SendString("LED_OFF"); /* send status of LED i.e. LED OFF */

		}

		//else

		//USART_SendString("Select proper option"); /* send message for selecting proper option */
	}

	return 0;

}

