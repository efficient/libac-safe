	.type	realign,@function
	.globl	realign
realign:
	.cfi_startproc
	call	panic
	ud2
	.cfi_endproc
