/**
 * @file raw_simple.s
 * @author volovo
 * @date 17.12.2014
 * @brief jednoduchy assemler program
 * @detail dela to naseldujici:
 *   int i, j;
 *   i = 10;
 *   j = i + 7;
 *   j++;
 *   return 3;
 * -------------------------------------
 * Poznamky:
 *  %eax - je 4bytovy general purpose register - AX register je na 16bitovych masinach
 *         extended AX (EAX) je na 32bitovych masinach
 *         na 64bitove masine jsou pointery rax, rbx, ...
 *  dalsi "normalni" 32bitove registry jsou: eax, ebx, ecx, edx, ebp, edi, esi 
 *         - jejich dolni 16bitova cast jsou ax, bx, cx, dx
 *         - jejich dolni 8bitova cast jsou al, bl, cl, dl 
 *         - horni byte 16bitove casti jsou registry ah, bh, ch, dh
 *  stack pointer - register esp (pro 32bitu), rsp (pro 64bitu), sp (16bitu)
 *  instruction pointer - eip (32b), rip(64b), ip(16b)
 *  base pointer - todo
 */
	.file	"raw_simple.s"
	.text
	.globl	main
	.type	main, @function	
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$10, -4(%rbp)         # do adresy na stack-4 ulozi 10 
	movl	-4(%rbp), %eax        # fullword z teto adresy na stacku ulozi do eax
	addl	$7, %eax              # eax incrementuje o 7
	movl	%eax, -8(%rbp)        # fullword z eax ulozi na stack-8
	addl	$1, -8(%rbp)          # fullwor na stack-8 inkrementuje o 1
	movl	$3, %eax              # do eax ulozi hodnotu 3
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 4.7.2-5) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
