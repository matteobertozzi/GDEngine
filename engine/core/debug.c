#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>

#include "debug.h"

void __gdWarningSysFail (const char *file, unsigned int line, const char *func,
                         const char *format, ...)
{
    va_list arg_list;

    fprintf(stderr, "%s %u: %s - ", file, line, func);

    va_start(arg_list, format);
    vfprintf(stderr, format, arg_list);
    va_end(arg_list);

    fprintf(stderr, ": %s\n", strerror(errno));
}

