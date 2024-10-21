/*
 * clock_gettime() for uClibc
 *
 * Copyright (C) 2003 by Justus Pendleton <uc@ryoohki.net>
 * Copyright (C) 2005 by Peter Kjellerstedt <pkj@axis.com>
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <time.h>
#include <sys/time.h>

#include <stdio.h>

int clock_gettime(clockid_t clock_id, struct timespec* tp)
{
	struct timeval tv;
	int retval = -1;

	// kernel 2.2.1 does not have this syscall, but much of uclibc needs
	// it. We can fake it, but not today.
	printf("Warning: TODO Implement i370 clock_gettime\n");
	errno = EPERM;

#if TODO
	switch (clock_id) {
		case CLOCK_REALTIME:
			/* In Linux, gettimeofday fails only on bad parameter.
			 * We know that here parameter isn't bad.
			 */
			// gettimeofday(&tv, NULL);
			TIMEVAL_TO_TIMESPEC(&tv, tp);
			retval = 0;
			break;

		default:
			errno = EINVAL;
			break;
	}
#endif

	return retval;
}
