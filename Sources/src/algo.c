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

/*static prototypes*/

static algo_bool_t Algo_BuildSrecLine(uint8_t* str, uint32_t len)
{
    uint32_t ii = 0;
    uint8_t* ptrForCrc;
    uint16_t sum = 0;

    algo_srec_line_st.record_type_1_u8 = 'S';
    algo_srec_line_st.record_type_2_u8 = '3';
    algo_srec_line_st.address_u32 = 0x00000000; //todo: support more addresses
    algo_srec_line_st.byte_count_u8 = 4 + len + 1; //address + data +crc
    memcpy(&algo_srec_line_st.data[0], str, len);

    ptrForCrc = &algo_srec_line_st.byte_count_u8;

    //computing crc
    for (ii = 0; ii < algo_srec_line_st.byte_count_u8 - 1; ii++)
    {
        sum += ptrForCrc[ii];
    }
    //ones complement
    sum = sum ^ 0xFFFF;

    //just the last byte
    algo_srec_line_st.crc = (uint8_t)sum;

    return ALGO_TRUE;
}


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
    {
        algo_bool_t res;
        res = Algo_BuildSrecLine(algo_global_string_ptr, strlen(algo_global_string_ptr));
        if (res==ALGO_TRUE)
        {
            algo_state_en = ALGO_FINISHED;
        }
        else
        {
            algo_state_en = ALGO_ERROR;
        }
    }
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
    int retVal = ALGO_FALSE;
    if(NULL!=string_ps)
    {
        uint32_t size=strlen(string_ps);
        //only 64 characters allowed
        if(size<=ALGO_MAX_SIZE_DATA*2)
        {
            memcpy(algo_string_ptr,string_ps,size);
            
            algo_global_string_ptr=&algo_string_ptr[0];
            
            algo_state_en = ALGO_INIT;
        }
        retVal = ALGO_TRUE;
    }

    return retVal;
}

int Algo_Compute(void)
{
    algo_state_en = ALGO_STARTED;
}

int Algo_GetResultToString(uint8_t* outString, uint16_t* size)
{
    if (outString != NULL)
    {
        outString[0] = algo_srec_line_st.record_type_1_u8;
        outString[1] = algo_srec_line_st.record_type_2_u8;
        outString[2] = algo_srec_line_st.byte_count_u8;
        memcpy(&outString[3], (uint8_t*)&algo_srec_line_st.address_u32, 4);
        memcpy(&outString[7], (uint8_t*)&algo_srec_line_st.data, algo_srec_line_st.byte_count_u8-4-1);
        outString[7 + algo_srec_line_st.byte_count_u8 - 4 - 1] = algo_srec_line_st.crc;

        //add also the first 3 things
        *size = algo_srec_line_st.byte_count_u8+3;
    }
    return ALGO_TRUE;
}

algo_states_t Algo_GetState(void)
{
    return algo_state_en;
}
