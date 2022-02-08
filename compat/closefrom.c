/*
 * closefrom.c compatibility shim
 * Public domain
 */

#include <linux/close_range.h>
#include <sys/syscall.h>
#include <limits.h>
#include "unistd.h"

int
closefrom(int lowfd)
{
	return syscall(__NR_close_range, lowfd, INT_MAX, 0);
}
