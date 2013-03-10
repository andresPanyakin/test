	.file	"sample.c"
	.text
.Ltext0:
	.comm	fd,4,4
	.section	.rodata
.LC0:
	.string	"Write %i to file (fd %i)\t"
	.text
	.globl	writeToFile
	.type	writeToFile, @function
writeToFile:
.LFB0:
	.file 1 "sample.c"
	.loc 1 10 0
	.cfi_startproc
	pushq	%rbp
.LCFI0:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
.LCFI1:
	.cfi_def_cfa_register 6
	.loc 1 12 0
	movl	j.2247(%rip), %eax
	cmpl	$10, %eax
	jle	.L2
	.loc 1 12 0 is_stmt 0 discriminator 1
	movl	$0, %eax
	jmp	.L3
.L2:
	.loc 1 13 0 is_stmt 1
	movl	fd(%rip), %eax
	movl	$4, %edx
	movl	$j.2247, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	write
	.loc 1 14 0
	movl	fd(%rip), %edx
	movl	j.2247(%rip), %eax
	movl	%eax, %ecx
	addl	$1, %eax
	movl	%eax, j.2247(%rip)
	movl	$.LC0, %eax
	movl	%ecx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	.loc 1 15 0
	movl	$1, %eax
.L3:
	.loc 1 16 0
	popq	%rbp
.LCFI2:
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	writeToFile, .-writeToFile
	.section	.rodata
.LC1:
	.string	"Read %i from file (fd %i)\n"
	.text
	.globl	readFromFile
	.type	readFromFile, @function
readFromFile:
.LFB1:
	.loc 1 19 0
	.cfi_startproc
	pushq	%rbp
.LCFI3:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
.LCFI4:
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	.loc 1 20 0
	movl	$0, -4(%rbp)
	.loc 1 21 0
	movl	fd(%rip), %eax
	movl	$1, %edx
	movq	$-4, %rsi
	movl	%eax, %edi
	movl	$0, %eax
	call	lseek
	.loc 1 22 0
	movl	fd(%rip), %eax
	leaq	-4(%rbp), %rcx
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	movl	$0, %eax
	call	read
	.loc 1 23 0
	movl	fd(%rip), %edx
	movl	-4(%rbp), %ecx
	movl	$.LC1, %eax
	movl	%ecx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	.loc 1 24 0
	leave
.LCFI5:
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	readFromFile, .-readFromFile
	.section	.rodata
.LC2:
	.string	"Usage: sample1 <outfile>\n"
.LC3:
	.string	"ERROR: "
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.loc 1 26 0
	.cfi_startproc
	pushq	%rbp
.LCFI6:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
.LCFI7:
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	.loc 1 31 0
	cmpl	$2, -4(%rbp)
	je	.L6
	.loc 1 32 0
	movl	$.LC2, %edi
	call	puts
	.loc 1 33 0
	movl	$-1, %eax
	jmp	.L7
.L6:
	.loc 1 36 0
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$66, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, fd(%rip)
	movl	fd(%rip), %eax
	cmpl	$-1, %eax
	jne	.L11
	.loc 1 37 0
	movl	$.LC3, %edi
	call	perror
	.loc 1 38 0
	movl	$-1, %eax
	jmp	.L7
.L10:
	.loc 1 41 0 discriminator 2
	movl	$0, %eax
	call	readFromFile
	jmp	.L9
.L11:
	.loc 1 41 0 is_stmt 0
	nop
.L9:
	.loc 1 41 0 discriminator 1
	movl	$0, %eax
	call	writeToFile
	testl	%eax, %eax
	jne	.L10
	.loc 1 42 0 is_stmt 1
	movl	fd(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	close
	.loc 1 43 0
	movl	$0, %eax
.L7:
	.loc 1 44 0
	leave
.LCFI8:
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.data
	.align 4
	.type	j.2247, @object
	.size	j.2247, 4
j.2247:
	.long	1
	.text
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x18b
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF15
	.byte	0x1
	.long	.LASF16
	.long	.LASF17
	.quad	.Ltext0
	.quad	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x4
	.byte	0x8
	.long	0x6b
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF9
	.uleb128 0x5
	.byte	0x1
	.long	.LASF18
	.byte	0x1
	.byte	0xa
	.long	0x57
	.quad	.LFB0
	.quad	.LFE0
	.long	.LLST0
	.long	0xc7
	.uleb128 0x6
	.string	"j"
	.byte	0x1
	.byte	0xb
	.long	0x57
	.byte	0x9
	.byte	0x3
	.quad	j.2247
	.uleb128 0x7
	.byte	0x1
	.long	.LASF10
	.byte	0x1
	.byte	0xd
	.long	0x57
	.byte	0x1
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x9
	.byte	0x1
	.long	.LASF19
	.byte	0x1
	.byte	0x13
	.quad	.LFB1
	.quad	.LFE1
	.long	.LLST1
	.long	0x116
	.uleb128 0x6
	.string	"i"
	.byte	0x1
	.byte	0x14
	.long	0x57
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.byte	0x1
	.long	.LASF20
	.byte	0x1
	.byte	0x15
	.long	0x57
	.byte	0x1
	.long	0x106
	.uleb128 0x8
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.long	.LASF11
	.byte	0x1
	.byte	0x16
	.long	0x57
	.byte	0x1
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0xb
	.byte	0x1
	.long	.LASF21
	.byte	0x1
	.byte	0x1a
	.byte	0x1
	.long	0x57
	.quad	.LFB2
	.quad	.LFE2
	.long	.LLST2
	.long	0x167
	.uleb128 0xc
	.long	.LASF12
	.byte	0x1
	.byte	0x1a
	.long	0x57
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xc
	.long	.LASF13
	.byte	0x1
	.byte	0x1a
	.long	0x167
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x7
	.byte	0x1
	.long	.LASF14
	.byte	0x1
	.byte	0x2a
	.long	0x57
	.byte	0x1
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.byte	0x8
	.long	0x65
	.uleb128 0xd
	.string	"fd"
	.byte	0x1
	.byte	0x7
	.long	0x57
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.string	"fd"
	.byte	0x1
	.byte	0x7
	.long	0x57
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	fd
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LFB0-.Ltext0
	.quad	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI0-.Ltext0
	.quad	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI1-.Ltext0
	.quad	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	.LCFI2-.Ltext0
	.quad	.LFE0-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST1:
	.quad	.LFB1-.Ltext0
	.quad	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI3-.Ltext0
	.quad	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI4-.Ltext0
	.quad	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	.LCFI5-.Ltext0
	.quad	.LFE1-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST2:
	.quad	.LFB2-.Ltext0
	.quad	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI6-.Ltext0
	.quad	.LCFI7-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI7-.Ltext0
	.quad	.LCFI8-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	.LCFI8-.Ltext0
	.quad	.LFE2-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF9:
	.string	"long long int"
.LASF15:
	.string	"GNU C 4.6.1"
.LASF3:
	.string	"unsigned int"
.LASF19:
	.string	"readFromFile"
.LASF21:
	.string	"main"
.LASF12:
	.string	"argc"
.LASF0:
	.string	"long unsigned int"
.LASF8:
	.string	"long long unsigned int"
.LASF10:
	.string	"write"
.LASF20:
	.string	"lseek"
.LASF1:
	.string	"unsigned char"
.LASF7:
	.string	"char"
.LASF18:
	.string	"writeToFile"
.LASF6:
	.string	"long int"
.LASF14:
	.string	"close"
.LASF17:
	.string	"/home/andres/sys_Progs"
.LASF16:
	.string	"sample.c"
.LASF11:
	.string	"read"
.LASF2:
	.string	"short unsigned int"
.LASF4:
	.string	"signed char"
.LASF13:
	.string	"argv"
.LASF5:
	.string	"short int"
	.ident	"GCC: (Ubuntu/Linaro 4.6.1-9ubuntu3) 4.6.1"
	.section	.note.GNU-stack,"",@progbits
