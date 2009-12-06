#ifndef _GDENGINE_UNIT_TEST_H_
#define _GDENGINE_UNIT_TEST_H_

#include <GDEngine/Types.h>

typedef struct {
    GDUInt numberOfFailed;
} GDUnitTests;

typedef void (*GDUnitTestFunc) (GDUnitTests *unitTests);

void _gdUnitTestAssert (GDUnitTests *unitTest,
                        const char *file,
                        unsigned int line,
                        const char *func,
                        const char *expr,
                        int expr_result,
                        const char *format,
                        ...);

#define gdUnitTestAssert(unitTest, expr, format, ...)                   \
    do {                                                                \
        if ((expr)) break;                                              \
        _gdUnitTestAssert(unitTest,                                     \
                          __FILE__, __LINE__,                           \
                          __PRETTY_FUNCTION__,                          \
                          #expr,                                        \
                          (expr),                                       \
                          format, __VA_ARGS__);                         \
    } while (0)

#endif /* !_GDENGINE_UNIT_TEST_H_ */

