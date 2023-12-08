- Labels are used to keep track of address spaces. When static arrays are added, the actual memory location is calculated at compilation. Hence why it cannot be explicitly declared
```
    .text
main:
	li $t0, 3
	mul $t0, $t0, 4 #address indice
	la $t1, x #load address into t1
	add $t2, $t1, $mul

	li $t3, 17
	sw $t3, ($t2)

.data
x:  .space 4*10
```

- Arrays are one dimensional regardless. Even arrays that are two dimensional are also just flattened arrays. Things with adjacent memory locations are cached together hence they are **FASTER** which is why it is important to know
- It is possible for CPU's to require alignment. Only storing 4 byte values in memory addresses that are divisible by 4 (or 8 bytes for doubles etc). This is done in MIPS by the command below
```
.align 4
```
- Structs in MIPS (actually in week 4)
- If you get the address of the struct, the offset is infront of the dereference
![[Pasted image 20230928231022.png]]
```
sw $t0, 44($t2)
#assuming $t0 is the variable to store and $t2 is the id. 44 is the offset to then access the memory location
```

