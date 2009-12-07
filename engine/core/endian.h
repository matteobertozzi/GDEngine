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

