

/*defines*/
#define ALGO_TRUE 1
#define ALGO_FALSE 0

#define ALGO_VER 0xCAFECAFEu

#define ALGO_MAX_SIZE_DATA 32u

/*types*/

typedef struct
{
    uint8_t    record_type_1_u8;
    uint8_t    record_type_2_u8;
    uint8_t    byte_count_u8;
    uint32_t   address_u32;
    uint8_t    data[ALGO_MAX_SIZE_DATA];
    uint8_t    crc;
}algo_srec_t;

typedef enum
{
    ALGO_NONE       =0,
    ALGO_INIT       =1,
    ALGO_STARTED    =2,
    ALGO_FINISHED   =3,
    ALGO_BUSY       =4,
    ALGO_ERROR      =5,
    ALGO_UNDEF      =0xFF
}algo_states_t;

typedef uint8_t algo_bool_t;

/*prototypes*/
extern int Algo_GetVersion(uint32_t *ver);
extern int Algo_SetPointerToString(uint8_t* string_ps);
extern int Algo_Compute(void);
extern int Algo_GetResultToString(uint8_t* outString, uint16_t* size);
extern algo_states_t Algo_GetState(void);

extern void Algo_MainFuncion(void);