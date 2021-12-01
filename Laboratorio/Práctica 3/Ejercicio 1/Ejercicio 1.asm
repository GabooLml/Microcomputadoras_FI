		 processor 16f877 		;Indica la versi�n de procesador
		 include <p16f877.inc> 	;Incluye la librer�a de la versi�n del procesador

valor1 	 equ h'21'			;Asigna el valor de 21 a valor1
valor2 	 equ h'22'			;Asigna el valor de 22 a valor2
valor3 	 equ h'23'			;Asigna el valor de 23 a valor3
cte1 	 equ 20h			;asigna el valor de 20 a cte1
cte2 	 equ 50h			;asigna el valor de 50 a cte2
cte3 	 equ 60h			;asigna el valor de 60 a cte3

		 ORG 0 				;Especifica un origen (vector de reset)
		 GOTO INICIO 		;C�digo del programa

		 ORG 5 				;Indica origen para inicio del programa
INICIO:  BSF STATUS, RP0	;Cambia al banco 0
		 BCF STATUS, RP1	;Regresa al banco 1
		 MOVLW H'0'			;Guarda en el registro W el valor 0
		 MOVWF TRISB		;Mueve el contenido del registro W al registro TRISB
		 BCF STATUS, RP0	;Pone en 0 el bit de RP0 del registro status
		 CLRF PORTB			;Borra el contenido del registro PORTB

LOOP2: 	 BSF PORTB, 0		;Pone en 1 el bit 0 del registro PORTB
	   	 CALL RETARDO		;Llama a la subrutina RETARDO
	   	 BCF PORTB, 0		;Pone en 0 el bit 0 del registo PORTB
	   	 CALL RETARDO		;Llama a la subrutina RETARDO
	   	 GOTO LOOP2			;Salta a LOOP2

RETARDO: MOVLW cte1			;Guarda en el registo W el valor de cte1
		 MOVWF valor1		;Mueve el contenido del registro W al registro valor1
		
TRES: 	 MOVLW cte2			;Guarda en el registo W el valor de cte2
	  	 MOVWF valor2		;Mueve el contenido del registro W al registro valor2

DOS: 	 MOVLW cte3			;Guarda en el registo W el valor de cte3
	 	 MOVWF valor3		;Mueve el contenido del registro W al registro valor3

UNO: 	 DECFSZ valor3		;Decrementa el registro valor3 hasta cero
	 	 GOTO UNO			;Salta a UNO
	 	 DECFSZ valor2		;Decrementa el registro valor2 hasta cero
	 	 GOTO DOS			;Salta a DOS
	 	 DECFSZ valor1		;Decrementa el registro valor1 hasta cero
	 	 GOTO TRES			;Salta a TRES
	 	 RETURN				;Regresa de la subrutina
	 	 END				;Directiva de fin de programa