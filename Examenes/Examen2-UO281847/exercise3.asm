.data
	var: dword 10
	res: dword 0

.code
main:
	daddi 	r10, r0, 9		; r10 <- 9
	daddi	r3, r0, 4		; r3 <- 4
	daddi	r4, r6, 3 		; r4 <- 3
	xor		r3, r3, r3
	ld    	r1, var(r0) 	; load var in r1
loop:
	xor		r6, r6, r6		; r6 <- 0
	ori		r2, r2, 2		; r2 <- 0
	daddi  	r1, r1, -5 		; r1 <- r1 - 5 
	beqz	r1, end			; checks if r1 is equals 0, and if so jumps to end label
	j		loop
end:
	sd 		r1, res(r0)		; store r1