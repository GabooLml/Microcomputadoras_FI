PROCESSOR 16f877
INCLUDE <p16f877.inc>

K	equ H'40'	;Registro que guarda el primer numero a comparar
L	equ H'41'	;Registro que guarda el segundo numero a comparar
LIM equ H'42'	;registro que guarda la direccion limite de la lista
BAND equ H'43'	;bandera para  verificar si la lista esta ordenada
	ORG 0
	GOTO INICIO
	ORG 5
INICIO:  MOVLW H'2F'
		 MOVWF LIM		; Ce carga a LIM la direccion limite de la lista (LIM = 2F)
		 MOVLW H'20'    ; Se carga en W la direccion inicial
		 MOVWF FSR		; carga en FSR la dirección contenida en W	(W = 20)
		 MOVLW H'00'
		 MOVWF BAND		; Inicializa BAND=0 indicando que no hay cambios en la lista
		 
NUM1:	 MOVF INDF, W	; se carga a W el contenido de lo que apunta FSR
		 MOVWF K		; se carga en K el contenido de W (K = W)
	
NUM2: INCF FSR			; incrementa el puntero
	  MOVF INDF, W 		; Se carga a W el contenido del registro apuntado
	  
COMPARA: SUBWF K, W			; resta a K el valor del registro apuntado (W = K - W)
	  	 BTFSC STATUS, C	; compara: ¿ NUM1 > NUM2 ?
	  	 GOTO CAMBIO		; C=0 : SI
	  	 GOTO LISTAF		; c=1 : NO

CAMBIO: MOVF INDF, W	; carga en W el contenido del registro apuntado
	    MOVWF K			; carga en K el contenido de W
		DECF FSR		; regresamos al numero anterior
		MOVF INDF, W	; carga en W el numero anterior (el que apunta FSR)
		MOVWF L			; guarda el numero anterior en L (L = W)
		MOVF K, W		; se carga en W el numero menor. Se mueve a W el contenido de K (W = K)
		MOVWF INDF		; se carga a donde apunta FSR el contenido de W
						; (se coloca el numero menor en una posicion anterior)
		
		INCF FSR		; Incrementeamos el puntero (volvemos a la posicion original)
		MOVF L, W		; se carga a W el contenido de L (W = L)
		MOVWF INDF		; se encarga en la pos. que apunta FSR, el contenido de W
						; (se coloca el numero mayor en una posicion ascendente)

		MOVF INDF, W	; cargamos en W el contenido del del registro apuntado
		MOVWF K			; cargamos en K el contenido de W; se actualiza el registro de K
						; para en una comparacion futura
		
		MOVLW H'01' 
		MOVWF BAND		; se carga a BAND=01, esto indica que hubo almenos un cambio 
						; al revisar la lista de nums.
						; Hasta que este CONT se mantenga en CONT=00 habiendo recorrido
						; la lista completa podemos estar seguros que esta ordenada.

LISTAF:					; Fin de la lista?
		 MOVF LIM, W 		;Se carga a W el contenido de LIM (W = LIM)
		 SUBWF FSR, W		; resta a FSR el valor del registro LIM (W = FSR - W)
	  	 BTFSS STATUS, C	; compara: el apuntador (FSR) es menor que LIM (¿FSR < LIM?)
	  	 GOTO NUM1			; c=1 : SI ; Continua con los siguientes numeros
	  	 
		 MOVLW H'01'		; C=0 : NO ; Fin de la lista; se limpia el registro W
 		 SUBWF BAND, W  	; resta para saber si esta ordenado (W = BAND - W)
		 BTFSS STATUS, C	; ¿Esta ordenado?
		 GOTO $				; c=1 : SI ; Lista Ordenada  
		 GOTO INICIO		; C: NO ; Se revisa de nuevo la lista desde el principio 	 

		 END