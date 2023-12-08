### MIPS Registers

- Registers are used to store information
![[Pasted image 20230922230340.png]]

- Basic Arithmetic Instruction for MIPS
```
add $t0, $t1, $t2    #t0 = t1 + t2
sub $t0, $t1, $t2    #t0 = t1 - t2
mul $t0, $t1, $t2    #t0 = t1 * t2
rem $t0, $t1, $t2    #t0 = t1 % t2 basically modulo
div $t0, $t1, $t2    #t0 = t1 / t2
addi $t0, $t1, 2    #t0 = t1 + 2   addition with a literature number
```

- Important Miscellaneous Instructions
```
li $t0, 1         #Load register with value
la $t0, msg1      #msg1 is a label. Load it with the address (in form of label)
move $t1, $t0     #$t1 = $t0
slt $t0, $t1, $t2 #Compares t1 and t2 where t0 = t1 < t2. t0 is 1 where t is                        less, else t0 is 0 where t1 is larger.
stli $t0, $t1, 3  #Same but compares with number instead of between registers
lui $t0, 1        #t0 = I * 65536 yes literally
```
### Syscalls Are Important

- Syscalls are called via the "syscall" instruciton. Instructions are loaded into $v0
![[Pasted image 20230923001954.png]]
![[Pasted image 20230923002002.png]]

