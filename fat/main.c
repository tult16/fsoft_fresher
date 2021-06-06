/*******************************************************************************
* Include
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "read_file.h"

/*******************************************************************************
* define
******************************************************************************/
#define FOLDER_ATTR     0x10
#define HOUR(x)         ((x >> 11)& 0x1f)
#define MINUTE(x)       ((x >> 5) & 0x3f)
#define SECOND(x)       (x & 0x1f)
#define YEAR(x)         (((x) >> 9) + 1980)
#define MONTH(x)        ((x >> 5) & 0xf)
#define DAY(x)          (x & 0x1f)

/*******************************************************************************
* Global variable
******************************************************************************/
cluster_node_t *g_pHead         = NULL;
cluster_node_t *g_pListPoint    = NULL;
cluster_node_t *g_pTail         = NULL;

/*******************************************************************************
* Prototypes
******************************************************************************/
void LinkedList_Delete(cluster_node_t** head_ref);
void LinkedList_AddNode(uint8_t *folder_name, uint16_t startCluster, bool isFile, uint8_t index, uint32_t fileSize);
void LinkedList_Display(void);
void printDirectoryInfo(uint16_t entryCount, uint32_t sectorIndex, boolean addNode);
bool searchFolder(uint8_t index, fat12_16_t bootSectorInfo);


/*******************************************************************************
* Code
******************************************************************************/
void LinkedList_Delete(cluster_node_t** head_ref)
{
    /* deref head_ref to get the real head */
    cluster_node_t* current = *head_ref;
    cluster_node_t* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
        in the caller. */
    *head_ref = NULL;
}

void LinkedList_AddNode(uint8_t *folder_name, uint16_t startCluster, bool isFile, uint8_t index, uint32_t fileSize)
{
    /* Create a new node */
    cluster_node_t *newNode = (cluster_node_t *)malloc(sizeof(cluster_node_t));
    newNode->currentCluster = startCluster;
    newNode->isFile = isFile;
    newNode->fileSize = fileSize;
    newNode->index = index;
    newNode->next = NULL;

    /* Checks if the list is empty */
    if(g_pHead == NULL) {
        /* If list is empty, both g_pHead and tail will point to new node */
        g_pHead = newNode;
        g_pTail = newNode;
    }
    else {
        /* newNode will be added after g_pTail such that g_pTail's next will point to newNode */
        g_pTail->next = newNode;
        /* newNode will become new g_pTail of the list */
        g_pTail = newNode;
    }
}

void LinkedList_Display(void)
{
    printf("===============================\n");
    /* Node current will point to g_pHead */
    cluster_node_t *current = g_pHead;

    if(g_pHead == NULL) {
        printf("List is empty \n");
        return;
    }
    while(current != NULL) {
        current = current->next;
    }
}

void printDirectoryInfo(uint16_t entryCount, uint32_t sectorIndex, boolean addNode)
{
    uint16_t i, entryIndex;
    uint8_t file_status;
    uint8_t folder_ext;
    uint8_t count = 0;
    bool is_file;
    root_entry_t *info;
    printf("%-5s \t %-8s \t %-3s \t %-19s \t %-6s \t %s\n",
           "Index",
           "File",
           "Ext",
           "Modified Date",
           "Cluster",
           "Size");
    uint8_t buffSector[512];
    /* 1 sector = 512 byte = 16 entries */
    for (i = 0; i < entryCount/16; i++)
    {
        fatfs_read_sector(&buffSector[0], (sectorIndex + i));
        for (entryIndex = 0; entryIndex < 16; entryIndex++)
        {
            /* read each entry from sector data */
            info = (root_entry_t *)&buffSector[entryIndex*32];
            switch (info->fileAttributes)
            {
                case 0x00:
                case FOLDER_ATTR:
                    switch (info->short_FileName[0])
                    {
                        case 0x00:
                        case 0xE5:
                        case 0x05:
                        /* case 0x2E: */
                            break;
                        default:
                            is_file = (FOLDER_ATTR == info->fileAttributes) ? false : true;
                            printf("[%-5d] [%.8s] \t [%.3s] \t %04d-%02d-%02d %02d:%02d.%02d \t 0x%04X \t %d\n",\
                                    count,
                                    info->short_FileName,
                                    info->extensionFileName,
                                    YEAR(info->Date),
                                    MONTH(info->Date),
                                    DAY(info->Date),
                                    HOUR(info->Time),
                                    MINUTE(info->Time),
                                    SECOND(info->Time),
                                    info->firstCluster,
                                    info->sizeofFile);
                            if (addNode == true)
                            {
                                LinkedList_AddNode(info->short_FileName, info->firstCluster, is_file, count, info->sizeofFile);
                            }

                            count++;
                            break;
                    }
                default:
                    break;
            }
        }
    }
}

bool searchFolder(uint8_t index, fat12_16_t bootSectorInfo)
{
    bool check = false;
    bool is_read_data = false;
    uint32_t cluster_offset;
    uint16_t entryCount;
    uint16_t rootDir = bootSectorInfo.BPB_NumFATs * bootSectorInfo.BPB_FATSz16 + 1;
    uint8_t *dataRead;
    char * readData;
    uint32_t i;
    uint32_t size;

    cluster_node_t *current = g_pHead;
    /* printf("g_pHead->cluster: %d\n", g_pHead->currentCluster); */
    if (g_pListPoint == NULL)
    {
        g_pListPoint = g_pHead;
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
            g_pListPoint->currentCluster = current->currentCluster;
            g_pListPoint->index = current->index;
            g_pListPoint->fileSize = current->fileSize;
            g_pListPoint->isFile = current->isFile;
            g_pListPoint->next = current->next;
        }
        else
        {
            is_read_data = true;
            readData = fatfs_read_file(current->currentCluster, bootSectorInfo, current->fileSize);
            size = current->fileSize;
        }
        if (0 != g_pListPoint->currentCluster)
        {
            cluster_offset = rootDir*SIZESECTOR + bootSectorInfo.BPB_RootEntCnt*ENTRY_SIZE + (g_pListPoint->currentCluster - 2)*SIZESECTOR;
            entryCount = bootSectorInfo.BPB_SecPerClus * bootSectorInfo.BPB_BytsPerSec/32;
        }
        else
        {
            cluster_offset = rootDir*SIZESECTOR;
            entryCount = bootSectorInfo.BPB_RootEntCnt;
        }

       system("cls");

       if (is_read_data != true)
       {
           LinkedList_Delete(&g_pHead);
       }

        printDirectoryInfo(entryCount, cluster_offset/SIZESECTOR, !is_read_data);
        current = g_pHead;
        if (is_read_data == true)
        {
            printf("Read data of index %d: \n", index);
            for (i = 0; i < size; i++)
            {
                printf("%c", readData[i]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Not found\n");
    }


    return check;
}

int main() {
    fat12_16_t bootSectorInfo;
    g_pListPoint = (cluster_node_t *)malloc(sizeof(cluster_node_t));
    uint16_t rootDirSectorIndex;

    bootSectorInfo = fatfs_init("d:\\test\\fsoft_fresher\\fat\\floppy.img");
    rootDirSectorIndex = bootSectorInfo.BPB_NumFATs * bootSectorInfo.BPB_FATSz16 + 1;

    printDirectoryInfo(bootSectorInfo.BPB_RootEntCnt, rootDirSectorIndex, true);
    g_pListPoint->currentCluster = 0;

    uint8_t index;
    while (true)
    {
        printf("User input: ");
        scanf("%d", &index);
        searchFolder(index, bootSectorInfo);
    }
    return 0;
}
