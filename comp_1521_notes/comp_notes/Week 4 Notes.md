- Storing pointers
```
	.text
main:
	la $t0, answer #load ADDRESS of answer into to
	lw $t1, ($t0) #load word into t1 (i.e. dereference)

	.data
answer: 
	.word 42
```

- Structs are covered, check week 3 notes
- Bases in math
	- Each digit of the base represents a power of the base
	 ![[Pasted image 20231019223756.png]]
- Base 16 is useful in computing
	- They go from 0-9, A-F (total 10 + 6) for 16 "digits"
	![[Pasted image 20231019224110.png]]
		Writing this out, numbers are more efficiently represented in base 16. Example is where 15089 = 0x3AF1 (0x denotes base 16)
		- Hexadecimal is useful as it is a power of 2. Therefore it can be converted to binary very quickly. Map each digit of a hexadecimal to binary. 
		- Ex: Ox48F = 0100 1000 1111 
	- Likewise, there is also Octal which is base 8. It is represented in programming if the number starts with 0 (ex: 052) in C. It can create **BUGS** 
- Behavior or numbers in C. Negative numbers are calculated with the formula <u>2^n - b</u> where n is the base and b is the negative number. Therefore when representing numbers of 8 bits. 
	- -128 is represented as
	- 2^8 - 128 = 128 = 1000 0000
	- Continuing this pattern
	- -127 = 1100 0000
	- -126 = 1110 0000
- STEPS FOR 2s complement, use normal binary then flip all bits, add 1. 
- This behaviour also explains why numbers loop back to negative when they are added out of bounds. 

- Chart of guaranteed sizes in C
![[Pasted image 20231019234706.png]]

- Small bug notes. Some systems define char as 0..255 instead of -128..127 (which most systems use). Therefore code that relies on -1 does not work properly (such as EOF statements). 

- Big vs small endian
	- Big endian: Most significant digit in the front (ie normal binary with largest numbers in the front)
	- Little endian: Most significant digit in the back (reverse binary)

## Back to C - Notes
- Bitwise operators in C. The bits are manipulated on the individual bits
```
x & y  // bitwise and
x | y  // bitwise or
x ^ y  // bitwise xor
~ x    // bitwise not
x << n // shift n bits left
x >> n // shift n bits right
```

- Bitwise Operators
	1. AND
		Returns 1 when both bits are 1. Otherwise returns 0. 
	2. OR
		Returns 1 when EITHER of the bits are 1. Otherwise, returns 0. 
	3. NOT
		Inverts the bit operated on
	4. XOR (very interesting) (^ symbol)
		![[Pasted image 20231020193151.png]]
	5. Shift operators
		Just shifts the bits. Any bits on the edge when shifted are lost. 
		Left shifts are equivalent to times two
		Right shifts 
			 Are equivalent to divide by two,
			 and is IMPLEMENTATION DEFINED FOR NON-NEGATIVE NUMBERS. Therefore use unsigned numbers otherwise it can add either positive or negative numbers
			 