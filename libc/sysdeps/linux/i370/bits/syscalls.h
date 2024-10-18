/* Copyright (C) 2011-2018 Free Software Foundation, Inc.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _BITS_SYSCALLS_H
#define _BITS_SYSCALLS_H
#ifndef _SYSCALL_H
# error "Never use <bits/syscalls.h> directly; include <sys/syscall.h> instead."
#endif

/* Define a macro which expands inline into the wrapper code for a system
   call.  */
# undef INLINE_SYSCALL
# define INLINE_SYSCALL(name, nr, args...)                              \
  ({                                                                    \
    unsigned long _sc_val = INTERNAL_SYSCALL (name, _unused, nr, args); \
    if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P (_sc_val, _unused), 0)) \
    {                                                                   \
      __set_errno (INTERNAL_SYSCALL_ERRNO (_sc_val, _unused));          \
      _sc_val = -1;                                                     \
    }                                                                   \
    (long) _sc_val;                                                     \
  })

#undef INTERNAL_SYSCALL
#define INTERNAL_SYSCALL(name, unused, nr, args...)        \
  internal_syscall##nr (SYS_ify (name), unused, args)

#undef INTERNAL_SYSCALL_NCS
#define INTERNAL_SYSCALL_NCS(number, unused, nr, args...)  \
  internal_syscall##nr (number, unused, args)

#undef INTERNAL_SYSCALL_DECL
#define INTERNAL_SYSCALL_DECL(err)

#undef INTERNAL_SYSCALL_ERROR_P
#define INTERNAL_SYSCALL_ERROR_P(val, unused) ((val) != 0)

#undef INTERNAL_SYSCALL_ERRNO
#define INTERNAL_SYSCALL_ERRNO(val, unused) (-(val))

#define internal_syscall0(num, err, dummy...)                           \
  ({                                                                    \
    unsigned long __sc_ret;                                             \
    register unsigned long __reg_1 __asm__ ("r1");                      \
    register unsigned long __reg_15 __asm__ ("r15") = 0;                \
                                                                        \
    __reg_1 = num;                                                      \
    __asm__ __volatile__ (                                              \
      "   SVC   0"                                                      \
      : "=&r" (__reg_15), "=&r" (__reg_1)                               \
      : "0"   (__reg_15), "1"   (__reg_1)                               \
      );                                                                \
    __sc_ret = __reg_15;                                                \
  })

#define internal_syscall1(num, err, arg1)                               \
  ({                                                                    \
    unsigned long __sc_ret;                                             \
    register unsigned long __reg_1 __asm__ ("r1");                      \
    register unsigned long __reg_5 __asm__ ("r5");                      \
    register unsigned long __reg_15 __asm__ ("r15") = 0;                \
                                                                        \
    __reg_1 = num;                                                      \
    __reg_5 = (unsigned long) (arg1);                                   \
    __asm__ __volatile__ (                                              \
      "   SVC   0"                                                      \
      : "=&r" (__reg_15), "=&r" (__reg_1)                               \
      : "0"   (__reg_15), "1"   (__reg_1),                              \
        "r"   (__reg_5)                                                 \
      );                                                                \
    __sc_ret = __reg_15;                                                \
  })

#define internal_syscall2(num, err, arg1, arg2)                         \
  ({                                                                    \
    unsigned long __sc_ret;                                             \
    register unsigned long __reg_1 __asm__ ("r1");                      \
    register unsigned long __reg_5 __asm__ ("r5");                      \
    register unsigned long __reg_6 __asm__ ("r6");                      \
    register unsigned long __reg_15 __asm__ ("r15") = 0;                \
                                                                        \
    __reg_1 = num;                                                      \
    __reg_5 = (unsigned long) (arg1);                                   \
    __reg_6 = (unsigned long) (arg2);                                   \
    __asm__ __volatile__ (                                              \
      "   SVC   0"                                                      \
      : "=&r" (__reg_15), "=&r" (__reg_1)                               \
      : "0"   (__reg_15), "1"   (__reg_1),                              \
        "r"   (__reg_5),                                                \
        "r"   (__reg_6)                                                 \
      );                                                                \
    __sc_ret = __reg_15;                                                \
  })

#define internal_syscall3(num, err, arg1, arg2, arg3)                   \
  ({                                                                    \
    unsigned long __sc_ret;                                             \
    register unsigned long __reg_1 __asm__ ("r1");                      \
    register unsigned long __reg_5 __asm__ ("r5");                      \
    register unsigned long __reg_6 __asm__ ("r6");                      \
    register unsigned long __reg_7 __asm__ ("r7");                      \
    register unsigned long __reg_15 __asm__ ("r15") = 0;                \
                                                                        \
    __reg_1 = num;                                                      \
    __reg_5 = (unsigned long) (arg1);                                   \
    __reg_6 = (unsigned long) (arg2);                                   \
    __reg_7 = (unsigned long) (arg3);                                   \
    __asm__ __volatile__ (                                              \
      "   SVC   0"                                                      \
      : "=&r" (__reg_15), "=&r" (__reg_1)                               \
      : "0"   (__reg_15), "1"   (__reg_1),                              \
        "r"   (__reg_5),                                                \
        "r"   (__reg_6),                                                \
        "r"   (__reg_7)                                                 \
      );                                                                \
    __sc_ret = __reg_15;                                                \
  })

#define internal_syscall4(num, err, arg1, arg2, arg3, arg4)             \
  ({                                                                    \
    unsigned long __sc_ret;                                             \
    register unsigned long __reg_1 __asm__ ("r1");                      \
    register unsigned long __reg_5 __asm__ ("r5");                      \
    register unsigned long __reg_6 __asm__ ("r6");                      \
    register unsigned long __reg_7 __asm__ ("r7");                      \
    register unsigned long __reg_8 __asm__ ("r8");                      \
    register unsigned long __reg_15 __asm__ ("r15") = 0;                \
                                                                        \
    __reg_1 = num;                                                      \
    __reg_5 = (unsigned long) (arg1);                                   \
    __reg_6 = (unsigned long) (arg2);                                   \
    __reg_7 = (unsigned long) (arg3);                                   \
    __reg_8 = (unsigned long) (arg4);                                   \
    __asm__ __volatile__ (                                              \
      "   SVC   0"                                                      \
      : "=&r" (__reg_15), "=&r" (__reg_1)                               \
      : "0"   (__reg_15), "1"   (__reg_1),                              \
        "r"   (__reg_5),                                                \
        "r"   (__reg_6),                                                \
        "r"   (__reg_7),                                                \
        "r"   (__reg_8)                                                 \
      );                                                                \
    __sc_ret = __reg_15;                                                \
  })

#define internal_syscall5(num, err, arg1, arg2, arg3, arg4, arg5)       \
  ({                                                                    \
    unsigned long __sc_ret;                                             \
    register unsigned long __reg_1 __asm__ ("r1");                      \
    register unsigned long __reg_5 __asm__ ("r5");                      \
    register unsigned long __reg_6 __asm__ ("r6");                      \
    register unsigned long __reg_7 __asm__ ("r7");                      \
    register unsigned long __reg_8 __asm__ ("r8");                      \
    register unsigned long __reg_9 __asm__ ("r9");                      \
    register unsigned long __reg_15 __asm__ ("r15") = 0;                \
                                                                        \
    __reg_1 = num;                                                      \
    __reg_5 = (unsigned long) (arg1);                                   \
    __reg_6 = (unsigned long) (arg2);                                   \
    __reg_7 = (unsigned long) (arg3);                                   \
    __reg_8 = (unsigned long) (arg4);                                   \
    __reg_9 = (unsigned long) (arg5);                                   \
    __asm__ __volatile__ (                                              \
      "   SVC   0"                                                      \
      : "=&r" (__reg_15), "=&r" (__reg_1)                               \
      : "0"   (__reg_15), "1"   (__reg_1),                              \
        "r"   (__reg_5),                                                \
        "r"   (__reg_6),                                                \
        "r"   (__reg_7),                                                \
        "r"   (__reg_8),                                                \
        "r"   (__reg_9)                                                 \
      );                                                                \
    __sc_ret = __reg_15;                                                \
  })

#define internal_syscall6(num, err, arg1, arg2, arg3, arg4, arg5, arg6) \
  ({                                                                    \
    unsigned long __sc_ret;                                             \
    register unsigned long __reg_1 __asm__ ("r1");                      \
    register unsigned long __reg_5 __asm__ ("r5");                      \
    register unsigned long __reg_6 __asm__ ("r6");                      \
    register unsigned long __reg_7 __asm__ ("r7");                      \
    register unsigned long __reg_8 __asm__ ("r8");                      \
    register unsigned long __reg_9 __asm__ ("r9");                      \
    register unsigned long __reg_10 __asm__ ("r10");                    \
    register unsigned long __reg_15 __asm__ ("r15") = 0;                \
                                                                        \
    __reg_1 = num;                                                      \
    __reg_5 = (unsigned long) (arg1);                                   \
    __reg_6 = (unsigned long) (arg2);                                   \
    __reg_7 = (unsigned long) (arg3);                                   \
    __reg_8 = (unsigned long) (arg4);                                   \
    __reg_9 = (unsigned long) (arg5);                                   \
    __reg_10 = (unsigned long) (arg6);                                  \
    __asm__ __volatile__ (                                              \
      "   SVC   0"                                                      \
      : "=&r" (__reg_15), "=&r" (__reg_1)                               \
      : "0"   (__reg_15), "1"   (__reg_1),                              \
        "r"   (__reg_5),                                                \
        "r"   (__reg_6),                                                \
        "r"   (__reg_7),                                                \
        "r"   (__reg_8),                                                \
        "r"   (__reg_9),                                                \
        "r"   (__reg_10)                                                \
      );                                                                \
    __sc_ret = __reg_15;                                                \
  })

#endif
