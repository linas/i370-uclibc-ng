#
# Linux i370 ELF ABI _start entry point. Sets up argc, argv, envp
# and the stack, then calls main().
#
# This file takes control of the process from the kernel, as currently
# implemented in linux-2.2.1 arch/i370/kernel/process.c start_thread()
# This is part of gcc, instead of the C library, because issues.
#
# Written by Linas Vepstas, October 2024

	.file    "crt1.s"

	.section .text
	.global _start
	.type   _start,@function
	.align 4
_start:
	BASR r6,0              # Figure out where we are.
	.using .,r6            # Establish addressing

	# TODO:
	# zero out .bss
	# LA r7, _edata
	# LA r8, _end
	# LA r9, 0
	# .Lzero_bss_loop:
	# ST r9, 0(r7)
	# LA r7, 4(r7)
	# BC ... .Lzero_bss_loop

	# We arrive here with R11 the frame pointer.
	# (Pointing to bottom of stack; stack grows up)
	# We arrive here with r1 holding the stack pointer.
	# (Pointing to the top of stack; the args are there)
	# Store stack pointer at as the first entry in the frame.
	# The C code prolog will load r13 with 0(r11)
	ST      r1, 0(r11)

	# Avoid common confusion from MVS people about R13.
	# The ELF-linked C code will do this in the prolog,
	# but if _init is hand-written assembly, it might not.
	LR      r13, r11

	# Upon entry, most registers contain invalid data, except for
	#
	#    r13         zero
	#    r11         Pointer to frame bottom
	#    r1          Pointer to frame top
	#    r2          Pointer to argc
	#    r3          Value of argv
	#    r4          Value of envp
	#
	# These need to be copied to set up the callees stack.
	#
	# The i370 ELF stackframe looks like this:
	#
	#    0          Page table
	#    4          unused
	#    8          Caller frame pointer
	#    12         Caller r14 (backchain aka link register)
	#    16         Caller r15
	#    20         Caller r0
	#    24         Caller r1
	#    ...
	#    60         Caller r10
	#    64         Callee frame pointer
	#    68         Caller r12
	#    72         Unused
	#    76         Unused
	#    80         Scratch
	#    84         Scratch
	#    88         Arg 0
	#    92         Arg 1
	#    ...
	#
	# Expected signature:
	# void __uClibc_main(int (*main)(int, char **, char **), int argc,
	#          char **argv, void (*app_init)(void), void (*app_fini)(void),
	#          void (*rtld_fini)(void),
	#          void *stack_end attribute_unused) attribute_noreturn;
	#
	L       r9,=A(main)    # Get address of main
	ST      r9,88(,r11)    # Pass main on stack.
	L       r2,0(r2)       # Get value of argc
	ST      r2,92(,r11)    # Pass argc on stack.
	ST      r3,96(,r11)    # Pass argv on stack
#if defined(__UCLIBC_CTOR_DTOR__)
	L       r9,=A(_init)   # Get address of _init()
	L       r10,=A(_fini)
#else
	SLR     r9,r9          # zero
	SLR     r10,r10        # zero
#endif

	ST      r9,100(,r11)   # _init
	ST      r10,104(,r11)  # _fini

	SLR     r9,r9          # zero
	ST      r9,108(,r11)   # rtld_fini
	ST      r9,112(,r11)   # stack_end

	LA      r14,12(,r11)   # Set up link register

	L       r15,=A(__uClibc_main)   # Get address of main()
	BASR    r14,r15        # BASR will write PSW to 12(,r11)

_exit:
	# Brute force when not provided
	LA      r1,1(0,0)      # define __NR_exit 1 in unistd.h
	LR      r5,r15         # Assuming main returned something in r15
	SVC     0

	.drop r6
	.align 4
	.ltorg

# We don't need a function page table ...
#	.align 4
#	.size _start,.-_start
