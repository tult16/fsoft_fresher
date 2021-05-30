#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define SIZESECTOR    512
#define ENTRY_SIZE    32
#define FOLDER_ATTR   0x10
#define ATTR_INVALID   0xFF
#define FILE_STATUS_INVALID 0
#define HOUR(x)     ((x >> 11)& 0x1f)
#define MINUTE(x)   ((x >> 5) & 0x3f)
#define SECOND(x)   (x & 0x1f)
#define YEAR(x)     (((x) >> 9) + 1980)
#define MONTH(x)    ((x >> 5) & 0xf)
#define DAY(x)      (x & 0x1f)
#define FAT16_EOF   0xFFFF
#define FAT12_EOF   0xFFF

#pragma pack(1)
typedef struct {
    uint8_t   BS_jmpBoot[3];//0x00-3byte Part of the bootstrap program.
    uint8_t   BS_OEMName[8];//0x03-8byte Optional manufacturer description.
    uint16_t  BPB_BytsPerSec;//0x0b-2byte Number of bytes per block (almost always 512).
    uint8_t   BPB_SecPerClus;//0x0d-1byte Number of blocks per allocation unit.
    uint16_t  BPB_RsvdSecCnt;//0x0e-2byte Number of reserved blocks.
    uint8_t   BPB_NumFATs;//0x10-1byte Number of File Allocation Tables.
    uint16_t  BPB_RootEntCnt;//0x11-2byte Number of root directory entries
    uint16_t  BPB_TotSec16;//0x13-2byte Total number of blocks in the entire disk.
    uint8_t   BPB_Media;//0x15-1byte Media Descriptor.
    uint16_t  BPB_FATSz16;//0x16-2byte The number of blocks occupied by one copy of the File Allocation Table.
    uint16_t  BPB_SecPerTrk;//0x18-2byte The number of blocks per track
    uint16_t  BPB_NumHeads;//0x1a-2byte The number of heads
    uint32_t  BPB_HiddSec;//0x1c-4byte The number of hidden blocks.
    uint32_t  BPB_TotSec32;//0x20-4byte Total number of blocks in the entire disk
    uint8_t   BS_DrvNum;//0x24-2byte Physical drive number.
    uint8_t   BS_Reserved1;//0x25-1byte  Unused
    uint8_t   BS_BootSig;//0x26-1byte Extended Boot Record Signature
    uint32_t  BS_VolID;//0x27-4byte Volume Serial Number.
    uint8_t   BS_VolLab[11];//0x2b-11byte Volume Label.
    uint8_t   BS_FilSysType[8];//0x36-8byte File system identifier

} fat12_16_t;//FatBootSector;

typedef struct {
   uint8_t  short_FileName[8];//11BYTE
   uint8_t  extensionFileName[3];
   uint8_t  fileAttributes;//1BYTE
   uint8_t  reserved[10];//10BYTE
   uint16_t Time;//2BYTE
   uint16_t Date;//2BYTE
   uint16_t firstCluster;//2BYTE
   uint32_t sizeofFile;//4BYTE
} root_entry_t;

typedef struct clusterNode {
    uint16_t    currentCluster;
    bool        isFile;
    uint8_t     index;
    uint32_t    fileSize;
    struct clusterNode *next;
} cluster_node_t;

cluster_node_t *head = NULL;
cluster_node_t *listPoint;
cluster_node_t *tail =  NULL;
FILE *pFile;


void LinkedList_Delete(cluster_node_t ** head)
{
    cluster_node_t * prev = *head;

    while (*head)
    {
        *head = (*head)->next;
        free(prev);
        prev = *head;
    }
}


void LinkedList_AddNode(uint8_t *folder_name, uint16_t startCluster, bool isFile, uint8_t index, uint32_t fileSize) {
    //Create a new node
    cluster_node_t *newNode = (cluster_node_t *)malloc(sizeof(cluster_node_t));
    newNode->currentCluster = startCluster;
    newNode->isFile = isFile;
    newNode->fileSize = fileSize;
    newNode->index = index;
    newNode->next = NULL;

    //Checks if the list is empty
    if(head == NULL) {
        //If list is empty, both head and tail will point to new node
        head = newNode;
        tail = newNode;
    }
    else {
        //newNode will be added after tail such that tail's next will point to newNode
        tail->next = newNode;
        //newNode will become new tail of the list
        tail = newNode;
    }
}

void LinkedList_Display() {
    printf("===============================\n");
    //Node current will point to head
    cluster_node_t *current = head;

    if(head == NULL) {
        printf("List is empty \n");
        return;
    }
    while(current != NULL) {
        current = current->next;
    }
}

void printDirectoryInfo(FILE *pFile, uint16_t entryCount)
{
    uint16_t i;
    uint8_t file_status;
    uint8_t folder_ext;
    uint8_t count = 0;
    bool is_file;
    root_entry_t info;
    printf("%-5s \t %-8s \t %-3s \t %-19s \t %-6s \t %s\n",
           "Index",
           "File",
           "Ext",
           "Modified Date",
           "Cluster",
           "Size");
    for (i = 0; i < entryCount; i++)
    {
        fread(&info, sizeof(root_entry_t), 1, pFile);
        switch (info.fileAttributes)
        {
            case 0x00:
            case FOLDER_ATTR:
                switch (info.short_FileName[0])
                {
                    case 0x00:
                    case 0xE5:
                    case 0x05:
                    // case 0x2E:
                        break;
                    default:
                        is_file = (FOLDER_ATTR == info.fileAttributes) ? false : true;
                        printf("[%-5d] [%.8s] \t [%.3s] \t %04d-%02d-%02d %02d:%02d.%02d \t 0x%04X \t %d\n",\
                                count,
                                info.short_FileName,
                                info.extensionFileName,
                                YEAR(info.Date),
                                MONTH(info.Date),
                                DAY(info.Date),
                                HOUR(info.Time),
                                MINUTE(info.Time),
                                SECOND(info.Time),
                                info.firstCluster,
                                info.sizeofFile);
                        LinkedList_AddNode(info.short_FileName, info.firstCluster, is_file, count, info.sizeofFile);
                        count++;
                        break;
                }
            default:
                break;
        }
    }
}


int32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    fseek(pFile, index*SIZESECTOR, SEEK_SET);
    return fread(buff, 1, SIZESECTOR, pFile);
}

int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff)
{
    printf("Offset: 0x%x\n", index*SIZESECTOR);
    fseek(pFile, index*SIZESECTOR, SEEK_SET);
    return fread(buff, 1, SIZESECTOR*num, pFile);
}

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


char * fatfs_read_file(uint16_t startCluster, fat12_16_t bootSectorInfo, uint32_t fileSize, FILE *pFile)
{
    uint32_t SecfirstData = bootSectorInfo.BPB_NumFATs * bootSectorInfo.BPB_FATSz16 + 1 + bootSectorInfo.BPB_RootEntCnt*ENTRY_SIZE/SIZESECTOR;
    uint32_t nextClus = startCluster;
    uint32_t index=0;
    uint8_t *buff = (uint8_t*)malloc(SIZESECTOR);
    int32_t ret;
    // read FAT data and save to buffer
    uint32_t fatAddrOffeset = bootSectorInfo.BPB_BytsPerSec;
    uint8_t fatData[bootSectorInfo.BPB_BytsPerSec * bootSectorInfo.BPB_NumFATs];
    fseek(pFile, fatAddrOffeset, SEEK_SET);
    fread(fatData, 1, bootSectorInfo.BPB_BytsPerSec * bootSectorInfo.BPB_NumFATs, pFile);

    if (fileSize <= SIZESECTOR)
    {
        ret = kmc_read_sector(SecfirstData + (nextClus-2)* bootSectorInfo.BPB_SecPerClus, buff);
        buff[fileSize] = '\0';
        // printf("data read: %s", buff);
    }
    else
    {
        ret = kmc_read_multi_sector(SecfirstData + (nextClus-2)* bootSectorInfo.BPB_SecPerClus, bootSectorInfo.BPB_SecPerClus, buff);
        index += bootSectorInfo.BPB_SecPerClus * bootSectorInfo.BPB_BytsPerSec;
        nextClus = fatfs_next_clus(nextClus, fatData);/*next cluster */
        buff[index] = '\0';
        // printf("%s", buff);
    }
    return buff;
    printf("\n");
}

bool searchFolder(uint8_t index, fat12_16_t *bootSectorInfo, FILE *pFile, cluster_node_t *currentNode)
{
    bool check = false;
    bool is_read_data = false;
    uint32_t cluster_offset;
    uint16_t entryCount;
    uint16_t rootDir = bootSectorInfo->BPB_NumFATs * bootSectorInfo->BPB_FATSz16 + 1;
    uint8_t *dataRead;
    char * readData;

    cluster_node_t *current = head;
    printf("head->cluster: %d\n", head->currentCluster);
    if (currentNode == NULL)
    {
        currentNode = head;
    }
    while(current != NULL) {
        if (index == current->index)
        {
            check = true;
            break;
        }
        current = current->next;
    }

    if (true == check)
    {
        if (current->isFile != true)
        {
            currentNode->currentCluster = current->currentCluster;
            currentNode->index = current->index;
            currentNode->fileSize = current->fileSize;
            currentNode->isFile = current->isFile;
            currentNode->next = current->next;
        }
        else
        {
            is_read_data = true;
            readData = fatfs_read_file(current->currentCluster, *bootSectorInfo, current->fileSize, pFile);
        }
        if (0 != currentNode->currentCluster)
        {
            cluster_offset = rootDir*SIZESECTOR + bootSectorInfo->BPB_RootEntCnt*ENTRY_SIZE + (currentNode->currentCluster - 2)*SIZESECTOR;
            entryCount = bootSectorInfo->BPB_SecPerClus * bootSectorInfo->BPB_BytsPerSec/32;
        }
        else
        {
            cluster_offset = rootDir*SIZESECTOR;
            entryCount = bootSectorInfo->BPB_RootEntCnt;
        }

        system("cls");
        fseek(pFile, cluster_offset, SEEK_SET);

        if (is_read_data != true)
        {
            LinkedList_Delete(&head);
        }

        printDirectoryInfo(pFile, entryCount);
        current = head;
        if (is_read_data == true)
        {
            printf("Read data of index %d: \"%s\"\n", index, readData);
        }
    }
    else
    {
        printf("Not found\n");
    }


    return check;
}

int main() {
    fat12_16_t *bootSectorInfo = (fat12_16_t *)malloc(sizeof(fat12_16_t));
    root_entry_t *rootEntryInfo = (root_entry_t *)malloc(sizeof(root_entry_t));
    listPoint = (cluster_node_t *)malloc(sizeof(cluster_node_t));
    uint16_t nodeRootDirectory;
    uint16_t entryCount;
    uint16_t i;
    uint16_t start_cluster;
    uint32_t cluster_offset;

    pFile=fopen("floppy.img","a+");
    memset(bootSectorInfo,'\0', sizeof(fat12_16_t));

    fread(bootSectorInfo, sizeof(fat12_16_t), 1, pFile);
    bootSectorInfo->BS_FilSysType[5] = '\0';

    nodeRootDirectory = bootSectorInfo->BPB_NumFATs * bootSectorInfo->BPB_FATSz16 + 1;

    fseek(pFile, nodeRootDirectory*SIZESECTOR, SEEK_SET);
    entryCount = bootSectorInfo->BPB_RootEntCnt;

    printDirectoryInfo(pFile, entryCount);
    listPoint->currentCluster = 0;

    uint8_t index;
    while (true)
    {
        printf("User input: ");
        scanf("%d", &index);
        searchFolder(index, bootSectorInfo, pFile, listPoint);
    }
    return 0;
}
