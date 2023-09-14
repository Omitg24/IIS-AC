.microarch
	out_of_order_retirement    = true
	forwarding                 = false
	early_branch_evaluation    = true
	register_renaming          = false
	branch_prediction          = always_not_taken
	exb_no_pipelined_cycles    = 1
	exb_instructions           = []
	exc_pipelined_cycles       = 1
	exc_instructions           = []
	ignore_div_exceptions      = false
	ignore_data_mem_exceptions = false

.data
	array: dword 6,9,12,92,100,2,3,1 ; array of numbers
	count: dword 8                   ; item count
	max:   dword 0                   ; maximum

.code
main:
	xor    r8, r8, r8     ; temporary maximum (0 is the minimum)
	xor    r9, r9, r9     ; memory index of the current item
	ld     r10, count(r0) ; remaining items
loop:
	ld     r11, array(r9)  ; current item
	daddi  r10, r10, -1    ; count--
	daddi  r9, r9, 8       ; move index to next item (64 bits)
	slt    r2, r8, r11     ; comparison  [r2 = r8 < r11 ? 1 : 0]
	movn   r8, r11, r2     ; update temporary max. [if (r2 != 0) r8 = r11]
	beqz   r10, end        ; end of the array
	j loop
end:
	sd     r8, max(r0)     ; maximum
