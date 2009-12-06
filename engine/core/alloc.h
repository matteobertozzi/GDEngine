#ifndef _GDENGINE_ALLOC_H_
#define _GDENGINE_ALLOC_H_

void *__gdAlloc  (const char *file, unsigned int line, const char *func,
                  unsigned int size);
void *__gdZAlloc (const char *file, unsigned int line, const char *func,
                  unsigned int size);

#define gdAlloc(type)                            \
    ((type *) __gdAlloc(__FILE__, __LINE__,      \
                        __PRETTY_FUNCTION__,     \
                        sizeof(type)))

#define gdZAlloc(type)                           \
    ((type *) __gdZAlloc(__FILE__, __LINE__,     \
                         __PRETTY_FUNCTION__,    \
                         sizeof(type)))

#define gdAllocArray(type, n)                   \
    ((type *) __gdAlloc(__FILE__, __LINE__,     \
                        __PRETTY_FUNCTION__,    \
                        (n) * sizeof(type)))

#define gdZAllocArray(type, n)                  \
    ((type *) __gdZAlloc(__FILE__, __LINE__,    \
                         __PRETTY_FUNCTION__,   \
                         (n) * sizeof(type)))

#define gdFree(ptr)                             \
    free(ptr)

#define gdZFree(pptr)                           \
    do {                                        \
        free(*(pptr));                          \
        *(pptr) = NULL;                         \
    } while (0)

#endif /* !_GDENGINE_ALLOC_H_ */

