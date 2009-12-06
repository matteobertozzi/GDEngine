#ifndef _GDENGINE_TYPES_H_
#define _GDENGINE_TYPES_H_

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef uint64_t    GDUInt64;
typedef uint32_t    GDUInt32;
typedef uint16_t    GDUInt16;
typedef uint8_t     GDUInt8;

typedef int64_t     GDInt64;
typedef int32_t     GDInt32;
typedef int16_t     GDInt16;
typedef int8_t      GDInt8;

typedef void        GDVoid;
typedef uint8_t     GDByte;
typedef uint32_t    GDUInt;
typedef int32_t     GDInt;

typedef double      GDDouble;
typedef float       GDFloat;

#define GD_FALSE        (0)
#define GD_TRUE         (1)
typedef uint8_t     GDBool;

#define gdBool(p)           ((GDBool *)(p))
#define gdBoolValue(p)      (*gdBool(p))

typedef void (*GDReleaseFunc) (void *ptr);

#endif /* !_GDENGINE_TYPES_H_ */

