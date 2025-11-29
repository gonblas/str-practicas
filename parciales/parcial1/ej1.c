#include <htc.h>
#define _XTAL_FREQ 1000000

void interrupt ISR(void)
{
	if (T0IF)
	{
		TMR0 = 12;
		T0IF = 0;
		PORTB <<= 1;
		if (PORTB == 0x00)
			PORTB = 0x01;
	}
}

void main(void)
{
	TRISA |= (1 << 0); // entrada RA0
	TRISB = 0x00;	   // salidas
	PORTB = 0x00;

	OPTION_REG = 0b00000111;
	TMR0 = 12;

	// espero primer presión para iniciar
	while ((PORTA & 0b00000001) != 0)
		;
	PORTB = 0x01;

	// habilito interrupciones globales
	GIE = 1;
	T0IF = 0;

	while (1)
	{
		if ((PORTA & 0b00000001) == 0) // pulsador presionado
			T0IE = 1;				   // se mueve la secuencia
		else
			T0IE = 0; // se congela la secuencia
	}
}
