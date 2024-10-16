
	.text

/* The implementation here is wrong.
   Here's what we actually need to do:
   -- restore regs from jump buffer, given as arg0 88(r13)
   -- This is not the usual ELF frame reg save order !? ??

   The "implementation" below is wrong; its just enough to build.
 */
	.balign 2
.globl __longjmp
	.type __longjmp, @function
__longjmp:
	L     r15,88(r13)       /* Get addr of jump buffer */
	LM    r0,r14,0(r15)     /* Save regs to jump buffer */
	L     r15,60(,r15)      /* Get return code */
	BR    r14               /* Return to caller */
