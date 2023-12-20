.data
buffer: .word 0
a: .word 0
.text
li a7, 5
ecall
mv s1, a0
la  s2, a
lw  s1, 0(s2) 
la  s2, a
lw  s1, 0(s2) 
mv a0, s1 
li a7, 1
ecall
li a7, 11 
li a0, '\n' 
ecall
li a7, 10 
ecall
