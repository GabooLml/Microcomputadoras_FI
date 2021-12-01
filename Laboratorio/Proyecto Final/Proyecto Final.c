#include <16F877.h>                                //Librería de microcomtrolador
#fuses HS,NOPROTECT,NOWDT
#device ADC = 10
#use delay(clock=20000000)                         //Frec. de Osc. 20Mhz
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)     //Configuración Puerto SERIAL
#org 0x1F00, 0x1FFF void loader16f877(void) {}
#use i2c(MASTER, SDA=PIN_C4, SCL=PIN_C3,SLOW, NOFORCE_SW)
#include <i2c_Flex_LCD.c>

int16 conversion = 0;
int contador = 0, carga = 0;
char dato;

void escribir_i2c(){
   i2c_start();
   i2c_write(0x42);
   i2c_write(contador);
   i2c_stop();
}

void leer_i2c(){                 //Función para leer datos del esclavo.
   i2c_start();                  //Inicia la comunicación I2C.
   i2c_write(0x41);              //Modo escritura dirección.
   carga = i2c_read(0);         //Lectura de los datos del esclavo.
   i2c_stop();                   //Fin de la comunicación.
}

#int_rda
void recepcion_serie(){
   dato = getchar();
   printf("Se recibio el dato: %c\n\r", dato);
}
   
void main(){
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   lcd_init(0x4E,16,2);
   lcd_backlight_led(ON);
   setup_port_a(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   delay_us(20);
   while(TRUE){
      switch(dato)
      {
         case'0':
            lcd_gotoxy(1,1);
            printf(LCD_PUTC, "Gabriel   ");
            lcd_gotoxy(1,2);
            printf(LCD_PUTC, "Mariana   ");
            break;
            
          case'1':
            escribir_i2c();
            contador++;
            delay_ms(200);
            break;
            
          case'2':
            conversion = read_adc();
            lcd_gotoxy(1,1);
            printf(LCD_PUTC, "Voltaje");
            lcd_gotoxy(1,2);
            printf(LCD_PUTC, "Vin %2.2f V", conversion/204.60);
            break;
            
          case'3':
            leer_i2c();
            lcd_gotoxy(1,1);
            printf(LCD_PUTC, "Dec        ");
            lcd_gotoxy(1,2);
            printf(LCD_PUTC, "%u         ", carga);
            break;
            
          case'4':
            leer_i2c();
            lcd_gotoxy(1,1);
            printf(LCD_PUTC, "Hex        ");
            lcd_gotoxy(1,2);
            printf(LCD_PUTC, "%x         ", carga);
            break;
            
          default:
            lcd_gotoxy(1,1);
            printf(LCD_PUTC, "Dato");
            lcd_gotoxy(1,2);
            printf(LCD_PUTC, "invalido");
      }
   }
}

