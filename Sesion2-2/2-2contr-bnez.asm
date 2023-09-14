	.code

main:
	daddi r8, r0, 2      ; 2 iterations
	xor   r10, r10, r10
	nop
loop:
	daddi r8, r8, -1
	daddi r21, r0, 3
	daddi r22, r0, 2
	bnez  r8, loop       ; branch if r8 != 0
	xor   r20, r20, r20
