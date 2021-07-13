#include "update_QUEUE.h"
///////////////////////////////////////
static queue_struct_t queueList;

void QUEUE_Init(void)
{
    queueList.putIndex = 0;
    queueList.getIndex = 0;
    queueList.fillLever = 0;
}

static int QUEUE_IsFull(void)
{
    bool retVal = false;

    if (QUEUE_MAX_ELEMENT == queueList.fillLever)
    {
        retVal = true;
    }

    return retVal;
}

static int QUEUE_IsEmpty(void)
{
    bool retVal = false;

    if (0 == queueList.fillLever)
    {
        retVal = true;
    }

    return retVal;
}

bool QUEUE_GetUnuseElement(uint8_t **output)
{
    bool retVal = true;
    uint8_t putIndex = 0;

    if (!QUEUE_IsFull())
    {
        putIndex = queueList.putIndex;
        *output = (uint8_t *)&queueList.element[putIndex];
    }
    else
    {
        retVal = false;
    }

    return retVal;
}

bool QUEUE_Push(void)
{
    bool retVal = true;
    uint8_t putIndex = 0;

    if (!QUEUE_IsFull())
    {
        queueList.putIndex = queueList.putIndex + 1;
        queueList.putIndex = queueList.putIndex % QUEUE_MAX_ELEMENT;
        queueList.fillLever++;
    }
    else
    {
        retVal = false;
    }

    return retVal;
}

bool QUEUE_GetData(uint8_t **output)
{
    bool retVal = true;
    uint8_t getIndex = 0;

    if (!QUEUE_IsEmpty())
    {
        getIndex = queueList.getIndex;
        *output = (uint8_t *)&queueList.element[getIndex];
    }
    else
    {
        retVal = false;
    }

    return retVal;
}

bool QUEUE_Pop(void)
{
    bool retVal = true;
    uint8_t getIndex = 0;

    if (!QUEUE_IsEmpty())
    {
        queueList.getIndex = queueList.getIndex + 1;
        queueList.getIndex = queueList.getIndex % QUEUE_MAX_ELEMENT;
        queueList.fillLever--;
    }
    else
    {
        retVal = false;
    }

    return retVal;
}
