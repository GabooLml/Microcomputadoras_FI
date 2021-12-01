#include <16f877.h>              // Librería del microcontrolador
#device ADC=10                   // Convertidor A/D indica resolución de 10 bits
#fuses HS,NOPROTECT,NOWDT,NOLVP
#use delay(clock=20000000)       //Frec. de Osc. 20Mhz
#define use_portd_lcd true       //Se define al puerto D como enlace al LCD
#include <lcd.c>
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)//Configuración del puerto SERIAL
#org 0x1F00, 0x1FFF void loader16F877(void) {}

int16 var;                       // Variable tipo entero
int16 contador=0;

#int_rtcc                        //Desbordamiento del TIMER0
void clock_isr(){                // Rutina de interrupcion por Timer0
    contador++;                  // Incrementa contador 
    if(contador==763){           //763 * 10.13 us ~~ 10 s
       output_b(var);            //Se muestra  resultado como salida  
       printf("Decimal = %lu, Hexadecimal = 0x%3lx\n\r",var, var);
       lcd_gotoxy(1,1);
       printf(lcd_putc,"Vin = %2.2f V", var/204.60);
       delay_ms(1000);
       contador=0;               // Inicializa contador, se reinicia  
    }
}

void main(){
    lcd_init();
    setup_port_a(ALL_ANALOG);    //Configuración del Puerto A como analógico  
    setup_adc(ADC_CLOCK_INTERNAL);  //Configuración del reloj interno ADC
    set_adc_channel(0);             //Configuración del Canal 0 
    set_timer0(0);                  // Inicia el timer0 en 00H
    setup_counters(RTCC_INTERNAL,RTCC_DIV_256); //Fuente de reloj y predivisor
    enable_interrupts(INT_RTCC);    // Habilita la interrupción TIMER0
    enable_interrupts(GLOBAL);      // Habilita interrupciones generales
   
    while(TRUE){                    // Ciclo while infinito
        delay_us(20);               // Retardo de 20us (microsegundos) 
        var = read_adc();           // resultado=valor de ADC
        delay_us(20);               // Retardo de 20us (microsegundos) 
    }
}
