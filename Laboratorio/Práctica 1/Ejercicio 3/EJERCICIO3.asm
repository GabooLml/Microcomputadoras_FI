	PROCESSOR 16f877		;Indica versión de procesador
	INCLUDE <p16f877.inc>	;Incluye librería de la versión del procesador
J equ H'26'					;Localidad de memoria 26
K equ H'27'					;Localidad de memoria 27
C1 equ H'28'				;Localidad de memoria 28
R1 equ H'29'				;Localidad de memoria 29

		ORG 0				;Especifica un origen (Vector de reset)
		GOTO INICIO			;Código del programa

		ORG 5				;Indica origen para inicio del programa
INICIO: MOVF J,W			;Mueve el contenido de J a w
		ADDWF K,0			;Suma aritmetica de K almacenada en W
		MOVWF R1			;Copia W a M
		BTFSS STATUS, 0		;Verifica la bandera de status de Carry
		GOTO FALSE			;Si bandera de Carry es igual a 1
		GOTO TRUE			;Si bandera de Carry es igual a 0

TRUE: 	MOVLW H'01'			;Mueve el número 00 a W
		MOVWF C1			;Mueve el contenido del registor W a C1
		GOTO INICIO			;Regresa e INICIO

FALSE: 	MOVLW H'00'			;Mueve el número 00 a W
		MOVWF C1			;Mueve el contenido del registor W a C1
		GOTO INICIO			;Regresa e INICIO

		END					;Directiva de fin de programa