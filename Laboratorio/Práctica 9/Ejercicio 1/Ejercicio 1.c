#include <16F877.h>              //Librería del microcontrolador.
#fuses HS,NOWDT,NOPROTECT
#use delay(clock=20000000)       //Frecuencia del reloj.
#use i2c(MASTER, SDA=PIN_C4, SCL=PIN_C3,SLOW, NOFORCE_SW) //Configurando modo
int contador=0;                                           //modo esclavo.

void escribir_i2c(){
   i2c_start();                  //Inicia la comunicación I2C.
   i2c_write(0x42);              //Modo escritura dirección
   i2c_write(contador);          //Modo escritura valor
   i2c_stop();                   //Fin de la comunicación.
}

void main(){
   while(true){                  //Ciclo infinito
      escribir_i2c();            //Llamada a función para escritura de datos
      delay_ms(500);             //por comunicación I2C.
      contador++;
   }
}
