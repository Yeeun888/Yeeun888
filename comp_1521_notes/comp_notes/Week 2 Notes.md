### Control Flow
- Jumps can be used to change location of execution
```
j label      #jump to a label 
jal label    #jump to label and save the address where execution jumped form in 
			 #$ra such that execution can return later
jr $register
jalr $register #both are similar but jump to registers in the program counter
```

- Branch instructions do if else statements then jumping to labels
![[Pasted image 20230923132107.png]]

### Data Structures
- MIPS operates on a memory subsystem of bytes (8 bits each). Each byte has a unique address which is accessed/stored for every operation. 

- Virtual Memory is "fake memory"
	- Programs are given virtual addresses to what seems like infinite memory allowing them to allocate memory themselves on a higher level instead of accessing bare metal. The virual addresses are then translated by the OS
	- This allows programs to share memory and for them to be loaded as necessary
	- Apparently implemented on the silicon level

- Address Sizes
	- Most computers use **64 Bit**
	- Older ones use 32, with embedded systems that use 32 and 16. 
	- **MIPSY** (the UNSW MIPS assembler) uses 32 bit addresses

- Instructions to access memory can be done
	- 1 bytes = byte. Use lb/sb
	- 2 bytes = half-world (hw). Use lh/sh.
	- 4 bytes = word. Use lw/sw.

- Code Example (labels with directives)
```
	.text

	.data
a:  .space 18 # int8_t a[18]; 
	.align 2 # align next object on 4-byte addr 
i:  .word 42 # int32_t i = 42; 
v:  .word 1,3,5 # int32_t v[3] = {1,3,5}; 
h:  .half 2,4,6 # int16_t h[3] = {2,4,6}; 
b:  .byte 7:5 # int8_t b[5] = {7,7,7,7,7}; 
f:  .float 3.14 # float f = 3.14; 
s:  .asciiz "abc" # char s[4] {'a','b','c','\0'}; 
t:  .ascii "abc" # char t[3] {'a','b','c'};
```

- Loading addresses can be done via these two lines which are the same
```
	la $t7, vec 
	li $t7, 0x10000100
```

- Example MIPS
```
    .globl main
main:
    li $t0, 0 # int i = 0;
loop:
    bge $t0 ,5, end    # if (i >= 5) goto end;
    la $t1, numbers    # int j = numbers[i]; 
	mul $t2, $t0, 4.   # calculate increment from the start address of number and store in $t2
    add $t3, $t2, $t1  # add inital addresss with increment into $t3
    lw $a0, 0($t3)     # printf("%d", j); note: 0() is basically dereference
    li $v0, 1          # syscall code
    syscall
    li $a0, '\n'       # printf("%c", '\n');
    li $v0, 11         # printf("%c", '\n');
    syscall            # printf("%c", '\n');
    addi $t0, $t0, 1   # i++
    b loop             # goto loop

end:
    li $v0, 0          # return 0
    jr $ra 

.data
numbers: # int numbers[10] = { 3, 9, 27, 81, 243};
    .word 3, 9, 27, 81, 243
```
