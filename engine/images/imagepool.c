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


