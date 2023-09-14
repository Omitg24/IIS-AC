.code
	ori r1, r0, 2 ; r1 = 2
loop:
	beqz r1, endloop ; Branch on equal to zero
 	daddi r1, r1, -1 ; r1 = r1 - 1
	j loop
endloop:
	xor r1, r1, r1 ; r1 = 0