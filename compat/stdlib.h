/*
 * stdlib.h compatibility shim
 * Public domain
 */

#include_next <stdlib.h>

#ifndef CUCOMPAT_STDLIB_H
long long strtonum(const char *nptr, long long minval,
		long long maxval, const char **errstr);
#endif
