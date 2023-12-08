        .globl main
        .text
main:
        li      $v0, 1 #Load syscall 4 into syscall register
        li      $t1, 1
        li      $t2, 2
        mul     $t3, $t2, $t1

        move    $a0, $t3
        syscall



        li  $v0, 10
        syscall
        
        .data

hello_world_message:
        .asciiz "Hello World\n"
