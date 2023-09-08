	.file	"sumofbillion.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC1:
	.ascii "Execution time: %f seconds\12\0"
LC2:
	.ascii "%lld\12\0"
	.section	.text.startup,"x"
	.p2align 4,,15
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
	pushl	%ebx
	andl	$-16, %esp
	subl	$32, %esp
	.cfi_offset 3, -12
	call	___main
	call	_clock
	movl	%eax, %ebx
	call	_clock
	subl	%ebx, %eax
	movl	$LC1, (%esp)
	movl	%eax, 28(%esp)
	fildl	28(%esp)
	fdivs	LC0
	fstpl	4(%esp)
	call	_printf
	movl	__imp___iob, %eax
	movl	$-243309312, 8(%esp)
	movl	$116415321, 12(%esp)
	movl	$LC2, 4(%esp)
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fprintf
	xorl	%eax, %eax
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
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
