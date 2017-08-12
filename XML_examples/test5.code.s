.data
.text
__init:
        # setup the base address of stack lui $sp, 0x8000
        addi $sp, $sp, 0x0000
        # allocate stack frame for main function
        addiu $sp, $sp, -64
        jal __main
        # make a system call and terminate the program
        li $v0, 10
        syscall

__main:
        li $t8,1
        move $s0,$t8
        li $t9,2
        mul $t0,$s0,$t9
        li $t9,3
        add $t1,$t0,$t9
        move $s0,$t1
                move $a0,$s0
        li $t8,2
        li $t9,3
        add $t2,$t8,$t9
                move $a0,$t2
        # allocate stack frame for the callee
        addiu $sp, $sp, -64
        sw $ra, 0($sp)
        jal __foo
        # restore the $ra and deallocate the stack frame for the callee
        lw $ra, 0($sp)
        addiu $sp, $sp, 64
        move $t3,$v0
        move $s0,$t3
        move $v0,$s0
        jr $ra

__foo:
        add $t4,$a0,$a1
        move $v0,$t4
        jr $ra
