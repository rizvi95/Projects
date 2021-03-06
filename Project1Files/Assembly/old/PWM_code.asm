
$MODLP51

; There is a couple of typos in MODLP51 in the definition of the timer 0/1 reload
; special function registers (SFRs), so:

TIMER0_RELOAD_L DATA 0xf2
TIMER1_RELOAD_L DATA 0xf3
TIMER0_RELOAD_H DATA 0xf4
TIMER1_RELOAD_H DATA 0xf5

CLK           EQU 22118400 ; Microcontroller system crystal frequency in Hz
TIMER0_RATE   EQU 4096     ; 2048Hz squarewave (peak amplitude of CEM-1203 speaker)
TIMER0_RELOAD EQU ((65536-(CLK/TIMER0_RATE)))
TIMER2_RATE   EQU 1000     ; 1000Hz, for a timer tick of 1ms
TIMER2_RELOAD EQU ((65536-(CLK/TIMER2_RATE)))

DUTY_0    EQU 0
DUTY_20   EQU 51   ;256 * 0.2
DUTY_50   EQU 128  ;256 * 0.5
DUTY_80   EQU 204  ;256 * 0.8
DUTY_100  EQU 255

org 0x0000
   ljmp MainProgram

; External interrupt 0 vector (not used in this code)
org 0x0003
	reti

; Timer/Counter 0 overflow interrupt vector
org 0x000B
	reti

; External interrupt 1 vector (not used in this code)
org 0x0013
	reti

; Timer/Counter 1 overflow interrupt vector (not used in this code)
org 0x001B
	reti

; Serial port receive/transmit interrupt vector (not used in this code)
org 0x0023 
	reti
	
; Timer/Counter 2 overflow interrupt vector
org 0x002B
	reti
	
DSEG at 0x30
Count1ms:      ds 2 ; Used to determine when half second has passed
x:             ds 4
y:             ds 4
bcd:           ds 5

BSEG

CSEG
	
;---------------------------------;
; Routine to initialize the ISR   ;
; for timer 1                     ; 
;---------------------------------;
Timer1_Init:
	mov a, TMOD
	anl a, #00001111B
	orl a, #00010000B
	mov TMOD, a
	
	mov TH1, #0             ;Current count value
	mov TL1, #0                  ;Linear Prescaling
	
	mov TIMER1_RELOAD_H, #DUTY_0 ;Duty cycle percentage. Replace this value to change the duty cycle
	mov TIMER1_RELOAD_L, #0      ;Frequency scaling/adjust f_out = f_sys/(256 * (256 - TL))
	
	mov a, TCONB ;load TCONB for PWM settings
	anl a, #00000000B
	orl a, #10000000B
	mov TCONB, a
	
	setb TR1
	reti
	
MainProgram:
    mov SP, #7FH ; Set the stack pointer to the begining of idata
    lcall Timer1_Init
    
forever:
	sjmp forever
=======
$MODLP51

; There is a couple of typos in MODLP51 in the definition of the timer 0/1 reload
; special function registers (SFRs), so:

TIMER0_RELOAD_L DATA 0xf2
TIMER1_RELOAD_L DATA 0xf3
TIMER0_RELOAD_H DATA 0xf4
TIMER1_RELOAD_H DATA 0xf5

CLK           EQU 22118400 ; Microcontroller system crystal frequency in Hz
TIMER0_RATE   EQU 4096     ; 2048Hz squarewave (peak amplitude of CEM-1203 speaker)
TIMER0_RELOAD EQU ((65536-(CLK/TIMER0_RATE)))
TIMER2_RATE   EQU 1000     ; 1000Hz, for a timer tick of 1ms
TIMER2_RELOAD EQU ((65536-(CLK/TIMER2_RATE)))

DUTY_0    EQU 0
DUTY_20   EQU 51   ;256 * 0.2
DUTY_50   EQU 128  ;256 * 0.5
DUTY_100  EQU 255

org 0x0000
   ljmp MainProgram

; External interrupt 0 vector (not used in this code)
org 0x0003
	reti

; Timer/Counter 0 overflow interrupt vector
org 0x000B
	ljmp Timer0_ISR

; External interrupt 1 vector (not used in this code)
org 0x0013
	reti

; Timer/Counter 1 overflow interrupt vector (not used in this code)
org 0x001B
	reti

; Serial port receive/transmit interrupt vector (not used in this code)
org 0x0023 
	reti
	
; Timer/Counter 2 overflow interrupt vector
org 0x002B
	ljmp Timer2_ISR
	
DSEG at 0x30
Count1ms:      ds 2 ; Used to determine when half second has passed
x:             ds 4
y:             ds 4
bcd:           ds 5

BSEG

CSEG
	
;---------------------------------;
; Routine to initialize the ISR   ;
; for timer 0                     ;
;---------------------------------;
Timer0_Init:
	mov a, TMOD
	anl a, #0xf0 ; Clear the bits for timer 0
	orl a, #0x01 ; Configure timer 0 as 16-timer
	mov TMOD, a
	mov TH0, #high(TIMER0_RELOAD)
	mov TL0, #low(TIMER0_RELOAD)
	; Set autoreload value
	mov TIMER0_RELOAD_H, #high(TIMER0_RELOAD)
	mov TIMER0_RELOAD_L, #low(TIMER0_RELOAD)
	; Enable the timer and interrupts
    setb ET0  ; Enable timer 0 interrupt   
    setb TR0  ; Start timer 0
	ret

;---------------------------------;
; ISR for timer 0.  Set to execute;
; every 1/4096Hz to generate a    ;
; 2048 Hz square wave at pin P3.7 ;
;---------------------------------;
Timer0_ISR:
	;clr TF0  ; According to the data sheet this is done for us already.
	sjmp no_beep
beep_on:
	;cpl SOUND_OUT ; Connect speaker to P3.7!
no_beep:
	reti
	
	
;---------------------------------;
; Routine to initialize the ISR   ;
; for timer 1                     ; 
;---------------------------------;
Timer1_Init:
	mov a, TMOD
	anl a, #00001111B
	orl a, #00010000B
	mov TMOD, a
	
	mov TH1, DUTY_CYCLE
	mov TL1, 
	
	mov a, TCONB ;load TCONB for PWM settings
	anl 
	
	


;---------------------------------;
; Routine to initialize the ISR   ;
; for timer 2                     ;
;---------------------------------;
Timer2_Init:
	mov T2CON, #0 ; Stop timer/counter.  Autoreload mode.
	mov TH2, #high(TIMER2_RELOAD)
	mov TL2, #low(TIMER2_RELOAD)
	; Set the reload value
	mov RCAP2H, #high(TIMER2_RELOAD)
	mov RCAP2L, #low(TIMER2_RELOAD)
	; Init One millisecond interrupt counter.  It is a 16-bit variable made with two 8-bit parts
	clr a
	mov Count1ms+0, a
	mov Count1ms+1, a
	; Enable the timer and interrupts
    setb ET2  ; Enable timer 2 interrupt
    setb TR2  ; Enable timer 2
	ret

;---------------------------------;
; ISR for timer 2                 ;
;---------------------------------;
Timer2_ISR:
	clr TF2  ; Timer 2 doesn't clear TF2 automatically. Do it in ISR
	cpl P3.6 ; To check the interrupt rate with oscilloscope. It must be precisely a 1 ms pulse.
	
	; The two registers used in the ISR must be saved in the stack
	push acc
	push psw
	
	; Increment the 16-bit one mili second counter
	inc Count1ms+0    ; Increment the low 8-bits first
	mov a, Count1ms+0
	cjne a, #10h, Timer2_ISR_done
	mov Count1ms+0, #0h
	
Timer2_ISR_done:
	pop psw
	pop acc
	reti
	
MainProgram:
    mov SP, #7FH ; Set the stack pointer to the begining of idata
    
forever:
	sjmp forever
END