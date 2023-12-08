# Reads a line and prints whether it is a palindrome or not

LINE_LEN = 256

########################################################################
# .TEXT <main>
main:
	# Locals:
	#   - ...

	# At this point none of the t and s registers are used 
       loop_initialize:

        la	$t0, line               #line is the address 
        li      $t1, 0                  #temporary counter 

        loop_body:
        addi	$t1, $t1, 1

        loop_condition:
        lb	$t2, ($t0)
        beq     $t2, '\n', loop_end
	addu	$t0, $t0, 1
	j 	loop_body

        loop_end:

	#The counter of i and j 
	move 	$t0, $t1		#length of string stored in t0
	sub	$t0, $t0, 2
	li 	$t1, 0

	my_start:

	my_condition:
	ble	$t0, $t1, my_end

	my_body:

	# la      $t4, line
        # addu	$t4, $t4, $t0           # shift for answer 
        # lb	$t5, ($t4)

	# li	$v0, 11			# syscall 11: print_char
	# move	$a0, $t5		#
	# syscall				# putchar('?');

	la	$t2, line
	addu	$t2, $t2, $t0
	lb 	$t3, ($t2) 

	la	$t2, line
	addu	$t2, $t2, $t1
	lb 	$t4, ($t2) 

	bne	$t3, $t4, not_palindrome

	addi	$t1, $t1, 1
	sub 	$t0, $t0, 1

	j 	my_condition;
	my_end:
	j 	is_palindrome

	not_palindrome:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_not_palindrome_str	#
	syscall					# printf("not palindrome\n");
	j 	end

	is_palindrome:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_palindrome_str	#
	syscall					# printf("palindrome\n");

	end:

	li	$v0, 0
	jr	$ra				# return 0;


########################################################################
# .DATA
	.data
# String literals
line_prompt_str:
	.asciiz	"Enter a line of input: "
result_not_palindrome_str:
	.asciiz	"not palindrome\n"
result_palindrome_str:
	.asciiz	"palindrome\n"

# Line of input stored here
line:
	.asciiz "01233210\n"

