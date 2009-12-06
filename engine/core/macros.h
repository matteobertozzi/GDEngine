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

