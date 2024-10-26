
	.text

/* The implementation here seems to work. Except we ignore
   the arg=1 case for dealing with signals.

   Here's what it's supposed to do:
   -- save regs into jump buffer, given as arg0 88(r13)
	-- if arg1 is 1, then save signals, too.
   -- This is not the usual ELF frame reg save order !? ??

   Out of over-anbundance of caution, all the regs are saved.
   The callee-saved regs do not need to be saved, but I don't
   feel like another marathon debug session, right now.
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


/* Caution: this one might be buggy. */
	.balign 2
.globl __sigsetjmp
	.type __sigsetjmp, @function
__sigsetjmp:
	.using .,r15
	L     r15,88(,r11)      /* Get addr of jump buffer */
	STM   r0,r14,0(r15)     /* Save regs to jump buffer */
	LA    r14,=V(__sigjmp_save)
	BR    r14               /* Jump __sigjmp_save */
	.ltorg
