/*******************************************************************************
* Include
******************************************************************************/
#include "read_file.h"
/*******************************************************************************
* variable
******************************************************************************/

/*******************************************************************************
* Prototypes
******************************************************************************/
static uint32_t fatfs_next_clus(uint32_t firstClus, uint8_t * fatData);

/*******************************************************************************
* Code
******************************************************************************/

/*function next cluster*/
static uint32_t fatfs_next_clus(uint32_t firstClus, uint8_t * fatData)
{
    uint32_t retVal;
    uint32_t fatIndex;

    fatIndex = firstClus*3/2;/*1.5 is size of element fat12*/

    if ((firstClus % 2) == 1)
    {
        retVal = (fatData[fatIndex] >> 4) | (fatData[fatIndex+1] << 4);
    }
    else
    {
        retVal = fatData[fatIndex] | ((fatData[fatIndex+1] & 0x0F) << 8);
    }
    return retVal;
}

fat12_16_t fatfs_init(char * filePath)
{
    fat12_16_t diskInfo;/*struct data information disk*/
    bool check = kmc_init(filePath);/*check open file img*/

    if(true == check)
    {
        /* read boot_sector */
        kmc_update_size_sec(sizeof(fat12_16_t));
        kmc_read_sector(0, (uint8_t *)&diskInfo);

        kmc_update_size_sec(diskInfo.BPB_BytsPerSec);/*update value byte per sector*/
    }

    return diskInfo;
}

static void prinf_file_content(uint8_t *buff, uint32_t size)
{
    uint32_t i;
    for (i = 0; i < size; i++)
    {
        printf("%c", buff[i]);
    }
}

void fatfs_read_file(uint16_t startCluster, fat12_16_t bootSectorInfo, uint32_t fileSize)
{
    uint32_t SecfirstData = bootSectorInfo.BPB_NumFATs * bootSectorInfo.BPB_FATSz16 + 1 + bootSectorInfo.BPB_RootEntCnt*ENTRY_SIZE/bootSectorInfo.BPB_BytsPerSec;
    uint32_t nextClus = startCluster;
    uint32_t cluster_status;
    uint32_t index=0;
    uint8_t i = 0;
    uint8_t buff[SIZESECTOR];
    int32_t ret;
    /* read FAT data and save to buffer */
    uint32_t fatAddrOffeset = bootSectorInfo.BPB_BytsPerSec;
    uint32_t fatByteCount = bootSectorInfo.BPB_BytsPerSec * bootSectorInfo.BPB_NumFATs * 9;
    uint8_t fatData[fatByteCount];
    /* printf("Fat offset: 0x%x\n", fatAddrOffeset); */

    for (i = 0; i < bootSectorInfo.BPB_NumFATs * 9; i++)
    {
        ret = kmc_read_sector((i+1), &fatData[i*bootSectorInfo.BPB_BytsPerSec]);
    }

    if (fileSize <= bootSectorInfo.BPB_BytsPerSec)
    {
        ret = kmc_read_sector(SecfirstData + (nextClus-2)* bootSectorInfo.BPB_SecPerClus, buff);
        prinf_file_content(buff, fileSize);
    }
    else
    {
        /* read until next cluster is FAT12_EOF */
        while (FAT12_EOF != nextClus)
        {
            ret = kmc_read_multi_sector(SecfirstData + (nextClus-2)* bootSectorInfo.BPB_SecPerClus, bootSectorInfo.BPB_SecPerClus, buff);
            nextClus = fatfs_next_clus(nextClus, fatData);
            if ((fileSize - index) > SIZESECTOR)
            {
                prinf_file_content(buff, SIZESECTOR);
            }
            else
            {
                prinf_file_content(buff, fileSize - index);
            }
            index += bootSectorInfo.BPB_SecPerClus * bootSectorInfo.BPB_BytsPerSec;
        }
    }
    printf("\n=================================\n");
    printf("End of reading file");
    printf("\n=================================\n");
    printf("\n");
}

int32_t fatfs_read_sector(uint8_t *buff, uint32_t sectorIndex)
{
    kmc_update_size_sec(SIZESECTOR);
    return kmc_read_sector(sectorIndex, buff);
}
