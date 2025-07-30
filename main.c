#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void USART_Init(unsigned int ubrr) {
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

void USART_Transmit(unsigned char data) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = data;
}

void USART_SendString(const char *str) {
	while (*str) {
		USART_Transmit(*str++);
	}
}

void ADC_Init() {
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}

uint16_t ADC_Read() {
	ADMUX = (ADMUX & 0xF0);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return ADC;
}

void PWM_Init() {
	DDRB |= (1<<PB1);
	TCCR1A = (1<<COM1A1)|(1<<WGM11);
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);
	ICR1 = 1023;
}

void PWM_SetDuty(uint16_t value) {
	if (value > 1023) value = 1023;
	OCR1A = value;
}

int main(void) {
	char buffer[10];

	DDRD |= (1 << PD1);

	USART_Init(51);
	ADC_Init();
	PWM_Init();
	
	DDRD |= (1<<PD5);
	DDRD |= (1<<PD6);
	PORTD |= (1<<PD5);
	PORTD &= ~(1<<PD6);

	while (1) {
		uint16_t adc_val = ADC_Read();
		PWM_SetDuty(adc_val);

		USART_SendString("Speed: ");
		itoa(adc_val, buffer, 10);
		USART_SendString(buffer);
		USART_SendString("\r\n");
		
		_delay_ms(200);
	}
}