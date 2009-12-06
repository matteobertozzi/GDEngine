#ifndef _GDENGINE_ENDIAN_H_
#define _GDENGINE_ENDIAN_H_

#include <stdint.h>

#include <GDEngine/Macros.h>

#define gdOctave(x, n)        (((x) >> (8 * (n))) & 0xff)
#define __gdSwap16(x)         ((gdOctave(x, 0) << 8) +      \
                               (gdOctave(x, 1) << 0))
#define __gdSwap32(x)         ((gdOctave(x, 0) << 24) +     \
                               (gdOctave(x, 1) << 16) +     \
                               (gdOctave(x, 2) << 8) +      \
                               (gdOctave(x, 3) << 0))
#define __gdSwap64(x)         ((gdOctave(x, 0) << 56) +     \
                               (gdOctave(x, 1) << 48) +     \
                               (gdOctave(x, 2) << 40) +     \
                               (gdOctave(x, 3) << 32) +     \
                               (gdOctave(x, 4) << 24) +     \
                               (gdOctave(x, 5) << 16) +     \
                               (gdOctave(x, 6) << 8) +      \
                               (gdOctave(x, 7) << 0))

#define gdSwap16(x)           ((uint16_t)__gdSwap16((uint16_t)(x)))
#define gdSwap32(x)           ((uint32_t)__gdSwap32((uint32_t)(x)))
#define gdSwap64(x)           ((uint64_t)__gdSwap64((uint64_t)(x)))

#if defined(GD_PLATFORM_BIG_ENDIAN)
    #define gdHostToLittle16(x)        gdSwap16(x)
    #define gdHostToLittle32(x)        gdSwap32(x)
    #define gdHostToLittle64(x)        gdSwap64(x)
    
    #define gdLittle16ToHost(x)        gdSwap16(x)
    #define gdLittle32ToHost(x)        gdSwap32(x)
    #define gdLittle64ToHost(x)        gdSwap64(x)

    #define gdHostToBig16(x)           (x)
    #define gdHostToBig32(x)           (x)
    #define gdHostToBig64(x)           (x)
    
    #define gdBig16ToHost(x)           (x)
    #define gdBig32ToHost(x)           (x)
    #define gdBig64ToHost(x)           (x)
#elif defined(GD_PLATFORM_LITTLE_ENDIAN)
    #define gdHostToLittle16(x)        (x)
    #define gdHostToLittle32(x)        (x)
    #define gdHostToLittle64(x)        (x)
    
    #define gdLittle16ToHost(x)        (x)
    #define gdLittle32ToHost(x)        (x)
    #define gdLittle64ToHost(x)        (x)
    
    #define gdHostToBig16(x)           gdSwap16(x)
    #define gdHostToBig32(x)           gdSwap32(x)
    #define gdHostToBig64(x)           gdSwap64(x)
    
    #define gdBig16ToHost(x)           gdSwap16(x)
    #define gdBig32ToHost(x)           gdSwap32(x)
    #define gdBig64ToHost(x)           gdSwap64(x)
#else
    #warning "GDEngine Platform Endianness not defined."
#endif

#endif /* !_GDENGINE_ENDIAN_H_ */

