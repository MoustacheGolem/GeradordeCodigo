.data
a: .word 0
b: .word 0
.text
addi rd,zero, 1 
st  rd,0(1) 
ld  rd,0(1) 
bgt rd,zero, ELSE#0 
ld  rd,0(1) 
addi rs1,zero, 1 
add  rd,rd, rs1 
st  rd,0(1) 
ld  rd,0(1) 
la  a1, rd
li a2, 4
li a0, 1 
li a7, 64
ecall
beq  zero,zero, ENDIF#0 
ELSE#0: 
addi rd,zero, 0 
la  a1, rd
li a2, 4
li a0, 1 
li a7, 64
ecall
ENDIF#0: 
