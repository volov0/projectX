/**
 * @file raw_simple.s
 * @author volovo
 * @date 17.12.2014
 * @brief jednoduchy assemler program AT&T syntax
 * @detail dela to naseldujici:
 *   int i, j, k;
 *   i = 10;
 *   j = i + 7;
 *   j++;
 *   k = fxn(j);
 *   return k;
 *
 * int fxn(int a) { int x = a + 9; return a; }
 *
 * -------------------------------------
 * Poznamky:
 *  %eax - je 4bytovy general purpose register - AX register je na 16bitovych masinach
 *         extended AX (EAX) je na 32bitovych masinach
 *         na 64bitove masine jsou pointery rax, rbx, ...
 *  dalsi "normalni" 32bitove registry jsou: eax, ebx, ecx, edx,  edi, esi 
 *         - jejich dolni 16bitova cast jsou ax, bx, cx, dx
 *         - jejich dolni 8bitova cast jsou al, bl, cl, dl 
 *         - horni byte 16bitove casti jsou registry ah, bh, ch, dh
 *  stack pointer - register esp (pro 32bitu), rsp (pro 64bitu), sp (16bitu)
 *                - instrukce pop, push implicitne meni esp(rsp), push dekrementuje esp
 *                  pop inkrementuje esp, prefix pop/push instrukce urcuje o kolik se 
 *                  de/inkrementuje (pushq - o 64bitu) 
 *  instruction pointer - eip (32b), rip(64b), ip(16b) - nelze ho menit, meni ho procesor
 *                      - dokonce ani nemuze v mov instrukci 
 *  base pointer - ebp(rbp) - je neco jako bazovy register, pri behu subrutiny obsahuje 
 *                 adresu vrcholu stacku v dobe kdy subrutina zacala. Tudiz tam jsou vsechny 
 *                 parametry a lokalni promenne, ktere jsou vzdy na konstantnim offsetu od ebp.
 *               - Na zacatku subrutiny se na stack vlozi stara hodnota ebp, aby se mohla   
 *                 obnovit pri navratu ze subrutiny.
 *  delka instrukci v x86 je variabilni... 1-15 bytu
 *
 *  POznamka ze stackoverflow.com
 *   GCC dictates how the stack is used. Contract between caller and callee on x86:
 *    - after call instruction:
 *      o %eip points at first instruction of function
 *      o %esp+4 points at first argument
 *      o %esp points at return address 
 *    - after ret instruction:
 *      o %eip contains return address
 *      o %esp points at arguments pushed by caller
 *      o called function may have trashed arguments
 *      o %eax contains return value (or trash if function is void)
 *      o %ecx, %edx may be trashed
 *      o %ebp, %ebx, %esi, %edi must contain contents from time of call 
 *    - Terminology:
 *      o %eax, %ecx, %edx are "caller save" registers
 *      o %ebp, %ebx, %esi, %edi are "callee save" registers 
 */
	.file	"raw_simple.s"
	.text
	.globl	main                  # glogbl direktiva dela symbol "main" viditelny pro ld (linker)
	.type	main, @function       # definuje typ symbolu "main" jako function
main:
	pushq	%rbp                  # uloz starou hodnotu base pointeru na stack
	movq	%rsp, %rbp            # nastav novou hodnotu base pointeru na soucasny vrchol stacku
	subq    $16,%rsp              # alokuj misto na stacku pro lokalni promenne
	movl	$10, -4(%rbp)         # do adresy na stack-4(int i) ulozi 10
	movl	-4(%rbp), %eax        # 4byty z teto adresy na stacku ulozi do eax
	addl	$7, %eax              # eax incrementuje o 7
	movl	%eax, -8(%rbp)        # 4byty z eax ulozi na stack-8(int j)
	addl	$1, -8(%rbp)          # 4bytovy int na stack-8(int j) inkrementuje o 1 - instrukce memory to memory (znak CISC architektury - ARM to treba nema)
	movl	-8(%rbp), %eax        # 4bytovy int na stack-8(int j) uloz do eax
	movl	%eax, %edi     	      # eax uloz do edi, coz je parametr
	call	fxn            	      # volej fxn() - na stack ulozi aktualni pozici v kodu(eip/rip)
	movl	%eax, -12(%rbp)       # uloz navratovou hodnotu z fxn() na stack-12(int k)	
	movl	-12(%rbp), %eax	      # uloz hodnotu ze stack-12(int k) do eax (return value)
	leave                         # leave instrukce kopiruje base pointer(ebp) do stack pointeru(esp) = inkrementace stack pointeru
	ret                           # vrat kontrolu volajici procedure (v tomto pripade OS) - adresa je na stacku
	.size	main, .-main          # velikost asociovana se symbolem "main"
	.globl	fxn
	.type	fxn, @function	
fxn:                       	
	pushq	%rbp                  # uloz starou hodnotu base pointeru na stack
	movq	%rsp, %rbp            # nastav novou hodnotu base pointeru na soucasny vrchol stacku
/* tady by mela byt alokace mista pro lokalni promennou -4(%rbp), 
 * ale kompilator to neudelal... (asi protoze se odtud nevola zadna dalsi funkce) */
	movl	%edi, -20(%rbp)       # uloz hodnotu %edi na stack-20
	movl	-20(%rbp), %eax       # do eax uloz hodnotu parametru
	addl	$9, %eax              # k eax pricti 9
	movl	%eax, -4(%rbp)        # vysledek uloz na stack-4(int x)
	movl	-4(%rbp), %eax        # uloz hodnotu ze stack-4(int x) do eax (return value)
	popq	%rbp                  # obnov base pointeru - je na vrcholu stacku
	ret                           # vrat kontrolu volajici procedure (main) - kam skocit se zjisti ze stacku
	.size	fxn, .-fxn            # velikost asociovana se symbolem fxn
	.ident	"GCC: (Debian 4.7.2-5) 4.7.2"     # GCC si to sem dalo samo pri dekodovani, neni nutne
	.section	.note.GNU-stack,"",@progbits  # ???
