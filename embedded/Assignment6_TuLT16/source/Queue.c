/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Queue.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static char s_queue[QUEUE_MAX_SIZE][100] = {0};
static int s_first_index = -1;
static int s_last_index = -1;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void Push_line(char *buffSrc, char *buffDest, uint8_t n);

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function insret srec line in queue */
void QUEUE_insert(char *str_buff, uint8_t byte_count)
{
    if (s_last_index == (QUEUE_MAX_SIZE -1))
    {
        s_last_index = -1;
        s_first_index = 0;
    }

    if (s_first_index == -1)
    {
        s_first_index = 0;
    }
    s_last_index++;
    /* Push one srec line in queue */
    Push_line(str_buff, s_queue[s_last_index], byte_count);
    s_queue[s_last_index][byte_count-1] = '\0';
}

/* Function get srec line in queue. */
bool QUEUE_get(char **str_out)
{
    bool check;

    if ((s_first_index == -1) || (s_first_index > s_last_index))
    {
        /* queue is empty */
        check = false;
    }
    else
    {
        *str_out = s_queue[s_first_index];
        s_first_index++;
        check = true;
    }

    return check;
}

/* Function push srec line to queue  */
static void Push_line(char *buffSrc, char *buffDest, uint8_t n)
{
    uint8_t j;

    for (j = 0; j < n; j++)
    {
        buffDest[j] = buffSrc[j];
    }
}
