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

#ifndef _GDENGINE_MATHS_H_
#define _GDENGINE_MATHS_H_

#include <math.h>

#define GD_MATH_EPSILON                 (0.0000001f)
#define GD_MATH_E                       (2.71828182845904523546f) /* e    */                                         
#define GD_MATH_PI                      (3.14159265358979323846f) /* pi   */
#define GD_MATH_PI2                     (6.28318548202514648438f) /* 2*pi */
#define GD_MATH_PI_2                    (1.57079632679489661923f) /* pi/2 */
#define GD_MATH_PI_4                    (0.78539816339744830962f) /* pi/4 */
#define GD_MATH_1_PI                    (0.31830988618379067154f) /* 1/pi */

#define gdMathRadToDeg(r)               ((r) * 57.29577951308232087679f)
#define gdMathDegToRad(d)               ((d) * 0.017453292519943295769f)

#define gdMathIsZero(x)                 (fabs(x) < GD_MATH_EPSILON)
#define gdMathEqual(a, b)               gdMathIsZero((a) - (b))

#define gdMathAbs                       fabs
#define gdMathRound                     roundf
#define gdMathMin(a, b)                 (((a) < (b)) ? (a) : (b))
#define gdMathMax(a, b)                 (((a) > (b)) ? (a) : (b))

#define gdMathWrap(x, y)                ((x) - ((y) * gdMathRound(x / y)))
#define gdMathWrapDegAngle(d)           gdMathWrap((d), 360.0f)
#define gdMathWrapRadAngle(r)           gdMathWrap((r), GD_MATH_PI2)

#define gdMathLerp(v1, v2, amount)      ((v1) + ((v2) - (v1)) * (amount))

#define gdMathBound(min, val, max)      gdMathMax(min, gdMathMax(max, val))

#define gdMathSin                       sinf
#define gdMathCos                       cosf
#define gdMathTan                       tanf
#define gdMathAsin                      asinf
#define gdMathAcos                      acosf
#define gdMathAtan                      atanf
#define gdMathAtan2                     atan2f

#define gdPow2(x)                       ((x) * (x))
#define gdPow3(x)                       ((x) * (x) * (x))
#define gdMathPow                       powf
#define gdMathPow2(x)                   powf((x), 2)
#define gdMathPow3(x)                   powf((x), 3)

#define gdMathCube                      gdPow3
#define gdMathSquared                   gdPow2

#define gdMathExp                       expf
#define gdMathExp10                     exp10f

#define gdMathSqrt                      sqrtf

#define gdMathLog                       logf
#define gdMathLog10                     log10f

#define gdMathHermite(v1, t1, v2, t2, amount)                              \
    (((amount) == 0.0f) ? (v1) : ((amount) == 1.0f) ? (v2) :               \
      (2.0f*(v1) - 2.0f*(v2) + (t2) + (t1)) * gdMathCube(amount) +         \
      (3.0f*(v2) - 3.0f*(v1) - 2.0f*(t1) - (t2)) * gdMathSquared(amount) + \
      (t1) * (amount) + (v1))

#define gdMathSmooth(v1, v2, amount)                                       \
    gdMathHermite(v1, 0.0f, v2, 0.0f, gdMathClamp(amount, 0.0f, 0.1f))

#endif /* !_GDENGINE_MATHS_H_ */

