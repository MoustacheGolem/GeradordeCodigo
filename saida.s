.data
buffer: .word 0
fatorial: .word 0
i: .word 0
.text
li s1, 1 
la  s2, fatorial
sw  s1, 0(s2) 
li s1, 12 
la  s2, i
sw  s1, 0(s2) 
FOR0: 
la  s2, i
lw  s1, 0(s2) 
li s2, 0 
slt  s1,s2, s1 
ble  s1, zero, ENDFOR0 
la  s2, fatorial
lw  s1, 0(s2) 
la  s3, i
lw  s2, 0(s3) 
mul  s1,s1 ,s2 
la  s2, fatorial
sw  s1, 0(s2) 
la  s2, i
lw  s1, 0(s2) 
li s2, 1 
sub  s1,s1, s2 
la  s2, i
sw  s1, 0(s2) 
beq  zero, zero, FOR0 
ENDFOR0: 
la  s2, fatorial
lw  s1, 0(s2) 
mv a0, s1 
li a7, 1
ecall
li a7, 11 
li a0, '
'
ecall
li a7, 10
ecall
