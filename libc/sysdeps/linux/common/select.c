/*
 * select() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/select.h>
#include <cancel.h>

#ifdef __NR__newselect
# undef __NR_select
# define __NR_select __NR__newselect
#endif

#if defined(__NR_pselect6) || defined(__NR_pselect6_time64)
# include <stdint.h>
# define USEC_PER_SEC 1000000L
#endif

#if defined(__UCLIBC_USE_TIME64__)
#include "internal/time64_helpers.h"
#endif

int __NC(select)(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		 struct timeval *timeout)
{
	struct timespec _ts, *ts = 0;
#if defined(__NR_pselect6) || defined(__NR_pselect6_time64)
	if (timeout) {
		uint32_t usec;
		_ts.tv_sec = timeout->tv_sec;

		/* GNU extension: allow for timespec values where the sub-sec
		* field is equal to or more than 1 second.  The kernel will
		* reject this on us, so take care of the time shift ourself.
		* Some applications (like readline and linphone) do this.
		* See 'clarification on select() type calls and invalid timeouts'
		* on the POSIX general list for more information.
		*/
		usec = timeout->tv_usec;
		if (usec >= USEC_PER_SEC) {
			_ts.tv_sec += usec / USEC_PER_SEC;
			usec %= USEC_PER_SEC;
		}
		_ts.tv_nsec = usec * 1000;

		ts = &_ts;
	}
#if defined(__UCLIBC_USE_TIME64__) && defined(__NR_pselect6_time64)
	return INLINE_SYSCALL(pselect6_time64, 6, n, readfds, writefds, exceptfds, TO_TS64_P(ts), 0);
#else
	return INLINE_SYSCALL(pselect6, 6, n, readfds, writefds, exceptfds, ts, 0);
#endif
#elif defined(__NR_select)
	return INLINE_SYSCALL(select, 5, n, readfds, writefds, exceptfds, ts);
#endif
}
/* we should guard it, but we need it in other files, so let it fail
 * if we miss any of the syscalls */
#if 1 /*defined __NR_select || defined __NR_pselect6*/
CANCELLABLE_SYSCALL(int, select, (int n, fd_set *readfds, fd_set *writefds,
				  fd_set *exceptfds, struct timeval *timeout),
		    (n, readfds, writefds, exceptfds, timeout))
lt_libc_hidden(select)
#endif
