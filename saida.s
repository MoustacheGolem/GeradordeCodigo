.data
buffer: .word 0
fatorial: .word 0
i: .word 0
.text
addi s1,zero, 1 
la  s2, fatorial
sw  s1, 0(s2) 
addi s1,zero, 9 
la  s2, i
sw  s1, 0(s2) 
FOR: 
la  s2, i
lw  s1, 0(s2) 
addi s2,zero, 0 
slt  s1,s1, s2 
ble  s1, zero, ENDFOR 
la  s2, fatorial
lw  s1, 0(s2) 
la  s1, i
lw  s3, 0(s1) 
add  s2,zero, s3 
mul  s1,s1 ,s2 
la  s2, fatorial
sw  s1, 0(s2) 
la  s2, fatorial
lw  s1, 0(s2) 
mv a0, s1 
li a7, 1
ecall
la  s2, i
lw  s1, 0(s2) 
addi s2,zero, 1 
add  s1,s1, s2 
la  s2, i
sw  s1, 0(s2) 
beq  zero, zero, FOR 
ENDFOR: 
la  s2, fatorial
lw  s1, 0(s2) 
mv a0, s1 
li a7, 1
ecall
li a7, 10
ecall
