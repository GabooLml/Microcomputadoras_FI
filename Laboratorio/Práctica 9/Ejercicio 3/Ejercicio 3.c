#include <16F877.h>              //Librería del microcontrolador.
#fuses HS,NOWDT,NOPROTECT,NOWDT,NOLVP
#use delay(clock=20000000)       //Frecuencia de reloj.
#org 0x1F00, 0x1FFF void loader16f877(void){}
#use i2c(MASTER, SDA=PIN_C4, SCL=PIN_C3,SLOW, NOFORCE_SW) //Configurando modo
#include <i2c_Flex_LCD.c>        //Librería para el uso del LCD| |esclavo

int contador=0;                  //Variable para llevar el conteo

void escribir_i2c(){
   i2c_start();                  //Inicia la comunicación I2C.
   i2c_write(0x42);              //Modo escritura dirección.
   i2c_write(contador);          //Modo escritura valor.
   i2c_stop();                   //Fin de la comunicación.
}

void main(){
   lcd_init(0x4E,16,2);          //Inicializa el LCD y espeficia su dirección
   lcd_backlight_led(ON);        //Configura la iluminación de fondo.
   while(true){
      lcd_gotoxy(1,1);
      printf(LCD_PUTC, "UNAM\n");
      lcd_gotoxy(1,2);
      printf(LCD_PUTC, "Contador = %X\n", contador);
      escribir_i2c();            //Llamada a fubción para escritura de datos.
      delay_ms(500);
      contador++;
      output_b(contador);        //Salida del conteo en el puerto B.
      }
}
