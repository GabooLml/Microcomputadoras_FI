#include <16f877.h>              //Incluye la librer�a del microControlador
#fuses HS,NOWDT,NOPROTECT,NOLVP 
#use delay(clock=20000000)
#define use_portb_lcd true       //Declara el puerto B como comunicaci�n con
#include <lcd.c>                 //el LCD. Librer�a que contiene el LCD

void main()
{ 
    lcd_init();                  //Inicializaci�n del LCD
    while(TRUE)                  //Ciclo while infinito
    { 
        lcd_gotoxy(1,1);         //Funci�n para determinar la posici�n del LCD
        printf(lcd_putc," UNAM \n"); 
        lcd_gotoxy(1,2); 
        printf(lcd_putc," FI \n");
        delay_ms(300); 
     }
}
