 /******************************************************************************
 * Copyright (C) 2024 by Illia Baliuk
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Illia Baliuk are not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file data.h
 * @brief Abstraction of basic data manipulation
 *
 * @author Illia Baliuk
 * @date March 21 2024
 */

#include <stdint.h>
#include <stddef.h>

#ifndef __DATA_H__
#define __DATA_H__

#define BASE_10 (10)
#define BASE_16 (16)

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);

#endif /* __DATA_H__ */
