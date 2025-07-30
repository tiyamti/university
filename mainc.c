#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define LCD_DDR DDRA
#define LCD_PORT PORTA
#define RS PA0
#define RW PA1
#define EN PA2

#define KEYPAD_PORT PORTC
#define KEYPAD_DDR DDRC
#define KEYPAD_PIN PINC

char keypad[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'C', '0', '=', '+'}
};

// -------- LCD --------
void lcd_command(unsigned char cmd) {
	LCD_PORT = (LCD_PORT & 0x0F) | (cmd & 0xF0);
	LCD_PORT &= ~(1 << RS);
	LCD_PORT &= ~(1 << RW);
	LCD_PORT |= (1 << EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (cmd << 4);
	LCD_PORT |= (1 << EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_ms(2);
}

void lcd_char(unsigned char data) {
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	LCD_PORT |= (1 << RS);
	LCD_PORT &= ~(1 << RW);
	LCD_PORT |= (1 << EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	LCD_PORT |= (1 << EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_ms(2);
}

void lcd_init() {
	LCD_DDR = 0xFF;
	_delay_ms(20);
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0C);
	lcd_command(0x06);
	lcd_command(0x01);
	_delay_ms(2);
}

void lcd_clear() {
	lcd_command(0x01);
	_delay_ms(2);
}

void lcd_print(char* str) {
	while (*str) lcd_char(*str++);
}

void lcd_float(float num) {
	char buf[16];
	dtostrf(num, 7, 2, buf);  
	lcd_print(buf);
}

// -------- calculator --------
void keypad_init() {
	KEYPAD_DDR = 0xF0;
	KEYPAD_PORT = 0xFF;
}

char keypad_getkey() {
	for (int col = 0; col < 4; col++) {
		KEYPAD_DDR = 0xF0;
		KEYPAD_PORT = ~(1 << (col + 4));
		_delay_ms(5);

		for (int row = 0; row < 4; row++) {
			if (!(KEYPAD_PIN & (1 << row))) {
				while (!(KEYPAD_PIN & (1 << row)));  
				return keypad[row][col];
			}
		}
	}
	return 0;
}

// -------- Main --------
int main(void) {
	char key;
	float num1 = 0, num2 = 0, result = 0;
	char op = 0;

	lcd_init();
	keypad_init();
	lcd_clear();
	lcd_print("Calc: ");

	while (1) {
		key = keypad_getkey();
		if (key != 0) {
			lcd_char(key);
			_delay_ms(100);

			if (key >= '0' && key <= '9') {
				if (op == 0)
				num1 = num1 * 10 + (key - '0');    
				else
				num2 = num2 * 10 + (key - '0');
				} else if (key == '+' || key == '-' || key == '*' || key == '/') {
				op = key;
				} else if (key == '=') {
				lcd_clear();
				lcd_print("Ans: ");
				switch (op) {
					case '+': result = num1 + num2; break;
					case '-': result = num1 - num2; break;
					case '*': result = num1 * num2; break;
					case '/':
					if (num2 != 0) result = num1 / num2;
					else {
						lcd_print("Err");
						continue;
					}
					break;
					default: lcd_print("Err"); continue;
				}
				lcd_float(result);
				num1 = num2 = result = 0;
				op = 0;
				} else if (key == 'C') {
				num1 = num2 = result = 0;
				op = 0;
				lcd_clear();
				lcd_print("Calc: ");
			}
		}
	}
}
