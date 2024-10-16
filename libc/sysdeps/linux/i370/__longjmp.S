
	.text

/* The implementation here seems to work ... sort-of.  */
	.balign 2
.globl __longjmp
	.type __longjmp, @function
__longjmp:
	L     r6,92(r11)        /* Get return code. */
	L     r15,88(r11)       /* Get addr of jump buffer */
	ST    r6,60(r15)        /* Get return code. */
	LM    r0,r14,0(r15)     /* Restore regs from jump buffer */
	L     r15,60(,r15)      /* Get return code */
	BR    r14               /* Return to caller */

libc_hidden_def(__longjmp)
