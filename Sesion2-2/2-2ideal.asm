	.data

var1: dword 14
var2: dword 24
var3: dword 5
var4: dword 4
res1: dword 0
res2: dword 0

	.code

main:
	ld    r10, var1(r0)  ; load var1 in r10
	ld    r20, var2(r0)  ; load var2 in r20
	ld    r11, var3(r0)  ;...
	ld    r21, var4(r0)
	nop                  ; nop = no operation
	dadd  r1, r20, r10   ; r1 <- r20 + r10       
	dadd  r2, r21, r11
	nop
	sd    r1,res1(r0)    ; store r1 in res1
	sd    r2,res2(r0)
