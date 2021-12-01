#INCLUDE <16F877.H>              //Librería del microcontrolador
#fuses HS,NOWDT,NOPROTECT
#use delay(clock=20000000)       //Frecuencia de oscilación
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)  //Configuración y habilitación
#org 0x1F00, 0x1FFF void loader16F877(void) {}  //de comunicación serial

#int_EXT                         //Rutina de interrupción por detección de
VOID ext_int(){                  //flanco de RB0
   output_toggle(PIN_D0);        //Si el pin D0 está en 0 cambia a 1 y viceversa
}

void main() {
   ext_int_edge(L_TO_H);         //Configura el flanco a detectar (subida)
   enable_interrupts(INT_EXT);   //Habilita interrupción por detección de flanco de RB0.
   enable_interrupts(GLOBAL);    //Habilita interrupciones generales
   output_low(PIN_D0);           //Se garantiza que el PIN D0 inicie apagado
   while( TRUE ) {}              //Ciclo infinito
}
