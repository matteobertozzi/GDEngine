#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "unittest.h"
#include <GDEngine/Macros.h>

extern GDUnitTestFunc unitTestFuncs[];

void _gdUnitTestAssert (GDUnitTests *unitTest,
                        const char *file,
                        unsigned int line,
                        const char *func,
                        const char *expr,
                        int expr_result,
                        const char *format,
                        ...)
{
    va_list arg_list;

    fprintf(stderr, "%s %u: %s - (%s == %d)\n - ", file, line, func, 
                                                   expr, expr_result);

    va_start(arg_list, format);
    vfprintf(stderr, format, arg_list);
    va_end(arg_list);

    unitTest->numberOfFailed++;
}

int main (int argc, char **argv) {
    GDUnitTests unitTests;
    int exit_status = 0;
    unsigned int i;

    printf("GDEngine Library Unit Tests:\n");

    /* Initialize Test Informations */
    unitTests.numberOfFailed = 0;

    /* Run all tests. */
    for (i = 0; unitTestFuncs[i] != NULL; ++i)
        unitTestFuncs[i](&unitTests);

    printf("[-] Test Passed %u/%u\n", i - unitTests.numberOfFailed, i);

    return(exit_status);
}

