/*
 * Licensed under the LGPL v2.1 or later, see the file COPYING.LIB
 * in this tarball.
 */

#ifndef __ASM_I370_POSIX_TYPES_H
#define __ASM_I370_POSIX_TYPES_H

/*
 * This file is generally used by user-level software, so you need to
 * be a little careful about namespace pollution etc.  Also, we cannot
 * assume GCC is being used.
 */

typedef unsigned int	__kernel_dev_t;
typedef unsigned int	__kernel_ino_t;
typedef unsigned int	__kernel_mode_t;
typedef unsigned short	__kernel_nlink_t;
typedef long		__kernel_off_t;
typedef int		__kernel_pid_t;
typedef unsigned int	__kernel_uid_t;
typedef unsigned int	__kernel_gid_t;
typedef unsigned long	__kernel_size_t;
typedef long		__kernel_ssize_t;
typedef long		__kernel_ptrdiff_t;
typedef long		__kernel_time_t;
typedef long		__kernel_suseconds_t;
typedef long		__kernel_clock_t;
typedef int		__kernel_daddr_t;
typedef char *		__kernel_caddr_t;
typedef short           __kernel_ipc_pid_t;

#ifdef __GNUC__
typedef long long	__kernel_loff_t;
#endif

typedef struct {
	int	val[2];
} __kernel_fsid_t;

#endif
