PROCESSOR 16f877
INCLUDE <p16f877.inc>

K	equ H'40'

	ORG 0
	GOTO INICIO
	ORG 5
INICIO:  MOVLW H'20'    ; Se carga en W la direccion inicial
		 MOVWF FSR		; carga en FSR la dirección contenida en W
		 GOTO MAYOR		
OTRA: INCF FSR			; incrementa el puntero
	  MOVF INDF, W 		; Mueve a W el contenido del registro apuntado
	  SUBWF K, W		; resta a K el valor del registro apuntado
	  BTFSC STATUS, C	; compara: K es menor que el dato apuntado C=0
	  GOTO MAYOR		; NO
	  GOTO SALTO		; SI
MAYOR: MOVF INDF, W		; mueve a W el contenido del registro apuntado
	   MOVWF K			; carga en K el contenido de W
SALTO: BTFSS FSR, 6		; El bit 6 de FSR se encuentra en 1?
       GOTO OTRA		; NO, borra el siguiente
       GOTO INICIO
       END