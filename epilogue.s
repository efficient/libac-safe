	.bss

	.type	ingerc_epilogue_a,@object
	.align	8
ingerc_epilogue_a:
	.zero	8
	.size	ingerc_epilogue_a, .-ingerc_epilogue_a

	.type	ingerc_epilogue_d,@object
	.align	8
ingerc_epilogue_d:
	.zero	8
	.size	ingerc_epiligue_d, .-ingerc_epilogue_d

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
	mov	ingerc_epilogue_a@gotpcrel(%rip), %rcx
	mov	%rax, (%rcx)
	mov	ingerc_epilogue_d@gotpcrel(%rip), %rcx
	mov	%rdx, (%rcx)
	mov	ingerc_epilogue_ip@gotpcrel(%rip), %rax
	mov	(%rsp), %rcx
	mov	%rcx, (%rax)
	mov	ingerc_epilogue_sp@gotpcrel(%rip), %rax
	lea	8(%rsp), %rcx
	mov	%rcx, (%rax)
	mov	ingerc_epilogue_fp@gotpcrel(%rip), %rax
	lea	8(%rdi), %rcx
	mov	%rcx, (%rax)
	mov	ingerc_epilogue_ra@gotpcrel(%rip), %rax
	mov	8(%rdi), %rcx
	mov	%rcx, (%rax)
	mov	ingerc_epilogue_end@gotpcrel(%rip), %rax
	mov	%rax, 8(%rdi)
	ret
	.size	ingerc_epilogue_start, .-ingerc_epilogue_start

	.type	ingerc_epilogue_end,@function
	.globl	ingerc_epilogue_end
ingerc_epilogue_end:
	mov	ingerc_epilogue_ra@gotpcrel(%rip), %rcx
	mov	(%rcx), %rdi
	xor	%rsi, %rsi
	mov	%rsi, (%rcx)
	jmp	*%rdi
	.size	ingerc_epilogue_end, .-ingerc_epilogue_end
