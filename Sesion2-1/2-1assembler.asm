.data
intval:   word 10h                        ; Decimal integer 16
array:    dword 6,9,-12,92,100,2,-3,1     ; Array of 64-bit integer numbers
string1:  byte 'Hello', 0                 ; A null terminated string
string2:  byte 'H', 'e', 'l', 'l', 'o', 0 ; The same string 
bytearr:  byten 4, 15h                    ; The same as byte 15h, 15h, 15h, 15h 
floatval: double 0.5                      ; IEEE-754 double value

.code
ld	  r1, array(r0)    ; r1 = array[0] = 6
dadd  r2, r1, r1       ; r2 = r1+r1 = 12
l.d   f1, floatval(r0) ; f1 = 0.5
mul.d f2, f1, f1       ; f2 = f1*f1 = 0.25
