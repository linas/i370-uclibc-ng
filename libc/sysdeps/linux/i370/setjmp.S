
	.text

/* The implementation here barely kind-of works. It's under-designed.
   Here's what we actually need to do:
   -- save regs into jump buffer, given as arg0 88(r13)
	-- if arg1 is 1, then save signals, too.
   -- This is not the usual ELF frame reg save order !? ??
 */
	.balign 2
.globl setjmp
	.type setjmp, @function
setjmp:
	L     r15,88(r11)       /* Get addr of jump buffer */
	STM   r0,r14,0(r15)     /* Save regs to jump buffer */
	LA    r15,0(,0)         /* Return success */
	BR    r14               /* Return to caller */

	.balign 2
.globl _setjmp
	.type _setjmp, @function
_setjmp:
	L     r15,88(,r11)      /* Get addr of jump buffer */
	STM   r0,r14,0(r15)     /* Save regs to jump buffer */
	LA    r15,0(,0)         /* Return success */
	BR    r14               /* Return to caller */
