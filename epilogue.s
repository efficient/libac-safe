	.bss

	.type	ingerc_epilogue_ip,@object
	.align	8
ingerc_epilogue_ip:
	.zero	8
	.size	ingerc_epilogue_ip, .-ingerc_epilogue_ip

	.type	ingerc_epilogue_sp,@object
	.align	8
ingerc_epilogue_sp:
	.zero	8
	.size	ingerc_epilogue_sp, .-ingerc_epilogue_sp

	.type	ingerc_epilogue_fp,@object
	.align	8
ingerc_epilogue_fp:
	.zero	8
	.size	ingerc_epilogue_fp, .-ingerc_epilogue_fp

	.type	ingerc_epilogue_ra,@object
	.align	8
ingerc_epilogue_ra:
	.zero	8
	.size	ingerc_epilogue_ra, .-ingerc_epilogue_ra

	.text

	.type	ingerc_epilogue_start,@function
	.globl	ingerc_epilogue_start
ingerc_epilogue_start:
	mov	ingerc_epilogue_ip@gotpcrel(%rip), %rsi
	mov	(%rsp), %rcx
	mov	%rcx, (%rsi)
	mov	ingerc_epilogue_sp@gotpcrel(%rip), %rsi
	lea	8(%rsp), %rcx
	mov	%rcx, (%rsi)
	mov	ingerc_epilogue_fp@gotpcrel(%rip), %rsi
	mov	%rdi, %rcx
	mov	%rcx, (%rsi)
	mov	ingerc_epilogue_ra@gotpcrel(%rip), %rsi
	mov	(%rdi), %rcx
	mov	%rcx, (%rsi)
	mov	ingerc_epilogue_end@gotpcrel(%rip), %rsi
	mov	%rsi, (%rdi)
	ret
	.size	ingerc_epilogue_start, .-ingerc_epilogue_start

	.type	ingerc_epilogue_end,@function
	.globl	ingerc_epilogue_end
ingerc_epilogue_end:
	mov	ingerc_epilogue_ra@gotpcrel(%rip), %rsi
	mov	(%rsi), %rdi
	xor	%rcx, %rcx
	mov	%rcx, (%rsi)
	jmp	*%rdi
	.size	ingerc_epilogue_end, .-ingerc_epilogue_end
