#include <stdio.h>
#include <stdint.h>
#include "algo.h"

int main(void)
{
    uint32_t lver;
    (void)Algo_GetVersion(&lver);
    return 0;
}