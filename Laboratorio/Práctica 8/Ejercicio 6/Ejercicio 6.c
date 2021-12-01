#include <16f877.h>   //Incluye la librería del microprocesador
#fuses HS,NOPROTECT, 
#use delay(clock=20000000) //Frec. de oscilación 20Mhz

//Configura y activa el puerto SERIAL
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) 
#org 0x1F00, 0x1FFF void loader16F877(void) {} 

char var1;   //Define una variable tipo CHAR
int var2;    //Define una variable tipo entero

void main()
{
    while(1) //Ciclo While infinito
    {
        //Lee la variable que es escrita en la
        //Hyperterminal y la guarda en var1
        var1=getchar();  

        if (var1=='0'){
           printf("0\n\r");
           printf("Todos los bits apagados\n\r");
           output_b(0x00);   //Pone en bajo los bit's del puerto B
        }
        if (var1=='1'){
           printf("%c\n\r", var1);
           printf("Todos los bits encendidos\n\r");
           output_b(0xff);   //Pone en alto los bit del puerto B
        }
        if (var1=='2'){
           printf("%c\n\r", var1);
           printf("Corrimiento hacia la derecha\n\r");
           var2=0x80;       //Inicializa con el valor de "10000000"
           output_b(var2);   //Manda Var2 al puerto B
           delay_ms(500);    //Retardo 1/2s
           //Se define un ciclo que realizar un corrimiento
           //a la derecha
           do{
                var2=var2/2; //Realiza una divisón entre 2 lo que
                //permite realizar un corrimiento a la derecha
                output_b(var2);//Muestra var2 en el puerto B
                delay_ms(500);
           }while (var2!=1); //Repite el ciclo mientas var2 sea 
                //diferente de 0x01="00000001" 
        }
        if (var1=='3'){
           printf("%c\n\r", var1);
           printf("Corrimiento hacia la izquierda\n\r");
           var2=0x01;       //Inicializa con el valor de "00000001"
           output_b(var2);   //Manda var2 al puerto B
           delay_ms(500);    //Retardo 1/2s
           do{
                var2+=var2;    //Realiza corrimiento a la izquierda
                output_b(var2);//Manda var2 al puerto B
                delay_ms(500);
           }while (var2!=0x80);//Repite el ciclo mientras var2 sea
                               //diferente de 0x80=b"10000000"
        }
        if (var1=='4'){
            printf("%c\n\r", var1);
            printf("Corrimiento hacia la derecha e izquierda\n\r");
            //Seinicializa var2=b"10000000"
            var2=0x80;
            output_b(var2);
            delay_ms(500);
          
            //Ciclo que realiza corrimiento a la derecha
            do{
                var2=var2/2;
                output_b(var2); 
                delay_ms(500);
            }while (var2!=1);
            //Seinicializa var2=b"00000001"
            var2=0x01;
            output_b(var2);
            delay_ms(500);
          
            //Ciclo que realiza corrimiento a la izquierda
            do{
                var2+=var2;
                output_b(var2); 
                delay_ms(500);
            }while (var2!=0x80);
        }
        if (var1=='5'){
           printf("%c\n\r", var1);
           printf("Apaga y enciende los bits\n\r");
           output_b(0xff);     //Enciende los bits del puerto B
           delay_ms(500);
           output_b(0x00);     //Apaga los bits del puerto B 
           delay_ms(500); 
        }
        if (var1 > '5'){
           printf("%c \n\r", var1);
           printf("Entrada no valida\n\r");
        }
    } 
}
