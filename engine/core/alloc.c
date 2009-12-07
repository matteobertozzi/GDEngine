/*
 * Copyright (c) 2009, Matteo Bertozzi <theo.bertozzi@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Matteo Bertozzi nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Matteo Bertozzi ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Matteo Bertozzi BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

