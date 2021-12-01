#include <16F877.h>                                //Librería de microcomtrolador
#fuses HS,NOPROTECT,NOWDT
#use delay(clock=20000000)                         //Frec. de Osc. 20Mhz
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)     //Configuración Puerto SERIAL
#org 0x1F00, 0x1FFF void loader16f877(void) {}
#use i2c(MASTER, SDA=PIN_C4, SCL=PIN_C3,SLOW, NOFORCE_SW)
#include <i2c_Flex_LCD.c>

byte const display[21]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20};

int aux = 0, bandera = 0;
int contador = 0, conteo = 0;    //Variables TIMER0
int cambiob0 = 0, cambiob4 = 0, cambiob5 = 0, cambiob6 = 0,cambiob7 = 0;
char dato;

void escribir_i2c(){
   i2c_start();
   i2c_write(0x42);
   i2c_write(conteo);
   i2c_stop();
}

#int_rtcc
void clock_isr(){
   contador++;
   if(contador == 15){
      escribir_i2c();
      conteo++;
      contador = 0;
   }
}

#int_rda
void recepcion_serie(){
   dato = getchar();
   printf("\n\r");
   printf("Se recibio el dato: %c\n\r", dato);
   }
   
#int_rb
void cambio_bits(){
   if(input(Pin_B4) == 1){
         cambiob4++;
         lcd_gotoxy(1,1);
         printf(LCD_PUTC, "B4=%d\n", cambiob4);
      }
   if(input(Pin_B5) == 1){
         cambiob5++;
         lcd_gotoxy(10,1);
         printf(LCD_PUTC, "B5=%d\n", cambiob5);
      }
   if(input(Pin_B6) == 1){
         cambiob6++;
         lcd_gotoxy(1,2);
         printf(LCD_PUTC, "B6=%d\n", cambiob6);
      }
   if(input(Pin_B7) == 1){
         cambiob7++;
         lcd_gotoxy(10,2);
         printf(LCD_PUTC, "B7=%d\n", cambiob7);
      }
}

#int_ext
void state_b0(){
      if(input(Pin_B0) == 1){
         cambiob0++;
         printf("El pin B0 ha cambiado %d\n\r", cambiob0);
      }
}

void main(){
  set_timer0(0);
  setup_counters(RTCC_INTERNAL,RTCC_DIV_256);
  enable_interrupts(INT_RTCC);
  enable_interrupts(INT_RDA);
  enable_interrupts(INT_RB);
  enable_interrupts(INT_EXT);
  enable_interrupts(GLOBAL);
  lcd_init(0x4E,16,2);          //Inicializa el LCD y espeficia su dirección
  lcd_backlight_led(ON);        //Configura la iluminación de fondo.
  
   while(TRUE){
      if(aux <= 19 && bandera == 0){
         output_d(display[aux]);
         aux++;
         //delay_ms(1000);
      }
      else{
         bandera = 1;
      }
      if(aux != 0 && bandera == 1){
         output_d(display[aux]);
         aux--;
         //delay_ms(1000);
      }
      else{
         bandera = 0;
      }
   }
}

