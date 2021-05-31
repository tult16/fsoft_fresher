/*******************************************************************************
* Include
******************************************************************************/
#include "read_file.h"
/*******************************************************************************
* variable
******************************************************************************/
FILE *pFile;

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

    if ((fatIndex % 2) == 1)
    {/*is odd number bit tail  = 1*/
        retVal = fatData[fatIndex]>>4 | (fatData[fatIndex+1]<<4);
    }
    else
    {/*is even number*/
        retVal = fatData[fatIndex]|(fatData[fatIndex+1]&0x0F)<<8;
    }
    return retVal;
}

fat12_16_t fatfs_init(char * filePath)
{
    fat12_16_t diskInfo;/*struct data information disk*/
    bool check = kmc_init(filePath);/*check open file img*/

    if(true == check)
    {
    	// read boot_sector
        kmc_update_size_sec(sizeof(fat12_16_t));
        kmc_read_sector(0, &diskInfo);
        
        kmc_update_size_sec(diskInfo.BPB_BytsPerSec);/*update value byte per sector*/
    }
    pFile = get_file_pointer();

    return diskInfo;
}

char * fatfs_read_file(uint16_t startCluster, fat12_16_t bootSectorInfo, uint32_t fileSize, FILE *pFile)
{
    uint32_t SecfirstData = bootSectorInfo.BPB_NumFATs * bootSectorInfo.BPB_FATSz16 + 1 + bootSectorInfo.BPB_RootEntCnt*ENTRY_SIZE/bootSectorInfo.BPB_BytsPerSec;
    uint32_t nextClus = startCluster;
    uint32_t cluster_status;
    uint32_t index=0;
    uint8_t *buff = (uint8_t*)malloc ((fileSize > bootSectorInfo.BPB_BytsPerSec) ? fileSize : bootSectorInfo.BPB_BytsPerSec);
    int32_t ret;
    // read FAT data and save to buffer
    uint32_t fatAddrOffeset = bootSectorInfo.BPB_BytsPerSec;
    uint8_t fatData[bootSectorInfo.BPB_BytsPerSec * bootSectorInfo.BPB_NumFATs];
    fseek(pFile, fatAddrOffeset, SEEK_SET);
    fread(fatData, 1, bootSectorInfo.BPB_BytsPerSec * bootSectorInfo.BPB_NumFATs, pFile);

    if (fileSize <= bootSectorInfo.BPB_BytsPerSec)
    {
        ret = kmc_read_sector(SecfirstData + (nextClus-2)* bootSectorInfo.BPB_SecPerClus, buff);
        buff[fileSize] = '\0';
    }
    else
    {
        // read multiple cluster, read until cluster status is FAT12_EOF or number of reading byte equals fileSize
    	do 
    	{
//    		printf("Cluster: %d\n", nextClus);
    		ret = kmc_read_multi_sector(SecfirstData + (nextClus-2)* bootSectorInfo.BPB_SecPerClus, bootSectorInfo.BPB_SecPerClus, &buff[index]);
        	index += bootSectorInfo.BPB_SecPerClus * bootSectorInfo.BPB_BytsPerSec;
        	cluster_status = fatfs_next_clus(nextClus, fatData);
//        	printf("Cluster status: 0x%x\n", nextClus);
        	nextClus++;
        	if (nextClus == (startCluster + (fileSize/bootSectorInfo.BPB_BytsPerSec)))
        	{
        		break;
        	}
		}
    	while (FAT12_EOF != cluster_status);
        buff[index] = '\0';
    }
    return buff;
    printf("\n");
}
