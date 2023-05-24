#ifndef _STRUCT_H
#define _STRUCT_H

#ifndef _GNU_SOURCE 
#define _GNU_SOURCE 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>

#define sameString(a, b) (strcmp((a), (b))==0)
void verboseDot();
/* Print "i-am-alive" dot */

long clock1000();

void uglyTime(char *label, ...);
/* Print label and how long it's been since last call.  Call with 
 * a NULL label to initialize. */

FILE *mustOpen(const char *fileName, char *mode);
/* Open a file or die */

void *xmalloc ( int size );
/* Wrapper for memory allocations */

void errAbort(char *format, ...)
/* Print error message to stderr and exit */
     __attribute__((noreturn, format(printf, 1, 2)));

#endif
