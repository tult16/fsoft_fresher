/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Queue.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static char s_QueueBuffer[QUEUE_MAX_SIZE][SREC_MAX_BYTE_COUNT] = {0};
static int s_QueuFirstIndex = -1;
static int s_QueuLastIndex  = -1;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void QUEUE_SrecLineToBuffer(char *buffSrc, char *buffDest, uint8_t n);

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function insret srec line in queue */
void QUEUE_Insert(char *strBuff, uint8_t byteCount)
{
    if (s_QueuLastIndex == (QUEUE_MAX_SIZE -1))
    {
        s_QueuLastIndex = -1;
        s_QueuFirstIndex = 0;
    }

    if (s_QueuFirstIndex == -1)
    {
        s_QueuFirstIndex = 0;
    }
    s_QueuLastIndex++;
    /* Push one srec line in queue */
    QUEUE_SrecLineToBuffer(strBuff, s_QueueBuffer[s_QueuLastIndex], byteCount);
    s_QueueBuffer[s_QueuLastIndex][byteCount-1] = '\0';
}

/* Function get srec line in queue. */
bool QUEUE_Get(char **str_out)
{
    bool check;

    if ((s_QueuFirstIndex == -1) || (s_QueuFirstIndex > s_QueuLastIndex))
    {
        /* queue is empty */
        check = false;
    }
    else
    {
        *str_out = s_QueueBuffer[s_QueuFirstIndex];
        s_QueuFirstIndex++;
        check = true;
    }

    return check;
}

/* Function push srec line to queue  */
static void QUEUE_SrecLineToBuffer(char *buffSrc, char *buffDest, uint8_t n)
{
    uint8_t j;

    for (j = 0; j < n; j++)
    {
        buffDest[j] = buffSrc[j];
    }
}
