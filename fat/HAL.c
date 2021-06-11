/*******************************************************************************
* Include
******************************************************************************/
#include "HAL.h"
/*******************************************************************************
* variable
******************************************************************************/
static FILE *sp_filePointer = NULL;/*pointer file*/
static uint32_t s_bytePerSec = 512;/*byte per sector*/

/*******************************************************************************
* Code
******************************************************************************/
/*initial function kmc*/
bool kmc_init(char * filePath)
{
    bool retVal = true;

    sp_filePointer = fopen(filePath,"rb");
    if(NULL == sp_filePointer) retVal = false;

    return retVal;
}

/* function read 1 sector save buff*/
int32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    int32_t retVal = -1;

    if(0 == fseek(sp_filePointer,index*s_bytePerSec, SEEK_SET))
    {
        retVal = fread(buff,1,s_bytePerSec,sp_filePointer);
    }
    
    return retVal;

}

/*Function read multi sector save byff*/
int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff)
{
    int32_t retVal = -1;
    
    if(0 == fseek(sp_filePointer,index*s_bytePerSec, SEEK_SET))
    {
        retVal = fread(buff,1,s_bytePerSec*num,sp_filePointer);
    }
    
    return retVal;

}

/*function update size of sector*/
void kmc_update_size_sec(uint32_t sizeSec)
{
    s_bytePerSec = sizeSec;
}

/*function deinitial kmc*/
bool kmc_deinit()
{
    bool retVal = fclose(sp_filePointer);/*close file*/

    return retVal;
}
