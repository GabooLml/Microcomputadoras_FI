#include <16f877.h>              //Librería del microcontrolador
#fuses HS,NOPROTECT, NOWDT, NOLVP
#device ADC = 10                 //Convertidor A/D indica resolución de 10 bits
#use delay(clock=20000000)       //Frec. de Osc. 20Mhz
#define use_portd_lcd true
#include <lcd.c> 
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) //Configuracion del Puerto SERIAL
#org 0x1F00, 0x1FFF void loader16F877(void) {}  

int16 var; // Variable tipo entero de 16 bits 

void main(){   
   lcd_init();                   //Inicialización del LCD
   setup_port_a(ALL_ANALOG);     //Configuración del Puerto A como analógico
   setup_adc(ADC_CLOCK_INTERNAL);//Relog interno de Conv. A/D
   set_adc_channel(0);           //Selecion del canal 0 
   delay_us(20);
    while(TRUE){                 // Ciclo while infinito
        var = read_adc();        // Se asigna a var la lectura del Canal 0  
        output_b(var);           // Se muestra  var en el puerto B 
        printf("Decimal = %lu, Hexadecimal = 0x%3lx\n\r",var, var);
        lcd_gotoxy(1,1);
        printf(lcd_putc,"Vin = %2.2f V\n", var/204.60);
        delay_ms(1000);          // Retardo de 20us (microsegundos)
    }
}
