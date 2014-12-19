	.file	"cpp_swap.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.text
	.globl	_Z4swapRiS_
	.type	_Z4swapRiS_, @function
_Z4swapRiS_:
.LFB969:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movq	-32(%rbp), %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-32(%rbp), %rax
	movl	-4(%rbp), %edx
	movl	%edx, (%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE969:
	.size	_Z4swapRiS_, .-_Z4swapRiS_
	.section	.rodata
.LC0:
	.string	"x = "
.LC1:
	.string	", y = "
.LC2:
	.string	"swap"
	.text
	.globl	main
	.type	main, @function
main:
.LFB970:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA970
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$10, -20(%rbp)
	movl	$20, -24(%rbp)
	movl	-24(%rbp), %ebx
	movl	-20(%rbp), %r12d
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
.LEHB0:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%r12d, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	leaq	-24(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z4swapRiS_
	movl	-24(%rbp), %ebx
	movl	-20(%rbp), %r12d
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%r12d, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
.LEHE0:
	movl	$0, %eax
	jmp	.L6
.L5:
	movq	%rax, %rdi
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
.L6:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE970:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA970:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE970-.LLSDACSB970
.LLSDACSB970:
	.uleb128 .LEHB0-.LFB970
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L5-.LFB970
	.uleb128 0
	.uleb128 .LEHB1-.LFB970
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE970:
	.text
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB979:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L7
	cmpl	$65535, -8(%rbp)
	jne	.L7
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE979:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z4swapRiS_, @function
_GLOBAL__sub_I__Z4swapRiS_:
.LFB980:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE980:
	.size	_GLOBAL__sub_I__Z4swapRiS_, .-_GLOBAL__sub_I__Z4swapRiS_
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z4swapRiS_
	.hidden	__dso_handle
	.ident	"GCC: (Debian 4.7.2-5) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
