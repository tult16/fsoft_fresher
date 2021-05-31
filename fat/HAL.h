#ifndef __HEADER_HAL__
#define __HEADER_HAL__
/*******************************************************************************
* Include
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*******************************************************************************
* Prototypes
******************************************************************************/
/*
function initial kmc
input:file path
output: true if open file else false
*/
bool kmc_init(char * filePath);
/*
function read sector
input: index of sector, buffer save data
output: size read data
*/
int32_t kmc_read_sector(uint32_t index, uint8_t *buff);
/*
function read multi sector
input: index of sector,number of sector, buffer save data
output: size read data
*/
int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff);
/*
functiom update size sector
input: read size sector
*/
void kmc_update_size_sec(uint32_t sizeSec);

FILE * get_file_pointer(void);
/*
function deinitial kmc
output: true if close file else false
*/
bool kmc_deinit();
#endif /*__HEADER_HAL__*/
