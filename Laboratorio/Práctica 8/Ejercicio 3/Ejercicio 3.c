#include <16f877.h>           //Incluye la librería del microControlador
#fuses HS,NOPROTECT, 
#use delay(clock=20000000) 
#org 0x1F00, 0x1FFF void loader16F877(void) {} 

int var1;                     //Define una variable tipo entero
                              //Metodo que lee el contenido del puerto A y muestra
                              //el resultado en el puerto B
void main()
{ 
    while(1)                  // Ciclo while infinito
    { 
       var1=input_a();        // Guarda en var1 el contenido del puerto A
       output_b(var1);        // Manda el contenido de var1 al puerto B
    } 
} 
