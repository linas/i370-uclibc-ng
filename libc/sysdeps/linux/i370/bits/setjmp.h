/*
 * Licensed under the LGPL v2.1 or later, see the file COPYING.LIB
 * in this tarball.
 */

#ifndef _BITS_SETJMP_H
#define _BITS_SETJMP_H	1

#if !defined _SETJMP_H  && !defined _PTHREAD_H
# error "Never include <bits/setjmp.h> directly; use <setjmp.h> instead."
#endif

typedef struct
{
  /* Top-of-stack pointer, r11 for the ELF ABI */
  unsigned long __sp;

  /* Return address; from r14 the link register from BASR */
  unsigned long __link;

  /* Callee-saved registers ... uh all for now.  */
  unsigned long __regs[16];
} __jmp_buf[1];

#endif /* _BITS_SETJMP_H */
