#include "object.h"
#include "alloc.h"

GDType *__gdTypeInit (unsigned int size, void *object) {
    GDBool internalAlloc = (object == NULL);
    GDType *base = gdObject(object);

    if (object == NULL)
        base = (GDType *) gdAllocArray(GDByte, size);

    base->internalAlloc = internalAlloc;
    base->retainCount = 1;

    return(base);
}

GDType *_gdObjectRetain (GDType *object) {
    object->retainCount++;
    return(object);
}

GDBool _gdObjectRelease (GDType *object) {
    return((--(object->retainCount)) == 0);
}

GDUInt gdObjectRetainCount (GDType *type) {
    return(type->retainCount);
}

