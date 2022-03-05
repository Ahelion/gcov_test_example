#include <stdio.h>
#include "algo.h"

#define CTEST_MAIN
#define CTEST_SEGFAULT


#include "ctest.h"


CTEST(suite1, test1) {
    uint32_t mylocalVer=2;
    int retVal=-1;
    retVal=Algo_GetVersion(&mylocalVer);
    ASSERT_EQUAL(ALGO_TRUE,retVal);
}

CTEST(suite1, test2) {
    uint32_t* mylocalVer=NULL;
    int retVal=-1;
    retVal=Algo_GetVersion(mylocalVer);
    ASSERT_EQUAL(ALGO_FALSE,retVal);
}

int main(int argc, const char *argv[])
{
    int result = ctest_main(argc, argv);

    return result;
}
