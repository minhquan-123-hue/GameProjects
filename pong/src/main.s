	.file	"main.cpp"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7612:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA7612
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$184, %rsp
	.cfi_offset 3, -24
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
.LEHB0:
	call	_ZN4PongC1Ev
.LEHE0:
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
.LEHB1:
	call	_ZN4Pong4initEv
	xorl	$1, %eax
	testb	%al, %al
	je	.L2
	movl	$1, %ebx
	jmp	.L3
.L2:
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4Pong3runEv
.LEHE1:
	movl	$0, %ebx
.L3:
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4PongD1Ev
	movl	%ebx, %eax
	jmp	.L7
.L6:
	movq	%rax, %rbx
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4PongD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L7:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7612:
	.section	.gcc_except_table,"a",@progbits
.LLSDA7612:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE7612-.LLSDACSB7612
.LLSDACSB7612:
	.uleb128 .LEHB0-.LFB7612
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB7612
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L6-.LFB7612
	.uleb128 0
	.uleb128 .LEHB2-.LFB7612
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE7612:
	.text
	.size	main, .-main
	.globl	__gxx_personality_v0
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
