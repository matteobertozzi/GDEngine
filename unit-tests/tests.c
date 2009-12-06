#include "unittest.h"

extern void test_maths (GDUnitTests *unitTests);

GDUnitTestFunc unitTestFuncs[] = {
     test_maths,
     NULL
};
