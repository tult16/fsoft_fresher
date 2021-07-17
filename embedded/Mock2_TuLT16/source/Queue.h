#ifndef _HEADER_QUEUE_
#define _HEADER_QUEUE_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define QUEUE_MAX_SIZE          4
#define SREC_MAX_BYTE_COUNT     100

/*******************************************************************************
 * Prototype
 ******************************************************************************/

/**
 * @brief Function insret Srec line to queue.
 * @param[in] str_buff Srec line to write to Queue
 * @param[in] byte_count Srec line length
 * @return none
 */
void QUEUE_Insert(char *str_buff, uint8_t byte_count);

/**
 * @brief Function check and get Srec line in queue.
 * @param[out] str_out Srec line in Queue
 * @return true if get queue successfully otherwise return false
 */
bool QUEUE_Get(char **str_out);

#endif /* _HEADER_QUEUE_ */
