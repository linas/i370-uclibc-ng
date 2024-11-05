# Stub. Does nothing yet.
#
   .text
   .balign 4
   .type _dl_linux_resolve, @function
_dl_linux_resolve:
# Function prologue
# extern int _dl_linux_resolve(void);
   .balign 2
   STM   r13,r12,8(r11)
   LR r13,r11
   BASR  r3,0
   .using   .,r3
# Function code
# Nothing here right now.
# Function epilogue
   L  r14,12(,r13)
   LM r2,r12,28(r13)
   L  r13,8(,r13)
   BASR  r1,r14
# Function literal pool
   .balign  4
   .ltorg
   .balign  4
   .size _dl_linux_resolve, .-_dl_linux_resolve
