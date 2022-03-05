#include <stdio.h>
#include <stdint.h>
#include "algo.h"

int Algo_GetVersion(uint32_t *ver)
{
    int retVal=0;
    if(ver==NULL)
    {
        retVal=ALGO_FALSE;
    }
    else
    {
        *ver=ALGO_VER;
        retVal=ALGO_TRUE;
    }

    return retVal;
}