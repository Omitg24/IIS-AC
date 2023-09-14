	.code

main:
	xor    r8, r8, r8
	daddi  r9, r0, 16	
for:
	beq    r8, r9, end
	dadd   r10, r10, r11  ; a = a + c
	
	dadd   r10, r10, r11  ; a = a + c
	
	dadd   r10, r10, r11  ; a = a + c
	
	dadd   r10, r10, r11  ; a = a + c
	daddi  r8, r8, 4
	j      for
end:	
	nop