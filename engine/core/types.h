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

