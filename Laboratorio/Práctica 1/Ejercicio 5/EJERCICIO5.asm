	PROCESSOR 16f877		;Indica versión de procesador
	INCLUDE <p16f877.inc>	;Incluye librería de la versión del procesador
DIR equ H'28'				;Localidad de memoria 28
DIR2 equ H'20'				;Localidad de memoria 20

		ORG 0				;Especifica un origen (Vector de reset)
		GOTO INICIO			;Código del programa

		ORG 5				;Indica origen para inicio del programa
INICIO: MOVLW H'09'			;Mueve el numero 09 a W
		MOVWF DIR2			;Se copia W a DIR2
		MOVLW H'00'			;Mueve el número 00 a W
		MOVWF DIR			;Copia W a DIR
		GOTO CUENTA			;Salta a CUENTA

CUENTA: MOVLW H'01' 		;Mueve el número 01 a W
		ADDWF DIR			;Suma aritmetica de DIR almacenada en W
		DECF DIR2			;Se decrementa DIR2
		BTFSC STATUS, 2		;Se comprueba la bandera de status del ciclo
		GOTO DIEZ			;Salta a DIEZ
		GOTO CUENTA			;Salta a cuenta

DIEZ:   MOVF DIR, W			;Copia a W el valor de DIR
		SUBLW 19			;Sustrae el valor 19 de W
		BTFSC STATUS,2		;Verifca el status de la bandera por si el valor es 19
		GOTO VEINTE			;Si el valor es 19 entonces se finaliza con 20
		GOTO DIEZ2			;Si no es 19 continua con el otro conteo

DIEZ2: 	MOVLW H'10'			;Mueve el número 10 a W
		MOVWF DIR			;Copia W a DIR
		MOVLW H'09'			;Copia el número 09 a W
		MOVWF DIR2			;Copia W a DIR2
		GOTO CUENTA;		;Regresa a cuenta

VEINTE: MOVLW H'20'			;Copia el número 20 a W
		MOVWF DIR			;Copia W a DIR
		GOTO INICIO
		END