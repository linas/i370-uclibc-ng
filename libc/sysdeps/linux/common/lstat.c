/*
 * lstat() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <sys/stat.h>
#include <bits/uClibc_arch_features.h>

#if defined __NR_fstatat64 && !defined __NR_lstat && !defined(__UCLIBC_USE_TIME64__)
# include <fcntl.h>

int lstat(const char *file_name, struct stat *buf)
{
	return fstatat(AT_FDCWD, file_name, buf, AT_SYMLINK_NOFOLLOW);
}
libc_hidden_def(lstat)

#elif __WORDSIZE == 64 && defined __NR_newfstatat
# include <fcntl.h>

int lstat(const char *file_name, struct stat *buf)
{
	return fstatat(AT_FDCWD, file_name, buf, AT_SYMLINK_NOFOLLOW);
}
libc_hidden_def(lstat)

#elif defined __NR_statx && defined __UCLIBC_HAVE_STATX__
# include <fcntl.h>
# include <statx_cp.h>

int lstat(const char *file_name, struct stat *buf)
{
      struct statx tmp;
      int rc = INLINE_SYSCALL (statx, 5, AT_FDCWD, file_name,
                               AT_NO_AUTOMOUNT | AT_SYMLINK_NOFOLLOW,
                               STATX_BASIC_STATS, &tmp);
      if (rc == 0)
        __cp_stat_statx ((struct stat *)buf, &tmp);

      return rc;
}
libc_hidden_def(lstat)

/* For systems which have both, prefer the old one */
#else
# include "xstatconv.h"
int lstat(const char *file_name, struct stat *buf)
{
	int result;
# ifdef __NR_lstat64
	/* normal stat call has limited values for various stat elements
	 * e.g. uid device major/minor etc.
	 * so we use 64 variant if available
	 * in order to get newer versions of stat elements
	 */
	struct kernel_stat64 kbuf;
	result = INLINE_SYSCALL(lstat64, 2, file_name, &kbuf);
	if (result == 0) {
		__xstat32_conv(&kbuf, buf);
	}
# else
	struct kernel_stat kbuf;

	result = INLINE_SYSCALL(lstat, 2, file_name, &kbuf);
	if (result == 0) {
		__xstat_conv(&kbuf, buf);
	}
# endif /* __NR_lstat64 */
	return result;
}
libc_hidden_def(lstat)

/* Convert between the kernel's `struct stat' format, and libc's.
   This is needed for i370, and I can't figure out how to force the
   needed build, so I brute-force copied it. WTF, It works.  */

#include <sys/stat.h>
#include <string.h>
#include "xstatconv.h"

void __xstat_conv(struct kernel_stat *kbuf, struct stat *buf)
{
	/* Convert to current kernel version of `struct stat'. */
	memset(buf, 0x00, sizeof(*buf));
	buf->st_dev = kbuf->st_dev;
	buf->st_ino = kbuf->st_ino;
	buf->st_mode = kbuf->st_mode;
	buf->st_nlink = kbuf->st_nlink;
	buf->st_uid = kbuf->st_uid;
	buf->st_gid = kbuf->st_gid;
	buf->st_rdev = kbuf->st_rdev;
	buf->st_size = kbuf->st_size;
	buf->st_blksize = kbuf->st_blksize;
	buf->st_blocks = kbuf->st_blocks;
	buf->st_atim.tv_sec = kbuf->st_atim.tv_sec;
	buf->st_atim.tv_nsec = kbuf->st_atim.tv_nsec;
	buf->st_mtim.tv_sec = kbuf->st_mtim.tv_sec;
	buf->st_mtim.tv_nsec = kbuf->st_mtim.tv_nsec;
	buf->st_ctim.tv_sec = kbuf->st_ctim.tv_sec;
	buf->st_ctim.tv_nsec = kbuf->st_ctim.tv_nsec;
}

# if ! defined __NR_fstatat64 && ! defined __NR_lstat64 && ! defined __UCLIBC_HAS_STATX__
strong_alias_untyped(lstat,lstat64)
libc_hidden_def(lstat64)
# endif

#endif /* __NR_fstatat64 */
