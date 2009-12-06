#ifndef _GDENGINE_DEBUG_
#define _GDENGINE_DEBUG_

void __gdWarningSysFail (const char *file, unsigned int line, const char *func,
                         const char *format, ...);

#define gdWarningSysFail(format, ...)                   \
    do {                                                \
        __gdWarningSysFail(__FILE__, __LINE__,          \
                           __PRETTY_FUNCTION__,         \
                           format, __VA_ARGS__);        \
    } while (0)

#define GD_ASSERT(expr, format, ...)        \
    do {                                    \
    } while (0)

#endif /* !_GDENGINE_DEBUG_ */

