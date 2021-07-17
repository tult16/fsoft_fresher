/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "SrecParser.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function parse srec line */
bool SREC_Parser(char *str, char *address, char *data, char *data_length)
{
    bool check = false;
    char recordType;
    // char address[SREC_MAX_SIZE];
    // char data[SREC_MAX_SIZE];
    uint8_t addressByte;
    uint8_t strSize;

    strSize = strlen(str);
    check = SREC_CheckRecordStart(str[0]);
    check &= SREC_CheckRecordType(str[1], &recordType);
    check &= SREC_CheckByteCount(str, strSize);
    check &= SREC_CheckAddress(str, recordType, &addressByte, address);
    check &= SREC_CheckData(str, strSize, addressByte, data);
    check &= SREC_CheckSum(str, strSize);
    *data_length = strSize - 2 - SREC_ADDRESS_START_INDEX - addressByte;

    return check;
}

/*Function convert char to hex*/
uint8_t ConvertChar2Hex(char byte)
{
    uint8_t number;
    if ((byte >= '0') && (byte <= '9'))
    {
        number = byte - '0';
    }
    else
    {
        if ((byte >= 'A') && (byte <= 'F'))
        {
            number = byte - 'A' + 10;
        }
        else
        {
            if ((byte >= 'a') && (byte <= 'f'))
            {
                number = byte - 'a' + 10;
            }
        }
    }
    return number;
}

/*Function check hex character*/
bool SREC_CheckHexCharater(char byte)
{
    bool check = true;

    if (('0' > byte) || ('F' < byte))
    {
        check = false;
    }

    return check;
}

/*Function check character record start is 'S' in line */
bool SREC_CheckRecordStart(char byte)
{
    bool check = true;
    if (byte != 'S')
    {
        check = false;
    }

    return check;
}

/*Function check record type*/
bool SREC_CheckRecordType(char byte, char* recordType)
{
    bool check = false;
    if ((byte >= '0') && (byte <= '9'))
    {
        check = true;
        *recordType = byte;
    }

    return check;
}

/*Function check ByteCount in line*/
bool SREC_CheckByteCount(char str[], int length)
{
    bool check = false;
    uint8_t byteCount;
    if (SREC_CheckHexCharater(str[SREC_BYTECOUNT_START_INDEX]) && SREC_CheckHexCharater(str[SREC_BYTECOUNT_START_INDEX+1]))
    {
        check = true;
        byteCount = (ConvertChar2Hex(str[SREC_BYTECOUNT_START_INDEX]) << 4) + ConvertChar2Hex(str[SREC_BYTECOUNT_START_INDEX + 1]);
        if (byteCount != ((length - 4)/2))
        {
            check = false;
        }
    }

    return check;
}

/*Function check Address in line*/
bool SREC_CheckAddress(char str[], char recordType, uint8_t *addressByte, char s19Address[])
{
    bool check = true;
    int i;
    switch (recordType)
    {
        case '0':
        case '1':
        case '5':
        case '9':
            *addressByte = 4;
            break;
        case '2':
        case '6':
        case '8':
            *addressByte = 6;
            break;
        case '3':
        case '7':
            *addressByte = 8;
            break;
        default:
            *addressByte = 0;
    }
    for (i = SREC_ADDRESS_START_INDEX; i < (SREC_ADDRESS_START_INDEX + *addressByte); i++)
    {
        if (false == (SREC_CheckHexCharater(str[i])))
        {
            check = false;
            break;
        }
        else
        {
            s19Address[i - SREC_ADDRESS_START_INDEX] = str[i];
        }
    }

    return check;
}

/*Function check data in line*/
bool SREC_CheckData(char str[], int length, int addressByte, char s19Data[])
{
    bool check = true;
    int i;
    if ((SREC_ADDRESS_START_INDEX + addressByte + SREC_CHECKSUM_BYTE_COUNT) >= length)
    {
        /* no data in line*/
        check = true;
        s19Data[0] = '\0';
    }
    else
    {
        for ( i = (SREC_ADDRESS_START_INDEX + addressByte); i < (length-2); i++)
        {
            if (false == (SREC_CheckHexCharater(str[i])))
            {
                check = false;
                break;
            }
            else
            {
                s19Data[i - (SREC_ADDRESS_START_INDEX + addressByte)] = str[i];
            }
        }
        s19Data[i - (SREC_ADDRESS_START_INDEX + addressByte)] = '\0';
    }

    return check;
}

/*Function check checksum in line*/
bool SREC_CheckSum(char str[], int length)
{
    bool check = false;
    uint16_t calCheckSum = 0;
    uint8_t actualCheckSum = 0;
    if (SREC_CheckHexCharater(str[length-2]) && SREC_CheckHexCharater(str[length-1]))
    {
        check = true;
        int i;
        for (i = 0; i < (length - SREC_RECORD_TYPE_BYTE_COUNT - SREC_CHECKSUM_BYTE_COUNT)/2; i++)
        {
            calCheckSum += (ConvertChar2Hex(str[SREC_BYTECOUNT_START_INDEX + 2*i]) << 4) + ConvertChar2Hex(str[SREC_BYTECOUNT_START_INDEX + 2*i + 1]);
        }
        calCheckSum     =  calCheckSum & 0xFF;
        calCheckSum     = ~calCheckSum & 0xFF;
        actualCheckSum  =  (ConvertChar2Hex(str[length-2]) << 4) + ConvertChar2Hex(str[length-1]);
        if (calCheckSum != actualCheckSum)
        {
            check = false;
        }
    }
    return check;
}




