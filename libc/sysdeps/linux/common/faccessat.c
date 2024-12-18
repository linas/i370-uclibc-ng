/*
 * faccessat() for uClibc
 *
 * Copyright (C) 2009 Analog Devices Inc.
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>

#ifdef __NR_faccessat
_syscall4(int, faccessat, int, fd, const char *, file, int, type, int, flag)
libc_hidden_def(faccessat)
#else
/* should add emulation with faccess() and /proc/self/fd/ ... */

/* For i370, there's no __NR_faccessat so I'm going to fake it.
   At this time, the only caller is euidaccess() used by the dynamic
   loader (to see if the app can be run) Its called with AT_FDCWD.
   I'm gonna ignore the issues here.
 */
int faccessat(int fd, const char * file, int type, int flag)
{
  return access(file, type);
}
libc_hidden_def(faccessat)

#endif
