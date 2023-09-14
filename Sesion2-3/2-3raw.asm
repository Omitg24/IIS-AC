.data
var1: word 34

.code
main:
	ori   r1, r0, 4
	daddi r2, r1, 1
	ori   r3, r1, 7
	ld    r4, var1(r1)
	daddi r6, r8, 100
	dadd  r6, r4, r4
	ori   r5, r4, 8
	beqz  r5, main