#include <htc.h>
#define _XTAL_FREQ 1000000

void main(void)
 {
    TRISA |= (1 << 1) | (1 << 0);   	 // pulsadores como entrada
    TRISB &= ~((1 << 5) | (1 << 4));      // leds como salida
    RB4 = 1; RB5 = 1; 			// inicialmente prendidos
   
    // como tiene pull-up externo preguntamos por si alguno de los valores es cero y eso permite continuar la ejecución
    while((PORTA & 0b00000011) == 0b00000011);
    while (1) {
       __delay_ms(250);
       RB4 ^= 1; RB5 ^= 1; 			// los invertimos
    }
 }