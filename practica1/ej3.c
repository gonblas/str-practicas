#include <htc.h>

__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_ON & CP_OFF);

#define _XTAL_FREQ 4000000UL

#define LATCH1 PORTDbits.RD6
#define LATCH2 PORTDbits.RD7

// Inicializa ADC (AN0) usando Vdd/Vss como referencia
void adc_init(void) {
    ADCON1 = 0x80;   // ADFM = 1 (right justified); Vref = Vdd
    ADCON0 = 0x01;   // ADON = 1, canal CHS = 0 (AN0)
    __delay_us(20);  // tiempo de adquisición inicial
}

unsigned int adc_read(void) {
    ADCON0bits.GO = 1;         // empezar conversión
    while(ADCON0bits.GO);      // esperar a que termine
    return ((unsigned int)ADRESH << 8) | ADRESL; // 10 bits en ADRESH/ADRESL
}

// Muestra el valor (0..1023) en 4 displays hex (0x000 .. 0x3FF)
// d0 = nibble menos significativo, d1 = siguiente, d2, d3
void display_hex(unsigned int value) {
    unsigned char d0 =  value        & 0x0F;
    unsigned char d1 = (value >> 4)  & 0x0F;
    unsigned char d2 = (value >> 8)  & 0x0F;
    unsigned char d3 = (value >> 12) & 0x0F; // normalmente 0 o 3 para 10 bits

    // Latch 1 controla los dos dígitos bajos (d0 en bits 0..3, d1 en bits 4..7)
    PORTB = (d1 << 4) | d0;
    LATCH1 = 1;
    __delay_us(1);
    LATCH1 = 0;

    // Latch 2 controla los dos dígitos altos (d2 en bajos, d3 en altos)
    PORTB = (d3 << 4) | d2;
    LATCH2 = 1;
    __delay_us(1);
    LATCH2 = 0;
}

void main(void) {
    // Configuraciones de puertos
    TRISAbits.TRISA0 = 1;   // RA0 entrada (AN0)
    TRISB = 0x00;           // PORTB salidas (datos a latchs)
    TRISDbits.TRISD6 = 0;   // RD6 salida -> LE latch1
    TRISDbits.TRISD7 = 0;   // RD7 salida -> LE latch2

    PORTB = 0x00;
    PORTD = 0x00;

    adc_init();

    while(1) {
        unsigned int valor = adc_read(); // 0..1023
        display_hex(valor);             // muestra en hex (0x000..0x3FF)
        __delay_ms(150);
    }
}