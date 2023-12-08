- Types of floating point
	- float = 32 bit
	- double = 64 bit
	- long double = 128 bits

- Printing floats 
```
printf("%le\n") //scientific notation
printf("%.9lf\n", d) // print to 9 decimal places
printf("%10.1lf\n",d) // 10 = field width (maximum amount of numbers, 1 = decimal places)
```

- Fixed point representation for floats. I.E multiplying by constants 
![[Pasted image 20231102172521.png]]

- IEEE 754 basic arithmetic. Note that all is done in binary 
![[Pasted image 20231102180602.png]]

It also has the following format
![[Pasted image 20231102182328.png]]

- Special Numbers in IEEE 754
	- Inf = exponent (all 1), mantissa (all 0)
	- NaN = exponent (all 1), mantissa (not 0). Fun fact there is an isnan(x) function.

- Comparison of floats should be done as a comparison of errors instead of direct comparisons
	ex:

```
	float a;
	float b;

	#instead of 
	if(a == b)

	#do
	if(abs(a - b) > 0.00001) 

	#As floating point comparisons will always have a tiny error

```

## Operating System
- The operating systems provide programs with a non-privileged mode such that the program does not crash the rest of the program
- 