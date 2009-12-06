#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "alloc.h"

/**
 * Internal Method for malloc() with Debug message when error occurs.
 */
void *__gdAlloc (const char *file, unsigned int line, const char *func,
                 unsigned int size)
{
    void *ptr;

    if ((ptr = malloc(size)) == NULL) {
        fprintf(stderr, "%s %u: %s - malloc(%u): %s\n", file, line, func, 
                                                        size, strerror(errno));

#ifdef GD_DEUBG
        abort();
#endif

        return(NULL);
    }

    return(ptr);
}

/**
 * Internal Method for malloc() with Debug message when error occurs.
 * The difference with __gdDataAlloc() is that call memset(p, 0, size)
 * to fill the new buffer with zeros.
 */
void *__gdZAlloc (const char *file, unsigned int line, const char *func,
                  unsigned int size)
{
    void *ptr;

    if ((ptr = malloc(size)) == NULL) {
        fprintf(stderr, "%s %u: %s - malloc(%u): %s\n", file, line, func, 
                                                        size, strerror(errno));

#ifdef GD_DEUBG
        abort();
#endif

        return(NULL);
    }

    return(memset(ptr, 0, size));
}

