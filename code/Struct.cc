#include "Struct.h"
#include <iostream>
using namespace std;

void verboseDot()
/* Print "i-am-alive" dot */
{
	putchar('.');
	fflush(stdout);
}

long clock1000()
/* A millisecond clock. */
{
    struct timeval tv;
    static long origSec;
    gettimeofday(&tv, NULL);
    if (origSec == 0) origSec = tv.tv_sec;
    return (tv.tv_sec-origSec)*1000 + tv.tv_usec / 1000;
}


void uglyTime(char *label, ...)
/* Print label and how long it's been since last call.  Call with 
 * a NULL label to initialize. */
{
    static long lastTime = 0;
    long time = clock1000();
    va_list args;
    va_start(args, label);
    if (label != NULL)
    {
        vfprintf(stdout, label, args);
        fprintf(stdout, " [%.3f seconds elapsed]\n", (time - lastTime)/1000.);
    }
    lastTime = time;
    va_end(args);
}

FILE *mustOpen(const char *fileName, char *mode)
/* Open a file or die */
{
	FILE *f;
	if (sameString(fileName, "stdin")) return stdin;
	if (sameString(fileName, "stdout")) return stdout;
	if ((f = fopen(fileName, mode)) == NULL)
	{
		char *modeName = ((char*)"");
		if (mode)
		{
			if (mode[0] == 'r') modeName = ((char*)" to read");
			else if (mode[0] == 'w') modeName = ((char*)" to write");
			else if (mode[0] == 'a') modeName = ((char*)" to append");
		}
		errAbort(((char*)"Can't open %s%s: %s"), fileName, modeName, strerror(errno));
	}
	return f;
}

void* xmalloc ( int size )
/* Wrapper for standard mallc */
{
	register void* value = malloc(size);
	if (value == NULL)
		errAbort(((char*)"Memory exhausted (xmalloc)"));
	return value;
}

void errAbort(char *format, ...)
/* Print error message and exit */
{
	va_list args;
	va_start(args, format);
	fprintf(stderr, "[Error] ");
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}


