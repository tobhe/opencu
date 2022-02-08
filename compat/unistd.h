/*
 * unistd.h compatibility shim
 * Public domain
 */

#include_next <unistd.h>

#ifndef CUCOMPAT_UNISTD_H
#define CUCOMPAT_UNISTD_H

int closefrom(int);

#endif
