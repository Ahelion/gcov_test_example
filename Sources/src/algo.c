#include <stdio.h>
#include <stdint.h>
#include "algo.h"

int Algo_GetVersion(uint32_t *ver)
{
    *ver = 32;

    printf("called\n");

    return ALGO_TRUE;
}