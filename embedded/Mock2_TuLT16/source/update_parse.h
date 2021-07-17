#ifndef _HEADER_UPDATE_PARSER_
#define _HEADER_UPDATE_PARSER_

// output: address, data va length
#include <stdint.h>
#include <stdbool.h>

#define SREC_LINE_TRUE               ">>\r\n"
#define SREC_LINE_TRUE_SIZE          4
#define SREC_LINE_FALSE              "Error\r\n"
#define SREC_LINE_FALSE_SIZE         7

typedef struct
{
    uint32_t address;
    uint8_t data[256];
    uint16_t length;
} srec_parse_data_struct_t;
typedef enum
{
    parseError_Done = 0x00,
    parseError_Start = 0x01,
    parseError_Inprogress = 0x02,
    parseError_Invalid,
    parseError_InvalidChecksum,
    parseError_InvalidSrecType,
    parseError_Undefined = 0xFF
} srec_parse_error_t;

srec_parse_error_t srec_parse(char srecLine[],srec_parse_data_struct_t *output);

#endif /* _HEADER_UPDATE_PARSER_ */
