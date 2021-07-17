#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "SrecPase.h"

#define SIZE 255


bool srecParse(char *str)
{
    bool check = false;
    char recordType;
    char address[SIZE];
    char data[SIZE];
    uint8_t addressByte;
    uint8_t str_size;

    str_size = strlen(str);

    check = checkRecordStart(str[0]);
    check &= checkRecordType(str[1], &recordType);
    check &= checkByteCount(str, str_size);
    check &= checkAddress(str, recordType, &addressByte, address);
    check &= checkData(str, str_size, addressByte, data);
    check &= checkCheckSum(str, str_size);

    return check;
}

/*Function convert char to hexa*/
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

/*Function check hexa character*/
bool checkHexCharater(char byte)
{
    bool check = true;

    if (('0' > byte) || ('F' < byte))
    {
        check = false;
    }

    return check;
}

/*Function check charcter record start is 'S' in line */
bool checkRecordStart(char byte)
{
    bool check = true;
    if (byte != 'S')
    {
        check = false;
    }

    return check;
}

/*Function check record type*/
bool checkRecordType(char byte, char* recordType)
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
bool checkByteCount(char str[], int length)
{
    bool check = false;
    uint8_t byteCount;
    if (checkHexCharater(str[S19_BYTECOUNT_START_INDEX]) && checkHexCharater(str[S19_BYTECOUNT_START_INDEX+1]))
    {
        check = true;
        byteCount = (ConvertChar2Hex(str[S19_BYTECOUNT_START_INDEX]) << 4) + ConvertChar2Hex(str[S19_BYTECOUNT_START_INDEX + 1]);
        if (byteCount != ((length - 4)/2))
        {
            check = false;
        }
    }

    return check;
}

/*Function check Adress in line*/
bool checkAddress(char str[], char recordType, uint8_t *addressByte, char s19Address[])
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
    for (i = S19_ADDRESS_START_INDEX; i < (S19_ADDRESS_START_INDEX + *addressByte); i++)
    {
        if (false == (checkHexCharater(str[i])))
        {
            check = false;
            break;
        }
        else
        {
            s19Address[i - S19_ADDRESS_START_INDEX] = str[i];
        }
    }

    return check;
}

/*Function check data in line*/
bool checkData(char str[], int length, int addressByte, char s19Data[])
{
    bool check = true;
    int i;
    if ((S19_ADDRESS_START_INDEX + addressByte + S19_CHECKSUM_BYTE_COUNT) >= length)
    {
        /* no data in line*/
        check = true;
        s19Data[0] = '\0';
    }
    else
    {
        for ( i = (S19_ADDRESS_START_INDEX + addressByte); i < (length-2); i++)
        {
            if (false == (checkHexCharater(str[i])))
            {
                check = false;
                break;
            }
            else
            {
                s19Data[i - (S19_ADDRESS_START_INDEX + addressByte)] = str[i];
            }
        }
        s19Data[i - (S19_ADDRESS_START_INDEX + addressByte)] = '\0';
    }

    return check;
}

/*Function check checksum in line*/
bool checkCheckSum(char str[], int length)
{
    bool check = false;
    uint16_t calCheckSum = 0;
    uint8_t actualCheckSum = 0;
    if (checkHexCharater(str[length-2]) && checkHexCharater(str[length-1]))
    {
        check = true;
        int i;
        for (i = 0; i < (length - S19_RECORD_TYPE_BYTE_COUNT - S19_CHECKSUM_BYTE_COUNT)/2; i++)
        {
            calCheckSum += (ConvertChar2Hex(str[S19_BYTECOUNT_START_INDEX + 2*i]) << 4) + ConvertChar2Hex(str[S19_BYTECOUNT_START_INDEX + 2*i + 1]);
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


