#include <16f877.h>        //Incluye la librería del microControlador
#fuses HS,NOPROTECT, 
#use delay(clock=20000000)  
#org 0x1F00, 0x1FFF void loader16F877(void) {}  

//Metodo que enciende y apaga LEDS del puerto B
void main()
{ 
   while(1)              //Ciclo  while infinito
   {  
      output_b(0xFF);    //Pone en alto todos los bits del puerto B 
      delay_ms(500);     //Retardo de 1s
      output_b(0x00);    //Pone en bajo todos los bits del puerto B
      delay_ms(500);     //Retrado de 1s
   }
}
