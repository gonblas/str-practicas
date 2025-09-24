#include <htc.h>
#define _XTAL_FREQ 1000000

void interrupt ISR(void)
{
    if (T0IF)
    {                      // bandera de TMR0
        TMR0 = 12;         // precarga para 244 cuentas: 250ms
        T0IF = 0;          // limpio bandera
        PORTB ^= (1 << 4); // toggle RB4
        PORTB ^= (1 << 5); // toggle RB5
    }
}

void main(void)
{
    TRISA |= (1 << 1) | (1 << 0);    // pulsadores como entrada
    TRISB &= ~((1 << 5) | (1 << 4)); // leds como salida
    RB4 = 1;
    RB5 = 1; // inicialmente prendidos

    // Configuración Timer0
    OPTION_REG = 0b00000111; // prescaler 1:256 asignado a TMR0
    TMR0 = 12;               // precarga

    // como tiene pull-up externo preguntamos por si alguno de los valores es cero y eso permite continuar la ejecución
    while ((PORTA & 0b00000011) == 0b00000011)
        ;

    // Habilito interrupciones
    T0IE = 1; // Timer0 interrupt enable
    GIE = 1;  // Global interrupt enable
    T0IF = 0; // limpio bandera

    while (1)
        ; // loop infinito
}
