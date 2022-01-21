#include <16F877.h>
#fuses HS, NOPROTECT, NOWDT
#use delay(clock=20000000)
#use i2c(MASTER, SDA=PIN_C4, SCL=PIN_C3, SLOW, NOFORCE_SW)

byte const display[61]={0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 
0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40, 0x41, 0x42, 0x43, 
0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x60};

int contador = 61;
int contador1 = 61;
int verde = 67;
int amarillo = 76;
int rojo = 176;
int bandera = 0;

void contador_i2c(){
   i2c_start();
   i2c_write(0x40);
   i2c_write(display[contador]);
   i2c_stop();
}

void contador1_i2c(){
   i2c_start();
   i2c_write(0x42);
   i2c_write(display[contador1]);
   i2c_stop();
}

void semaforo_verde_i2c(){
   i2c_start();
   i2c_write(0x44);
   i2c_write(verde);
   i2c_stop();
}

void semaforo_apagado_i2c(){
   i2c_start();
   i2c_write(0x44);
   i2c_write(0x40);
   i2c_stop();
}

void semaforo_amarillo_i2c(){
   i2c_start();
   i2c_write(0x44);
   i2c_write(amarillo);
   i2c_stop();
}

void semaforo_rojo_i2c(){
   i2c_start();
   i2c_write(0x44);
   i2c_write(rojo);
   i2c_stop();
}

void semaforo1_verde_i2c(){
   i2c_start();
   i2c_write(0x46);
   i2c_write(verde);
   i2c_stop();
}

void semaforo1_apagado_i2c(){
   i2c_start();
   i2c_write(0x46);
   i2c_write(0x40);
   i2c_stop();
}

void semaforo1_amarillo_i2c(){
   i2c_start();
   i2c_write(0x46);
   i2c_write(amarillo);
   i2c_stop();
}

void semaforo1_rojo_i2c(){
   i2c_start();
   i2c_write(0x46);
   i2c_write(rojo);
   i2c_stop();
}

#int_rb
void peticion_cambio(){
   if(input(PIN_B4) == 1){
         contador1 = 0;
         contador1_i2c();
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_verde_i2c();
         delay_ms(500);
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_verde_i2c();
         delay_ms(500);
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_verde_i2c();
         delay_ms(500);
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_verde_i2c();
         delay_ms(500);
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_amarillo_i2c();
         delay_ms(2000);
         contador1 = 61;
         bandera = 1;
   }
   if(input(PIN_B5) == 1){
         contador1 = 0;
         contador1_i2c();
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_verde_i2c();
         delay_ms(500);
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_verde_i2c();
         delay_ms(500);
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_verde_i2c();
         delay_ms(500);
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_verde_i2c();
         delay_ms(500);
         semaforo_apagado_i2c();
         delay_ms(500);
         semaforo_amarillo_i2c();
         delay_ms(2000);
         contador1 = 61;
         bandera = 1;
   }
   if(input(PIN_B6) == 1){
         contador = 0;
         contador_i2c();
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_verde_i2c();
         delay_ms(500);
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_verde_i2c();
         delay_ms(500);
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_verde_i2c();
         delay_ms(500);
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_verde_i2c();
         delay_ms(500);
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_amarillo_i2c();
         delay_ms(2000);
         contador = 61;
         bandera = 0;
   }
   if(input(PIN_B7) == 1){
         contador = 0;
         contador_i2c();
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_verde_i2c();
         delay_ms(500);
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_verde_i2c();
         delay_ms(500);
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_verde_i2c();
         delay_ms(500);
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_verde_i2c();
         delay_ms(500);
         semaforo1_apagado_i2c();
         delay_ms(500);
         semaforo1_amarillo_i2c();
         delay_ms(2000);
         contador = 61;
         bandera = 0;
   }
}

void main(){
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
   while(TRUE){
      if(bandera == 0){
         if(contador1 > 0){
            contador1_i2c();
            semaforo_verde_i2c();
            contador_i2c();
            semaforo1_rojo_i2c();
            delay_ms(250);
            contador1--;
         }
         else{
            contador1 = 0;
            contador1_i2c();
            semaforo_apagado_i2c();
            delay_ms(500);
            semaforo_verde_i2c();
            delay_ms(500);
            semaforo_apagado_i2c();
            delay_ms(500);
            semaforo_verde_i2c();
            delay_ms(500);
            semaforo_apagado_i2c();
            delay_ms(500);
            semaforo_verde_i2c();
            delay_ms(500);
            semaforo_apagado_i2c();
            delay_ms(500);
            semaforo_verde_i2c();
            delay_ms(500);
            semaforo_apagado_i2c();
            delay_ms(500);
            semaforo_amarillo_i2c();
            delay_ms(2000);
            contador1 = 61;
            bandera = 1;
         }
      }
      else{
         if(contador > 0){
            contador_i2c();
            semaforo1_verde_i2c();
            semaforo_rojo_i2c();
            delay_ms(250);
            contador--;
         }
         else{
            contador = 0;
            contador_i2c();
            semaforo1_apagado_i2c();
            delay_ms(500);
            semaforo1_verde_i2c();
            delay_ms(500);
            semaforo1_apagado_i2c();
            delay_ms(500);
            semaforo1_verde_i2c();
            delay_ms(500);
            semaforo1_apagado_i2c();
            delay_ms(500);
            semaforo1_verde_i2c();
            delay_ms(500);
            semaforo1_apagado_i2c();
            delay_ms(500);
            semaforo1_verde_i2c();
            delay_ms(500);
            semaforo1_apagado_i2c();
            delay_ms(500);
            semaforo1_amarillo_i2c();
            delay_ms(2000);
            contador = 61;
            bandera = 0;
         }
      }
   }
}
