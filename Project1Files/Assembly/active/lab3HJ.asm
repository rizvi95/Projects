CSEG

$NOLIST
$include(math32.inc)   ; A library of 32bit math functions
$LIST

Send_BCD mac
	push ar0
	mov r0, %0
	lcall ?Send_BCD
	mov a, #'\r'
    lcall putchar
    mov a, #'\n'
    lcall putchar
	pop ar0
endmac

; Configure the serial port and baud rate
InitSerialPort:
    ; Since the reset button bounces, we need to wait a bit before
    ; sending messages, otherwise we risk displaying gibberish!
    mov R1, #222
    mov R0, #166
    djnz R0, $   ; 3 cycles->3*45.21123ns*166=22.51519us
    djnz R1, $-4 ; 22.51519us*222=4.998ms
    ; Now we can proceed with the configuration
	orl	PCON,#0x80
	mov	SCON,#0x52
	mov	BDRCON,#0x00
	mov	BRL,#BRG_VAL
	mov	BDRCON,#0x1E ; BDRCON=BRR|TBCK|RBCK|SPD;
    ret

; Send a character using the serial port
putchar:
    jnb TI, putchar
    clr TI
    mov SBUF, a
    ret

; Send a constant-zero-terminated string using the serial port
SendString:
    clr A
    movc A, @A+DPTR
    jz SendStringDone
    lcall putchar
    inc DPTR
    sjmp SendString
SendStringDone:
    ret
    
INIT_SPI:
	setb MY_MISO ; Make MISO an input pin
 	clr MY_SCLK ; For mode (0,0) SCLK is zero
 	ret

DO_SPI_G:
 	push acc
 	mov R1, #0 ; Received byte stored in R1
 	mov R2, #8 ; Loop counter (8-bits)
DO_SPI_G_LOOP:
 	mov a, R0 ; Byte to write is in R0
 	rlc a ; Carry flag has bit to write
 	mov R0, a
 	mov MY_MOSI, c
 	setb MY_SCLK ; Transmit
 	mov c, MY_MISO ; Read received bit
 	mov a, R1 ; Save received bit in R1
 	rlc a
 	mov R1, a
 	clr MY_SCLK
 	djnz R2, DO_SPI_G_LOOP
 	pop acc
 	ret
 
Hello_World:
    DB  'Hello, World!', '\r', '\n', 0
    
Delay:
	mov R1, #222
    mov R0, #166
    djnz R0, $   ; 3 cycles->3*45.21123ns*166=22.51519us
    djnz R1, $-4 ; 22.51519us*222=4.998ms
    reti
    
Left_blank mac
	mov a, %0
	anl a, #0xf0
	swap a
	jz Left_blank_%M_a
	ljmp %1
Left_blank_%M_a:
	Display_char(#' ')
	mov a, %0
	anl a, #0x0f
	jz Left_blank_%M_b
	ljmp %1
Left_blank_%M_b:
	Display_char(#' ')
endmac
   
; Sends 10-digit BCD number in bcd to the LCD 
Display_10_digit_BCD:
	Set_Cursor(2, 7)
	Display_BCD(bcd+4)
	Display_BCD(bcd+3)
	Display_BCD(bcd+2)
	Display_BCD(bcd+1)
	Display_BCD(bcd+0)
	; Replace all the zeros to the left with blanks
	Set_Cursor(2, 7)
	Left_blank(bcd+4, skip_blank)
	Left_blank(bcd+3, skip_blank)
	Left_blank(bcd+2, skip_blank)
	Left_blank(bcd+1, skip_blank)
	mov a, bcd+0
	anl a, #0f0h
	swap a
	jnz skip_blank
	Display_char(#' ')
skip_blank:
	ret
	
Display_10_digit_BCD_2:
	Set_Cursor(1, 7)
	Display_BCD(bcd+4)
	Display_BCD(bcd+3)
	Display_BCD(bcd+2)
	Display_BCD(bcd+1)
	Display_BCD(bcd+0)
	; Replace all the zeros to the left with blanks
	Set_Cursor(1, 7)
	Left_blank(bcd+4, skip_blank_2)
	Left_blank(bcd+3, skip_blank_2)
	Left_blank(bcd+2, skip_blank_2)
	Left_blank(bcd+1, skip_blank_2)
	mov a, bcd+0
	anl a, #0f0h
	swap a
	jnz skip_blank_2
	Display_char(#' ')
skip_blank_2:
	ret

	; Sends 10-digit BCD number in BCD to the SPI
Send_10_digit_BCD:
	Send_BCD(bcd+4)
	Send_BCD(bcd+3)
	Send_BCD(bcd+2)
	Send_BCD(bcd+1)
	Send_BCD(bcd+0)
	ret

?Send_BCD:
	push acc
	; Write most significant digit
	mov a, r0
	swap a
	anl a, #0fh
	orl a, #30h
	lcall putchar
	; write least significant digit
	mov a, r0
	anl a, #0fh
	orl a, #30h
	lcall putchar
	pop acc
	ret

;LM355
;Temp = 100(V_Out - 2.73) = 100*V_Out - 273
GET_LM355_TEMP:
    Get_ADC_Channel(#10000000b)
    
    mov x+0, ADC_Result+0
    mov x+1, ADC_Result+1
    mov x+2, #0
    mov x+1, #0
    
    Load_y(100)
    lcall mul32
    
    Load_y(273)
    lcall sub32
    
    ;Store the LM355 Temp in Result
    mov Result+0, x+0
    mov Result+1, x+1
 	ret

;____________________________________
 ;*************************************

; This is the code that converts the amplified voltage from the the k-type thermocouple 
; to temperature data for use. 
; Current Parameters: 
;		Op-amp gain: ~200
;		Thermocouple conversion: 41 uV/celcius
; 		Reference Voltage: 4.096 
; inputs
;*************************************		
;------------------------------------- 
GET_THERMO_TEMP:
    Get_ADC_Channel_milliV(#10010000b)
    
    ;Move thermo milli_voltage
    mov x+0, ADC_Result+0
    mov x+1, ADC_Result+1
    mov x+2, #0
    mov x+3, #0
    
    ;Multiply by inverse 41uV = 24390 (div 10 see lower step)
    Load_y(2439)
    lcall mul32
    
    ;Divide by gain
    Load_y(205)
    lcall div32
    
    ;Divide by 1000 (x10 see upper step) to adjust for milli_v
    Load_y(100)
    lcall div32
    
    ;Add the temp from the LM355
    mov y+0, Result+0
    mov y+1, Result+1
    mov y+2, Result+2
    mov y+3, Result+3
    lcall add32
    
    ;Store the Thermo coupler result for later use
    mov Result_Thermo+0, x+0
    mov Result_Thermo+1, x+1
  	ret		


GET_TEMP_DATA: 
	jnb one_second_flag, GET_TEMP_DATA_END
	clr one_second_flag ; We clear this flag in the main loop, but it is set in the ISR for timer 2
	
	;Gets, displays, and pushes ADC LM355 temp values
	lcall GET_LM355_TEMP
    ;lcall Display_10_digit_BCD
    
    ; Gets, displays, and pushes k-type thermocouple vlaues
	lcall GET_THERMO_TEMP
    ;lcall Send_10_digit_BCD
    ;lcall Display_10_digit_BCD_2
    
    ;lcall Delay
 GET_TEMP_DATA_END:
    ret
	


END