#ifndef _GDENGINE_OBJECT_H_
#define _GDENGINE_OBJECT_H_

#include <GDEngine/Types.h>

typedef struct {
    GDBool internalAlloc;
    GDUInt retainCount;
} GDType;

#define GD_OBJECT           GDType _base;
#define gdObject(p)         ((GDType *)(p))

GDType *__gdTypeInit (unsigned int size, void *object);

#define _gdObjectInit(type, obj)      ((type *) __gdTypeInit(sizeof(type), obj))
#define _gdObjectInternalAlloc(obj)   (gdObject(obj)->internalAlloc)
GDType *_gdObjectRetain     (GDType *object);
GDBool  _gdObjectRelease    (GDType *object);

GDUInt  gdObjectRetainCount (GDType *type);

#endif /* !_GDENGINE_OBJECT_H_ */

