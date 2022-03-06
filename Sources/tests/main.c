#include <stdio.h>
#include <stdint.h>
#include "algo.h"

#define CTEST_MAIN
#define CTEST_SEGFAULT


#include "ctest.h"


CTEST(suite1, test1) {
    uint32_t mylocalVer=2;
    int retVal=-1;
    retVal=Algo_GetVersion(&mylocalVer);
    ASSERT_EQUAL(ALGO_TRUE,retVal);
    ASSERT_EQUAL(ALGO_VER,mylocalVer);
}

CTEST(suite1, test2) {
    uint32_t* mylocalVer=NULL;
    int retVal=-1;
    retVal=Algo_GetVersion(mylocalVer);
    ASSERT_EQUAL(ALGO_FALSE,retVal);
}

CTEST(suite1, test3) {
    int retVal;
    retVal = Algo_SetPointerToString(NULL);
    ASSERT_EQUAL(ALGO_FALSE, retVal);
}

int main(int argc, const char *argv[])
{
    int result = ctest_main(argc, argv);

    return result;
}

