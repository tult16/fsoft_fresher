#ifndef _HEADER_SREC_PARSE_
#define _HEADER_SREC_PARSE_

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define SIZE 255
#define S19_BYTECOUNT_START_INDEX   2
#define S19_ADDRESS_START_INDEX     4
#define S19_CHECKSUM_BYTE_COUNT     2
#define S19_RECORD_TYPE_BYTE_COUNT  2

bool srecParse(char *str);
bool checkCheckSum(char str[], int length);
bool checkData(char str[], int length, int addressByte, char s19Data[]);
bool checkAddress(char str[], char recordType, uint8_t *addressByte, char s19Address[]);
bool checkByteCount(char str[], int length);
bool checkRecordType(char byte, char* recordType);
bool checkRecordStart(char byte);
bool checkHexCharater(char byte);
uint8_t ConvertChar2Hex(char byte);

#endif /* _HEADER_SREC_PARSE_ */
