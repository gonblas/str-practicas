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
		{
			PORTB = 0x01; // reinicia secuencia
			T0IE = 0;			// detiene desplazamiento
		}
	}
}

void main(void)
{
	TRISA = 0b00000001; // RA0 entrada
	TRISB = 0x00;				// RB como salida
	PORTB = 0x00;

	OPTION_REG = 0b00000111; // prescaler 1:256
	TMR0 = 12;

	GIE = 1;	// habilito interrupciones globales
	T0IE = 0; // deshabilito Timer0 por ahora
	T0IF = 0; // limpio bandera de Timer0

	while (1)
	{
		while (RA0 == 1)
			; // espera hasta que el botón se presione
		if(PORTB == 0x00){
			PORTB = 0x01;
		}
		T0IE = 1;			// habilita Timer0 para desplazamiento
	}
}
