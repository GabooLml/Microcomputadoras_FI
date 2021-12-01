#include <16f877.h>              //Librería de microcomtrolador
#device ADC = 10                 //Resolución Conv A/D
#fuses HS,NOPROTECT,
#use delay(clock=20000000)       //Frec. de Osc. 20Mhz
#define use_portd_lcd true       //Se define el puerto D como enlace al LCD
#include <lcd.c>
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)   //Configuración Puerto SERIAL
#org 0x1F00, 0x1FFF void loader16F877(void) {}
 
int16 var;
int16 contador=0;
int16 contador1=0;
int16 contador2=0;
int aux = 0;

#int_rtcc                        
void clock_isr(){                //Rutina de interrupción por TIMER0.
   contador++;                   //Contadores que permitirán las interrupciones
   contador1++;                  //independientes de cada uno de los casos
   contador2++;                  //solicitados.
   
   if(contador2==19){            //19 * 13us = 248 ms
      output_b(aux);             //Se imprime el contador de 8 bits en puerto
      aux++;                     //B
      contador2 = 0;
   }
   
   if(contador1==763){           //763 * 10.13 us = 9.99 s
      lcd_gotoxy(1,1);           //Se imprime la conversión en el LCD
      printf(lcd_putc,"Vin = %2.2f V", var/204.60);//1023 / 204.0 = 5
      contador1 = 0;
   }
   
   if(contador==1908){           //1908 * 13.10 us = 24.99 s
     printf("Gabriel Rojas Méndez\n\r");
     printf("Numero de cuenta:     314141712\n\r");
     printf("Grupo de teoria:      1\n\r");
     printf("Grupo de laboratorio: 4\n\r");
     printf("===============================\n\r");
     printf("Mariana Ivette Carreón Guzmán\n\r");
     printf("Numero de cuenta:     312103914\n\r");
     printf("Grupo de teoria:      4\n\r");
     printf("Grupo de laboratorio: 4\n\r");
     contador=0;
   }
}

void main(){
   lcd_init();
   setup_port_a(ALL_ANALOG);              //Configura PORTA como analógico
   setup_adc(ADC_CLOCK_INTERNAL);         //Relog interno de Conv. A/D
   set_adc_channel(0);                    //Selección del Canal 0
   set_timer0(0);                         //Inicia el timer0 en 00H
   setup_counters(RTCC_INTERNAL,RTCC_DIV_256);
   enable_interrupts(INT_RTCC);           //Habilita la interrupción TIMER0
   enable_interrupts(GLOBAL);             //Habilita interrupciones generales
      
   while(TRUE){
      delay_us(20);                       //Retardo 
      var=read_adc();                     //Lee el resultado de la Conversión
      delay_us(20);                       //Retardo
    }
}
