#include <stdio.h>
#include <stdint.h>
#include "algo.h"

int main(void)
{
    uint32_t lver;
    uint8_t localString[] = "This String is for demo";
    uint8_t localStringOut[100];
    uint16_t size = 0;
    (void)Algo_GetVersion(&lver);
    Algo_SetPointerToString(&localString[0]);
    Algo_Compute();
    //call 4 times
    Algo_MainFuncion();
    Algo_MainFuncion();
    Algo_MainFuncion();
    Algo_MainFuncion();

    Algo_GetResultToString(&localStringOut[0],&size);
    uint32_t ii = 0;
    printf("%c", localStringOut[0]);
    printf("%c", localStringOut[1]);
    for (ii = 2; ii < size; ii++)
    {
        printf("%02x", localStringOut[ii]);
    }
    printf("\n");
    return 0;
}