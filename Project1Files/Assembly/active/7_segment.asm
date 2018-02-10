
; Pattern to load passed in accumulator
load_segments:
	mov c, acc.0
	mov SEGA, c
	mov c, acc.1
	mov SEGB, c
	mov c, acc.2
	mov SEGC, c
	mov c, acc.3
	mov SEGD, c
	mov c, acc.4
	mov SEGE, c
	mov c, acc.5
	mov SEGF, c
	mov c, acc.6
	mov SEGG, c
	mov c, acc.7
	mov SEGP, c
	ret
	
seg_state_machine:
	; Turn all displays off
	setb CA1
	setb CA2
	setb CA3

	mov a, seg_state ; Load current state value
			
	seg_state0: ;Display LED 1
		cjne a, #0, seg_state1
		mov a, disp1
		lcall load_segments
		clr CA1
		inc seg_state
		sjmp seg_state_done
	seg_state1: ;Display LED 2
		cjne a, #1, seg_state2
		mov a, disp2
		lcall load_segments
		clr CA2
		inc seg_state
		sjmp seg_state_done
	seg_state2: ;Display LED 3
		cjne a, #2, seg_state_reset
		mov a, disp3
		lcall load_segments
		clr CA3
		mov seg_state, #0
		sjmp seg_state_done
	seg_state_reset: ;Back to LED 1
		mov seg_state, #0
	seg_state_done:
	ret

seg_state_init:
	mov a, #0
	mov seg_state, a  ;set 7_seg 7_seg_state to 0
	mov a, #00010001b
	mov BCD_temp+0, a
	mov a, #00000001b
	mov BCD_temp+1, a
	
	lcall set_7_segment_diplay
	ret

set_7_segment_diplay:
	mov dptr, #HEX_7SEG
	
	mov a, BCD_temp      ;
	anl a, #0x0f         ;Clear upper 4 bits
	movc a, @a+dptr      ;Access HEX_7SEG[a]
	mov disp1, a         ;Move Lowest BCD to display 1
	
	mov a, BCD_temp      ;
	swap a               ;Swaps the high and low nibbles
	anl a, #0x0f         ;Clear upper 4 bits (which are now the lower 4)
	movc a, @a+dptr      ;Access HEX_7SEG[a]
	mov disp2, a         ;Move Second Lowest BCD to display 2
	
	mov a, BCD_temp+1    ;Get the upper 2 BCD digits of value being diplayed
	anl a, #0x0f         ;Clear upper 4 bits
	movc a, @a+dptr      ;Access HEX_7SEG[a]
	mov disp3, a         ;Moves highest bcd digit to diplay 3
	ret


END