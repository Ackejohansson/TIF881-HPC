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
LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$64, %esp
	call	___main
	movl	$0, 56(%esp)
	movl	$0, 60(%esp)
	movl	$1000000000, 48(%esp)
	call	_clock
	movl	%eax, 44(%esp)
	movl	$0, 52(%esp)
	jmp	L2
L3:
	movl	52(%esp), %eax
	cltd
	addl	%eax, 56(%esp)
	adcl	%edx, 60(%esp)
	addl	$1, 52(%esp)
L2:
	movl	52(%esp), %eax
	cmpl	48(%esp), %eax
	jle	L3
	call	_clock
	movl	%eax, 40(%esp)
	movl	40(%esp), %eax
	subl	44(%esp), %eax
	movl	%eax, 28(%esp)
	fildl	28(%esp)
	fldl	LC0
	fdivrp	%st, %st(1)
	fstpl	4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	56(%esp), %eax
	movl	60(%esp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$LC2, 4(%esp)
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fprintf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE11:
	.section .rdata,"dr"
	.align 8
LC0:
	.long	0
	.long	1083129856
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_clock;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
