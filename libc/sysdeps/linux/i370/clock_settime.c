/*
 * clock_settime() for uClibc
 *
 * Copyright (C) 2005 by Peter Kjellerstedt <pkj@axis.com>
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <time.h>
#include <sys/time.h>

#include <stdio.h>

int clock_settime(clockid_t clock_id, const struct timespec* tp)
{
	struct timeval tv;
	int retval = -1;

	if (tp->tv_nsec < 0 || tp->tv_nsec >= 1000000000) {
		errno = EINVAL;
		return -1;
	}

	// kernel 2.2.1 does not have this syscall, but much of uclibc needs
	// it. We can fake it, but not today.
	printf("Warning: Not implemented: i370 clock_settime()\n");
	errno = EPERM;

#ifdef LATER
	switch (clock_id) {
		case CLOCK_REALTIME:
			TIMESPEC_TO_TIMEVAL(&tv, tp);
			retval = settimeofday(&tv, NULL);
			break;

		default:
			errno = EINVAL;
			break;
	}
#endif

	return retval;
}
