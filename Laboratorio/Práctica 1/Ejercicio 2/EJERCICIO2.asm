	PROCESSOR 16f877		;Indica versi�n de procesador
	INCLUDE <p16f877.inc>	;Incluye librer�a de la versi�n del procesador
K 	equ H'20'					;Localidad de memoria 26
L 	equ H'21'					;Localidad de memoria 27
M 	equ H'22'					;Localidad de memoria 28

		ORG 0				;Especifica un origen (Vector de reset)
		GOTO INICIO			;C�digo del programa

		ORG 5				;Indica origen para inicio del programa
INICIO: MOVF K,W			;Mueve el contenido de K a W
		ADDWF L,0			;Suma aritmetica de L almacenada en W
		MOVWF M				;Copia W a M
		GOTO INICIO			;Regresa a INICIO
		END					;Directiva de fin de programa