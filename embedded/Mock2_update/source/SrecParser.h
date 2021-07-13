#ifndef _HEADER_SREC_PARSER_
#define _HEADER_SREC_PARSER_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define SREC_MAX_SIZE                255
#define SREC_BYTECOUNT_START_INDEX   2
#define SREC_ADDRESS_START_INDEX     4
#define SREC_CHECKSUM_BYTE_COUNT     2
#define SREC_RECORD_TYPE_BYTE_COUNT  2
#define SREC_LINE_TRUE               ">>\r\n"
#define SREC_LINE_TRUE_SIZE          4
#define SREC_LINE_FALSE              "Error\r\n"
#define SREC_LINE_FALSE_SIZE         7


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Function srec parse line.
 * @param[in] str
 * @return true if line not error else false
 */
bool SREC_Parser(char *str, char *address, char *data);

/**
 * @brief Function check check sum srec line.
 * @param[in] str
 * @param[in] length
 * @return true if check sum not error else false
 */
bool SREC_CheckSum(char str[], int length);

/**
 * @brief Function check data.
 * @param[in] str
 * @param[in] length
 * @param[in] addressByte
 * @param[in] s19Data
 * @return true if check data not error else false
 */
bool SREC_CheckData(char str[], int length, int addressByte, char *s19Data);

/**
 * @brief Function check address.
 * @param[in] str
 * @param[in] recordType
 * @param[in] addressByte
 * @param[in] s19Address
 * @return true if check address not error else false
 */
bool SREC_CheckAddress(char str[], char recordType, uint8_t *addressByte, char *s19Address);

/**
 * @brief Function check bytecount.
 * @param[in] str
 * @param[in] length
 * @return true if check bytecount not error else false
 */
bool SREC_CheckByteCount(char str[], int length);

/**
 * @brief Function check record type.
 * @param[in] buff
 * @param[in] recordType
 * @return true if check record type not error else false
 */
bool SREC_CheckRecordType(char byte, char* recordType);

/**
 * @brief Function check RecordStart.
 * @param[in] buff
 * @return true if check RecordStart not error else false
 */
bool SREC_CheckRecordStart(char byte);

/**
 * @brief Function check hexa character.
 * @param[in] byte
 * @return true if byte is character else false
 */
bool SREC_CheckHexCharater(char byte);

/**
 * @brief Function convert character to hex.
 * @param[in] byte
 * @return hex of input
 */
uint8_t ConvertChar2Hex(char byte);

#endif /* _HEADER_SREC_PARSER_ */
