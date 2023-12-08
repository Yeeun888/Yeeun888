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
	.word 4

shape_coordinates:		# struct coordinate shape_coordinates[PIECE_SIZE];
	.word 0,  0,  0,  -1,  -1,  0,  1,  0

piece_symbol:			# char piece_symbol;
	.byte	84#'I'

piece_x:			# int piece_x;
	.word	4

piece_y:			# int piece_y;
	.word	4

piece_rotation:			# int piece_rotation;
	.word	0

score:				# int score = 0;
	.word	0

game_running:			# int game_running = TRUE;
	.word	1

field:				# char field[FIELD_HEIGHT][FIELD_WIDTH];
	.byte	32:FIELD_HEIGHT * FIELD_WIDTH


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

	.text
main:
	jal 	consume_lines

	li 	$v0, 10
	syscall

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