########################################################################
# COMP1521 23T3 -- Assignment 1 -- Tetris!
#
#
# !!! IMPORTANT !!!
# Before starting work on the assignment, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
# Instructions to configure your text editor can be found here:
#   https://cgi.cse.unsw.edu.au/~cs1521/23T3/resources/mips-editors.html
# !!! IMPORTANT !!!
#
#
# This program was written by YOUR-NAME-HERE (z5555555)
# on INSERT-DATE-HERE
#
# Version 1.0 (2023-09-25): Team COMP1521 <cs1521@cse.unsw.edu.au>
#
########################################################################

#![tabsize(8)]

# ##########################################################
# ####################### Constants ########################
# ##########################################################

# C constants
FIELD_WIDTH  = 9
FIELD_HEIGHT = 15
PIECE_SIZE   = 4
NUM_SHAPES   = 7

FALSE = 0
TRUE  = 1

EMPTY = ' '

# NULL is defined in <stdlib.h>
NULL  = 0

# Other useful constants
SIZEOF_INT = 4

COORDINATE_X_OFFSET = 0
COORDINATE_Y_OFFSET = 4
SIZEOF_COORDINATE = 8

SHAPE_SYMBOL_OFFSET = 0
SHAPE_COORDINATES_OFFSET = 4
SIZEOF_SHAPE = SHAPE_COORDINATES_OFFSET + SIZEOF_COORDINATE * PIECE_SIZE


	.data
# ##########################################################
# #################### Global variables ####################
# ##########################################################

# !!! DO NOT ADD, REMOVE, OR MODIFY ANY OF THESE DEFINITIONS !!!

shapes:				# struct shape shapes[NUM_SHAPES] = ...
	.byte 'I'
	.word -1,  0,  0,  0,  1,  0,  2,  0
	.byte 'J'
	.word -1, -1, -1,  0,  0,  0,  1,  0
	.byte 'L'
	.word -1,  0,  0,  0,  1,  0,  1, -1
	.byte 'O'
	.word  0,  0,  0,  1,  1,  1,  1,  0
	.byte 'S'
	.word  0,  0, -1,  0,  0, -1,  1, -1
	.byte 'T'
	.word  0,  0,  0, -1, -1,  0,  1,  0
	.byte 'Z'
	.word  0,  0,  1,  0,  0, -1, -1, -1

# Note that semantically global variables without
# an explicit initial value should be be zero-initialised.
# However to make testing earlier functions in this
# assignment easier, some global variables have been
# initialised with other values. Correct translations
# will always write to those variables befor reading,
# meaning the difference shouldn't matter to a finished
# translation.

next_shape_index:		# int next_shape_index = 0;
	.word 0

shape_coordinates:		# struct coordinate shape_coordinates[PIECE_SIZE];
	.word -1,  0,  0,  0,  1,  0,  2,  0

piece_symbol:			# char piece_symbol;
	.byte	'I'

piece_x:			# int piece_x;
	.word	3

piece_y:			# int piece_y;
	.word	1

piece_rotation:			# int piece_rotation;
	.word	0

score:				# int score = 0;
	.word	0

game_running:			# int game_running = TRUE;
	.word	1

field:				# char field[FIELD_HEIGHT][FIELD_WIDTH];
	.byte	0:FIELD_HEIGHT * FIELD_WIDTH


# ##########################################################
# ######################### Strings ########################
# ##########################################################

# !!! DO NOT ADD, REMOVE, OR MODIFY ANY OF THESE STRINGS !!!

str__print_field__header:
	.asciiz	"\n/= Field =\\    SCORE: "
str__print_field__next:
	.asciiz	"     NEXT: "
str__print_field__footer:
	.asciiz	"\\=========/\n"

str__new_piece__game_over:
	.asciiz	"Game over :[\n"
str__new_piece__appeared:
	.asciiz	"A new piece has appeared: "

str__compute_points_for_line__tetris:
	.asciiz	"\n*** TETRIS! ***\n\n"

str__choose_next_shape__prompt:
	.asciiz	"Enter new next shape: "
str__choose_next_shape__not_found:
	.asciiz	"No shape found for "

str__main__welcome:
	.asciiz	"Welcome to 1521 tetris!\n"

str__show_debug_info__next_shape_index:
	.asciiz	"next_shape_index = "
str__show_debug_info__piece_symbol:
	.asciiz	"piece_symbol     = "
str__show_debug_info__piece_x:
	.asciiz	"piece_x          = "
str__show_debug_info__piece_y:
	.asciiz	"piece_y          = "
str__show_debug_info__game_running:
	.asciiz	"game_running     = "
str__show_debug_info__piece_rotation:
	.asciiz	"piece_rotation   = "
str__show_debug_info__coordinates_1:
	.asciiz	"coordinates["
str__show_debug_info__coordinates_2:
	.asciiz	"]   = { "
str__show_debug_info__coordinates_3:
	.asciiz	", "
str__show_debug_info__coordinates_4:
	.asciiz	" }\n"
str__show_debug_info__field:
	.asciiz	"\nField:\n"
str__show_debug_info__field_indent:
	.asciiz	":  "

str__game_loop__prompt:
	.asciiz	"  > "
str__game_loop__quitting:
	.asciiz	"Quitting...\n"
str__game_loop__unknown_command:
	.asciiz	"Unknown command!\n"
str__game_loop__goodbye:
	.asciiz	"\nGoodbye!\n"

# !!! Reminder to not not add to or modify any of the above !!!
# !!! strings or any other part of the data segment.        !!!



############################################################
####                                                    ####
####   Your journey begins here, intrepid adventurer!   ####
####                                                    ####
############################################################

################################################################################
#
# Implement the following functions,
# and check these boxes as you finish implementing each function.
#
#  SUBSET 0
#  - [x] main
#  - [x] rotate_left
#  - [x] move_piece
#  SUBSET 1
#  - [x] compute_points_for_line
#  - [x] setup_field
#  - [x] choose_next_shape
#  SUBSET 2
#  - [x] print_field
#  - [x] piece_hit_test
#  - [x] piece_intersects_field
#  - [x] rotate_right
#  SUBSET 3
#  - [ ] place_piece
#  - [ ] new_piece
#  - [ ] consume_lines
#  PROVIDED
#  - [X] show_debug_info
#  - [X] game_loop
#  - [X] read_char

################################################################################
# .TEXT <main>
        .text
main:
        # Subset:   0
        #
        # Args:     None
        #
        # Returns:  $v0: int
        #
        # Uses:     Used as entry point for full function
        # Clobbers: $ra
	# Leaf function: No
        #
        # Locals:
        #   - None
        #
        # Structure:
        #   main
        #   -> [prologue] to initialize message
        #       -> body to call three different functions
        #   -> [epilogue] ending sequence

main__prologue:
	li 	$v0, 4
	la 	$a0, str__main__welcome #Adds string
	syscall

main__body:

	push 	$ra			#push ra into stack
	jal 	setup_field		#call function which clobbers $ra
	pop	$ra			#pop ra back into stack later 

	li	$a0, FALSE	
	push	$ra
	jal 	new_piece
	pop 	$ra
	push	$ra
	jal 	game_loop
	pop 	$ra

main__epilogue:
	li	$v0, 0
        jr      $ra


################################################################################
# .TEXT <rotate_left>
        .text
rotate_left:
        # Subset:   0
        #
        # Args:     None
        #
        # Returns:  None
	# Uses:     Rotate left just calls rotate_right three times
	# Clobbers: $ra
	# Leaf function: No

	push 	$ra
	jal 	rotate_right
	pop	$ra

	push 	$ra
	jal 	rotate_right
	pop	$ra

	push 	$ra
	jal 	rotate_right
	pop	$ra

rotate_left__epilogue:
        jr      $ra



################################################################################
# .TEXT <move_piece>
        .text
move_piece:
        # Subset:   0
        #
        # Args:
        #    - $a0: int dx
        #    - $a1: int dy
        #
        # Returns:  $v0: int
        #
        # Uses:     Check if piece is colliding. Then moves piece if not
        # Clobbers: $s1, $s2, $s3, $s4, $ra
	# Leaf function: No
        #
        # Locals:
        #   - s1, s2 used as temporary piece_x and piece_y values
	#   - note: s1 and s2 ARE SEPARATE from piece_x and piece_y
	#   - s3, s3 used as a0 and a1. 
        #
        # Structure:
        #   move_piece
	#   -> [intialization] fills in s registers and 
	#      changes piece_x and piece_y based on a0 and a1. Adds clobbered
	#      items into the stack
        #   -> [prologue] calls piece_intersect_field function and branches 
	#      based on the result 
        #       -> [false] does nothing
        #       -> [true] piece DO INTERSECT therefore, change back to previous
	#   		  number (subtract from original calling values stored)
	#		  in s registers
        #   -> [epilogue] returns back to function, pops out all items in the 
	#       stack

move_piece__initialization:
	begin 
	push 	$s1
	push 	$s2
	push 	$s3
	push 	$s4

	la	$t0, piece_x
	lw	$s1, 0($t0)	
	add	$s1, $s1, $a0 		#add a0 to x
	sw	$s1, 0($t0)

	la	$t0, piece_y 
	lw	$s2, 0($t0)
	add	$s2, $s2, $a1 		#add a1 to y
	sw	$s2, 0($t0)

	add	$s3, $0, $a0 		#save a0 in s3
	add 	$s4, $0, $a1 		#save a1 in s4

move_piece__prologue:

	push 	$ra
	jal 	piece_intersects_field
	pop 	$ra

	beq 	$v0, 1, piece_intersect__true
piece_intersect__false:
	li	$v0, TRUE
	j move_piece__epilogue

piece_intersect__true:
	sub 	$s1, $s1, $s3
	sub 	$s2, $s2, $s4
	la 	$t0, piece_x
	sw 	$s1, ($t0)
	la	$t0, piece_y
	sw 	$s2, ($t0)

	li	$v0, FALSE
	j 	move_piece__epilogue	

move_piece__epilogue:
	pop 	$s4
	pop	$s3
	pop	$s2
	pop	$s1
	end

        jr      $ra

################################################################################
# .TEXT <compute_points_for_line>
        .text
compute_points_for_line:
        # Subset:   1
        #
        # Args:
        #    - $a0: int bonus
        #
        # Returns:  $v0: int
        #
        # Uses:     Computes the amount of points rewarded to player
        # Clobbers: $ra
	# Leaf function: Yes
        #
        # Structure:
        #   compute_points_for_line - function starts and initializes, has 
	#			      branch condition to check for print tetris
        #   -> [print_tetris] 	    - prints tetris message
        #   -> [compute_points]     -
	#	-> [compute_points_for_line__prologue] - does math for the points
	#   -> [compute_points_for_line__epilogue] - end of function

					#check if TETRIS has to be printed
	beq 	$a0, 4, print_tetris
	j compute_points_for_line__prologue
print_tetris:
	move	$t3, $a0		#save original a0 as a0 will be LA(ed)

	li 	$v0, 4 			#printing start message
	la	$a0, str__compute_points_for_line__tetris
	syscall

	move 	$a0, $t3 		#a0 back to original value

compute_points_for_line__prologue:
	li 	$t0, 100
	move	$t1, $a0 		#t1 = a0
	addi	$t1, $t1, -1
	li 	$t2, 40
	mul	$t2, $t2, $t1
	mul	$t2, $t2, $t1
	add	$t0, $t2, $t0

	move	$v0, $t0
compute_points_for_line__epilogue:
        jr      $ra

################################################################################
# .TEXT <setup_field>
        .text
setup_field:
        # Subset:   1
        #
        # Args:     None
        #
        # Returns:  None
        #
        # Uses:     Sets up the field for usage
        # Clobbers: $ra
	# Leaf function: Yes
        #
        # Locals:
        #   t0: loop iterator (i) for field height
        #   t1: loop iterator (j) for field width
	#
        # Structure:
        #   setup_field
        #   -> [prologue] - set up iterators i and j
        #       -> [body] - empty function
	#	-> [rows_loop] - branch to end when i reaches field height
	#	-> [column_loop] - go through columsn and change to zero
        #   -> [epilogue] - back to $ra

setup_field__prologue:
	li	$t0, 0 #i = 0
	li	$t1, 0 #j = 0

setup_field__body:

setup_rows_loop:
	bge 	$t0, FIELD_HEIGHT, setup_field__epilogue
setup_column_loop:
	bge 	$t1, FIELD_WIDTH, setup_column_loop_end
	
	#Calculate increment
	mul	$t2, $t0, 9 		#32 bytes per row 
	mul	$t3, $t1, 1		#4 bytes per word
	add	$t2, $t2, $t3		#(32 x row) + (4 words) = t2, t3 free

	la 	$t3, field
	addu 	$t3, $t3, $t2
	li	$t4, EMPTY
	sb 	$t4, ($t3)

	addi 	$t1, $t1, 1
	j 	setup_rows_loop
	
setup_column_loop_end:
        li	$t1, 0
	addi	$t0, $t0, 1
	j 	setup_rows_loop

setup_field__epilogue:
        jr      $ra



################################################################################
# .TEXT <choose_next_shape>
        .text
choose_next_shape:
        # Subset:   1
        #
        # Args:     None
        #
        # Returns:  None
        #
        # Uses:     Changes the shape to next shape 
        # Clobbers: $ra, $a0, $s0, $t1-7
	# Leaf Function: No
        #
        # Structure:
        #   choose_next_shape
        #   -> [prologue] - setup iterator and print important strings
	#		    also pushes variables to be clobbered
        #       -> body
        #       -> [shape_loop] - goes through shapes array to find shape
        #       -> [no_shape_found] - actions when shape is not found
        #       -> [shape_found] - shape found code
        #   -> [epilogue]

choose_next_shape__prologue:

	begin
	push 	$s0

	li 	$v0, 4
	la 	$a0, str__choose_next_shape__prompt
	syscall

	li 	$s0, 0			#s0 is iterator = 0

	push	$ra
	jal	read_char
	pop	$ra

	move	$t7, $v0

choose_next_shape__body:

choose_next_shape_loop:			#While loop
	bge 	$s0, 7, no_shape_found
	mul	$t1, $s0, 36		#i * address offset
	la 	$t2, shapes		#36 is the size of the struct (32 + 4)
	addu 	$t2, $t2, $t1		#add them together
	lb	$t2, ($t2)
	beq  	$t2, $v0, shape_found
	addi	$s0, $s0, 1		#i++ increment
	j 	choose_next_shape_loop

no_shape_found:				#Code if there is no shape
	li	$v0, 4
	la 	$a0, str__choose_next_shape__not_found 
	syscall

	li 	$v0, 11
	move 	$a0, $t7
	syscall
	li 	$v0, 11
	li 	$a0, '\n'
	syscall

	j choose_next_shape__epilogue

shape_found:				#Code for shape found
	la 	$t3, next_shape_index
	sw	$s0, ($t3)

choose_next_shape__epilogue:

	pop	$s0			#final pop to "unclobber"
	end 

        jr      $ra



################################################################################
# .TEXT <print_field>
        .text
print_field:
        # Subset:   2
        #
        # Args:     None
        #
        # Returns:  None
        #
        # Uses:     Prints the entire playing field after each "move"
        # Clobbers: $s0, $s1, $s2, $ra, $t1-7
	# Leaf Function: No
        #
        # Structure:
        #   print_field
        #   -> [prologue] push variables where required 
        #   -> [out_loop]
	#       -> [out_loop_initialize] Initialize iterator for row loop
	#       -> [out_for_loop] Trivial outer loop tasks such as
	#			  printing
	#           -> [in_for_loop_epilogue] Initialize column loop 
	#           -> [in_for_loop] Bulk of work is done here
	#			     to test for piece hitting. Calls 
	#			     piece_hit_test function
	#               -> [piece_hit_test_true] Code if piece_hit_test is true
	#               -> [piece_hit_test_false] Same but if false
	#           -> [in_for_loop_condition] Condition to keep column loop
	#				       running
	#           -> [in_for_loop_end] End
	#       -> [if_row_is_one] Checks if row is one to print next piece
	#       -> [newline]       Newline function. 
        #   -> [out_for_loop_condition] row loop running condition
        #   -> [epilogue] Pops required variables

print_field__prologue:
	#Print starting words
	begin
	push	$s0
	push	$s1
	push 	$ra

	li	$v0, 4
	la 	$a0, str__print_field__header	
	syscall

	li 	$v0, 1
	lw 	$a0, score
	syscall

	li 	$v0, 11
	li 	$a0, '\n'
	syscall	

print_field__body:
	#Where the real work is being done

print_field_out_loop_initialize:
	li 	$s0, 0 			#s0 row = 0

print_field_out_for_loop:
	li	$v0, 11			#putchar('|');
	li 	$a0, '|'
	syscall

print_field_in_for_loop_epilogue:
	li	$s1, 0			#s1 col = 0

print_field_in_for_loop:
	#load parameters for piece hit test
	la	$a0, shape_coordinates	#a0 = shape coordinates
	move	$a1, $s0		#a1 = rows
	move	$a2, $s1		#a2 = columns

	jal	piece_hit_test		#call piece_hit_test

	beq	$v0, 0, print_field_piece_hit_test_false #branch is false
	j	print_field_piece_hit_test_true	#branch if true

print_field_piece_hit_test_true:
	lb 	$a0, piece_symbol
	li	$v0, 11
	syscall
	j	print_field_in_for_loop_condition

print_field_piece_hit_test_false:
	#row and column arithmetic
	mul	$t2, 9, $s0		#t2 = 9 * row
	add	$t2, $t2, $s1		#t2 = t2 + col
	la	$t3, field
	addu	$t2, $t3, $t2		#t2 = *field + t2 (the increment)
	lb	$a0, ($t2)	

	li	$v0, 11
	syscall
	j	print_field_in_for_loop_condition


print_field_in_for_loop_condition:
	li	$t7, 8
	bge	$s1, $t7, print_field_in_for_loop_end
	addi	$s1, $s1, 1		#col++

	j 	print_field_in_for_loop

print_field_in_for_loop_end:

	li	$v0, 11
	li	$a0, '|'
	syscall

	beq 	$s0, 1, print_field_if_row_is_one
	j 	print_field_newline

print_field_if_row_is_one:
	li	$a0, str__print_field__next
	li	$v0, 4
	syscall

	lw 	$t4, next_shape_index
	# la	$t4, next_shape_index	
	mul	$t4, 36, $t4		#t4 = t4 * 33
	# lw	$t4, ($t4)		#t4 = next_shape_index

	la	$t5, shapes
	addu	$t5, shapes, $t4	#t5 = shapes + increment

	lb	$a0, ($t5)
	li	$v0, 11
	syscall
	j 	print_field_newline

print_field_newline:
	li 	$v0, 11
	li	$a0, '\n'
	syscall

print_field_out_for_loop_condition:
	# add	$t7, FIELD_HEIGHT, $0
	# addi	$t7, $t7, -1
	addi	$s0, $s0, 1		#row++
	bge	$s0, FIELD_HEIGHT, print_field__epilogue #
	j 	print_field_out_for_loop

print_field__epilogue:
	li	$v0, 4
	la 	$a0, str__print_field__footer
	syscall

	pop	$ra
	pop	$s1
	pop	$s0
	end

        jr      $ra



################################################################################
# .TEXT <piece_hit_test>
        .text
piece_hit_test:
        # Subset:   2
        #
        # Args:
        #    - $a0: struct coordinate coordinates[PIECE_SIZE]
        #    - $a1: int row
        #    - $a2: int col
        #
        # Returns:  $v0: struct coordinate *
        #
        # Uses:     Checks if the piece hits other pieces or walls
        # Clobbers: $a0, $t0, $t1, $t2, $t3, $t4, $v0
	# Leaf Function: Yes
        #
        # Structure:
        #   piece_hit_test
        #   -> [prologue]
        #       -> body
        #   -> [epilogue]

	#Is a leaf function and therefore utilizes all $t registers
piece_hit_test__prologue:

piece_hit_test_for_loop_initialize:
	li	$t0, 0			#t0 = i = 0

piece_hit_test_for_loop:
	lw	$t1, ($a0)		#t1 = x
	lw	$t2, 4($a0)		#t2 = y
	
	lw	$t3, piece_x		#t1 + piece_x
	add	$t1, $t1, $t3

	lw	$t4, piece_y		#t2 + piece_y
	add	$t2, $t2, $t4

	bne 	$t1, $a2, piece_hit_test_for_loop_condition
	bne 	$t2, $a1, piece_hit_test_for_loop_condition

	#Bottom part executes where both conditions are met
	j 	piece_hit_test_return_coordinates

piece_hit_test_for_loop_condition:
	addi	$t0, $t0, 1
	addi	$a0, $a0, 8		#increment a0 to move to next coordinate
	bge	$t0, PIECE_SIZE, piece_hit_test__epilogue
	j piece_hit_test_for_loop

piece_hit_test_return_coordinates:
	move	$v0, $a0
	jr	$ra

piece_hit_test__epilogue:
	move	$v0, $0
        jr      $ra

################################################################################
# .TEXT <piece_intersects_field>
        .text
piece_intersects_field:
        # Subset:   2
        #
        # Args:     None
        #
        # Returns:  $v0: int
        #
        # Uses:     Check if piece is intersecting with field and returns 
	#	    TRUE or FALSE 
        # Clobbers: $v0, $t0-4, $t7
	# Leaf Function: Yes
        #
        # Structure:
        #   piece_intersects_field
        #   -> [piece_intersects_for_loop_initialize] Initializes loop counter
        #   -> [piece_intersects_field_for_loop] For loop for conditions
        #   -> [piece_intersects_for_loop_condition] Check for i > PIECE_SIZE
        #   -> [piece_intersect_field_return_true] Jump point to return TRUE
	#					   and jr $ra
        #   -> [piece_intersects_field__epilogue] Jump point to return FALSE
	#					  and jr $ra

piece_intersects_for_loop_initialize:
	li	$t0, 0			#t0 = i = 0
	la	$t7, shape_coordinates

piece_intersects_field_for_loop:
	lw	$t1, ($t7)		#t1 = x
	lw	$t2, 4($t7)		#t2 = y
	
	lw	$t3, piece_x		#t1 + piece_x
	add	$t1, $t1, $t3

	lw	$t4, piece_y		#t2 + piece_y
	add	$t2, $t2, $t4

	#Begin tests
	#Check for conditions on X
	ble 	$t3, 0, piece_intersect_field_return_true
	bgt	$t3, FIELD_WIDTH, piece_intersect_field_return_true

	#Check for conditions on Y
	ble 	$t4, 0, piece_intersect_field_return_true
	bgt	$t4, FIELD_WIDTH, piece_intersect_field_return_true

	#Check for conditions on field being empty
	la	$t3, field		#t3 = address
	mul	$t4, $t2, FIELD_WIDTH 
	add	$t4, $t4, $t1		#t4 = increment 
	addu	$t3, $t3, $t4		#t3 = address + increment
	lb	$t3, ($t3)		#load byte of t3

	bne	$t3, EMPTY, piece_intersect_field_return_true

piece_intersects_for_loop_condition:
	addi	$t0, $t0, 1
	addi	$t7, $t7, 8		#increment a0 to move to next coordinate
	bge	$t0, PIECE_SIZE, piece_intersects_field__epilogue
	j 	piece_intersects_field_for_loop

piece_intersect_field_return_true:
	li	$v0, TRUE
	jr	$ra

piece_intersects_field__epilogue:
	li	$v0, FALSE
        jr      $ra



################################################################################
# .TEXT <rotate_right>
        .text
rotate_right:
        # Subset:   2
        #
        # Args:     None
        #
        # Returns:  None
        #
        # Uses:     Rotates a block with some arithmetic
        # Clobbers: $t0-3
	# Leaf Function: Yes
        #
        # Structure:
        #   -> [rotate_right__body] Loop to rotate right
        #       -> [rotate_right_for_loop_initialize] Initializes loop
        #       -> [rotate_right_for_loop] Performs arithmetic on all pieces
        #       -> [rotate_right_for_loop_condition] Checks i > PIECE_SIZE bound
        #       -> [rotate_right_for_loop_end] End of loop to jump
        #   -> [rotate_right_if_statement] Checks if piece is I or O piece
        #       -> [rris_loop_initialize] Initiliazes loop
        #       -> [rris_loop] Loop to perform right shift
        #       -> [rris_loop_condition] Check to see i > PIECE_SIZE
        #   -> [epilogue] jr $ra

rotate_right__prologue:

rotate_right__body:
	#Thank you Andrew Taylor
	lw	$t0, piece_rotation
	addi	$t0, $t0, 1
	sw	$t0, piece_rotation

rotate_right_for_loop_initialize:
	li	$t0, 0
	la	$t1, shape_coordinates

rotate_right_for_loop:
	lw	$t2, ($t1)		#t2 = shape_coordinates.x
	lw	$t3, 4($t1)		#t3 = shape_coordinates.y
	mul	$t3, $t3, -1

	sw	$t2, 4($t1)
	sw	$t3, ($t1)

rotate_right_for_loop_condition:
	addi	$t0, $t0, 1		#t0 += 1
	addi	$t1, $t1, 8		#t1 += 8
	bge 	$t0, PIECE_SIZE, rotate_right_for_loop_end
	j 	rotate_right_for_loop

rotate_right_for_loop_end:

	#t0 - t3 are not used anymore. Therefore free for the next calculations
	lb	$t0, piece_symbol
	li	$t1, 'I'
	beq	$t0, $t1, rotate_right_if_statement
	li	$t1, 'O'
	beq	$t0, $t1, rotate_right_if_statement
	#else jump to end
	j 	rotate_right__epilogue

rotate_right_if_statement:		#shortened to rris

rris_loop_initialize:
	li	$t0, 0
	la	$t1, shape_coordinates
	
rris_loop:
	lw	$t2, shape_coordinates
	addi	$t2, $t2, 1
	sw	$t2, ($t1)

rris_loop_condition:
	addi	$t0, $t0, 1
	addi	$t1, $t1, 8
	bge	$t0, PIECE_SIZE, rotate_right__epilogue

rotate_right__epilogue:
        jr      $ra

################################################################################
# .TEXT <place_piece>
        .text
place_piece:
        # Subset:   3
        #
        # Args:     None
        #
        # Returns:  None
        #
        # Frame:    [...]
        # Uses:     [...]
        # Clobbers: [...]
        #
        # Locals:
        #   - ...
        #
        # Structure:
        #   place_piece
        #   -> [prologue]
        #       -> body
        #   -> [epilogue]

place_piece__body:

place_piece_loop_initialize:
	li 	$t0, 0			#t0 = iterator
	la 	$t1, shape_coordinates

place_piece_loop:
	lw	$t2, ($t1)		#col = t2 
	lw 	$t3, 4($t1)		#row = t3

	lw	$t4, piece_x
	add	$t2, $t2, $t4		#t2 = t2 + piece_x
		
	lw	$t4, piece_y
	add	$t3, $t3, $t4		#t3 = t3 + piece_y

	#Do arithmetic for field[row][col]
	la 	$t4, field		
	mul	$t5, $t3, FIELD_WIDTH	#t5 = field + (width * rows) + col
	add	$t5, $t5, $t2		#t5 is total increment
	addu 	$t4, $t4, $t5		#t4 = field + total increment	
	
	lb	$t6, piece_symbol
	sb	$t6, ($t4)

place_piece_loop_condition:
	addi	$t0, $t0, 1
	addi	$t1, $t1, 8
	bge 	$t0, PIECE_SIZE, place_piece_loop_end
	j	place_piece_loop

place_piece_loop_end:

	begin				#Start of stack behavior and calling a 
					#bunch of functions 
	push 	$ra
	jal 	consume_lines
	pop	$ra

	li 	$a0, TRUE
	push 	$ra
	jal 	new_piece
	pop	$ra

	end

place_piece__epilogue:
        jr      $ra



################################################################################
# .TEXT <new_piece>
        .text
new_piece:
        # Subset:   3
        #
        # Args:
        #    - $a0: int should_announce
        #
        # Returns:  None
        #
        # Frame:    [...]
        # Uses:     [...]
        # Clobbers: [...]
        #
        # Locals:
        #   - ...
        #
        # Structure:
        #   new_piece
        #   -> [prologue]
        #       -> body
        #   -> [epilogue]

new_piece__prologue:
	begin
	#Change piece_x, piece_y, piece_rotation
	la	$t0, piece_x
	li 	$t1, 4
	sw 	$t1, ($t0)

	la	$t0, piece_y
	li 	$t1, 1
	sw 	$t1, ($t0)

	la	$t0, piece_rotation
	li 	$t1, 0
	sw 	$t1, ($t0)

	#t0, t1 are free to use again
	#piece_symbol = shapes[next_shape_index].symbol

	la 	$t0, piece_symbol	#t0 = piece symbol address
	la	$t1, shapes		#t1 = shapes address
	lw	$t2, next_shape_index	#t2 = next_shape_index
	
	#pointer arithmetic
	mul	$t2, $t2, 36		#t2 = next_shape_index * 36
	addu 	$t1, $t1, $t2		#t1 = shapes address + increment
	lb 	$t1, ($t1)		#t1 = dereference
	sb 	$t1, ($t0)		#(t0) = value 

	#t0, t1, t2 are free

new_piece__if_statement_1:		#Compare if O or I and jump to function
	la	$t0, piece_symbol
	lb	$t0, ($t0)
	li 	$t1, 'O'
	beq	$t0, $t1, new_piece__is_o 

	la	$t0, piece_symbol
	lb	$t0, ($t0)
	li 	$t1, 'I'
	beq	$t0, $t1, new_piece__is_i 

	j 	new_piece__for_loop_prologue

	#t0 and t1 are free to use beyond this point

new_piece__is_o:
	la 	$t0, piece_x
	lw	$t1, ($t0)
	addi	$t1, $t1, -1
	sb 	$t1, ($t0)

	la 	$t0, piece_y
	lw	$t1, ($t0)
	addi	$t1, $t1, -1
	sb 	$t1, ($t0)

	j	new_piece__for_loop_prologue 

new_piece__is_i:
	la 	$t0, piece_y
	lw	$t1, ($t0)
	addi	$t1, $t1, -1
	sb 	$t1, ($t0)

	j	new_piece__for_loop_prologue 

	#t0 and t1 are free to use beyond this point
new_piece__for_loop_prologue:
	#initialization 
	li 	$t0, 0
	la 	$t1, shape_coordinates
	la	$t2, shapes

	lw	$t3, next_shape_index	#Calculate increment of shapes to 
	mul 	$t3, $t3, 36		#the appropriate letter of SHAPES
	addi	$t3, $t3, 4		#get to start of array

	addu 	$t2, $t2, $t3		#Add increment with memory address

new_piece__for_loop:
	#change the X variable first
	lw	$t3, ($t2)
	sw	$t3, ($t1)

	#change the Y variable first
	lw	$t3, 4($t2)
	sw	$t3, 4($t1)

new_piece__for_loop_condition:
	addi	$t0, $t0, 1
	addi	$t1, $t1, 8
	addi	$t2, $t2, 8
	bge 	$t0, PIECE_SIZE, new_piece__next_shape_index_modify
	j	new_piece__for_loop 

	#t0, t1, t2, t3, are free to use again
	
new_piece__next_shape_index_modify:
	lw	$t0, next_shape_index
	addi	$t0, $t0, 1
	rem	$t0, $t0, NUM_SHAPES
	la 	$t1, next_shape_index
	sw	$t0, ($t1)

	#t0 and t1 are free to use 

new_piece__if_statement_2:
	push 	$ra
	jal 	piece_intersects_field
	pop	$ra
	beq 	$v0, 1, new_piece__if_statement_2_true
	j	new_piece__if_statement_2_else_if	

new_piece__if_statement_2_true:
	push 	$ra
	jal 	print_field
	pop 	$ra

	li 	$v0, 4
	la	$a0, str__new_piece__game_over
	syscall

	la	$t0, game_running
	li 	$t1, FALSE
	sw	$t1, ($t0)

new_piece__if_statement_2_else_if:
	bne	$a0, 1, new_piece__epilogue

new_piece__else_if_true:
	li 	$v0, 4
	la 	$a0, str__new_piece__appeared
	syscall

	li 	$v0, 11	
	lb 	$a0, piece_symbol
	syscall

	li 	$v0, 11	
	li	$a0, '\n'
	syscall

new_piece__epilogue:
	end
        jr      $ra



################################################################################
# .TEXT <consume_lines>
        .text
consume_lines:
        # Subset:   3
        #
        # Args:     None
        #
        # Returns:  None
        #
        # Frame:    [...]
        # Uses:     [...]
        # Clobbers: [...]
        #
        # Locals:
        #   - ...
        #
        # Structure:
        #   consume_lines
        #   -> [prologue]
        #       -> body
        #   -> [epilogue]

	#FUNCTION NAMING SCHEME
	#Function will be named CL (consume prologue) with name and level
	#ex: cl_for_loop_initialize_1_2
	#cl for loop initalize level 1, 2nd loop

consume_lines__prologue:
	begin

	push 	$s0 			#lines_cleared
	push 	$s1			#iterator row 
	push 	$s2			#line_is_full
	push 	$s3			
	push 	$s4
	push 	$s5
	push 	$s6
	push 	$s7

	li 	$s0, 0 

cl_for_loop_initialize_1:
	addi	$s1, $0, FIELD_HEIGHT 	#row = FIELD_HEIGHT - 1
	sub	$s1, $s1, 1

cl_for_loop_1:
	li	$s2, TRUE 		#line_is_full = TRUE


cl_for_loop_initialize_2_1: 
	li 	$t0, 0			#t0 int col = 0

cl_for_loop_2_1:
	#Calculate if field_row[row][col] == EMPTY
	la	$t1, field		#t1 = field address
	mul	$t2, $s1, FIELD_WIDTH	#t2 = field_width * row
	add	$t2, $t2, $t0		#t2 = t2 + col operator
	addu	$t1, $t1, $t2		#t1 = incremented row location

	lb	$t1, ($t1) 		#contents of t1 in t1
	beq 	$t1, EMPTY, cl_for_loop_2_1_true
	j	cl_for_loop_condition_2_1 

cl_for_loop_2_1_true:	
	li	$s2, FALSE		

cl_for_loop_condition_2_1:
	addi	$t0, $t0, 1
	bge 	$t0, FIELD_WIDTH, cl_for_loop_end_2_1
	j	cl_for_loop_2_1	
	#t0, t1, t2, are free to use again

cl_for_loop_end_2_1:
	#Check if line is full
	#Equivalent c code
	#if (!line_is_full) {
        #    continue;
        #}
	beq	$s2, 0, cl_for_loop_condition_1 

cl_for_loop_initialize_2_2:
	move	$t0, $s1		#t0 = row_to_copy

cl_for_loop_condition_2_2:
	bgt	0, $t0, cl_for_loop_end_2_2 #row_to_copy >= 0

cl_for_loop_2_2:

#######################################
cl_for_loop_initialize_3_1:
	li	$t1, 0 			#t1 = col = 0

cl_for_loop_condition_3_1:
	bge 	$t1, FIELD_WIDTH, cl_for_loop_end_3_1 

cl_for_loop_3_1:
	bne 	$t0, 0, row_copy_not_zero 

row_copy_zero:
	la	$t2, field
	mul	$t3, $t0, FIELD_WIDTH
	add	$t3, $t3, $t1
	addu	$t2, $t2, $t3
	li	$t3, EMPTY
	sb	$t3, ($t2)

	j 	cl_for_loop_increment_3_1

row_copy_not_zero:
	la	$t2, field		
	mul	$t3, $t0, FIELD_WIDTH
	add	$t3, $t3, $t1		#SAVE ADDRESS OF field[row_to_copy][col]
	addu	$t2, $t2, $t3		#at t2

	la	$t3, field
	move	$t4, $t0		#t4 = row-copy
	sub	$t4, $t4, 1		#t4 -= 1
	mul	$t5, $t4, FIELD_WIDTH
	add	$t5, $t5, $t1
	addu	$t3, $t3, $t5		#t3 = address of field[rtc - 1][col]

	lb 	$t4, ($t3)
	sb	$t4, ($t2)

	j 	cl_for_loop_increment_3_1

cl_for_loop_increment_3_1:
	addi	$t1, $t1, 1
	j 	cl_for_loop_condition_3_1 

cl_for_loop_end_3_1:
	#t0, t1, t2, t3, t4, t5 are free and can be used again
########################################

	sub	$t0, $t0, 1
	j	cl_for_loop_condition_2_2 

cl_for_loop_end_2_2:
	#add
	#       row++;
        # lines_cleared++;
        # score += compute_points_for_line(lines_cleared);
	addi	$s1, $s1, 1
	addi	$s0, $s0, 1

	#add score by calling function
	move 	$a0, $s0
	push 	$ra
	jal 	compute_points_for_line	#Score to be added is now in v0
	pop	$ra
	
	la	$t7, score
	lw	$t6, ($t7)
	add	$t6, $t6, $v0
	sw	$t6, ($t7)

cl_for_loop_condition_1:
	sub	$s1, $s1, 1		#row--
	bgt	0, $s1, consume_lines__epilogue
	j	cl_for_loop_1 

consume_lines__epilogue:

	pop	$s7
	pop	$s6
	pop	$s5
	pop	$s4
	pop	$s3
	pop	$s2
	pop	$s1
	pop	$s0
	end

        jr      $ra


################################################################################
################################################################################
###                   PROVIDED FUNCTIONS — DO NOT CHANGE                     ###
################################################################################
################################################################################

################################################################################
# .TEXT <show_debug_info>
        .text
show_debug_info:
	# Args:     None
        #
        # Returns:  None
	#
	# Frame:    []
	# Uses:     [$a0, $v0, $t0, $t1, $t2, $t3]
	# Clobbers: [$a0, $v0, $t0, $t1, $t2, $t3]
	#
	# Locals:
	#   - $t0: i
	#   - $t1: coordinates address calculations
	#   - $t2: row
	#   - $t3: col
	#   - $t4: field address calculations
	#
	# Structure:
	#   print_board
	#   -> [prologue]
	#   -> body
	#     -> coord_loop
	#       -> coord_loop__init
	#       -> coord_loop__cond
	#       -> coord_loop__body
	#       -> coord_loop__step
	#       -> coord_loop__end
	#     -> row_loop
	#       -> row_loop__init
	#       -> row_loop__cond
	#       -> row_loop__body
	#         -> col_loop
	#           -> col_loop__init
	#           -> col_loop__cond
	#           -> col_loop__body
	#           -> col_loop__step
	#           -> col_loop__end
	#       -> row_loop__step
	#       -> row_loop__end
	#   -> [epilogue]

show_debug_info__prologue:

show_debug_info__body:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, str__show_debug_info__next_shape_index
	syscall					# printf("next_shape_index = ");

	li	$v0, 1				# sycall 1: print_int
	lw	$a0, next_shape_index		# next_shape_index
	syscall					# printf("%d", next_shape_index);

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'
	syscall					# putchar('\n');


	li	$v0, 4				# syscall 4: print_string
	la	$a0, str__show_debug_info__piece_symbol
	syscall					# printf("piece_symbol     = ");

	li	$v0, 1				# sycall 1: print_int
	lb	$a0, piece_symbol		# piece_symbol
	syscall					# printf("%d", piece_symbol);

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'
	syscall					# putchar('\n');


	li	$v0, 4				# syscall 4: print_string
	la	$a0, str__show_debug_info__piece_x
	syscall					# printf("piece_x          = ");

	li	$v0, 1				# sycall 1: print_int
	lw	$a0, piece_x			# piece_x
	syscall					# printf("%d", piece_x);

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'
	syscall					# putchar('\n');


	li	$v0, 4				# syscall 4: print_string
	la	$a0, str__show_debug_info__piece_y
	syscall					# printf("piece_y          = ");

	li	$v0, 1				# sycall 1: print_int
	lw	$a0, piece_y			# piece_y
	syscall					# printf("%d", piece_y);

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'
	syscall					# putchar('\n');


	li	$v0, 4				# syscall 4: print_string
	la	$a0, str__show_debug_info__game_running
	syscall					# printf("game_running     = ");

	li	$v0, 1				# sycall 1: print_int
	lw	$a0, game_running		# game_running
	syscall					# printf("%d", game_running);

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'
	syscall					# putchar('\n');


	li	$v0, 4				# syscall 4: print_string
	la	$a0, str__show_debug_info__piece_rotation
	syscall					# printf("piece_rotation   = ");

	li	$v0, 1				# sycall 1: print_int
	lw	$a0, piece_rotation		# piece_rotation
	syscall					# printf("%d", piece_rotation);

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'
	syscall					# putchar('\n');


show_debug_info__coord_loop:
show_debug_info__coord_loop__init:
	li	$t0, 0				# int i = 0;

show_debug_info__coord_loop__cond:		# while (i < PIECE_SIZE) {
	bge	$t0, PIECE_SIZE, show_debug_info__coord_loop__end

show_debug_info__coord_loop__body:
	li	$v0, 4				#   syscall 4: print_string
	la	$a0, str__show_debug_info__coordinates_1
	syscall					#   printf("coordinates[");

	li	$v0, 1				#   syscall 1: print_int
	move	$a0, $t0
	syscall					#   printf("%d", i);

	li	$v0, 4				#   syscall 4: print_string
	la	$a0, str__show_debug_info__coordinates_2
	syscall					#   printf("]   = { ");

	mul	$t1, $t0, SIZEOF_COORDINATE	#   i * sizeof(struct coordinate)
	addi	$t1, $t1, shape_coordinates	#   &shape_coordinates[i]

	li	$v0, 1				#   syscall 1: print_int
	lw	$a0, COORDINATE_X_OFFSET($t1)	#   shape_coordinates[i].x
	syscall					#   printf("%d", shape_coordinates[i].x);

	li	$v0, 4				#   syscall 4: print_string
	la	$a0, str__show_debug_info__coordinates_3
	syscall					#   printf(", ");

	li	$v0, 1				#   syscall 1: print_int
	lw	$a0, COORDINATE_Y_OFFSET($t1)	#   shape_coordinates[i].y
	syscall					#   printf("%d", shape_coordinates[i].y);

	li	$v0, 4				#   syscall 4: print_string
	la	$a0, str__show_debug_info__coordinates_4
	syscall					#   printf(" }\n");

show_debug_info__coord_loop__step:
	addi	$t0, $t0, 1			#   i++;
	b	show_debug_info__coord_loop__cond

show_debug_info__coord_loop__end:		# }

	li	$v0, 4				# syscall 4: print_string
	la	$a0, str__show_debug_info__field
	syscall					# printf("\nField:\n");

show_debug_info__row_loop:
show_debug_info__row_loop__init:
	li	$t2, 0				# int row = 0;

show_debug_info__row_loop__cond:		# while (row < FIELD_HEIGHT) {
	bge	$t2, FIELD_HEIGHT, show_debug_info__row_loop__end

show_debug_info__row_loop__body:
	bge	$t2, 10, show_debug_info__print_row
	li	$v0, 11				#  if (row < 10) {
	li	$a0, ' '
	syscall					#     putchar(' ');

show_debug_info__print_row:			#   }
	li	$v0, 1				#   syscall 1: print_int
	move	$a0, $t2
	syscall					#   printf("%d", row);


	li	$v0, 4				#   syscall 4: print_string
	la	$a0, str__show_debug_info__field_indent
	syscall					#   printf(":  ");

show_debug_info__col_loop:
show_debug_info__col_loop__init:
	li	$t3, 0				#   int col = 0;

show_debug_info__col_loop__cond:		#   while (col < FIELD_WIDTH) {
	bge	$t3, FIELD_WIDTH, show_debug_info__col_loop__end

show_debug_info__col_loop__body:
	mul	$t4, $t2, FIELD_WIDTH		#     row * FIELD_WIDTH
	add	$t4, $t4, $t3			#     row * FIELD_WIDTH + col
	addi	$t4, $t4, field			#     &field[row][col]

	li	$v0, 1				#     syscall 1: print_int
	lb	$a0, ($t4)			#     field[row][col]
	syscall					#     printf("%d", field[row][col]);

	li	$v0, 11				#     syscall 11: print_char
	li	$a0, ' '
	syscall					#     putchar(' ');

	lb	$a0, ($t4)			#     field[row][col]
	syscall					#     printf("%c", field[row][col]);

	li	$v0, 11				#     syscall 11: print_char
	li	$a0, ' '
	syscall					#     putchar(' ');

show_debug_info__col_loop__step:
	addi	$t3, $t3, 1			#     i++;
	b	show_debug_info__col_loop__cond

show_debug_info__col_loop__end:			#   }

	li	$v0, 11				#   syscall 11: print_char
	li	$a0, '\n'
	syscall					#   putchar('\n');

show_debug_info__row_loop__step:
	addi	$t2, $t2, 1			#   row++;
	b	show_debug_info__row_loop__cond

show_debug_info__row_loop__end:			# }

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'
	syscall					# putchar('\n');

show_debug_info__epilogue:
	jr	$ra


################################################################################
# .TEXT <game_loop>
        .text
game_loop:
        # Args:     None
        #
        # Returns:  None
        #
        # Frame:    [$ra]
        # Uses:     [$t0, $t1, $v0, $a0]
        # Clobbers: [$t0, $t1, $v0, $a0]
        #
        # Locals:
        #   - $t0: copy of game_running
        #   - $t1: char command
        #
        # Structure:
        #   game_loop
        #   -> [prologue]
        #       -> body
	#         -> big_loop
	#         -> big_loop__cond
	#         -> big_loop__body
	#           -> game_loop__command_r
	#           -> game_loop__command_R
	#           -> game_loop__command_n
	#           -> game_loop__command_s
	#           -> game_loop__command_S
	#           -> game_loop__command_a
	#           -> game_loop__command_d
	#           -> game_loop__command_p
	#           -> game_loop__command_c
	#           -> game_loop__command_question
	#           -> game_loop__command_q
	#           -> game_loop__unknown_command
	#         -> big_loop__step
	#         -> big_loop__end
        #   -> [epilogue]

game_loop__prologue:
	begin
	push	$ra

game_loop__body:
game_loop__big_loop__cond:
	lw	$t0, game_running
	beqz	$t0, game_loop__big_loop__end		# while (game_running) {

game_loop__big_loop__body:
	jal	print_field				#   print_field();

	li	$v0, 4					#   syscall 4: print_string
	la	$a0, str__game_loop__prompt
	syscall						#   printf("  > ");

	jal	read_char
	move	$t1, $v0				#   command = read_char();

	beq	$t1, 'r', game_loop__command_r		#   if (command == 'r') { ...
	beq	$t1, 'R', game_loop__command_R		#   } else if (command == 'R') { ...
	beq	$t1, 'n', game_loop__command_n		#   } else if (command == 'n') { ...
	beq	$t1, 's', game_loop__command_s		#   } else if (command == 's') { ...
	beq	$t1, 'S', game_loop__command_S		#   } else if (command == 'S') { ...
	beq	$t1, 'a', game_loop__command_a		#   } else if (command == 'a') { ...
	beq	$t1, 'd', game_loop__command_d		#   } else if (command == 'd') { ...
	beq	$t1, 'p', game_loop__command_p		#   } else if (command == 'p') { ...
	beq	$t1, 'c', game_loop__command_c		#   } else if (command == 'c') { ...
	beq	$t1, '?', game_loop__command_question	#   } else if (command == '?') { ...
	beq	$t1, 'q', game_loop__command_q		#   } else if (command == 'q') { ...
	b	game_loop__unknown_command		#   } else { ... }

game_loop__command_r:					#   if (command == 'r') {
	jal	rotate_right				#     rotate_right();

	jal	piece_intersects_field			#     call piece_intersects_field();
	beqz	$v0, game_loop__big_loop__cond		#     if (piece_intersects_field())
	jal	rotate_left				#       rotate_left();

	b	game_loop__big_loop__cond		#   }

game_loop__command_R:					#   else if (command == 'R') {
	jal	rotate_left				#     rotate_left();

	jal	piece_intersects_field			#     call piece_intersects_field();
	beqz	$v0, game_loop__big_loop__cond		#     if (piece_intersects_field())
	jal	rotate_right				#       rotate_right();

	b	game_loop__big_loop__cond		#   }

game_loop__command_n:					#   else if (command == 'n') {
	li	$a0, FALSE				#     argument 0: FALSE
	jal	new_piece				#     new_piece(FALSE);

	b	game_loop__big_loop__cond		#   }

game_loop__command_s:					#   else if (command == 's') {
	li	$a0, 0					#     argument 0: 0
	li	$a1, 1					#     argument 1: 1
	jal	move_piece				#     call move_piece(0, 1);

	bnez	$v0, game_loop__big_loop__cond		#     if (!piece_intersects_field())
	jal	place_piece				#       rotate_left();

	b	game_loop__big_loop__cond		#   }

game_loop__command_S:					#   else if (command == 'S') {
game_loop__hard_drop_loop:
	li	$a0, 0					#     argument 0: 0
	li	$a1, 1					#     argument 1: 1
	jal	move_piece				#     call move_piece(0, 1);
	bnez	$v0, game_loop__hard_drop_loop		#     while (move_piece(0, 1));

	jal	place_piece				#     place_piece();

	b	game_loop__big_loop__cond		#   }

game_loop__command_a:					#   else if (command == 'a') {
	li	$a0, -1					#     argument 0: -1
	li	$a1, 0					#     argument 1: 0
	jal	move_piece				#     move_piece(-1, 0);

	b	game_loop__big_loop__cond		#   }

game_loop__command_d:					#   else if (command == 'd') {
	li	$a0, 1					#     argument 0: 1
	li	$a1, 0					#     argument 1: 0
	jal	move_piece				#     move_piece(1, 0);

	b	game_loop__big_loop__cond		#   }

game_loop__command_p:					#   else if (command == 'p') {
	jal	place_piece				#     place_piece();

	b	game_loop__big_loop__cond		#   }

game_loop__command_c:					#   else if (command == 'c') {
	jal	choose_next_shape			#     choose_next_shape();

	b	game_loop__big_loop__cond		#   }

game_loop__command_question:				#   else if (command == '?') {
	jal	show_debug_info				#     show_debug_info();

	b	game_loop__big_loop__cond		#   }

game_loop__command_q:					#   else if (command == 'q') {
	li	$v0, 4					#     syscall 4: print_string
	la	$a0, str__game_loop__quitting
	syscall						#     printf("Quitting...\n");

	b	game_loop__big_loop__end		#     break;

game_loop__unknown_command:				#   } else {
	li	$v0, 4					#     syscall 4: print_string
	la	$a0, str__game_loop__unknown_command
	syscall						#     printf("Unknown command!\n");

game_loop__big_loop__step:				#   }
	b	game_loop__big_loop__cond

game_loop__big_loop__end:				# }
	li	$v0, 4					# syscall 4: print_string
	la	$a0, str__game_loop__goodbye
	syscall						# printf("\nGoodbye!\n");

game_loop__epilogue:
	pop	$ra
	end

	jr	$ra					# return;


################################################################################
# .TEXT <show_debug_info>
        .text
read_char:
	# NOTE: The implementation of this function is
	#       DIFFERENT from the C code! This is
	#       because mipsy handles input differently
	#       compared to `scanf`. You do not need to
	#       worry about this difference as you will
	#       only be calling this function.
	#
        # Args:     None
        #
        # Returns:  $v0: char
        #
        # Frame:    []
        # Uses:     [$v0]
        # Clobbers: [$v0]
        #
        # Locals:
	#   - $v0: char command
        #
        # Structure:
        #   read_char
        #   -> [prologue]
        #       -> body
        #   -> [epilogue]

read_char__prologue:

read_char__body:
	li	$v0, 12				# syscall 12: read_char
	syscall					# scanf("%c", &command);

read_char__epilogue:
	jr	$ra				# return command;
