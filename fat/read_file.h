#ifndef __HEADER_READ_FILE__
#define __HEADER_READ_FILE___
/*******************************************************************************
* Include
******************************************************************************/
#include "HAL.h"
/*******************************************************************************
* define
******************************************************************************/
#define MAXNAME         256 /*max size long file name*/
#define SIZESECTOR      512
#define ENTRY_SIZE      32
#define FAT16_EOF       0xFFFF
#define FAT12_EOF       0xFFF

/*******************************************************************************
* typedef struct
******************************************************************************/
#pragma pack(1)
typedef struct {
    uint8_t   BS_jmpBoot[3];    /* 0x00-3byte Part of the bootstrap program. */
    uint8_t   BS_OEMName[8];    /* 0x03-8byte Optional manufacturer description. */
    uint16_t  BPB_BytsPerSec;   /* 0x0b-2byte Number of bytes per block (almost always 512). */
    uint8_t   BPB_SecPerClus;   /* 0x0d-1byte Number of blocks per allocation unit. */
    uint16_t  BPB_RsvdSecCnt;   /* 0x0e-2byte Number of reserved blocks. */
    uint8_t   BPB_NumFATs;      /* 0x10-1byte Number of File Allocation Tables. */
    uint16_t  BPB_RootEntCnt;   /* 0x11-2byte Number of root directory entries */
    uint16_t  BPB_TotSec16;     /* 0x13-2byte Total number of blocks in the entire disk. */
    uint8_t   BPB_Media;        /* 0x15-1byte Media Descriptor. */
    uint16_t  BPB_FATSz16;      /* 0x16-2byte The number of blocks occupied by one copy of the File Allocation Table. */
    uint16_t  BPB_SecPerTrk;    /* 0x18-2byte The number of blocks per track */
    uint16_t  BPB_NumHeads;     /* 0x1a-2byte The number of heads */
    uint32_t  BPB_HiddSec;      /* 0x1c-4byte The number of hidden blocks. */
    uint32_t  BPB_TotSec32;     /* 0x20-4byte Total number of blocks in the entire disk */
    uint8_t   BS_DrvNum;        /* 0x24-2byte Physical drive number. */
    uint8_t   BS_Reserved1;     /* 0x25-1byte  Unused */
    uint8_t   BS_BootSig;       /* 0x26-1byte Extended Boot Record Signature */
    uint32_t  BS_VolID;         /* 0x27-4byte Volume Serial Number. */
    uint8_t   BS_VolLab[11];    /* 0x2b-11byte Volume Label. */
    uint8_t   BS_FilSysType[8]; /* 0x36-8byte File system identifier */

} fat12_16_t; /* FatBootSector; */

typedef struct {
   uint8_t  short_FileName[8];
   uint8_t  extensionFileName[3];
   uint8_t  fileAttributes;
   uint8_t  reserved[10];
   uint16_t Time;
   uint16_t Date;
   uint16_t firstCluster;
   uint32_t sizeofFile;
} root_entry_t;

typedef struct clusterNode {
    uint16_t    currentCluster;
    bool        isFile;
    uint8_t     index;
    uint32_t    fileSize;
    struct clusterNode *next;
} cluster_node_t;

/*******************************************************************************
* Prototypes
******************************************************************************/
fat12_16_t fatfs_init(char * filePath);

/*
function reads file/folder from start cluster number
input: start cluster, boot secto information, size of folder/size
output: buffer read data
*/
void fatfs_read_file(uint16_t startCluster, fat12_16_t bootSectorInfo, uint32_t fileSize);

/*
function reads 1 sector
input: buffer save data, index of sector
output: size read data
*/
int32_t fatfs_read_sector(uint8_t *buff, uint32_t sectorIndex);

#endif /*__HEADER_READ_FILE___*/
