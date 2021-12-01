#include <16f877.h>     //Incluye la librería del microControlador 
#fuses HS,NOPROTECT, 
#use delay(clock=20000000)//Frec. de Oscilación 20Mhz
#org 0x1F00, 0x1FFF void loader16F877(void) {}  

//Metodo que enciende y apaga  el bit 0 del puerto B
void main()  
{ 
   while(1) //Ciclo while infinito
   {  
      output_b(0x01);  //Enciende el bit 0 del puerto B 
      delay_ms(1000);  //Delay de 1s
      output_b(0x00);  //Apaga bits del puerto B
      delay_ms(1000);  //Delay de 1s
   }
} 
