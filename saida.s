.section .data
buffer: .word 0
i: .word 0
.section .text
addi rd,zero, 0 
la  rs1, i
sw  rd, 0(rs1) 
FOR#0: 
la  rs1, i
lw  rd, 0(rs1) 
addi rs1,zero, 8 
slt  rd,rd, rs1 
ble  rd, zero, ENDFOR#0 
la  rs1, i
lw  rd, 0(rs1) 
la  a1, rd
li a2, 4
li a0, 1 
li a7, 64
ecall
la  rs1, i
lw  rd, 0(rs1) 
addi rs1,zero, 1 
add  rd,rd, rs1 
la  rs1, i
sw  rd, 0(rs1) 
beq  zero, zero, FOR#0 
ENDFOR#0: 
li  a7, 93ecall
