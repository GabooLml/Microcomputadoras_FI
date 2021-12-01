#include <16F877.h>              //Librer�a del microcontrolador.
#fuses HS,NOWDT,NOPROTECT
#use delay(clock=20000000)       //Frecuencia del reloj.
#org 0x1F00, 0x1FFF void loader16f877(void){}
#use i2c(MASTER, SDA=PIN_C4, SCL=PIN_C3,SLOW, NOFORCE_SW) //Configurando modo
int contador=0;                                           // esclavo.

void escribir_i2c(){
   i2c_start();                  //Inicia la comunicaci�n I2C.
   i2c_write(0x42);              //Modo escritura direcci�n.
   i2c_write(contador);          //Modo escritura valor.
   i2c_stop();                   //Fin de la comunicaci�n.
}

void main(){
   while(true){                  //Ciclo infinito
      escribir_i2c();            //Llamada a funci�n para escritura de datos
      delay_ms(500);             //por comunicaci�n I2C.
      contador++;
      output_b(contador);        //Se muestra el valor del contador en el
   }                             //puerto B.
}
