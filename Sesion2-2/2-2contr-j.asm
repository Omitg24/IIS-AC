.data

.code
main:
	xor   r10, r10, r10
	daddi r20, r0, 12
	daddi r21, r0, 3
	daddi r22, r0, 2
	j     dest			; jump (unconditional)
	nop
	xor   r20, r20, r20
dest:
	dsub  r20, r20, r21
	dadd  r22, r22, r21