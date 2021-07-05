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
#define QUEUE_MAX_SIZE 5

/*******************************************************************************
 * Prototype
 ******************************************************************************/

/**
 * @brief Function insret srec line in queue.
 * @param[in] str_buff
 * @param[in] byte_count
 * @return none
 */
void QUEUE_insert(char *str_buff, uint8_t byte_count);

/**
 * @brief Function get srec line in queue.
 * @param[in] str_out
 * @return true if get queue else false
 */
bool QUEUE_get(char **str_out);

#endif /* _HEADER_QUEUE_ */
