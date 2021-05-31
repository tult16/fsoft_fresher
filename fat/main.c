#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "read_file.h"

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



cluster_node_t *head = NULL;
cluster_node_t *listPoint;
cluster_node_t *tail =  NULL;


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

bool searchFolder(uint8_t index, fat12_16_t *bootSectorInfo, FILE *pFile, cluster_node_t *currentNode)
{
    bool check = false;
    bool is_read_data = false;
    uint32_t cluster_offset;
    uint16_t entryCount;
    uint16_t rootDir = bootSectorInfo->BPB_NumFATs * bootSectorInfo->BPB_FATSz16 + 1;
    uint8_t *dataRead;
    char * readData;
    uint32_t i;
    uint32_t size;

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
            size = current->fileSize;
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
    fat12_16_t *bootSectorInfo = (fat12_16_t *)malloc(sizeof(fat12_16_t));
    root_entry_t *rootEntryInfo = (root_entry_t *)malloc(sizeof(root_entry_t));
    listPoint = (cluster_node_t *)malloc(sizeof(cluster_node_t));
    uint16_t nodeRootDirectory;
    uint16_t entryCount;
    uint16_t i;
    uint16_t start_cluster;
    uint32_t cluster_offset;
    
//    read boot_sector
    *bootSectorInfo = fatfs_init("");

//	read roor_directory
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
