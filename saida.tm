.data 
a: .word 0
b: .word 0
.text 
addi rd,zero, 10 
st  rd,0(1) 
beq  zero,zero, WHILE# 
WHILEB#: 
ld  rd,0(1) 
addi rs1,zero, 1 
sub  rd,rd, rs1 
st  rd,0(1) 
ld  rd,0(1) 
WHILE: 
jgt  rd,zero, WHILEB# 
