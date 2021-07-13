#include "update_parse.h"

static uint32_t errorCount = 0;

static uint8_t srec_charToHex(char ch)
{
    uint8_t retVal = 0xFF;

    if ((ch >= '0') && (ch <= '9'))
    {
        retVal = ch - '0';
    }
    else if ((ch >= 'A') && (ch <= 'F'))
    {
        retVal = ch - 'A' + 10;
    }
    else
    {
        errorCount++;
    }

    return retVal;
}

srec_parse_error_t srec_parse(uint8_t srecLine[],srec_parse_data_struct_t *output)
{
    srec_parse_error_t errorCode = parseError_Undefined;
    uint8_t srecType = 0;
    uint8_t byteCount = 0;
    uint16_t offset = 4;   // address possion
    uint8_t checksum = 0;
    uint8_t numberOfAddressByte = 0;
    uint32_t address = 0;
    uint8_t dataTpm = 0;
    uint8_t dataIndex = 0;

    if (srecLine[0] == 'S')
    {
        srecType = srec_charToHex(srecLine[1]);
        byteCount = (srec_charToHex(srecLine[2]) << 4) | srec_charToHex(srecLine[3]);
        checksum = byteCount;
        switch (srecType)
        {
        case 0:
            // Khi ung dung nhan duoc status nay thi bat dau xoa bo nho
            errorCode = parseError_Start;
            break;
        case 1:
        case 2:
        case 3:
            // tinh so byte address
            numberOfAddressByte = srecType +1;
            errorCode = parseError_Inprogress;
            break;
        case 5:
        case 6:
            // optional-> bo qua
            break;
        case 7:
        case 8:
        case 9:
            errorCode = parseError_Done;
            numberOfAddressByte = 11 - srecType;
            break;
        default:
           errorCode = parseError_Invalid;
            break;
        }

        if ((errorCode == parseError_Inprogress) || (errorCode == parseError_Done))
        {
            // parse Data
            // get address
            for (dataIndex  = 0; dataIndex < numberOfAddressByte; dataIndex++)
            {
                dataTpm = srec_charToHex(srecLine[offset] <<4) | srec_charToHex(srecLine[offset +1]);
                address = (address << 8) | dataTpm;
                offset +=2;
                checksum += dataTpm;
            }
            // update address
            output -> address = address;
            output -> length = byteCount -1 - numberOfAddressByte;

            // get data
            for (dataIndex  = 0; dataIndex < output->length; dataIndex++)
            {
                dataTpm = srec_charToHex(srecLine[offset] <<4) | srec_charToHex(srecLine[offset +1]);
                output ->data[dataIndex] = dataTpm;
                offset +=2;
                checksum += dataTpm;
            }

            // offset tro toi vi tri cua checksum byte trong line
            // tinh checksum
            checksum += srec_charToHex(srecLine[offset] <<4) | srec_charToHex(srecLine[offset +1]);
            if (0xFF != checksum)
            {
                errorCode = parseError_InvalidChecksum;
            }
        }
    }
    else
    {
        errorCode = parseError_Invalid;
    }

    return errorCode;
}
