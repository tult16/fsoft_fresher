#ifndef _HEADER_UPDATE_QUEUE_
#define _HEADER_UPDATE_QUEUE_

#include <stdint.h>
#include <stdbool.h>

#define QUEUE_MAX_DATA      528
#define QUEUE_MAX_ELEMENT   4

typedef struct
{
    uint8_t data[QUEUE_MAX_DATA];
} queue_element_struct_t;

typedef struct
{
    queue_element_struct_t element[QUEUE_MAX_ELEMENT];
    uint8_t putIndex;
    uint8_t getIndex;
    uint8_t fillLever;
    uint8_t reserve; // data alignment
} queue_struct_t;

void QUEUE_Init(void);

bool QUEUE_GetUnuseElement(uint8_t **output);

bool QUEUE_GetData(uint8_t **output);

// enqueue
bool QUEUE_Push(void);
// dequeue
bool QUEUE_Pop(void);

#endif /* _HEADER_UPDATE_QUEUE_ */
