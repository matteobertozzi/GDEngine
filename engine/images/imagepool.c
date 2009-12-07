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

#include "imagepool.h"
#include "macros.h"
#include "debug.h"
#include "list.h"

/* Internal Image Pool List */
static GDList *__imagePool = NULL;

static GDList *_gdImagePool (void) {
    if (__imagePool == NULL)
        __imagePool = gdListAlloc();
    return(__imagePool);
}

GDImage *gdImagePoolFind (const char *filename) {
    GDImage *image;
    GDList *pool;
    GDUInt i, n;

    pool = _gdImagePool();
    GD_ASSERT(format != NULL, "Image Pool Unable to Initialize");

    for (i = 0, n = gdListSize(pool); i < n; ++i) {
        if ((image = gdImage(gdListAt(pool, i))) == NULL)
            continue;

        if (!strcmp(filename, image->name))
            return(image);
    }

    return(NULL);
}

GDImage *gdImagePoolAdd (GDImage *image) {
    gdReturnValueIfNull(image, NULL);

    if (!gdListAppend(_gdImagePool(), image)) {
        /* TODO: Free Image */
        return(NULL);
    }
    return(image);
}

void gdImagePoolRemove (GDImage *image) {
    if (image != NULL)
        gdListRemove(_gdImagePool(), image);
}


