  processor 16f877
  include<p16f877.inc>

; Variables para el DELAY
valor1 equ h'21'
valor2 equ h'22'
valor3 equ h'23'
cte1 equ 10h 
cte2 equ 50h
cte3 equ 60h

;Definicion de variables a utilizar para
;comparar las entradas a través del puerto A
v0 equ h'24'
v1 equ h'25'
v2 equ h'26'
v3 equ h'27'
v4 equ h'28'


c0 equ 0h 
c1 equ 2h
c2 equ 4h
c3 equ 8h 
c4 equ 16h

  org 0h
  goto INICIO
  org 05h

INICIO:
       clrf PORTA
       bsf STATUS,RP0    ;Cambia la banco 1
       bcf STATUS,RP1 
       movlw h'0'
       movwf TRISB       ;Configura puerto B como salida
       clrf PORTB
            
       movlw 06h         ;Configura puertos A y E como digitales
       movwf ADCON1 
       movlw 3fh         ;Configura el puerto A como entrada
       movwf TRISA
       bcf STATUS,RP0    ;regresa al banco 0
CICLO:      
       movlw c0
       movwf v0
       movfw PORTA      ;Mueve lo que hay en PORTA a W
       xorwf v0,w       ;Verifica si la entrada es 00000000
       btfsc STATUS,Z   ;z=0?
       goto PARO        ;NO, entonces v0=W
                        ;SI, entonces v0!=W
       movlw c1
       movwf v1
       movfw PORTA
       xorwf v1,w       ;Verifica si la entrada es 00000010
       btfsc STATUS,Z
       goto HORARIO
       
       movlw c2
       movwf v2
       movfw PORTA
       xorwf v2,w       ;Verifica si la entrada es 000100
       btfsc STATUS,Z
       goto ANTIHORARIO

       movlw c3 
       movwf v3
       movfw PORTA
       xorwf v3,w      ;Verifica si la entrada es 001000
       btfsc STATUS,Z
       goto  HORARIO1

       movlw c4
       movwf v4        ;Verifica si la entrada es 010000
       movfw PORTA
       xorwf v4,w
       btfsc STATUS,Z
       goto ANTIHORARIO1

PARO:
       movlw h'00'      ;MOTOR IZQ=OFF DER=OFF
       movwf PORTB
       goto CICLO

HORARIO:
        movlw b'1100'   ;MOTOR IZQ=OFF DER=ON DIR1=1
        movwf PORTB
        call retardo       
        goto CICLO

ANTIHORARIO:
        movlw b'1000'    ;MOTOR IZQ=OFF DER=ON DIR1=0
        movwf PORTB
        call retardo        
        goto CICLO

HORARIO1: 
       movlw b'0011'     ;MOTOR IZQ=ON DER=OFF DIR2=1
       movwf PORTB
       call retardo
       goto CICLO

ANTIHORARIO1:
       movlw b'0010'    ;MOTOR IZQ=ON DER=OFF DIR2=0
       movwf PORTB
       call retardo
       goto CICLO
       
retardo movlw cte1   ;;Rutina que genera un DELAY
     movwf valor1
tres movwf cte2
     movwf valor2
dos  movlw cte3
     movwf valor3
uno  decfsz valor3 
     goto uno 
     decfsz valor2
     goto dos
     decfsz valor1   
     goto tres
     return
     end