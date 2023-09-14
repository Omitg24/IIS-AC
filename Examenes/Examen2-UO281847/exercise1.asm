.data
	exp:	dword 2		; exponent 
	op:		dword 6		; operand
	res:	dword 0		; res = operand^exponent
	tmp:	dword 1		; tmp = 1 
.code
main:
	ld		r3, tmp(r0)	; temporary pow (1 is the default value)
	ld		r4, exp(r0)	; remaining items
	ld		r5, op(r0)	; operand
loop:
	daddi 	r4, r4, -1	; exp --
	dmul	r6, r3, r5	; r6 = r5 * r5
	dadd	r3, r6,	r9	; Update r3 value
	ddiv	r5, r2, r7	; r5 = r2 / r7
	beqz 	r4, end		; end of the multiplication
	j loop
end:
	sd		r3, res(r0)	; result of the operation 