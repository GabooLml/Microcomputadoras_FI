	PROCESSOR 16f877		;Indica versión de procesador
	INCLUDE <p16f877.inc>	;Incluye librería de la versión del procesador
DIR equ H'27'				;Localidad de memoria 26
DIRA equ H'20'				;Localidad de memoria 27

		ORG 0				;Especifica un origen (Vector de reset)
		GOTO INICIO			;Código del programa

		ORG 5				;Indica origen para inicio del programa
INICIO: MOVLW H'07'			;Mueve el numero 07 a W
		MOVWF DIRA			;Se copia W a DIRA
		MOVLW H'01'			;Mueve el número 01 a W
		MOVWF DIR			;Copia W a DIR
		GOTO DOBLE			;Salta a DOBLE

DOBLE: 	ADDWF DIR, W		;Suma aritmetica almacenada en W
		MOVWF DIR			;Mueve el contenido del registor W a DIR
		DECF DIRA			;Se hace un decremento en DIRA
		BTFSC STATUS,2		;Verifica la bandera de status de DIRA
		GOTO INICIO			;Regresa e INICIO
		GOTO DOBLE			;Regresa al inicio por si quedan más registros por contar
		END