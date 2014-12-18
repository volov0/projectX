	.file	"simple.c"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	$10, -4(%rbp)
	movl	-4(%rbp), %eax
	addl	$7, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %edi
	call	fxn
	movl	%eax, -12(%rbp)
	addl	$1, -12(%rbp)
	movl	-12(%rbp), %eax
	leave
	ret
	.size	main, .-main
	.globl	fxn
	.type	fxn, @function
fxn:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	addl	$9, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	$2, %edx
	movl	$4, %esi
	movl	%eax, %edi
	call	gxn
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
	.size	fxn, .-fxn
	.globl	gxn
	.type	gxn, @function
gxn:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movl	%edx, -44(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movl	-4(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movl	%edx, -32(%rbp,%rax,4)
	addl	$1, -4(%rbp)
.L6:
	cmpl	$3, -4(%rbp)
	jle	.L7
	movl	-44(%rbp), %eax
	movl	-4(%rbp), %edx
	addl	%eax, %edx
	movl	-36(%rbp), %eax
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	ret
	.size	gxn, .-gxn
	.ident	"GCC: (Debian 4.7.2-5) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
