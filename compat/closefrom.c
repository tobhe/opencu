/*
 * Copyright (c) 2004-2005, 2007, 2010, 2012-2015, 2017-2022
 *	Todd C. Miller <Todd.Miller@sudo.ws>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifdef HAVE_LINUX_CLOSE_RANGE_H
#include <linux/close_range.h>
#endif
#include <sys/syscall.h>
#include <limits.h>
#include "unistd.h"

#ifndef OPEN_MAX
# define OPEN_MAX	256
#endif

#if defined(HAVE_CLOSE_RANGE)
void
closefrom(int lowfd)
{
	close_range(lowfd, ~0U, 0);
}
#else
/*
 * Close all file descriptors greater than or equal to lowfd.
 * This is the expensive (fallback) method.
 */
void
closefrom(int lowfd)
{
	long fd, maxfd;

	/*
	 * Fall back on sysconf(_SC_OPEN_MAX).  This is equivalent to
	 * checking the RLIMIT_NOFILE soft limit.  It is possible for
	 * there to be open file descriptors past this limit but there's
	 * not much we can do about that since the hard limit may be
	 * RLIM_INFINITY (LLONG_MAX or ULLONG_MAX on modern systems).
	 */
	maxfd = sysconf(_SC_OPEN_MAX);
	if (maxfd < OPEN_MAX)
		maxfd = OPEN_MAX;

	/* Make sure we didn't get RLIM_INFINITY as the upper limit. */
	if (maxfd > INT_MAX)
		maxfd = INT_MAX;

	for (fd = lowfd; fd < maxfd; fd++) {
		(void)close((int)fd);
	}
}
#endif
