		PROCESSOR 16f877
		INCLUDE  <p16f877.inc>

		ORG 0
		GOTO INICIO
	
		ORG 5
INICIO: BCF STATUS, RP1  ; Pone en 0 el bit 6 (RP1) del registro STATUS
		BSF STATUS, RP0  ; Pone en 1 el bit 5 (RP0) del registro STATUS
		MOVLW 0X20		 ; W = 0x20
		MOVWF FSR		 ; Mueve el contenido de W al registro FSR (FSR=0x20)

LOOP:   MOVLW 0X5F		 ; Carga 0x5F en el registro W
		MOVWF INDF		 ; Mueve el contenido de W a la dir apuntada por FSR				 ; La dirección de memoria 0x20 tendrá el valor 0x5f
		INCF FSR		 ; incrementa el registro FSR (FSR = 0x21)
		BTFSS FSR, 6	 ; prueba que el bit 6(RP1) del registro FSR este en 1
		GOTO LOOP		 ; RP1 = 0
		GOTO $			 ; RP1 = 1
		END