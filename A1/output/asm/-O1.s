	.file	"sumofbillion.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC1:
	.ascii "Execution time: %f seconds\12\0"
LC2:
	.ascii "%lld\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB14:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	andl	$-16, %esp
	subl	$32, %esp
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	call	___main
	call	_clock
	movl	%eax, %ebx
	movl	$0, %eax
	movl	$0, %edx
L2:
	addl	$1, %eax
	adcl	$0, %edx
	movl	%eax, %ecx
	xorl	$1000000001, %ecx
	movl	%edx, %esi
	orl	%ecx, %esi
	jne	L2
	call	_clock
	subl	%ebx, %eax
	movl	%eax, 28(%esp)
	fildl	28(%esp)
	fdivs	LC0
	fstpl	4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$-243309312, 8(%esp)
	movl	$116415321, 12(%esp)
	movl	$LC2, 4(%esp)
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fprintf
	movl	$0, %eax
	leal	-8(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.section .rdata,"dr"
	.align 4
LC0:
	.long	1148846080
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_clock;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
