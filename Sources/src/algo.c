#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "algo.h"
/*
    Functionality:
    given a specific string it creates motorola srec:
    https://en.wikipedia.org/wiki/SREC_(file_format)
*/

static uint8_t algo_string_ptr[ALGO_MAX_SIZE_DATA];

static uint8_t* algo_global_string_ptr=NULL;

static algo_srec_t algo_srec_line_st;

static algo_states_t algo_state_en=ALGO_NONE;

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

void Algo_MainFuncion(void)
{
    switch(algo_state_en)
    {
    case ALGO_NONE:
         break;
    case ALGO_INIT:
         break;
    case ALGO_STARTED:
         break;
    case ALGO_FINISHED:
          break;
    case ALGO_ERROR:
          break;
    default:
          break;
    }
}

int Algo_SetPointerToString(uint8_t* string_ps)
{
    if(NULL!=string_ps)
    {
        uint32_t size=strlen(string_ps);
        //only 64 characters allowed
        if(size<=ALGO_MAX_SIZE_DATA*2)
        {
            memcpy(algo_string_ptr,string_ps,size-1);
        }
    }
}

int Algo_Compute(void)
{
    
}

int Algo_GetResultToString(uint8_t* outString)
{

}

algo_states_t Algo_GetState(void)
{
    return algo_state_en;
}