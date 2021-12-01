	PROCESSOR 16f877 		;Indica versión de procesador
	INCLUDE <p16f877.inc>	;Incluye librería de la versión del procesador

K 	equ H'20'				;Localidad de memoria 26
L 	equ H'21'				;Localidad de memoria 27

		ORG 0				;Especifica un origen (Vector de reset)
		GOTO INICIO			;Código del programa

		ORG 5				;Indica origen para inicio del programa
INICIO: MOVLW H'05'			;Mueve el número 05 en hexadecimal a W
		ADDWF K,0			;Suma aritmetica de K almacenada en W
		MOVWF L				;Mueve el contenido del registro W a L
		GOTO INICIO			;Regresa a INICIO
		END					;Directiva de fin de programa