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

#ifndef _GDENGINE_MACROS_H_
#define _GDENGINE_MACROS_H_

#if (defined(__i386__) || defined(__x86_64__)) && !defined(__LITTLE_ENDIAN__)
    #define __LITTLE_ENDIAN__ 1
#endif

#if !defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)
    #error Do not know the endianess of this architecture
#endif

#if !__BIG_ENDIAN__ && !__LITTLE_ENDIAN__
    #error Both __BIG_ENDIAN__ and __LITTLE_ENDIAN__ cannot be false
#endif

#if __BIG_ENDIAN__ && __LITTLE_ENDIAN__
    #error Both __BIG_ENDIAN__ and __LITTLE_ENDIAN__ cannot be true
#endif

#if __LITTLE_ENDIAN__
    #define GD_PLATFORM_LITTLE_ENDIAN
#else
    #define GD_PLATFORM_BIG_ENDIAN
#endif

#define gdReturnIfNull(ptr)                   if ((ptr) == NULL) return
#define gdReturnIfTrue(expr)                  if (expr) return
#define gdReturnIfFalse(expr)                 if (!(expr)) return
#define gdReturnValueIfNull(ptr, retval)      if ((ptr) == NULL) return(retval)
#define gdReturnValueIfTrue(expr, retval)     if (expr) return(retval)
#define gdReturnValueIfFalse(expr, retval)    if (!(expr)) return(retval)

#endif /* !_GDENGINE_MACROS_H_ */

